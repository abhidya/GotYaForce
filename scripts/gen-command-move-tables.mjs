#!/usr/bin/env node
// Generate the ROM command/action tables consumed at actor+0x4ec.
//
// Source chain:
// - constructor dispatch: chunk_0007.c:412-416, PTR_PTR_802d3224[family][variant]
// - final command lookup: chunk_0009.c:456-599 and 605-679
// - per-constructor +0x4ec/+0x4b0 writes: chunks listed in COMMAND_TABLE_SOURCES below
// - anonymous constructors that copy command pointer vectors from the DOL into actor+0x4b4..0x4f0

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const bootDolPath = path.join(repoRoot, "user-data/GG4E/disc/sys/boot.dol");
const borgsPath = path.join(repoRoot, "packages/assets/data/borgs.json");
const outPath = path.join(repoRoot, "packages/combat/src/data/commandMoveTables.json");

const CONSTRUCTOR_TABLE = 0x802d3224;
const COMMAND_MODE_OFFSET = 0xb8;
const COMMAND_TYPE_COUNT = 8;
const COMMAND_SUBTYPE_COUNT = 6;
const DIRECTION_COUNT = 4;
const RECORD_SIZE = 4;
const ACTOR_COMMAND_STRUCT_OFFSET = 0x4b0;
const ACTOR_COMMAND_POINTER_OFFSET = 0x4ec;
const CONSTRUCTOR_SCAN_BYTES = 0x300;

const COMMAND_TABLE_SOURCES = [
  {
    id: "ctor_80072048",
    name: "family 01 base command table",
    constructorAddress: 0x80072048,
    pointerLabelAddress: 0x802d42b8,
    commandStructAddress: 0x802d4478,
    evidence: "research/decomp/ghidra-export/chunk_0010.c:131-134",
  },
  {
    id: "ctor_80105144",
    name: "constructor 80105144 command table",
    constructorAddress: 0x80105144,
    pointerLabelAddress: 0x80321f70,
    commandStructAddress: 0x80321c88,
    evidence: "research/decomp/ghidra-export/chunk_0029.c:589-592",
  },
  {
    id: "ctor_80106e3c",
    name: "constructor 80106e3c command table",
    constructorAddress: 0x80106e3c,
    pointerLabelAddress: 0x80322e80,
    commandStructAddress: 0x80322f40,
    evidence: "research/decomp/ghidra-export/chunk_0029.c:1927-1930",
  },
  {
    id: "ctor_801223c0",
    name: "samurai family command table",
    constructorAddress: 0x801223c0,
    pointerLabelAddress: 0x8032c760,
    commandStructAddress: 0x8032d2a8,
    evidence: "research/decomp/ghidra-export/chunk_0033.c:958-961",
  },
  {
    id: "ctor_801223c0_alt_70c_70d",
    name: "samurai family 0x70c/0x70d command table",
    constructorAddress: 0x801223c0,
    pointerLabelAddress: 0x8032c760,
    commandStructAddress: 0x8032d3c0,
    appliesToIds: ["pl070c", "pl070d"],
    evidence: "research/decomp/ghidra-export/chunk_0033.c:970-977",
  },
  {
    id: "ctor_8018ccfc",
    name: "G RED / NEO G RED command table",
    constructorAddress: 0x8018ccfc,
    pointerLabelAddress: 0x80365570,
    commandStructAddress: 0x80365ac8,
    evidence: "research/decomp/ghidra-export/chunk_0046.c:4804-4807",
  },
  {
    id: "ctor_8018ccfc_gblack",
    name: "G BLACK command table",
    constructorAddress: 0x8018ccfc,
    pointerLabelAddress: 0x80365570,
    commandStructAddress: 0x80365be0,
    appliesToIds: ["pl062a"],
    evidence: "research/decomp/ghidra-export/chunk_0046.c:4813-4816",
  },
  {
    id: "ctor_8019e414",
    name: "constructor 8019e414 command table",
    constructorAddress: 0x8019e414,
    pointerLabelAddress: 0x803750a8,
    commandStructAddress: 0x80375128,
    evidence: "research/decomp/ghidra-export/chunk_0049.c:824-827",
  },
  {
    id: "ctor_8019e9a4",
    name: "constructor 8019e9a4 command table",
    constructorAddress: 0x8019e9a4,
    pointerLabelAddress: 0x80376420,
    commandStructAddress: 0x803765e0,
    evidence: "research/decomp/ghidra-export/chunk_0049.c:1169-1172",
  },
  {
    id: "ctor_8019e9a4_alt_000c",
    name: "constructor 8019e9a4 pl000c command table",
    constructorAddress: 0x8019e9a4,
    pointerLabelAddress: 0x80376420,
    commandStructAddress: 0x803766f8,
    appliesToIds: ["pl000c"],
    evidence: "research/decomp/ghidra-export/chunk_0049.c:1178-1181",
  },
  {
    id: "ctor_801a04f0",
    name: "constructor 801a04f0 command table",
    constructorAddress: 0x801a04f0,
    pointerLabelAddress: 0x80377840,
    commandStructAddress: 0x80377918,
    evidence: "research/decomp/ghidra-export/chunk_0049.c:2356-2359",
  },
  {
    id: "ctor_801a10e8",
    name: "constructor 801a10e8 command table",
    constructorAddress: 0x801a10e8,
    pointerLabelAddress: 0x803786e0,
    commandStructAddress: 0x803782b0,
    evidence: "research/decomp/ghidra-export/chunk_0049.c:2876-2879",
  },
  {
    id: "ctor_801a10e8_alt_090b",
    name: "constructor 801a10e8 pl090b command table",
    constructorAddress: 0x801a10e8,
    pointerLabelAddress: 0x803786e0,
    commandStructAddress: 0x803783c8,
    appliesToIds: ["pl090b"],
    evidence: "research/decomp/ghidra-export/chunk_0049.c:2885-2888",
  },
  {
    id: "ctor_801a51cc",
    name: "constructor 801a51cc command table",
    constructorAddress: 0x801a51cc,
    pointerLabelAddress: 0x803793c8,
    commandStructAddress: 0x80379448,
    evidence: "research/decomp/ghidra-export/chunk_0050.c:2424-2427",
  },
  {
    id: "ctor_801b289c",
    name: "constructor 801b289c command table",
    constructorAddress: 0x801b289c,
    pointerLabelAddress: 0x80380a78,
    commandStructAddress: 0x80380aa0,
    evidence: "research/decomp/ghidra-export/chunk_0052.c:3727-3730",
  },
  {
    id: "ctor_801b3598",
    name: "constructor 801b3598 command table",
    constructorAddress: 0x801b3598,
    pointerLabelAddress: 0x80380ee0,
    commandStructAddress: 0x80380f08,
    evidence: "research/decomp/ghidra-export/chunk_0052.c:4319-4322",
  },
  {
    id: "ctor_801b3c6c",
    name: "constructor 801b3c6c command table",
    constructorAddress: 0x801b3c6c,
    pointerLabelAddress: 0x80381528,
    commandStructAddress: 0x803811e0,
    evidence: "research/decomp/ghidra-export/chunk_0052.c:4714-4717",
  },
];

function fail(message) {
  console.error(`gen-command-move-tables: ${message}`);
  process.exit(1);
}

if (!fs.existsSync(bootDolPath)) fail(`missing ${path.relative(repoRoot, bootDolPath)}`);
if (!fs.existsSync(borgsPath)) fail(`missing ${path.relative(repoRoot, borgsPath)}`);

const dol = fs.readFileSync(bootDolPath);
const borgsData = JSON.parse(fs.readFileSync(borgsPath, "utf8"));
if (!Array.isArray(borgsData.borgs)) fail("packages/assets/data/borgs.json missing borgs array");

const sectionOffsets = Array.from({ length: 18 }, (_, index) => dol.readUInt32BE(index * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, index) => dol.readUInt32BE(0x48 + index * 4));
const sectionSizes = Array.from({ length: 18 }, (_, index) => dol.readUInt32BE(0x90 + index * 4));

function offsetFor(address) {
  for (let index = 0; index < sectionSizes.length; index += 1) {
    const size = sectionSizes[index];
    const base = sectionAddresses[index];
    if (size > 0 && address >= base && address < base + size) {
      return sectionOffsets[index] + (address - base);
    }
  }
  return null;
}

function requireOffset(address, label) {
  const offset = offsetFor(address);
  if (offset === null) fail(`${label} address ${hex(address)} is outside mapped DOL sections`);
  return offset;
}

function readU32(address) {
  return dol.readUInt32BE(requireOffset(address, "u32"));
}

function readU32IfMapped(address) {
  const offset = offsetFor(address);
  return offset === null ? null : dol.readUInt32BE(offset);
}

function readS8(address) {
  const value = dol.readUInt8(requireOffset(address, "s8"));
  return value > 127 ? value - 256 : value;
}

function hex(value) {
  return `0x${value.toString(16).padStart(8, "0")}`;
}

function compactHex(value) {
  return `0x${value.toString(16)}`;
}

function sign16(value) {
  const masked = value & 0xffff;
  return masked >= 0x8000 ? masked - 0x10000 : masked;
}

function sourceIdForDerivedCommandTable(constructorAddress, rootAddress, commandStructAddress) {
  return `ctor_${constructorAddress.toString(16)}_root_${rootAddress.toString(16)}_cmd_${commandStructAddress.toString(16)}`;
}

function decodeCommandTable(source) {
  const rootAddress = source.rootAddress ?? readU32(source.pointerLabelAddress);
  const modes = Array.from({ length: COMMAND_TYPE_COUNT }, (_, type) =>
    readS8(source.commandStructAddress + COMMAND_MODE_OFFSET + type),
  );
  const types = [];

  for (let commandType = 0; commandType < COMMAND_TYPE_COUNT; commandType += 1) {
    const mode = modes[commandType];
    const pointerAddress = rootAddress + commandType * 4;
    const tableAddress = readU32(pointerAddress);
    const entry = {
      type: commandType,
      mode,
      modeName: modeName(mode),
      pointerAddress: hex(pointerAddress),
      tableAddress: hex(tableAddress),
      records: [],
    };

    if ((mode === 0 || mode === 1) && offsetFor(tableAddress) !== null) {
      for (let subtype = 0; subtype < COMMAND_SUBTYPE_COUNT; subtype += 1) {
        const directions = mode === 1 ? DIRECTION_COUNT : 1;
        for (let direction = 0; direction < directions; direction += 1) {
          const recordAddress =
            mode === 1
              ? tableAddress + subtype * DIRECTION_COUNT * RECORD_SIZE + direction * RECORD_SIZE
              : tableAddress + subtype * RECORD_SIZE;
          const bytes = Array.from({ length: RECORD_SIZE }, (_, index) => readS8(recordAddress + index));
          entry.records.push({
            subtype,
            direction: mode === 1 ? direction : null,
            address: hex(recordAddress),
            bytes,
            disabled: bytes[0] === -1,
            cueId: bytes[0],
            stateMode: bytes[1],
            actionIndex: bytes[2],
            variantIndex: bytes[3],
          });
        }
      }
    }

    types.push(entry);
  }

  return {
    id: source.id,
    name: source.name,
    constructorAddress: hex(source.constructorAddress),
    pointerLabelAddress: hex(source.pointerLabelAddress),
    rootAddress: hex(rootAddress),
    commandStructAddress: hex(source.commandStructAddress),
    evidence: source.evidence,
    modes,
    types,
  };
}

function modeName(mode) {
  if (mode === -1) return "disabled";
  if (mode === 0) return "subtype";
  if (mode === 1) return "subtype+direction";
  return "reserved";
}

function borgNumber(id) {
  return Number.parseInt(id.slice(2), 16);
}

function constructorForBorgId(id) {
  const value = borgNumber(id);
  const family = value >> 8;
  const variant = value & 0xff;
  const familyTable = readU32(CONSTRUCTOR_TABLE + family * 4);
  const constructorAddress = readU32(familyTable + variant * 4);
  return { value, family, variant, familyTable, constructorAddress };
}

const derivedConstructorSourceCache = new Map();

function actorLoadValue(offset, borgValue) {
  if (offset === 0x3e8) return borgValue;
  if (offset === 0x3e9) return borgValue & 0xff;
  if (offset === 0x3e7) return (borgValue >> 8) & 0xff;
  return null;
}

function compareValues(left, right) {
  if (left === right) return { lt: false, gt: false, eq: true };
  return { lt: left < right, gt: left > right, eq: false };
}

function crBit(cr0, bi) {
  if (!cr0) return null;
  const bit = bi & 3;
  if (bit === 0) return cr0.lt;
  if (bit === 1) return cr0.gt;
  if (bit === 2) return cr0.eq;
  return false;
}

function branchConditionMet(word, cr0) {
  const bo = (word >>> 21) & 0x1f;
  const bi = (word >>> 16) & 0x1f;
  if (bo === 20) return true;

  const bit = crBit(cr0, bi);
  if (bit === null) return null;
  if (bo === 12) return bit;
  if (bo === 4) return !bit;
  return null;
}

function branchDisplacement(word) {
  const raw = word & 0xfffc;
  return raw >= 0x8000 ? raw - 0x10000 : raw;
}

function branchTarget(pc, word) {
  const displacement = branchDisplacement(word);
  return (word & 2) !== 0 ? displacement >>> 0 : (pc + displacement) >>> 0;
}

function branchImmediateTarget(pc, word) {
  let li = word & 0x03fffffc;
  if ((li & 0x02000000) !== 0) li -= 0x04000000;
  return (word & 2) !== 0 ? li >>> 0 : (pc + li) >>> 0;
}

function isBclr(word) {
  return (word & 0xfc0007fe) === 0x4c000020;
}

function isBcctr(word) {
  return (word & 0xfc0007fe) === 0x4c000420;
}

function collectConstructorStoresForBorg(constructorAddress, borgValue) {
  const regs = Array.from({ length: 32 }, () => null);
  const regSources = Array.from({ length: 32 }, () => null);
  const regValueAddresses = Array.from({ length: 32 }, () => null);
  const stores = [];
  let cr0 = null;
  let ctr = null;
  let pc = constructorAddress;
  let steps = 0;

  while (steps < 512 && pc >= constructorAddress && pc < constructorAddress + CONSTRUCTOR_SCAN_BYTES) {
    steps += 1;
    const word = readU32IfMapped(pc);
    if (word === null) break;

    const opcode = word >>> 26;
    const rt = (word >>> 21) & 0x1f;
    const ra = (word >>> 16) & 0x1f;
    const rb = (word >>> 11) & 0x1f;
    const simm = sign16(word);
    const rawImm = word & 0xffff;
    let nextPc = (pc + 4) >>> 0;

    if (opcode === 15 && ra === 0) {
      regs[rt] = (rawImm << 16) >>> 0;
      regSources[rt] = `${hex(pc)} lis`;
      regValueAddresses[rt] = null;
    } else if (opcode === 14) {
      if (ra === 0) {
        regs[rt] = simm >>> 0;
        regSources[rt] = `${hex(pc)} addi`;
        regValueAddresses[rt] = null;
      } else if (regs[ra] !== null) {
        regs[rt] = (regs[ra] + simm) >>> 0;
        regSources[rt] = `${regSources[ra]} + ${hex(pc)} addi`;
        regValueAddresses[rt] = null;
      } else {
        regs[rt] = null;
        regSources[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 10) {
      const left = regs[ra];
      cr0 = left === null ? null : compareValues(left >>> 0, rawImm);
    } else if (opcode === 11) {
      const left = regs[ra];
      cr0 = left === null ? null : compareValues(left | 0, simm);
    } else if (opcode === 21) {
      const rs = rt;
      const sh = (word >>> 11) & 0x1f;
      const mb = (word >>> 6) & 0x1f;
      const me = (word >>> 1) & 0x1f;
      if (regs[rs] !== null && mb === 0 && me === 31 - sh) {
        regs[ra] = (regs[rs] << sh) >>> 0;
        regSources[ra] = `${regSources[rs]} + ${hex(pc)} slwi`;
        regValueAddresses[ra] = null;
      } else {
        regs[ra] = null;
        regSources[ra] = null;
        regValueAddresses[ra] = null;
      }
    } else if (opcode === 32) {
      if (regs[ra] !== null) {
        const address = (regs[ra] + simm) >>> 0;
        regs[rt] = readU32IfMapped(address);
        regSources[rt] = regs[rt] === null ? null : `${hex(pc)} lwz ${hex(address)}`;
        regValueAddresses[rt] = regs[rt] === null ? null : address;
      } else {
        regs[rt] = null;
        regSources[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 34) {
      const actorValue = ra === 3 ? actorLoadValue(simm, borgValue) : null;
      if (actorValue !== null) {
        regs[rt] = actorValue & 0xff;
        regSources[rt] = `${hex(pc)} actor+${compactHex(simm)}`;
        regValueAddresses[rt] = null;
      } else if (regs[ra] !== null) {
        const address = (regs[ra] + simm) >>> 0;
        const offset = offsetFor(address);
        regs[rt] = offset === null ? null : dol.readUInt8(offset);
        regSources[rt] = regs[rt] === null ? null : `${hex(pc)} lbz ${hex(address)}`;
        regValueAddresses[rt] = null;
      } else {
        regs[rt] = null;
        regSources[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 36) {
      const offset = sign16(word);
      if (ra === 3 && (offset === ACTOR_COMMAND_POINTER_OFFSET || offset === ACTOR_COMMAND_STRUCT_OFFSET)) {
        stores.push({
          pc,
          offset,
          value: regs[rt],
          valueSource: regSources[rt],
          valueAddress: regValueAddresses[rt],
        });
      }
    } else if (opcode === 42) {
      const actorValue = ra === 3 ? actorLoadValue(simm, borgValue) : null;
      if (actorValue !== null) {
        regs[rt] = sign16(actorValue);
        regSources[rt] = `${hex(pc)} actor+${compactHex(simm)}`;
        regValueAddresses[rt] = null;
      } else if (regs[ra] !== null) {
        const address = (regs[ra] + simm) >>> 0;
        const offset = offsetFor(address);
        regs[rt] = offset === null ? null : dol.readInt16BE(offset);
        regSources[rt] = regs[rt] === null ? null : `${hex(pc)} lha ${hex(address)}`;
        regValueAddresses[rt] = null;
      } else {
        regs[rt] = null;
        regSources[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if (opcode === 16) {
      const shouldBranch = branchConditionMet(word, cr0);
      if (shouldBranch) nextPc = branchTarget(pc, word);
    } else if (opcode === 18) {
      const link = (word & 1) !== 0;
      if (!link) nextPc = branchImmediateTarget(pc, word);
    } else if (opcode === 19 && isBclr(word)) {
      const shouldReturn = branchConditionMet(word, cr0);
      if (shouldReturn === null || shouldReturn) break;
    } else if (opcode === 19 && isBcctr(word)) {
      if (ctr === null) break;
      nextPc = ctr >>> 0;
    } else if (opcode === 31) {
      const xo = (word >>> 1) & 0x3ff;
      if (xo === 23) {
        if (regs[ra] !== null && regs[rb] !== null) {
          const address = (regs[ra] + regs[rb]) >>> 0;
          regs[rt] = readU32IfMapped(address);
          regSources[rt] = regs[rt] === null ? null : `${hex(pc)} lwzx ${hex(address)}`;
          regValueAddresses[rt] = regs[rt] === null ? null : address;
        } else {
          regs[rt] = null;
          regSources[rt] = null;
          regValueAddresses[rt] = null;
        }
      } else if (xo === 467) {
        ctr = regs[rt];
      } else if (xo === 954) {
        regs[ra] = regs[rt] === null ? null : ((regs[rt] << 24) >> 24);
        regSources[ra] = regs[rt] === null ? null : `${regSources[rt]} + ${hex(pc)} extsb`;
        regValueAddresses[ra] = null;
      } else {
        regs[rt] = null;
        regSources[rt] = null;
        regValueAddresses[rt] = null;
      }
    } else if ([24, 40].includes(opcode)) {
      regs[rt] = null;
      regSources[rt] = null;
      regValueAddresses[rt] = null;
    }

    pc = nextPc;
  }

  return stores;
}

function derivedSourceForConstructor(constructorAddress, borgValue) {
  const cacheKey = `${constructorAddress}:${borgValue}`;
  if (derivedConstructorSourceCache.has(cacheKey)) {
    return derivedConstructorSourceCache.get(cacheKey);
  }

  const stores = collectConstructorStoresForBorg(constructorAddress, borgValue);
  const pointerStore = stores.findLast((store) => store.offset === ACTOR_COMMAND_POINTER_OFFSET && store.value !== null);
  const commandStructStore = stores.findLast(
    (store) => store.offset === ACTOR_COMMAND_STRUCT_OFFSET && store.value !== null,
  );

  if (!pointerStore || !commandStructStore) {
    derivedConstructorSourceCache.set(cacheKey, null);
    return null;
  }

  const rootAddress = pointerStore.value;
  const pointerLabelAddress = pointerStore.valueAddress ?? pointerStore.value;
  const commandStructAddress = commandStructStore.value;
  if (
    offsetFor(rootAddress) === null ||
    offsetFor(pointerLabelAddress) === null ||
    offsetFor(commandStructAddress + COMMAND_MODE_OFFSET + COMMAND_TYPE_COUNT - 1) === null
  ) {
    derivedConstructorSourceCache.set(cacheKey, null);
    return null;
  }

  const source = {
    id: sourceIdForDerivedCommandTable(constructorAddress, rootAddress, commandStructAddress),
    name: `constructor ${compactHex(constructorAddress)} vector command table`,
    constructorAddress,
    pointerLabelAddress,
    rootAddress,
    commandStructAddress,
    resolution: "constructor-vector",
    evidence: `user-data/GG4E/disc/sys/boot.dol:${hex(constructorAddress)} copies actor+0x4ec root via ${hex(
      pointerStore.pc,
    )} and actor+0x4b0 via ${hex(commandStructStore.pc)}`,
  };

  derivedConstructorSourceCache.set(cacheKey, source);
  return source;
}

function sourceForBorg(id, constructorAddress) {
  const exact = COMMAND_TABLE_SOURCES.find(
    (source) => source.constructorAddress === constructorAddress && source.appliesToIds?.includes(id),
  );
  if (exact) return exact;
  const direct = COMMAND_TABLE_SOURCES.find(
    (source) => source.constructorAddress === constructorAddress && !source.appliesToIds,
  );
  if (direct) return direct;
  return derivedSourceForConstructor(constructorAddress, borgNumber(id));
}

const sourceById = new Map(COMMAND_TABLE_SOURCES.map((source) => [source.id, source]));
const borgs = {};
for (const borg of borgsData.borgs) {
  const id = String(borg.id).toLowerCase();
  const ctor = constructorForBorgId(id);
  const source = sourceForBorg(id, ctor.constructorAddress);
  if (source) sourceById.set(source.id, source);
  borgs[id] = {
    id,
    name: borg.name,
    borgNumber: compactHex(ctor.value),
    family: ctor.family,
    variant: ctor.variant,
    constructorFamilyTable: hex(ctor.familyTable),
    constructorAddress: hex(ctor.constructorAddress),
    tableId: source?.id ?? null,
    exactCommandTable: source !== null,
    commandTableResolution: source ? (source.resolution ?? "direct") : null,
    commandTableEvidence: source?.evidence ?? null,
    pointerLabelAddress: source ? hex(source.pointerLabelAddress) : null,
    commandStructAddress: source ? hex(source.commandStructAddress) : null,
  };
}

const allSources = [...sourceById.values()];
const tables = Object.fromEntries(allSources.map((source) => [source.id, decodeCommandTable(source)]));
const exactBorgs = Object.values(borgs).filter((borg) => borg.exactCommandTable).length;
const output = {
  _meta: {
    generatedBy: "scripts/gen-command-move-tables.mjs",
    source: "user-data/GG4E/disc/sys/boot.dol",
    constructorDispatch: {
      tableAddress: hex(CONSTRUCTOR_TABLE),
      evidence: "research/decomp/ghidra-export/chunk_0007.c:412-416",
      note: "family byte indexes PTR_PTR_802d3224; low id byte indexes that family constructor table",
    },
    finalDispatch: {
      evidence: "research/decomp/ghidra-export/chunk_0009.c:456-599,605-679",
      note: "actor+0x4b0[type+0xb8] selects disabled/subtype/subtype+direction; actor+0x4ec[type] points to 4-byte records consumed by zz_006a104_",
    },
    coverage: {
      rosterBorgs: borgsData.borgs.length,
      exactCommandTableBorgs: exactBorgs,
      decodedTables: allSources.length,
      directCommandTableSources: COMMAND_TABLE_SOURCES.length,
      derivedConstructorVectorSources: allSources.filter((source) => source.resolution === "constructor-vector").length,
    },
  },
  tables,
  borgs,
};

fs.mkdirSync(path.dirname(outPath), { recursive: true });
fs.writeFileSync(outPath, `${JSON.stringify(output, null, 2)}\n`);
console.log(
  `wrote ${path.relative(repoRoot, outPath)} (${allSources.length} tables, ${exactBorgs}/${borgsData.borgs.length} roster borgs exact)`,
);
