#!/usr/bin/env python3
"""Extract original slot-table spawn evidence from Dolphin MEM1/save-state dumps."""

import argparse
import json
import struct
from pathlib import Path
from typing import List, Optional, Tuple

import lz4.block

MEM1_SIZE = 0x01800000
RAM_BASE = 0x80000000


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("inputs", nargs="+", help="MEM1 .bin or Dolphin .sav files")
    parser.add_argument("--out", type=Path, default=None, help="Optional JSON output path")
    args = parser.parse_args()

    report = {
        "notes": [
            "PTR_DAT_80433934 is read from *(u32*)0x80433934.",
            "DAT_803c4e84 actor table pointer is read from *(u32*)0x803c4e84.",
            "Spawn-source fields are PTR_DAT_80433934 + 0x1604 + slot*0x0c (x/y/z), per chunk_0007.c:448-505.",
            "Live actor position is actor +0x20/+0x24/+0x28, stride 0x1e00 from DAT_803c4e84.",
        ],
        "sources": [extract_source(Path(p)) for p in args.inputs],
    }

    text = json.dumps(report, indent=2) + "\n"
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        with args.out.open("w", encoding="utf-8", newline="\n") as fh:
            fh.write(text)
    print(text, end="")
    return 0


def extract_source(path: Path) -> dict:
    data, meta = load_mem1(path)
    table_ptr = u32(data, 0x433934)
    actor_ptr = u32(data, 0x3C4E84)
    table_off = ram_offset(table_ptr)
    actor_off = ram_offset(actor_ptr)
    slots = []
    for slot in range(6):
        spawn_off = table_off + 0x1604 + slot * 0x0C
        aoff = actor_off + slot * 0x1E00
        slots.append(
            {
                "slot": slot,
                "slotTeam": u8(data, table_off + 0xCB + slot),
                "activeBorgRaw": f"{u16(data, table_off + 0x10 + slot * 2):04x}",
                "spawnSource": vec3(data, spawn_off),
                "actor": {
                    "borgRaw": f"{u16(data, aoff + 1000):04x}",
                    "mode": u8(data, aoff + 0x18),
                    "team": u8(data, aoff + 0x88),
                    "hp": i16(data, aoff + 0x1C6),
                    "maxHp": i16(data, aoff + 0x1C4),
                    "position": vec3(data, aoff + 0x20),
                    "yawBam16": i16(data, aoff + 0x72),
                    "state544": u8(data, aoff + 0x544),
                },
            }
        )
    return {
        "path": str(path).replace("\\", "/"),
        **meta,
        "slotTablePointer": hex(table_ptr),
        "actorTablePointer": hex(actor_ptr),
        "slots": slots,
    }


def load_mem1(path: Path) -> Tuple[bytes, dict]:
    raw = path.read_bytes()
    if path.suffix.lower() != ".sav":
        return raw, {"kind": "mem1", "mem1StateOffset": 0, "bytes": len(raw)}

    data, meta = decompress_dolphin_save(raw)
    mem1_offset = find_mem1_base(data)
    if mem1_offset is None:
        raise RuntimeError(f"could not locate MEM1 in {path}")
    return data[mem1_offset : mem1_offset + MEM1_SIZE], {
        **meta,
        "kind": "dolphin-sav",
        "mem1StateOffset": hex(mem1_offset),
        "mem1Bytes": min(MEM1_SIZE, len(data) - mem1_offset),
    }


def decompress_dolphin_save(raw: bytes) -> Tuple[bytes, dict]:
    version_len = struct.unpack_from("<I", raw, 0x1C)[0]
    version_offset = 0x20
    version = raw[version_offset : version_offset + version_len].decode("ascii", "replace")
    ext_offset = version_offset + version_len
    header_version, compression_type, payload_offset, uncompressed_size = struct.unpack_from("<HHIQ", raw, ext_offset)
    if compression_type != 1:
        raise RuntimeError(f"unsupported Dolphin compression type {compression_type}; expected LZ4=1")

    cursor = ext_offset + 16 + payload_offset
    out = bytearray()
    chunks = []
    while cursor + 4 <= len(raw):
        compressed_len = struct.unpack_from("<i", raw, cursor)[0]
        cursor += 4
        if compressed_len <= 0:
            break
        block = raw[cursor : cursor + compressed_len]
        cursor += compressed_len
        remaining = uncompressed_size - len(out)
        decoded = None
        for size in dict.fromkeys([remaining, 32 * 1024 * 1024, 16 * 1024 * 1024]):
            try:
                decoded = lz4.block.decompress(block, uncompressed_size=size)
                break
            except Exception:
                pass
        if decoded is None:
            decoded = lz4.block.decompress(block)
        out.extend(decoded)
        chunks.append({"compressedBytes": compressed_len, "decompressedBytes": len(decoded)})
        if len(out) >= uncompressed_size:
            break

    return bytes(out), {
        "dolphinVersion": version,
        "stateHeaderVersion": header_version,
        "compressionType": compression_type,
        "uncompressedBytes": uncompressed_size,
        "chunks": chunks,
    }


def find_mem1_base(data: bytes) -> Optional[int]:
    start = 0
    while True:
        offset = data.find(b"GG4E", start)
        if offset < 0:
            return None
        if offset + 0x20 <= len(data) and data[offset + 0x1C : offset + 0x20] == b"\xC2\x33\x9F\x3D":
            return offset
        start = offset + 1


def ram_offset(addr: int) -> int:
    return addr - RAM_BASE


def vec3(data: bytes, off: int) -> List[float]:
    return [round(f32(data, off + i * 4), 6) for i in range(3)]


def u8(data: bytes, off: int) -> int:
    return data[off]


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
