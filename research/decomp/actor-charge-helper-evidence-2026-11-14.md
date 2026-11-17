# Actor charge helper: archived source evidence

## Result and boundary

The fixed reader represents **all 164 instructions** in the complete
`800686f0..80068980` helper, its four f32 constants and two three-entry u32 mask
tables from both existing authenticated local ProgramDB snapshots. The snapshots
agree on every decoded operand, typed value, digest and physical trace. No
instruction is omitted or assumed unreachable. This is archived source evidence,
not unchanged original-DOL identity, live FPSCR/GQR/r2 state, actor ownership,
gameplay parity, production integration or a complete actor tick.

The dedicated reader and tests are
[`read_archived_charge_helper_evidence.py`](../tools/matching-decomp/read_archived_charge_helper_evidence.py)
and
[`test_archived_charge_helper_evidence.py`](../tools/matching-decomp/test_archived_charge_helper_evidence.py).
Shared readers and allowlists remain unchanged. The only new reads are the three
fixed spans below. The CLI accepts a snapshot path only; there are no arbitrary
address, width, raw-output or execution options. Output is derived operands,
typed values, provenance, digests and physical traces, never executable bytes.
No original or archived instructions are executed.

The source C cross-reference is `ghidra-export/chunk_0008.c:4692-4793`.
`research/symbols/GG4E-CSM-20220412.map:800-801` records entry `800686f0`, size
`0x290`, and the adjacent entry `80068980`. The C export's warnings about
`80068700` and `80068964` do not justify an omission: these are the reachable
paired stack-save and stack-restore instructions, both decoded here. The global
early-return branch directly targets `80068964`. Scalar `stfd`/`lfd`, paired
`psq_st`/`psq_l`, `stmw`/`lmw` and the final `blr` are all represented. Paired
stack fields are W=0, I=0; their encoding does not establish live GQR0 state.

## Authentication and fixed spans

Inputs remain in the existing local directory
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` verifies the whole snapshot, exact
schemas, executable metadata, big-endian Gekko/Broadway language, address map,
empty File Bytes table, full data5 digest and existing controls before any new
fixed read. Unchanged `read_archived_command_evidence.mappings` checks the exact
text1/data3/data5 block/subblock identities and all-block overlap. Width and
fixed SHA-256 checks precede every new instruction decode or data interpretation.
Data values are independently checked after their digest, including the positive
zero bit pattern rather than merely numeric equality with negative zero.

- Executable import-metadata SHA-256:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This is metadata, not independent evidence of unchanged executable bytes.
- File Bytes table: version 0, root -1, count 0.
- Block size 16384, master root 1, image offset `80000000`.
- Text1: start `800055e0`, length 2796416, block/subblock 1, root 21.
- Data3: start `802bae60`, end `803af120`, length `0xf42c0`, block/subblock 5,
  root 199.
- Data5: start `80436a20`, end `8043d500`, length 27360, block/subblock 7,
  root 263. Full data5 SHA-256:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- All three mappings require subblock type 2, starting offset 0, source offset 0.

| Fixed span | Width | SHA-256 |
| --- | --- | --- |
| `800686f0..80068980` | 656 / 164 instructions | `55523dd4f938a0f11bb9f7a26ae31de5d5eb3647354af3315ba37979340f3817` |
| `802d3970..802d3988` | 24 / six u32 | `57b950110534ba512d9dc0bc63a304c0c8b37bff19ae889779618d3109cd2ae0` |
| `80437628..80437638` | 16 / four f32 | `339a9072dd04453256cb6f8826245e04de4e202128dc8a7cc54cf4654b06e03c` |

Physical spans are identical in both snapshots. Offsets are decimal and all
three spans use obfuscated ProgramDB storage:

| Range | Root / data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| helper | 21 / 46 | 405776 | 12704 | 782758 | 656 |
| masks | 199 / 206 | 101136 | 2868 | 3394362 | 24 |
| constants | 263 / 264 | 3080 | 3080 | 4344846 | 16 |

## Constants, tables and retained values

The four big-endian f32 constants are:

| Address | Value | r2 displacement | Use |
| --- | --- | --- | --- |
| `80437628` | 10 | -29688 | optional rate multiplier and warmup threshold |
| `8043762c` | +0 | -29684 | resets and decay floor |
| `80437630` | 1 | -29680 | warmup step |
| `80437634` | 2 | -29676 | release decay multiplier |

Displacements use the separately recorded SDA2 basis `r2=8043ea20`, not a new
live register capture. Constants are not loaded together at the top of each
slot. The live instruction load sites and retained FPR values matter:

- `8006872c` loads 10 only if the actor's `6fc` byte is nonzero. `80068730`
  performs `fmuls f31,f31,f0` once. Otherwise f31 retains the original rate.
- Reset branch `80068790` or `800687cc` loads +0 into f0 once and uses that
  retained value for both stores.
- Held path `800687fc` loads warmup into f1, then `80068800` loads 10 into f2.
  The comparison and possible warmup overflow use this retained f2.
- Warmup `8006886c` loads 1 into f0, then adds the retained f1 warmup. The source
  stores and explicitly reloads warmup before its second comparison.
- Release `800688c8` loads +0 into f3, then `800688d0` loads 2 into f2. The f3
  zero survives the decay stores and is reused by the final comparison/clamp.
- f31 is retained across the whole three-slot loop and across the mature-path
  call by the calling convention. Release decay **does not use f31**: it
  reloads the actor's current unscaled `768` rate at `800688dc` for every reached
  release slot, after its warmup-zero store.

The six u32 cells are two adjacent but distinct tables:

| Slot | Held table `802d3970 + 4*i` | Release-result table `802d397c + 4*i` |
| --- | --- | --- |
| 0 | `0x200` | `0x400` |
| 1 | `0x200` | `0x800` |
| 2 | `0x400` | `0x1000` |

The repeated held mask for slots 0 and 1 is genuine. The held word is tested
against actor+`5b4`; the release result is ORed into actor+`5d4`. Neither table
identifies a physical controller input or establishes an upstream capture
owner. The selected tables end at the separately authenticated shared-handler
dispatch table `802d3988`; no new read crosses that boundary.

The whole loop retains actor r25, old655 r26, slot i r27, byte stride `4*i` r29,
held-table pointer r30, release-table pointer r28 and actor-slot base r31.
Initially i and stride are zero, r31=actor, and the table pointers are formed
at `80068748` and `8006874c`. Every completed or skipped slot reaches
`8006890c`: increment i by 1, both table pointers by 4, stride by 4 and actor-slot
base by 4, then signed compare i<3 branches to `80068758`. Actor fields below
are hexadecimal offsets; slot warmup and charge fields use `+4*i`.

## Entry and lazy slot gates

1. `80068708` loads the recorded global pointer from r13-31852. `80068710`
   reads its byte `1829`; `extsb.` tests signed byte zero/nonzero. Nonzero
   branches directly to the epilogue at `80068964`, genuinely returns and
   reaches no actor-field load or store.
2. Otherwise load actor byte `6fc` at `8006871c`, then actor f32 `768` into f31
   at `80068720`. **The flag read precedes the rate read**, not vice versa.
   Sign-extension tests the flag. If nonzero, multiply f31 by 10 with one
   single-rounded `fmuls`. This calculation occurs even if all slots will later
   prove disabled.
3. Load actor byte `655` into retained r26 at `80068734`, then clear actor byte
   `655` at `80068744`. The old byte is not reloaded for the final old/new test.
4. At each iteration, `80068758` reloads actor pointer `4b0`, then `80068760`
   loads descriptor byte `bb+i` using `lbzx`. `extsb` makes this a signed-byte
   field. Exactly -1 (`0xff`) skips the whole slot directly to loop advance.
   No slot flags, mask, warmup, charge or threshold are read on that path.
   The descriptor pointer is not a snapshot taken before the loop.
5. Enabled slots read actor u32 `5e0` and test its low two bits. Only when those
   bits are nonzero does `8006877c` read actor byte `584`, sign-extend it and
   compare it to i+3. Equality takes the first reset branch. A zero low-bit
   result skips the `584` read entirely.
6. If the first reset was not taken, `800687bc` reads actor byte `58e` and
   tests `1 << (i+3)`. A set bit takes the second reset branch.
7. Otherwise `800687ec` reads actor u32 `5b4`, `800687f0` reads the current
   held-table entry, and their bitwise AND selects held versus release.

Both reset branches store retained +0 first to `63c+4*i`, then to `648+4*i`.
Only **after those two stores** do they read actor byte `654`, clear bit i with
`andc` and store its low byte. They then advance the loop. Reset does not read
threshold pointer `4ac`, threshold `184+4*i`, rate768 again or old charge.
The first reset does not read `58e`; neither reset reaches `5b4`.

## Held warmup and mature boundary

The held path loads f32 warmup `63c+4*i`, then 10. `fcmpo` and `cror` form
warmup>=10. In the supported finite domain, values below 10 take warmup:

1. Load 1 and `fadds` retained warmup+1, single-rounded; store to warmup at
   `80068874`.
2. **Reload warmup** at `80068878`, then compare to retained 10. If not strictly
   greater, advance the slot with no charge, `654` or threshold read.
3. If greater, `fsubs` computes single-rounded reloaded warmup minus 10 at
   `80068884`. Only then load charge at `80068888`.
4. `fadds` computes single-rounded charge+excess. Store charge at `80068890`,
   then store retained 10 to warmup at `80068894`, and advance.

Do not collapse the two arithmetic instructions, use the pre-store warmup for
its second comparison, clamp charge to a threshold, set `654`, or call an effect
on this path. There is no threshold read here.

For warmup>=10, source order is:

1. Load charge `648+4*i` at `80068810`.
2. `fadds` charge+retained f31 at `80068820`, then store charge at `80068828`.
3. Load actor byte `654` at `8006882c`, OR bit i, and store byte `654` at
   `80068834`.
4. `80068838` calls **`800f0104(actor,1,4)`**.

A bounded no-effect closure must refuse at that exact call after retaining all
preceding writes, including the entry's `655=0` and any earlier slots. It must
not call a no-op or guessed effect, continue to the threshold or undo its
completed prefix.

The authenticated instructions after the call, which the bounded closure does
not execute, are informative but not permission to skip the effect: reload
actor pointer `4ac` at `8006883c`, load charge at `80068844`, indexed-load f32
threshold `184+4*i` at `80068848`, compare charge>=threshold, and if so store
threshold to charge at `80068858` and OR bit i into byte `655` at `80068864`.
This is the only source path that sets a nonzero `655` after its entry clear.

## Release result, exact fused decay and floor

Release begins at `8006889c`:

1. Load actor pointer `4ac`, form `0x184+4*i`, load charge at `800688a4`, then
   indexed-load descriptor threshold at `800688a8`. The charge read precedes
   the threshold read, though its descriptor pointer was loaded first.
2. Compare charge>=threshold. Only if true, load actual actor u32 `5d4`, load
   the current release-result table entry, OR them and store `5d4` at
   `800688c4`. If false, skip both the `5d4` read and the result-mask read.
3. Load +0 into f3 and 2 into f2, then store +0 to warmup at `800688d8`.
4. **Fresh-load unscaled actor rate768** at `800688dc`, then fresh-load charge
   at `800688e0`. Neither the entry rate f31 nor the comparison charge is reused.
5. `800688e4` is **`fnmsubs f0,f2,f1,f0`**: exact product `2*rate` minus charge,
   with one binary32 rounding, then negation. Conceptually in the finite
   RN00/NI0 domain: `-FMA32(2, rate, -charge)`. Store the result to charge at
   `800688e8`.
6. Load actor byte `654`, clear bit i and store it at `800688f4`.
7. **Reload charge** at `800688f8`. Compare it to retained f3 +0 using `fcmpo`,
   `cror LT,EQ`; if charge<=+0, store retained +0 at `80068908`. Otherwise leave
   the value and advance.

There is no intermediate rounded `2*rate` product and no separate rounded
subtraction. In particular, a finite fused cancellation may succeed even when
rounding the product alone would overflow. Negation occurs after fused rounding:
an exact-zero subtraction may produce -0 at the first charge store. That sign
is real intermediate behavior. The later reload/<=0 floor stores **+0**, after
clearing `654`; do not normalize zero before the first store. Reordering the
floor ahead of the `654` read changes the retained prefix on a later refusal.

The source uses `fcmpo`; NaN/exception behavior is not justified by ordinary
JavaScript comparisons. A bounded implementation must delimit its supported
finite binary32 operands/results and RN00/NI0 arithmetic without claiming these
snapshots establish live FPSCR state. Reached-input validation should follow the
load order above and retain earlier stores when a later reached load, arithmetic
operation, destination or unsupported call refuses. It must not preflight every
slot or validate unused thresholds, warmup fields or masks.

## Final old/new655 transition and genuine returns

After all three slots, `80068928` sign-extends retained old655 from r26 and tests
zero/nonzero. It does not compare individual bits or require equality:

- If old655==0, load new655 at `80068930`. If new655==0, genuinely return via
  the epilogue. Otherwise `80068944` calls **`800061cc(actor,0x13)`**.
- If old655!=0, load new655 at `8006894c`. If new655!=0, genuinely return.
  Otherwise `80068960` calls **`800061cc(actor,0x14)`**.

A bounded closure without that callee must refuse exactly at the reached call,
with the actual target, call PC and argument value, retaining all completed
writes. There is no effect call for a nonzero-to-different-nonzero change.

In the normal no-effect bounded closure, old655 is cleared at entry and the
only later source stores that can set bits in655 lie **after** the refused mature
call. Consequently successful disabled/reset/warmup/release loops leave new655
zero. The 0->nonzero transition is authenticated source behavior but is not
normally reachable within that no-effect closure; it must not be made reachable
by a test-only fabricated setter or a permissive effect stub. Nonzero->zero and
its argument0x14 refusal are reachable after the loop. Global1829 nonzero is a
separate genuine early return that leaves655 untouched.

The call into this helper at `800686d8` is separately authenticated by the
[tenth-input evidence](actor-tenth-input-machine-evidence-2026-11-14.md).
The outer actor-tick continuation `800590bc -> 8005a190` is a separate caller
boundary, not newly read or implemented by this evidence. A genuine helper
return does not claim the next outer helper is supported.

## Verification

The dedicated stdlib test suite passes **16 tests**, including both local
archives with no skips when run with the existing archive directory. It checks:

- all164 instruction addresses, forms and operands against an explicit expected
  list, not a golden list generated by the decoder;
- both archives' agreement and complete coverage including paired save/restore;
- all six u32 values, all four f32 encodings and all three physical spans;
- precise call PCs and targets, descriptor sign-extension, branch operands,
  single-rounded arithmetic and the fused negative multiply-subtract operands;
- invalid types, nonallowlisted/partial/adjacent spans, duplicate entries,
  wrong roots/mappings, length/digest failure before decode/interpretation;
- changed schema, metadata/authentication failures, overlap/duplicate/mapping
  guards before fixed reads, and unchanged shared allowlists;
- reserved or unsupported instruction forms, arbitrary CLI option rejection and
  no raw executable/data output.

Run the dedicated suite from the repository's matching-decomp directory:

```sh
PYTHONDONTWRITEBYTECODE=1 python -m unittest test_archived_charge_helper_evidence -v
```

The complete `test_archived*.py` discovery suite also passes **552 tests** with
no skips after adding this reader and its tests.

These checks validate derived archived evidence and fail-closed reader behavior.
They do not execute a retail oracle or prove the eventual bounded runtime;
runtime, composition and aggregate tests are separate obligations.
