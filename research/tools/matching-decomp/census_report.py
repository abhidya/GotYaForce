#!/usr/bin/env python3
"""census_report.py -- render docs/matching-compiler-census.md from the artifact.

Kept out of census.py so the measurement and its presentation are separable: the
JSON is the result, this file only formats it.  Nothing here recomputes anything.
"""
from __future__ import annotations


def _row(cells):
    return "| " + " | ".join(str(c) for c in cells) + " |"


def _table(headers, rows, align=None):
    out = [_row(headers)]
    if align is None:
        align = ["---"] * len(headers)
    out.append(_row(align))
    out.extend(_row(r) for r in rows)
    return "\n".join(out)


STATUS_BLURB = {
    "COMPILES": "mwcc-rs produced an object",
    "CODEGEN_UNSUPPORTED": "parsed, then refused to lower -- a compiler capability gap",
    "CODEGEN_PANIC": "the compiler crashed",
    "FRONT_END_REFUSAL": "refused at parse/typecheck",
    "HARNESS_SHIM_GAP": "this tool's translation unit was incomplete, not a compiler limit",
    "SOURCE_NON_ASCII": "the Ghidra C is not encodable as Shift-JIS, which mwcc-rs requires",
    "SOURCE_NOT_C": "the Ghidra export emitted something that is not C",
    "NO_GHIDRA_SOURCE": "the entry point has no block in the Ghidra export",
    "DECOMPILE_FAILED": "Ghidra itself produced no code for it",
    "NAME_NOT_C_IDENTIFIER": "the symbol name is not a legal C identifier",
    "TIMEOUT": "the compile did not finish",
}

CLASS_BLURB = {
    "ok": "compiled",
    "codegen": "COMPILER: parsed and could not lower",
    "frontend": "COMPILER: refused to parse or typecheck",
    "panic": "COMPILER: crashed",
    "harness": "HARNESS: this tool's fault, not the compiler's",
    "corpus": "CORPUS: the decompiled C is defective, nobody's compiler could take it",
    "no_source": "no input to compile",
}


def render(p):
    t = p["totals"]
    ca = p["compile_ability"]
    tf, ti = t["entry_points"], t["instructions"]
    comp = p["inputs"]["compiler"]
    L = []

    L.append("# Matching-decompilation compiler census")
    L.append("")
    L.append("**Generated `%s`.** The question this answers: the matching-decompilation "
             "spike\n(`docs/matching-decompilation-spike.md`) matched 13 functions and named "
             "five compiler\nblockers, all of them found by hand. This measures the same "
             "compiler against **the\nwhole corpus** -- every one of the %s entry points and "
             "%s instructions -- so the\nproject's throughput and scope estimates rest on a "
             "number instead of a vendor claim."
             % (p["generated_utc"], f"{tf:,}", f"{ti:,}"))
    L.append("")
    L.append("Every count below carries **both** a function count and an instruction share, "
             "because\nspike doc sec 5.2 is the standing rule here: half the functions are a "
             "tenth of the code, and a\nfunction-weighted number is a lie by construction.")
    L.append("")
    L.append("## Reproduction")
    L.append("")
    L.append("```bash")
    L.append("# one command; CPU only, no model, no network")
    L.append("MWCC_RS=<path to mwcc-rs>/target/release/mwcc.exe \\")
    L.append("  python research/tools/matching-decomp/census.py")
    L.append("")
    L.append("# drift check: re-derives everything, writes nothing, exit 1 if stale")
    L.append("python research/tools/matching-decomp/census.py --check")
    L.append("```")
    L.append("")
    L.append("### Inputs, digested")
    L.append("")
    ins = p["inputs"]
    L.append(_table(
        ["input", "identity"],
        [["Ghidra corpus index", "`%s` sha256 `%s`" % (ins["corpus_index"]["path"],
                                                       ins["corpus_index"]["sha256"][:16])],
         ["Ghidra chunks (%d files)" % ins["corpus_chunks"]["files"],
          "rolled sha256 `%s`" % ins["corpus_chunks"]["sha256_rolled"][:16]],
         ["oracle registry", "`%s` sha256 `%s`" % (ins["registry"]["path"],
                                                   ins["registry"]["sha256"][:16])],
         ["link map", "`%s` sha256 `%s`" % (ins["symbol_map"]["path"],
                                            ins["symbol_map"]["sha256"][:16])],
         ["retail `.text`", "sha256 `%s`" % ins["dol"]["text_sha256"][:16]],
         ["compiler", "%s build %s, exe sha256 `%s`" % (comp["backend"], comp["build"],
                                                        comp["exe_sha256"][:16])],
         ["compiler commit", "`%s`" % comp["commit"][:40]],
         ["shim header", "`census_shim.h` sha256 `%s`, derived from `%s` sha256 `%s`"
          % (ins["shim_header"]["sha256"][:16],
             ins["shim_header"]["derived_from"]["path"],
             ins["shim_header"]["derived_from"]["sha256"][:16])],
         ["flags", "`%s`" % " ".join(comp["cflags"])]]))
    L.append("")
    L.append("## 1. Compile-ability")
    L.append("")
    L.append("Each entry point's **verbatim** Ghidra C, sliced out of the export and "
             "materialised as a\nsingle translation unit the way the port driver does: the "
             "`gnt4_shim` typedef block, `code`\nfor indirect dispatch, `extern` declarations "
             "for callees and address-named globals.\nNothing in the function body is "
             "rewritten. This does not ask whether the bytes match --\nit asks whether the "
             "compiler can ingest the **shape** of this game's code.")
    L.append("")
    mt = p["inputs"].get("materialisation") or {}
    L.append("The exact recipe, because it bounds every number below:")
    L.append("")
    L.append(_table(["step", "rule"],
                    [["callee declarations", mt.get("callee_declarations", "")],
                     ["global declarations", mt.get("global_declarations", "")],
                     ["missing type names",
                      "declared opaque (`typedef struct X_census_opaque X;`) when a "
                      "declaration names a class the export never defines"],
                     ["adaptive rounds",
                      "up to %s -- while the diagnostic names something the harness "
                      "failed to declare, declare it and retry, so a missing `extern` "
                      "is never counted as a compiler limit"
                      % mt.get("adaptive_rounds_max", "")],
                     ["shim delivery",
                      "**inlined**, not `#include`d: mwcc-rs will not accept a typedef "
                      "that arrived through an include as a file-scope function's "
                      "return type, and Ghidra returns a placeholder type constantly"]]))
    L.append("")
    st = ca["by_status"]
    rows = []
    for k in sorted(st, key=lambda k: -st[k]["instructions"]):
        v = st[k]
        rows.append([("**%s**" % k) if k == "COMPILES" else k,
                     f"{v['functions']:,}", "%.2f%%" % v["pct_functions"],
                     f"{v['instructions']:,}", "**%.2f%%**" % v["pct_instructions"],
                     STATUS_BLURB.get(k, "")])
    L.append(_table(["status", "functions", "% of functions", "instructions",
                     "% of code", "meaning"],
                    rows, ["---", "---:", "---:", "---:", "---:", "---"]))
    L.append("")
    L.append("Rolled up by who is at fault:")
    L.append("")
    cl = ca["by_class"]
    rows = []
    for k in sorted(cl, key=lambda k: -cl[k]["instructions"]):
        v = cl[k]
        rows.append([k, f"{v['functions']:,}", "%.2f%%" % v["pct_functions"],
                     f"{v['instructions']:,}", "%.2f%%" % v["pct_instructions"],
                     CLASS_BLURB.get(k, "")])
    L.append(_table(["class", "functions", "% of functions", "instructions",
                     "% of code", ""],
                    rows, ["---", "---:", "---:", "---:", "---:", "---"]))
    L.append("")
    comp_f = st.get("COMPILES", {}).get("functions", 0)
    comp_i = st.get("COMPILES", {}).get("instructions", 0)
    harness_i = cl.get("harness", {}).get("instructions", 0)
    L.append("> **%s of %s entry points compile -- %.2f%% of the functions and %.2f%% of the "
             "instructions.**"
             % (f"{comp_f:,}", f"{tf:,}", 100.0 * comp_f / tf if tf else 0,
                100.0 * comp_i / ti if ti else 0))
    L.append(">")
    L.append("> The `harness` class (%s instructions, %.2f%% of the code) is this tool's own "
             "floor and\n> is **not** charged to the compiler: a translation unit assembled by "
             "regex from one\n> decompiled function is not the original translation unit. "
             "`corpus` and `no_source` are\n> not the compiler's either. The "
             "compiler-capability number is `codegen` + `frontend` +\n> `panic` and nothing "
             "else." % (f"{harness_i:,}", 100.0 * harness_i / ti if ti else 0))
    L.append("")
    L.append("## 2. What stops the rest, ranked by instructions blocked")
    L.append("")
    L.append("The compiler roadmap. A construct high in this table is worth a lowering; one "
             "low in it\nis not, however many functions it touches.")
    L.append("")
    rows = []
    for r in p["refusals"][:40]:
        rows.append([r["construct"][:96], r["class"], f"{r['functions']:,}",
                     "%.2f%%" % r["pct_functions"], f"{r['instructions']:,}",
                     "%.2f%%" % r["pct_instructions"], "`%s`" % r["example"]])
    L.append(_table(["construct (the compiler's own diagnostic)", "class", "functions",
                     "%fn", "instructions", "%code", "example"],
                    rows, ["---", "---", "---:", "---:", "---:", "---:", "---"]))
    if len(p["refusals"]) > 40:
        L.append("")
        L.append("*(%d further constructs, each below the fortieth; the full list is in the "
                 "JSON.)*" % (len(p["refusals"]) - 40))
    L.append("")
    src_examples = [r for r in p["refusals"][:20] if r.get("example_source_line")]
    if src_examples:
        L.append("Where the diagnostic points at a line, the line it points at:")
        L.append("")
        for r in src_examples[:8]:
            L.append("- **%s** (%s functions) --" % (r["construct"][:70],
                                                     f"{r['functions']:,}"))
            L.append("  ```c")
            L.append("  " + r["example_source_line"])
            L.append("  ```")
        L.append("")
    sv = p.get("sensitivity_long_long") or {}
    if sv.get("applies_to_functions"):
        L.append("### 2a. One sensitivity check, because the top bucket is ambiguous")
        L.append("")
        L.append("Ghidra types the EABI argument registers it cannot resolve as "
                 "`undefined8`, and the\nport's shim contract makes that a 64-bit "
                 "integer. The compiler then refuses the function\nfor a long-long "
                 "shape the retail code does not contain. Re-compiling exactly those\n"
                 "functions with `undefined8` narrowed to 32 bits -- semantically "
                 "wrong, and used for\nnothing but this diagnostic -- separates *the "
                 "compiler needs 64-bit lowering* from *the\ncorpus needs argument "
                 "types*:")
        L.append("")
        L.append(_table(
            ["", "functions", "instructions"],
            [["refused for a long-long shape", f"{sv['applies_to_functions']:,}",
              f"{sv['applies_to_instructions']:,}"],
             ["of those, compile with `undefined8` = 32-bit",
              f"{sv['compiles_under_variant_functions']:,}",
              f"{sv['compiles_under_variant_instructions']:,}"]],
            ["---", "---:", "---:"]))
        L.append("")
        if sv.get("still_blocked_top"):
            L.append("What the rest hit instead, once the long-long shape is out "
                     "of the way:")
            L.append("")
            L.append(_table(["next construct", "instructions"],
                            [[x["construct"][:88], f"{x['instructions']:,}"]
                             for x in sv["still_blocked_top"]],
                            ["---", "---:"]))
            L.append("")
    L.append("## 3. Near-match probe: how far verbatim Ghidra C gets on its own")
    L.append("")
    nm = p["near_match"]
    L.append("Every function that compiled, run once through the same oracle `match.py` uses, "
             "against\nthe retail bytes. **One shot** -- no iteration, no rewriting. This is "
             "the floor the LLM\nloop starts from, not what it can reach.")
    L.append("")
    rows = [[d["bucket"], f"{d['functions']:,}", f"{d['instructions']:,}"]
            for d in nm["distribution"]]
    L.append(_table(["first-try match", "functions", "instructions"], rows,
                    ["---", "---:", "---:"]))
    L.append("")
    es = nm.get("extent_source") or {}
    if es:
        L.append("The retail extent comes from the link map for %s of these and from the "
                 "census's own\nnext-entry-point cap for the other %s. The cap can swallow "
                 "inter-function alignment\npadding, and objdiff requires equal lengths for a "
                 "MATCH -- so that half of the sample can\nonly ever *lose* matches. The count "
                 "below is a floor."
                 % (f"{es.get('link_map', 0):,}", f"{es.get('next_entry_point', 0):,}"))
        L.append("")
    L.append("> **%s of the %s probed match >= 90%% on the first try, and %s of those are "
             "byte-exact.**\n> That is the LLM loop's cheapest class -- and it is %s "
             "instructions, **%.3f%% of the game**.\n> Spike doc sec 5.2, again, with fresh "
             "numbers: %.1f%% of the entry points, well under one\n> percent of the code."
             % (f"{nm['ge90_first_try']:,}", f"{nm['probed']:,}",
                f"{nm['exact_match_first_try']:,}",
                f"{nm['ge90_instructions']:,}",
                100.0 * nm["ge90_instructions"] / ti if ti else 0,
                100.0 * nm["ge90_first_try"] / tf if tf else 0))
    L.append("")
    if nm["top"]:
        L.append("The best of them:")
        L.append("")
        rows = [[("`%s`" % x["name"]), x["addr"], x["insns"],
                 "%.2f%%" % x["match_pct"], x["verdict"]] for x in nm["top"][:25]]
        L.append(_table(["function", "address", "insns", "first-try match", "verdict"],
                        rows, ["---", "---", "---:", "---:", "---"]))
        L.append("")
    L.append("## 4. Shape sharing: the real 'free wins' number")
    L.append("")
    sh = p["shapes"]
    L.append("A *shape* is a function's ordered mnemonic sequence with registers, immediates "
             "and branch\ntargets dropped. Two functions of the same shape differ only in "
             "operands, so a matched\nfunction is a worked example for every other function "
             "sharing its shape. Spike doc sec 3.1.5\ncounted this for the thirteen matched "
             "functions over functions of <= 16 instructions; this is\nthe same measurement "
             "over the whole corpus.")
    L.append("")
    L.append(_table(["", "value"],
                    [["distinct shapes", f"{sh['distinct_shapes']:,}"],
                     ["shapes seen exactly once", f"{sh['singleton_shapes']:,}"],
                     ["functions", f"{sh['total_functions']:,}"],
                     ["instructions", f"{sh['total_instructions']:,}"]],
                    ["---", "---:"]))
    L.append("")
    fcov = sh["shapes_covering_pct_of_functions"]
    icov = sh["shapes_covering_pct_of_instructions"]
    rows = []
    for k in ("50", "80", "95"):
        rows.append([k + "%", f"{fcov.get(k, 0):,}", f"{icov.get(k, 0):,}"])
    L.append(_table(["to cover this share", "distinct shapes (of functions)",
                     "distinct shapes (of instructions)"],
                    rows, ["---", "---:", "---:"]))
    L.append("")
    L.append("Read that carefully. Ranked by **instructions**, the head of the "
             "distribution is not\nreuse -- it is the biggest functions, each with a "
             "shape of its own. The reuse that\nactually pays is in the tail:")
    L.append("")
    ru = sh.get("reuse") or {}
    rows = []
    for k in (">=2", ">=5", ">=10", ">=25"):
        v = ru.get(k)
        if not v:
            continue
        rows.append(["shapes shared by %s functions" % k.replace(">=", "at least "),
                     f"{v['shapes']:,}", f"{v['functions']:,}",
                     f"{v['followers']:,}", f"{v['follower_instructions']:,}"])
    if rows:
        L.append(_table(["", "shapes", "functions in them",
                         "**followers** (one exemplar each solved)",
                         "follower instructions"],
                        rows, ["---", "---:", "---:", "---:", "---:"]))
        L.append("")
    me = sh.get("matched_exemplars") or {}
    if me:
        L.append("And the number that is actually actionable today -- shapes this "
                 "census already has a\n**byte-exact worked example** for:")
        L.append("")
        L.append(_table(
            ["", "value"],
            [["shapes with a matched exemplar",
              f"{me['shapes_with_a_matched_exemplar']:,}"],
             ["functions already matched in them",
              f"{me['functions_already_matched_in_them']:,}"],
             ["**follower functions** (same shape, not yet matched)",
              f"**{me['follower_functions']:,}**"],
             ["follower instructions",
              "**%s** (%.3f%% of the game)"
              % (f"{me['follower_instructions']:,}",
                 100.0 * me["follower_instructions"] / ti if ti else 0)]],
            ["---", "---:"]))
        L.append("")
        if me.get("top"):
            rows = [[f"{x['followers']:,}", f"{x['follower_instructions']:,}",
                     "`%s`" % x["exemplar"], "`%s`" % x["shape"][:90]]
                    for x in me["top"][:15]]
            L.append(_table(["followers", "instructions", "matched exemplar", "shape"],
                            rows, ["---:", "---:", "---", "---"]))
            L.append("")
    L.append("The commonest shapes:")
    L.append("")
    rows = [[f"{x['functions']:,}", f"{x['instructions']:,}", x["shape_len"],
             "`%s`" % x["shape"], "`%s`" % x["example"]]
            for x in sh["top_shapes"][:20]]
    L.append(_table(["functions", "instructions", "len", "shape", "example"],
                    rows, ["---:", "---:", "---:", "---", "---"]))
    L.append("")
    L.append("## 5. What this does to the spike's estimates")
    L.append("")
    L.append("Read against `docs/matching-decompilation-spike.md` sec 3.1.3, sec 4.2 "
             "and sec 5.2.")
    L.append("")
    top = p["refusals"][0] if p["refusals"] else None
    # The three spike-doc sec 3.1.3 blockers that are refusals rather than
    # mismatches, measured rather than asserted.
    named_keys = ("rlwinm mask", "pointer leaf access", "loop codegen")
    named_i = sum(r["instructions"] for r in p["refusals"]
                  if any(k in r["construct"] for k in named_keys))
    codegen_i = cl.get("codegen", {}).get("instructions", 0)
    frontend_i = cl.get("frontend", {}).get("instructions", 0)
    panic = ca["by_status"].get("CODEGEN_PANIC", {}).get("functions", 0)
    L.append(_table(
        ["the spike said", "the census measures"],
        [["five compiler blockers, found by hand on five functions",
          "**%d distinct diagnostics.** Three of the five are refusals and are all "
          "here (`rlwinm`-mask AND, pointer leaf access, loop codegen) -- together "
          "**%s instructions, %.1f%%** of the game. The other two (`r0` index "
          "routing, `lbzu`) are MISMATCH classes, not build failures, so no "
          "compile-ability pass can see them."
          % (len(p["refusals"]), f"{named_i:,}",
             100.0 * named_i / ti if ti else 0)],
         ["\"it could not compile the moderate tier at all\"",
          "%.2f%% of the corpus's instructions compile. The compiler's own limits "
          "block **%.1f%%** of the code (%.1f%% codegen, %.1f%% front end); the "
          "harness's own floor is %.2f%%."
          % (100.0 * comp_i / ti if ti else 0,
             100.0 * (codegen_i + frontend_i) / ti if ti else 0,
             100.0 * codegen_i / ti if ti else 0,
             100.0 * frontend_i / ti if ti else 0,
             100.0 * harness_i / ti if ti else 0)],
         ["13 matched functions, 43 instructions, 14 iterations",
          "**%s byte-exact on the FIRST try from verbatim Ghidra C, no iteration "
          "at all** -- %s instructions, %.3f%% of the game"
          % (f"{nm['exact_match_first_try']:,}",
             f"{nm['distribution'][0]['instructions']:,}",
             100.0 * nm["distribution"][0]["instructions"] / ti if ti else 0)],
         ["233 functions share a shape with the 13 (sec 3.1.5)",
          "%s follower functions share a shape with something already matched "
          "(%s instructions); across the whole corpus %s shapes are shared by at "
          "least two functions, covering %s follower instructions"
          % (f"{(sh.get('matched_exemplars') or {}).get('follower_functions', 0):,}",
             f"{(sh.get('matched_exemplars') or {}).get('follower_instructions', 0):,}",
             f"{((sh.get('reuse') or {}).get('>=2') or {}).get('shapes', 0):,}",
             f"{((sh.get('reuse') or {}).get('>=2') or {}).get('follower_instructions', 0):,}")],
         ["mwcc-rs \"fails honestly\"",
          "confirmed at corpus scale: **%d panics and %d timeouts** across the %s "
          "functions attempted. Every refusal was a diagnostic, never "
          "plausible-but-wrong bytes."
          % (panic, ca["by_status"].get("TIMEOUT", {}).get("functions", 0),
             f"{p['totals']['attempted']:,}")]]))
    L.append("")
    if top:
        L.append("**The single most valuable lowering** is `%s` -- %s functions and "
                 "%s instructions, %.2f%% of the game, behind one diagnostic."
                 % (top["construct"][:80], f"{top['functions']:,}",
                    f"{top['instructions']:,}", top["pct_instructions"]))
        L.append("")
    L.append("Three things this census does **not** establish, stated so they are not "
             "read into it:")
    L.append("")
    L.append("1. **A compile is not a match.** %.2f%% of instructions compile; %.3f%% "
             "match. The gap\n   between them is the LLM loop's actual job, and this "
             "measurement says nothing about\n   how many iterations it takes to close."
             % (100.0 * comp_i / ti if ti else 0,
                100.0 * nm["distribution"][0]["instructions"] / ti if ti else 0))
    L.append("2. **These are mwcc-rs-exact, not MWCC-exact.** `mwcceppc.exe` is still "
             "absent. Where\n   mwcc-rs diverges from real Metrowerks, a match here "
             "would be wrong, and nothing on\n   this machine can check that "
             "(`TOOLCHAIN.md` sec 4).")
    L.append("3. **The materialisation is a floor, not a ceiling.** A translation unit "
             "assembled by\n   regex from one decompiled function, with globals "
             "declared `extern int` and callees\n   left unprototyped, is strictly "
             "worse input than a real translation unit would be.\n   Every number here "
             "moves up, never down, as the input improves.")
    L.append("")
    L.append("---")
    L.append("")
    L.append("*Artifact: `research/decomp/data/matching-compiler-census.json` "
             "(schema `%s`). This document is generated; edit the tool, not the page.*"
             % p["schema"])
    L.append("")
    return "\n".join(L)
