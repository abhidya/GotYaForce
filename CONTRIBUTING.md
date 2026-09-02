# Contributing to GotYaForce

GotYaForce accepts small, evidence-backed improvements to the browser game,
research corpus, tooling, and atlas. A contribution should be reproducible from
a clean checkout and should distinguish demonstrated behavior from inference.

> **Licensing note:** this repository does not currently include a root license
> file. Do not assume permission to redistribute its contents. Contact the
> maintainer before reusing code or submitting substantial work.

## Clean setup

Requirements: Node.js 20 or newer, Corepack, pnpm 9, Git, and a browser with
WebGL support.

```bash
git clone https://github.com/abhidya/GotYaForce.git
cd GotYaForce
corepack enable
pnpm install --frozen-lockfile
pnpm verify:contributor
```

The final command must exit zero. It type-checks the workspace, runs the four app
selfchecks (`hud`, `menu-flow`, `game-session`, `title-frontend`) plus combat
lifecycle and OGhidra-import regression tests, and builds the production game.
Run `pnpm dev` for the game or `pnpm atlas:dev` for the research atlas.

## Before a pull request

```bash
pnpm verify:contributor
pnpm verify:docs
git status --short
```

`verify:docs` regenerates atlas data and lets VitePress reject broken internal
links. Generated output remains ignored; review `git status` and commit only
intentional source or manifest changes.

Keep each commit focused. In the pull request, name the input evidence, the
command you ran, its result, and the product behavior it proves.

## Evidence and promotion terms

- **Compiled:** the candidate passes its compiler and import/link checks.
- **Oracle-verified:** an independent behavioral check matches the evidence.
- **Integrated:** verified code is selected by the production runtime.
- **Playable:** the browser acceptance route reaches and operates the intended
  game state; compilation alone never establishes this.

For wasm port units the recorded tiers are `compile_only`, `oracle_green`,
`boundary_green`, `transcript_green`, and `dispatch_green`. **`compile_only` means the unit
compiled and linked and nothing else** — it is inventory, not progress, and at
least one `compile_only` unit is proven behaviorally wrong. Never describe a
`compile_only` unit as ported, done, or working. The tier vocabulary is defined
in the root `README.md`, in the
[atlas porting guide](docs-site/contributing/porting.md), and — with the measured
ceiling for each tier and the current per-area state — in
[`docs/verification-status.md`](docs/verification-status.md).

`oracle_green` is the only byte-exact write-comparison claim. `boundary_green`
and `transcript_green` are **callee-boundary** claims and are strictly weaker:
they verify the calls a function makes (and, for `transcript_green`, its return
value), not the memory it wrote. Never report either as `oracle_green`, and
never count a `transcript_green` function toward write-verified coverage. A
`transcript_green` result is a per-FUNCTION artifact
(`research/decomp/data/oracle-results/<unit>.<export>.transcript.json`) and is
deliberately **not** a unit tier in the driver's ledger — two counters
(`src/port_contract.py:125` and `src/port_progress.py:209` in the OGhidra checkout)
treat "tier is not `compile_only`" as verified, which would over-count it. That defect
is latent today and is recorded in full, with its blast radius, in
[`docs/verification-status.md`](docs/verification-status.md) §6.

`dispatch_green` (added 2026-09-02) is a fifth, **orthogonal** console-derived
standard for the class that had no route to any claim at all: the 1,602
functions whose behaviour goes through a ROM function-pointer table. It compares
the port's indirect-dispatch stream — the site, the **resolved GameCube target**,
the uniform-frame arguments and the return of every indirect call — against the
address the console's own branch register held at the branch. It is **not a rung
of the oracle/boundary/transcript ladder**: it sees a channel none of them can
see and is blind to channels they check, so it is never totalled with any of
them and never reported as one of them. It also **requires a module built with
the assembly gate's indirect-call lowering** — an ordinary unit build is still
unobservable, and the harness refuses one rather than passing. Results are
per-FUNCTION artifacts
(`research/decomp/data/oracle-results/<unit>.<export>.dispatch.json`,
verdict token `DISPATCH_GREEN`).

The **GX HLE host** has two further console-derived standards, added 2026-08-31:
`gx_callstream_green` (the SDK-seam call and write-gather-pipe stream) and
`gx_framebuffer_equivalent` (one draw's contribution to a real console frame,
within a declared per-channel tolerance). They are **orthogonal** to the four
tiers above, not weaker or stronger: they compare things a write set, a callee
boundary and a return value cannot see. Never total a GX result with a wasm-unit
tier, and never let `gx_framebuffer_equivalent` be written up as a pixel match —
the ceiling for that boundary is "framebuffer-equivalent, never pixel-identical"
and no result may quietly upgrade it. A GX adapter's `evidenceClass` stays
`"synthetic"` until *that adapter's own* behaviour is checked; neither standard
does that, and the browser smoke phase fails if one ever claims otherwise.

Unknown behavior stays `PARTIAL`, `TUNED`, or `BLOCKED`. Do not replace missing
evidence with plausible constants and label it exact.

## Legal and repository boundaries

Never commit disc images, extracted proprietary binaries, encryption keys,
proprietary SDK files, secrets, local model transcripts, runtime telemetry, or
machine-specific state. Use only lawfully obtained personal inputs under
ignored `user-data/`; publish reproducible hashes, manifests, and derived
evidence where appropriate.

The [atlas contributor guide](docs-site/contributing/) covers verification,
port artifacts, assets, and clean-checkout troubleshooting in more detail.
