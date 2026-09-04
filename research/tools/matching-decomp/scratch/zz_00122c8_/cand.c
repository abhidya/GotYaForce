/* Candidate for zz_00122c8_ @ 0x800122c8 -- UNVERIFIED, NEVER COMPILED.
 *
 * RETAIL:
 *   800122c8  9421fff0  stwu r1, -0x10(r1)     <- stwu FIRST: the MWCC frame
 *   800122cc  7c0802a6  mflr r0
 *   800122d0  90010014  stw  r0, 0x14(r1)
 *   800122d4  48000035  bl   0x80012308        <- R_PPC_REL24 in a fresh .o
 *   800122d8  80010014  lwz  r0, 0x14(r1)
 *   800122dc  7c0803a6  mtlr r0
 *   800122e0  38210010  addi r1, r1, 0x10
 *   800122e4  4e800020  blr
 *
 * A forwarding wrapper. MWCC does not tail-call by default, which is why a
 * frame is built and torn down around a single bl. Arguments pass through
 * untouched -- r3.. are never rewritten -- so the wrapper's parameter list
 * must be exactly the callee's, or MWCC emits register shuffling the retail
 * code does not have.
 *
 * This is the target that exercises the relocation path. In a fresh object
 * the bl encodes as 0x48000001 with an R_PPC_REL24 naming the callee, and
 * objdiff.py masks that operand field and compares the SYMBOL instead.
 * selftest.py T6 proves that path with a synthetic ELF32-BE object; T7 shows
 * that without the relocation the same object would be a false MISMATCH.
 */

struct Ctx;

extern void zz_0012308_(struct Ctx *ctx);

void zz_00122c8_(struct Ctx *ctx)
{
    zz_0012308_(ctx);
}
