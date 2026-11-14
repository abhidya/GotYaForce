# Ground height-plus-normal query: fixed evidence, 2026-11-14

## Scope and authentication

`research/tools/matching-decomp/read_archived_ground_query_evidence.py` selects
only the complete independently named `8003e0a8/844` and `800677b0/544`
instruction spans and five instruction-named scalars. It authenticates the
whole source before selection, using the unchanged existing full-file hashes,
schema/language checks, Program metadata, empty File Bytes, address map,
text1/data3/data5 mapping controls, full data5 hash and independent controls.
It retains exact mapping types, root, offsets, lengths, bounds and overlap
rejection. No arbitrary-address CLI, pointer following, broad table dump,
raw executable payload, original instruction execution or runtime telemetry
is introduced. Shared reader allowlists are unchanged.

Both local snapshots authenticate:

- db.3.gbf: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`
- db.4.gbf: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`

They agree on every new derived instruction operand, scalar, mapping and
physical trace. Import metadata says `boot.dol`, Ghidra12.1.2, executable
SHA256 `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
as property type2. This is metadata, not proof that bytes still match the
original DOL. File Bytes is version0, root−1, count0. Full data5 SHA256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

| Named span | Bytes / instructions | SHA256 | Root/data | Chain/data/physical offset |
| --- | --- | --- | --- | --- |
| `8003e0a8`–`8003e3f4` | 844 / 211 | `4310809c29ad48750521ad16c4e2f47192b2c69b1d3dc357d613870af21d1708` | 21/36 | 232136/2844/609058 |
| `800677b0`–`800679d0` | 544 / 136 | `09ab80886742547a9862056d729a3b23984007549f8cd636ea2d5cf3e63bf246` | 21/46 | 401872/8800/778854 |

Both chains are obfuscated. All347 instructions and all their operands are
represented, including prologues, paired register saves/restores, branch
condition fields and record bits. Frozen complete operand schedules are
independently inverse-encoded to both span hashes in the focused test.

Extents come from adjacent named C markers in `chunk_0004.c:7349–7486`
(`3e0a8`, `3e3f4`) and `chunk_0008.c:3978–4060` (`677b0`, `679d0`), with
terminal `blr` instructions at `3e3f0` and `679cc`. The symbol-map row for
`677b0` independently gives size220 hexadecimal. There is no `3e0a8` map
row; its width is not claimed to be map-derived.

## Reused exact evidence

The new reader reports references rather than reselecting these prior ranges:

- [Terrain query evidence](terrain-query-evidence-2026-11-13.md): shared
  `3fb00/88` XZ range test, `3f320/872` ceiling query, and `3fa68/152`
  floor-list lookup. These exact prior fixed hashes are unchanged. The prior
  reader omits only link-register save/restore instructions where present;
  its arithmetic, load/store and branch evidence remains available.
- [Double action evidence](double-action-envelope-evidence-2026-11-14.md):
  paired subtract `20ba78/36`, scale `20ba9c/28`, add `20ba54/36`, and
  post-ground phase0 `ff30c/268`. The current reader neither duplicates
  their selection nor changes their allowlists.
- Existing fixed constants: `80436f68=+0`, `80436f78=1`,
  `804375d0=+0`; grid size `80436ffc=500`, signed conversion bias
  `80436f88`, XZ bounds `80437034=-7500` and `80437038=7500`.
  The prior `80436f70=-0.5` witness describes the excluded nonempty ceiling20
  path, not a newly admitted runtime branch.

The focused local tests revalidate these exact prior fixed spans/constants
through their unchanged original readers in both authenticated snapshots.
They do not select pointer-returned addresses or the rest of any table.

## Newly selected scalars

| Address | Width | Bits | Value / purpose | Chain=data offset | Physical offset |
| --- | --- | --- | --- | --- | --- |
| `8043702c` | 4 | `c59c4000` | −5000, outside height | 1548 | 4343314 |
| `804375f8` | 4 | `2edbe6fe` | 9.999999439624929e−11, squared displacement threshold | 3032 | 4344798 |
| `804375d4` | 4 | `3f666666` | 0.8999999761581421, steep-slope damping | 2996 | 4344762 |
| `80437600` | 8 | `3fe0000000000000` | 0.5, double sqrt refinement | 3040 | 4344806 |
| `80437608` | 8 | `4008000000000000` | 3.0, double sqrt refinement | 3048 | 4344814 |

All use root263/data264 and obfuscation. Exact per-scalar SHA256 and physical
traces are emitted by the reader and frozen in its tests. New selected bytes
total1416:1388 code and28 scalars. Reused references do not count as new bytes.
The recorded r2/r13 bases are `8043ea20`/`8043b5a0`, not authenticated live
register values. The terrain owner loaded through r13−21316 is `8043625c`;
this global and its pointee are not selected from the archive.

## Distinct `3e0a8` query order

The query receives clearance in f1, actor r3, point r4, output normal r5.
Its actual owner is signed actor byte1db, not targetCC or actor1e4.

The nonzero1db branch loads actor1e0, then its matrix pointer60, calls
`8020b7a8` with actor1f8 and a local vector, copies actor normal words
1ec/1f0/1f4 into the caller's normal in XYZ order and returns localY. That
matrix/support path is represented but not implemented by this evidence.
Do not manufacture a zero-support result for it.

The zero-support path:

1. Loads +0 and1, writes caller normalX/Y/Z=(0,1,0) at
   `3e130/134/138`, then calls the actual XZ test3fb00 at `3e13c`.
   Outside XZ bounds returns freshly loaded **−5000** at `3e148`.
   It does not return pointY as3d6e4 does and does not return a status.
2. Loads the terrain owner and initial upper34. At `3e15c–168`, saves
   whether **original** clearance>=upper, before adjusting clearance.
3. Captures pointX into local+2c, loads pointY then actor6d0, adds single
   and stores localY, then captures pointZ. Loads actor30 savedGroundPos.y,
   then previousStep6d4, adds single and calls real3f320 at `3e19c`.
   The existing ceiling query visits owner24 then owner20 and uses the
   actual indexed cell lists. Empty lists retain that query's upper value.
4. After the ceiling call, freshly loads actor30, captures ceiling f31,
   loads6d4, actor24 and6d0, computes separately rounded previous sum,
   current sum and difference. If the difference>0, adds it to clearance.
   Reloads original pointY at `3e1d0` and adds it to adjusted clearance.
5. Calls real3fa68 on the original point at `3e1dc`, obtaining floor1c's
   cell list. Reloads terrain owner, lower68 then upper34, initializing
   eligible best and maximum to lower, minimum to upper. Initializes both
   fallback normals to (0,1,0). The scan's XZ deltas use the previously
   captured localX/localZ, not fresh original-point coordinates.

### Triangle and normal captures

Each list entry is tested against `0xffffffff`. For each actual triangle,
three separately rounded XZ cross-product comparisons reject an outside
point; edge equality is included. No absolute area epsilon is invented.

The normal loads are **raw words**: nx at `3e284`, nz at `3e288`, ny at
`3e290`. The sequence is nx/nz reads, local nx store, ny read, local nz
store, float nx/nz local loads, local ny store. It then executes:

1. `3e2a4`: single multiply nx*dx.
2. `3e2a8`: single multiply nz*dz.
3. `3e2ac`: read triangle vertex0.y; `3e2b0`: load captured ny.
4. `3e2b4`: single add the first two products.
5. `3e2b8`: single multiply ny*vertex0.y.
6. `3e2bc`: single add that product.
7. `3e2c0`: single divide by captured ny.

**There is no fused multiply-add in3e0a8.** A flat-floor admission must still
use these captures and rounding stages, not replace the height calculation
with an unexplained direct vertexY lookup. Candidate normal stores reuse
captured nx/ny/nz words; the triangle normal is not reread afterward.

Eligible best requires height<adjusted clearance+pointY, height<ceiling,
and best<=height. It writes caller normal XYZ at `3e2e0/2e8/2ec` and retains
height. Minimum fallback updates for height<=minimum; maximum updates for
maximum<=height. All three retain the **later** normal on admitted equal-height
ties. The minimum/maximum copies reload captured local normal words.

If original clearance>=initial upper, `3e35c–370` copies maximum normal:
load X, load Y, store outX, load Z, store outY, store outZ; returns captured
maximum. Otherwise it reloads terrain owner/lower at `3e378/37c` and uses
`fcmpu` to test best==fresh lower. If unequal it returns best. If equal it
copies minimum normal using the same load/load/store/load/store/store pattern
at `3e390–3a4`, reloads terrain owner/upper, and tests minimum==fresh upper
with `fcmpu` at `3e3b0`. Equality returns fresh lower68, otherwise minimum.
These final owner reads and normal stores must not be replaced with an eager
whole-state snapshot. Output/point aliasing needs an explicit admission rule.

## `677b0` ground helper and boundaries

The complete helper first reads/sign-extends canonical actor7c9. Nonzero
returns0 without query. Zero loads hover668 into f1 at `677e4`, supplies
actor+20 in r4 and a caller-local normal in r5, and calls3e0a8 at `677f0`.
After return it **freshly** loads posY24 at `677f4`, captures height f31,
loads step6d0 at `677fc`, adds single at `67800`, and compares at `67804`.
CurrentY+step>height returns0; equality continues to contact work.

Only after that comparison does `67814/18` freshly read/sign-extend1db.
For zero, it calls the already authenticated paired subtract20ba78 using
position20 minus savedGroundPos2c into a local vector. That callee loads both
XY inputs and stores XY before either sourceZ load; GQR0/W0 supplies XY and
GQR0/W1 supplies Z. Squared displacement is explicitly single x*x, y*y, z*z,
then **(x*x+y*y), followed by z*z+that sum**. Above804375f8 it calls general
normalization20bab8 and dot20bb58, returning0 when dot>0. Those callees are
not newly selected or implemented here. A bounded no-contact helper can
refuse before the subtract after the fresh1db read; it cannot claim contact
or landing by skipping these calls.

Next, slopeMode698>0 selects signed descriptor4b0+ae; otherwise signed
4b0+ac. These are not actor4ac parameter+ae turn rate. Horizontal normal
magnitude uses separately rounded x*x+z*z. If positive, `frsqrte` at678cc
begins three double refinements using0.5 and3. Each correction uses actual
**`fnmsub`**, not separate multiply/subtract. The final multiplication is
rounded by `frsp` at6790c and a store/reload before BAM helper452a0.
Decoding this sequence does not supply a numerical implementation of
`frsqrte`. A flat normal skips the sqrt branch but still calls452a0(0,ny).
The existing table-byte direction result is not evidence for a BAM result.

If the signed returned angle exceeds the signed descriptor limit, helper
45238 supplies the cosine; height−fresh posY is multiplied by it, then the
normal is scaled and added through the prior paired helpers. The code stores
hDecel4c=0, then damps fresh hSpeed44, then fresh yVel48 by0.9 and returns0.
Otherwise it loads step6d0, stores posY=height−step at67990 **before** loading
onLand754 at67994. A nonnull callback is invoked and only then returns1.
Neither null callback nor descriptor limits may be guessed.

## Post-ground phase0 remains source ordered

The unchanged complete `ff30c` witness establishes the continuation only after
677b0 returns: signed config0 from80433868 to byte6ea, fresh control40 test,
optional signed config1 from8043386a to6ea; capture6ea atff3cc, calculate
incrementff3dc, sign-extend the captured byte to the stream slot atff3e0,
store incremented6ea atff3e4. Real4beb8 is called atff3f4 with mask15,
group4, captured signed slot, rate−1 and trailing−1/−1. Only afterward does
ff3fc store80c=0. Config is an address, not a callback pointer. No new
post-ground selection or legacy stream schedule is introduced here.

## Reproduction and ceiling

From the repository root, without fetching inputs:

```sh
python -m unittest discover -s research/tools/matching-decomp -p test_archived_ground_query_evidence.py -v
python -m unittest discover -s research/tools/matching-decomp -p test_archived_double_action_evidence.py -v
python -m unittest discover -s research/tools/matching-decomp -p test_archived_terrain_query_evidence.py -v
python research/tools/matching-decomp/read_archived_ground_query_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_ground_query_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

The new suite passes **22 tests**, including both local archives. Unchanged
Double and terrain-query suites pass19 and16 tests. Inverse-encoding tests
need no archive; missing local archives skip rather than fetch. Guards cover
selection/type/duplicate/width/hash errors, mappings and schemas before new
reads, unknown instructions, terminal/branch extents, reserved fields,
scalar values and forbidden CLI options. Exact prior witnesses are rechecked.

This is focused static evidence, not contributor/docs aggregates, original
DOL execution, live numerical parity, browser integration or playability.
The bounded finite-input host domain needs FPSCR RN00/NI0 and GQR0 type0,
scale0 as explicit assumptions, not authenticated live settings. Nonzero
support, nonempty ceilings, general floor normals, displacement normalization,
BAM slope conversion, steep response and landing callback execution need
separate implementation admission and tests. No full Double action, clone
allocation, later shared-X phase or complete actor-frame claim follows.
