// cueResolver — ROM-faithful 1:1 port of the GG4E audio cue→sound resolution.
//
// This closes the audio bridge gap: the ROM's onPlayCue / playSound entry points had no
// shared resolver, so apps/game hand-maintained TITLE_SOUND_IDS and COMBAT_SFX. Here the
// cue→sound mapping is driven straight from boot.dol evidence, not a hand-tuned table:
//
//   zz_00f036c_(actor, cueId)                    @ chunk_0026.c:792 (0x800f036c)
//     // The cue id passed to playSound IS the soundId — no intermediate lookup table.
//     actor == 0 → zz_00efb3c_(cueId, 0, 0x7f, 0x40, 0x2000)   // fixed pan/vol (title/UI)
//     actor != 0 → zz_00f04b4_(cueId, actorPos, actor+0x96)    // position-panned (combat)
//                   └─ ends in the SAME zz_00efb3c_ call with the SAME soundId
//   zz_00efb3c_(soundId, ...)                    @ chunk_0026.c:435 (0x800efb3c)
//     if (soundId < 0x180)                       // ← guard: drop everything else silently
//       zz_00f0f84_(bank = soundId >> 7,
//                   sample = soundId & 0x7f, ...) // routed via DAT_802d0bec[bank]
//
// So the resolution is ARITHMETIC, not table-driven: bank = soundId >> 7, sample =
// soundId & 0x7f. The only DOL-resident table in this path is the bank-routing table
// DAT_802d0bec (dumped by scripts/gen-cue-resolver-table.mjs into the generated module
// below). The asset-side manifest idScheme is `se_<soundId 3-hex-lowercase>`
// (apps/game/public/audio/se/manifest.json), which resolveCue emits verbatim.
//
// The actor-panned branch changes only mixer params (pan/volume derived from the actor's
// position +0x20 and the +0x96 byte); the resolved sample is identical, so resolveCue
// returns the same key regardless of which branch the caller came through.

import type { AudioManifest } from "./index.js";
import {
  CUE_BANK_TABLE,
  CUE_BANK_SHIFT,
  CUE_BATTLE_BANK_COUNT,
  CUE_MAX_SOUND_ID,
  CUE_SAMPLE_MASK,
} from "./cueResolverTable.generated.js";

/** A manifest play key, e.g. "se_17c" (idScheme: `se_<soundId 3-hex-lowercase>`). */
export type PlayKey = string;

/** The soundId decomposition produced by zz_00efb3c_ @ chunk_0026.c:442-443. */
export interface SoundIdParts {
  readonly bank: number;
  readonly sample: number;
}

/** A DAT_802d0bec bank-routing row: the {tsb,chd,dpk} AFS member triple the dispatcher
 *  hands to zz_00f0f84_ for a given bank. */
export interface BankRoute {
  readonly bank: number;
  readonly soundbank: string;
  readonly tsb: number;
  readonly chd: number;
  readonly dpk: number;
}

/** The playSound guard ceiling from zz_00efb3c_ (`soundId < 0x180`). soundIds at or above
 *  this are silently dropped by the ROM — resolveCue returns null for them. */
export const MAX_SOUND_ID: number = CUE_MAX_SOUND_ID;
/** bank select shift: `bank = soundId >> CUE_BANK_SHIFT` (zz_00efb3c_). */
export const BANK_SHIFT: number = CUE_BANK_SHIFT;
/** sample select mask: `sample = soundId & CUE_SAMPLE_MASK` (zz_00efb3c_). */
export const SAMPLE_MASK: number = CUE_SAMPLE_MASK;
/** Number of battle/title soundbanks reachable via playSound (banks 0..2). Bank 3
 *  (snd_com04, the menu bank) is only attached via zz_0043390_'s param_9!=0 branch and is
 *  never dispatched by the playSound path. */
export const BATTLE_BANK_COUNT: number = CUE_BATTLE_BANK_COUNT;

/** Decompose a soundId into (bank, sample) exactly as zz_00efb3c_ does at
 *  chunk_0026.c:442-443 (bank = soundId >> 7, sample = soundId & 0x7f). Performs no
 *  range validation; use resolveCue for the guarded, host-facing resolution. */
export function decomposeSoundId(soundId: number): SoundIdParts {
  return { bank: soundId >>> CUE_BANK_SHIFT, sample: soundId & CUE_SAMPLE_MASK };
}

/** Look up the DOL bank-routing entry (DAT_802d0bec[bank]) for a bank index, or null
 *  when the bank is outside the dumped table. */
export function bankRoute(bank: number): BankRoute | null {
  const entry = CUE_BANK_TABLE[bank];
  if (!entry) return null;
  const { soundbank, tsb, chd, dpk } = entry;
  return { bank, soundbank, tsb, chd, dpk };
}

/** Format a soundId as the manifest play key (`se_<soundId 3-hex-lowercase>`). No range
 *  check; the caller is expected to have passed the ROM guard. */
function formatPlayKey(soundId: number): PlayKey {
  return `se_${soundId.toString(16).padStart(3, "0")}`;
}

/** 1:1 port of the resolution half of `zz_00f036c_(actor, cueId)` → `zz_00efb3c_(cueId)`.
 *  The cueId passed to playSound IS the soundId; this returns the manifest play key for
 *  any cueId that passes the ROM guard (`0 <= cueId < 0x180`), or null when the guard
 *  drops it (matching the hardware's silent drop — no throw, no log).
 *
 *  NOTE: this returns the key the ROM *would* play. Whether the host has an exported OGG
 *  for it is a separate (asset) concern — see resolveCueToAsset. */
export function resolveCue(cueId: number): PlayKey | null {
  if (!Number.isInteger(cueId) || cueId < 0 || cueId >= CUE_MAX_SOUND_ID) return null;
  return formatPlayKey(cueId);
}

/** resolveCue intersected with the available manifest keys. Returns null when the ROM
 *  guard rejects the cue OR the resolved sample has not been exported to the asset
 *  manifest yet (honest partial port: the ROM would still play the TSB entry, but the
 *  host has no OGG for it, so the cue is skipped). `availableKeys` is the set of manifest
 *  `key` values (build it once via collectManifestPlayKeys). */
export function resolveCueToAsset(cueId: number, availableKeys: ReadonlySet<string>): PlayKey | null {
  const key = resolveCue(cueId);
  if (key === null) return null;
  return availableKeys.has(key) ? key : null;
}

/** Collect every `key` the audio manager would accept for sfx/voice playback. This is the
 *  set resolveCueToAsset checks against. Built from `GotchaAudioManager.manifest.files`
 *  (the public manifest) — each entry's primary `key` is the `se_*` id the resolver emits.
 *  Pass the result to resolveCueToAsset; rebuild after a manifest refresh. */
export function collectManifestPlayKeys(manifest: AudioManifest): Set<string> {
  const keys = new Set<string>();
  for (const entry of manifest.files) {
    if (entry.type === "sfx" || entry.type === "voice") {
      keys.add(entry.key);
    }
  }
  return keys;
}

// ============================================================================
// Self-tests — mirrors the `runXxxSelfTests(assert)` convention from packages/combat.
// Covers: title cues (the ones TITLE_SOUND_IDS maps), combat cues (COMBAT_SFX se_* keys),
// the soundId decomposition, the bank-routing table, the guard boundary, and the
// asset-availability intersection. availableKeys mirrors apps/game/public/audio/se/
// manifest.json's exported `se_*` keys (a representative spread, not the full file).
// ============================================================================
export function runCueResolverSelfTests(assert: (cond: boolean, msg: string) => void): void {
  // Representative exported-keys set mirroring apps/game/public/audio/se/manifest.json.
  // (Title: se_17a/17b/17c; combat: se_003/008/010/01e/025/0dd/0f2; etc.)
  const availableKeys = new Set<string>([
    "se_003", "se_005", "se_008", "se_009", "se_00a", "se_00b", "se_00c", "se_00f",
    "se_010", "se_012", "se_013", "se_01e", "se_020", "se_024", "se_025", "se_026",
    "se_067", "se_06a", "se_09b", "se_0ac", "se_0dd", "se_0e6", "se_0f2",
    "se_17a", "se_17b", "se_17c",
  ]);

  // --- Title cues (titleVm.ts opcode 0x15 → zz_00f036c_(0, cue); TITLE_SOUND_IDS). ---
  assert(resolveCue(0x017a) === "se_17a", "title cue 0x017a → se_17a (screw-settle impact)");
  assert(resolveCue(0x017b) === "se_17b", "title cue 0x017b → se_17b (nut/washer drop)");
  assert(resolveCue(0x017c) === "se_17c", "title cue 0x017c → se_17c (title reveal stinger)");
  assert(resolveCueToAsset(0x017c, availableKeys) === "se_17c", "title stinger is in the manifest");

  // --- Combat cues (COMBAT_SFX se_* DERIVED keys). ---
  assert(resolveCue(0x008) === "se_008", "combat cue 0x008 → se_008 (shoot/projectile launch)");
  assert(resolveCue(0x010) === "se_010", "combat cue 0x010 → se_010 (knockback crash, light)");
  assert(resolveCue(0x01e) === "se_01e", "combat cue 0x01e → se_01e (landing/footfall)");
  assert(resolveCue(0x025) === "se_025", "combat cue 0x025 → se_025 (jump launch)");
  assert(resolveCue(0x0dd) === "se_0dd", "combat cue 0x0dd → se_0dd (knockdown thud)");
  assert(resolveCue(0x0f2) === "se_0f2", "combat cue 0x0f2 → se_0f2 (dash/boost/warp)");

  // --- soundId decomposition (zz_00efb3c_ bank/sample split). ---
  assert(decomposeSoundId(0x17c).bank === 2 && decomposeSoundId(0x17c).sample === 0x7c,
    "0x17c decomposes to bank 2, sample 0x7c (snd_com03 #124)");
  assert(decomposeSoundId(0x0f2).bank === 1 && decomposeSoundId(0x0f2).sample === 0x72,
    "0x0f2 decomposes to bank 1, sample 0x72 (snd_com02 #114)");
  assert(decomposeSoundId(0x008).bank === 0 && decomposeSoundId(0x008).sample === 0x08,
    "0x008 decomposes to bank 0, sample 0x08 (snd_com01 #8)");
  assert(decomposeSoundId(0x17f).bank === 2 && decomposeSoundId(0x17f).sample === 0x7f,
    "0x17f (max valid) decomposes to bank 2, sample 0x7f");

  // --- Bank-routing table (DAT_802d0bec dump). ---
  const b0 = bankRoute(0);
  assert(b0 !== null && b0.soundbank === "snd_com01" && b0.tsb === 2839 && b0.chd === 2840 && b0.dpk === 2841,
    "bank 0 routes to snd_com01 {tsb 2839, chd 2840, dpk 2841}");
  const b2 = bankRoute(2);
  assert(b2 !== null && b2.soundbank === "snd_com03" && b2.tsb === 2845 && b2.chd === 2846 && b2.dpk === 2847,
    "bank 2 routes to snd_com03 (title/battle SE bank)");
  const b3 = bankRoute(3);
  assert(b3 !== null && b3.soundbank === "snd_com04", "bank 3 is the menu bank snd_com04 (not reachable via playSound)");
  assert(bankRoute(99) === null, "an out-of-range bank index does not resolve");

  // --- Guard boundary (zz_00efb3c_: soundId < 0x180). ---
  assert(resolveCue(0x17f) === "se_17f", "0x17f is the highest accepted soundId (< 0x180)");
  assert(resolveCue(0x180) === null, "0x180 is dropped by the guard (== ceiling)");
  assert(resolveCue(0x200) === null, "0x200 is dropped by the guard (>= 0x180)");
  assert(resolveCue(0xffff) === null, "a max u16 cue (0xffff) is dropped by the guard");
  assert(resolveCue(-1) === null, "a negative cue is dropped");
  assert(resolveCue(1.5) === null, "a non-integer cue is dropped");

  // --- Asset-availability intersection (honest partial port). ---
  assert(resolveCue(0x001) === "se_001", "0x001 resolves to a key (ROM would play TSB #1)");
  assert(resolveCueToAsset(0x001, availableKeys) === null, "0x001 has no exported OGG → skipped");
  assert(resolveCueToAsset(0x100, availableKeys) === null,
    "0x100 (guard-break, TSB-muted sample 0 in bank 2) is not exported → skipped");
  assert(resolveCueToAsset(0x0f2, availableKeys) === "se_0f2", "0x0f2 is exported → resolved");
  assert(resolveCueToAsset(0x180, availableKeys) === null, "guard-rejected cue is null even with a populated manifest");

  // --- collectManifestPlayKeys (sfx/voice keys only, mirrors GotchaAudioManager). ---
  const sampleManifest = {
    files: [
      { key: "se_17c", type: "sfx" as const, path: "audio/se/se_17c.ogg" },
      { key: "se_0f2", type: "sfx" as const, path: "audio/se/se_0f2.ogg" },
      { key: "bgm00", type: "bgm" as const, path: "audio/bgm/bgm00.ogg" },
      { key: "vo01", type: "voice" as const, path: "audio/vo/vo01.ogg" },
    ],
  };
  const collected = collectManifestPlayKeys(sampleManifest);
  assert(collected.size === 3 && collected.has("se_17c") && collected.has("se_0f2") && collected.has("vo01") && !collected.has("bgm00"),
    "collectManifestPlayKeys gathers sfx+voice keys, excludes bgm");
  assert(resolveCueToAsset(0x17c, collected) === "se_17c", "resolver + collected set resolves a present cue");

  // --- Consonance with the existing hand-tuned maps (which this replaces). ---
  // Every TITLE_SOUND_IDS entry must resolve to the same key resolveCue produces.
  const titleMap: Readonly<Record<number, string>> = { 0x017a: "se_17a", 0x017b: "se_17b", 0x017c: "se_17c" };
  for (const [cue, expected] of Object.entries(titleMap)) {
    assert(resolveCue(Number(cue)) === expected, `resolveCue matches TITLE_SOUND_IDS for ${cue}`);
  }
}
