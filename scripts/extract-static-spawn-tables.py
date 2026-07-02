#!/usr/bin/env python3
"""Extract static spawn-vector tables from GG4E boot.dol."""

from __future__ import annotations

import argparse
import json
import math
import struct
from pathlib import Path
from typing import Optional

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_DOL = ROOT / "user-data" / "GG4E" / "disc" / "sys" / "boot.dol"
DEFAULT_OUT = ROOT / "research" / "decomp" / "data" / "static-spawn-tables.json"

PTR_TABLE_ADDR = 0x8037F5D0
MISSION_RECORD_MIN = 0x8037D000
MISSION_RECORD_MAX = 0x8037F5D0
MISSION_RECORD_SIZE = 0x30
ENEMY_SPAWN_TABLE_ADDR = 0x8037F8F0
ENEMY_SPAWN_RECORD_SIZE = 0x14


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--dol", type=Path, default=DEFAULT_DOL)
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT)
    args = parser.parse_args()

    dol = args.dol.read_bytes()
    mapper = DolMapper(dol)
    mission_records = extract_mission_records(dol, mapper)
    referenced_enemy_rows = sorted({
        row
        for record in mission_records
        for row in record["enemyRowIndices"]
        if row >= 0
    })
    enemy_records = extract_enemy_records(dol, mapper, referenced_enemy_rows)
    report = {
        "sources": {
            "dol": str(args.dol.relative_to(ROOT)).replace("\\", "/"),
            "missionSpawnPointerTable": hex(PTR_TABLE_ADDR),
            "enemySpawnTable": hex(ENEMY_SPAWN_TABLE_ADDR),
        },
        "notes": [
            "zz_0186964_ reads mission records through (&PTR_DAT_8037f5d0)[battle_index].",
            "Mission record offset +0x0c is the active/player spawn vector; +0x18 is the other-side spawn vector.",
            "Enemy add rows come from DAT_8037f8f0 records; spawn vector is record +0x04/+0x08/+0x0c.",
            "Y=0 means actor init queries STIH floor via FUN_8003d6e4 instead of using the raw Y.",
        ],
        "missionRecords": mission_records,
        "enemySpawnRows": enemy_records,
    }

    args.out.parent.mkdir(parents=True, exist_ok=True)
    with args.out.open("w", encoding="utf-8", newline="\n") as fh:
        fh.write(json.dumps(report, indent=2) + "\n")
    print(json.dumps({"out": str(args.out.relative_to(ROOT)).replace("\\", "/"), "missionRecords": len(mission_records), "enemySpawnRows": len(enemy_records)}, indent=2))
    return 0


class DolMapper:
    def __init__(self, data: bytes):
        offsets = struct.unpack_from(">18I", data, 0x00)
        addrs = struct.unpack_from(">18I", data, 0x48)
        sizes = struct.unpack_from(">18I", data, 0x90)
        self.sections = [
            (offsets[i], addrs[i], sizes[i])
            for i in range(18)
            if sizes[i] != 0
        ]

    def offset(self, addr: int) -> Optional[int]:
        for file_off, ram_addr, size in self.sections:
            if ram_addr <= addr < ram_addr + size:
                return file_off + (addr - ram_addr)
        return None

    def checked_offset(self, addr: int, size: int) -> int:
        off = self.offset(addr)
        if off is None:
            raise ValueError(f"address {hex(addr)} is not mapped by the DOL")
        return off


def extract_mission_records(dol: bytes, mapper: DolMapper) -> list[dict]:
    records = []
    for index in range(512):
        ptr = u32(dol, mapper.checked_offset(PTR_TABLE_ADDR + index * 4, 4))
        if not (MISSION_RECORD_MIN <= ptr < MISSION_RECORD_MAX):
            break
        off = mapper.checked_offset(ptr, MISSION_RECORD_SIZE)
        raw = dol[off : off + MISSION_RECORD_SIZE]
        records.append(
            {
                "index": index,
                "address": hex(ptr),
                "enemyRowIndices": [i16(raw, i * 2) for i in range(5)],
                "playerSpawn": spawn_vec(raw, 0x0C, raw[0x24]),
                "otherSideSpawn": spawn_vec(raw, 0x18, raw[0x25]),
                "timeMinutes": i16(raw, 0x26),
                "flags": hex(u16(raw, 0x28)),
            }
        )
    return records


def extract_enemy_records(dol: bytes, mapper: DolMapper, indices: list[int]) -> list[dict]:
    records = []
    for index in indices:
        off = mapper.checked_offset(ENEMY_SPAWN_TABLE_ADDR + index * ENEMY_SPAWN_RECORD_SIZE, ENEMY_SPAWN_RECORD_SIZE)
        raw = dol[off : off + ENEMY_SPAWN_RECORD_SIZE]
        records.append(
            {
                "index": index,
                "rowBytes": list(raw[:4]),
                "spawn": spawn_vec(raw, 0x04, raw[0x10]),
            }
        )
    return records


def spawn_vec(raw: bytes, offset: int, facing_byte: int) -> dict:
    return {
        "pos": [json_float(f32(raw, offset + i * 4)) for i in range(3)],
        "facingByte": facing_byte,
        "facingLowBits": facing_byte & 0x03,
        "facingHighBits": facing_byte & 0xF8,
    }


def json_float(value: float) -> float | None:
    return round(value, 6) if math.isfinite(value) else None


def u16(data: bytes, off: int) -> int:
    return struct.unpack_from(">H", data, off)[0]


def i16(data: bytes, off: int) -> int:
    return struct.unpack_from(">h", data, off)[0]


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from(">I", data, off)[0]


def f32(data: bytes, off: int) -> float:
    return struct.unpack_from(">f", data, off)[0]


if __name__ == "__main__":
    raise SystemExit(main())
