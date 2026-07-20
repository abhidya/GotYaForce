# OGhidra Coverage-Gap Detection Tool — v2 Design

**Status:** Design (implementation-ready)
**Author:** design pass, 2026-07-20
**Replaces:** `scripts/ogh-scan-coverage.ps1` (v1) — kept as fallback during migration
**Target runtime:** PowerShell 5.1 driver + Python 3.11 signal engine + OGhidra MCP `/create_function` (new endpoint)

---

## Table of Contents

1. [Goals & Non-Goals](#1-goals--non-goals)
2. [Multi-Signal Detection](#2-multi-signal-detection)
3. [Signal Merge & Gap Taxonomy](#3-signal-merge--gap-taxonomy)
4. [Storage & History](#4-storage--history)
5. [Automation](#5-automation)
6. [Performance Budget](#6-performance-budget)
7. [CI / Scheduling Integration](#7-ci--scheduling-integration)
8. [Migration Plan](#8-migration-plan)
9. [Appendix A — v1 vs v2 Comparison](#appendix-a--v1-vs-v2-comparison)
10. [Appendix B — Open Questions](#appendix-b--open-questions)

---

## 1. Goals & Non-Goals

### 1.1 What "non-hardcoded" means, concretely

| Rule | v1 | v2 |
|---|---|---|
| No hand-maintained address lists in driver | partial (TEMPLATE_CTORS live in `force_create_missing_functions.java:39-43`) | **enforced** — the 3 Borg template ctors (`0x8007ca5c`, `0x800cfe9c`, `0x80129608`) must fall out of a general detection rule, not be special-cased |
| No hard-coded MCP URL/port | partial | unchanged (`-McpUrl` flag stays) |
| No magic regex exceptions per file | OK | OK |
| No "skip these addresses" allowlist | OK | **enforced** — false-positive suppression must be rule-based (e.g. "address is in `.data`/`.bss`"), not enumerated |

**Validation criterion:** removing every `0x80xxxxxx` literal from the v2 codebase and re-running it must still surface exactly the 3 template ctors in `ghidra_missing_true_gaps`. If it doesn't, the rule is wrong.

### 1.2 Acceptable false-positive rate

| Output bucket | Target FP rate | Rationale |
|---|---|---|
| `ghidra_missing_true_gaps` | **0** (zero) | This bucket drives auto-fix; any FP creates a spurious Ghidra function and corrupts the program file |
| `ghidra_missing_candidates` | ≤ 50% | Human-triaged; OK to be noisy if recall is high |
| `session_pending` | N/A (measurement only) | Not actionable, just reported |
| `cited_data_addresses` | ≤ 10% | Surfaced for awareness; FPs here are non-destructive |

The v1 baseline of 5 entries in `ghidra_missing_true_gaps` is treated as ground truth; v2 must not regress.

### 1.3 Auto-fix vs report-only

**Decision:** v2 produces a report by default and applies auto-fix only when `--apply` is passed. Auto-fix is restricted to `ghidra_missing_true_gaps` only (never candidates). See §5.

Rationale: auto-fix on candidates risks corrupting the Ghidra project file; the v1 workflow of "review report, run Java script" is preserved as the safe path.

---

## 2. Multi-Signal Detection

Six signals. Each emits a set of `(address, evidence)` pairs; the merge layer (§3) combines them.

### 2.1 Signal inventory

| ID | Signal | Source | Works on bare DOL? | Cost | Est. FP rate | Recall on the 8 known gaps |
|---|---|---|---|---|---|---|
| S1 | DOL prologue scan | boot.dol bytes | yes | ~50 ms | ~0% | 5 of 8 |
| S2 | DOL `blr`-boundary scan | boot.dol bytes | yes | ~80 ms | ~2% | 7 of 8 (adds 2 template ctors) |
| S3 | `bl`-target scan | boot.dol bytes | yes | ~80 ms | ~0% | 8 of 8 (all are call targets or have one) |
| S4 | Function-pointer table scan | boot.dol bytes + heuristic | yes | ~150 ms | ~5% | 3 of 3 template ctors (redundant with S2/S3 for those) |
| S5 | Live MCP ground truth | OGhidra `/list_functions` | no (needs Ghidra) | ~3 s | 0% (definition) | N/A (this is the comparison set) |
| S6 | Citation harvest (strict) | `research/`, `packages/`, `scripts/` source | no (text grep) | ~10 s parallel | ~30% (after strict filter; was ~99% in v1) | 5 of 8 (template ctors are cited via constructor pattern) |

**Key insight:** S2 + S3 together catch all 8 known gaps **without any hardcoded list**. S4 is a redundant safety net for indirect-call-only functions (none currently known, but defensive). S6 is for **discovery** of gaps outside the DOL text sections (e.g. overlays, BSS-handled indirection) and is downgraded to "candidate" tier because of FP rate.

### 2.2 S1 — DOL prologue scan (unchanged from v1)

**Implementation:** v1 logic in `ogh-scan-coverage.ps1:107-145`. Keep verbatim, ported to Python.

**Pseudocode:**
```python
def scan_prologues(dol_bytes, text_sections):
    entries = {}
    for s in text_sections:
        prev = 0
        for off in range(0, s.size, 4):
            w = read_be32(dol_bytes, s.file_offset + off)
            if (w & 0xFFFF0000) == 0x94210000 and (w & 0xFFFF) >= 0xFF00:
                # stwu r1,-N(r1)
                if off == 0 or is_return_class(prev):
                    entries[s.virt_addr + off] = ("S1_prologue",)
            prev = w
    return entries
```

**Cost:** ~50 ms for ~3.5 MB of text. **Bare DOL:** yes.

### 2.3 S2 — DOL `blr`-boundary scan (NEW, the template-ctor killer)

**Implementation:** Any 4-byte-aligned address whose preceding word is a return-class instruction AND whose own word decodes to a valid PPC instruction is a function-entry candidate. No requirement on the first instruction itself — this is what catches `li r0,0; cmpwi; bge +0x84` template dispatchers.

**Return-class instruction set** (extend v1's `Test-BlrVariant`):
- `blr`   = `0x4E800020`
- `blrl`  = `0x4E800021`
- `bctr`  = `0x4E800420`
- `bctrl` = `0x4E800421`
- `bclr[cond]`  = `(w & 0xFC0007FF) == 0x4C000020`
- `bcctr[cond]` = `(w & 0xFC0007FF) == 0x4C000420`

**Pseudocode:**
```python
def scan_blr_boundaries(dol_bytes, text_sections):
    entries = {}
    for s in text_sections:
        for off in range(4, s.size, 4):
            prev = read_be32(dol_bytes, s.file_offset + off - 4)
            if not is_return_class(prev):
                continue
            w = read_be32(dol_bytes, s.file_offset + off)
            if not is_valid_ppc_word(w):
                continue
            # Heuristic: also require the next 1-2 words to be valid PPC.
            # This rejects random padding 0x00000000 or 0xFFFFFFFF after a blr.
            va = s.virt_addr + off
            entries[va] = ("S2_blr_boundary", prev)
    return entries
```

**`is_valid_ppc_word` lightweight check (no full disassembler):**
- Reject `0x00000000`, `0xFFFFFFFF`, `0x60000000` (canonical `nop` is allowed but a run of >4 nops at the start signals padding → reject).
- Reject if primary opcode (bits 26-31) is reserved (`0x00`, `0x09`-`0x0B`, `0x1E`, `0x3F`).
- Reject if the word decodes as a `bl`/`b` whose target points outside any text section (indicates data misread).

**Cost:** ~80 ms (single pass over text bytes; same pass can also feed S1, S3). **Bare DOL:** yes. **Estimated FP:** ~2% — typically a `bclr` inside a jump table trailer; filtered by the multi-signal merge.

**Why it catches the 3 template ctors:** Each one is immediately preceded by a `blr` from the previous function's tail (Ghidra's auto-analysis stops at the `blr`; v1's prologue rule misses the entry because `li r0,0` is not a prologue). All 3 addresses (`0x8007ca5c`, `0x800cfe9c`, `0x80129608`) satisfy S2.

### 2.4 S3 — `bl`-target scan (NEW, definitive for direct calls)

**Implementation:** A `bl` (branch-and-link) is unambiguous: opcode `0x48000001` (AA=1, LK=1) or `0x4Bxxxxxx` with bit 0 set. Its target is by definition a function entry.

**PPC `bl` decode:**
```python
def decode_bl(w, pc):
    # b[l][a] forms: opcode 18 (bits 26-30 = 01001 for b/lk/aa variants)
    if (w & 0xFC000003) != 0x48000001 and (w & 0xFC000003) != 0x48000003:
        return None
    # Note: 0x48000001 = b LK=1 AA=0 (relative); 0x48000003 = bl absolute
    aa = (w >> 1) & 1
    if (w & 0xFC000002) != 0x48000000:  # not a b-family at all
        return None
    lk = w & 1
    if not lk:
        return None  # plain b, not bl
    imm = w & 0x03FFFFFC
    if imm & 0x02000000:  # sign-extend 26-bit
        imm |= 0xFC000000
    target = imm if aa else (pc + imm) & 0xFFFFFFFF
    return target
```

**Pseudocode:**
```python
def scan_bl_targets(dol_bytes, text_sections):
    targets = {}
    for s in text_sections:
        for off in range(0, s.size, 4):
            w = read_be32(dol_bytes, s.file_offset + off)
            pc = s.virt_addr + off
            t = decode_bl(w, pc)
            if t is not None and in_text_sections(t, text_sections):
                targets.setdefault(t, []).append(pc)
    return targets
```

**Cost:** ~80 ms (same single pass; merge into S1/S2 scanner). **Bare DOL:** yes. **Estimated FP:** ~0% — every `bl` target is by definition a function call site.

**Why it catches the 3 template ctors:** Each is invoked via a `bl 0x80xxxxxx` from the Borg constructor dispatcher table (the `ctor_*_root_*_cmd_*` tables). Even though the template-ctor body has no prologue, the call site unambiguously marks it as a function entry.

### 2.5 S4 — Function-pointer table scan (NEW, indirect-call net)

**Implementation:** The Borg command-move tables store `{s16 id, u8 flags, u8 _pad, u32 fn_addr, u32 fallback}` records in `.rodata`. A sequence of such records, each pointing into a text section, is a function-pointer table and every `fn_addr` is a real function entry.

**Detection heuristic (no Ghidra needed):**
1. Slide a 8-byte window across `.rodata` and `.data`.
2. For each 4-byte-aligned offset, read the word as a big-endian address.
3. If it falls in any text section, count it as a "code pointer."
4. If ≥ 2 consecutive 8-byte windows each contain a code pointer (i.e. ≥ 2 code pointers within 64 bytes), classify the region as a function-pointer table.
5. Add every code pointer in that region to S4.

**Pseudocode:**
```python
def scan_function_pointer_tables(dol_bytes, data_sections, text_sections):
    candidates = defaultdict(list)
    for s in data_sections:
        for off in range(0, s.size - 4, 4):
            w = read_be32(dol_bytes, s.file_offset + off)
            if in_text_sections(w, text_sections):
                candidates[s.virt_addr + off].append(w)
    # Cluster: find windows where ≥2 code pointers live within 64 bytes
    entries = {}
    addrs = sorted(candidates.keys())
    i = 0
    while i < len(addrs):
        j = i
        while j + 1 < len(addrs) and addrs[j+1] - addrs[i] <= 64:
            j += 1
        if j - i >= 1:  # at least 2 in window
            for k in range(i, j+1):
                for target in candidates[addrs[k]]:
                    entries.setdefault(target, []).append(addrs[k])
        i = j + 1
    return entries
```

**Cost:** ~150 ms. **Bare DOL:** yes. **Estimated FP:** ~5% — typically a single scattered code pointer in `.data` that isn't part of a table; the ≥2-in-window rule suppresses most of these.

### 2.6 S5 — Live MCP ground truth (kept from v1)

**Implementation:** v1 logic in `ogh-scan-coverage.ps1:74-105`. Page through `/list_functions?offset=N&limit=500` up to 60 pages. Parse `^name at 80xxxxxx$`.

**Cost:** ~3 s (60 sequential HTTP round-trips on localhost). Could be parallelised to ~1 s with 8 concurrent page requests — see §6.

### 2.7 S6 — Citation harvest (kept, with stricter filter)

**v1 problem:** Matches any `0x80xxxxxx` substring, producing 54,051 citations of which 42,079 are "not in MCP" — almost all are data addresses, byte literals, hashes, etc. The report becomes unreadable.

**v2 fix:** Keep the harvest but require the citation to appear in a **code-evidence context**. Drop bare hex matches.

**Context patterns (require at least one):**
```
ctor 0x80xxxxxx                    # Borg constructor reference
constructor 0x80xxxxxx             # long-form
boot.dol:0x80xxxxxx                # explicit ROM citation
0x80xxxxxx at                      # "address at" (location-style)
at 0x80xxxxxx                      # reversed form
FUN_80xxxxxx                       # Ghidra auto-name (uppercase hex, no 0x)
zz_00xxxxx_                        # port naming convention (already lowercased hex)
0x80xxxxxx (                       # immediately followed by paren (call site)
```

**Reject patterns (mutually exclusive with the above):**
- `0x80xxxxxx,` followed by another hex (array literal)
- `0x80xxxxxx]` or `0x80xxxxxx}` (data array member)
- Line contains only the hex literal with no surrounding text

**Pseudocode:**
```python
EVIDENCE_RX = re.compile(
    r'(?:ctor\s+(?:0x)?(80[0-9a-fA-F]{6})'
    r'|constructor\s+(?:0x)?(80[0-9a-fA-F]{6})'
    r'|boot\.dol:(?:0x)?(80[0-9a-fA-F]{6})'
    r'|(?:0x)?(80[0-9a-fA-F]{6})\s+at\b'
    r'|\bat\s+(?:0x)?(80[0-9a-fA-F]{6})'
    r'|FUN_(80[0-9a-fA-F]{6})'
    r'|zz_00([0-9a-fA-F]{6})_)',
    re.IGNORECASE
)

def harvest_citations(dirs):
    counts = defaultdict(int)
    for path in iter_source_files(dirs, exts=('.ts','.js','.mjs','.json','.md','.py')):
        text = read_text(path)
        for m in EVIDENCE_RX.finditer(text):
            for g in m.groups():
                if g:
                    addr = normalize_hex(g)  # → '80xxxxxx'
                    counts[addr] += 1
                    break
    return counts
```

**Cost:** ~10 s on 7,600 files in parallel (v1 was serial; see §6). **Estimated FP:** ~30% (down from ~99%); still noisy because `FUN_*` matches Ghidra dumps that reference data symbols, but every match is at least a deliberate reference rather than a byte literal.

---

## 3. Signal Merge & Gap Taxonomy

### 3.1 Merge algorithm

```
For every address A in (S1 ∪ S2 ∪ S3 ∪ S4 ∪ S6):
    applicable = [sig for sig in [S1,S2,S3,S4] if A ∈ domain of sig]
    agreeing   = [sig for sig in applicable if A in sig's output]
    confidence = len(agreeing) / max(1, len(applicable))
    cited      = (A in S6)   # boosts confidence by 0.1 if true, capped at 1.0
    in_mcp     = (A in S5)

    bucket = classify(A, applicable, agreeing, confidence, cited, in_mcp)
```

**Classification rules (evaluated in order):**

| # | Condition | Bucket |
|---|---|---|
| 1 | `in_mcp` is False AND `confidence ≥ 0.5` AND `agreeing` contains S3 (call target) | `ghidra_missing_true_gaps` |
| 2 | `in_mcp` is False AND `confidence ≥ 0.5` (no S3 but ≥2 other signals) | `ghidra_missing_true_gaps` |
| 3 | `in_mcp` is False AND `confidence < 0.5` AND `agreeing` non-empty | `ghidra_missing_candidates` |
| 4 | `in_mcp` is False AND only S6 (citation) agrees | `cited_data_addresses` |
| 5 | `in_mcp` is True AND `cited` is True AND address is in `session.json` but not analyzed | `session_pending` |
| 6 | (default) | discarded |

**Rule 1's S3 primacy:** A `bl` target is by definition code. If Ghidra hasn't made it a function, that's a true gap. This is what catches all 3 template ctors in the absence of any hardcoding.

### 3.2 Confidence score

`confidence = (count of agreeing structural signals) / (count of applicable structural signals) + (0.1 if cited else 0)`, capped at 1.0.

Where "structural" = S1, S2, S3, S4 (not S5/S6 — S5 is the comparison set, S6 is evidence not structure).

**Examples (against the 8 known gaps):**

| Address | S1 | S2 | S3 | S4 | S6 | Confidence | Bucket |
|---|---|---|---|---|---|---|---|
| `0x8000d694` | ✓ | ✓ | ✓ | ? | ✓ | 1.00 | true_gaps |
| `0x8000d7d0` | ✓ | ✓ | ✓ | ? | ✓ | 1.00 | true_gaps |
| `0x801aadb4` | ✓ | ✓ | ✓ | ? | ✓ | 1.00 | true_gaps |
| `0x8024cdc0` | ✓ | ✓ | ✓ | ? | ✓ | 1.00 | true_gaps |
| `0x8024ceec` | ✓ | ✓ | ✓ | ? | ✓ | 1.00 | true_gaps |
| `0x8007ca5c` (template) | ✗ | ✓ | ✓ | ✓ | ✓ | 1.00 | true_gaps |
| `0x800cfe9c` (template) | ✗ | ✓ | ✓ | ✓ | ✓ | 1.00 | true_gaps |
| `0x80129608` (template) | ✗ | ✓ | ✓ | ✓ | ✓ | 1.00 | true_gaps |

(?" = depends on whether the Borg table happens to span the S4 window; the merge doesn't require it since S2+S3 already give confidence ≥ 0.67.)

### 3.3 Output schema (v2 JSON)

```jsonc
{
  "schema_version": "2.0",
  "generated_at": "2026-07-20T12:00:00-04:00",
  "mcp_url": "http://localhost:8080",
  "dol_path": "D:\\GotYaForce\\user-data\\GG4E\\disc\\sys\\boot.dol",
  "dol_sha256": "ab12...",

  "counts": {
    "mcp_functions": 11972,
    "dol_prologue_entries_s1": 9889,
    "dol_blr_boundary_entries_s2": 9905,
    "bl_targets_s3": 9920,
    "fp_table_entries_s4": 412,
    "cited_strict_s6": 312,
    "merged_universe": 9971,
    "ghidra_missing_true_gaps": 8,
    "ghidra_missing_candidates": 23,
    "session_pending": 42,
    "cited_data_addresses": 187
  },

  "ghidra_missing_true_gaps": [
    {
      "address": "8000d694",
      "confidence": 1.0,
      "signals": ["S1", "S2", "S3"],
      "cited": 3,
      "auto_fix_eligible": true
    }
    // ... 7 more
  ],

  "ghidra_missing_candidates": [
    { "address": "80xxxxxx", "confidence": 0.33, "signals": ["S2"], "cited": 0 }
    // ...
  ],

  "session_pending": [
    { "address": "80xxxxxx", "mcp_name": "FUN_80xxxxxx", "in_session_json": true }
    // ...
  ],

  "cited_data_addresses": [
    { "address": "804335e0", "citation_count": 5, "first_context": "ctor 0x804335e0" }
    // ...
  ],

  // ---- v1-compat array (string-only) so force_create_missing_functions.java
  //      can keep reading it unchanged during migration ----
  "ghidra_missing_true_gaps_v1": [
    "8000d694", "8000d7d0", "801aadb4", "8024cdc0", "8024ceec",
    "8007ca5c", "800cfe9c", "80129608"
  ],

  "history": {
    "prev_run_at": "2026-07-13T10:11:12-04:00",
    "new_gaps": [],
    "closed_gaps": [],
    "baseline_gaps": 8
  }
}
```

**v1 compatibility note:** the array `ghidra_missing_true_gaps` changes shape from `[string]` to `[{address, confidence, ...}]`. To avoid breaking `force_create_missing_functions.java:85-89` mid-migration, v2 also emits `ghidra_missing_true_gaps_v1` as a plain string array. The Java script is updated once to read either key. See §8.

### 3.4 Session staleness measurement

`session_pending` is populated by diffing the MCP `/list_functions` set against the function addresses present in `research/tools/OGhidra/analysis_sessions/session_*/session.json`. The session JSON is the OGhidra-side cache of what Ghidra has analyzed; divergence from live MCP means a re-sweep is needed.

```python
def measure_session_staleness(mcp_addrs, session_json_path):
    session_addrs = load_session_function_addrs(session_json_path)
    pending = mcp_addrs - session_addrs     # in MCP, not in session
    stale   = session_addrs - mcp_addrs     # in session, not in MCP (closed since sweep)
    return pending, stale
```

If `len(pending) > 50` or `len(stale) > 0`, the report flags `session_sweep_recommended: true`.

---

## 4. Storage & History

### 4.1 Report format

- **Primary:** `research/decomp/ogh-coverage-YYYY-MM-DD.json` — same path convention as v1, schema v2.0 (above).
- **Human summary:** `research/decomp/ogh-coverage-YYYY-MM-DD.md` — markdown table of `ghidra_missing_true_gaps` with confidence + signals; one-paragraph trend note.

### 4.2 SQLite index schema

`research/decomp/ogh-coverage-history.sqlite` — single file, append-only by run.

```sql
CREATE TABLE IF NOT EXISTS runs (
  run_id         INTEGER PRIMARY KEY AUTOINCREMENT,
  generated_at   TEXT NOT NULL,             -- ISO 8601
  dol_sha256     TEXT NOT NULL,
  mcp_url        TEXT NOT NULL,
  mcp_count      INTEGER NOT NULL,
  total_gaps     INTEGER NOT NULL,
  baseline_gaps  INTEGER NOT NULL,
  schema_version TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS gaps (
  run_id     INTEGER NOT NULL REFERENCES runs(run_id),
  address    TEXT NOT NULL,                 -- '80xxxxxx' lowercase, no 0x
  bucket     TEXT NOT NULL,                 -- 'true_gap' | 'candidate' | 'session_pending' | 'cited_data'
  confidence REAL NOT NULL,
  signals    TEXT NOT NULL,                 -- JSON array, e.g. '["S1","S2","S3"]'
  cited      INTEGER NOT NULL DEFAULT 0,
  UNIQUE(run_id, address)
);

CREATE INDEX IF NOT EXISTS idx_gaps_address ON gaps(address);
CREATE INDEX IF NOT EXISTS idx_gaps_run     ON gaps(run_id);

CREATE TABLE IF NOT EXISTS signal_stats (
  run_id        INTEGER NOT NULL REFERENCES runs(run_id),
  signal        TEXT NOT NULL,              -- 'S1'..'S6'
  output_count  INTEGER NOT NULL,
  UNIQUE(run_id, signal)
);
```

### 4.3 Trend computation

```python
def diff_against_last_run(sqlite_path, current_true_gaps):
    prev = load_prev_run_true_gaps(sqlite_path)
    current_set = {g["address"] for g in current_true_gaps}
    return {
        "closed_gaps": sorted(prev - current_set),     # were gaps, now fixed
        "new_gaps":    sorted(current_set - prev),     # newly broken
    }
```

Both lists are written into the report's `history` block (§3.3). A non-empty `new_gaps` triggers CI failure (§7).

---

## 5. Automation

### 5.1 New MCP endpoint: `/create_function`

**Plugin:** `com.lauriewired.GhidraMCPPlugin.java`. Pattern follows the existing `setCommentAtAddress` (lines 1034-1060): use `SwingUtilities.invokeAndWait`, `startTransaction`/`endTransaction`, signal success via `AtomicBoolean`.

**New imports required (add to existing import block):**
```java
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.address.Address;
import java.util.concurrent.atomic.AtomicBoolean;
import javax.swing.SwingUtilities;
```
(`Address` and `SwingUtilities` are likely already imported; verify before patching.)

**New endpoint context (add inside `startServer()`, near line 305 alongside `/rename_function_by_address`):**
```java
server.createContext("/create_function", exchange -> {
    Map<String, String> params = parsePostParams(exchange);
    String address = params.get("address");
    boolean overwrite = "true".equalsIgnoreCase(params.get("overwrite"));
    String result = createFunctionAtAddress(address, overwrite);
    sendResponse(exchange, result);
});
```

**New method (place near `setCommentAtAddress`, ~line 1060):**
```java
/**
 * Force-create a function at the given address. Disassembles first if the
 * address has no instruction yet, then runs CreateFunctionCmd. Returns a
 * short status string for the MCP client.
 *
 * @param addressStr  hex virtual address, e.g. "0x8007ca5c"
 * @param overwrite   if true and a function already exists at the address,
 *                    delete it first (use to recover from mis-analyzed bodies)
 */
private String createFunctionAtAddress(String addressStr, boolean overwrite) {
    Program program = getCurrentProgram();
    if (program == null) return "fail: no program loaded";
    if (addressStr == null || addressStr.isEmpty()) return "fail: address required";

    AtomicBoolean ok = new AtomicBoolean(false);
    AtomicReference<String> msg = new AtomicReference<>("fail: unknown");

    try {
        SwingUtilities.invokeAndWait(() -> {
            int tx = program.startTransaction("create_function " + addressStr);
            try {
                Address addr = program.getAddressFactory().getAddress(addressStr);
                if (addr == null) { msg.set("fail: bad address"); return; }

                FunctionManager fm = program.getFunctionManager();
                Function existing = fm.getFunctionAt(addr);
                if (existing != null && !overwrite) {
                    msg.set("exists: " + existing.getName());
                    ok.set(true);
                    return;
                }
                if (existing != null) {
                    fm.removeFunction(addr);
                }

                // Clear conflicting data typing and disassemble.
                new DisassembleCommand(addr, null, true).applyTo(program, monitor);
                new CreateFunctionCmd(addr).applyTo(program, monitor);

                Function created = fm.getFunctionAt(addr);
                if (created != null) {
                    msg.set("created: " + created.getName());
                    ok.set(true);
                } else {
                    msg.set("fail: createFunction returned null");
                }
            } catch (Exception e) {
                msg.set("fail: " + e.getMessage());
            } finally {
                program.endTransaction(tx, ok.get());
            }
        });
    } catch (InterruptedException | InvocationTargetException e) {
        Msg.error(this, "create_function swing failure", e);
        return "fail: swing exception";
    }
    return msg.get();
}
```

**Additional import:** `import java.util.concurrent.atomic.AtomicReference;`

**Notes for implementer:**
- `monitor` is the plugin's existing field (same one used by `decompileFunctionByAddress` line 977). Confirm scope.
- The transaction commits only when `ok` is true. This matches `setCommentAtAddress` semantics.
- `overwrite=true` is intentionally separate from the default path so callers must opt in to destroying an existing function (defensive against bot-driven PRs).

### 5.2 v2 auto-fix invocation

After writing the report, v2 (when run with `--apply`) issues one HTTP POST per gap:

```python
def apply_fixes(gaps, mcp_url, dry_run=True):
    results = []
    for g in gaps:
        if g["confidence"] < 1.0 or not g.get("auto_fix_eligible"):
            continue
        if dry_run:
            results.append((g["address"], "skipped (dry-run)"))
            continue
        r = requests.post(
            f"{mcp_url}/create_function",
            data={"address": "0x" + g["address"], "overwrite": "false"},
            timeout=15,
        )
        results.append((g["address"], r.text.strip()))
    return results
```

**Gate:** only gaps with `confidence == 1.0` AND `auto_fix_eligible == true` (set by the rule: gap must have S3 OR (S2 AND S4) — i.e. structurally provable code) are eligible. This excludes candidate-only gaps.

### 5.3 pyGhidra restart strategy

**Decision:** v2 stays **headless** and does **not** restart pyGhidra. The MCP plugin must already be running (the scan refuses to start if `/list_functions` returns no program). After `--apply`, the user reloads the project in their interactive Ghidra instance to see the new functions.

Rationale: restarting pyGhidra mid-scan invalidates the MCP ground truth; the report should reflect one consistent snapshot. If a sweep is needed post-fix, run v2 again — it will report zero `ghidra_missing_true_gaps` if the fix landed.

For headless batch auto-fix (CI): use `analyzeHeadless.bat` with `force_create_missing_functions.java` directly (v1 path), bypassing the MCP entirely. v2 emits the input JSON for this; it doesn't replace the Java script.

---

## 6. Performance Budget

### 6.1 Target

**Total wall-clock: < 60 seconds** on the current GotYaForce repo (3.5 MB DOL, 7,600 source files, MCP localhost).

v1 baseline: ~5 minutes (dominated by serial citation harvest).

### 6.2 Parallelization plan

| Phase | v1 time | v2 target | How |
|---|---|---|---|
| MCP `/list_functions` poll | ~3 s | ~1 s | 8 concurrent page requests |
| DOL parse (S1+S2+S3 in single pass) | ~50 ms | ~80 ms | Same pass; one Python loop emits all three signals. Cache result. |
| Function-pointer table scan (S4) | n/a | ~150 ms | Single pass over `.rodata`/`.data`; parallelise across sections if needed |
| Citation harvest (S6) | **~4 min** | ~10 s | Parallel file walk (`concurrent.futures.ThreadPoolExecutor(max_workers=16)`); regex per file |
| Signal merge + classify | ~1 s | < 1 s | Pure set ops; no I/O |
| SQLite write | n/a | < 500 ms | Single transaction |
| Report JSON write | < 1 s | < 1 s | Unchanged |

**Parallel scheduling:** S1-S4 run on one process (shared DOL bytes in memory). S5 (MCP) and S6 (citation) run concurrently in two more processes. All three pipelines join before the merge step.

```python
import concurrent.futures as cf

with cf.ThreadPoolExecutor(max_workers=3) as pool:
    fut_dol  = pool.submit(scan_dol_signals, dol_bytes)         # S1+S2+S3+S4
    fut_mcp  = pool.submit(poll_mcp_functions, mcp_url)         # S5
    fut_cite = pool.submit(harvest_citations, scan_dirs)        # S6
    s1, s2, s3, s4 = fut_dol.result()
    s5 = fut_mcp.result()
    s6 = fut_cite.result()
```

### 6.3 DOL parse caching

Text section bytes do not change between runs (the DOL is read-only). Cache the parsed signal sets to disk keyed by `sha256(boot.dol)`:

```
research/decomp/.cache/dol-<sha256[:12]>.pickle
```

Cache contents: `{S1: set[int], S2: set[int], S3: dict[int, list[int]], S4: dict[int, list[int]]}`.

On startup, hash the DOL. If the cache file exists, load it and skip the DOL scan entirely (~5 ms). This drops steady-state wall-clock to **~12 seconds** (just MCP + citations + merge).

Cache invalidation: `dol_sha256` mismatch. Manual purge: delete the file.

### 6.4 Worst-case budget tracker

| Component | Time | % of 60s budget |
|---|---|---|
| DOL hash + cache check | 50 ms | 0% |
| MCP poll (8-way parallel) | 1.0 s | 2% |
| Citation harvest (16-way parallel) | 10 s | 17% |
| Merge + classify | 0.5 s | 1% |
| SQLite write | 0.5 s | 1% |
| Report write | 0.5 s | 1% |
| **Total (cold cache)** | **~12.5 s** | **21%** |
| **Total (warm cache)** | **~12.5 s** | **21%** (DOL parse already negligible) |

Headroom for repo growth: 4.8× before hitting budget.

---

## 7. CI / Scheduling Integration

### 7.1 Cadence

| Trigger | Action |
|---|---|
| Weekly cron (Sun 02:00 local) | Full v2 scan, write JSON + SQLite row, open an issue if `new_gaps` non-empty |
| Pre-commit hook (`.git/hooks/pre-commit` or Husky task) | Skip — DOL scan + MCP poll too slow for commit-time; commit only blocks on file-size sanity |
| PR check (GitHub Action / local `pnpm check:coverage`) | Run v2 against a baseline snapshot; block merge on regression (below) |
| Manual (`pnpm scan:coverage`) | Full v2 scan with console output |

### 7.2 PR-fail thresholds

A PR is blocked if **any** of the following hold:

1. `len(history.new_gaps) > 0` — new true gaps introduced.
2. `counts.ghidra_missing_true_gaps > baseline_gaps` — total grew (baseline stored in SQLite; initialised to 8 for the v2 launch).
3. `len(closed_gaps) > 0 AND len(new_gaps) > 0` — churn without net improvement; requires human review.

A PR is **not** blocked for:
- Growth in `ghidra_missing_candidates` (noisy by design).
- Growth in `cited_data_addresses` (informational).
- `session_pending` growth (separate sweep concern).

### 7.3 Baseline management

The baseline is stored as `baseline_gaps` in the `runs` table. Update it explicitly:

```
pnpm scan:coverage --rebaseline
```

This writes a new row with `baseline_gaps = counts.ghidra_missing_true_gaps`. Otherwise the baseline is read from the most recent run where `baseline_gaps == total_gaps` (i.e. the last "clean" run).

### 7.4 Required CI secrets / env

| Var | Purpose |
|---|---|
| `OGH_MCP_URL` | MCP base URL; default `http://localhost:8080`. CI runner must have Ghidra + OGhidra plugin running. |
| `OGH_DOL_PATH` | Path to `boot.dol`; default repo-relative. |
| `OGH_SCAN_DIRS` | Comma-separated citation dirs; default `research,packages,scripts`. |

---

## 8. Migration Plan

### 8.1 Rollout phases

| Phase | Duration | State |
|---|---|---|
| P0 — Land v2 driver + plugin patch | 1 day | v2 script exists alongside v1; `/create_function` endpoint added to plugin but no callers yet |
| P1 — Shadow run | 1 week | v2 runs nightly **in parallel** with v1; both write reports; engineer diffs the two outputs daily |
| P2 — Validate against known 8 | end of week 1 | v2 must report exactly the 5 + 3 = 8 known gaps in `ghidra_missing_true_gaps` with no extras; if not, fix rules before promoting |
| P3 — Promote v2 as default | 1 day | `pnpm scan:coverage` points at v2; v1 script moved to `scripts/legacy/`; `force_create_missing_functions.java` updated to read `ghidra_missing_true_gaps_v1` (still works) or the rich `ghidra_missing_true_gaps[*].address` field |
| P4 — Retire v1 | 2 weeks later | Delete `ogh-scan-coverage.ps1`; remove `TEMPLATE_CTORS` from `force_create_missing_functions.java`; the 3 template ctors are now found dynamically by v2 and persisted in the report |

### 8.2 Validation checklist (gate for P2 → P3)

Run v2 against the current repo. The report MUST satisfy **all** of:

- [ ] `counts.ghidra_missing_true_gaps == 8`
- [ ] The 8 addresses are exactly: `8000d694`, `8000d7d0`, `801aadb4`, `8024cdc0`, `8024ceec`, `8007ca5c`, `800cfe9c`, `80129608`
- [ ] Each of the 8 has `confidence ≥ 0.5`
- [ ] The 3 template ctors each have `S2` and `S3` in their `signals` array (proves no hardcoding)
- [ ] `ghidra_missing_v1` (the compat array) contains the same 8 strings
- [ ] Removing the literal strings `8007ca5c`, `800cfe9c`, `80129608` from any non-report file in the repo and re-running v2 produces the **same** 8 entries (proves the rules are structural)
- [ ] v2 wall-clock < 60 s
- [ ] `dol_sha256` matches `Get-FileHash user-data/GG4E/disc/sys/boot.dol`

### 8.3 Backward compatibility

| Consumer | v1 input | v2 input | Migration |
|---|---|---|---|
| `force_create_missing_functions.java` | `ghidra_missing_true_gaps: [string]` | `ghidra_missing_true_gaps: [{address, ...}]` and `ghidra_missing_true_gaps_v1: [string]` | Update Java to read `ghidra_missing_true_gaps_v1` first, fall back to old field. Patch is 5 lines in `force_create_missing_functions.java:85-89`. |
| Human reader of report JSON | `top_cited_not_mcp` array | Removed (replaced by `cited_data_addresses` with contexts) | Document in commit message; no tooling depends on it. |
| Anyone diffing reports | flat `counts` keys | Same keys + new ones | Additive only; old keys preserved. |

### 8.4 Rollback

If v2 misbehaves in P1/P3:

1. Move `scripts/ogh-scan-coverage.ps1` back from `scripts/legacy/` to `scripts/`.
2. Revert `pnpm scan:coverage` package.json script to invoke v1.
3. v1's reports remain readable; no data loss.

The SQLite history is independent and continues to accumulate across rollback.

---

## Appendix A — v1 vs v2 Comparison

| Concern | v1 | v2 | Winner |
|---|---|---|---|
| Hardcoded template ctors | Yes (Java `TEMPLATE_CTORS[3]`) | No (structural rules S2+S3) | v2 |
| Citation false positives | ~42,000 (99% FP) | ~187 expected (30% FP after strict filter) | v2 |
| Run time | ~5 min | ~12 s | v2 |
| Trending | None | SQLite history with `new_gaps`/`closed_gaps` | v2 |
| Auto-fix | None (manual Java script) | Opt-in `--apply` via MCP `/create_function` | v2 |
| Code vs data distinction | None | `cited_data_addresses` bucket separated | v2 |
| MCP `/create_function` | Missing | Added (~40 lines) | v2 |
| Session staleness measured | Implicit (count mismatch) | Explicit `session_pending` + `session_sweep_recommended` flag | v2 |
| Plugin recompile needed per fix | Yes | No (HTTP endpoint) | v2 |
| DOL parse caching | No | Yes (sha256-keyed pickle) | v2 |
| v1 false negatives on indirect-call funcs | Possible | Covered by S4 | v2 |
| Complexity / lines of code | ~250 LoC PowerShell | ~600 LoC Python + 40 LoC Java + SQLite schema | v1 (simplicity) |
| External deps | PowerShell only | Python 3.11 + `requests` + stdlib | v1 (zero deps) |

**Where v2 is NOT better than v1:**
- **Dependencies:** v2 needs Python and the `requests` library. v1 was pure PowerShell. Acceptable cost; document in README.
- **Code size:** v2 is ~2.5× larger. Justified by the multi-signal design.
- **First-run setup:** v2 requires patching the OGhidra plugin and recompiling. One-time cost; see §5.1.

---

## Appendix B — Open Questions

These are unresolved from the current repo state and need a human decision before implementation:

1. **Is the OGhidra plugin buildable from this repo?** §5.1 assumes you can add a method to `GhidraMCPPlugin.java` and rebuild. The file lives under `research/tools/OGhidra/OGhidraMCP/` — confirm the build system (Gradle? pre-built jar only?) and whether a rebuilt jar can be dropped into the running Ghidra without reinstalling the plugin.

2. **Is `monitor` accessible from instance methods of `GhidraMCPPlugin`?** The `setCommentAtAddress` pattern at line 1034-1060 doesn't use `monitor`, but `decompileFunctionByAddress` at line 977 does. The new `createFunctionAtAddress` calls `applyTo(program, monitor)` — verify `monitor` is in scope for non-`GhidraScript` classes (the plugin is a `Plugin`, not a `GhidraScript`, so it likely uses a dummy `TaskMonitor` or `ConsoleTaskMonitor`). If unavailable, swap in `new ConsoleTaskMonitor()`.

3. **`AtomicReference` import.** §5.1 adds it; confirm it's not already imported elsewhere with a conflicting alias.

4. **`session.json` location.** §3.4 assumes `research/tools/OGhidra/analysis_sessions/session_*/session.json`. Confirm the most recent session is the active one (no explicit pointer file was found during this design pass).

5. **DOL `data_sections` enumeration for S4.** §2.5 references `.rodata`/`.data` but the DOL format only has `data[0..10]` generic sections. Confirm which DOL data section indices correspond to `.rodata` vs `.data` vs `.bss` for GotYaForce's `boot.dol`, or relax S4 to scan all data sections (safer, slightly noisier).

6. **Citation harvest scope creep.** The 7,600-file scan includes `node_modules`? The v1 script doesn't filter `node_modules`, but its `ScanDirs` defaults (`research`, `packages`, `scripts`) shouldn't include it. Confirm `packages/` doesn't symlink into `node_modules/`.

7. **Auto-fix safety.** §5.2 sets `auto_fix_eligible = True` only for confidence-1.0 gaps. Is there a scenario where a confidence-1.0 gap is still wrong (e.g. a `bl` into a jump table that Ghidra correctly dissects as data)? Consider gating first auto-fix runs behind `--dry-run` for one cycle.

8. **Weekly cron host.** §7.1 assumes a long-running Windows host with Ghidra + OGhidra. Confirm this exists in the GotYaForce environment; otherwise the weekly run needs a VM or container with the plugin loaded.

9. **`cited_data_addresses` bucket boundary.** §3.2 rule 4 puts S6-only citations here, but a code address with no structural signal could still be a real function (e.g. reached only via computed jump). The S4 function-pointer scan should catch most of these, but if `cited_data_addresses` is consistently > 200 entries, revisit whether S4's windowing threshold (64 bytes, ≥2 pointers) is too strict.

10. **What closes the session-pending gap?** §3.4 flags staleness but doesn't fix it. Is there an OGhidra operation to re-sweep, or does the user manually re-run analysis in the GUI? If manual, document the steps in the report markdown.
