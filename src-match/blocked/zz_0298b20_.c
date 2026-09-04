/* BLOCKED  zz_0298b20_ @ 0x80298b20  (4 instructions)  -- NOT MATCHED
 *
 *   80298b20  1c040074  mulli r0, r4, 0x74
 *   80298b24  7c630214  add   r3, r3, r0
 *   80298b28  8063114c  lwz   r3, 0x114c(r3)
 *   80298b2c  4e800020  blr
 *
 * This one COMPILES.  It is the register allocator that diverges:
 *
 *   retail     mulli r0, r4, 0x74      <- scaled index through the scratch
 *   mwcc-rs    mulli r4, r4, 0x74      <- reuses the dead input register
 *
 * Instructions 2-4 are identical; the oracle reports MISMATCH at 50 %.
 * FOUR different C spellings were tried -- struct-array member, unsigned
 * index, an explicit cast to a pointer-to-element, and a named intermediate
 * pointer -- and all four produced the same divergence.  It is not reachable
 * from the source.
 *
 * mwcc-rs's own README calls matching MWCC's exact register colouring "the
 * single hardest part of the whole project".  Treat this class as out of
 * scope rather than as something a better candidate would fix.
 */

typedef struct E { int field; char pad[0x70]; } E;   /* sizeof == 0x74 */
typedef struct S { char pad[0x114c]; E tbl[1]; } S;

int f(S *s, int index)
{
    return s->tbl[index].field;
}
