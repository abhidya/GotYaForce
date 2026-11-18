# Ninja animation joint-selection evidence

Scope: GG4E, Normal Ninja (`pl0000`) and Sasuke (`pl000a`). This records
numeric facts from the user-supplied game image, not extracted game assets.

The original constructor at `8006f4f8` stores descriptor `802d3dc8` at
actor `+4b0`; for actor ID `0x000a` it stores `802d3ee0` instead. The first
`0xb0` bytes at both addresses have SHA-256
`57f57268eb4b7761258c288d68ef168657dcdc84599c8d5c47132275da0e253b`.
The constructor assignment was checked from the DOL instructions at
`8006f5c0..8006f608`; it is not a guess based on an adjacent family.

Both descriptors have signed boundary bytes `+0c..0e` of `11,20,20`.
Their first 20 signed joint-map bytes at `+8c` are:

```
2 3 4 5 6 7 8 9 10 11 12 0 1 13 14 15 16 17 18 19
```

Original setup copies the boundary bytes to actor `+1d91..1d93`.
`8004b8f4` uses those values for the first three channel boundaries; the
fourth range ends at actor `+1d90`. `8005380c` sets that count from archive
JOBJ traversal. On 2026-11-18, the original AFS members 485 (Normal Ninja) and 495
(Sasuke) were read from the user-supplied GG4E disc. Member 5 of each PZZ
was decompressed locally and parsed with the repository's HSDRaw library;
each `JOBJDescs` model index 0 has 20 nodes in its `RootJoint.TreeList`.
The temporary archive files were deleted after inspection. This independently
agrees with the 20 named JOBJ nodes in each checked-in GLB. This archive parse alone is not a live actor measurement. The existing
`research/format-specs/mot-animation-format.md` additionally notes 23
AnimJoint nodes in Ninja's b00 animation tree.

`8005380c` resets its counter between two `80067e18` walks and stores the
second count. `800419ec` creates both `+708` and `+788` banks by calling
`80007030` with the same model index; `80007030` loads a JOBJ root from that
model descriptor. In a separate Dolphin JIT64 session of GG4E, a native roster reload into a
Ninja versus Sasuke battle produced four active actors (two per ID). Each
had `+1d90..1d93` equal to `[20,11,20,20]`, and the expected descriptor
address for its ID. Thus the fourth selected range is empty for those
observed actors. This is emulator evidence, not physical-console validation.

The play instruction for Ninja ground/air X uses part mask `0xf` according to
`ninja-source-x-2026-11-12.md`; this requests all four channels, not an
unconditional assertion that the displayed GLB skeleton is an equivalent
source pose bank. Descriptor bytes `+42,+43` are `7,11`; their original
visibility stores occur after slerp. No physical-console validation or live
pose/geometry parity is implied by these static observations.

## Bounded runtime visibility observation

On 2026-11-18, an isolated Dolphin JIT64 session reloaded a Ninja/Sasuke
roster from the user-supplied GG4E image. A synthetic X-button press cycle ran
for 160 pad frames while the source `8004a8cc` entry was monitored. At 76
sampled calls for the first Normal Ninja actor, the four bytes `+1d74..1d77`
were `[0,1,0,1]`, and `+1d94..1d95` were `[0,1]`. They did not change at
those sampled entries. The experiment did not establish that the intended X
move was admitted, and it did not capture Sasuke's blend calls. It therefore
cannot establish general visibility behavior, an exhaustive transition trace,
or rendered geometry parity. The separately launched instance was stopped;
an unrelated pre-existing Dolphin process was left running.

## What the two output bytes select

The output bytes should not be treated as simple per-bone booleans. In the
original decompilation, `8004fdf0` reads `actor+1d94`, checks it against a
signed bound at the model record's `+c0f`, adds it to the draw descriptor's
first byte, and selects an entry from the model record's `+708` pointer table.
`8004fe60` performs the corresponding operation for `actor+1d95`, using the
bound at `+c13`. Both pass the selected object to `zz_00076d0_`, then call
`zz_00097b4_`. See `research/decomp/ghidra-export/chunk_0006.c` at those
addresses. The exact mapping from those original archive/model entries to the
exported GLB meshes remains unverified, so setting `Object3D.visible` from
these bytes would not be a supported port of this behavior.

## Ninja draw descriptor candidates

Read-only inspection of the user-supplied GG4E DOL on 2026-11-18 resolves
`PTR_PTR_802d2564[0]` to `802d14b4`. Variant 0 points to `802d1334` and
variant 10 to `802d146c`. The Normal descriptor's first drawable row is
`[1,7,0,0]`, followed by candidates with first bytes 2 through 5 and type
byte `ff`; its second drawable row is `[6,11,1,0]`, followed by candidates
7 through 9 with type `ff`. Sasuke has the same rows and one additional
candidate with first byte 10. Each list ends in `ff`.

Together with the `8004fcfc` dispatch and `8004fdf0/8004fe60` consumers,
this identifies descriptor bases 1 and 6 and the source joint-mask bits 7
and 11. It does not by itself establish which exported mesh corresponds to
any archive pointer or whether each selector value is valid for each variant.
The currently checked-in character model directories contain only
`model_00.glb`; the selected additional source objects have not yet been
traced to equivalent rendered geometry. Do not infer a Boolean visibility map
or claim complete Ninja appearance from these descriptor rows alone.

### Original archive model inventory

On 2026-11-18, original PZZ member 5 from AFS entries 485 and 495 was
decompressed locally and read with HSDRaw. Normal Ninja's model archive has
16 non-null JOBJ roots (indices 0–15); Sasuke's has 19 (indices 0–18). In
both, root 0 has 20 joints with seven joints carrying display objects. Each
additional root has one joint carrying a display object. The draw-descriptor
candidate indices above therefore correspond to populated extra model roots,
not additional joints inside model 0. Temporary extracted archives were
removed after inspection. This identifies a concrete source-to-export gap,
but it does not yet map meshes, prove animation selector ranges, or validate
rendered appearance against the original game.

### Export and attachment experiment

Using temporary extracts of the same original member-5 archives, the existing
HSDRawViewer exporter successfully produced textured Collada for roots 1 and 7
of each character, and the existing runtime converter successfully converted
all four to validated GLBs. The first experiment remained local. Subsequently, the four validated GLBs
were added to the draft port branch and wired into the limited Ninja X/recovery
rendering path and verified group-0 idle; they are not a visual parity claim. Exporting each root into a separate
directory avoids collisions between the exporter's texture filenames.

The two draw consumers pass `actor+a24` and `actor+ae4` respectively to
`800076d0`; these offsets equal `actor+8d4 + 7*0x30` and
`actor+8d4 + 11*0x30`. `800076d0` copies its matrix argument into the
selected object's JOBJ matrix. The existing exporter bakes parent transforms
into vertex positions (see `tools/HSDLib/HSDRawViewer/IO/ModelExporter.cs`,
position transform near line 576), so directly parenting its exported scene
under a joint without removing the export bind transform can misplace geometry.
The renderer applies the inverse exported bind transform when attaching each
part. The live adapter is limited to the observed target models, retains a
known target through verified group-0 idle, and hides it for other unmodeled actions; source
draw masks, source matrix equivalence, and visual parity remain unverified.

### X and recovery target selectors

An isolated GG4E Dolphin JIT64 battle with Normal Ninja and Sasuke was loaded
on 2026-11-18. All four active actors pointed to family animation metadata
bank `802bd780`, had default group 0, and had descriptor defaults
`+be,+bf = [0,1]`. Resolving the original signed-short tables gave:

| Group / slot | Descriptor | Bytes 9, 10 |
|---|---|---|
| 4 / 0 | `802bdd60` | `ff,ff` |
| 4 / 1 | `802bdd74` | `ff,ff` |
| 0 / 0 | `802bd8c4` | `ff,ff` |
| 0 / 14 | `802bd950` | `ff,ff` |

The original setup treats each `ff` as a request for its descriptor default,
so those four target animations select values `[0,1]`: draw-descriptor bases
1 and 6 therefore resolve to model indices 1 and 7, subject to the original
range checks and draw masks. This observes descriptor inputs, not the previous
pose's selectors; a transition may continue drawing the previous selector
while its saved-pose weight exceeds 0.5. Do not replace unknown previous
selectors with these target values. The dedicated emulator was stopped after
the read; the unrelated existing Dolphin instance was not touched.

### Group-0 metadata coverage

A separate read-only DOL table walk resolved group 0 slots 0 through 25
through the signed-short metadata tables rooted at `802bd780`. Every one
has selector bytes 9 and 10 equal to `ff,ff`; each therefore requests the
verified actor-descriptor defaults `[0,1]` when the observed default group is
0. This establishes metadata target selections for those descriptor slots,
not that every host-selected animation, source draw mask, or transition has
been proven equivalent. The group-0 descriptors can alias each other.
