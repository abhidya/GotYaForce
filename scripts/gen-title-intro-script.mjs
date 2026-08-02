#!/usr/bin/env node
import { createHash } from "node:crypto";
import { readFileSync, writeFileSync } from "node:fs";
import path from "node:path";

const BOOT_DOL_PATH = "user-data/GG4E/disc/sys/boot.dol";
const OUT_PATH = "apps/game/src/ui/titleIntroScript.generated.ts";

const ADDRS = {
  opcodeLengths: 0x8038a3b8,
  script: 0x8038a3ec,
  actorDescriptors: 0x8038a4ec,
  opcodeHandlers: 0x8038a4f8,
  widgetDescriptors: 0x8038a570,
  propMotionRows: 0x8038a5b4,
  propTaskStateHandlers: 0x8038a674,
  propInitHandlers: 0x8038a684,
  propPostInitHandlers: 0x8038a690,
  propUpdateHandlers: 0x8038a69c,
  propWobbleFrames: 0x8038a6a8,
  propZero: 0x8043bcf8,
  radiansToBam: 0x8043bcfc,
  overlayInitialOpacity: 0x8043bd08,
  overlayOpacityStep: 0x8043bd0c,
  physicalMenuWidgetDescriptors: 0x8038a720,
  physicalMenuModelTriplets: 0x8038a760,
  physicalMenuAngularSteps: 0x8038a78c,
  physicalMenuTaskStateHandlers: 0x8038a79c,
  physicalMenuInitHandlers: 0x8038a7ac,
  physicalMenuUpdateHandlers: 0x8038a7b8,
  physicalMenuDrawHandlers: 0x8038a7c4,
  physicalMenuDirectionTable: 0x80301cf0,
  physicalMenuModeDispatch: 0x802cfdc4,
};

const OPCODE_COUNT = 0x16;
// DAT_8038a4ec is a FLAT array of 6 big-endian u16 borg ids (one per actor slot 0..5),
// NOT three (borgId, variant) pairs. Proven at chunk_0006.c:7055
// (Battle_SpawnActiveBorgFromSlotTables: `*(u16*)(actor+1000) = *(u16*)(global + slot*2 + 0x10)`)
// and chunk_0046.c:1176-1192 (stride-2 / 6-slot layout: offsets +0x10/+0x12/+0x14/+0x16/+0x18/+0x1a).
// The variant lives in a SEPARATE +0xa0 byte table seeded elsewhere, not here.
// Slot 0 = 0x0615 (G RED), slot 1 = 0x000a (Sasuke pl000a), slots 2..5 = 0xffff (empty).
const ACTOR_DESCRIPTOR_COUNT = 6;
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
  [0x07, "animateSelectedScene"],
  [0x08, "waitForSceneFrame"],
  [0x09, "setCameraMode"],
  [0x0a, "waitForCamera"],
  [0x0b, "attachDeskArchives"],
  [0x0c, "setSceneAuxMode"],
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
  // FUN_801c81a0 passes group selector 5. The recovered group-5 resolver maps
  // intro animation id 6 to group 0, slot 9 (not slot 6).
  [6, { group: 0, slot: 9, label: "fly_transition", file: "anim_g00_s09_fly_transition.json" }],
  [7, { group: 0, slot: 7, label: "jump_land", file: "anim_g00_s07_jump_land.json" }],
]);

const SCENE_FRAME_TABLE = [0, 1, 30, 59, 399, 729, 789];
const TDC_END_FRAME_BY_RESOURCE_SLOT = new Map([
  [12, 39], [13, 23], [14, 60], [15, 49], [16, 49],
  [17, 80], [18, 31], [19, 49], [20, 29], [21, 29],
]);

function hex(value, width = 8) {
  return `0x${value.toString(16).padStart(width, "0")}`;
}

function runtimeToFileOffset(dol, addr) {
  for (let index = 0; index < 18; index += 1) {
    const fileOffset = dol.readUInt32BE(index * 4);
    const runtimeAddress = dol.readUInt32BE(0x48 + index * 4);
    const size = dol.readUInt32BE(0x90 + index * 4);
    if (size > 0 && addr >= runtimeAddress && addr < runtimeAddress + size) {
      return fileOffset + (addr - runtimeAddress);
    }
  }
  throw new Error(`DOL address ${hex(addr)} is outside mapped sections`);
}

function readAt(dol, addr, len) {
  const off = runtimeToFileOffset(dol, addr);
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

function readF32(buf, off) {
  return buf.readFloatBE(off);
}

function decodeActorDescriptors(buf) {
  const descriptors = [];
  for (let slot = 0; slot < ACTOR_DESCRIPTOR_COUNT; slot += 1) {
    const off = slot * 2;
    const rawBorgId = readU16(buf, off);
    descriptors.push({
      slot,
      rawBorgId,
      borgId: rawBorgId === 0xffff ? null : `pl${rawBorgId.toString(16).padStart(4, "0")}`,
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

function decodePropMotionRows(buf) {
  return Array.from({ length: 8 }, (_, variant) => {
    const off = variant * 0x18;
    return {
      variant,
      waitFrames: readI16(buf, off),
      soundId: readI16(buf, off + 2),
      angularAccelerationBam: readI16(buf, off + 4),
      angularVelocityBam: readI16(buf, off + 6),
      velocity: readF32(buf, off + 8),
      acceleration: readF32(buf, off + 0x0c),
      accelerationStep: readF32(buf, off + 0x10),
      terminalVelocity: readF32(buf, off + 0x14),
    };
  });
}

function decodePointerTable(dol, address, count) {
  const buf = readAt(dol, address, count * 4);
  return Array.from({ length: count }, (_, index) => ({
    index,
    address: hex(readU32(buf, index * 4)),
  }));
}

function decodePhysicalMenuWidgetDescriptors(buf) {
  const descriptors = [];
  for (let off = 0; off + 3 < buf.length; off += 4) {
    const kind = buf.readInt8(off);
    if (kind < 0) break;
    descriptors.push({
      index: descriptors.length,
      kind,
      menuIndex: buf[off + 1],
      layer: buf[off + 2],
      priority: buf[off + 3],
    });
  }
  return descriptors;
}

function decodePhysicalMenuModelTriplets(buf) {
  return Array.from({ length: 7 }, (_, menuIndex) => {
    const off = menuIndex * 6;
    return {
      menuIndex,
      baseModelId: readU16(buf, off),
      selectionModelId: readU16(buf, off + 2),
      labelModelId: readU16(buf, off + 4),
    };
  });
}

function decodeCommands(script, opcodeLengths, opcodeHandlers) {
  const commands = [];
  let offset = 0;
  while (offset < script.length) {
    const opcode = script[offset];
    const length = opcodeLengths[opcode];
    if (opcode === undefined || length === undefined) {
      throw new Error(`Script decode hit unknown opcode at ${hex(offset, 3)}.`);
    }
    const payload = Array.from(script.subarray(offset + 1, offset + 1 + length));
    const command = {
      offset,
      frame: -1,
      opcode,
      name: OPCODE_NAMES.get(opcode) ?? `opcode_${opcode.toString(16).padStart(2, "0")}`,
      handler: hex(opcodeHandlers[opcode] ?? 0),
      payload,
    };
    if (opcode === 0x05 && payload.length === 2) {
      command.waitFrames = (payload[0] << 8) | payload[1];
    }
    if (opcode === 0x0d && payload.length === 3) {
      const [mode, operand2, operand3] = payload;
      command.actor = {
        mode,
        slot: mode === 2 ? operand3 : operand2,
        value: mode === 2 ? operand2 : operand3,
        action:
          mode === 0
            ? "startAnimation"
            : mode === 1
              ? "reset"
              : mode === 2
                ? "setPoseFlag"
                : "unknown",
      };
    }
    commands.push(command);
    offset += 1 + length;
    if (opcode === 0x04) break;
  }

  // Execute the recovered scheduler semantics so annotations include opcode 0x08's
  // COBJ-frame waits, not just opcode 0x05's explicit delays.
  let commandIndex = 0;
  let frame = 0;
  let inputConsumed = 0;
  let waitFrameCount = 0;
  let selectedResourceSlot = 0xff;
  const timeline = { current: 0, target: 0, step: 0, active: 0 };
  const integrate = () => {
    if (timeline.active === 0) return;
    if (timeline.active >= 0x80) {
      timeline.active = 1;
      return;
    }
    timeline.current += timeline.step;
    if (timeline.target <= timeline.current) {
      timeline.current = timeline.target;
      timeline.active = 0;
    }
  };

  for (; frame < 10000; frame += 1) {
    if (waitFrameCount > 0) {
      waitFrameCount -= 1;
      if (waitFrameCount > 0) {
        integrate();
        continue;
      }
    }
    let ended = false;
    for (;;) {
      const command = commands[commandIndex];
      if (!command) {
        ended = true;
        break;
      }
      if (command.frame < 0) command.frame = frame;
      const p = command.payload;
      let advance = true;
      switch (command.opcode) {
        case 0x04:
          ended = true;
          advance = false;
          break;
        case 0x05:
          if (inputConsumed === 0) {
            inputConsumed = 1;
            waitFrameCount = (p[0] << 8) | p[1];
            advance = false;
          }
          break;
        case 0x06:
          selectedResourceSlot = p[0];
          break;
        case 0x07:
          timeline.current = SCENE_FRAME_TABLE[p[0]] ?? 0;
          timeline.target = p[1] === 0xff
            ? (TDC_END_FRAME_BY_RESOURCE_SLOT.get(selectedResourceSlot) ?? 0)
            : (SCENE_FRAME_TABLE[p[1]] ?? 0);
          timeline.step = SCENE_FRAME_TABLE[p[2]] ?? 0;
          timeline.active = 0xff;
          break;
        case 0x08:
          advance = p[0] === 0xff
            ? timeline.active === 0
            : timeline.current === (SCENE_FRAME_TABLE[p[0]] ?? 0);
          break;
      }
      if (!advance) break;
      commandIndex += 1;
      inputConsumed = 0;
    }
    integrate();
    if (ended) break;
  }

  const actorEvents = commands.flatMap((command) => {
    if (command.opcode !== 0x0d || command.actor?.mode !== 0) return [];
    const [, slot, animId] = command.payload;
    const asset = GRED_ASSET_CLIPS.get(animId) ?? null;
    return [{
      frame: command.frame,
      offset: command.offset,
      slot,
      actionGroup: 5,
      animId,
      assetGroup: asset?.group ?? null,
      assetSlot: asset?.slot ?? null,
      label: asset?.label ?? null,
      file: asset?.file ?? null,
    }];
  });
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
  readAt(dol, ADDRS.actorDescriptors, ACTOR_DESCRIPTOR_COUNT * 2),
);
const widgetDescriptors = decodeWidgetDescriptors(readAt(dol, ADDRS.widgetDescriptors, MAX_WIDGET_DESCRIPTOR_BYTES));
const propMotionRows = decodePropMotionRows(readAt(dol, ADDRS.propMotionRows, 8 * 0x18));
const propDispatch = {
  taskState: decodePointerTable(dol, ADDRS.propTaskStateHandlers, 4),
  initByKind: decodePointerTable(dol, ADDRS.propInitHandlers, 3),
  postInitByKind: decodePointerTable(dol, ADDRS.propPostInitHandlers, 3),
  updateByKind: decodePointerTable(dol, ADDRS.propUpdateHandlers, 3),
};
const propWobbleBuf = readAt(dol, ADDRS.propWobbleFrames, 8 * 4);
const propWobbleFrames = Array.from({ length: 8 }, (_, index) => readF32(propWobbleBuf, index * 4));
const propScalarConstants = {
  zero: readF32(readAt(dol, ADDRS.propZero, 4), 0),
  radiansToBam: readF32(readAt(dol, ADDRS.radiansToBam, 4), 0),
  overlayInitialOpacity: readF32(readAt(dol, ADDRS.overlayInitialOpacity, 4), 0),
  overlayOpacityStep: readF32(readAt(dol, ADDRS.overlayOpacityStep, 4), 0),
};
const physicalMenuWidgetDescriptors = decodePhysicalMenuWidgetDescriptors(
  readAt(dol, ADDRS.physicalMenuWidgetDescriptors, 0x80),
);
const physicalMenuModelTriplets = decodePhysicalMenuModelTriplets(
  readAt(dol, ADDRS.physicalMenuModelTriplets, 7 * 6),
);
const physicalMenuAngularBuf = readAt(dol, ADDRS.physicalMenuAngularSteps, 7 * 2);
const physicalMenuAngularSteps = Array.from({ length: 7 }, (_, menuIndex) => ({
  menuIndex,
  bamStep: readI16(physicalMenuAngularBuf, menuIndex * 2),
}));
const physicalMenuHandlers = {
  taskState: decodePointerTable(dol, ADDRS.physicalMenuTaskStateHandlers, 4),
  initByKind: decodePointerTable(dol, ADDRS.physicalMenuInitHandlers, 3),
  updateByKind: decodePointerTable(dol, ADDRS.physicalMenuUpdateHandlers, 3),
  drawByKind: decodePointerTable(dol, ADDRS.physicalMenuDrawHandlers, 3),
};
const physicalMenuDirectionBuf = readAt(dol, ADDRS.physicalMenuDirectionTable, 7 * 4);
const physicalMenuDirectionTable = Array.from({ length: 7 }, (_, menuIndex) => ({
  menuIndex,
  up: physicalMenuDirectionBuf[menuIndex * 4],
  down: physicalMenuDirectionBuf[menuIndex * 4 + 1],
  left: physicalMenuDirectionBuf[menuIndex * 4 + 2],
  right: physicalMenuDirectionBuf[menuIndex * 4 + 3],
}));
const physicalMenuModeDispatch = decodePointerTable(dol, ADDRS.physicalMenuModeDispatch, 7);

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
${toTsConst("TITLE_INTRO_PROP_MOTION_ROWS", propMotionRows)}
${toTsConst("TITLE_INTRO_PROP_DISPATCH", propDispatch)}
${toTsConst("TITLE_INTRO_PROP_WOBBLE_FRAMES", propWobbleFrames)}
${toTsConst("TITLE_INTRO_PROP_SCALAR_CONSTANTS", propScalarConstants)}
${toTsConst("PHYSICAL_MENU_WIDGET_DESCRIPTORS", physicalMenuWidgetDescriptors)}
${toTsConst("PHYSICAL_MENU_MODEL_TRIPLETS", physicalMenuModelTriplets)}
${toTsConst("PHYSICAL_MENU_ANGULAR_STEPS", physicalMenuAngularSteps)}
${toTsConst("PHYSICAL_MENU_HANDLERS", physicalMenuHandlers)}
export const PHYSICAL_MENU_CURSOR_MODEL_ID = 0x38 as const;
${toTsConst("PHYSICAL_MENU_DIRECTION_TABLE", physicalMenuDirectionTable)}
${toTsConst("PHYSICAL_MENU_MODE_DISPATCH", physicalMenuModeDispatch)}
${toTsConst("TITLE_INTRO_COMMANDS", commands)}
${toTsConst("TITLE_INTRO_ACTOR_EVENTS", actorEvents)}
export const TITLE_INTRO_TOTAL_FRAMES = ${totalFrames} as const;
`;

writeFileSync(OUT_PATH, out);
console.log(`wrote ${OUT_PATH} (${commands.length} commands, ${actorEvents.length} actor anim events)`);
