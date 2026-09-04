#!/usr/bin/env python3
"""census.py -- measure the matching-decompilation compiler against THIS corpus.

The spike (docs/matching-decompilation-spike.md) matched 13 functions and named
five compiler blockers.  Both numbers came from a handful of functions chosen by
hand.  This tool answers the question those numbers cannot: **across all 12,062
entry points, what fraction of this game's code can the compiler ingest at all,
and what stops the rest** -- counted in instructions, never only in functions.

It is read-only on the corpus.  It writes two artifacts:

    research/decomp/data/matching-compiler-census.json
    docs/matching-compiler-census.md

Four passes, in order:

  1. COMPILE-ABILITY.  For every entry point, slice its verbatim Ghidra C out of
     research/decomp/ghidra-export/, materialise it as a single translation unit
     the way the port driver does (the gnt4_shim typedef block, `code` for
     indirect dispatch, extern declarations for callees and address-named
     globals), and feed it to mwcc-rs.  Classify the result.  This does NOT ask
     whether the bytes match -- it asks whether the compiler can ingest the
     SHAPE of this game's code.
  2. REFUSAL BUCKETS.  Group the failures by the compiler's own diagnostic,
     normalised into a construct key, ranked by instructions blocked.
  3. NEAR-MATCH PROBE.  Every function that compiles is run through the oracle
     (objdiff, the same one match.py uses) against the retail bytes.  One shot,
     no iteration: this measures how far verbatim Ghidra C gets on its own.
  4. SHAPE SHARING.  Cluster every entry point by its masked instruction
     sequence (mnemonics only -- registers, immediates and branch targets
     dropped) and report how few distinct shapes cover 50 / 80 / 95 % of the
     functions and of the instructions.

Reproduction (one command):

    python research/tools/matching-decomp/census.py

Drift check, writes nothing, exit 1 if the tree no longer produces the committed
numbers (the same contract build_tier_survey.py has):

    python research/tools/matching-decomp/census.py --check

`MWCC_RS=<path to mwcc.exe>` selects the compiler; without it the search list in
match.py applies.  Nothing is downloaded and no model is contacted.

HONESTY NOTE, because this measurement has a floor it cannot see past: a
translation unit assembled by regex from one decompiled function is NOT the
original translation unit.  Where this tool declares a global `extern int` and
the code wanted a pointer, the refusal is the harness's, not the compiler's.
Every such class is bucketed separately and reported as `harness`, never folded
into the compiler's score.  The compiler-capability numbers quoted in the report
are the `frontend` + `codegen` classes only.
"""
from __future__ import annotations

import argparse
import datetime
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
from collections import Counter, defaultdict
from pathlib import Path


def write_text(path, text, encoding="utf-8"):
    """Path.write_text(newline=) is 3.10+; this runs on the 3.7 that has capstone."""
    import io
    with io.open(str(path), "w", encoding=encoding, newline="\n") as fh:
        fh.write(text)

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from dolsym import Dol, SymbolMap  # noqa: E402
from ppcdis import disasm_word  # noqa: E402
from objdiff import Elf32BE, compare  # noqa: E402
import match as matchmod  # noqa: E402

PRODUCT_ROOT = HERE.parents[2]

INDEX_REL = "research/decomp/ghidra-export/_index.tsv"
REGISTRY_REL = "research/decomp/data/oracle-registry.json"
MAP_REL = "research/symbols/GG4E-CSM-20220412.map"
SHIM_SEED_REL = "research/decomp/generated/finish-game-port/gnt4_shim_seed.h"
OUT_JSON_REL = "research/decomp/data/matching-compiler-census.json"
OUT_MD_REL = "docs/matching-compiler-census.md"

BUILD_LABEL = "2.7"

# ---------------------------------------------------------------- corpus text

MARKER_RX = re.compile(r"^// ==== ([0-9a-fA-F]{8})\s+(.+?) ====\s*$")
IDENT_RX = re.compile(r"^[A-Za-z_]\w*$")
# Ghidra's address-suffixed globals: DAT_80436498, PTR_FUN_804335b8,
# FLOAT_80436f68, s_Hello_802c1234, _DAT_80000034.  Function names are excluded
# by subtracting the corpus universe; `zz_00122c8_` cannot match because it ends
# in an underscore, which is a word character, so the trailing \b never fires.
GLOBAL_RX = re.compile(r"\b([A-Za-z_]\w*_[0-9a-f]{6,8})\b")
CALL_RX = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
COMMENT_RX = re.compile(r"/\*.*?\*/", re.S)
LINE_COMMENT_RX = re.compile(r"//[^\n]*")
STRING_RX = re.compile(r'"(?:\\.|[^"\\])*"')
CHARLIT_RX = re.compile(r"'(?:\\.|[^'\\])*'")

C_KEYWORDS = set("""auto break case char const continue default do double else enum
extern float for goto if inline int long register return short signed sizeof static
struct switch typedef union unsigned void volatile while""".split())

# Types the shim block provides; never re-declared as globals.
SHIM_TYPES = set("""undefined undefined1 undefined2 undefined4 undefined8 byte ushort
uint ulong ulonglong longlong code bool""".split())

# Ghidra's synthetic "value that was already in a register" names.  They appear
# in the body's own declaration block, so they need nothing here, but they are
# listed so a stray one is never mistaken for a global.
GHIDRA_PSEUDO_PREFIXES = ("in_", "extraout_", "unaff_", "__return_")


def strip_code(text):
    """Comments, strings and char literals blanked, for identifier scanning."""
    text = COMMENT_RX.sub(" ", text)
    text = LINE_COMMENT_RX.sub(" ", text)
    text = STRING_RX.sub('""', text)
    text = CHARLIT_RX.sub("' '", text)
    return text


def parse_signature(text, name):
    """The Ghidra return type of `name`, or None."""
    t = strip_code(text)
    m = re.search(r"([\w\s\*]+?[\s\*])" + re.escape(name) + r"\s*\(", t)
    if not m:
        return None
    return " ".join(m.group(1).split()).strip()


DEF_RX = re.compile(r"([A-Za-z_]\w*)\s*\(")


def definition_name(text):
    """The C identifier the block actually defines.

    The export's marker carries the RAW link-map symbol, which is often not a C
    identifier at all (`gnt4-memset`, `cCameraManager::HasCamera(cBaseCamera`).
    Ghidra sanitises it in the definition it emits, and that sanitised spelling
    is what every call site in the corpus uses -- so it, not the marker, is the
    function's name for compilation purposes.
    """
    t = strip_code(text)
    head = t.split("{", 1)[0]
    last = None
    for m in DEF_RX.finditer(head):
        tok = m.group(1)
        if tok in C_KEYWORDS:
            continue
        last = tok
        break
    return last


def load_chunks(repo):
    """{addr: {'name','chunk','text'}} for every function in the Ghidra export."""
    index = repo / INDEX_REL
    rows = []
    with index.open(encoding="utf-8") as fh:
        fh.readline()
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 3:
                rows.append((int(parts[0], 16), parts[1], parts[2]))
    by_chunk = defaultdict(list)
    for addr, name, chunk in rows:
        by_chunk[chunk].append((addr, name))

    out = {}
    base = repo / "research" / "decomp" / "ghidra-export"
    for chunk in sorted(by_chunk):
        path = base / chunk
        if not path.is_file():
            continue
        raw = path.read_text(encoding="utf-8", errors="replace")
        lines = raw.splitlines()
        marks = []
        for i, ln in enumerate(lines):
            m = MARKER_RX.match(ln)
            if m:
                marks.append((i, int(m.group(1), 16), m.group(2)))
        for j, (i, addr, name) in enumerate(marks):
            end = marks[j + 1][0] if j + 1 < len(marks) else len(lines)
            body = "\n".join(lines[i + 1:end]).strip("\n")
            out[addr] = {"map_name": name, "name": definition_name(body) or name,
                         "chunk": chunk, "text": body, "line": i + 1}
    return out


# ------------------------------------------------------------- entry points

def entry_points(repo, dol, smap):
    """The same 12,062-entry universe leaf_census.py builds, same extent rule."""
    reg = json.loads((repo / REGISTRY_REL).read_text(encoding="utf-8"))
    entries = {}
    for f in reg["functions"]:
        entries[int(f["address"], 16)] = f["name"]
    for f in reg.get("excluded", []):
        entries.setdefault(int(f["address"], 16), f["name"])
    for r in smap.text_functions():
        entries.setdefault(r["addr"], r["name"])

    addrs = sorted(a for a in entries if dol.is_text(a))

    def sect_end(addr):
        for _off, adr, sz in dol.text:
            if adr <= addr < adr + sz:
                return adr + sz
        return addr

    out = []
    for i, addr in enumerate(addrs):
        nxt = addrs[i + 1] if i + 1 < len(addrs) else sect_end(addr)
        size = min(nxt, sect_end(addr)) - addr
        size -= size % 4
        if size <= 0:
            continue
        # The link map states a function's extent where it knows one; the
        # next-entry-point cap is the fallback and can swallow alignment padding.
        rec = smap.by_addr.get(addr)
        map_size = rec["size"] if (rec and rec["section"] == ".text"
                                   and 0 < rec["size"] <= size) else None
        blob = dol.read(addr, size)
        if blob is None:
            continue
        out.append({"addr": addr, "name": entries[addr], "size": size,
                    "insns": size // 4, "map_size": map_size, "bytes": blob})
    return out


# ------------------------------------------------------------ materialisation

def local_names(text):
    """Identifiers the function declares itself (params + local block)."""
    t = strip_code(text)
    names = set()
    # parameter list
    m = re.search(r"\(([^)]*)\)\s*\n?\s*\{", t, re.S)
    if m:
        for tok in re.findall(r"\b([A-Za-z_]\w*)\b(?=\s*(?:\[|,|\)|$))", m.group(1)):
            names.add(tok)
    # declaration block: `type name;` / `type *name;` / `type name [n];`
    for ln in t.splitlines():
        s = ln.strip()
        dm = re.match(r"^[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\**\s*"
                      r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;$", s)
        if dm:
            names.add(dm.group(1))
    for tok in re.findall(r"\b(in_\w+|extraout_\w+|unaff_\w+|__return_\w+)\b", t):
        names.add(tok)
    return names


def global_decl(name):
    """One extern declaration for an address-named Ghidra global.

    Widths follow Ghidra's own naming prefix.  Everything unprefixed becomes an
    `int`, which is the single most common shape and the honest default: where
    the code wanted a pointer, the resulting diagnostic is the harness's fault
    and is bucketed as such.
    """
    if name.startswith("FLOAT_"):
        return "extern float %s;" % name
    if name.startswith("DOUBLE_"):
        return "extern double %s;" % name
    if name.startswith("PTR_"):
        return "extern void *%s;" % name
    if name.startswith(("s_", "e_", "u_")):
        return "extern char %s[];" % name
    return "extern int %s;" % name


PROLOGUE = """/* GENERATED BY research/tools/matching-decomp/census.py -- DO NOT EDIT.
 * One entry point's VERBATIM Ghidra C, materialised as a translation unit.
 * Nothing below the declaration block is rewritten.
 *
 * census_shim.h is INLINED rather than #included, and that is not a style
 * choice: mwcc-rs does not admit a typedef name that arrived through an
 * #include as the return type of a file-scope function definition
 * (`undefined *f(int)` -> "expected a type, found Identifier(\\"undefined\\")"),
 * while the identical text pasted into the .c compiles.  Since roughly a third
 * of Ghidra's functions return a placeholder type, leaving it as an #include
 * would have charged that harness artifact to the corpus. */
"""


def materialise(self_name, text, universe, sigs, shim_names, shim_text,
                extra_globals=(), extra_types=()):
    """The translation unit fed to the compiler."""
    scan = strip_code(text)
    locals_ = local_names(text)

    callees = set()
    for tok in CALL_RX.findall(scan):
        if tok in C_KEYWORDS or tok in SHIM_TYPES or tok == self_name:
            continue
        if tok in locals_ or tok in shim_names:
            continue
        if tok in universe:
            callees.add(tok)

    globals_ = set()
    for tok in GLOBAL_RX.findall(scan):
        if (tok in universe or tok in locals_ or tok in shim_names
                or tok in C_KEYWORDS or tok in SHIM_TYPES or tok == self_name):
            continue
        if tok.startswith(GHIDRA_PSEUDO_PREFIXES):
            continue
        globals_.add(tok)
    globals_ |= set(extra_globals) - shim_names - universe

    parts = [PROLOGUE, shim_text, "\n"]
    if extra_types:
        parts.append("/* class/struct type names Ghidra used and the export "
                     "never defines;\n * incomplete on purpose -- anything that "
                     "dereferences one still fails honestly. */\n")
        for t in sorted(extra_types):
            parts.append("typedef struct %s_census_opaque %s;\n" % (t, t))
        parts.append("\n")
    if globals_:
        parts.append("/* address-named globals referenced by this function */\n")
        for g in sorted(globals_):
            parts.append(global_decl(g) + "\n")
        parts.append("\n")
    if callees:
        parts.append("/* callees: return type from the callee's own Ghidra\n"
                     " * signature, parameter list deliberately UNPROTOTYPED --\n"
                     " * Ghidra's per-function argument lists disagree with its\n"
                     " * own call sites often enough that prototyping them would\n"
                     " * measure the decompiler, not the compiler. */\n")
        for c in sorted(callees):
            ret = sigs.get(c) or "int"
            if ret in ("", "void"):
                parts.append("extern void %s();\n" % c)
            else:
                parts.append("extern %s %s();\n" % (ret, c))
        parts.append("\n")
    parts.append(text)
    parts.append("\n")
    return "".join(parts)


# ------------------------------------------------------------- classification

UNKNOWN_VAR_RX = re.compile(r"unknown (?:variable|function|identifier) '([^']+)'")

# Message -> (class, construct).  `class` is one of:
#   codegen  -- the compiler parsed it and cannot lower it: a real capability gap
#   frontend -- the compiler refused to parse/typecheck it: also a real gap when
#               the construct is legal C, which every one of these is
#   harness   -- an artifact of assembling a TU by regex, NOT a compiler limit
#   tooling   -- the run itself failed (timeout, crash of the driver)
CLASS_RULES = [
    ("panicked at", "panic", "compiler panic"),
    ("not implemented yet", "codegen", None),
    ("roadmap", "codegen", None),
    ("a general register was requested for a non-leaf expression", "codegen",
     "AND/arith against a constant that is not an rlwinm mask"),
    ("branchless compare idioms", "codegen",
     "comparison against a large constant"),
    ("pointer leaf access needs a pointer variable", "codegen",
     "type-punning cast through a struct member"),
    ("Shift-JIS", "harness", "source contains non-Shift-JIS characters"),
    ("unknown variable", "harness", "identifier the harness failed to declare"),
    ("unknown function", "harness", "callee the harness failed to declare"),
]


def normalise_message(msg):
    """Collapse a diagnostic to a construct key: identifiers and numbers out."""
    m = msg.strip().splitlines()
    line = ""
    for ln in m:
        ln = ln.strip()
        if ln and not ln.startswith("warning"):
            line = ln
            break
    if not line and m:
        line = m[0].strip()
    line = re.sub(r"^mwcc:\s*", "", line)
    line = re.sub(r"\(in function '[^']*'\)", "", line)
    line = re.sub(r'Variable\("[^"]*"\)', 'Variable("X")', line)
    # mwcc-rs appends the offending AST node to many diagnostics.  Two functions
    # blocked by the same missing lowering print different ASTs, so leaving them
    # in shatters one roadmap item into fifty rows.  The message head is the
    # construct; the AST is an example of it and lives in `example_message`.
    line = re.split(r"\s*\((?:in structured|while evaluating|inside structured)",
                    line)[0]
    line = re.split(r":\s*(?:Cast|Store|Binary|Unary|Dereference|Variable|"
                    r"AddressOf|Call|Assignment|Member|Index|IntegerLiteral|"
                    r"FloatLiteral|Load|Return|Conditional)\b", line)[0]
    line = re.sub(r"'[^']*'", "'X'", line)
    line = re.sub(r"\b0x[0-9a-fA-F]+\b", "N", line)
    line = re.sub(r"\b\d+\b", "N", line)
    line = re.sub(r"[A-Za-z_]\w*\(\d+\)", "X(N)", line)
    line = re.sub(r"\s+", " ", line).strip()
    return line[:200]


MEMBER_ON_GLOBAL_RX = re.compile(
    r"member '[^']*' on a non-struct-pointer base: Variable\(\"([A-Za-z_]\w*_[0-9a-f]{6,8})\"\)")


def classify(rc, log):
    """(status, klass, construct) for one compile result."""
    low = log.lower()
    if "panicked at" in low or "rust_backtrace" in low:
        return "CODEGEN_PANIC", "panic", normalise_message(log)
    if MEMBER_ON_GLOBAL_RX.search(log):
        # Ghidra typed that global as a struct; this tool declared it `extern
        # int` because the export carries no type for it.  The compiler is
        # right and the harness is wrong -- never charge this to the compiler.
        return ("HARNESS_SHIM_GAP", "harness",
                "struct member on a global this tool could only declare as int")
    for needle, klass, label in CLASS_RULES:
        if needle.lower() in low:
            construct = label or normalise_message(log)
            status = {"codegen": "CODEGEN_UNSUPPORTED",
                      "harness": "HARNESS_SHIM_GAP",
                      "panic": "CODEGEN_PANIC"}[klass]
            return status, klass, construct
    return "FRONT_END_REFUSAL", "frontend", normalise_message(log)


# ------------------------------------------------------------------- compiling

class Compiler(object):
    def __init__(self, exe, build=BUILD_LABEL):
        self.exe = str(exe)
        self.build = build
        self.cflags = list(matchmod.DEFAULT_CFLAGS_RS)

    def run(self, src_path, obj_path, timeout=60):
        cmd = ([self.exe, "-c", str(src_path), "-o", str(obj_path),
                "--build", self.build] + self.cflags)
        try:
            r = subprocess.run(cmd, capture_output=True, timeout=timeout)
        except subprocess.TimeoutExpired:
            return None, "TIMEOUT after %ds" % timeout, 124
        log = (r.stdout + r.stderr).decode("latin1", "replace")
        ok = r.returncode == 0 and Path(obj_path).exists()
        return (obj_path if ok else None), log, r.returncode


MAX_SHIM_ROUNDS = 12

TEMPLATE_NAME_RX = re.compile(r"[A-Za-z_]\w*<[^>\s]*>")

MISSING_TYPE_RX = re.compile(r"expected Semicolon, found Identifier\(\"[^\"]+\"\)"
                             r".*?\(line (\d+), column")
DECL_LINE_RX = re.compile(r"^([A-Za-z_]\w*)\s+\**\s*[A-Za-z_]\w*"
                          r"(?:\s*\[[^\]]*\])?\s*;$")


def missing_type_name(log, tu):
    """A class/struct name Ghidra used in a declaration and never defined.

    `cBaseCamera *pcVar1;` parses as two identifiers unless `cBaseCamera` is a
    type, and the export defines no types at all.  Declaring it opaque is the
    same mechanical shim the port driver applies, and it turns a harness gap
    into either a compile or an honest compiler diagnostic.
    """
    m = MISSING_TYPE_RX.search(log)
    if not m:
        return None
    rows = tu.splitlines()
    ln = int(m.group(1))
    if not (0 < ln <= len(rows)):
        return None
    dm = DECL_LINE_RX.match(rows[ln - 1].strip())
    if not dm:
        return None
    name = dm.group(1)
    if name in C_KEYWORDS or name in SHIM_PROVIDED:
        return None
    return name


_WORKER = {}


def worker_init(exe, shim_text, universe_l, sigs, defnames, iso_str, map_str,
                build):
    _WORKER["cc"] = Compiler(exe, build)
    _WORKER["shim"] = shim_text
    _WORKER["universe"] = set(universe_l)
    _WORKER["sigs"] = sigs
    _WORKER["defnames"] = defnames
    _WORKER["dol"] = Dol.from_iso(iso_str)
    _WORKER["smap"] = SymbolMap(map_str)
    _WORKER["tmp"] = tempfile.mkdtemp(prefix="census_")


def compile_one(job):
    """Materialise, compile (with an adaptive declaration loop), probe.

    The adaptive loop exists so a missing `extern` never counts as a compiler
    limit: while the diagnostic names an identifier the harness did not declare,
    declare it and retry.  Anything still failing after MAX_SHIM_ROUNDS is
    reported as a harness gap, explicitly, not as a compiler refusal.
    """
    addr, name, insns, map_size, extent_size, text_block, probe = job
    universe = _WORKER["universe"]
    sigs = _WORKER["sigs"]
    shim_names = SHIM_PROVIDED
    shim_text = _WORKER["shim"]
    cc = _WORKER["cc"]
    tmp = Path(_WORKER["tmp"])
    src = tmp / ("f_%08x.c" % addr)
    obj = tmp / ("f_%08x.o" % addr)

    extra = set()
    types = set()
    rounds = 0
    while True:
        tu = materialise(name, text_block, universe, sigs, shim_names,
                         shim_text, extra, types)
        try:
            write_text(src, tu, encoding="ascii")
        except UnicodeEncodeError:
            return {"addr": addr, "status": "SOURCE_NON_ASCII", "class": "harness",
                    "construct": "Ghidra C contains non-ASCII text",
                    "rounds": rounds, "message": "", "insns": insns}
        if obj.exists():
            obj.unlink()
        got, log, rc = cc.run(src, obj)
        if got is not None:
            break
        m = UNKNOWN_VAR_RX.search(log)
        if m and rounds < MAX_SHIM_ROUNDS and m.group(1) not in extra:
            extra.add(m.group(1))
            rounds += 1
            continue
        t = missing_type_name(log, tu)
        if t and rounds < MAX_SHIM_ROUNDS and t not in types:
            types.add(t)
            rounds += 1
            continue
        status, klass, construct = classify(rc, log)
        out = {"addr": addr, "status": status, "class": klass,
               "construct": construct, "rounds": rounds,
               "message": log.strip()[:400], "insns": insns}
        lc = re.search(r"\(line (\d+), column (\d+)\)", log)
        if lc:
            rows = tu.splitlines()
            ln = int(lc.group(1))
            if 0 < ln <= len(rows):
                line = rows[ln - 1].strip()[:160]
                out["source_line"] = line
                if TEMPLATE_NAME_RX.search(line):
                    # `nlDLRingGetStart<11cBaseCamera>_cBaseCamera(...)`.  Ghidra
                    # sanitises most C++ symbols into C identifiers and misses
                    # template names.  That is neither a compiler limit nor this
                    # tool's shimming -- it is a defect in the export.
                    out["status"] = "SOURCE_NOT_C"
                    out["class"] = "corpus"
                    out["construct"] = ("the Ghidra export emits a C++ template "
                                        "name that is not a C identifier")
        return out

    res = {"addr": addr, "status": "COMPILES", "class": "ok", "construct": "",
           "rounds": rounds, "message": "", "insns": insns}
    if probe:
        res.update(oracle_probe(addr, name, map_size, extent_size, obj))
    return res


def oracle_probe(addr, name, map_size, extent_size, obj_path):
    """One shot through the same oracle match.py uses.  No iteration.

    Extent: the link map states one for the 5,897 symbols it carries, and that
    is authoritative.  For the rest the census's own next-entry-point cap is
    used, which can swallow inter-function alignment padding -- and since
    objdiff requires equal lengths for a MATCH, that only ever costs matches.
    The bias is one-directional and is recorded per function as `extent`.
    """
    dol = _WORKER["dol"]
    smap = _WORKER["smap"]
    source = "link_map"
    size = map_size or None
    if size is None:
        rec = smap.by_addr.get(addr)
        size = rec["size"] if rec and rec["size"] else None
    if size is None:
        size = extent_size
        source = "next_entry_point"
    if not size:
        return {"probe": "NO_EXTENT"}
    retail = dol.read(addr, size)
    if retail is None:
        return {"probe": "NO_EXTENT"}
    try:
        e = Elf32BE(Path(obj_path).read_bytes())
        cand = e.data(e.section(".text"))
        relocs = e.relocs_for(".text")
        for sy in e.symbols():
            if sy["name"] == name and sy["size"]:
                cand = cand[sy["value"]:sy["value"] + sy["size"]]
                relocs = [(o - sy["value"], t, n, ad) for o, t, n, ad in relocs
                          if sy["value"] <= o < sy["value"] + sy["size"]]
                break
        # The retail callee's name comes from the link map, which carries raw
        # symbols (`gnt4-memset`, `cCameraManager::HasCamera(cBaseCamera`).  The
        # candidate object's relocation names the SANITISED spelling Ghidra
        # emitted, because that is what the source calls.  Comparing the two
        # verbatim would report a wrong callee on every SDK call -- so the
        # expectation is translated through the export's own definition names.
        exp = matchmod.expected_symbols(smap, retail, addr)
        names = _WORKER["defnames"]
        exp = dict((off, names.get(sym, sym)) for off, sym in exp.items())
        v = compare(retail, cand, relocs, addr, expected_syms=exp)
    except Exception as ex:                      # noqa: BLE001 - reported, not raised
        return {"probe": "ORACLE_ERROR", "probe_detail": str(ex)[:200]}
    return {"probe": v["verdict"], "match_pct": round(v.get("match_pct", 0.0), 2),
            "cand_insns": len(cand) // 4, "extent": source}


# ------------------------------------------------------------------- shapes

_MNEMONIC_CACHE = {}


def mnemonic(word):
    m = _MNEMONIC_CACHE.get(word)
    if m is None:
        m = disasm_word(word, 0x80000000).split(" ")[0]
        _MNEMONIC_CACHE[word] = m
    return m


def shape_of(blob):
    n = len(blob) // 4
    words = struct.unpack(">%dI" % n, blob[:n * 4])
    return " ".join(mnemonic(w) for w in words)


def shape_report(fns):
    shapes = defaultdict(lambda: {"functions": 0, "instructions": 0,
                                  "example": None})
    for f in fns:
        s = f["shape"]
        e = shapes[s]
        e["functions"] += 1
        e["instructions"] += f["insns"]
        if e["example"] is None:
            e["example"] = f["name"]
    total_f = sum(e["functions"] for e in shapes.values())
    total_i = sum(e["instructions"] for e in shapes.values())

    def coverage(key, total):
        ranked = sorted(shapes.items(),
                        key=lambda kv: (-kv[1][key], -kv[1]["functions"], kv[0]))
        marks = {}
        run = 0
        for i, (_s, e) in enumerate(ranked, 1):
            run += e[key]
            for p in (50, 80, 95):
                if p not in marks and run * 100.0 >= p * total:
                    marks[p] = i
        return marks, ranked

    fmarks, franked = coverage("functions", total_f)
    imarks, _ = coverage("instructions", total_i)
    top = [{"shape": s if len(s) <= 220 else s[:217] + "...",
            "shape_len": len(s.split()),
            "functions": e["functions"], "instructions": e["instructions"],
            "example": e["example"]}
           for s, e in franked[:40]]
    singleton = sum(1 for e in shapes.values() if e["functions"] == 1)
    reuse = {}
    for k in (2, 5, 10, 25):
        sel = [e for e in shapes.values() if e["functions"] >= k]
        reuse[">=%d" % k] = {
            "shapes": len(sel),
            "functions": sum(e["functions"] for e in sel),
            "instructions": sum(e["instructions"] for e in sel),
            # one function per shape has to be solved the hard way; the rest
            # are worked examples of it.  That difference is the free win.
            "followers": sum(e["functions"] - 1 for e in sel),
            "follower_instructions": sum(
                e["instructions"] - e["instructions"] // e["functions"]
                for e in sel),
        }
    return {
        "distinct_shapes": len(shapes),
        "singleton_shapes": singleton,
        "reuse": reuse,
        "total_functions": total_f,
        "total_instructions": total_i,
        "shapes_covering_pct_of_functions": {str(k): v for k, v in
                                             sorted(fmarks.items())},
        "shapes_covering_pct_of_instructions": {str(k): v for k, v in
                                                sorted(imarks.items())},
        "top_shapes": top,
    }


# ------------------------------------------------------------------ digests

def sha256_file(path):
    h = hashlib.sha256()
    with Path(path).open("rb") as fh:
        for blk in iter(lambda: fh.read(1 << 20), b""):
            h.update(blk)
    return h.hexdigest()


def sha256_text(text):
    return hashlib.sha256(text.encode("utf-8")).hexdigest()


def file_stamp(path, root):
    p = Path(path)
    return {"path": p.relative_to(root).as_posix(), "bytes": p.stat().st_size,
            "sha256": sha256_file(p)}


def chunk_stamp(repo):
    base = repo / "research" / "decomp" / "ghidra-export"
    rolled = hashlib.sha256()
    files = sorted(p.name for p in base.glob("chunk_*.c"))
    for name in files:
        rolled.update(name.encode("utf-8"))
        rolled.update(sha256_file(base / name).encode("ascii"))
    return {"files": len(files), "sha256_rolled": rolled.hexdigest()}


def mwcc_rs_commit(exe):
    """Best effort: the pinned commit recorded in TOOLCHAIN.md, confirmed
    against the checkout the exe was built from if that checkout is still
    present.  Traceability only; the exe's own sha256 is what --check compares.
    """
    root = Path(exe).resolve()
    for _ in range(4):
        root = root.parent
    for probe in (root / "Cargo.toml",):
        if probe.is_file():
            try:
                r = subprocess.run(["git", "-C", str(root), "rev-parse", "HEAD"],
                                   capture_output=True, text=True)
                if r.returncode == 0:
                    return r.stdout.strip()
            except OSError:
                pass
    return "7c093483f9c6c5775eb856a1a343a5dc6671233b (TOOLCHAIN.md, unverified here)"


# ------------------------------------------------------------------ the shim

SHIM_HEADER_DOC = """/* census_shim.h -- GENERATED by research/tools/matching-decomp/census.py.
 *
 * NOT a new type vocabulary.  This is %s
 * with four mechanical changes, each forced and each recorded:
 *
 *   1. transliterated to pure ASCII.  mwcc-rs encodes its input as Shift-JIS
 *      and refuses a source file it cannot encode; the seed's typographic
 *      dashes and section signs are comment characters only.
 *   2. `#include <stdbool.h>` dropped and `bool` typedef'd directly -- the
 *      compile runs with -nodefaults and there is no system include path.
 *   3. the two GCC builtins in the seed (__builtin_clz, __builtin_fabs)
 *      replaced -- ABS by a portable macro, countLeadingZeros by an extern
 *      declaration.  MWCC has neither builtin, and a `static` body would be
 *      compiled into all 12,062 units and charge its own diagnostics to the
 *      function under test.
 *   4. five further type names the corpus's own declaration blocks use and
 *      the seed never needed, listed where they are defined below.
 *
 * Everything else -- every typedef, every macro -- is the seed's, byte for
 * byte.  `code` is added from the port driver's own generated block, in
 * research/decomp/port-units-staging (any unit's gnt4_shim.h), not invented
 * here.  The seed's gnt4_* SDK declarations are dropped: they name wasm
 * imports, and a census unit links nothing.
 *
 * seed sha256: %s
 */
#ifndef CENSUS_SHIM_H
#define CENSUS_SHIM_H

typedef unsigned char      undefined;
typedef unsigned char      undefined1;
typedef unsigned short     undefined2;
typedef unsigned int       undefined4;
typedef unsigned long long undefined8;  /* an INTEGER, never double */
typedef unsigned char      byte;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef unsigned long long ulonglong;
typedef long long          longlong;
typedef int                bool;

/* Five further names Ghidra emits in this corpus's own declaration blocks and
 * the seed never needed: `size_t` and `wchar_t` are the C standard library's,
 * `uint3` and `undefined3` are Ghidra's three-byte types widened to the
 * nearest legal C type, and `FILE` is opaque because nothing dereferences it.
 * Counted, not guessed: size_t 114 declarations, uint3 5, FILE 3, wchar_t 2,
 * undefined3 1 across the whole export. */
typedef unsigned long      size_t;
typedef unsigned short     wchar_t;
typedef unsigned int       uint3;
typedef unsigned int       undefined3;
typedef struct _CENSUS_FILE FILE;

/* Ghidra `code` for indirect dispatch: unprototyped so any-arg calls compile.
 * Verbatim from the port driver's generated block. */
typedef void (code)();

#define CONCAT44(hi, lo) \\
  (((unsigned long long)(unsigned int)(hi) << 32) | (unsigned int)(lo))
#define CONCAT31(hi, lo) \\
  (((unsigned int)(hi) << 8) | (unsigned char)(lo))
#define CONCAT22(hi, lo) \\
  (((unsigned int)(unsigned short)(hi) << 16) | (unsigned short)(lo))
#define CONCAT13(hi, lo) CONCAT31(hi, lo)
#define SUB84(x, n) ((unsigned int)((unsigned long long)(x) >> ((n) * 8)))
#define SUB41(x, n) ((unsigned char)((unsigned int)(x) >> ((n) * 8)))
#define SUB42(x, n) ((unsigned short)((unsigned int)(x) >> ((n) * 8)))
#define SUB21(x, n) ((unsigned char)((unsigned short)(x) >> ((n) * 8)))

/* The seed's two helpers are DECLARED, not defined: a `static` body would be
 * compiled into every one of the 12,062 translation units, and its own
 * diagnostics would then be charged to the function under test. */
#define ABS(x) ((x) < 0 ? -(x) : (x))
extern uint countLeadingZeros(int x);

#define GC_F32(a)  (*(float *)(unsigned int)(a))
#define GC_F64(a)  (*(double *)(unsigned int)(a))
#define GC_U8(a)   (*(unsigned char *)(unsigned int)(a))
#define GC_S16(a)  (*(short *)(unsigned int)(a))
#define GC_PTR(a)  (*(char **)(unsigned int)(a))
#define GC_IPTR(a) (*(int *)(unsigned int)(a))

#endif /* CENSUS_SHIM_H */
"""


def build_shim(repo):
    """The shim text, and its seed's digest.  Inlined into every unit, not
    written to disk -- see PROLOGUE for why an #include cannot be used."""
    seed = repo / SHIM_SEED_REL
    text = SHIM_HEADER_DOC % (SHIM_SEED_REL, sha256_file(seed))
    # A stray `*/` inside the banner closes the comment early and turns the rest
    # of it into tokens; the resulting parse error then looks like a corpus
    # problem.  This cost an afternoon once, so it is now an assertion.
    banner = text.split("*/", 1)[0]
    assert "/*" not in banner[2:], "census_shim banner comment is not well formed"
    for block in (PROLOGUE,):
        assert block.count("*/") == 1, "generated comment block closes early"
    return text


SHIM_PROVIDED = set("""undefined undefined1 undefined2 undefined3 undefined4
undefined8 byte ushort uint uint3 ulong ulonglong longlong bool code size_t
wchar_t FILE CONCAT44 CONCAT31 CONCAT22 CONCAT13 SUB84 SUB41 SUB42 SUB21 ABS
countLeadingZeros GC_F32 GC_F64 GC_U8 GC_S16 GC_PTR GC_IPTR""".split())


# --------------------------------------------------------------------- report

def pct(n, d):
    return round(100.0 * n / d, 3) if d else 0.0


def build_payload(args):
    repo = Path(args.repo_root).resolve()
    iso = repo / "Gotcha Force.iso"
    if not iso.is_file():
        iso = Path(matchmod.REPO_DEFAULT) / "Gotcha Force.iso"
    mapfile = repo / MAP_REL
    if not mapfile.is_file():
        mapfile = Path(matchmod.REPO_DEFAULT) / MAP_REL

    dol = Dol.from_iso(iso)
    smap = SymbolMap(mapfile)
    fns = entry_points(repo, dol, smap)
    blocks = load_chunks(repo)

    # shapes, over the whole universe -- no compiler needed
    for f in fns:
        f["shape"] = shape_of(f["bytes"])
    shapes = shape_report(fns)

    universe = set()
    sigs = {}
    for addr, b in blocks.items():
        if IDENT_RX.match(b["name"]):
            universe.add(b["name"])
    for addr, b in blocks.items():
        if b["name"] in universe:
            sigs[b["name"]] = parse_signature(b["text"], b["name"]) or "int"

    kind, exe = matchmod.pick_backend(args.backend)
    if exe is None:
        sys.stderr.write(
            "no PowerPC compiler found. Set MWCC_RS to the mwcc-rs build "
            "(see research/tools/matching-decomp/TOOLCHAIN.md).\n")
        raise SystemExit(3)

    shim_text = build_shim(repo)

    jobs = []
    skipped = []
    for f in fns:
        b = blocks.get(f["addr"])
        name = f["name"]
        if b is None:
            skipped.append((f, "NO_GHIDRA_SOURCE"))
            continue
        if not IDENT_RX.match(b["name"]):
            skipped.append((f, "NAME_NOT_C_IDENTIFIER"))
            continue
        body = b["text"]
        if ("DECOMPILE FAILED" in body or "EXCEPTION" in body
                or "{" not in body):
            skipped.append((f, "DECOMPILE_FAILED"))
            continue
        jobs.append((f["addr"], b["name"], f["insns"], f["map_size"], f["size"],
                     body, not args.no_probe))
    if args.limit:
        jobs = jobs[:args.limit]

    defnames = dict((b["map_name"], b["name"]) for b in blocks.values()
                    if b["map_name"] != b["name"])
    results = run_jobs(jobs, exe, shim_text, universe, sigs, defnames, iso,
                       mapfile, args)

    by_addr = {r["addr"]: r for r in results}
    skip_reason = {f["addr"]: why for f, why in skipped}
    per_function = []
    status_f = Counter()
    status_i = Counter()
    class_f = Counter()
    class_i = Counter()
    constructs = defaultdict(lambda: {"functions": 0, "instructions": 0,
                                      "class": "", "example": None,
                                      "example_message": "",
                                      "example_source_line": ""})
    probed = []
    for f in fns:
        r = by_addr.get(f["addr"])
        if r is None:
            reason = skip_reason.get(f["addr"], "NOT_RUN")
            row = {"addr": "0x%08x" % f["addr"], "name": f["name"],
                   "insns": f["insns"], "status": reason, "class": "no_source"}
            status_f[reason] += 1
            status_i[reason] += f["insns"]
            class_f["no_source"] += 1
            class_i["no_source"] += f["insns"]
            per_function.append(row)
            continue
        row = {"addr": "0x%08x" % f["addr"], "name": f["name"],
               "insns": f["insns"], "status": r["status"], "class": r["class"],
               "shim_rounds": r.get("rounds", 0)}
        if r["construct"]:
            row["construct"] = r["construct"]
        if r.get("probe"):
            row["probe"] = r["probe"]
            if r.get("extent"):
                row["extent"] = r["extent"]
            if "match_pct" in r:
                row["match_pct"] = r["match_pct"]
                probed.append((f, r))
        status_f[r["status"]] += 1
        status_i[r["status"]] += f["insns"]
        class_f[r["class"]] += 1
        class_i[r["class"]] += f["insns"]
        if r["status"] != "COMPILES":
            c = constructs[(r["class"], r["construct"])]
            c["functions"] += 1
            c["instructions"] += f["insns"]
            c["class"] = r["class"]
            if c["example"] is None:
                c["example"] = "%s @ 0x%08x" % (f["name"], f["addr"])
                c["example_message"] = r.get("message", "")[:240]
                c["example_source_line"] = r.get("source_line", "")
        per_function.append(row)

    total_f = len(fns)
    total_i = sum(f["insns"] for f in fns)

    shapes["matched_exemplars"] = matched_exemplar_reach(fns, by_addr)

    sensitivity = long_long_sensitivity(
        fns, by_addr, jobs, exe, shim_text, universe, sigs, defnames, iso,
        mapfile, args)

    # Every ordering in this artifact is TOTAL, so two runs of the same tree
    # produce byte-identical JSON and `--check` means something.  A pool returns
    # results in whatever order they finish; ties broken by anything else would
    # make the drift check fire at random.
    ranked = sorted(constructs.items(),
                    key=lambda kv: (-kv[1]["instructions"], -kv[1]["functions"],
                                    kv[0][1], kv[0][0]))
    refusal_table = [{
        "construct": key[1], "class": key[0],
        "functions": v["functions"], "instructions": v["instructions"],
        "pct_functions": pct(v["functions"], total_f),
        "pct_instructions": pct(v["instructions"], total_i),
        "example": v["example"], "example_message": v["example_message"],
        "example_source_line": v["example_source_line"],
    } for key, v in ranked]

    # near-match distribution
    buckets = [(100, 100), (90, 99.999), (75, 90), (50, 75), (25, 50), (0, 25)]
    dist = []
    for lo, hi in buckets:
        sel = [p for p in probed
               if (p[1]["match_pct"] >= lo and
                   (p[1]["match_pct"] <= hi if lo == 100 else p[1]["match_pct"] < hi))]
        dist.append({"bucket": ("=100%" if lo == 100 else ">=%d%% and <%g%%" % (lo, hi)),
                     "functions": len(sel),
                     "instructions": sum(p[0]["insns"] for p in sel)})
    ge90 = [p for p in probed if p[1]["match_pct"] >= 90.0]
    exact = [p for p in probed if p[1]["probe"] == "MATCH"]
    # Largest first: a one-instruction `blr` that matches says nothing, and a
    # 27-instruction function that matches from verbatim Ghidra C says a lot.
    ge90.sort(key=lambda p: (-p[0]["insns"], -p[1]["match_pct"], p[0]["addr"]))

    payload = {
        "schema": "matching-compiler-census/1",
        "generated_utc": datetime.datetime.utcnow().strftime(
            "%Y-%m-%dT%H:%M:%SZ"),
        "question": ("what fraction of THIS corpus can the matching-decompilation "
                     "compiler ingest, and what stops the rest -- measured, not "
                     "quoted from the vendor"),
        "inputs": {
            "corpus_index": file_stamp(repo / INDEX_REL, repo),
            "corpus_chunks": chunk_stamp(repo),
            "registry": file_stamp(repo / REGISTRY_REL, repo),
            "symbol_map": {"path": MAP_REL, "sha256": sha256_file(mapfile)},
            "dol": {"iso": iso.name,
                    "text_sha256": hashlib.sha256(
                        b"".join(dol.blob[o:o + s] for o, _a, s in dol.text)
                    ).hexdigest()},
            "compiler": {
                "backend": kind,
                "exe": str(exe),
                "exe_sha256": sha256_file(exe),
                "commit": mwcc_rs_commit(exe),
                "build": BUILD_LABEL,
                "cflags": list(matchmod.DEFAULT_CFLAGS_RS),
            },
            "shim_header": {
                "name": "census_shim.h",
                "sha256": sha256_text(shim_text),
                "derived_from": file_stamp(repo / SHIM_SEED_REL, repo),
            },
            "materialisation": {
                "callee_declarations": "unprototyped, return type from the "
                                       "callee's own Ghidra signature",
                "global_declarations": "extern, width from Ghidra's naming "
                                       "prefix (FLOAT_/DOUBLE_/PTR_/s_), else int",
                "adaptive_rounds_max": MAX_SHIM_ROUNDS,
            },
        },
        "totals": {"entry_points": total_f, "instructions": total_i,
                   "attempted": len(jobs)},
        "compile_ability": {
            "by_status": {k: {"functions": status_f[k],
                              "instructions": status_i[k],
                              "pct_functions": pct(status_f[k], total_f),
                              "pct_instructions": pct(status_i[k], total_i)}
                          for k in sorted(status_f)},
            "by_class": {k: {"functions": class_f[k],
                             "instructions": class_i[k],
                             "pct_functions": pct(class_f[k], total_f),
                             "pct_instructions": pct(class_i[k], total_i)}
                         for k in sorted(class_f)},
        },
        "refusals": refusal_table,
        "near_match": {
            "probed": len(probed),
            "extent_source": {
                "link_map": sum(1 for p in probed
                                if p[1].get("extent") == "link_map"),
                "next_entry_point": sum(1 for p in probed
                                        if p[1].get("extent") ==
                                        "next_entry_point"),
            },
            "distribution": dist,
            "exact_match_first_try": len(exact),
            "ge90_first_try": len(ge90),
            "ge90_instructions": sum(p[0]["insns"] for p in ge90),
            "top": [{"name": p[0]["name"], "addr": "0x%08x" % p[0]["addr"],
                     "insns": p[0]["insns"], "match_pct": p[1]["match_pct"],
                     "verdict": p[1]["probe"]} for p in ge90[:40]],
        },
        "sensitivity_long_long": sensitivity,
        "shapes": shapes,
        "per_function": per_function,
    }
    return payload


def matched_exemplar_reach(fns, by_addr):
    """Spike doc sec 3.1.5, extended to what this census actually matched.

    A shape with at least one byte-exact match in it is a shape with a worked
    example.  Every other function in that shape differs only in operands, so
    it is the cheapest work available.  Counted both ways, as always.
    """
    by_shape = defaultdict(list)
    for f in fns:
        by_shape[f["shape"]].append(f)
    shapes = 0
    followers = 0
    follower_insns = 0
    matched = 0
    top = []
    for shape, group in by_shape.items():
        hits = [g for g in group
                if by_addr.get(g["addr"], {}).get("probe") == "MATCH"]
        if not hits:
            continue
        shapes += 1
        matched += len(hits)
        hit_addrs = set(g["addr"] for g in hits)
        rest = [g for g in group if g["addr"] not in hit_addrs]
        followers += len(rest)
        follower_insns += sum(g["insns"] for g in rest)
        if rest:
            top.append({"shape": shape if len(shape) <= 200 else shape[:197] + "...",
                        "matched": len(hits), "followers": len(rest),
                        "follower_instructions": sum(g["insns"] for g in rest),
                        "exemplar": hits[0]["name"]})
    top.sort(key=lambda x: (-x["followers"], -x["follower_instructions"],
                            x["shape"]))
    return {
        "shapes_with_a_matched_exemplar": shapes,
        "functions_already_matched_in_them": matched,
        "follower_functions": followers,
        "follower_instructions": follower_insns,
        "top": top[:25],
    }


LONGLONG_CONSTRUCT = "this long long shape is not modeled yet"

U8_TYPEDEF_RX = re.compile(r"^typedef unsigned long long undefined8;.*$", re.M)


def long_long_sensitivity(fns, by_addr, jobs, exe, shim_text, universe, sigs,
                          defnames, iso, mapfile, args):
    """Is the top blocker the compiler's, or Ghidra's placeholder typing?

    Ghidra types the eight EABI argument registers it cannot resolve as
    `undefined8`, and the port's shim contract makes that a 64-bit integer.  The
    compiler then refuses the function for a long-long shape that the retail
    code does not contain.  This pass re-compiles exactly those functions with
    `undefined8` narrowed to 32 bits -- SEMANTICALLY WRONG for CONCAT44, and
    used for nothing but this diagnostic -- and reports how many convert.  The
    difference separates 'mwcc-rs needs 64-bit lowering' from 'the corpus needs
    argument types'.
    """
    subset = [j for j in jobs
              if by_addr.get(j[0], {}).get("construct", "").startswith(
                  LONGLONG_CONSTRUCT)]
    if not subset:
        return {"applies_to_functions": 0, "note": "no long-long refusals"}
    variant = U8_TYPEDEF_RX.sub(
        "typedef unsigned int       undefined8;  "
        "/* CENSUS SENSITIVITY VARIANT ONLY */", shim_text)
    if variant == shim_text:
        return {"error": "could not build the narrowed-undefined8 variant"}
    subset = [(j[0], j[1], j[2], j[3], j[4], j[5], False) for j in subset]
    res = run_jobs(subset, exe, variant, universe, sigs, defnames, iso, mapfile,
                   args)
    insns = dict((j[0], j[2]) for j in subset)
    ok = [r for r in res if r["status"] == "COMPILES"]
    still = Counter()
    for r in res:
        if r["status"] != "COMPILES":
            still[r["construct"][:80]] += r["insns"]
    return {
        "question": ("of the functions mwcc-rs refuses for a long-long shape, "
                     "how many are refused only because Ghidra typed the "
                     "unresolved argument registers `undefined8`?"),
        "variant": "undefined8 narrowed to unsigned int (diagnostic only)",
        "applies_to_functions": len(subset),
        "applies_to_instructions": sum(insns.values()),
        "compiles_under_variant_functions": len(ok),
        "compiles_under_variant_instructions": sum(r["insns"] for r in ok),
        "still_blocked_top": [{"construct": k, "instructions": v}
                              for k, v in sorted(still.items(),
                                                 key=lambda kv: (-kv[1], kv[0]))[:8]],
    }


def run_jobs(jobs, exe, shim_text, universe, sigs, defnames, iso, mapfile, args):
    if not jobs:
        return []
    init = (str(exe), shim_text, sorted(universe), sigs, defnames, str(iso),
            str(mapfile), BUILD_LABEL)
    if args.jobs == 1:
        worker_init(*init)
        out = []
        for i, j in enumerate(jobs, 1):
            out.append(compile_one(j))
            if args.progress and i % 200 == 0:
                sys.stderr.write("  %d/%d\n" % (i, len(jobs)))
        return out
    import multiprocessing as mp
    ctx = mp.get_context("spawn")
    with ctx.Pool(args.jobs, initializer=worker_init, initargs=init) as pool:
        out = []
        for i, r in enumerate(pool.imap_unordered(compile_one, jobs,
                                                  chunksize=8), 1):
            out.append(r)
            if args.progress and i % 500 == 0:
                sys.stderr.write("  %d/%d\n" % (i, len(jobs)))
        return out


def serialise(payload):
    return json.dumps(payload, indent=1, sort_keys=False) + "\n"


VOLATILE_KEYS = ("generated_utc",)


def strip_volatile(doc):
    d = json.loads(json.dumps(doc))
    for k in VOLATILE_KEYS:
        d.pop(k, None)
    comp = d.get("inputs", {}).get("compiler", {})
    comp.pop("exe", None)          # a path, not a number-determining input
    comp.pop("commit", None)       # traceability only, per TOOLCHAIN.md's rule
    return d


def dump_one(repo, args):
    """Debug aid: show exactly what the compiler is being handed, and its reply."""
    blocks = load_chunks(repo)
    addr = int(args.dump, 16)
    b = blocks.get(addr)
    if b is None:
        sys.stderr.write("no Ghidra block at 0x%08x\n" % addr)
        return 2
    universe = set(x["name"] for x in blocks.values() if IDENT_RX.match(x["name"]))
    sigs = dict((x["name"], parse_signature(x["text"], x["name"]) or "int")
                for x in blocks.values() if x["name"] in universe)
    kind, exe = matchmod.pick_backend(args.backend)
    workdir = Path(tempfile.mkdtemp(prefix="census_dump_"))
    shim_text = build_shim(repo)
    cc = Compiler(exe)
    extra = set()
    types = set()
    for _ in range(2 * MAX_SHIM_ROUNDS + 1):
        tu = materialise(b["name"], b["text"], universe, sigs, SHIM_PROVIDED,
                         shim_text, extra, types)
        src = workdir / "dump.c"
        write_text(src, tu, encoding="ascii")
        obj = workdir / "dump.o"
        if obj.exists():
            obj.unlink()
        got, log, rc = cc.run(src, obj)
        if got is not None:
            break
        m = UNKNOWN_VAR_RX.search(log)
        if m and m.group(1) not in extra:
            extra.add(m.group(1))
            continue
        t = missing_type_name(log, tu)
        if t and t not in types:
            types.add(t)
            continue
        break
    print(tu.replace(shim_text, "/* ... census_shim.h inlined here ... */\n"))
    print("---- rc=%s ----" % rc)
    print(log.strip())
    lc = re.search(r"\(line (\d+), column (\d+)\)", log)
    if lc:
        ln, col = int(lc.group(1)), int(lc.group(2))
        rows = tu.splitlines()
        if 0 < ln <= len(rows):
            print("---- source at line %d ----" % ln)
            print(rows[ln - 1])
            print(" " * (col - 1) + "^")
    print("---- classify: %s ----" % (classify(rc, log),))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--repo-root", default=str(PRODUCT_ROOT))
    ap.add_argument("--backend", choices=["mwcceppc", "mwcc-rs"],
                    default="mwcc-rs")
    ap.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) - 2))
    ap.add_argument("--limit", type=int, default=0,
                    help="pilot mode: only the first N functions")
    ap.add_argument("--no-probe", action="store_true",
                    help="skip pass 3 (the oracle near-match probe)")
    ap.add_argument("--progress", action="store_true", default=True)
    ap.add_argument("--out")
    ap.add_argument("--md")
    ap.add_argument("--dump", default="",
                    help="debug: print the translation unit this tool would "
                         "feed the compiler for one address (0x8000598c) and "
                         "the compiler's answer, then exit")
    ap.add_argument("--check", action="store_true",
                    help="re-derive and diff against the committed artifact; "
                         "exit 1 on drift, write nothing")
    args = ap.parse_args()

    repo = Path(args.repo_root).resolve()
    out_json = Path(args.out) if args.out else repo / OUT_JSON_REL
    out_md = Path(args.md) if args.md else repo / OUT_MD_REL

    if args.dump:
        return dump_one(repo, args)

    payload = build_payload(args)
    text = serialise(payload)

    if args.check:
        if not out_json.is_file():
            sys.stderr.write("missing artifact: %s\n" % out_json)
            return 1
        old = strip_volatile(json.loads(out_json.read_text(encoding="utf-8")))
        new = strip_volatile(json.loads(text))
        if old != new:
            sys.stderr.write(
                "%s is STALE: the tree no longer produces these numbers. "
                "Re-run without --check and commit the result.\n" % out_json.name)
            return 1
        print("%s: up to date" % out_json.name)
        return 0

    out_json.parent.mkdir(parents=True, exist_ok=True)
    write_text(out_json, text)
    out_md.parent.mkdir(parents=True, exist_ok=True)
    write_text(out_md, render_markdown(payload))

    t = payload["totals"]
    ca = payload["compile_ability"]["by_status"]
    print("wrote %s" % out_json)
    print("wrote %s" % out_md)
    print("  entry points %d, instructions %d" % (t["entry_points"],
                                                  t["instructions"]))
    for k in sorted(ca, key=lambda k: -ca[k]["instructions"]):
        print("  %-22s %6d fn %6.2f%%   %7d insn %6.2f%%"
              % (k, ca[k]["functions"], ca[k]["pct_functions"],
                 ca[k]["instructions"], ca[k]["pct_instructions"]))
    nm = payload["near_match"]
    print("  near-match probed %d, >=90%% first try %d, exact %d"
          % (nm["probed"], nm["ge90_first_try"], nm["exact_match_first_try"]))
    return 0


# --------------------------------------------------------------- markdown

def render_markdown(p):
    from census_report import render          # noqa: PLC0415
    return render(p)


if __name__ == "__main__":
    raise SystemExit(main())
