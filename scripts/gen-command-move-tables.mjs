#!/usr/bin/env node
// Generate the ROM command/action tables consumed at actor+0x4ec.
//
// Source chain:
// - constructor dispatch: chunk_0007.c:412-416, PTR_PTR_802d3224[family][variant]
// - final command lookup: chunk_0009.c:456-599 and 605-679
// - per-constructor +0x4ec/+0x4b0 writes: chunks listed in COMMAND_TABLE_SOURCES below

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

function decodeCommandTable(source) {
  const rootAddress = readU32(source.pointerLabelAddress);
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

function sourceForBorg(id, constructorAddress) {
  const exact = COMMAND_TABLE_SOURCES.find(
    (source) => source.constructorAddress === constructorAddress && source.appliesToIds?.includes(id),
  );
  if (exact) return exact;
  return COMMAND_TABLE_SOURCES.find(
    (source) => source.constructorAddress === constructorAddress && !source.appliesToIds,
  ) ?? null;
}

const tables = Object.fromEntries(COMMAND_TABLE_SOURCES.map((source) => [source.id, decodeCommandTable(source)]));
const borgs = {};
for (const borg of borgsData.borgs) {
  const id = String(borg.id).toLowerCase();
  const ctor = constructorForBorgId(id);
  const source = sourceForBorg(id, ctor.constructorAddress);
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
  };
}

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
      decodedTables: COMMAND_TABLE_SOURCES.length,
    },
  },
  tables,
  borgs,
};

fs.mkdirSync(path.dirname(outPath), { recursive: true });
fs.writeFileSync(outPath, `${JSON.stringify(output, null, 2)}\n`);
console.log(
  `wrote ${path.relative(repoRoot, outPath)} (${COMMAND_TABLE_SOURCES.length} tables, ${exactBorgs}/${borgsData.borgs.length} roster borgs exact)`,
);
