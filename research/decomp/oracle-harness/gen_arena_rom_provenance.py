#!/usr/bin/env python3
"""Bind the oracle arena to real GameCube RAM.

The arena (``research/decomp/poc/wasm-port-poc/arena.json``) is the static memory
image every differential oracle reads: damage tables, remap rows, float constants,
runtime struct pointers. Until now nothing recorded where those 13,312 bytes came
from -- the file carries no provenance at all -- so a regenerated or hand-edited
arena would silently change what every oracle compares against.

This generator establishes that binding once, against a Dolphin-captured MEM1 image
of the real console RAM, and writes a tracked witness sidecar so the binding can be
re-checked forever WITHOUT the private capture.

The endianness point, which is the whole subtlety:

    The arena stores each segment in host (little-endian) byte order, because the
    ported C runs on wasm. Real GameCube RAM is big-endian PowerPC. So the arena is
    NOT a byte-for-byte copy of RAM -- it is an element-wise byte-swapped copy, and
    the swap width is a per-segment property of the data (s16 rows swap at 2 bytes,
    f32/pointer tables at 4, f64 constants at 8, char tables not at all).

    Comparing the two naively reports ~1% agreement and looks like a catastrophe.
    Applying each segment's own element width reports 100% on every segment. That
    width is exactly the invariant nothing was recording.

Usage:
    python gen_arena_rom_provenance.py <mem1.bin> [<mem1_second.bin> ...]

Every image given must agree on every segment; passing two captures taken at
different moments of live play is the cheap way to prove the regions are static
data rather than something that merely happened to match once.
"""
from __future__ import annotations

import base64
import hashlib
import json
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
REPO_ROOT = HERE.parents[2]
ARENA_PATH = REPO_ROOT / "research/decomp/poc/wasm-port-poc/arena.json"
OUT_PATH = HERE / "arena-rom-provenance.json"
PROVENANCE_SCHEMA = 1

# GameCube MEM1 is mapped at 0x80000000.
MEM1_BASE = 0x80000000
# Element widths a segment may be stored at, widest first: a 4-byte-swapped region
# is never also 2-byte-swapped unless its data is symmetric, and preferring the
# wider reading keeps f32/pointer tables from being mislabelled as s16 rows.
CANDIDATE_WIDTHS = (8, 4, 2, 1)


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def swap_elements(data: bytes, width: int) -> bytes:
    """Reverse bytes within each `width`-sized element."""
    if width == 1:
        return data
    return b"".join(data[i : i + width][::-1] for i in range(0, len(data), width))


def matching_widths(le_bytes: bytes, rom_bytes: bytes) -> list[int]:
    """Every element width at which the arena segment reproduces the ROM bytes."""
    return [
        w
        for w in CANDIDATE_WIDTHS
        if len(le_bytes) % w == 0 and swap_elements(le_bytes, w) == rom_bytes
    ]


def main(argv: list[str]) -> int:
    if len(argv) < 2:
        print(__doc__, file=sys.stderr)
        return 2

    images: list[tuple[str, bytes]] = []
    for arg in argv[1:]:
        p = Path(arg)
        if not p.is_file():
            print(f"ERROR: no such MEM1 image: {p}", file=sys.stderr)
            return 2
        images.append((p.name, p.read_bytes()))

    arena_raw = ARENA_PATH.read_bytes()
    arena = json.loads(arena_raw.decode("utf-8-sig"))

    segments = []
    failures = []
    for seg in arena["segments"]:
        addr = seg["addr"]
        le_bytes = base64.b64decode(seg["b64"])
        offset = addr - MEM1_BASE

        # Every image must agree, and must agree at the SAME width.
        per_image: dict[str, list[int]] = {}
        rom_bytes = None
        for name, image in images:
            if offset < 0 or offset + len(le_bytes) > len(image):
                per_image[name] = []
                continue
            window = image[offset : offset + len(le_bytes)]
            if rom_bytes is None:
                rom_bytes = window
            elif window != rom_bytes:
                failures.append(f"0x{addr:08x}: images disagree -- region is not static data")
            per_image[name] = matching_widths(le_bytes, window)

        common = [w for w in CANDIDATE_WIDTHS if all(w in v for v in per_image.values())]
        if not common or rom_bytes is None:
            failures.append(
                f"0x{addr:08x} ({len(le_bytes)}B): no element width reproduces ROM "
                f"(per-image candidates: {per_image})"
            )
            continue

        segments.append(
            {
                "addr": addr,
                "addr_hex": f"0x{addr:08x}",
                "size": len(le_bytes),
                # The chosen width, and every width that also happened to work.
                # Symmetric data (an all-zero constant) matches at every width; the
                # ambiguity is recorded rather than hidden behind the chosen value.
                "elem_width": common[0],
                "elem_width_candidates": common,
                "width_ambiguous": len(common) > 1,
                # The witness: sha of the bytes AS THEY APPEAR IN REAL RAM. A future
                # check swaps the arena by elem_width and must reproduce this hash --
                # no MEM1 capture required.
                "rom_be_sha256": sha256(rom_bytes),
                "note": seg.get("note", ""),
            }
        )

    if failures:
        print("ARENA ROM BINDING FAILED:", file=sys.stderr)
        for f in failures:
            print(f"  - {f}", file=sys.stderr)
        return 1

    payload = {
        "provenance_schema": PROVENANCE_SCHEMA,
        "generated_by": "research/decomp/oracle-harness/gen_arena_rom_provenance.py",
        "describes": {
            "path": "research/decomp/poc/wasm-port-poc/arena.json",
            "sha256": sha256(arena_raw),
        },
        "rom_sources": [
            {"name": name, "sha256": sha256(image), "bytes": len(image)}
            for name, image in images
        ],
        "notes": [
            "The arena stores each segment little-endian (the port runs on wasm);",
            "real GameCube RAM is big-endian PowerPC. Each segment is therefore an",
            "ELEMENT-WISE byte-swapped copy at its own elem_width -- comparing the",
            "two without that width reports ~1% agreement and is meaningless.",
            "rom_be_sha256 lets the binding be re-verified from the tracked arena",
            "alone; the MEM1 captures under user-data/ are private and never needed",
            "again except to re-establish the binding from scratch.",
        ],
        "segments": segments,
    }
    OUT_PATH.write_text(json.dumps(payload, indent=1) + "\n", encoding="utf-8", newline="\n")

    total = sum(s["size"] for s in segments)
    ambiguous = sum(1 for s in segments if s["width_ambiguous"])
    print(f"verified {len(segments)} segments / {total} bytes against {len(images)} MEM1 image(s)")
    print(f"  width-ambiguous (symmetric data, any width reproduces ROM): {ambiguous}")
    print(f"wrote {OUT_PATH.relative_to(REPO_ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
