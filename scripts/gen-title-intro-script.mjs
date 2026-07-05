#!/usr/bin/env node
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync } from "node:fs";
import path from "node:path";

const BOOT_DOL_PATH = "user-data/GG4E/disc/sys/boot.dol";
const OUT_PATH = "apps/game/src/ui/titleIntroScript.generated.ts";

const DATA_SECTION_RUNTIME_BASE = 0x802bae60;
const DATA_SECTION_FILE_BASE = 0x2b7e60;

const ADDRS = {
  opcodeLengths: 0x8038a3b8,
  script: 0x8038a3ec,
  actorDescriptors: 0x8038a4ec,
  opcodeHandlers: 0x8038a4f8,
  widgetDescriptors: 0x8038a570,
};

const OPCODE_COUNT = 0x16;
const ACTOR_DESCRIPTOR_COUNT = 3;
const MAX_SCRIPT_BYTES = 512;
const MAX_WIDGET_DESCRIPTOR_BYTES = 0x100;

const OPCODE_NAMES = new Map([
  [0x00, "setSceneStep"],
  [0x01, "screenColor"],
  [0x02, "waitForArchive"],
  [0x03, "clearArchiveWait"],
  [0x04, "end"],
  [0x05, "waitFrames"],
  [0x06, "selectWidgetOrEffect"],
  [0x07, "fade"],
  [0x08, "setFadeTarget"],
  [0x09, "setCameraMode"],
  [0x0a, "waitForCamera"],
  [0x0b, "attachDeskArchives"],
  [0x0c, "setAudioCue"],
  [0x0d, "actorControl"],
  [0x0e, "unknown0e"],
  [0x0f, "toggleOverlay"],
  [0x10, "copyOverlayTransform"],
  [0x11, "rampOverlay"],
  [0x12, "titleLightBar"],
  [0x13, "spawnTitleWidget"],
  [0x14, "setTitleWidgetMode"],
  [0x15, "playSound"],
]);

const GRED_ASSET_CLIPS = new Map([
  [0, { group: 0, slot: 0, label: "idle", file: "anim_g00_s00_idle.json" }],
  [1, { group: 0, slot: 1, label: "move", file: "anim_g00_s01_move.json" }],
  [3, { group: 0, slot: 3, label: "dash_back", file: "anim_g00_s03_dash_back.json" }],
  [4, { group: 0, slot: 4, label: "dash_left", file: "anim_g00_s04_dash_left.json" }],
  [6, { group: 0, slot: 6, label: "jump_takeoff", file: "anim_g00_s06_jump_takeoff.json" }],
  [7, { group: 0, slot: 7, label: "jump_land", file: "anim_g00_s07_jump_land.json" }],
]);

function hex(value, width = 8) {
  return `0x${value.toString(16).padStart(width, "0")}`;
}

function runtimeToFileOffset(addr) {
  return DATA_SECTION_FILE_BASE + (addr - DATA_SECTION_RUNTIME_BASE);
}

function readAt(dol, addr, len) {
  const off = runtimeToFileOffset(addr);
  return dol.subarray(off, off + len);
}

function readU16(buf, off) {
  return buf.readUInt16BE(off);
}

function readI16(buf, off) {
  return buf.readInt16BE(off);
}

function readU32(buf, off) {
  return buf.readUInt32BE(off);
}

function decodeActorDescriptors(buf) {
  const descriptors = [];
  for (let slot = 0; slot < ACTOR_DESCRIPTOR_COUNT; slot += 1) {
    const off = slot * 4;
    const rawBorgId = readU16(buf, off);
    const variant = readU16(buf, off + 2);
    descriptors.push({
      slot,
      rawBorgId,
      borgId: rawBorgId === 0xffff ? null : `pl${rawBorgId.toString(16).padStart(4, "0")}`,
      variant: variant === 0xffff ? null : variant,
    });
  }
  return descriptors;
}

function decodeWidgetDescriptors(buf) {
  const descriptors = [];
  for (let off = 0; off + 5 < buf.length; off += 6) {
    const modelId = readI16(buf, off);
    const updateKind = readI16(buf, off + 2);
    const variant = readI16(buf, off + 4);
    descriptors.push({ index: descriptors.length, modelId, updateKind, variant });
    if (modelId < 0) break;
  }
  return descriptors;
}

function decodeCommands(script, opcodeLengths, opcodeHandlers) {
  const commands = [];
  const actorEvents = [];
  let offset = 0;
  let frame = 0;
  while (offset < script.length) {
    const opcode = script[offset];
    const length = opcodeLengths[opcode];
    if (opcode === undefined || length === undefined) {
      throw new Error(`Script decode hit unknown opcode at ${hex(offset, 3)}.`);
    }
    const payload = Array.from(script.subarray(offset + 1, offset + 1 + length));
    const command = {
      offset,
      frame,
      opcode,
      name: OPCODE_NAMES.get(opcode) ?? `opcode_${opcode.toString(16).padStart(2, "0")}`,
      handler: hex(opcodeHandlers[opcode] ?? 0),
      payload,
    };
    if (opcode === 0x05 && payload.length === 2) {
      command.waitFrames = (payload[0] << 8) | payload[1];
    }
    if (opcode === 0x0d && payload.length === 3) {
      const [mode, slot, value] = payload;
      command.actor = {
        mode,
        slot,
        value,
        action:
          mode === 0
            ? "startAnimation"
            : mode === 1
              ? "reset"
              : mode === 2
                ? "setPoseFlag"
                : "unknown",
      };
      if (mode === 0) {
        const asset = GRED_ASSET_CLIPS.get(value) ?? null;
        actorEvents.push({
          frame,
          offset,
          slot,
          actionGroup: 5,
          animId: value,
          assetGroup: asset?.group ?? null,
          assetSlot: asset?.slot ?? null,
          label: asset?.label ?? null,
          file: asset?.file ?? null,
        });
      }
    }
    commands.push(command);
    offset += 1 + length;
    if (command.waitFrames) frame += command.waitFrames;
    if (opcode === 0x04) break;
  }
  return { commands, actorEvents, totalFrames: frame, consumedBytes: offset };
}

function toTsConst(name, value) {
  return `export const ${name} = ${JSON.stringify(value, null, 2)} as const;\n`;
}

const dol = readFileSync(BOOT_DOL_PATH);
const bootDolSha1 = createHash("sha1").update(dol).digest("hex");
const opcodeLengths = Array.from(readAt(dol, ADDRS.opcodeLengths, OPCODE_COUNT));
const opcodeHandlersBuf = readAt(dol, ADDRS.opcodeHandlers, OPCODE_COUNT * 4);
const opcodeHandlers = Array.from({ length: OPCODE_COUNT }, (_, i) => readU32(opcodeHandlersBuf, i * 4));
const scriptBuf = readAt(dol, ADDRS.script, MAX_SCRIPT_BYTES);
const { commands, actorEvents, totalFrames, consumedBytes } = decodeCommands(scriptBuf, opcodeLengths, opcodeHandlers);
const scriptBytes = Array.from(scriptBuf.subarray(0, consumedBytes));
const actorDescriptors = decodeActorDescriptors(
  readAt(dol, ADDRS.actorDescriptors, ACTOR_DESCRIPTOR_COUNT * 4),
);
const widgetDescriptors = decodeWidgetDescriptors(readAt(dol, ADDRS.widgetDescriptors, MAX_WIDGET_DESCRIPTOR_BYTES));

const source = {
  bootDolPath: BOOT_DOL_PATH,
  bootDolSha1,
  evidence:
    "FUN_801c795c installs DAT_8038a3ec; zz_01c7de4_ dispatches via PTR_FUN_8038a4f8 and DAT_8038a3b8; FUN_801c81a0 handles opcode 0x0d actor controls.",
  addresses: Object.fromEntries(Object.entries(ADDRS).map(([key, value]) => [key, hex(value)])),
  generatedBy: path.basename(import.meta.url),
};

const out = `// Generated by scripts/gen-title-intro-script.mjs from user-data/GG4E/disc/sys/boot.dol.
// Do not hand-edit; rerun the generator after updating DOL/decomp evidence.

${toTsConst("TITLE_INTRO_SCRIPT_SOURCE", source)}
${toTsConst("TITLE_INTRO_OPCODE_LENGTHS", opcodeLengths)}
${toTsConst("TITLE_INTRO_OPCODE_HANDLERS", opcodeHandlers.map((addr) => hex(addr)))}
${toTsConst("TITLE_INTRO_SCRIPT_BYTES", scriptBytes)}
${toTsConst("TITLE_INTRO_ACTOR_DESCRIPTORS", actorDescriptors)}
${toTsConst("TITLE_INTRO_WIDGET_DESCRIPTORS", widgetDescriptors)}
${toTsConst("TITLE_INTRO_COMMANDS", commands)}
${toTsConst("TITLE_INTRO_ACTOR_EVENTS", actorEvents)}
export const TITLE_INTRO_TOTAL_FRAMES = ${totalFrames} as const;
`;

writeFileSync(OUT_PATH, out);
console.log(`wrote ${OUT_PATH} (${commands.length} commands, ${actorEvents.length} actor anim events)`);
