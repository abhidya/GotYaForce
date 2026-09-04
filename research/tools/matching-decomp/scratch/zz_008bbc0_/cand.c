/* Candidate for zz_008bbc0_ @ 0x8008bbc0 -- UNVERIFIED, NEVER COMPILED.
 *
 * mwcceppc.exe is not on this machine, so this candidate has not been through
 * the oracle. It is here to show what the loop submits, not what it achieved.
 *
 * Reading of the target: r3 is written but never read, so the incoming r3 is
 * dead. Under the EABI that is what a C++ member function looks like when it
 * ignores `this`. This game is C++ -- the link map carries mangled names such
 * as cCameraManager::HasCamera -- so that is the first hypothesis to try.
 *
 * 0x00FF1F7F is a mask, not an address: bits 0..6, 8..12, 16..23.
 */

typedef unsigned long u32;

struct Obj;

u32 Obj_maskField(struct Obj *self, u32 v)
{
    return v & 0x00FF1F7Ful;
}

/* Feedback the diff would give, and the next move for each case:
 *
 *  - candidate emits lis+ori where retail has lis+addi
 *      -> not a source problem; an -opt / codegen flag difference. Re-run the
 *         flag calibration in spike doc section 2.4.
 *  - the argument arrives in r3 rather than r4
 *      -> the `self` hypothesis is wrong; make it a free function of one arg.
 *  - `and` has rS and rB swapped (0x7c640038 instead of 0x7c830038)
 *      -> write `MASK & v` instead of `v & MASK`. A one-token fix, and
 *         exactly the kind of thing the byte diff localises for free.
 */
