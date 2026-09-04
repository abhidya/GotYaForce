//! `*(T *)&aggregate` — reading or writing a small struct through a scalar type.
//!
//! This is the Dolphin SDK's house idiom for a 32-bit-wide colour/flag struct:
//!
//! ```c
//! void GXInitLightColor(GXLightObj *lt_obj, GXColor color) {
//!     __GXLightObjInt *obj = (__GXLightObjInt *)lt_obj;
//!     *(u32 *)&obj->Color = *(u32 *)&color;      /* GXLight.c */
//! }
//! ```
//!
//! and mwcc compiles it to a plain word load and a plain word store — retail
//! Gotcha Force `GXInitLightColor` @ 0x802285f4 is `lwz r0,0(r4); stw r0,0xc(r3);
//! blr`, nothing more. Before this pass mwcc-rs could not compile it at all:
//!
//!   * `*(u32 *)&obj->Color` was rejected outright with *"pointer leaf access
//!     needs a pointer variable (roadmap)"*, because the address operand is a
//!     `Member`, not a pointer variable; and
//!   * `*(u32 *)&color`, on a struct parameter the EABI passes BY REFERENCE,
//!     took `AddressOf` at face value, gave the parameter a stack home and
//!     emitted `stwu; stw r3,8(r1); lwz r3,8(r1); addi r1; blr` — a spill and
//!     reload of a pointer that was already in a register.
//!
//! Both are the same mistake: treating the pun as an address computation when
//! it is only a re-typing of storage that already has an address. So normalise
//! it away before lowering. `*(T *)&X`, where `X` is an aggregate lvalue whose
//! size equals `sizeof(T)`, becomes an ordinary `T`-typed member access at X's
//! own offset — which every existing load/store path already handles, folding
//! the offset into the instruction displacement exactly as retail does.
//!
//! Scope is deliberately narrow:
//!
//!   * only when the punned-through type is a `Type::Struct` — a pun of a
//!     `float` to `u32` is a different question with its own lowering
//!     (`float/punned.rs`), and this pass must not steal it;
//!   * only when the sizes match exactly, so no access is widened or narrowed;
//!   * only for a scalar target type with a defined member access.
//!
//! Every shape it fires on is one that previously produced a hard diagnostic or
//! the spill above, so it cannot silently change code that already compiled.

use mwcc_syntax_trees::{
    ArmBody, Expression, Function, GuardedReturn, Pointee, Statement, SwitchArm, Type,
};

/// The member type a `T *` pun reads, and its byte width. `None` for pointee
/// types with no single-instruction scalar access.
fn punned_member_type(pointee: Pointee) -> Option<(Type, u32)> {
    Some(match pointee {
        Pointee::Int => (Type::Int, 4),
        Pointee::UnsignedInt => (Type::UnsignedInt, 4),
        Pointee::Char => (Type::Char, 1),
        Pointee::UnsignedChar => (Type::UnsignedChar, 1),
        Pointee::Short => (Type::Short, 2),
        Pointee::UnsignedShort => (Type::UnsignedShort, 2),
        Pointee::Float => (Type::Float, 4),
        _ => return None,
    })
}

/// The declared type of a named parameter or local, when it is a struct value.
fn aggregate_size(function: &Function, name: &str) -> Option<u32> {
    let declared = function
        .parameters
        .iter()
        .find(|parameter| parameter.name == name)
        .map(|parameter| parameter.parameter_type)
        .or_else(|| {
            function
                .locals
                .iter()
                .find(|local| local.name == name)
                .map(|local| local.declared_type)
        })?;
    match declared {
        Type::Struct { size, .. } => Some(size),
        _ => None,
    }
}

/// Rewrite this node if it is exactly `*(T *)&aggregate`; the caller has already
/// rewritten its children.
fn rewrite_node(function: &Function, expression: Expression) -> Expression {
    match punned_access(function, &expression) {
        Some(rewritten) => rewritten,
        None => expression,
    }
}

fn punned_access(function: &Function, expression: &Expression) -> Option<Expression> {
    let Expression::Dereference { pointer } = expression else {
        return None;
    };
    let Expression::Cast {
        target_type: Type::Pointer(pointee),
        operand,
    } = pointer.as_ref()
    else {
        return None;
    };
    let (member_type, width) = punned_member_type(*pointee)?;
    let Expression::AddressOf { operand } = operand.as_ref() else {
        return None;
    };
    Some(match operand.as_ref() {
        // `*(T *)&s->member` — retype the member in place, keeping its offset so
        // the access stays a single displacement load/store.
        Expression::Member {
            base,
            offset,
            member_type: Type::Struct { size, .. },
            index_stride,
        } if *size == width => Expression::Member {
            base: base.clone(),
            offset: *offset,
            member_type,
            index_stride: *index_stride,
        },
        // `*(T *)&v` on a struct VALUE. The EABI hands a struct parameter over
        // by reference, so the name already denotes an address: this is the
        // member at offset zero, not a fresh stack home.
        Expression::Variable(name)
            if aggregate_size(function, name) == Some(width) =>
        {
            Expression::Member {
                base: Box::new(Expression::Variable(name.clone())),
                offset: 0,
                member_type,
                index_stride: None,
            }
        }
        _ => return None,
    })
}

fn boxed(function: &Function, inner: &Expression, changed: &mut bool) -> Box<Expression> {
    Box::new(rewrite_expression(function, inner, changed))
}

fn rewrite_all(function: &Function, all: &[Expression], changed: &mut bool) -> Vec<Expression> {
    all.iter()
        .map(|inner| rewrite_expression(function, inner, changed))
        .collect()
}

fn rewrite_body(function: &Function, all: &[Statement], changed: &mut bool) -> Vec<Statement> {
    all.iter()
        .map(|inner| rewrite_statement(function, inner, changed))
        .collect()
}

fn rewrite_arm(function: &Function, arm: &ArmBody, changed: &mut bool) -> ArmBody {
    match arm {
        ArmBody::Return(inner) => ArmBody::Return(rewrite_expression(function, inner, changed)),
        ArmBody::Statements(inner) => ArmBody::Statements(rewrite_body(function, inner, changed)),
    }
}

fn rewrite_expression(function: &Function, expression: &Expression, changed: &mut bool) -> Expression {
    macro_rules! recurse {
        ($inner:expr) => {
            boxed(function, $inner, changed)
        };
    }
    macro_rules! recurse_all {
        ($all:expr) => {
            rewrite_all(function, $all, changed)
        };
    }
    let rebuilt = match expression {
        Expression::IntegerLiteral(_)
        | Expression::FloatLiteral(_)
        | Expression::StringLiteral(_)
        | Expression::Variable(_)
        | Expression::CompoundLiteral { .. } => expression.clone(),
        Expression::AggregateLiteral(items) => Expression::AggregateLiteral(recurse_all!(items)),
        Expression::Binary {
            operator,
            left,
            right,
        } => Expression::Binary {
            operator: *operator,
            left: recurse!(left),
            right: recurse!(right),
        },
        Expression::Unary { operator, operand } => Expression::Unary {
            operator: *operator,
            operand: recurse!(operand),
        },
        Expression::Conditional {
            condition,
            when_true,
            when_false,
            origin,
        } => Expression::Conditional {
            condition: recurse!(condition),
            when_true: recurse!(when_true),
            when_false: recurse!(when_false),
            origin: *origin,
        },
        Expression::Cast {
            target_type,
            operand,
        } => Expression::Cast {
            target_type: *target_type,
            operand: recurse!(operand),
        },
        Expression::BitFieldRead {
            extracted,
            promoted_type,
            storage,
            shift,
            width,
        } => Expression::BitFieldRead {
            extracted: recurse!(extracted),
            promoted_type: *promoted_type,
            storage: recurse!(storage),
            shift: *shift,
            width: *width,
        },
        Expression::IndexedUpdateValue { value } => Expression::IndexedUpdateValue {
            value: recurse!(value),
        },
        Expression::Dereference { pointer } => Expression::Dereference {
            pointer: recurse!(pointer),
        },
        Expression::AddressOf { operand } => Expression::AddressOf {
            operand: recurse!(operand),
        },
        Expression::Index { base, index } => Expression::Index {
            base: recurse!(base),
            index: recurse!(index),
        },
        Expression::Member {
            base,
            offset,
            member_type,
            index_stride,
        } => Expression::Member {
            base: recurse!(base),
            offset: *offset,
            member_type: *member_type,
            index_stride: *index_stride,
        },
        Expression::MemberAddress {
            base,
            offset,
            element,
            index_stride,
        } => Expression::MemberAddress {
            base: recurse!(base),
            offset: *offset,
            element: *element,
            index_stride: *index_stride,
        },
        Expression::CallThrough { target, arguments } => Expression::CallThrough {
            target: recurse!(target),
            arguments: recurse_all!(arguments),
        },
        Expression::VirtualCall {
            object,
            vptr_offset,
            slot_offset,
            return_type,
            variadic,
            arguments,
        } => Expression::VirtualCall {
            object: recurse!(object),
            vptr_offset: *vptr_offset,
            slot_offset: *slot_offset,
            return_type: *return_type,
            variadic: *variadic,
            arguments: recurse_all!(arguments),
        },
        Expression::ConstructedNew {
            allocation,
            allocation_size,
            constructor,
            arguments,
        } => Expression::ConstructedNew {
            allocation: recurse!(allocation),
            allocation_size: *allocation_size,
            constructor: constructor.clone(),
            arguments: recurse_all!(arguments),
        },
        Expression::Call { name, arguments } => Expression::Call {
            name: name.clone(),
            arguments: recurse_all!(arguments),
        },
        Expression::PostStep {
            target,
            operator,
            pointer_link,
        } => Expression::PostStep {
            target: recurse!(target),
            operator: *operator,
            pointer_link: *pointer_link,
        },
        Expression::Assign { target, value } => Expression::Assign {
            target: recurse!(target),
            value: recurse!(value),
        },
        Expression::Comma { left, right } => Expression::Comma {
            left: recurse!(left),
            right: recurse!(right),
        },
    };
    let rewritten = rewrite_node(function, rebuilt);
    if matches!(expression, Expression::Dereference { .. })
        && matches!(rewritten, Expression::Member { .. })
    {
        *changed = true;
    }
    rewritten
}

fn rewrite_statement(function: &Function, statement: &Statement, changed: &mut bool) -> Statement {
    macro_rules! expression {
        ($inner:expr) => {
            rewrite_expression(function, $inner, changed)
        };
    }
    macro_rules! body {
        ($all:expr) => {
            rewrite_body(function, $all, changed)
        };
    }
    match statement {
        Statement::Store { target, value } => Statement::Store {
            target: expression!(target),
            value: expression!(value),
        },
        Statement::Assign { name, value } => Statement::Assign {
            name: name.clone(),
            value: expression!(value),
        },
        Statement::Expression(inner) => Statement::Expression(expression!(inner)),
        Statement::InlineAsm(_) | Statement::Break | Statement::Continue => statement.clone(),
        Statement::Goto(_) | Statement::Label(_) => statement.clone(),
        Statement::If {
            condition,
            then_body,
            else_body,
        } => Statement::If {
            condition: expression!(condition),
            then_body: body!(then_body),
            else_body: body!(else_body),
        },
        Statement::Return(value) => Statement::Return(match value {
            Some(inner) => Some(expression!(inner)),
            None => None,
        }),
        Statement::Switch {
            scrutinee,
            arms,
            default,
        } => {
            let scrutinee = expression!(scrutinee);
            let mut rewritten_arms = Vec::with_capacity(arms.len());
            for arm in arms {
                rewritten_arms.push(SwitchArm {
                    value: arm.value,
                    body: rewrite_arm(function, &arm.body, changed),
                    falls_through: arm.falls_through,
                });
            }
            let rewritten_default = match default {
                Some(arm) => Some(rewrite_arm(function, arm, changed)),
                None => None,
            };
            Statement::Switch {
                scrutinee,
                arms: rewritten_arms,
                default: rewritten_default,
            }
        }
        Statement::Loop {
            kind,
            initializer,
            condition,
            step,
            body: loop_body,
        } => Statement::Loop {
            kind: *kind,
            initializer: match initializer {
                Some(inner) => Some(expression!(inner)),
                None => None,
            },
            condition: match condition {
                Some(inner) => Some(expression!(inner)),
                None => None,
            },
            step: match step {
                Some(inner) => Some(expression!(inner)),
                None => None,
            },
            body: body!(loop_body),
        },
    }
}

/// `Some(rewritten)` when at least one `*(T *)&aggregate` was normalised away;
/// `None` leaves the caller on the original function with no clone.
pub(crate) fn normalize(function: &Function) -> Option<Function> {
    let mut changed = false;
    let statements = function
        .statements
        .iter()
        .map(|statement| rewrite_statement(function, statement, &mut changed))
        .collect::<Vec<_>>();
    let guards = function
        .guards
        .iter()
        .map(|guard| GuardedReturn {
            condition: rewrite_expression(function, &guard.condition, &mut changed),
            value: rewrite_expression(function, &guard.value, &mut changed),
        })
        .collect::<Vec<_>>();
    let return_expression = function
        .return_expression
        .as_ref()
        .map(|value| rewrite_expression(function, value, &mut changed));
    let locals = function
        .locals
        .iter()
        .map(|local| {
            let mut local = local.clone();
            local.initializer = local
                .initializer
                .as_ref()
                .map(|value| rewrite_expression(function, value, &mut changed));
            local
        })
        .collect::<Vec<_>>();
    if !changed {
        return None;
    }
    let mut rewritten = function.clone();
    rewritten.statements = statements;
    rewritten.guards = guards;
    rewritten.return_expression = return_expression;
    rewritten.locals = locals;
    Some(rewritten)
}
