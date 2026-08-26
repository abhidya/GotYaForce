// =============================================================================
// adapters/damage.ts — real bridged-callee adapters for the damage path,
// backed by the existing TS scaffold (design I1: "the TS scaffold MAY back an
// adapter's logic ... but the adapter owns marshalling — state moves into and
// out of GC memory at the adapter boundary, never implicitly through TS
// object state").
//
// The symbols are the damage seam's own functions — the exact contract the
// oracle-verified wasm unit was proven against (packages/combat/src/rom/
// wasmDamageCore.ts, byte-exact over 26,232 replayed cases), which is the
// evidence these adapters derive their memory contracts from:
//
//   zz_003d344_ @ 0x8003d344  apply_hp_damage_subtract_clamp
//     reads  target+0x1c4 (u16 maxHp), target+0x1c6 (s16 hp)
//     writes target+0x1c8 (s16 pre-subtract HP mirror), target+0x1c6 (s16
//            clamped HP) — HP==0 is a no-op including the mirror
//     (chunk_0004.c:6832-6860; wasmDamageCore.ts applyHpDamage)
//
//   zz_0066298_ @ 0x80066298  lookup_type_category_table
//     reads  *argptr[0] as 2 bytes: [0]=family, [1]=variant (borgNumber is
//            stored big-endian bytewise — family HIGH byte first)
//     returns the canonical category 0..19 (chunk_0008.c:2976-2982)
//
// Addresses are parameterizable ONLY as a test affordance (the browser
// self-test runs the same adapter logic inside a small synthetic-arena
// module); production registration uses the ROM addresses below.
// =============================================================================

import { applyHpDamage, lookupTypeCategory, type SourceDamageTarget } from "@gf/combat";
import { defineAdapter, type BridgedCalleeAdapter } from "../adapters.js";
import { FrameValueClass } from "../frame.js";

/** GC address of zz_003d344_ (apply_hp_damage_subtract_clamp). */
export const GC_APPLY_HP_DAMAGE_ADDR = 0x8003d344;
/** GC address of zz_0066298_ (lookup_type_category_table). */
export const GC_LOOKUP_TYPE_CATEGORY_ADDR = 0x80066298;

/**
 * Adapter for zz_003d344_(target, amount) -> void.
 *
 * Marshalling is adapter-owned end to end: the target struct is READ from GC
 * memory at the pointer the frame carries, the scaffold computes on a
 * transient TS object, and the observable writes a linked callee would have
 * made (+0x1c6 clamped HP, +0x1c8 pre-subtract mirror) are written BACK to GC
 * memory. No TS object state survives the call.
 */
export function createApplyHpDamageAdapter(gcAddr: number = GC_APPLY_HP_DAMAGE_ADDR): BridgedCalleeAdapter {
  return defineAdapter({
    gcAddr,
    name: "zz_003d344_",
    evidence:
      "oracle-verified seam contract: packages/combat/src/rom/wasmDamageCore.ts applyHpDamage " +
      "(research/decomp/data/oracle-results/damage-core.json); source chunk_0004.c:6832-6860",
    retClass: FrameValueClass.VOID,
    service(ctx) {
      const targetPtr = ctx.frame.u32Arg(0);
      const amount = ctx.frame.i32Arg(1);
      // Unmarshal the callee-read fields from the shared arena.
      const target: SourceDamageTarget = {
        maxHp: ctx.mem.readU16(targetPtr + 0x1c4),
        hp: ctx.mem.readI16(targetPtr + 0x1c6),
      };
      const before = target.hp;
      // Scaffold-backed compute (packages/combat sourceDamage.applyHpDamage —
      // the 1:1 TS port of the same function).
      applyHpDamage(target, amount);
      // Marshal the linked callee's write set back to GC memory. ROM
      // semantics: HP==0 is a no-op, including the prevHp mirror.
      if (before !== 0) {
        ctx.mem.writeI16(targetPtr + 0x1c8, target.prevHp ?? before);
        ctx.mem.writeI16(targetPtr + 0x1c6, target.hp);
      }
      return ctx.frame.setRetVoid();
    },
  });
}

/**
 * Adapter for zz_0066298_(borgNumberPtr) -> i32 category.
 *
 * The pointer argument is dereferenced in the shared arena: byte 0 = family,
 * byte 1 = variant (the ROM stores borgNumber big-endian bytewise). The
 * scaffold's remap-table lookup backs the logic; the category returns through
 * the frame's authoritative ret slot.
 */
export function createLookupTypeCategoryAdapter(
  gcAddr: number = GC_LOOKUP_TYPE_CATEGORY_ADDR,
): BridgedCalleeAdapter {
  return defineAdapter({
    gcAddr,
    name: "zz_0066298_",
    evidence:
      "oracle-verified seam contract: packages/combat/src/rom/wasmDamageCore.ts lookupTypeCategory " +
      "(research/decomp/data/oracle-results/damage-core.json); source chunk_0008.c:2976-2982",
    retClass: FrameValueClass.I32,
    service(ctx) {
      const ptr = ctx.frame.u32Arg(0);
      const family = ctx.mem.readU8(ptr);
      const variant = ctx.mem.readU8(ptr + 1);
      const category = lookupTypeCategory((family << 8) | variant);
      return ctx.frame.setRetI32(category);
    },
  });
}
