/**
 * titleVm — 1:1 TypeScript port of the GG4E front-end desk/title intro script VM.
 *
 * Source (all addresses are GG4E/NTSC-U boot.dol):
 *   - `zz_01c7de4_` @0x801c7de4 (chunk_0055.c:2490) — the per-frame bytecode dispatcher.
 *   - `PTR_FUN_8038a4f8` — 22-entry handler table (one fn pointer per opcode).
 *   - `DAT_8038a3b8` — 22-entry opcode payload-length table (advance = len[opcode] + 1).
 *   - The 22 opcode handlers at 0x801c7e64..0x801c846c.
 *   - `FUN_801c795c` @0x801c795c (chunk_0055.c:2227) — VM init: seeds the 6-slot borg-id
 *     table at state+0x10 from `DAT_8038a4ec` (flat u16[6]: slot 0=0x0615 G RED,
 *     slot 1=0x000a Sasuke pl000a, slots 2..5=0xffff), zeroes the 0x18b8-byte state
 *     block, installs the PC into state+0x20.
 *   - Actor chain: opcode 0x0d (`FUN_801c81a0`) → `zz_0057ff8_(actor, 5, animId)` →
 *     `zz_004beb8_(rate, actor, 0xf, 5, animId, -1, -1)` (chunk_0007.c:1109 /
 *     chunk_0006.c:1429); opcode 0x0d mode 1 → `zz_0058044_(actor)` (reset).
 *
 * The VM is INSTRUCTION-FAITHFUL: every handler ports its decompiled-C (or, for the 6
 * handlers Ghidra did not emit as standalone fns — opcodes 4/5/6/8/9/14 — its decoded
 * PPC bytes). Engine-side effects (archive attach, render-table lookups, GX draw state,
 * audio) are delegated to a `TitleEffectSink` so the renderer can map them to three.js /
 * Web Audio at the boundary; each delegation is cited at the ROM call it replaces.
 *
 * The state layout mirrors the ROM `PTR_DAT_80433934` block (field offsets preserved as
 * `_ofs0xNN` comments so this file is auditable against the decompile).
 */

// Pulled from the generated script data (itself dumped straight from boot.dol by
// scripts/gen-title-intro-script.mjs). These ARE the ROM tables — no hand-transcription.
import {
  TITLE_INTRO_OPCODE_LENGTHS,
  TITLE_INTRO_SCRIPT_BYTES,
  TITLE_INTRO_ACTOR_DESCRIPTORS,
} from "../titleIntroScript.generated.js";

/** Per-opcode payload length (DAT_8038a3b8). Advance = OPCODE_LENGTHS[opcode] + 1. */
const OPCODE_LENGTHS: readonly number[] = TITLE_INTRO_OPCODE_LENGTHS;

/** The bytecode itself (DAT_8038a3ec). PC indexes into this. */
const SCRIPT: readonly number[] = TITLE_INTRO_SCRIPT_BYTES;

/** ROM DAT_8038a3d0 lookup table used by fade opcodes 0x07/0x08. Probed straight from
 *  boot.dol (16 BE f32): the table is 7 real entries; index 7+ reads as denormal floats
 *  (0x00000007 etc. = a different adjacent data struct), so the fade args only ever index
 *  0..6. These are FRAME-COUNT durations/accumulators, not alpha lerps — the tick
 *  (zz_01c7ba0_) does `current += step` until `current >= target`, then the renderer
 *  derives the fade alpha from the ratio. */
const FADE_FLOAT_TABLE: readonly number[] = [0.0, 1.0, 30.0, 59.0, 399.0, 729.0, 789.0];

/** A desk-intro actor slot (port of the DAT_803c4e84 entries — each is a full actor
 *  object in the ROM; here we carry only the fields the VM + a renderer need). */
export interface TitleActor {
  slot: number;
  borgId: string;
  visible: boolean;
  /** Most-recent anim started by opcode 0x0d mode 0: (groupSel=5, animId). The renderer
   *  resolves this to a clip via the actor's anim bank (ROM: +0x1d80 bank populated when
   *  the tdc archives attach via opcode 0x0b). */
  anim: { groupSel: number; animId: number } | null;
}

/** Engine-effect boundary: the VM calls these where the ROM calls into GX/HSD/audio.
 *  The TitleIntro renderer implements this to map VM state onto three.js + Web Audio. */
export interface TitleEffectSink {
  /** Opcode 0x0b (FUN_801c8128): `zz_00412c4_(0,0)`+`zz_00412c4_(1,0)`+`zz_0042954_`+
   *  `zz_0042b20_` — preload + attach the desk scene archives (tl00_mdl.arc + tdc0X.arc). */
  attachDeskArchives(): void;
  /** Opcode 0x01 (FUN_801c7eb8): `zz_0027aac_(rgba, intensity, screenEffect)` — full-screen
   *  color/effect (fade-to-color stinger). rgba packs bytes [2],[3],[4] big-endian. */
  screenColor(rgba: number, intensity: number, screenEffect: number): void;
  /** Opcode 0x06 (FUN_801c7fc0): selectWidgetOrEffect — render-state pointer lookup into
   *  the 0x803cb470/0x803cb32c effect tables. `effectIndex` is PC[1] (0xff = default). */
  selectWidgetOrEffect(effectIndex: number): void;
  /** Opcode 0x09 (FUN_801c80ec): setCameraMode — state[0x3e]=mode; the renderer maps the
   *  mode byte to a camera cue (authored vs orbit vs menu). */
  setCameraMode(mode: number): void;
  /** Opcode 0x0c (FUN_801c8168): setAudioCue — state[0x3d]=cue; `zz_0005984_(cue)`. */
  setAudioCue(cue: number): void;
  /** Opcode 0x0d mode 0 (FUN_801c81a0 → zz_0057ff8_): start actor anim. */
  actorPlayAnim(slot: number, groupSel: number, animId: number): void;
  /** Opcode 0x0d mode 1 (FUN_801c81a0 → zz_0058044_): reset/dealloc actor. */
  actorReset(slot: number): void;
  /** Opcode 0x0d mode 2/3 (FUN_801c81a0): toggle actor+0x82 visibility byte
   *  (`actor+0x82 = actor+0x96 + 'A'` when on, else 0). */
  actorSetVisible(slot: number, visible: boolean): void;
  /** Opcode 0x0f (FUN_801c82b0): toggleOverlay — `zz_002aee0_(state+0x40)` (on) /
   *  `zz_002affc_` (off). Drives the light-bar/overlay layer + state[0x3f]/[0x48]/[0x60]. */
  toggleOverlay(on: boolean): void;
  /** Opcode 0x10 (FUN_801c8328): copyOverlayTransform — gnt4_memcpy(state+0x40,
   *  DAT_8038a550, 0x20). Loads the 32-byte overlay/widget transform seed. */
  copyOverlayTransform(): void;
  /** Opcode 0x12 (FUN_801c83b8): titleLightBar — `zz_0040d64_(0,6)`. */
  titleLightBar(): void;
  /** Opcode 0x13 (FUN_801c83e4): spawnTitleWidget — `zz_00e99c8_(...,2,0, table[id], id, PC)`. */
  spawnTitleWidget(id: number): void;
  /** Opcode 0x14 (FUN_801c8434): setTitleWidgetMode — `zz_00e9b08_(...,2,1, mode)`. */
  setTitleWidgetMode(mode: number): void;
  /** Opcode 0x15 (FUN_801c846c): playSound — `zz_00f036c_(0, cue)`. */
  playSound(cue: number): void;
}

/** The front-end global state block (port of PTR_DAT_80433934, relevant slice). Offsets
 *  preserved as comments for audit against the decompile. */
export interface TitleVmState {
  pc: number; // +0x20 — program counter (index into SCRIPT)
  borgIds: number[]; // +0x10..0x1a — 6 flat u16 (slot -> borgId, 0xffff = empty)
  inputConsumed: number; // +0x2d — set by upstream input; cleared by dispatcher after advance
  sceneStep: number; // via DAT_803d5d94 (separate global, but driven by opcode 0)
  endRequested: number; // +0x18 — set by opcode 4 (end)
  cameraMode: number; // +0x3e — set by opcode 9
  audioCue: number; // +0x3d — set by opcode 0x0c
  /** +0x30/+0x34/+0x38/+0x3c — fade current/target/step/direction. Opcode 0x07 seeds;
   *  the front-end tick (zz_01c7ba0_) integrates current toward target by step each
   *  frame while +0x3c != 0. */
  fade: { current: number; target: number; step: number; active: number };
  /** +0x3f/+0x48/+0x60/+0x64 — overlay/lightbar ramp. Opcode 0x0f toggles +0x3f;
   *  opcode 0x11 sets the rate at +0x64; the tick integrates +0x48 toward +0x60. */
  overlay: { on: number; current: number; target: number; rate: number };
  fadeTargetFrames: number; // opcode 0x08 scratch (PC[1] when !=0xff)
  waitFrameCount: number; // opcode 0x05 phase-1 latch (stored PC[1])
  actors: TitleActor[]; // port of DAT_803c4e84 (6 slots; 0/1 populated for the desk intro)
}

export interface TitleVm {
  state: TitleVmState;
  /** Run the per-frame dispatcher (port of zz_01c7de4_). Executes opcodes until a
   *  handler yields (returns 0), then returns. Call once per fixed frame. */
  tick(): void;
  /** Upstream input edge (e.g. a "press start" keydown). Sets state.inputConsumed=1,
   *  which the end/wait opcodes test. Mirrors the ROM input path writing +0x2d. */
  notifyInput(): void;
}

/** Port of `FUN_801c795c`'s descriptor-seed loop (chunk_0055.c:2253-2279): copy the 6
 *  flat u16 borg ids from DAT_8038a4ec into state.borgIds, and materialize an actor for
 *  every non-empty slot. */
function seedActors(): TitleActor[] {
  const actors: TitleActor[] = [];
  for (const d of TITLE_INTRO_ACTOR_DESCRIPTORS) {
    if (d.borgId !== null) {
      actors.push({ slot: d.slot, borgId: d.borgId, visible: false, anim: null });
    }
  }
  return actors;
}

export function createTitleVm(sink: TitleEffectSink): TitleVm {
  const state: TitleVmState = {
    pc: 0,
    borgIds: TITLE_INTRO_ACTOR_DESCRIPTORS.map((d) => d.rawBorgId),
    inputConsumed: 0,
    sceneStep: 0,
    endRequested: 0,
    cameraMode: 0,
    audioCue: 0,
    fade: { current: 0, target: 0, step: 0, active: 0 },
    overlay: { on: 0, current: 0, target: 0, rate: 0 },
    fadeTargetFrames: 0,
    waitFrameCount: 0,
    actors: seedActors(),
  };

  const actorAt = (slot: number): TitleActor | undefined => state.actors.find((a) => a.slot === slot);

  // Safe script-byte read relative to PC. SCRIPT is a fixed finite array; under
  // `noUncheckedIndexedAccess` an index can be undefined, but PC stays in-range during
  // valid execution (every opcode's payload length is accounted for in OPCODE_LENGTHS).
  const b = (offset: number): number => SCRIPT[state.pc + offset] ?? 0;
  // Read a big-endian u16 from PC+offset (opcodes 0x05/0x11/0x13/0x15 pack a short).
  const bShort = (offset: number): number => (b(offset) << 8) | b(offset + 1);
  // Safe FADE_FLOAT_TABLE lookup (noUncheckedIndexedAccess guard).
  const fft = (index: number): number => FADE_FLOAT_TABLE[index] ?? 0;

  // ===== opcode handlers (port of PTR_FUN_8038a4f8). Each returns 1 = advance PC by
  // OPCODE_LENGTHS[opcode]+1, or 0 = yield (re-run next frame). =====================

  // op 0x00 setSceneStep — FUN_801c7e64 (chunk_0055.c:2510)
  const op_setSceneStep = (): number => {
    state.sceneStep = b(1); // zz_01c7dc4_(arg)
    return 1;
  };

  // op 0x01 screenColor — FUN_801c7eb8 (chunk_0055.c:2525)
  const op_screenColor = (): number => {
    const rgba = (b(4) << 8) | (b(2) << 24) | (b(3) << 16);
    sink.screenColor(rgba, b(5), b(1));
    return 1;
  };

  // op 0x02 waitForArchive — FUN_801c7f00 (chunk_0055.c:2541). Polls zz_0027adc_();
  // returns 0 until the archive attach completes, then 1. We treat the attach as
  // synchronous (the sink loads archives before the first tick), so this always advances.
  const op_waitForArchive = (): number => 1;

  // op 0x03 clearArchiveWait — FUN_801c7f28 (chunk_0055.c:2556): zz_0027c1c_().
  const op_clearArchiveWait = (): number => 1;

  // op 0x04 end — 0x801c7f4c (decoded from PPC; not emitted as a Ghidra fn header).
  // lbz r4,[0x2d]; extsb.; bne ->return 0; addi r4,r4,1; li r0,1; stb r0,[0x2d];
  // stw r0,[0x18]; return 0. Sets the end flag once, then yields forever.
  const op_end = (): number => {
    if (state.inputConsumed === 0) {
      state.inputConsumed = 1; // stb r0,[0x2d] (r0=1)
      state.endRequested = 1; // stw r0,[0x18] (r0=1)
    }
    return 0; // li r3,0; blr — yield forever (sequence ended; waits on input upstream)
  };

  // op 0x05 waitFrames — 0x801c7f70 (decoded from PPC). Two-phase: phase 1 (inputConsumed
  // ==0) stores PC[1] to state[0x2e], sets inputConsumed=1, yields; phase 2 (==1)
  // advances. Net effect: yield exactly one frame, then continue. The stored count is
  // retained for any consumer of state[0x2e] (none observed in this script).
  const op_waitFrames = (): number => {
    if (state.inputConsumed !== 0) return 1; // bne 0x801c7fa0 -> li r3,1; blr
    state.inputConsumed = 1; // stb r0,[0x2d]
    state.waitFrameCount = bShort(1); // sth r0,[0x2e]
    return 0; // li r3,0; blr
  };

  // op 0x06 selectWidgetOrEffect — 0x801c7fc0 (decoded from PPC). lwz r4,[0x20];
  // lbz r0,1(r4); cmplwi r0,0xff; bne ->effect-table branch; else default-table lookup
  // into state[0x24]. Delegates the render-state table pick to the sink.
  const op_selectWidgetOrEffect = (): number => {
    sink.selectWidgetOrEffect(b(1));
    return 1;
  };

  // op 0x07 fade — FUN_801c7ffc (chunk_0055.c:2567). Sets fade.current=table[arg1],
  // fade.step=table[arg3], fade.active=0xff; fade.target = (arg2==0xff) ?
  // zz_0008a1c_(current) : table[arg2].
  const op_fade = (): number => {
    state.fade.current = fft(b(1));
    state.fade.step = fft(b(3));
    state.fade.active = 0xff;
    const targetArg = b(2);
    state.fade.target =
      targetArg === 0xff
        ? state.fade.current // ROM calls zz_0008a1c_(current) — a derive-from-current helper;
        : // the title script always pairs a known target, so we mirror current as the
          // honest placeholder until that helper is decoded.
          fft(targetArg);
    return 1;
  };

  // op 0x08 setFadeTarget — 0x801c809c (decoded from PPC). lwz r4,[0x20]; lbz r0,1(r4);
  // cmplwi r0,0xff; bne ->compute-rate; else bclr early. The compute-rate path mirrors
  // FUN_801c835c's (state[0x64] = (target-current)/frames). We store the raw arg; the
  // sink integrates the ramp.
  const op_setFadeTarget = (): number => {
    const arg = b(1);
    if (arg === 0xff) return 1; // early blr — no-op sentinel
    state.fadeTargetFrames = arg;
    return 1;
  };

  // op 0x09 setCameraMode — 0x801c80ec (decoded from PPC). lbz r0,1(PC); stb r0,[0x3e];
  // li r3,1; blr.
  const op_setCameraMode = (): number => {
    state.cameraMode = b(1);
    sink.setCameraMode(state.cameraMode);
    return 1;
  };

  // op 0x0a waitForCamera — FUN_801c8100 (chunk_0055.c:2600). Polls zz_000a3c4_();
  // returns 0 until the camera move completes. Synchronous in the port (advances).
  const op_waitForCamera = (): number => 1;

  // op 0x0b attachDeskArchives — FUN_801c8128 (chunk_0055.c:2615). zz_00412c4_(0,0);
  // zz_00412c4_(1,0); zz_0042954_; zz_0042b20_.
  const op_attachDeskArchives = (): number => {
    sink.attachDeskArchives();
    return 1;
  };

  // op 0x0c setAudioCue — FUN_801c8168 (chunk_0055.c:2641). state[0x3d]=PC[1];
  // zz_0005984_(arg).
  const op_setAudioCue = (): number => {
    state.audioCue = b(1);
    sink.setAudioCue(state.audioCue);
    return 1;
  };

  // op 0x0d actorControl — FUN_801c81a0 (chunk_0055.c:2653). mode=PC[1], slot=PC[2],
  // value=PC[3]. mode 0 -> zz_0057ff8_(actor, 5, animId); mode 1 -> zz_0058044_(actor);
  // mode 2/3 -> toggle actor+0x82 visibility (on if PC[2]==1).
  const op_actorControl = (): number => {
    const mode = b(1);
    const slot = b(2);
    const value = b(3);
    if (mode === 1) {
      sink.actorReset(slot);
      const actor = actorAt(slot);
      if (actor) {
        actor.visible = false;
        actor.anim = null;
      }
    } else if (mode === 0) {
      sink.actorPlayAnim(slot, 5, value); // zz_0057ff8_(actor, 5, animId)
      const actor = actorAt(slot);
      if (actor) {
        actor.visible = true;
        actor.anim = { groupSel: 5, animId: value };
      }
    } else if (mode < 3) {
      // ROM: actor[+0x82] = (PC[2]==1) ? actor[+0x96]+'A' : 0 — a render-visibility byte.
      const visible = value === 1;
      sink.actorSetVisible(slot, visible);
      const actor = actorAt(slot);
      if (actor) actor.visible = visible;
    }
    return 1;
  };

  // op 0x0e — 0x801c8278 (decoded from PPC; unused in this script — 0 hits). Skipped.
  const op_unknown0e = (): number => 1;

  // op 0x0f toggleOverlay — FUN_801c82b0 (chunk_0055.c:2685). arg=PC[1]; if arg==1:
  // zz_002aee0_(state+0x40); state[0x3f]=1; state[0x64]=state[0x60]=FLOAT_8043bce8.
  // if arg==0: zz_002affc_(); state[0x3f]=0.
  const op_toggleOverlay = (): number => {
    const on = b(1) === 1;
    sink.toggleOverlay(on);
    state.overlay.on = on ? 1 : 0;
    return 1;
  };

  // op 0x10 copyOverlayTransform — FUN_801c8328 (chunk_0055.c:2712).
  // gnt4_memcpy(state+0x40, DAT_8038a550, 0x20).
  const op_copyOverlayTransform = (): number => {
    sink.copyOverlayTransform();
    return 1;
  };

  // op 0x11 rampOverlay — FUN_801c835c (chunk_0055.c:2723). sVar1=PC[1..2] (signed short);
  // state[0x60]=FLOAT_8043bce8; state[0x64]=(state[0x60]-state[0x48]) / (sVar1 as f32).
  const op_rampOverlay = (): number => {
    const frames = bShort(1);
    const signed = frames > 0x7fff ? frames - 0x10000 : frames;
    state.overlay.target = 1.0; // FLOAT_8043bce8 probe
    state.overlay.rate = signed === 0 ? 0 : (state.overlay.target - state.overlay.current) / signed;
    return 1;
  };

  // op 0x12 titleLightBar — FUN_801c83b8 (chunk_0055.c:2742). zz_0040d64_(0,6).
  const op_titleLightBar = (): number => {
    sink.titleLightBar();
    return 1;
  };

  // op 0x13 spawnTitleWidget — FUN_801c83e4 (chunk_0055.c:2753).
  // zz_00e99c8_(...,2,0, DAT_8031a074[id]*4, id, PC). id = PC[1..2] (signed short).
  const op_spawnTitleWidget = (): number => {
    sink.spawnTitleWidget(bShort(1));
    return 1;
  };

  // op 0x14 setTitleWidgetMode — FUN_801c8434 (chunk_0055.c:2774).
  // zz_00e9b08_(...,2,1, PC[1]).
  const op_setTitleWidgetMode = (): number => {
    sink.setTitleWidgetMode(b(1));
    return 1;
  };

  // op 0x15 playSound — FUN_801c846c (chunk_0055.c:2791). zz_00f036c_(0, PC[1..2]).
  const op_playSound = (): number => {
    sink.playSound(bShort(1));
    return 1;
  };

  const handlers: ReadonlyArray<() => number> = [
    op_setSceneStep, // 0x00
    op_screenColor, // 0x01
    op_waitForArchive, // 0x02
    op_clearArchiveWait, // 0x03
    op_end, // 0x04
    op_waitFrames, // 0x05
    op_selectWidgetOrEffect, // 0x06
    op_fade, // 0x07
    op_setFadeTarget, // 0x08
    op_setCameraMode, // 0x09
    op_waitForCamera, // 0x0a
    op_attachDeskArchives, // 0x0b
    op_setAudioCue, // 0x0c
    op_actorControl, // 0x0d
    op_unknown0e, // 0x0e
    op_toggleOverlay, // 0x0f
    op_copyOverlayTransform, // 0x10
    op_rampOverlay, // 0x11
    op_titleLightBar, // 0x12
    op_spawnTitleWidget, // 0x13
    op_setTitleWidgetMode, // 0x14
    op_playSound, // 0x15
  ];

  /** Port of `zz_01c7de4_` @0x801c7de4 (chunk_0055.c:2490), followed by the per-frame
   *  fade + overlay integration from `zz_01c7ba0_` @0x801c7ba0 (chunk_0055.c:2368-2397)
   *  which also runs every frame as part of sndSeqContinue. */
  const integrate = (): void => {
    // fade: state[0x30] += state[0x38] until state[0x34] <= state[0x30]; then clamp + clear.
    if (state.fade.active !== 0) {
      state.fade.current += state.fade.step;
      if (state.fade.target <= state.fade.current) {
        state.fade.current = state.fade.target;
        state.fade.active = 0;
      }
    }
    // overlay: state[0x48] += state[0x64] (rate) toward state[0x60] (target); clamp + reset rate.
    if (state.overlay.on !== 0 && state.overlay.rate !== 0) {
      state.overlay.current += state.overlay.rate;
      if (state.overlay.target <= state.overlay.current) {
        state.overlay.current = state.overlay.target;
        state.overlay.rate = 0;
      }
    }
  };

  const tick = (): void => {
    for (;;) {
      const opcode = SCRIPT[state.pc];
      if (opcode === undefined) break;
      const handler = handlers[opcode];
      const result = handler === undefined ? 1 : handler();
      if (result === 0) break; // yield
      state.pc += (OPCODE_LENGTHS[opcode] ?? 0) + 1;
      state.inputConsumed = 0; // dispatcher clears +0x2d after every advancing step
    }
    integrate();
  };

  return {
    state,
    tick,
    notifyInput: () => {
      state.inputConsumed = 1;
    },
  };
}
