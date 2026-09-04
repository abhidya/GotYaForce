//! Non-contiguous signed-immediate masks materialized through the scratch.

#[allow(unused_imports)]
use super::*;

impl Generator {
    /// Emit `leaf & C` when `C` is a signed 16-bit mask that cannot be represented
    /// by one `rlwinm`.
    ///
    /// PowerPC has no non-recording `andi`, and a negative mask such as
    /// `~0x28` must retain its high bits after integer promotion. MWCC therefore
    /// materializes it in r0 and uses a register AND:
    ///
    /// ```text
    /// li  r0,-41
    /// and result,leaf,r0
    /// ```
    ///
    /// Keep this separate from the immediate-form selector: this is a
    /// two-instruction register operation whose scratch lifetime is visible to
    /// allocation and scheduling.
    ///
    /// The POSITIVE masks are the same family and are handled here too, because
    /// `rlwinm` covers only a contiguous run of set bits and mwcc has three
    /// other forms for the rest:
    ///
    /// ```text
    /// x & 0x0EEF      andi.  rA,rS,0xeef             (fits the 16-bit field)
    /// x & 0x0EEF0000  andis. rA,rS,0xeef             (low half empty)
    /// x & 0x00FF1F7F  lis  free,0xff                 (neither: materialize,
    ///                 addi r0,free,0x1f7f             then a register `and`,
    ///                 and  rA,rS,r0                   the constant in r0)
    /// ```
    ///
    /// The three-instruction form is read directly off retail Gotcha Force
    /// `zz_008bbc0_` @ 0x8008bbc0, which is `lis r3,0xff; addi r0,r3,0x1f7f;
    /// and r3,r4,r0` — the constant's high half goes to a free register, the
    /// assembled constant to the scratch, and the operand stays where it is.
    /// That is the same shape the wide-constant `mullw` path already emits,
    /// which is the corroboration that it is mwcc's general rule and not a
    /// one-function coincidence.
    ///
    /// Only a full-width (32-bit) leaf takes the new paths. A narrow leaf needs
    /// the promotion/extension reasoning the surrounding code defers on, and a
    /// wrong `andi.` on an un-extended signed byte is a silent miscompile.
    pub(crate) fn try_emit_materialized_bitand_constant(
        &mut self,
        operator: BinaryOperator,
        variable: &Expression,
        constant: i64,
        destination: u8,
    ) -> Compilation<bool> {
        if operator != BinaryOperator::BitAnd || rlwinm_mask(constant).is_some() {
            return Ok(false);
        }
        let Ok((source, width, _)) = self.leaf_info(variable) else {
            return Ok(false);
        };
        if source == GENERAL_SCRATCH {
            return Ok(false);
        }

        // A negative mask that fits `li`: materialize in the scratch, register AND.
        if constant < 0 && i16::try_from(constant).is_ok() {
            self.load_integer_constant(GENERAL_SCRATCH, constant);
            self.output.instructions.push(Instruction::And {
                a: destination,
                s: source,
                b: GENERAL_SCRATCH,
            });
            return Ok(true);
        }

        if width != 32 || !(0..=u32::MAX as i64).contains(&constant) {
            return Ok(false);
        }
        let value = constant as u32;

        // Low half only: `andi.` takes it, zero-extended, which is exactly the
        // mask. (PowerPC has no non-recording andi; CR0 is volatile.)
        if value <= 0xffff {
            self.output
                .instructions
                .push(Instruction::AndImmediateRecord {
                    a: destination,
                    s: source,
                    immediate: value as u16,
                });
            return Ok(true);
        }

        // High half only: `andis.`, likewise zero-extending the other half.
        if value & 0xffff == 0 {
            self.output
                .instructions
                .push(Instruction::AndImmediateShiftedRecord {
                    a: destination,
                    s: source,
                    immediate: (value >> 16) as u16,
                });
            return Ok(true);
        }

        // Both halves set: build the constant with `lis` + `addi`, the low half
        // sign-extended so the high half is carry-adjusted, and AND against it.
        let low = (value & 0xffff) as i16;
        let high = ((value as i32).wrapping_sub(low as i32) >> 16) as i16;
        let free = self.free_general_excluding(source)?;
        self.output
            .instructions
            .push(Instruction::load_immediate_shifted(free, high));
        self.output.instructions.push(Instruction::AddImmediate {
            d: GENERAL_SCRATCH,
            a: free,
            immediate: low,
        });
        self.output.instructions.push(Instruction::And {
            a: destination,
            s: source,
            b: GENERAL_SCRATCH,
        });
        Ok(true)
    }
}

#[cfg(test)]
mod tests {
    use std::collections::{HashMap, HashSet};

    use mwcc_syntax_trees::{
        Function, InlineExpansionFacts, Parameter, SourceFundamentalType, Type,
    };
    use mwcc_versions::{CompilerConfig, GC_3_0A3};

    use super::*;
    use crate::{lower_function, InlineBodySet, InlineSummaries};

    #[test]
    fn a_non_contiguous_negative_mask_is_materialized_in_r0() {
        let function = Function {
            return_type: Type::Int,
            name: "f".into(),
            is_static: false,
            is_weak: false,
            parameters: vec![Parameter {
                parameter_type: Type::Int,
                name: "x".into(),
            }],
            locals: Vec::new(),
            statements: Vec::new(),
            guards: Vec::new(),
            return_expression: Some(Expression::Binary {
                operator: BinaryOperator::BitAnd,
                left: Box::new(Expression::Variable("x".into())),
                right: Box::new(Expression::IntegerLiteral(-41)),
            }),
            section: None,
            preceded_by_asm: false,
            asm_body: None,
            inline_asm_blocks: Vec::new(),
            force_active: false,
            text_deferred: false,
            peephole_disabled: false,
        };
        let fundamentals =
            HashMap::from([(function.name.clone(), SourceFundamentalType::SignedInteger)]);
        let mut config = CompilerConfig::new(GC_3_0A3);
        config.flags.cpp_exceptions = false;

        let machine = lower_function(
            &function,
            &[],
            &HashMap::new(),
            &HashMap::new(),
            &HashMap::new(),
            &HashMap::new(),
            &HashSet::new(),
            &HashSet::new(),
            &HashSet::new(),
            &HashSet::new(),
            &HashMap::new(),
            &HashMap::new(),
            &InlineBodySet::default(),
            &InlineSummaries::default(),
            InlineExpansionFacts::default(),
            &HashMap::new(),
            &fundamentals,
            config,
        )
        .expect("materialized mask should lower");

        assert_eq!(
            machine.encode_text(),
            [0x3800_ffd7_u32, 0x7c63_0038, 0x4e80_0020,]
                .into_iter()
                .flat_map(u32::to_be_bytes)
                .collect::<Vec<_>>()
        );
    }

    /// One `int` parameter named `x`, returning `x & mask`.
    fn lower_masked_return(parameters: Vec<&str>, leaf: &str, mask: i64) -> Vec<u8> {
        let function = Function {
            return_type: Type::Int,
            name: "f".into(),
            is_static: false,
            is_weak: false,
            parameters: parameters
                .into_iter()
                .map(|name| Parameter {
                    parameter_type: Type::Int,
                    name: name.into(),
                })
                .collect(),
            locals: Vec::new(),
            statements: Vec::new(),
            guards: Vec::new(),
            return_expression: Some(Expression::Binary {
                operator: BinaryOperator::BitAnd,
                left: Box::new(Expression::Variable(leaf.into())),
                right: Box::new(Expression::IntegerLiteral(mask)),
            }),
            section: None,
            preceded_by_asm: false,
            asm_body: None,
            inline_asm_blocks: Vec::new(),
            force_active: false,
            text_deferred: false,
            peephole_disabled: false,
        };
        let fundamentals =
            HashMap::from([(function.name.clone(), SourceFundamentalType::SignedInteger)]);
        let mut config = CompilerConfig::new(GC_3_0A3);
        config.flags.cpp_exceptions = false;
        lower_function(
            &function,
            &[],
            &HashMap::new(),
            &HashMap::new(),
            &HashMap::new(),
            &HashMap::new(),
            &HashSet::new(),
            &HashSet::new(),
            &HashSet::new(),
            &HashSet::new(),
            &HashMap::new(),
            &HashMap::new(),
            &InlineBodySet::default(),
            &InlineSummaries::default(),
            InlineExpansionFacts::default(),
            &HashMap::new(),
            &fundamentals,
            config,
        )
        .expect("masked return should lower")
        .encode_text()
    }

    fn text(words: &[u32]) -> Vec<u8> {
        words.iter().copied().flat_map(u32::to_be_bytes).collect()
    }

    #[test]
    fn a_non_contiguous_positive_mask_inside_16_bits_uses_andi() {
        // `x & 0xeef` -> andi. r3,r3,0xeef ; blr
        assert_eq!(
            lower_masked_return(vec!["x"], "x", 0xeef),
            text(&[0x7063_0eef, 0x4e80_0020])
        );
    }

    #[test]
    fn a_non_contiguous_mask_in_the_high_half_uses_andis() {
        // `x & 0x0eef0000` -> andis. r3,r3,0xeef ; blr
        assert_eq!(
            lower_masked_return(vec!["x"], "x", 0x0eef_0000),
            text(&[0x7463_0eef, 0x4e80_0020])
        );
    }

    #[test]
    fn a_wide_non_contiguous_mask_is_built_with_lis_addi_and_anded() {
        // Retail Gotcha Force zz_008bbc0_ @ 0x8008bbc0, byte for byte:
        //   lis r3,0xff ; addi r0,r3,0x1f7f ; and r3,r4,r0 ; blr
        // The first parameter is dead, so its register is the free one the
        // constant's high half lands in.
        assert_eq!(
            lower_masked_return(vec!["unused", "value"], "value", 0x00ff_1f7f),
            text(&[0x3c60_00ff, 0x3803_1f7f, 0x7c83_0038, 0x4e80_0020])
        );
    }

    #[test]
    fn a_contiguous_mask_still_takes_the_rlwinm_path() {
        // `x & 0xff` is one `clrlwi` (rlwinm r3,r3,0,24,31); the new paths must
        // not steal it.
        assert_eq!(
            lower_masked_return(vec!["x"], "x", 0xff),
            text(&[0x5463_063e, 0x4e80_0020])
        );
    }
}
