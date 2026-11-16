# Actor cue0 and terrain lifecycle: bounded archived evidence

## Result and limits

Both existing authenticated snapshots agree on **150 instructions in two fixed
spans**, the previously authenticated cue0 table cell, and four literal
floating-point constants. This evidence establishes the exact source schedule,
not a completed cue0 port or a synthetic terrain result.

- Cell `802d3300` still contains `8005913c`. That body is now selected separately
  as an independent 180-byte span, not by following the cell value.
- Movement byte `661 == 3` calls `8006a750(actor, 0x1b)` and then
  `8006a6fc(actor, 0x1b)` before returning. Both calls matter.
- Otherwise cue0 calls `80068df8` first. A zero return continues to `800699d8`,
  not to a successful no-op. Subsequent callees remain ordered, short-circuiting
  boundaries unless separately supported.
- Terrain guard `5e0 & 0x40` returns zero before mode `4a0` is read. Mode 2
  returns zero before sampling. The other path invokes genuine `8003d6e4` with
  actor, position pointer `actor+20`, and actor float `668`, then stores its
  result to `24`.
- Byte `732` is read **eagerly after the terrain-result store**, before the
  snapped-height and prior-height loads and before the drop comparison. Float
  `674` is loaded only once; the upper-step comparison reuses that register.
- The active ledge path restores old `24` before displacement math. Positive
  squared distance reaches hardware `frsqrte`, followed by double arithmetic
  with fused `fnmsub`; host `sqrt` is not equivalent evidence.
- A nonpositive squared-distance branch skips the estimate. It still divides
  by actor `5f8`, compares speed, may store speed **before** calling `800452a0`,
  then stores constant `30.0f` to `698` **before** calling `8006a5a4`.
- The non-active upper-step rollback uses raw word loads/stores in a specific
  interleaved order. It is not a batched numeric triple copy.

This is archived ProgramDB static evidence, **not original-DOL identity, live
actor ownership, processor state, retail behavioral parity or playable-game
proof**. No callee body is selected here. In particular, this report does not
supply `8003d6e4`, `800452a0`, `8006a5a4`, or the cue-state helpers. Call identity
must survive any composition with independently supported implementations.

Artifacts:
[`read_archived_actor_cue0_evidence.py`](../tools/matching-decomp/read_archived_actor_cue0_evidence.py)
and
[`test_archived_actor_cue0_evidence.py`](../tools/matching-decomp/test_archived_actor_cue0_evidence.py).
Only these files and this report are added. Shared archive readers/allowlists
are unchanged. The reader has no arbitrary-address, width, pointer-following,
raw-output or execution CLI. No original instructions execute, no binary
payload is written, and neither a retired driver nor a live global is used.

## Fixed selections and extent evidence

The exact selection plan was reported before the first new payload reads.
Selections are independent literals, not values discovered by following code
or data pointers.

| Entry / selection | End exclusive | Bytes | Instructions | Extent basis |
| --- | --- | --- | --- | --- |
| Cue0 `8005913c` | `800591f0` | 180 | 45 | C chunk 7 entry at line 2111, next entry at 2137; sole `blr` at `800591ec`; all non-call branches internal |
| Terrain `80068df8` | `80068f9c` | 420 | 105 | C chunk 8 entry at line 4966, next entry at 5033; sole `blr` at `80068f98`; all non-call branches internal |
| Cue0 cell `802d3300` | `802d3304` | 4 | n/a | Reuse unchanged normal reader's exact cell/hash/target authentication |
| Constant `8043762c` | `80437630` | 4 | n/a | C constant name and source `lfs` at `80068e8c` |
| Constant `80437638` | `80437640` | 8 | n/a | C constant name and source `lfd` at `80068ebc` |
| Constant `80437640` | `80437648` | 8 | n/a | C constant name and source `lfd` at `80068ec0` |
| Constant `80437648` | `8043764c` | 4 | n/a | C constant name and source `lfs` at `80068f24` |

Source C is under `research/decomp/ghidra-export/`. Neither function has a named
extent in `research/symbols/GG4E-CSM-20220412.map`. Map line 803 independently
places predecessor `80068d04` at width `0xf4`, ending at `80068df8`; it does not
provide the terrain function's length. The next C markers, complete decoding,
internal branch targets and terminal returns corroborate these bounded spans,
not an independent retail symbol-map identity claim.

The terrain C export warns that it removed blocks at `80068e08` and
`80068f80`. Both are real paired-single ABI save/restore instructions in the
selected bytes and are explicitly represented. They are not missing bytes or
excluded gaps. Both spans have zero unrepresented instructions/ranges.

## Authentication and provenance

Only these two existing local files under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/` were used:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` authenticates the actual complete
file digest, exact table schemas, program `boot.dol`, language
`PowerPC:BE:32:Gekko_Broadway`, Ghidra creation version `12.1.2`, executable hash
metadata and property type, empty File Bytes, address maps, entire data5 hash
and established controls before any new selection. Executable SHA metadata is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
It remains import metadata, not independent unchanged-original authentication.
File Bytes has version 0, root -1, count 0. Image offset is `80000000`, archive
block size 16384 and master root 1.

Unchanged `read_archived_command_evidence.mappings` checks all-block overlap,
encoded addresses, identities, lengths and subblocks. All exact typed mappings
are then derived from the authenticated rows before any selected payload read:

| Mapping | Range | Block / subblock | Length | Chain root |
| --- | --- | --- | --- | --- |
| `MAIN_.text1` | `800055e0..802b0160` | 1 / 1 | 2796416 | 21 |
| `MAIN_.data3` | `802bae60..803af120` | 5 / 5 | 1000128 | 199 |
| `MAIN_.data5` | `80436a20..8043d500` | 7 / 7 | 27360 | 263 |

Each requires subblock type 2, starting offset 0 and source offset 0. Complete
data5 SHA-256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
Code selections additionally require exact integer address/width, unique
allowlist entry, alignment, mapping bounds, returned width, complete span
SHA-256, explicit decoding of every instruction, terminal return and internal
non-call branch targets. Constants require exact fixed address/width, mapping,
bounds and bits. The cell reuses normal-reader hash and u32 target checks.

| Selection | SHA-256 |
| --- | --- |
| `8005913c/180` | `ae9d04496b94a8823bda233ea5be5e51b2a7855fe462b83ba29c251cc4e3188b` |
| `80068df8/420` | `975733da691528eb19e1ddc92bef341167d1a60154dad7d79836d26f967267c9` |
| `802d3300/4` | `9580f1cc45ceb6223ad8f8413118771eee94978d6f6c1c752bab7d772c40c400` |

All selections have a single identical physical trace in both snapshots.
Offsets and widths below are decimal; all selected spans are obfuscated in the
archive.

| Address | Root / data buffer | Chain offset | Data offset | Physical offset | Width |
| --- | --- | --- | --- | --- | --- |
| `8005913c` | 21 / 42 | 342876 | 15316 | 719834 | 180 |
| `80068df8` | 21 / 46 | 407576 | 14504 | 784558 | 420 |
| `802d3300` | 199 / 206 | 99488 | 1220 | 3392714 | 4 |
| `8043762c` | 263 / 264 | 3084 | 3084 | 4344850 | 4 |
| `80437638` | 263 / 264 | 3096 | 3096 | 4344862 | 8 |
| `80437640` | 263 / 264 | 3104 | 3104 | 4344870 | 8 |
| `80437648` | 263 / 264 | 3112 | 3112 | 4344878 | 4 |

## Literal constants and SDA2 caveat

| Address | Type | Exact bits | Value | SHA-256 |
| --- | --- | --- | --- | --- |
| `8043762c` | f32 | `00000000` | +0 | `df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119` |
| `80437638` | f64 | `3fe0000000000000` | 0.5 | `ace5732151a42e3c2ce91e039d0bd2d3a86dce1bccb6b874852b1aaa7f01d3bd` |
| `80437640` | f64 | `4008000000000000` | 3 | `de6e66408b37be649404fe9033a088f217bfc6a37dfe9dd7a735a376d88d8cdd` |
| `80437648` | f32 | `41f00000` | 30 | `964bc35d520d851571318cf74d05c759824d6ff4c949dc8cf9160a989b72da35` |

Previously recorded `r2 = 8043ea20` is from
`docs/static-recompilation-spike.md:178`. The four authenticated load
displacements are respectively `-29684`, `-29672`, `-29664`, `-29656`, producing
the exact static addresses above. This arithmetic relation is not a fresh
startup-instruction authentication or live r2 capture. No globals are read to
infer actor state, helper output, processor modes or ownership.

## Exact cue0 call schedule

`80059150` uses `lbz r0,0x661(r3)` followed immediately by signed-immediate
comparison with 3. There is **no `extsb`** here. Equality selects the following
path; inequality at `80059158` jumps to `80059174`.

1. `8005915c`: r4 receives `0x1b`; `80059160`: call `8006a750`.
2. `80059164`: r3 receives the saved actor; `80059168`: r4 receives `0x1b`.
3. `8005916c`: call `8006a6fc`; `80059170`: jump to epilogue `800591dc`.

The return from the first call does not suppress the second call. The remaining
path has these exact call/check sites:

| Call site | Target | Compare returned r3 with 0 | Nonzero exit branch |
| --- | --- | --- | --- |
| `80059174` | `80068df8` | `80059178` | `8005917c` |
| `80059184` | `800699d8` | `80059188` | `8005918c` |
| `80059194` | `80069814` | `80059198` | `8005919c` |
| `800591a4` | `800696f4` | `800591a8` | `800591ac` |
| `800591b4` | `80069038` | `800591b8` | `800591bc` |
| `800591c4` | `80069354` | `800591c8` | `800591cc` |

Each branch is `bc BO=4, BI=2` to `800591dc` (not equal). The zero path restores
r3 to the actor before the next call. Only if all six return zero does
`800591d4` call `80068f9c`. `800591d8` still compares its return with zero, but
there is no following conditional branch; the epilogue begins immediately.
The only return instruction is `800591ec`.

## Terrain guards and genuine sample

After ABI saves, `80068e10` loads actor word `5e0`; `80068e14` saves actor in
r31. `80068e18` uses `rlwinm. SH=0, MB=25, ME=25`, selecting mask `0x40`.
Zero goes to `80068e28`; nonzero sets r3 to zero at `80068e20` and jumps to the
epilogue. Only the zero-mask path loads mode `4a0` at `80068e28`. Its `lbz` is
compared directly with 2, again with no sign extension. Mode 2 returns zero via
`80068e34/38`.

Other modes perform:

| PC | Exact source effect |
| --- | --- |
| `80068e3c` | `lfs f31,0x24(r31)`: preserve the pre-sample Y |
| `80068e40` | r4 = actor + `20` |
| `80068e44` | `lfs f1,0x668(r31)` |
| `80068e48` | `bl 8003d6e4`, r3 still actor, r4 position pointer, f1 argument |
| `80068e4c` | `stfs f1,0x24(r31)`: store returned terrain Y |
| `80068e50` | r3 = 0 |
| `80068e54` | load byte `732` |
| `80068e58` | load snapped Y `24` to f1 |
| `80068e5c` | load prior Y `30` to f0 |
| `80068e60` | `extsb.` byte `732`, recording CR0 |
| `80068e64` | load step limit `674` to f2 |
| `80068e68` | single `fsubs f1,f1,f0` |
| `80068e6c/70` | if sign-extended byte is nonzero, set r3 = 1 |
| `80068e74` | `fneg f0,f2` |
| `80068e78/7c` | ordered `fcmpo f1,f0`; LT enters active path `80068e88` |
| `80068e80/84` | otherwise compare r3 with 0; zero enters `80068f3c`; nonzero falls through active |

Byte `732` must not become a lazy read performed only if the drop comparison
fails. Step `674` must not be reloaded for the upper comparison. Source C's
logical expression does not convey these instruction-order details.

## Active ledge: exact supported prefix and ordered boundaries

`80068e88` first restores saved f31 to actor `24`. Only then:

1. `80068e8c`: load static +0 into f0.
2. `80068e90/94/98`: load current Z `28`, prior Z `34`, current X `20`.
3. `80068e9c`: `fsubs f2 = currentZ - priorZ`.
4. `80068ea0`: load prior X `2c`; `80068ea4`: `fsubs f1 = currentX - priorX`.
5. `80068ea8`: single `fmuls f3 = f2 * f2`.
6. `80068eac`: single **fused** `fmadds f6 = f1 * f1 + f3`.
7. `80068eb0`: ordered compare f6 with +0. `80068eb4` branches to `80068f04`
   if GT is false. Positive f6 falls through to `80068eb8`.

For a finite nearest-even binary32 implementation, f6 can be zero after rounded
underflow even if a displacement was nonzero. The branch tests f6, not a
separate `dx == 0 && dz == 0` predicate. Static instruction evidence does not
supply captured FPSCR modes, exceptional arithmetic or universal numeric
parity. Such domains must be explicitly limited rather than silently guessed.

### Positive f6

`80068eb8` is `frsqrte f3,f6`. A runtime without an authenticated implementation
must refuse here, after the earlier terrain store and Y restoration. Replacing
it with `1 / Math.sqrt(f6)` or `Math.sqrt(f6)` would invent behavior.

The remaining static schedule is fully represented, even when unsupported at
runtime. `80068ebc/ec0` load f5=0.5 and f4=3 as doubles. Each of the first two
refinements uses four double instructions:

- `80068ec4/d4`: `fmul f0,f3,f3`.
- `80068ec8/d8`: `fmul f3,f5,f3`.
- `80068ecc/dc`: fused `fnmsub f0,f6,f0,f4`.
- `80068ed0/e0`: `fmul f3,f3,f0`.

The third begins `80068ee4/e8/ec` with the same square, half-scale and fused
negative multiply-subtract. `80068ef0` multiplies f3 by the correction into f0;
`80068ef4` multiplies f6 by f0. `80068ef8` rounds with `frsp`; `80068efc` stores
to stack+8 and `80068f00` reloads f6. These are double multiplies and fused
negative multiply-subtract, not single operations or a reassociated C formula.

### After the estimate branch, including zero f6

`80068f04` loads denominator `5f8` into f3; **then** `80068f08` loads speed `44`
into f0. `80068f0c` is single `fdivs f3,f6,f3`. `80068f10` uses ordered compare
f3 against f0. Not-GT at `80068f14` jumps to `80068f24`.

The greater path stores f3 to actor `44` at `80068f18`, then calls `800452a0` at
`80068f1c` with the retained dx/dz in f1/f2. The returned low16 is stored at
actor `5ae` at `80068f20`. No host angle function is authenticated here. If the
callee is unsupported, refusal occurs after the speed write, before its return
or the `5ae` store can be fabricated.

Both paths next load exact `30.0f` at `80068f24`, restore actor to r3 at
`80068f28`, and store the constant to actor `698` at `80068f2c`. The call to
`8006a5a4` is at `80068f30`; only after it returns does `80068f34` set r3 to 1.
The helper's body was deliberately not added to this checkpoint. An unsupported
helper is therefore a boundary **after the `698` store**, not a successful
terrain return. A zero-distance implementation still needs a declared finite,
nonzero denominator domain for division; source guards do not validate it.

## Non-active upper-step rollback

`80068f3c` compares the retained f1 (dy) with retained f2 (step `674`) using
`fcmpo`. Not-GT at `80068f40` skips to the return-zero instruction `80068f7c`.
For GT, the function loads current X `20` and prior X `2c` at `80068f44/48`
and compares with `fcmpu` at `80068f4c`. Not-equal at `80068f50` enters rollback
immediately, without loading Z for comparison. Otherwise it loads current Z
`28` and prior Z `34` at `80068f54/58`; `fcmpu` at `80068f5c` and equality
branch at `80068f60` skip rollback if Z is also equal.

The rollback instruction order is exactly:

1. `80068f64`: `lwz` prior X `2c` into r3.
2. `80068f68`: `lwz` prior Y `30` into r0.
3. `80068f6c`: `stw` r3 to current X `20`.
4. `80068f70`: `stw` r0 to current Y `24`.
5. `80068f74`: `lwz` prior Z `34` into r0.
6. `80068f78`: `stw` r0 to current Z `28`.
7. `80068f7c`: r3 = 0.

These are raw 32-bit transfers. Current and prior coordinates are not all
loaded before the first store. Already-performed stores must remain visible if
an explicitly unsupported later access stops a bounded runtime implementation.

## ABI representation and verification

The terrain prologue contains `stfd f31,32(r1)` at `80068e04` and
`psq_st f31,40(r1),W=0,I=0` at `80068e08`. The epilogue begins with
`psq_l f31,40(r1),W=0,I=0` at `80068f80`, then restores LR, f31 via `lfd`, r31
and the stack before `blr` at `80068f98`. Decoding these forms does not establish
live GQR0 contents, paired-lane state or full instruction execution parity.

Verification command:

```sh
python3 -m unittest discover -s research/tools/matching-decomp \
  -p 'test_archived_actor_cue0_evidence.py' -v
```

Result: **30 tests passed**, including 15 synthetic fail-closed tests and 15
archive/source tests; neither existing snapshot was skipped. Tests cover exact
selection bounds/types/mappings, digest-before-decode, constants and signed-zero
bits, cell identity, unsupported/reserved operands, paired-single saves,
terminal/internal control-flow checks, authentication-before-selection, CLI
scope, complete coverage, source extent caveats, every meaningful call/read/
write/arithmetic schedule, and equality of both snapshots' derived evidence.
This focused result is not a full repository build or behavioral parity claim.

Regression command `python3 -m unittest discover -s research/tools/matching-decomp -p 'test_archived_actor_*evidence.py' -q` also passed: **205 tests**, with no skips. `git diff --check` passed. These remain archive-reader checks, not original-code execution.
