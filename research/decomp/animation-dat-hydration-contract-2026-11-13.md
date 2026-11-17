# Bounded animation DAT hydration contract

Source audit: 2026-11-13, starting at `8796661e`. This note distinguishes the
on-disc format and observed retail consumers from the narrower offline importer.
Only checked-in source/specifications were read. No original DAT/MOT/DOL,
capture, external source or production asset was acquired or inspected.

## Bare DAT layout and relocation

`research/decomp/ghidra-export/chunk_0072.c:3616–3680`
(`HSD_ArchiveParse`, `8025b00c`) copies a 0x20-byte header and derives these regions:

| Header offset | BE u32 field | Derived file offset |
| --- | --- | --- |
| 0x00 | file size | End of the supplied bare DAT |
| 0x04 | data size D | Data starts at 0x20 |
| 0x08 | relocation count R | Relocations at 0x20 + D, R entries of 4 bytes |
| 0x0c | public count P | Publics at 0x20 + D + 4R, P entries of 8 bytes |
| 0x10 | external-reference count E | Externals follow publics, E entries of 8 bytes |
| 0x14–0x1f | other header bytes | Copied, not interpreted by this function |

Strings begin at `0x20 + D + 4R + 8P + 8E`, when that position is below file size.
The actual function sets the data/table pointers only when their respective
size/count is nonzero. It checks header file size against its supplied size;
it does **not** establish general range, alignment, uniqueness or graph checks.
The BE interpretation is corroborated by
`research/format-specs/arc-hsd-format.md:18–33` and
`research/prototypes/hsd_walker.py:27–53`.

Each relocation entry is the **data-relative position of a pointer word**, not
its target. The retail loop unconditionally adds the data base to that word
(`chunk_0072.c:3665–3669`). Consequently:

- Relocation at slot S, raw value 0: a non-null pointer to data offset 0.
- Relocation at slot S, raw value T: a pointer to data offset T.
- No relocation at a known pointer field, raw value 0: null in this importer.
- No relocation, nonzero raw pointer value: not a supported local pointer. The
  retail parser leaves it untouched; refusing it is a host restriction, not a
  proof that all DAT files prohibit it.

Public-entry offsets are **not** inferred from the relocation set. A public
target 0 names the start of data. Duplicate relocation entries would cause
multiple additions in retail, so rejecting them is preferable to silently
deduplicating and claiming identical behavior. The same applies to relocating
a consumed scalar, record padding, or a packed-stream byte: this importer must
refuse such layouts rather than silently consume their pre-relocation values.

The zero-target caveat is independently recorded in
`arc-hsd-format.md:96` and correctly handled for vertex arrays by
`hsd_walker.py:79–82`. Do not copy that prototype's generic `ptr` shortcut
(`:60–61`) or the zero-sentinel `PP` convention in
`scripts/gen-ptl-cell-map.mjs:95–100`: they cannot distinguish every zero target
from null.

## Public entries, names and selection

Each public entry is `(u32 dataOffset, u32 stringOffset)`. Name lookup by index
returns `strings + stringOffset`, for a nonnegative in-range index
(`chunk_0072.c:3685–3693`). `HSD_ArchiveGetPublicAddress` scans entries in order,
compares NUL-terminated bytes using `strcmp`, returns `data + dataOffset` for
the **first matching name**, and returns null when no name matches
(`:3698–3719`). Duplicate names and shared target offsets are not rejected there.

Hydration must preserve table order and exact name bytes. Selecting public index
N does not change the source's subsequent name lookup into direct index lookup:
if N's name duplicates an earlier name, the earlier target wins. The bounded
importer requires that earlier target address also occur among the explicitly
selected roots, then binds both addresses normally. This preflight rule is
narrower than the source lookup; it never silently substitutes N for the first
matching entry.

The DAT header does not tag root types. The caller must explicitly identify the
roots to interpret as AnimJoint; a suffix or plausible bytes alone is not a type
proof. Prior animation documentation reports `plXXXX_bNN_animjoint` roots and
overlapping/truncated skeleton views
(`research/format-specs/mot-animation-format.md:37–57`). This is historical
evidence, not new verification of assets on this machine.

## Descriptor fields consumed by the real loaders

Offsets are relative to the descriptor's data address; integers/floats are BE
except the packed FObj stream's own encoding. Sizes below are the minimum
extents needed for these fields, not inferred allocator metadata.

| Descriptor | Minimum size | Fields |
| --- | --- | --- |
| AnimJoint | 0x14 | child00 pointer, next04 pointer, aobj08 pointer, robj0c pointer, flags10 u32 |
| AObjDesc | 0x10 | flags00 u32, end04 f32, fobj08 pointer, joint0c pointer/reference |
| FObjDesc | 0x14 | next00 pointer, length04 u32, start08 f32, track0c u8, format0d u8, format0e u8, unused byte0f, data10 pointer |

Primary evidence:

- AnimJoint `aobj08`, `robj0c`, `flags10`: `HSD_JObjAddAnim`,
  `chunk_0071.c:4000–4030`. Child: `HSD_JObjAddAnimAll`, `:4167–4174`;
  next: `:4295–4300`, `:4339–4344`.
- AObjDesc: `HSD_AObjLoadDesc`, `chunk_0070.c:2683–2713`. It allocates,
  combines supported flags, sets rewind/end, loads FObjs, then handles the
  non-null joint reference through the ID table and possible JObj loading.
- FObjDesc: `HSD_FObjLoadDesc`, `chunk_0071.c:1253–1298`, `:1328–1335`.
  It allocates head-to-tail and initializes tail-to-head, preserving next links,
  converting start to the runtime short, then storing track, formats, data and
  length. Byte 0x0f is not read. There is no justification here for requiring
  that byte, or otherwise uninterpreted header bytes, to be zero.

`scripts/gen-ptl-cell-map.mjs:215–223` corroborates the AObj/FObj field layout.
`research/format-specs/hsd-animation-semantics.md:33–37` summarizes both FObj
and FObjDesc; its short FObj offsets must not be mistaken for the linked
FObjDesc offsets above.

Retain the original packed stream bytes. The existing data owner decodes LE
float/16-bit values (`packages/combat/src/rom/fobj-data.ts:120–138`); changing
DAT byte order does not change that nested encoding. The exporter instead
constructs HSDRaw players and samples/bakes per-frame poses
(`scripts/export-borg-animation-hsd.mjs:206–215`, `:272–283`). Those baked poses
are not equivalent input to the descriptor or packed-stream owners.

## Ownership, aliases and graph boundaries

The retail archive parser performs relocation, not graph traversal. Its raw
pointers preserve aliases; it does not clone a descriptor for each public
entry. Intern each admitted descriptor by its original data offset, and preserve
exact repeated stream addresses when mapping to existing owners. FObj lists can
share a suffix across different AObjs; that is not a cycle. A repeated address
within one next-chain is a cycle. The loader's recursion does not detect it
(`chunk_0071.c:1257–1291`), whereas the existing host loader explicitly refuses
revisits (`packages/combat/src/rom/fobj-descriptor.ts:131–145`).

An address reused as incompatible record types, overlapping records, and
distinct-start overlapping streams cannot simply become unrelated owner
objects while claiming faithful RAM aliases. Refuse unsupported overlap or
state the immutable-copy limitation explicitly. Existing `fobj-data.ts:1–5`
already scopes itself to nonaliasing copied storage. Exact shared stream starts
can use one owned byte copy sized to the maximum admitted declared length;
each descriptor still keeps its own original length.

The source `8004adc8` looks up a public name/address and calls **single-joint**
`HSD_JObjAddAnim` with null material/shape descriptors
(`chunk_0006.c:679–694`). It does not traverse child/next there. The initial
importer's selected **leaf-root** domain (null child and next) is intentionally
narrower than both the DAT format and even this single-joint consumer. It must
be advertised as a host refusal boundary, not as a requirement for real
animation archives. Full tree import, joint mapping, and multi-joint playback
remain separate work.

## Existing owner boundary and limits

The importer should call the real existing factories, not synthesize runtime
identities or callbacks:

- `archive-public.ts:20–27,95–121`: private byte copy, canonical cursors and
  archive binding. File coordinates use data cursor 0x20 and the computed
  table/string cursors.
- `fobj-data.ts:65–73` / the actual FObj runtime: original packed byte copies.
- `fobj-descriptor.ts:30–42,113–123`: copied FObjDesc records.
- `allocated-aobj-descriptor.ts:22–31,77–86`: copied AObjDesc records.
- `jobj-add-animation.ts:22–31,72–76`: copied AnimJoint records.
- `archive-joint-setup.ts:130–134,195–203`: actual wrapper descriptor and
  explicit address-to-owned-AnimJoint binding. Bind each address once; aliases
  reuse it.

Complete structural preflight before publishing these owners is a host safety
choice; it is not the retail parser's mutation/failure order. Byte/count/visit
caps, arithmetic overflow checks, data-region bounds, alignment requirements,
external-reference refusal, finite-float checks, record-overlap restrictions,
cycle rejection and supported root selection are likewise host admission.
External-table sizing is known; importing/resolving its semantics is not done.

Hydration is not playback validation. FObj factories accept finite float32
starts; loading presently admits only integral signed16 starts
(`fobj-descriptor.ts:57–66,151–161`). Joint references remain unsupported
(`allocated-aobj-descriptor.ts:119–120`). Reached RObj/DObj attachment retains
`jobj-add-animation.ts:91–99` refusals. Scalar interpretation supports eligible
opcodes 1, 2 and 6 only (`fobj-callback.ts:1–6,43–51`). Unsupported tracks,
effects or later consumers must fail, never fall back to baked motion.

## Not the tagged archive allocation/parse path

Actual `8004d548` handles a tagged table entry by clearing bit 0, allocating
via `800197a0c(2)`, parsing into wrapper+0x0c and replacing the table cell and
part+4 with the wrapper (`chunk_0006.c:2400–2408`). The current
`animation-archive-bank.ts:1–9,87–111` supports already-owned untagged entries.
Constructing an offline hydrated wrapper does **not** execute or complete that
tagged branch, its allocation, or its cache mutation.

Likewise, one bare DAT is not the MOT container. Existing exporter
`ExtractBlob` uses the next bank-listed blob boundary, potentially including
padding (`export-borg-animation-hsd.mjs:135–145`); the bare importer can require
an exact header-sized span without claiming every extracted container span
has that length. No wrapper scanning, archive acquisition, production bootstrap,
Battle activation, renderer integration, FPSCR parity or original-game parity
is established by this contract or by synthetic importer fixtures.

## Read-only implementation review

Reviewed `packages/combat/src/rom/animation-archive-hydration.ts` and the added
hydrated fixture in `attached-setup-animation.selftest.ts` against this contract.
The importer separates structural preflight from real owner construction,
retains public ordering and exact aliases, and checks FObj cycles without
rejecting completed shared suffixes. Different-start stream overlaps use the
explicit immutable-copy limitation described above. A private-copy handoff
issue identified during review was corrected by passing `bytes.slice()` to the
archive byte factory before later packed-stream copies are made.

The integration fixture changes stream values to distinguish imported bytes
from its earlier handwritten graph, then exercises actual setup, wait-driven
advancement and replacement. This audit did not run tests or the aggregate;
those checks belong to the implementation/integration work, and do not establish
original-input or production parity.
