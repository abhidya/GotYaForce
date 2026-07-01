#!/usr/bin/env python3
import json
import re
import string
import struct
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path

import lz4.block

REPO_ROOT = Path(__file__).resolve().parents[1]
TRACE_DIR = REPO_ROOT / "user-data" / "GG4E" / "traces"
OUT_JSON = REPO_ROOT / "research" / "traces" / "GG4E" / "challenge-battle1-memory-evidence.json"
OUT_MD = REPO_ROOT / "research" / "traces" / "GG4E" / "challenge-battle1-memory-evidence.md"
BORG_JSON = REPO_ROOT / "packages" / "assets" / "data" / "borgs.json"

MEM1_SIZE = 0x01800000
MEM1_RAM_BASE = 0x80000000

SOURCES = [
    {"id": "mem1_t1", "kind": "mem1", "path": TRACE_DIR / "mem1_t1.bin"},
    {"id": "mem1_t2", "kind": "mem1", "path": TRACE_DIR / "mem1_t2.bin"},
    {"id": "battle1_challenge", "kind": "dolphin-sav", "path": TRACE_DIR / "battle1_challenge.sav"},
    {"id": "battle1_challenge_t2", "kind": "dolphin-sav", "path": TRACE_DIR / "battle1_challenge_t2.sav"},
    {"id": "battle1_start_checkpoint", "kind": "dolphin-sav", "path": TRACE_DIR / "battle1_start_checkpoint.sav"},
]

PATTERNS = {
    "stageArchives": re.compile(rb"st[0-9a-fA-F]{2}(?:_mdl\.arc|\.pzz)"),
    "stageSetArchives": re.compile(rb"set[0-9a-fA-F]{4}\.arc"),
    "stageHitBins": re.compile(rb"hit[0-9a-fA-F]{3}\.bin|comhit\.bin"),
    "borgAnimJoints": re.compile(rb"pl[0-9a-fA-F]{4}_b[0-9]{2}_animjoint"),
}


def main():
    borgs = load_borgs()
    source_reports = []
    pattern_totals = {name: 0 for name in PATTERNS}
    stage_matches = defaultdict(lambda: {"totalMatches": 0, "sources": defaultdict(int), "examples": []})
    borg_matches = defaultdict(
        lambda: {
            "totalMatches": 0,
            "sources": defaultdict(int),
            "bones": set(),
            "examples": [],
        }
    )

    for spec in SOURCES:
        if not spec["path"].exists():
            source_reports.append({"id": spec["id"], "path": rel(spec["path"]), "kind": spec["kind"], "exists": False})
            continue

        data, meta = load_source(spec)
        mem1_base = meta.get("mem1StateOffset")
        counts = {name: 0 for name in PATTERNS}

        for name, pattern in PATTERNS.items():
            for match in pattern.finditer(data):
                counts[name] += 1
                pattern_totals[name] += 1
                offset = match.start()
                text = match.group(0).decode("ascii").lower()
                example = make_example(spec, data, offset, text, mem1_base)

                if name == "borgAnimJoints":
                    borg_id = text[:6]
                    bone_id = text[7:10]
                    entry = borg_matches[borg_id]
                    entry["totalMatches"] += 1
                    entry["sources"][spec["id"]] += 1
                    entry["bones"].add(bone_id)
                    if len(entry["examples"]) < 4:
                        entry["examples"].append(example)
                else:
                    stage_id = text[:4] if text.startswith("st") else None
                    key = stage_id or text
                    entry = stage_matches[key]
                    entry["totalMatches"] += 1
                    entry["sources"][spec["id"]] += 1
                    if len(entry["examples"]) < 4:
                        entry["examples"].append(example)

        source_reports.append(
            {
                "id": spec["id"],
                "path": rel(spec["path"]),
                "kind": spec["kind"],
                "exists": True,
                "bytesScanned": len(data),
                **meta,
                "patternCounts": counts,
            }
        )
        del data

    report = {
        "generatedAt": datetime.now(timezone.utc).isoformat(),
        "generatedBy": rel(Path(__file__)),
        "principle": (
            "Challenge battle memory evidence can prove retained runtime data, but absence of strings does not prove "
            "absence of a load. Stage selection still needs DVDOpen/archive-open tracing if no selected st## string remains."
        ),
        "inputs": source_reports,
        "summary": {
            "stageArchiveStringMatches": pattern_totals["stageArchives"],
            "stageSetArchiveStringMatches": pattern_totals["stageSetArchives"],
            "stageHitBinStringMatches": pattern_totals["stageHitBins"],
            "borgAnimJointStringMatches": pattern_totals["borgAnimJoints"],
            "uniqueBorgAnimPrefixes": len(borg_matches),
            "stageSelectionStatus": (
                "unproven: no st##_mdl.arc, st##.pzz, set####.arc, hit###.bin, or comhit.bin strings were found "
                "in the scanned Challenge battle save-state payloads or MEM1 dumps"
            ),
        },
        "stageStringEvidence": compact_stage_matches(stage_matches),
        "borgAnimPrefixEvidence": compact_borg_matches(borg_matches, borgs),
        "supportingEvidence": [
            "research/decomp/ram-trace-analysis.md",
            "research/decomp/index/archive-load-xrefs.md",
            "research/asset-inventory/stage-code-evidence.md",
        ],
        "requiredNextTraceTasks": [
            "Use DVDOpen/gcCiOpen breakpoints from archive-load-xrefs to capture selected st## filenames during Challenge battle entry.",
            "Use active object spawn/init breakpoints to connect retained pl#### animation prefixes to live active borg object pointers.",
            "Do not treat resident pl####_b##_animjoint strings as a complete force roster until the object table is traced.",
        ],
    }

    OUT_JSON.parent.mkdir(parents=True, exist_ok=True)
    with OUT_JSON.open("w", encoding="utf-8", newline="\n") as fh:
        fh.write(json.dumps(report, indent=2) + "\n")
    with OUT_MD.open("w", encoding="utf-8", newline="\n") as fh:
        fh.write(render_markdown(report))

    print("challenge battle memory evidence")
    print(f"sources: {len(source_reports)}")
    print(f"stage archive strings: {report['summary']['stageArchiveStringMatches']}")
    print(f"borg anim prefixes: {report['summary']['uniqueBorgAnimPrefixes']}")
    print(f"wrote {rel(OUT_JSON)}")
    print(f"wrote {rel(OUT_MD)}")


def load_source(spec):
    if spec["kind"] == "mem1":
        data = spec["path"].read_bytes()
        return data, {
            "mem1StateOffset": 0,
            "mem1RamBase": hex(MEM1_RAM_BASE),
            "mem1BytesAvailable": len(data),
        }
    if spec["kind"] == "dolphin-sav":
        data, meta = decompress_dolphin_save(spec["path"])
        mem1_offset = find_mem1_base(data)
        meta["mem1StateOffset"] = mem1_offset
        meta["mem1RamBase"] = hex(MEM1_RAM_BASE) if mem1_offset is not None else None
        meta["mem1BytesAvailable"] = min(MEM1_SIZE, len(data) - mem1_offset) if mem1_offset is not None else 0
        return data, meta
    raise ValueError(f"unknown source kind: {spec['kind']}")


def decompress_dolphin_save(path):
    raw = path.read_bytes()
    version_len = struct.unpack_from("<I", raw, 0x1C)[0]
    version_offset = 0x20
    version = raw[version_offset : version_offset + version_len].decode("ascii", "replace")
    ext_offset = version_offset + version_len
    header_version, compression_type, payload_offset, uncompressed_size = struct.unpack_from("<HHIQ", raw, ext_offset)
    payload_start = ext_offset + 16 + payload_offset
    cursor = payload_start
    chunks = []
    out = bytearray()

    if compression_type != 1:
        raise ValueError(f"{rel(path)} uses unsupported compression type {compression_type}; expected Dolphin LZ4=1")

    while cursor + 4 <= len(raw):
        compressed_len = struct.unpack_from("<i", raw, cursor)[0]
        cursor += 4
        if compressed_len <= 0:
            break
        block = raw[cursor : cursor + compressed_len]
        cursor += compressed_len
        remaining = uncompressed_size - len(out)
        sizes_to_try = [remaining]
        if remaining > 32 * 1024 * 1024:
            sizes_to_try.extend([32 * 1024 * 1024, 16 * 1024 * 1024])
        decoded = None
        last_error = None
        for size in dict.fromkeys(sizes_to_try):
            try:
                decoded = lz4.block.decompress(block, uncompressed_size=size)
                break
            except Exception as exc:  # lz4 raises a module-specific C extension exception.
                last_error = exc
        if decoded is None:
            try:
                decoded = lz4.block.decompress(block)
            except Exception as exc:
                raise RuntimeError(f"could not decompress chunk {len(chunks)} from {rel(path)}: {last_error or exc}") from exc
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


def find_mem1_base(data):
    start = 0
    while True:
        offset = data.find(b"GG4E", start)
        if offset < 0:
            return None
        if offset + 0x20 <= len(data) and data[offset + 0x1C : offset + 0x20] == b"\xC2\x33\x9F\x3D":
            return offset
        start = offset + 1


def make_example(spec, data, offset, text, mem1_base):
    ram = None
    if mem1_base is not None and mem1_base <= offset < mem1_base + MEM1_SIZE:
        ram = hex(MEM1_RAM_BASE + offset - mem1_base)
    start = max(0, offset - 32)
    end = min(len(data), offset + len(text) + 32)
    return {
        "source": spec["id"],
        "stateOffset": hex(offset),
        "ramAddress": ram,
        "text": text,
        "context": sanitize(data[start:end]),
    }


def compact_stage_matches(stage_matches):
    out = []
    for key, entry in sorted(stage_matches.items()):
        out.append(
            {
                "id": key,
                "totalMatches": entry["totalMatches"],
                "sources": dict(sorted(entry["sources"].items())),
                "examples": entry["examples"],
            }
        )
    return out


def compact_borg_matches(borg_matches, borgs):
    out = []
    for borg_id, entry in sorted(borg_matches.items(), key=lambda item: (-item[1]["totalMatches"], item[0])):
        borg = borgs.get(borg_id, {})
        out.append(
            {
                "borgId": borg_id,
                "name": borg.get("name"),
                "tribe": borg.get("tribe"),
                "energy": borg.get("energy"),
                "hasModel": borg.get("hasModel"),
                "hasAnim": borg.get("hasAnim"),
                "totalMatches": entry["totalMatches"],
                "sources": dict(sorted(entry["sources"].items())),
                "boneNamesSeen": sorted(entry["bones"]),
                "examples": entry["examples"],
                "evidenceNote": note_for_borg(borg_id),
            }
        )
    return out


def note_for_borg(borg_id):
    if borg_id == "pl0615":
        return "Matches G RED, the active player borg named in research/decomp/ram-trace-analysis.md."
    return "Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot."


def load_borgs():
    data = json.loads(BORG_JSON.read_text(encoding="utf-8"))
    return {entry["id"].lower(): entry for entry in data.get("borgs", [])}


def render_markdown(report):
    lines = [
        "# Challenge Battle 1 Memory Evidence",
        "",
        f"Generated: {report['generatedAt']}",
        "",
        "## Principle",
        "",
        report["principle"],
        "",
        "## Summary",
        "",
    ]
    for key, value in report["summary"].items():
        lines.append(f"- {key}: {value}")
    lines.extend(["", "## Source Scans", ""])
    lines.append("| Source | Kind | Bytes scanned | MEM1 state offset | Stage archive strings | Borg joint strings |")
    lines.append("| --- | --- | ---: | --- | ---: | ---: |")
    for source in report["inputs"]:
        if not source.get("exists"):
            lines.append(f"| {source['id']} | {source['kind']} | missing | missing | 0 | 0 |")
            continue
        counts = source["patternCounts"]
        lines.append(
            f"| {source['id']} | {source['kind']} | {source['bytesScanned']} | "
            f"{hex_or_none(source.get('mem1StateOffset'))} | {counts['stageArchives']} | {counts['borgAnimJoints']} |"
        )
    lines.extend(["", "## Stage String Evidence", ""])
    if report["stageStringEvidence"]:
        lines.append("| ID | Matches | Sources | First example |")
        lines.append("| --- | ---: | --- | --- |")
        for item in report["stageStringEvidence"]:
            first = item["examples"][0] if item["examples"] else {}
            lines.append(
                f"| {item['id']} | {item['totalMatches']} | {format_sources(item['sources'])} | "
                f"{first.get('source', '')} {first.get('ramAddress') or first.get('stateOffset', '')} `{first.get('text', '')}` |"
            )
    else:
        lines.append(
            "No `st##_mdl.arc`, `st##.pzz`, `set####.arc`, `hit###.bin`, or `comhit.bin` strings were retained "
            "in the scanned Challenge battle memory/save-state payloads."
        )
    lines.extend(["", "## Borg Animation Prefix Evidence", ""])
    lines.append("| Borg | Name | Energy | Matches | Sources | Bones seen | Note |")
    lines.append("| --- | --- | ---: | ---: | --- | ---: | --- |")
    for item in report["borgAnimPrefixEvidence"]:
        lines.append(
            f"| {item['borgId']} | {item.get('name') or ''} | {item.get('energy') or ''} | "
            f"{item['totalMatches']} | {format_sources(item['sources'])} | {len(item['boneNamesSeen'])} | {item['evidenceNote']} |"
        )
    lines.extend(["", "## Required Next Trace Tasks", ""])
    for task in report["requiredNextTraceTasks"]:
        lines.append(f"- {task}")
    lines.append("")
    return "\n".join(lines)


def format_sources(sources):
    return "<br>".join(f"{key}: {value}" for key, value in sorted(sources.items()))


def hex_or_none(value):
    return "none" if value is None else hex(value)


def sanitize(data):
    allowed = set(string.printable) - {"\r", "\n", "\t", "\x0b", "\x0c"}
    return "".join(ch if ch in allowed else "." for ch in data.decode("latin1", "replace"))


def rel(path):
    return str(Path(path).resolve().relative_to(REPO_ROOT)).replace("\\", "/")


if __name__ == "__main__":
    main()
