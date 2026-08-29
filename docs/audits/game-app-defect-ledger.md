# Game app and ported-library defect ledger

**Provenance.** Rescued 2026-08-29 from untracked session audits dated 2026-08-21
(`game-webapp-libraries-audit`, `current-game-webapp-audit`, `playability-architecture-audit`),
2026-08-22 (`game-webapp-bug-hunt`), and a 2026-08-23 re-validation pass appended to the
libraries audit. Baselines: GotYaForce `8b785f73` / `0901d3cd`.

**Status of this page.** Mixed. The P0 tier was fixed on `claude/rom-driver-p0-fixes`
(eleven commits, 2026-08-22) and re-confirmed here; a substantial P1/P2 remainder is still
open. Each row says which. Statuses re-checked against the tree on 2026-08-29 unless the
row says UNVERIFIED.

---

## 1. The two sweeps and what they were

Two independent read-only sweeps of `apps/game` and the workspace packages it consumes.
ROM-behaviour claims were checked line by line against `research/decomp/ghidra-export/`
before anything was changed. The value of the ledger is that it separates three things
that look alike from the outside: real ROM transcription errors, product bugs a player
would see, and stale test harnesses that fail without indicating a defect.

The audits also settled a scope question that keeps resurfacing: **the browser game is a
real vertical slice, not a scaffold.** A live Chromium run went Title → Challenge → Normal
→ 1P → Load Box → Select Force → Battle Intro → rendered battle HUD with no console
errors, and a production bundle builds and serves under `/GotYaForce/game/`. The
conclusion was to repair and gate it, not replace it.

---

## 2. Fixed and confirmed

Landed on `claude/rom-driver-p0-fixes` (2026-08-22) and verified present in the tree on
2026-08-29.

| # | Defect | Where | Confirmation |
| --- | --- | --- | --- |
| 1 | **ROM stream clock double-advanced**, dropping every other frame. `tick()` did `dispatchEvent(streamFrame)` → `streamFrame++` → `resolveHits(...)`, and `resolveHits` opened with `this.streamFrame += 1`. From the first `armHit` on, the clock ran 2/frame while dispatch ran 1/frame: half of every ported family's decoded stream events (`playAnim`, `fireChild`, later `armHit`) were silently skipped, specials timed out at half their authored length, and a 1-frame hit window on the wrong parity could never fire. The rate was not even constant within one move — the increment sat inside the `armedHits.length === 0` early return. | `packages/combat/src/bridge.ts:2314` | commit `b9dd2d4e`. The fix also had to separate the hit-window clock from the stream clock, because `onArmHit` reset the shared counter and desynchronised every schedule. |
| 2 | **Three inverted control-word masks.** `& ~0xffffffNN` where the ROM uses `& 0xffffffNN`. In JS `~0xffffff4f === 0xb0`, so these *kept* the bits the ROM *clears*. DEATH BORG ALPHA's action-0 blast wiped the airborne latch and all status bits ≥ `0x100`, making the airborne re-dispatch permanently unreachable; the third inverted the other way and left METAL HERO flagged airborne for the rest of the move. Eleven sibling family modules do it correctly — isolated transcription errors. | `packages/combat/src/families/unregistered-cluster.ts:320`, `:426`, `:1047`, against `chunk_0049.c:1431`, `chunk_0049.c:1733`, `chunk_0054.c:3317` | commit `b9dd2d4e` |
| 3 | **Title screen soft-locked permanently if any title asset 404'd.** The VM ticks only from the rAF loop started as the *last* statement of the async loader's `try`. Every preceding `await` was unguarded (only the 37 diorama models had `.catch(() => null)`). One 404 → warning logged, VM never ticks, every keypress/click/gamepad button swallowed forever — and `data-gf-runtime` was already `boot-ready`, so health checks read green. | `apps/game/src/ui/screens/TitleIntro.ts:717-718`, `:648-652`, `:684-704` | commit `48d1ed0a` |
| 6 | `interrupt()` never reset `parts[].streamPtr`, so after any mid-special interrupt (e.g. death) the `handled` check returned true forever and every later X press locked the borg into a bogus 30-frame special. | `bridge.ts:2341`, check at `:2004-2006` | commit `5656295e` |
| 7 | **ROM-driven borgs were immune to hitstun.** `battle.ts` interrupted on death only, though `bridge.ts:2339` documents "hit/down/death". A struck borg's `stateTime` never advanced, hitstun never expired, and the hit reaction was discarded on completion. | `battle.ts:1129-1147` | commit `605ef8ec`; `packages/combat` now has `test:lifecycle` (`scripts/run-lifecycle-tests.mjs`), wired into `pnpm verify:contributor` and therefore into CI. |
| 13/23 | Family projectiles never drained (`bridge.ts:1414`) and colliding uids. | | commit `4c23a327` |
| 14 | **Gotcha Box save destroyed by one malformed row.** Whole-array-discard-then-overwrite: one bad row, or any version bump, wiped the save and the next write persisted the empty state. | `apps/game/src/sim/getStorage.ts:39` | commit `a558086e`. Confirmed: `GOTCHA_BOX_UNREADABLE_KEY = "gf-gotcha-box-v1.unreadable"` parks the unreadable payload before the empty state replaces it, and keeps the **first** such payload so a later failure cannot clobber the copy. |
| 15 | Same class, all 30 force slots destroyed by one malformed entry. | `SelectForce.ts:65-86` | commit `ac450214`; `FORCE_SLOTS_UNREADABLE_KEY = "gf-force-slots-v1.unreadable"`. |
| 18 | One throw permanently froze the render loop while the sim kept running. | `packages/core/src/index.ts:80-84` | commit `57061fd5`; `pnpm test:render-loop` exists. |
| 22 | **PowerPC vs JS shift semantics** in the status immunity test. `1 << maskedId` overflows for ids 32–63. | `packages/combat/src/status.ts` | commit `47af5c82`. Confirmed: `status.ts:37` now returns `false` for `maskedId >= 32` before the shift. |
| — | eagle-jet: wrong exit cue + missing cooldown, inclusive cone gate, unbranched part slots. | `families/eagle-jet.ts:133-135`, `:147` | commit `4242b81c` |
| — | `stepTargetRoll` dropped targets the ROM keeps, at 8 of 9 call sites. A second defect the sweep did not name was found during the fix: the `+0x1dfc` decay ran outside the `param_2 == 0` gate entirely, not just at the wrong call sites. | `rom/helpers.ts:216-239` | commit `eb46e2a2` |
| P1-3 | Battle Intro confirmation leaked into the battle Pause edge — the same Enter press that confirmed the Intro opened `1P PAUSE` as the battle mounted. | `apps/game/src/main.ts` | Fixed by `7330d329` (2026-08-21 05:58), *before* the audit that reported it; `pauseInputEdge.consume(pauseControlPressed())` sits at the battle-session creation site and `scripts/battle-pause-input-edge.test.mjs` covers it ("a held briefing confirmation can be consumed by the new battle"). Wired as `pnpm selfcheck:battle-pause-edge`. |
| P1 | The autonomous port-PoC browser gate asserted `data-gf-runtime="loaded"`, a value `main.ts` no longer produces (it emits `booting` / `boot-ready` / `boot-failed`), so a successful candidate promotion reached a browser stage whose readiness assertion was obsolete. | `scripts/finish-game-port-poc.mjs:717-726` | The stale marker is gone from that script, and `scripts/finish-game-port-browser-gate.test.mjs` now asserts against the maintained smoke's source (`pnpm selfcheck:browser-poc-gate`, in `verify:contributor`). |
| P0 | **No generated C/Wasm had any product interface.** The audited production bundle contained zero `.wasm` files; no loader, no shared-memory contract, no host imports, no adapter from C exports to `Battle`/`RomActor`. | | Since built: `packages/rom-runtime/` (`host.ts`, `memory.ts`, `protocol.ts`, `worker.ts`), `packages/combat/src/rom/wasmDamageCore.ts`, and `apps/game/src/sim/romDamageBoot.ts`. See [`../playable-port-design.md`](../playable-port-design.md) for the contract this became. |

### Two findings deliberately **not** fixed

- **#11 dead-borg hide.** The code reads as inverted against its own comment
  ("dim/hide once dead so the death pose reads"), but keeping a dead borg **visible** is
  what makes a death pose readable. The comment is wrong, not the code; flipping it would
  likely hide the pose.
- **The stub-definition guard** was built as deterministic validation rather than a prompt
  change, on the grounds that a prompt cannot be relied on and validation is testable.
  Whether the prompt should *also* say it is an owner decision.

---

## 3. Still open

### 3.1 The combat test corpus is largely unreachable — OPEN

`packages/combat/src/selfcheck.ts` carries roughly 120 assertions with no runner anywhere.
Of the `scripts/run-*.mjs` runners present in the tree, **18 are still absent from every
`package.json` script** as of 2026-08-29: `run-ammo-tests`, `run-attack-schema-tests`,
`run-burst-tests`, `run-challenge-flow-tests`, `run-challenge-tables-crosscheck`,
`run-contact-damage-tests`, `run-cue-resolver-tests`, `run-fusion-tests`,
`run-healing-tests`, `run-judge-tests`, `run-level-tests`, `run-mash-counter-tests`,
`run-move-properties-tests`, `run-penetration-tests`, `run-projectile-tests`,
`run-source-camera-tests`, `run-status-tests`, `run-voice-cues-tests`.

This has materially improved since the audit — CI now runs `pnpm verify:contributor`,
`pnpm test:oracle` and `pnpm verify:docs`, where at the time of the audit
`deploy-pages.yml` ran no tests at all — but the corpus above is still dark.

**This is the finding that lets the others survive.** Finding #4 below shipped precisely
because its test was orphaned.

Two runners were reported failing in the committed tree, independently of the P0 fixes
(both reproduced with the changes stashed):

- `run-projectile-tests.mjs` — 121 of 145 checks FAIL; first failure
  `victim.lastHitImpactEffectId mirrors the applied record — expected 1, got undefined`.
- `run-burst-tests.mjs` — `ERR_MODULE_NOT_FOUND` for
  `packages/render/src/camera/sourceCamera.js`.

*Not re-verified on 2026-08-29:* these runners import from `packages/combat/dist/`, so
they need `pnpm -r build` first; running them cold only reproduces the missing-`dist`
error, which is not the same claim.

### 3.2 `cMtxLookAt` look-vector direction — OPEN, needs an owner decision

`packages/render/src/camera/sourceCamera.ts` computes `vLook = target - cam`. The audit
found libogc's `C_MTXLookAt` — cited in that file's own header — uses `camPos - target`,
which would leave the view matrix rotated 180° about Y, **and found that the test at
`:458-460` pins the buggy matrix**. The file header today documents
`vLook = norm(target-eye)`, i.e. the direction the audit flagged. Because the pinning test
is one of the orphaned runners (§3.1), nothing currently arbitrates this. Resolve it
against libogc before wiring `run-source-camera-tests.mjs` into CI, or the test will lock
in whichever answer is already there.

### 3.3 ROM X-special unreachable for all 17 X-Charge borgs — UNVERIFIED

`tryStartXSpecial` sat only in the `else if (pressedSpecialEdge)` arm
(`packages/combat/src/combat.ts:2440-2466`). All 17 X-Charge borgs are registered
families, so their ported phase machines could never be entered.

### 3.4 WebGL context and GPU-memory leaks — OPEN

- Actor GLB models are never disposed. Models are deep-cloned per instance, so this is a
  real leak, not shared state (`apps/game/src/sim/battleScene.ts:757-764`, `:789-805`).
- `ui/sceneModel.ts:97-103` and two other sites call `renderer.dispose()` **without**
  `forceContextLoss()`. `SelectForce.renderSlot` builds a new renderer per slot change, so
  roughly 10–15 Left/Right presses can kill the main battle canvas. Confirmed 2026-08-29:
  `forceContextLoss` appears nowhere under `apps/game/src`.
- Stage switching calls `stageRoot.clear()` *before* fetching the next stage and its GLBs
  (`apps/game/src/main.ts:493-518`). Three.js `clear()` only detaches; nothing disposes
  stage GLTF geometry, materials or textures. If the fetch fails, the previous working
  stage is already gone.

### 3.5 Package entry points break Node/dist consumers, and combat pulls in rendering — OPEN

`packages/render`, `packages/combat` and `packages/missions` point `main` and `types` at
`src/index.ts` (raw TypeScript). The render barrel re-exports `./camera/sourceCamera.js`.
Vite and TypeScript map this source-oriented convention; **Node loading a built consumer
resolves the TS package entry and then cannot find the sibling `.js` beside it.** That is
the direct cause of the `sourceCamera.js` failures in `selfcheck:1p`,
`selfcheck:challenge-stages`, `selfcheck:readability-flagged-stages` and
`run-burst-tests`.

Separately, `packages/combat/src/bootGlobals.ts` imports `createSourceCamera` and
`sourceCameraBootViewSetup` from `@gf/render`, which contradicts `index.ts`'s own
"NO DOM, NO three.js" contract and makes `@gf/combat` depend on all of render — so
supposedly headless combat tests acquire a browser/render dependency. Confirmed
2026-08-29: `@gf/combat`'s `package.json` still declares `"@gf/render": "workspace:*"`
and still points `main`/`module`/`types` at `src/index.ts`.

This is **not** an unused-dependency cleanup. Fixing it means relocating the pure camera
math to a lower, Three-free package — an architectural change.

### 3.6 `@gf/save` is a facade — OPEN

`apps/game/src/main.ts:746-750`: "Load Box Data" `onConfirm` and `onSkip` both call the
same `box-continue`; no load occurs. `packages/save/src/index.ts` is confirmed still a
comment block plus `export {}`. The app instead stores a custom Gotcha Box JSON blob in
`localStorage`. There is no GameCube save import/export, IndexedDB schema, migration, or
byte-exact round trip. Either implement the `@gf/save` contract behind the screen or
rename it Skip-only.

### 3.7 Remaining P1/P2 findings — UNVERIFIED

Recorded 2026-08-22, not re-checked:

- `onArmHit` discards prior windows and rewinds the clock — replaces `armedHits` wholesale
  and sets `streamFrame = 0` mid-tick (`bridge.ts:2206`, `:2219`).
- Entry-frame velocity sync is dead code; the guard is inverted relative to its own
  comment and all three callers set `specialActive = true` first, so momentum is zeroed at
  the first ROM special (`bridge.ts:1843`).
- CPU ×0.5 damage halving wrongly applied on INSANE: `battle.ts:316` sets
  `isChallengeMode` from `cfg.challengeMode !== undefined`, but the gate is documented as
  modes 0/1 only (`damage/sourceDamage.ts:128`, `:240-242`).
- Force edited from MAIN MENU is silently reverted (`ui/screens/SelectForce.ts:62-63`,
  `:96-110`).
- `families/ninja-cluster.ts:202-207` advances phase-1 wrongly in both directions.
- `moveProperties.ts:64` — `startsWith` makes `"X"` match `"X Charge"` for 5 borgs. Still
  a prefix match at that line on 2026-08-29; whether it is now guarded upstream was not
  determined.
- `battle.ts:897-902` — ROM ground clamp sits 10 units below the generic one.
- `bootGlobals.ts:489-548` — `__fill_mem` alignment math leaves the tail unfilled.
- `main.ts:397` — debug overlay detached before first use.
- Challenge-menu, HUD, AI and lifecycle items (detail was in the session transcript only
  and did not survive; treat the list above as the recoverable set).

### 3.8 The differential promotion gate has a structural blind spot — OPEN, important

`scripts/lib/oghidra-port-auto-verify.mjs:63-65`: `deriveBoundaryScenarios` collapses the
IR's `branchValues` to a single scalar (`0x61b`) — **the exact value at which the buggy
eagle-jet fallback coincides with the ROM.** The gate reported `passed` and promotion was
written while a live divergence existed. The same blind spot applies to any future value
switch. A differential gate that samples one point of a branch space is not a gate.

### 3.9 Fidelity fallbacks hide gaps in verification runs — UNVERIFIED

`GF_SOURCE_STRICT` is off by default in `gameSession`, so Challenge VM exceptions warn and
silently use a hardcoded HLE roster. UI scene-model failure leaves an empty canvas. Audio
initialization, autoplay and SFX errors are caught without diagnostics
(`main.ts:550-570`, `:558-563`, `:589-596`, `:599-604`). Storage hides
unavailable/corrupt/quota failures. These are defensible player-facing fallbacks and
indefensible in a verification run: **verification mode must fail on fallback, asset 404,
missing cue, and source-path substitution.**

Related: Challenge stage/roster selection uses `Math.random`
(`gameSession.ts:267,278`) and drop RNG is seeded from `Date.now`
(`main.ts:667-678`), so two runs cannot serve as a stable differential corpus without an
injected seed and clock.

### 3.10 2P is exposed but not independently playable — UNVERIFIED

`gameSession.ts:654,782,815` creates up to two local players and `main.ts:1055-1060` gives
P2 a second gamepad, but session focus is always `localPlayerIds[0]`
(`gameSession.ts:823`) and one camera/HUD follows that focus. Player 2 can act with no
camera and no HUD. Either prove separate P1/P2 surfaces or hide the 2P choice until a
shared-camera specification exists.

Network multiplayer is a dormant server, not a web-app seam: `apps/game/server.mjs`
implements room validation and pose broadcasts, but `main.ts:532-537` only has
`let ws` / `closeSocket` / `void closeSocket` and never constructs a `WebSocket`. Vite
does not run `dev:server` and GitHub Pages is static.

### 3.11 Reference-capture docs point at paths that do not exist — UNVERIFIED

`apps/game/reference/README.md:3-9` demands five filenames that do not exist; the actual
captures use `challenge-*` names in the `captures` subdirectory.
`apps/game/reference/captures/BRANCHES.md:16-18` links `../../../user-data/GG4E/traces`,
which resolves to a nonexistent `apps/user-data/...`; the real gitignored directory is at
the repository root.

---

## 4. Checked and clean

Recorded so the next sweep does not re-spend the effort. Checked 2026-08-22 with nothing
found: `==` vs `===`, operator precedence, swapped arguments, menu index wrapping,
`addEventListener` without removal, collision math
(`packages/physics/src/collision.ts`), scoring/GET/settlement math, silently skipped tests
(the problem is orphaned runners, not skips), shared module-level mutable state in
`families/`, and try/catch swallowing errors in the ROM driver layer (there is no
try/catch there).

---

## 5. Standing rule: what may be called "playable"

From the playability audit, and still the bar. A commit may claim a playable vertical
slice only when one fresh command, from a clean checkout plus documented user-supplied
assets, proves all of:

strict type-check and production build; the production-base server route; zero unexpected
console errors, network failures or fallback flags; title/menu input; Challenge
configuration and real asset load; battle model/stage/HUD rendering; at least one
player-controlled move or attack with an asserted state effect; death, deployment/energy
accounting, and a **non-ongoing** battle result; the Results screen and a next action; and
the exact promoted-behavior manifest and oracle attestation consumed by that build.

Unit count, commit throughput, compilation, assembly high-water marks, and readiness
markers do not substitute for any line of that.

### Metrics that were measured to be false

| Claim | Why it was false | Replacement |
| --- | --- | --- |
| `status=green` | Included compile-only artifacts and legacy un-tiered records. | Count `compiled_isolated`, `oracle_verified`, `product_verified`, `integrated` separately. |
| "27 staged" | Inventory can grow without reducing any playable-path gap. | Dependency-closed vertical-slice manifest coverage. |
| `largest_n_passed=5` | Historical high-water, not current membership; the last run had failed. | Hash of the exact certified manifest plus a current pass attestation. |
| Assembly instantiate smoke | Imports every function as `() => 0` and invokes no export. | Execute an exported scenario with the real host adapter and assert a state diff. |
| `data-gf-runtime="loaded"` | Set before initial assets complete and before any playable screen. | A browser transcript: boot-ready → input → battle → non-ongoing → Results, zero console/network errors. |
| TypeScript type-check | Passed while runtime selfchecks failed. | Type-check **plus** a supported package-entry import **plus** behavioral tests. |
| Manifest/file counts | 6,105 references existed while one production code path still built the wrong URL. | Production-base network assertions plus render/use assertions. |
