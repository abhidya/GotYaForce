#!/usr/bin/env python3
"""Build research/decomp/data/oracle-registry.json — Phase 0 of the oracle-coverage
workstream (NEXT-STEPS.md "Oracle registry": map wasm units to reference
implementations / oracle strategies).

Deterministic analysis over:
  - research/decomp/generated/finish-game-port/wasm-units.json      (current queue)
  - research/decomp/generated/finish-game-port/wasm-units-skipped.json
  - research/decomp/ghidra-export/chunk_*.c + _index.tsv            (function bodies)
  - research/decomp/data/family-state-machine-coverage.json         (gap audit)
  - packages/**, apps/** .ts/.tsx/.mjs/.js                          (TS citations)

One record per exported ROM function; a ranked top-50 unit list; a summary of
oracle-ability by structural class x citation grade. Re-run to regenerate:

  python research/decomp/data/build_oracle_registry.py

(Python >= 3.8; run from repo root or anywhere — paths resolve from this file.)
"""

import bisect
import json
import os
import re
import sys
from collections import Counter, defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", ".."))

QUEUE_PATH = os.path.join(ROOT, "research", "decomp", "generated", "finish-game-port", "wasm-units.json")
SKIPPED_PATH = os.path.join(ROOT, "research", "decomp", "generated", "finish-game-port", "wasm-units-skipped.json")
INDEX_PATH = os.path.join(ROOT, "research", "decomp", "ghidra-export", "_index.tsv")
COVERAGE_PATH = os.path.join(ROOT, "research", "decomp", "data", "family-state-machine-coverage.json")
OUT_PATH = os.path.join(ROOT, "research", "decomp", "data", "oracle-registry.json")

TS_ROOTS = [os.path.join(ROOT, "packages"), os.path.join(ROOT, "apps")]
TS_EXTS = (".ts", ".tsx", ".mjs", ".js")
TS_SKIP_DIRS = {"node_modules", ".git", "dist", "build", "coverage", "out", ".next", ".turbo"}

MARKER_RX = re.compile(r"^// ==== ([0-9a-fA-F]{8})\s+(.+?) ====\s*$")
ZZ_RX = re.compile(r"^zz_([0-9a-f]{7})_$")
FUN_RX = re.compile(r"^FUN_([0-9a-fA-F]{8})$")
GLOBAL_RX = re.compile(r"\b(PTR_FUN|PTR_DAT|PTR_PTR|FLOAT|DOUBLE|DAT|UNK)_([0-9a-fA-F]{6,8})\b")
CALL_RX = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
IDENT_RX = re.compile(r"^[A-Za-z_]\w*$")

PORT_GRADE_RX = re.compile(r"port of|1:1|decoded", re.I)
UNPORTED_GRADE_RX = re.compile(r"unported|no-op|stub", re.I)
GRADE_CONTEXT = 3  # lines of context either side of a citation

CLASS_RANK = {"A": 0, "B": 1, "C": 2, "D": 3, "E": 4}


def addr_from_name(name):
    m = ZZ_RX.match(name)
    if m:
        return 0x80000000 + int(m.group(1), 16)
    m = FUN_RX.match(name)
    if m:
        return int(m.group(1), 16)
    return None


def is_ambiguous_ts_name(name):
    """Names like start/free/floor/strlen/sprintf would false-positive all over a
    TS codebase; skip citation scanning for short plain lowercase identifiers."""
    return bool(re.fullmatch(r"[a-z][a-z0-9]*", name)) and len(name) <= 8


def split_params(paramtext):
    """Split a C parameter list on top-level commas."""
    parts, depth, cur = [], 0, []
    for ch in paramtext:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    tail = "".join(cur).strip()
    if tail:
        parts.append(tail)
    if parts == ["void"]:
        return []
    return parts


def parse_signature(text, name):
    """Extract (return_type, params list) from a prototype/definition snippet."""
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", " ", text)
    m = re.search(r"([\w\s\*]+?[\s\*])" + re.escape(name) + r"\s*\((.*)\)", text, re.S)
    if not m:
        return None
    ret = " ".join(m.group(1).split()).strip()
    params = split_params(" ".join(m.group(2).split()))
    return {"return_type": ret, "params": params}


def load_chunks(queue_units):
    """Read each referenced chunk file once; return {relpath: lines} and marker index."""
    files = sorted({e["file"] for u in queue_units for e in u["extractions"]})
    chunks, markers = {}, {}
    for rel in files:
        with open(os.path.join(ROOT, rel), encoding="utf-8", errors="replace") as fh:
            lines = fh.read().splitlines()
        chunks[rel] = lines
        idx = {}
        for i, ln in enumerate(lines, 1):
            m = MARKER_RX.match(ln)
            if m:
                idx[i] = (int(m.group(1), 16), m.group(2))
        markers[rel] = idx
    return chunks, markers


def build_universe():
    universe = {}
    with open(INDEX_PATH, encoding="utf-8") as fh:
        header = fh.readline()
        for row in fh:
            parts = row.rstrip("\n").split("\t")
            if len(parts) < 3:
                continue
            addr, name, chunk = parts[0], parts[1], parts[2]
            if IDENT_RX.match(name):
                universe[name] = int(addr, 16)
    return universe


def scan_ts_citations(scannable_names):
    """One pass over packages/apps sources; returns {name: [(relpath, line, grade)]}."""
    zzfun_rx = re.compile(r"\b(zz_[0-9a-f]{7}_|FUN_[0-9a-fA-F]{8})\b")
    other = sorted(n for n in scannable_names
                   if not ZZ_RX.match(n) and not FUN_RX.match(n))
    other_rx = None
    if other:
        other_rx = re.compile(r"\b(" + "|".join(re.escape(n) for n in other) + r")\b")
    hits = defaultdict(list)
    for root in TS_ROOTS:
        if not os.path.isdir(root):
            continue
        for dirpath, dirnames, filenames in os.walk(root):
            dirnames[:] = sorted(d for d in dirnames if d not in TS_SKIP_DIRS)
            for fn in sorted(filenames):
                if not fn.endswith(TS_EXTS):
                    continue
                path = os.path.join(dirpath, fn)
                rel = os.path.relpath(path, ROOT).replace("\\", "/")
                try:
                    with open(path, encoding="utf-8", errors="replace") as fh:
                        lines = fh.read().splitlines()
                except OSError:
                    continue
                for i, line in enumerate(lines):
                    found = set()
                    for m in zzfun_rx.finditer(line):
                        if m.group(1) in scannable_names:
                            found.add(m.group(1))
                    if other_rx and other_rx.search(line):
                        for m in other_rx.finditer(line):
                            found.add(m.group(1))
                    if not found:
                        continue
                    lo = max(0, i - GRADE_CONTEXT)
                    hi = min(len(lines), i + GRADE_CONTEXT + 1)
                    ctx = "\n".join(lines[lo:hi])
                    if PORT_GRADE_RX.search(ctx):
                        grade = "port"
                    elif UNPORTED_GRADE_RX.search(ctx):
                        grade = "unported"
                    else:
                        grade = "weak"
                    for name in found:
                        hits[name].append((rel, i + 1, grade))
    return hits


def structural_class(callee_count, has_globals, has_ptr_args, returns_value):
    if callee_count == 0:
        if not returns_value:
            return "C"
        if not has_globals and not has_ptr_args:
            return "A"
        return "B"
    return "D" if callee_count <= 2 else "E"


def main():
    queue = json.load(open(QUEUE_PATH, encoding="utf-8"))
    skipped = json.load(open(SKIPPED_PATH, encoding="utf-8"))
    coverage = json.load(open(COVERAGE_PATH, encoding="utf-8"))
    units = queue["units"]

    universe = build_universe()
    chunks, markers = load_chunks(units)

    # --- family gap neighborhoods -------------------------------------------
    fams = []
    for fam in coverage["families"]:
        ctor = int(fam["constructorAddress"], 16)
        partial = sum(1 for a in fam["actions"] if a["status"] == "partial")
        fams.append({"ctor": ctor, "partial_slots": partial,
                     "members": fam.get("members", [])})
    fams.sort(key=lambda f: f["ctor"])
    ctor_addrs = [f["ctor"] for f in fams]
    spans = [b - a for a, b in zip(ctor_addrs, ctor_addrs[1:])]
    last_cap = ctor_addrs[-1] + max(spans)  # deterministic bound for the final neighborhood

    def gap_alignment(addr):
        if addr is None or addr < ctor_addrs[0]:
            return None
        i = bisect.bisect_right(ctor_addrs, addr) - 1
        if i == len(ctor_addrs) - 1 and addr >= last_cap:
            return None
        fam = fams[i]
        return {"family_ctor": "0x%08x" % fam["ctor"],
                "partial_slots": fam["partial_slots"],
                "members": fam["members"]}

    # --- exported-function names, ambiguity filter --------------------------
    all_names = [f for u in units for f in u["exported_functions"]]
    scannable = {n for n in all_names if not is_ambiguous_ts_name(n)}
    ts_hits = scan_ts_citations(scannable)

    # --- per-function records ------------------------------------------------
    functions = []
    anomalies = []
    unit_agg = {}
    for unit in units:
        exported = unit["exported_functions"]
        extractions = unit["extractions"]
        if len(exported) != len(extractions):
            anomalies.append("unit %s: %d exports vs %d extractions" %
                             (unit["name"], len(exported), len(extractions)))
            continue
        prelude_text = "\n".join(unit.get("prelude", []))
        agg = unit_agg[unit["name"]] = {
            "unit": unit["name"],
            "oracle_kind": (unit.get("oracle") or {}).get("type")
                           or ("command" if (unit.get("oracle") or {}).get("command") else None),
            "functions": [], "total_loc": 0, "class_ranks": [],
            "port_citation_total": 0, "port_fn_count": 0,
            "citation_total": 0, "gap_partials": [], "gap_ctors": set(),
            "aligned_fn_count": 0,
        }
        for name, ext in zip(exported, extractions):
            rel, start, end = ext["file"], ext["start"], ext["end"]
            lines = chunks[rel][start - 1:end]
            marker = markers[rel].get(start)
            marker_addr = marker[0] if marker else None
            if marker and marker[1] != name:
                anomalies.append("%s @ %s:%d marker says %s" % (name, rel, start, marker[1]))
            addr = addr_from_name(name)
            if addr is None:
                addr = marker_addr if marker_addr is not None else universe.get(name)
            elif marker_addr is not None and addr != marker_addr:
                # renamed/moved symbol: the chunk marker (and _index.tsv) are
                # ground truth, the zz_ digits are historical
                anomalies.append("%s: name addr %08x != marker %08x (marker wins)"
                                 % (name, addr, marker_addr))
                addr = marker_addr

            # split signature text vs body at the first '{'
            brace_i = next((i for i, ln in enumerate(lines) if "{" in ln), len(lines))
            sig_lines = lines[1:brace_i] if marker else lines[:brace_i]
            body = "\n".join(lines[brace_i:])
            sig = parse_signature("\n".join(sig_lines) + " {", name) \
                or parse_signature(prelude_text, name)
            ret = sig["return_type"] if sig else None
            params = sig["params"] if sig else None
            returns_value = (ret is not None) and not (ret == "void")
            has_ptr_args = bool(params) and any("*" in p for p in params)

            callees = sorted({m.group(1) for m in CALL_RX.finditer(body)
                              if m.group(1) != name and m.group(1) in universe})
            seen_globals, global_refs = set(), []
            for m in GLOBAL_RX.finditer(body):
                sym = m.group(0)
                if sym in seen_globals:
                    continue
                seen_globals.add(sym)
                prefix = m.group(1)
                global_refs.append({"symbol": sym, "prefix_type": prefix,
                                    "width_known": prefix not in ("DAT", "UNK")})

            cites = ts_hits.get(name, [])
            grades = [g for (_, _, g) in cites]
            if name not in scannable:
                grade, scan_skipped = None, "ambiguous_name"
            elif "port" in grades:
                grade, scan_skipped = "port", None
            elif "unported" in grades:
                grade, scan_skipped = "unported", None
            elif grades:
                grade, scan_skipped = "weak", None
            else:
                grade, scan_skipped = "none", None

            loc = end - start + 1
            sclass = structural_class(len(callees), bool(global_refs),
                                      has_ptr_args, returns_value)
            gap = gap_alignment(addr)
            rec = {
                "name": name,
                "address": ("0x%08x" % addr) if addr is not None else None,
                "unit": unit["name"],
                "chunk_file": rel,
                "line_range": [start, end],
                "loc": loc,
                "return_type": ret,
                "params": params,
                "returns_value": returns_value,
                "has_pointer_args": has_ptr_args,
                "external_callees": {"count": len(callees), "list": callees},
                "global_refs": global_refs,
                "structural_class": sclass,
                "ts_citations": [{"where": "%s:%d" % (f, l), "grade": g}
                                 for (f, l, g) in cites],
                "citation_grade": grade,
                "citation_scan_skipped": scan_skipped,
                "gap_alignment": gap,
            }
            functions.append(rec)

            agg["functions"].append(name)
            agg["total_loc"] += loc
            agg["class_ranks"].append(CLASS_RANK[sclass])
            agg["citation_total"] += len(cites)
            port_cites = grades.count("port")
            agg["port_citation_total"] += port_cites
            if grade == "port":
                agg["port_fn_count"] += 1
            if gap:
                agg["aligned_fn_count"] += 1
                agg["gap_partials"].append(gap["partial_slots"])
                agg["gap_ctors"].add(gap["family_ctor"])

    functions.sort(key=lambda r: (r["address"] or "zzzz", r["name"]))

    # --- unit ranking --------------------------------------------------------
    ranked = []
    for name, a in unit_agg.items():
        gap_partial = max(a["gap_partials"]) if a["gap_partials"] else 0
        max_rank = max(a["class_ranks"]) if a["class_ranks"] else 4
        ranked.append({
            "unit": name,
            "oracle_kind": a["oracle_kind"],
            "fn_count": len(a["functions"]),
            "gap_partial_slots": gap_partial,
            "gap_family_ctors": sorted(a["gap_ctors"]),
            "port_citations": a["port_citation_total"],
            "port_grade_fns": a["port_fn_count"],
            "total_citations": a["citation_total"],
            "max_structural_class": "ABCDE"[max_rank],
            "total_loc": a["total_loc"],
            "fully_gap_aligned": a["aligned_fn_count"] == len(a["functions"])
                                 and len(a["functions"]) > 0,
        })
    ranked.sort(key=lambda r: (-r["gap_partial_slots"], -r["port_citations"],
                               CLASS_RANK[r["max_structural_class"]],
                               r["total_loc"], r["unit"]))
    ranked_units = ranked[:50]

    # --- oracle-ability buckets (unit level) --------------------------------
    buckets = {"differential_vs_ts": [], "state_diff": [],
               "citations_no_family": [], "trace_only": []}
    for r in ranked:
        if r["port_grade_fns"] > 0:
            buckets["differential_vs_ts"].append(r["unit"])
        elif r["total_citations"] > 0 and r["gap_family_ctors"]:
            buckets["state_diff"].append(r["unit"])
        elif r["total_citations"] > 0:
            buckets["citations_no_family"].append(r["unit"])
        else:
            buckets["trace_only"].append(r["unit"])

    # --- summary -------------------------------------------------------------
    matrix = defaultdict(Counter)
    for rec in functions:
        g = rec["citation_grade"] or "ambiguous_name"
        matrix[rec["structural_class"]][g] += 1
    class_by_grade = {c: dict(sorted(matrix[c].items())) for c in sorted(matrix)}
    fully_aligned_units = sorted(r["unit"] for r in ranked if r["fully_gap_aligned"])

    excluded = []
    for chunk, entries in sorted(skipped.get("skipped_by_chunk", {}).items()):
        for e in entries:
            excluded.append({"name": e["name"], "address": "0x" + e["addr"],
                             "chunk": chunk, "reason": e["reason"]})

    summary = {
        "functions_total": len(functions),
        "units_total": len(unit_agg),
        "excluded_total": len(excluded),
        "excluded_reasons": dict(Counter(e["reason"] for e in excluded)),
        "structural_class_counts": dict(Counter(r["structural_class"] for r in functions)),
        "citation_grade_counts": dict(Counter((r["citation_grade"] or "ambiguous_name")
                                              for r in functions)),
        "class_by_citation_grade": class_by_grade,
        "gap_aligned_functions": sum(1 for r in functions if r["gap_alignment"]),
        "gap_aligned_functions_partial_family": sum(
            1 for r in functions
            if r["gap_alignment"] and r["gap_alignment"]["partial_slots"] > 0),
        "fully_gap_aligned_units": len(fully_aligned_units),
        "fully_gap_aligned_unit_names": fully_aligned_units,
        "oracle_able_units": {k: len(v) for k, v in buckets.items()},
        "oracle_able_unit_names": buckets,
        "anomalies": anomalies,
    }

    meta = {
        "generated_by": "research/decomp/data/build_oracle_registry.py",
        "inputs": {
            "queue": os.path.relpath(QUEUE_PATH, ROOT).replace("\\", "/"),
            "skipped": os.path.relpath(SKIPPED_PATH, ROOT).replace("\\", "/"),
            "chunk_index": os.path.relpath(INDEX_PATH, ROOT).replace("\\", "/"),
            "family_coverage": os.path.relpath(COVERAGE_PATH, ROOT).replace("\\", "/"),
        },
        "conventions": {
            "address": "zz_XXXXXXX_ -> 0x80000000+offset; FUN_80XXXXXX -> literal; else chunk marker/_index.tsv",
            "structural_class": "A leaf value-returning no globals/ptr-args; B leaf value-returning with globals or ptr args; C leaf void; D 1-2 callees; E 3+ callees",
            "citation_grade": "port: /port of|1:1|decoded/i within +-3 lines; unported: /unported|no-op|stub/i within +-3 lines; weak: cited without either; none: no citations; ambiguous_name: name too generic to token-search (libc-style short lowercase)",
            "gap_alignment": "family constructor neighborhoods [ctor, next_ctor) from family-state-machine-coverage.json; final neighborhood capped at last ctor + max inter-ctor span",
            "ranked_units_sort": "(gap_partial_slots desc, port_citations desc, max_structural_class asc, total_loc asc, unit asc)",
            "oracle_able_units": "differential_vs_ts: >=1 port-grade fn; state_diff: citations but no port-grade, gap family exists; citations_no_family: citations, no gap family; trace_only: no citations",
        },
    }

    with open(OUT_PATH, "w", encoding="utf-8", newline="\n") as fh:
        fh.write("{\n")
        fh.write('"meta": %s,\n' % json.dumps(meta, indent=1))
        fh.write('"summary": %s,\n' % json.dumps(summary, indent=1))
        fh.write('"ranked_units": %s,\n' % json.dumps(ranked_units, indent=1))
        fh.write('"functions": [\n')
        for i, rec in enumerate(functions):
            fh.write(json.dumps(rec, separators=(",", ":")))
            fh.write(",\n" if i < len(functions) - 1 else "\n")
        fh.write('],\n')
        fh.write('"excluded": %s\n' % json.dumps(excluded, indent=1))
        fh.write("}\n")

    print("functions:", len(functions), "units:", len(unit_agg),
          "excluded:", len(excluded), "anomalies:", len(anomalies))
    print("classes:", summary["structural_class_counts"])
    print("grades:", summary["citation_grade_counts"])
    print("oracle-able:", summary["oracle_able_units"])
    print("wrote", OUT_PATH)


if __name__ == "__main__":
    sys.exit(main())
