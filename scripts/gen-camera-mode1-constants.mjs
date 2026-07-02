#!/usr/bin/env node
// Generate ROM-confirmed constants for the battle camera mode-1 follow blend.
//
// Source:
//   user-data/GG4E/disc/sys/boot.dol
//   research/decomp/ghidra-export/chunk_0001.c
//     - zz_000bda4_  @ 0x8000bda4 (per-frame camera loop)
//     - FUN_8000c660 @ 0x8000c660 (mode-0 init: places eye behind actor heading)
//     - FUN_8000c918 @ 0x8000c918 (mode-1: dispatch via sub-table 0x802c3894[actor+0x3f1])
//     - FUN_8000cb8c @ 0x8000cb8c (mode-1 sub 1: state machine over camera+0x2e6)
//     - FUN_8000cdc0 @ 0x8000cdc0 (mode-1 state 2: no-lock follow — primary gameplay goal-eye)
//     - FUN_8000cf28 @ 0x8000cf28 (mode-1 state 3: lock-on follow)
//     - FUN_8000fc2c @ 0x8000fc2c (shared interest + distance-clamp update)
//     - FUN_8000c988 @ 0x8000c988 (mode-2: approach/orbit — distance decay to floor)
//
// Runtime consumes these through apps/game/src/sim/camera.ts.

import { createHash } from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const bootDolRel = "user-data/GG4E/disc/sys/boot.dol";
const decompRel = "research/decomp/ghidra-export/chunk_0001.c";
const outRel = "apps/game/src/sim/camera.generated.ts";

const symbols = {
  FLOAT_80436ac4: { address: 0x80436ac4, role: "half blend used by camera interest-height updates" },
  FLOAT_80436acc: {
    address: 0x80436acc,
    role: "mode-1 previous eye XZ weight; also mode-2 eye-Y rise per frame (FUN_8000c988)",
  },
  FLOAT_80436ad8: { address: 0x80436ad8, role: "degenerate trail-direction epsilon (FUN_800452e4 callers)" },
  FLOAT_80436adc: {
    address: 0x80436adc,
    role: "mode-1 eye-Y blend denominator (FUN_8000cdc0); also mode-2 height-cap multiplier",
  },
  FLOAT_80436ae0: { address: 0x80436ae0, role: "mode-2 approach minimum camera distance (FUN_8000c988)" },
  FLOAT_80436ae4: { address: 0x80436ae4, role: "mode-2 approach distance decay multiplier (FUN_8000c988)" },
  FLOAT_80436ae8: { address: 0x80436ae8, role: "mode-1 eye XZ blend denominator" },
  FLOAT_80436af0: { address: 0x80436af0, role: "mode-1 previous eye-Y weight (FUN_8000cdc0)" },
};

function sha1(buffer) {
  return createHash("sha1").update(buffer).digest("hex");
}

function readDolSections(buffer) {
  const sections = [];
  for (let i = 0; i < 18; i += 1) {
    const fileOffset = buffer.readUInt32BE(i * 4);
    const address = buffer.readUInt32BE(0x48 + i * 4);
    const size = buffer.readUInt32BE(0x90 + i * 4);
    if (fileOffset !== 0 && address !== 0 && size !== 0) {
      sections.push({ index: i, fileOffset, address, size });
    }
  }
  return sections;
}

function fileOffsetForAddress(sections, address) {
  const section = sections.find((entry) => address >= entry.address && address < entry.address + entry.size);
  if (!section) throw new Error(`address 0x${address.toString(16)} is outside DOL sections`);
  return section.fileOffset + (address - section.address);
}

function readFloatAt(buffer, sections, address) {
  return buffer.readFloatBE(fileOffsetForAddress(sections, address));
}

function renderConstObject(entries) {
  return `{\n${entries
    .map(
      ([name, entry]) =>
        `  ${name}: { address: ${JSON.stringify(entry.addressHex)}, value: ${JSON.stringify(entry.value)}, role: ${JSON.stringify(entry.role)} },`,
    )
    .join("\n")}\n}`;
}

const bootDolPath = path.join(repoRoot, bootDolRel);
const decompPath = path.join(repoRoot, decompRel);
const bootDol = fs.readFileSync(bootDolPath);
const decomp = fs.readFileSync(decompPath, "utf8");
const sections = readDolSections(bootDol);

const constants = Object.fromEntries(
  Object.entries(symbols).map(([name, entry]) => [
    name,
    {
      ...entry,
      addressHex: `0x${entry.address.toString(16)}`,
      value: readFloatAt(bootDol, sections, entry.address),
    },
  ]),
);

for (const marker of [
  "==== 8000c988  FUN_8000c988 ====",
  "==== 8000cb8c  FUN_8000cb8c ====",
  "==== 8000cdc0  FUN_8000cdc0 ====",
  "==== 8000fc2c  FUN_8000fc2c ====",
]) {
  if (!decomp.includes(marker)) throw new Error(`decomp source no longer contains ${marker}`);
}
if (!decomp.includes("FLOAT_80436acc * *(float *)(param_1 + 0x2f4)") || !decomp.includes("FLOAT_80436ae8")) {
  throw new Error("decomp source no longer contains the expected mode-2 blend formula");
}
// FUN_8000cdc0 eye-Y blend: (FLOAT_80436af0 * prevY + (dist * tan(pitch) + interestY)) / FLOAT_80436adc.
if (!decomp.includes("(fVar3 * *(float *)(param_1 + 0x31c) +")) {
  throw new Error("decomp source no longer contains the FUN_8000cdc0 eye-Y blend");
}
// FUN_8000c988 per-frame yaw step: rotate camera+0x33c around Y by 0x200 BAM.
if (!decomp.includes("zz_00453fc_('y',(float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c),0x200);")) {
  throw new Error("decomp source no longer contains the FUN_8000c988 0x200 yaw step");
}

const previousWeight = constants.FLOAT_80436acc.value;
const denominator = constants.FLOAT_80436ae8.value;
if (previousWeight + 1 !== denominator) {
  throw new Error(`unexpected camera blend constants: previous=${previousWeight}, denominator=${denominator}`);
}
const previousWeightY = constants.FLOAT_80436af0.value;
const denominatorY = constants.FLOAT_80436adc.value;
if (previousWeightY + 1 !== denominatorY) {
  throw new Error(`unexpected camera eye-Y blend constants: previous=${previousWeightY}, denominator=${denominatorY}`);
}
if (constants.FLOAT_80436ac4.value !== 0.5) {
  throw new Error(`unexpected camera half constant: ${constants.FLOAT_80436ac4.value}`);
}
if (constants.FLOAT_80436ae0.value <= 0 || constants.FLOAT_80436ae4.value <= 0 || constants.FLOAT_80436ae4.value >= 1) {
  throw new Error("unexpected mode-2 distance clamp/decay constants");
}

// Instruction-immediate (not a DOL float): FUN_8000c988 rotates the trail direction by 0x200
// BAM16 per frame around Y. Guarded by the decomp assertion above.
const mode2YawStepBam = 0x200;

const source = `// Generated by scripts/gen-camera-mode1-constants.mjs.
// Source: ${bootDolRel}; ${decompRel}
// Do not hand-edit; rerun the generator after updating decomp/DOL evidence.

export const CAMERA_MODE1_SOURCE = {
  bootDolPath: ${JSON.stringify(bootDolRel)},
  bootDolSha1: ${JSON.stringify(sha1(bootDol))},
  decompPath: ${JSON.stringify(decompRel)},
  decompSha1: ${JSON.stringify(sha1(decomp))},
  functions: [
    { address: "0x8000bda4", name: "zz_000bda4_" },
    { address: "0x8000c660", name: "FUN_8000c660" },
    { address: "0x8000c918", name: "FUN_8000c918" },
    { address: "0x8000cb8c", name: "FUN_8000cb8c" },
    { address: "0x8000cdc0", name: "FUN_8000cdc0" },
    { address: "0x8000cf28", name: "FUN_8000cf28" },
    { address: "0x8000fc2c", name: "FUN_8000fc2c" },
    { address: "0x8000c988", name: "FUN_8000c988" },
  ],
  description:
    "ROM-confirmed constants for the mode-1 battle-camera goal-eye and the mode-2 approach camera.",
} as const;

export const CAMERA_MODE1_ROM_CONSTANTS = ${renderConstObject(Object.entries(constants))} as const;

/** FLOAT_80436acc: mode-1 XZ blend, eye = (prevEye * 4 + desired) / 5 (FUN_8000cdc0/FUN_8000c988). */
export const CAMERA_MODE1_PREVIOUS_EYE_WEIGHT = ${JSON.stringify(previousWeight)};

/** FLOAT_80436ae8: denominator for the mode-1 previous-eye XZ blend. */
export const CAMERA_MODE1_EYE_BLEND_DENOMINATOR = ${JSON.stringify(denominator)};

/** FLOAT_80436af0: mode-1 eye-Y blend, eyeY = (prevY * 9 + desiredY) / 10 (FUN_8000cdc0). */
export const CAMERA_MODE1_PREVIOUS_EYE_Y_WEIGHT = ${JSON.stringify(previousWeightY)};

/** FLOAT_80436adc: denominator for the mode-1 previous-eye-Y blend. */
export const CAMERA_MODE1_EYE_Y_BLEND_DENOMINATOR = ${JSON.stringify(denominatorY)};

/** FLOAT_80436ac4, used by mode-1 interest-height blend paths (FUN_8000fc2c). */
export const CAMERA_MODE1_HALF_BLEND = ${JSON.stringify(constants.FLOAT_80436ac4.value)};

/** FLOAT_80436ad8: if the trail direction collapses below this epsilon, FUN_800452e4 rebuilds
 * it from a BAM16 heading as (sin, 0, cos). Used by FUN_8000cdc0/FUN_8000c988/FUN_800101c8. */
export const CAMERA_MODE1_TRAIL_EPSILON = ${JSON.stringify(constants.FLOAT_80436ad8.value)};

/** FLOAT_80436ae0, minimum camera distance floor of the mode-2 approach (FUN_8000c988). */
export const CAMERA_MODE1_MIN_DISTANCE = ${JSON.stringify(constants.FLOAT_80436ae0.value)};

/** FLOAT_80436ae4, mode-2 approach per-frame distance decay multiplier (FUN_8000c988). */
export const CAMERA_MODE1_DISTANCE_DECAY = ${JSON.stringify(constants.FLOAT_80436ae4.value)};

/** FUN_8000c988 instruction immediate: per-frame yaw step (BAM16) applied to the trail
 * direction via zz_00453fc_('y', dir, dir, 0x200). */
export const CAMERA_MODE2_YAW_STEP_BAM = ${JSON.stringify(mode2YawStepBam)};

/** FLOAT_80436acc reused as an addend in FUN_8000c988: the tracked eye-Y rises this many
 * world units per frame until it reaches its cap. */
export const CAMERA_MODE2_EYE_RISE_PER_FRAME = ${JSON.stringify(previousWeight)};
`;

const outPath = path.join(repoRoot, outRel);
fs.mkdirSync(path.dirname(outPath), { recursive: true });
fs.writeFileSync(outPath, source);
console.log(`wrote ${outRel}; mode1 eye blend previous ${previousWeight}/${denominator}`);
