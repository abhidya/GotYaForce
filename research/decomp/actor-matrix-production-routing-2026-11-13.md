# Actor matrix production routing, 2026-11-13

Read-only assessment baseline: `ffd19f7d`, `feat/double-clone-lifecycle`.
This note records source ordering and production ownership boundaries. It does
not enable production execution or establish original-input replay.

## Source callsites and timing

All source paths below are relative to `research/decomp/ghidra-export/`.

- `chunk_0006.c:6958–6994`, `54070`: snapshot previous transforms through
  `5685c`; conditionally dispatch lifecycle18 under the 3e5/globalD2 gate;
  perform terrain/contact adjustment; call `5a580`; call `465fc` when
  lifecycle18 is 1 or 2; then clear contact fields and perform cleanup. Matrix
  work is outside the inner lifecycle inhibition gate.
- `chunk_0005.c:2986–3022`: `465fc` gates on 4a0!=2, calls `46754`, then
  `46bd0(actor,0)`. When 661==0 it additionally calls `46e7c` and
  `46bd0(actor,1)`. Conditional `47904` and `47a2c` follow. `46698` has the
  same 4a0 gate but only calls `46754` and `46bd0(actor,0)`.
- `chunk_0007.c:1221–1235`, `581b8`: snapshot previous transforms; dispatch
  its separate lifecycle table; call `46698` only when lifecycle18==1;
  perform cleanup. This alternate caller does not justify replacing normal
  `54070 →465fc` with the first-pass-only helper.
- `chunk_0005.c:3024–3034`, `466dc`: when 4a0!=2, call `465fc`, then
  `896d0`. The collision/action phase `battle_frame_target_action_dispatch`
  reaches this wrapper at `chunk_0003.c:6331` after reaction/forced-movement
  processing or a change reported by `5a580`. Scale helper `2caa8` also
  reaches it at `chunk_0003.c:6444` after storing actor scale fields.
- Family callbacks can request an explicit first-pass refresh before reading
  matrix coordinates. For example, `73330` clears correction shorts, calls
  `46698`, then reads joint coordinates at `chunk_0010.c:925–937`.

Thus matrix refresh is not universally once per actor tick or once per frame.
Preserve reached source calls. A frame-number deduplication guard or a single
unconditional end-of-frame refresh would change behavior.

`48648` at `chunk_0005.c:4232–4257` completes the selected setup handler,
then for part 1 stores 6d8 and calls `4d08c`. There is no intervening matrix
rebuild. Setup captures pose, while movement can consume retained matrices.

## Actual actor matrix boundary

`46bd0` at `chunk_0005.c:3221–3257` builds the root from actor translation,
short rotations, conditional 6b8 yaw correction and actor scale. It copies the
root to 114 and 1aa4, adjusts 1ac0 by 6d0, then selects traversal 4679c or 46914.

`4679c` at `chunk_0005.c:3062–3115` uses actor hierarchy 1994 and mask 1d70.
The byte1 recursive branch receives the incoming parent index; byte0
continuation receives the current joint as parent. A disabled joint retains
its matrix, but traversal still continues. This is not the imported JObj tree.

Joint 1 applies `457d4` wrappers in z,x,y order using 1d68/1d64/1d66 and
passes 1d54 as translation. `46754` derives that translation from 12e0 and 1dbc,
or writes only its Y component under 48a&6. Ordinary joints use captured
bank-zero translation 12d4. Rendering later copies actor matrices into JObj+44
(`chunk_0007.c:308–405`), not the other way around.

At the assessed baseline, `packages/combat/src/rom/actor-joint-matrix.ts`
implements only the explicit 46dd4 callee with supplied parent, actual pose,
zero correction shorts and exact (+0,+0,+0,1) quaternion. Its pose-translation
input cannot silently substitute for joint 1's special translation. A caller
extension must resolve that source explicitly without rewriting captured pose.
`actor-movement-followup.ts:174–220` reads retained matrix element 7 through
the existing owner; it must not generate matrices during those reads.

## Production ownership conflicts

- `packages/combat/src/battle.ts:635` attaches the legacy bridge.
  `bridge.ts:2102–2163` creates a `RomActor`, configures family behavior and
  supplies movement parameters. It does not construct the new source-owned
  setup/playback/mapping/matrix graph.
- The inspected setup, animation-dispatch, joint-mapping, joint-matrix and
  movement-followup constructors have no production callers outside their
  definitions and selftests at this baseline.
- `Battle.step` already writes actor state before `bridge.tick`: history and
  reaction observations at 1153–1159, aura/drain handling at 1165–1173,
  input/AI processing, status/ammo/gauges at 1222–1232, death/hit handling
  at 1267–1298 and charge bookkeeping from 1301. Owner selection at 1334 is
  therefore too late to exclude overlapping host mutations.
- `bridge.ts:2947–2950` runs the family update before returning for inactive
  specials. Active paths synchronize fields, dispatch, clamp motion, advance
  stream events and resolve hits. Action admission can already dispatch at
 2703 and 2893. These are action-specific ownership paths, not an exclusive
  source actor lifecycle.
- `rom/state-tables.ts:308–320` implements only prehook, saved-FB selection,
  UB, FB and posthook. It is not the complete 55568 or 54070 envelope.
  UB 62 reaction and UB 63 death remain listed as unported at 259–267.
- `apps/game/src/sim/battleView.ts:27–30,73–74` exposes a clip reference and
  optional playhead. `battleScene.ts:1364–1387` seeks a baked Three clip;
  its update loop at 961–969 advances presentation mixers. Neither is a
  source actor-matrix presentation path.

## Remaining input and lifecycle requirements

Production needs verified model/animation DAT selection, actor-to-model bank
and map provenance, actor hierarchy/update mask, bind poses and initial
matrices. It also needs real family/shared program banks1d80/1d84,
metadata1d88/1d8c, archive banks1d78/1d7c, part state/boundaries, timestep and
an explicit admitted numeric profile. Legacy frameClock, baked clips and
animation labels cannot supply these fields.

The existing setup composition executes actual bounded mode0 setup, attachment,
packed playback and pose capture. It does not support every reached setup or
animation mode, linked continuation, transformation or attachment case. Actual
actors also require the matrix domains they reach: joint 1 wrappers, nonzero
Euler/general quaternion, root generation and normal465fc's terrain/second
pass/postprocessing. An unsupported effect cannot be replaced with a no-op.

Exclusive production ownership additionally requires supported lifecycle,
input/status/gauge/motion/reaction and accepted-contact processing, including
collision-time immediate reactions and matrix refreshes. Current bounded
runtime refusals retain prior effects; no verified whole-step fallback or
rollback contract exists.

## Implementation recommendation

Extend the existing actual-DAT/setup/playback integration in
`rom/attached-setup-animation.selftest.ts:358–409` from its supplied-parent
46dd4 demonstration to a real admitted actor traversal. Keep matrix calls
explicit and share the existing pose and matrix owners. Do not add a clock or
refresh inside setup, movement or matrix getters.

Production composition should eventually create one source actor owner at
spawn, with real inputs, and select its route before all overlapping host
writes. Enable a bounded offline Battle scenario only after its reachable
lifecycle/contact closure is supported, preserving actor-sweep-before-contact
ordering and the separate explicit matrix callsites. Do not enable a live
mode, infer missing data, or hand a partially mutated actor back to host logic.

This assessment ran no tests or aggregates and made no runtime changes.

## Subsequent bounded normal-caller implementation

The earlier assessment above remains a record of its baseline. The current
local implementation adds explicit `actor-world-matrix.ts` first-pass stages
and `actor-matrix-update.ts` for the admitted normal `465fc` route:

- One `46754` preparation and a genuine `46bd0(mode0)` traversal.
- When the shared movement byte `661` is zero, ordered count clears, real
  `46ef4` damping, and a genuine `46bd0(mode1)` traversal with nonpositive
  reached scan counts. Suppression bit `0x20000000` and authenticated low
  nibble selector1 are the two admitted damping paths.
- Shared visibility/globalD2 gate and the sequential early returns of `47904`.
- Final mode reload and a real `47a2c` copy into the linked actor's existing
  world-matrix slots. The source count is reloaded and sign-extended for each
  iteration; target mode/count and unrelated target state are not consulted.

See `normal-actor-matrix-evidence-2026-11-13.md` for the fixed archived spans,
dispatch addresses, constant, source load order and explicit limits. Joint1's
X correction now reads actual `RomActor.steerYaw` at `18da` after the first
pose concatenation, rather than retaining a second owner for the same short.

The DAT/setup/playback integration exercises both actual source and target
matrix owners, retained poses/matrices between explicit calls, and movement's
consumption of the retained source output. Its supplied metadata and actor
state are synthetic admitted inputs, not proof that a retail Double Ninja
spawn reaches only these branches. Neither caller is installed in Battle.

Normal terrain handlers other than damping, positive IK scan counts, active
`47904`, nonzero short rotations and nonidentity pose quaternions still refuse.
The input provenance, source lifecycle/contact closure, exclusive Battle
ownership and presentation requirements above still apply. A real admitted
normal call does not authorize treating the unsupported remainder as no-ops,
substituting this caller for alternate `46698`, or changing source refresh
cadence.

## Subsequent bounded terrain dispatch paths

The normal caller now also admits the actual `47344` selector3 leaf and
`47164` selector2 exits that never reach a terrain query. Both multiply the
existing `1d60` by the authenticated binary32 damping constant, store it,
then add its reloaded value to existing `world.adjusted1d54.y`. They execute
the genuine corrected traversal and linked receiver copy afterward.

Selector2 uses the existing metadata, movement descriptor/clearance, actual
actor position and actual full world-matrix arrays. It preserves the initial
rounded sum and fused threshold construction, exact -1 descriptor sentinel,
signed freshly loaded skip masks, four-entry bound, cached X index and
reloaded Y/Z index. Even an above-threshold joint reads Z. A reached query
refuses before `8003d6e4`, retaining the first pass and dispatcher count clears
but doing no damping, correction-tail, second-pass or receiver-copy effects.
No terrain result, correction entries or positive counts are invented.

The actual synthetic DAT/setup integration checks these routes, skipped and
sentinel reads, wait-time matrix retention and replacement setup consuming the
corrected retained matrix. This expands the explicit normal caller's accepted
source domain. It still does not establish original spawn inputs or install
an exclusive Battle lifecycle. General matrices, reached terrain queries,
positive correction scans, active `47904`, lifecycle/contact closure and
source-matrix presentation remain requirements. See
`terrain-matrix-handlers-evidence-2026-11-13.md` for authenticated source spans.


## Source transform-history ownership preparation

A full source lifecycle needs the actual `5685c` snapshot, not only the live
bridge's existing position-history subset. The bounded explicit snapshot now
uses the same world owner and RomActor as setup, movement and matrices. Its
only new storage is the missing prior rotation, prior prerotation, prior
step height and prior aim origin. Current/old/older positions, current shorts,
height, aim and visibility association remain in their existing records.
The source visibility association at `+cc` is distinct from the matrix-copy
link at `+4a4`.

This primitive is composed explicitly in the real-owner synthetic DAT/setup
integration before and after genuine wait, movement and matrix operations.
It is not installed in Battle. `beginFrame` currently consumes `runtime.pos`
before `syncIn`; the RomActor position may still be stale there. Replacing
those writes by an isolated snapshot call without real owner construction
would regress the live route, and running both would duplicate history.
The eventual exclusive route must replace the overlapping host writes for
admitted actors and keep one Battle-owned frame guard outside the primitive.

The transform-history assessment identified actual savedGroundPos.y (`+30`), current
stepHeight (`+6d0`) and the new prior-height owner (`+6d4`) as terrain inputs. A useful bounded
`3d6e4` domain has zero supporting-actor contact, genuine empty ceiling cells,
and nonempty floor-cell triangle evaluation, followed by a no-correction
return into `47164`. Existing `floorSurfaceYAt` is not a substitute: it uses
filtered/tolerant geometry, merged layers and fallback searches. The source
view must retain the real layer headers and sentinel-terminated cell lists;
`hit-bin.ts` currently discards sentinels and silently ignores invalid pointers.
At that checkpoint, the query, grid lookup, bounds helper and numeric constants
still needed their own narrow instruction authentication before implementation.
The following slice supplies that evidence and implementation. No permission
or access denial was encountered during this local source assessment.

## Genuine bounded terrain query and caller continuation

The next source boundary is now executable explicitly. `actor-terrain-query.ts`
implements the authenticated zero-support-contact `8003d6e4` path, including
strict X/Z bounds, actual `+24`, `+20`, then `+1c` layer lookups and a real floor
triangle scan. `terrain-query-evidence-2026-11-13.md` records the fixed source
spans, original 500-unit divisor, signed conversions and separately rounded
arithmetic. Empty floor fallback and the out-of-bounds point-Y return are also
admitted; the integration evidence uses a genuinely nonempty floor cell.

The new formats `sourceTerrainGrid` namespace constructs a strict owned view
from explicit unrelocated STIH bytes plus the existing parsed record owners.
It resolves file+8-relative pointers and stops at the first actual -1 sentinel,
without the host parser's filtered cells or floor fallback. Parsed headers,
triangles, vertices and normals retain identity. The view does not emulate
in-place loader writes: shared list addresses are represented as aliases, not
as evidence that the original loader can safely relocate a nonempty list twice.
Input bytes and decoded geometry are not mutated or uploaded. Construction
validates the supplied storage; query helpers subsequently validate only the
reached fields, preserving lazy nonempty-ceiling and skipped-triangle refusals.

The admitted query domain is finite exact binary32, RN=00 and NI=0, explicit
stable own-data owners, zero supporting-contact byte, genuinely empty selected
ceiling lists, and reached floor normals `(±0,1,±0)`. Bounds and cell indexing
are source computations, not host collision searches. Current/history top
heights adjust only query-local clearance. Products and sums round separately;
the local division helper uses exact rational nearest-even rounding. The three
floor accumulators, initial selection flag and final sentinel reloads remain
source ordered. Other normals, nonempty ceilings and contact matrix paths
refuse when reached; no fabricated result resumes the caller.

Normal handler `47164` receives this runtime explicitly. After a real query it
adds the returned height to the caller's original saved clearance and reloads
caller-local Y. Strict greater-than alone resumes the existing scan, damping,
corrected traversal and linked copy. Equality/lower refuses before stack-Y
replacement or the first persistent correction-entry store. Synthetic DAT
integration reaches a real flat floor, produces corrected world/receiver Y18,
retains those matrices during an actual wait and consumes them in replacement
setup. A positive prior-top displacement demonstrates that adjusted query
clearance does not leak into the caller comparison.

This is still offline explicit composition, not live source gameplay. No
Battle branch, frame guard, contact producer, spawn input or renderer owner was
replaced. Positive correction entries/IK scans, nonempty ceilings, broader
matrix domains, active `47904`, lifecycle/contact closure and matrix-driven
presentation remain required before a complete exclusive production route.

## Genuine secondary terrain correction

Correction-taking `47164` results can now populate explicitly supplied owned
primary `1a14` and secondary `1a94` records. The controller and corrected world
traversal share the same exact arrays/rows and count fields. Missing storage
still refuses before the first omitted effect. Source XYZ and descriptor bytes
are stored in order, primary and secondary cursors advance independently, count
increments retain byte wrap, and secondary padding is never overwritten. The
movement descriptor owner now accepts the explicitly supplied extra bytes
beside its existing joint fields; no duplicate joint identity or implicit zero
fields are introduced.

The corrected traversal snapshots each signed count per enabled joint, scans
primary records first using `current == sign8(joint) - 2`, and only on a miss
scans the secondary list. A first primary match still refuses before `47368`.
A genuine secondary match calls the actual bounded `4784c` path. It transforms
the raw bank-zero pose by the incoming parent, stores target XYZ, freshly reads
movement `670`, invokes the real `3de80` normal query, then reloads entry axes
and reconstructs orientation. It does not use the special joint1 adjusted
translation and does not consume the primary stored ground height.

The new normal query uses the actual three source grid owners and history,
writes its caller-local default normal before the bounds test, updates that
output only for an eligible best floor, and retains source refusal prefixes.
It has no height query's min/max fallback and no persistent normal shadow.
A real outside-bounds return writes the default and returns zero; `4784c`
ignores that status, as the source does. Nonzero support, nonempty ceiling and
nonflat reached floor branches remain excluded.

`terrain-orientation-evidence-2026-11-13.md` authenticates the nine new text
spans, two constrained selector windows and four constants in both archived
snapshots. Positive axes `(2,1)` select constructor `46158`. Matrix/vector
operations preserve actual paired loads, FMA, stores, magnitude/refinement,
cross products, normalization and final Scale/Concat, including signed zeros.
The bounded orientation admits distinct signed-axis columns with nonzero
magnitudes `{0.5,1,2,4,8}`, a flat normal and a successful first basis build.
Other selectors, fallbacks and estimator inputs refuse rather than using sqrt
or an identity approximation.

The reciprocal-square-root specialization is independently derived from the
pinned canonical Dolphin estimate model, not a new hardware capture. For this
finite domain the original normalized component is `1 - 2^-24`, and restored
basis magnitude is `m * (1 - 2^-23)`. The implementation executes the refinement
and source operations; it does not directly substitute mathematical unit
vectors. The note separates original archived instructions from that numerical
model, and no GPL estimator implementation or lookup table was imported.

The real-owner composite uses a nonzero floor result and creates both lists.
Descriptor joint1 misses the primary `-2` predicate and genuinely matches the
secondary list. The former first-pass joint `(140,10,468)` becomes raw-pose
translation `(134,47,448)` with the source's nonidentity scale rounding. The
linked clone receives those exact matrices. An actual wait retains them, then
replacement setup/movement consumes Y47 and produces height `9.449999809265137`
without a second matrix pass; the next explicit history snapshot captures it.
Repeated refresh, equality/lower floor results, per-entry masks, cursor/count
behavior, primary-match refusal and partial stores are covered separately.

This closes a real secondary normal-alignment path, not two-bone height
placement. Primary `47368`, broader orientation/terrain/matrix domains, active
`47904`, real spawn hydration, full contact/lifecycle ownership and presentation
remain incomplete. No partial source route or fallback is installed in Battle.

Verification for this extension: focused real-owner integration, enhanced strict
TypeScript and the full contributor/production-build gate pass. Matching-tool
discovery passes all 263 tests; the existing oracle harness passes 83 with its
one expected absent-private-MEM1 skip. The four new private mutation suites
reject 128 meaningful variants with no runtime-test survivors or build/anchor
failures. The independent BigInt reference passes 4,096 actual contexts and
8,192 refreshes, including genuine queries, linked matrix copies and retained
setup/movement consumers. Numerical claims remain restricted to the documented
Dolphin-model-backed finite axis domain, not new hardware or replay evidence.


## Genuine folded primary placement

A first primary `46914` match now executes the actual bounded `47368` closure
rather than refusing unconditionally. The shared record supplies its target and
raw descriptor axes. The current raw pose and adjacent raw pose remain distinct
from the special joint1 adjusted translation and from topology-selected nodes.
The source's interleaved raw-X/joint/Y/Z loads and the nine retained matrix
translation loads occur before either length recovery or persistent write.

The selected domain measures first and second retained bone lengths exactly
2 and 0.5, and reaches target displacement `(±0,1,±0)` with orientation axes
`(2,1)`. Three actual binary64 estimator refinements recover those lengths;
the existing SDK magnitude/refinement returns a slightly sub-unit target
length. Exact binary32 cosine calculations then clamp to +1 and -1. Signed-zero
sines, the authenticated signed bend lookup for X/Y/Z, both actual RotTrig
matrices and both original Concat operation trees execute. The first Concat
writes the current matrix, and the second writes its physical adjacent matrix
using the adjacent raw pose captured at entry. These are not identity or exact
endpoint shortcuts. Other measured lengths or positive sine-square paths are
still refused, with completed source effects retained.

The special traversal is part of the closure. After primary placement it
visits the current byte1 branch with the incoming parent, reloads current byte0,
skips that node's ordinary mask/count/compose work, visits its byte1 branch with
the current node as parent, then reloads its byte0 and continues using the
skipped node as parent. A negative skipped-node index is an unsupported
address, not successful traversal termination. First-match priority, repeated
and disabled nodes, live topology reloads and failures after completed work
have direct tests.

The actual composite is reachable through the existing floor query and caller:
raw joint1 Y10 plus source offset Y-2 produces first-pass base Y8. Adjacent raw
translations Y2 and Y0.5 produce retained middle Y10 and distal Y10.5. A real
flat floor Y10 plus clearance1 creates target Y11. Metadata0x15 admits that
query and legitimately suppresses its secondary record. Primary placement
transforms raw base Y10, so its target vector is +Y1. With bend Z the base,
middle and distal finish at Y10, Y12 and Y11.5. The requested Y11 is inside the
chain's minimum reach, and the result intentionally does not claim to attain it.
All four matrices reach the linked clone. A later real wait and replacement
setup retain the matrices and the movement consumer produces height 3.5 from
base Y10. Repeated explicit refresh does not accumulate normalization error.

`primary-terrain-placement-evidence-2026-11-13.md` and its fixed reader cover
primary47368, Subtract, SquareDistance, six typed constants and the narrow
signed bend table, reusing existing orientation and RotTrig evidence. Numerical
seed facts remain the pinned canonical Dolphin finite model, not a new hardware
capture. The power-of-two double products prove the fused refinement equivalence
inside this domain; no general host sqrt or trigonometric approximation was added.

This closes genuine minimum-reach primary placement, not general bending or
exclusive production activation. Battle still lacks real source spawn hydration
and must select an exclusive owner before host history, status, input, death and
reaction updates. A switch at bridge.tick is too late, and fallback after source
writes is unsafe. Broader primary/orientation domains, active47904, complete
contact/lifecycle and source-matrix presentation remain unfinished.


Independent validation of the folded path passes 2,048 real integration
contexts with 4,096 refreshes, 2,560 placements, 3,072 genuine height queries
and 512 retained setup consumers. A separate eight-node reference passes
1,024 contexts, including 512 nonroot cases, 24 topology shapes, 16 masks and
2,048 corrected passes/linked copies. Both references use independent BigInt
nearest-even arithmetic; all their final input manifests match. The separate
double-refinement proof checks each stage for all five canonical power-of-two
seeds without broadening the actual placement lengths beyond 2/0.5.

Three new private mutation suites reject all 77 meaningful variants: 41 math,
24 traversal and 12 real composite controls. Seven initial survivors exposed
missing regression witnesses, including nonroot parents and observable signed
zeros; those tests were added without changing the runtime. Six other new
candidates are provably equivalent inside the deliberately clamped domain and
are explicitly excluded rather than counted as kills. Original outcomes and
proofs remain preserved. No surviving meaningful control or build/anchor failure
remains. These checks do not establish general bending or original replay parity.

Final focused real-owner tests, enhanced strict TypeScript and the full
contributor/production-build gate pass. Matching-tool discovery passes all
286 tests, including both authenticated local snapshots for the new reader.
The existing oracle harness passes 83 tests with its one expected absent
private-MEM1 skip. This is validation of the stated source boundaries, not a
new original-game capture or activation of the clone in production.

## Equal-length positive bending extension

The additional retained pair `(1, 1)` now takes genuine positive sine branches
in47368 while preserving the previous `(2, 0.5)` folded path. Actual source
cosines, two finite model-backed estimate seeds, three binary64 refinements,
fused corrections, sine signs and both rotations/concatenations execute.
`primary-positive-bending-evidence-2026-11-13.md` records provenance, all
intermediate words and the deliberately bounded admission domain.

The real first pass producesY8/9/10, queries floor10 and creates targetY11.
The raw base isY10. Positive Z bend places the middle at
`(100.86602783203125, 10.5, 100)`; special traversal places the distal at
`(100, 11, 100)`. Both X/Z signs reach that rounded target in this fixture;
Y bends produceY12. This is source geometry, not an endpoint snap. All actual
matrices reach the linked clone and later wait/setup/movement consumers.
Repeated refresh, late bend refusal and unproved mixed length pairs preserve
existing ownership and partial-write behavior.

Exact intermediate verification matters: an unfused host correction differs
by one binary64 bit at the first sine's second iteration, despite yielding
the same final binary32 sine. Direct fusion/stage checks complement actual
matrix and caller integration tests. This extends gameplay mathematics, not
production activation: complete source spawn/lifecycle/contact ownership and
source-matrix presentation still need integration before an exclusive route
can safely replace Battle's host sweep.

## Source attribute refresh before movement

The explicit `80055dcc` boundary now joins the existing source actor, mapping,
world and movement owners. This helper is reached during real spawn `541ac`
and before status/state dispatch in ordinary lifecycle `55568`; it is not a
substitute for either complete caller. The fixed 280-byte archived span and
its load/store order are documented in
`actor-attribute-refresh-evidence-2026-11-13.md`.

The helper stores control bit6 at actor+87, retains the selected mapping
descriptor and model scale, then computes the five separate source products
in their original order. Existing movement fields66c/670 and the actor's
hoverOffset668 remain the actual destinations. The three parameter4ac limit
reads reload that pointer separately and update the actor's existing speed
limits. Fifteen sequential float copies then update814..84c; sources868/874/880
are the existing actionSpeedRows rather than a second cached row table. Only
previously absent fields receive explicit new owned storage.

The final call is the real existing `4d08c` movement helper. It reads retained
world matrices and the newly written dimensions, with all ordinary movement
gates occurring after the attribute stores. Attribute refresh does not rebuild
matrices, advance animation, snapshot history or choose a frame cadence.
Reached validation preserves completed effects, including failures inside the
movement callee. Descriptor products use finite binary32 operands and one
nearest-even binary32 rounding; arbitrary NaN payloads and live machine-state
parity remain outside the stated host domain.

This removes manually supplied dimension values from the explicit composite's
refresh operation, but the descriptor scalars, parameter identity/limits and
prepared row values are still explicitly supplied synthetic inputs. Retail
spawn hydration, status/input/contact closure, exclusive ownership before
Battle's host updates and source-matrix presentation remain incomplete.
Production is not enabled, and no fallback after partial source writes is added.

## Source status timers on the actual owner graph

The next explicit ordinary-lifecycle prefix is now actual `55dcc -> 5568c`,
including the latter's unconditional `6dcc0` ammo operation. This is a bounded
full-return domain of the helper, not a completed `55568`, `54070`, spawn or
Battle route. Its fixed archived instructions and numeric assumptions are
recorded in `actor-status-timers-evidence-2026-11-13.md`. Inputs remain supplied
synthetic records, with finite exact binary32 arithmetic under RN00/NI0.

The binding preserves the existing owners instead of introducing status
snapshots:

- Control5e0, timer694, housekeeping73f, rate768, FB5da and slope timer698 use
  the same actual RomActor already shared by world and movement. World6b8 and
  mode4a1 remain the existing world binding; class661 remains movement's byte.
- The source clock is the existing mapping timestep1dc8. Source marker709 is
  the existing stream-start binding, cleared by the real mask2 start. Legacy
  RomActor.dt and contactFlags remain distinct and are deliberately given
  different values in the witness. They are not silently synchronized.
- Attribute byte87 and parameter4ac are the existing records. Signed shorts
  04/08 extend that same parameter identity alongside its74/78/7c limits.
  Regeneration and the later7d4 cap reload the actual pointer when reached.
- A stable borrowed host-field owner holds the existing BorgRuntime gauge,
  combo, HP/drain and invincTimer fields. It is supplied explicitly rather than
  obtained by production spawn, copied into a new status state or routed
  through host stepStatus/stepAmmoRefill. Host invincTimer is the selected720
  owner; a present legacy RomActor.invulnTimer is an explicit conflict, checked
  at bind and again when source720 is reached.
- Three distinct actual WeaponCells hold source current/max/mode/parameter/debt.
  Their separate slot records add only the missing776 mirrors. The witness's
  browser weaponCells1/2 intentionally alias source cell2; source cell1 is
  independently supplied. Binding that browser alias list as three source
  cells is rejected. Legacy HUD ammo and cached sourceAmmoRefillRate are not
  source owners or implicit synchronization targets.

The composite executes active timer decrements/clamps, world6b8 countdown,
all six stream counters, host balance refill, combo and invulnerability expiry,
parameter-cap writes, three real ammo visits with current/mirror refill, and
FB accumulation. A real replacement start then clears709, which the next
status call observes; changing mapping timestep also changes the next694
subtraction while legacy dt stays different. Actual wait advances pose without
hidden status work. Only a later explicit465fc updates matrices and the linked
clone, and later55dcc invokes real4d08c on that retained result. History advances
only at its explicit callsite. All prior test blocks remain ahead of this new
composite in the aggregate.

The admitted full-return path has zero poison6ba, eight null child pointers,
and source predicates that avoid f0104, 3d3e8, 3d444 and 5c290. These predicates
are not global skip flags: active effects elsewhere still execute. Real mode0
ammo expiry is supported; mode1 expiry preserves negative remaining debt, but
its reached positive-debt division remains refused after the timer store.
Nonzero poison and nonnull children remain bounded refusals, not no-ops.
Tests also reach all four unsupported calls, late missing4ac, readonly ammo
mirror and a newly introduced720 conflict, checking their completed stores and
untouched suffixes rather than treating the error alone as success.

The unconditional next helper `59068` is still missing. Full55568 also needs
its dispatch marker, prehook/UB/saved-FB/posthook sequence,55ee4, frozen-position
restoration and5b880. Full54070 still needs its real lifecycle/contact envelope,
5a580, explicit465fc and cleanup. Before any live route, conflicting legacy
clock/marker/invulnerability owners, host status/input/death writes, real spawn
provenance and source-matrix presentation must be resolved at the ownership
boundary. No successful dummy callee, host fallback after partial writes,
production activation or original-input replay is claimed.

## Real gauge resets and an explicit scale helper

The next additive extension supplies actual `3d3e8` and `3d444` callees to
`5568c`, then exercises `5bab8` at its own explicit helper boundary. It does
not turn the preceding status composition into a continuous `59068` prefix:
that caller's two `760/764` divisions by model scale occur before `5bab8` and
remain absent. The archived instruction/constant evidence and admitted numeric
bounds are recorded in `actor-gauge-scale-evidence-2026-11-13.md`.

Status now has an optional, once-bound real gauge-reset owner. The earlier
unbound-reset fixture and all its historical assertions remain unchanged,
including reached `688/7d8` refusal prefixes. A separate additive fixture
extends that same actual DAT/setup/world/attribute/status graph and binds the
real gauge implementation rather than successful callback substitutes. Both
positive timers expire, store zero and invoke their actual reset; combo,
invulnerability, ammo and the remaining status suffix then really execute.
A later invalid secondary base preserves the earlier down-gauge reset and
both timer stores while refusing the unreached suffix.

Ownership remains singular:

- Actual `BorgRuntime.downGaugeBase/downGauge` supply `6c4/6c6`. Their existing
  raw unsigned-short representation is sign-extended on the source load and
  stored as low16 bits. Only absent signed `7d6/7dc` receive explicit storage.
- Actual `RomActor.modelScale` supplies `B4`; the existing world binding's
  `scale58` vector supplies `58/5c/60`. Actual `RomActor.collisionScale` must
  exist for the `C0` store. The host's fallback to model scale is not used.
  Only missing target `B8`, gate byte `7c9` and `C4` receive explicit fields.
- `74a/74e/750` remain the same `BorgRuntime.paramTier` object, not a copied
  timer/tier record. The real positive signed-short timer decrements by one.
  Reached expiry preserves that store and refuses the unresolved `6817c`
  global gate/table refresh before clearing `750/74e` or touching scale.
  The existing host clamp helper cannot stand in for that source call.

The reset operations follow the authenticated three-stage arithmetic:
round `B4-1`, round `0.5*delta`, then round `signedBase*factor`. Truncation to
signed32, signed16 conversion and final low16 wrapping are distinct. The C
expression's apparent `base*0.5` grouping is not the source operation order.
Finite exact-f32 RN00/NI0 inputs and representable signed32 conversion bound
execution; this is not arbitrary FPSCR, NaN-payload or original-run parity.

Actual scale interpolation uses archived `3d4ccccd` (`0.05000000074505806`).
Both directions make a nontrivial step, overshoot clamps to the target and
invokes real `3d3e8`, then five independent source copies write world X/Y/Z,
collision scale and `C4` in that order. Equal-target and byte gates do not
perform these copies. Reached readonly/missing destinations preserve the
completed timer, scale, reset and copy prefix, including a missing collision
owner after all three world-vector stores.

The composite moves `B4` from2 through2.049999952316284 to2.0625 while retaining
world matrices and animation state. A live descriptor makes the next actual
`55dcc` write half-height132; genuine `4d08c` observes it on retained worldY95.
A separate real status call clears its yaw countdown, and genuine wait advances
pose without ticking scale. Only explicit `465fc` then observes the changed
world-scale vector, writes worldY82.3125 and copies actual matrices to the linked
actor. It does not copy that actor's model-scale fields. A later actual
`55dcc/4d08c` yields stepHeight7.21875; real replacement setup consumes the
retained result, and only explicit history updates previous height.

All prior composite blocks and status invocations retain their original
order. The new composite runs after them, and focused gauge/scale tests follow
the prior focused status tests before the lifecycle aggregate's final PASS.
Inputs remain supplied synthetic records. Full `59068`, `55568`, `54070`,
source spawn/contact ownership, exclusive host routing and source-matrix
presentation remain incomplete. No production route, dummy success callee,
implicit ordinary tick or fallback after partial source writes is added.

## Bounded actual59068 prefix on the same owners

Fixed archived instruction coverage and explicit omitted support-body bounds are
recorded in [actor tick-prefix evidence](actor-tick-prefix-evidence-2026-11-13.md).

The preceding status/gauge sections record their incremental stages. The new
additive composition now admits actual `59068` from its two distance divisions
through real `5bab8` and the zero-contact return of actual `67a70`. It always
refuses the next unreconstructed call, `59e58`; this is not a successful tick,
complete `59068/55568/54070`, or a production activation.

`actor-tick-prefix.ts` binds the same actual actor, genuine gauge runtime and
borrowed Borg/paramTier as the DAT/setup/world/attribute/status fixture. It
requires an explicit `externally-decoded-pre59068-raw` input record. The existing
actual `RomActor.targetDistance760` is the full three-dimensional source distance;
new optional actual `horizontalDistance764` is its distinct XZ distance. Both
are supplied decoded raw values, never cached speed multipliers, shadow adapter
fields or implicit bridge data. Only absent byte598 receives a separate binding.
The tag declares an input boundary, not authenticated provenance: this does not
implement or observe the source target lookup, square root, `6ae60/6bda8`, capture
or no-target constant. A caller relabeling already-normalized values as raw is
outside the contract and is not detected by the tag.

The archived order is retained: load760 and currentB4, divide/store760, then
load764 and a freshB4, divide/store764; call real5bab8; enter actual67a70, clear
control5e0 bit `0x100000`, clear598, then inspect actual supportContact1db. Zero
contact genuinely returns. Nonzero contact refuses the reached missing1e4
supporting-actor owner after both clears, rather than substituting the existing
separate collision adapter or inventing a pointer. The next unconditional59e58
remains refused even when every earlier effect completes. Division is bounded
to finite exact binary32 inputs and RN00/NI0 with exact rational nearest-even
rounding, retained signed zeros/subnormals, and refusal of zero divisors or
rounded overflow. These are explicit host bounds, not new hardware captures.

One synchronous guarded operation consumes a monotonically increasing per-actor
input epoch before the first raw-ingestion store, then performs ordered raw
stores and the source prefix. Raw stores are host boundary effects, not claimed
source instructions. A failed attempt retains its consumed epoch and every
completed store. Repeating that epoch cannot overwrite raw values, divide again
or decrement750 twice. This is an input-attempt token, not a whole-frame claim
that760/764 remain normalized: source command6a104 can recapture raw values later
in the frame. A new admitted input epoch must supply fresh raw fields explicitly.
There is no public unclaim or host fallback after partial writes.

Claims reject legacy `speedScalar760/764`, `kfmSpeedScalar760/764` and
`curTargetDist` ownership conflicts at bind and entry. A minimal guard at the
start of legacy `bridge.syncIn` prevents its writes to a claimed actor; it does
not route a source tick or change behavior for unclaimed actors. Other overlapping
host/producer writes and the full lifecycle still need exclusive ownership
before a live route could be enabled.

The additive fixture preserves every earlier fixture assertion and execution
order. It normalizes distinct raw64/20 by oldB4=2 to32/10 before actual scale
interpolation, reaches a second explicitly supplied raw66/22 refresh, and proves
that both divisions precede clamp/reset49 atB4=2.0625. Actual paramTier750,
world58/5c/60, collisionC0 andC4 remain their existing owners. Complete unrelated
owner snapshots surround prefix calls. Reached6817c, missingC0, readonly control
or598, missing598 and nonzero1db retain their exact completed prefixes. Repeated
epochs after both early and late failures make no further distance/timer effects.

Only later explicit real55dcc/4d08c consumes the new model scale; actual status
and wait retain separate cadence. Explicit465fc then writes worldY82.3125 and
copies linked matrices without copying the linked actor's model scale. Later
real movement reaches7.21875, genuine replacement setup consumes retained output,
and explicit history advances previous height. None of that is a fabricated
successful suffix of59068. The focused standalone test is appended after the
existing focused gauge/status registrations, before lifecycle PASS.

The next implementation boundary is real59e58 plus the remaining reached
movement/input/dispatch calls and their actual owners. Full status tier expiry
still needs6817c global/table behavior, and nonzero67a70 contact needs1e4 and its
continuation. Retail raw-distance production, spawn/input/contact closure,
exclusive host lifecycle and source-matrix presentation remain unfinished.

The existing `NeoGredMeleeState.targetDistance760` accessor is also constructed
over the same actual actor before the prefix and reads its normalized760
after each input epoch, with no copied distance property or family dispatch.
This is a concrete existing consumer witness, not activation of that family.
