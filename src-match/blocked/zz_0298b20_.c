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
 *
 * ---------------------------------------------------------------------------
 * MEASURED 2026-09-04 -- this is now a QUANTIFIED CEILING, not a guess.
 *
 *   python research/tools/matching-decomp/blocker_census.py --scaled-index
 *
 * Over all 12,062 functions, of the 7,085 `mulli` / power-of-two `slwi` sites
 * whose product is consumed by an address computation:
 *
 *   r0, the scratch ................ 4,706 sites   66.4 %
 *   the index's own register ....... 1,008 sites   14.2 %   <- mwcc-rs's default
 *   a third register ............... 1,371 sites   19.4 %
 *
 * So mwcc-rs's rule -- reuse the index register when its value dies there --
 * is the choice MWCC makes one time in seven.  It is the wrong default, not a
 * tie-break to tune.
 *
 * It is also not a one-line flip, and that was TESTED, not assumed.  Upstream
 * already forces r0 in one place (MEMBER_ARRAY_CALL_CURSOR_PREFIX, in
 * expressions/members.rs).  Forcing that preference to the scratch
 * unconditionally, rebuilding, and re-running this function changed NOTHING --
 * so its `mulli` comes from a different one of the ~40 sites that scale an
 * index.  Closing this needs one register-assignment model for address
 * temporaries applied at every site, which is exactly the "core research
 * target" the README names.  The experiment was reverted.
 *
 * FOR THE LOOP: a candidate that differs only in which register holds a scaled
 * index is not a bad candidate.  The signature is same mnemonic, same
 * immediate, different destination register, and match.py's `first_diff` names
 * it.  Recognise it and stop; do not spend iterations rewriting C against it.
 */

typedef struct E { int field; char pad[0x70]; } E;   /* sizeof == 0x74 */
typedef struct S { char pad[0x114c]; E tbl[1]; } S;

int f(S *s, int index)
{
    return s->tbl[index].field;
}
