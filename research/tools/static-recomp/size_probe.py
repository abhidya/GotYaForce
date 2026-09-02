#!/usr/bin/env python3
"""size_probe.py -- measure the wasm cost of static recompilation.

Emits C for a sample of real ROM functions, links it with the pinned emsdk, and
reports bytes of wasm per translated PowerPC instruction.  That ratio, times the
DOL's whole instruction count, is the honest projection for a full port -- as
opposed to guessing from the one 99-instruction function the spike verified.

Also counts the functions that contain a paired-single instruction, because
those are the ones a translator cannot finish without a Gekko SIMD model.
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from dol_inventory import Dol, gekko_fallback  # noqa: E402
import ppc_recomp as R  # noqa: E402


def wasm_section_sizes(path):
    b = Path(path).read_bytes()
    p = 8
    out = {}

    def leb():
        nonlocal p
        r = s = 0
        while True:
            x = b[p]; p += 1
            r |= (x & 0x7F) << s; s += 7
            if not x & 0x80:
                return r
    while p < len(b):
        sid = b[p]; p += 1
        n = leb()
        out[sid] = out.get(sid, 0) + n
        p += n
    return out, len(b)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--registry", required=True)
    ap.add_argument("--sample", type=int, default=1500)
    ap.add_argument("--emcc", required=True)
    ap.add_argument("--python", required=True)
    ap.add_argument("--workdir", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    dol = Dol.from_iso(Path(a.iso))
    secs = dol.text

    def word(addr):
        for off, ad, sz in secs:
            if ad <= addr < ad + sz:
                return struct.unpack(">I",
                                     dol.blob[off + (addr - ad):off + (addr - ad) + 4])[0]
        return None

    from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.skipdata = True

    def disasm_text(addr, w):
        g = list(md.disasm(struct.pack(">I", w), addr, count=1))
        if g and g[0].mnemonic not in (".byte", ".long", ""):
            return ("%s %s" % (g[0].mnemonic, g[0].op_str)).strip()
        return gekko_fallback(w) or "<undecoded>"

    reg = json.loads(Path(a.registry).read_text())
    fns = reg["functions"]
    addrs = set(int(f["address"], 16)
                for f in (fns.values() if isinstance(fns, dict) else fns))
    for e in reg["excluded"]:
        if isinstance(e, dict) and e.get("address"):
            addrs.add(int(e["address"], 16))
    entries = sorted(addrs)
    nxt = {entries[i]: entries[i + 1] for i in range(len(entries) - 1)}
    nxt[entries[-1]] = max(ad + sz for _, ad, sz in secs)

    # ---- paired-single concentration (whole corpus, no sampling) --------
    ps_fns, ps_instrs = 0, 0
    extents = {}
    for e in entries:
        try:
            lo, hi = R.function_extent(word, e, limit=min(nxt[e] - e, 0x8000))
        except Exception:
            continue
        extents[e] = (lo, hi)
        n = 0
        for addr in range(lo, hi, 4):
            w = word(addr)
            if w is not None and (w >> 26) in (4, 56, 57, 60, 61):
                n += 1
        if n:
            ps_fns += 1
            ps_instrs += n

    # ---- emit the sample -------------------------------------------------
    wd = Path(a.workdir); wd.mkdir(parents=True, exist_ok=True)
    emitted, total_instr, names = [], 0, []
    for e in entries:
        if len(emitted) >= a.sample:
            break
        if e not in extents:
            continue
        lo, hi = extents[e]
        try:
            src, man = R.emit(word, e, "fn_%08x" % e, a.iso, disasm_text)
        except Exception:
            continue
        emitted.append(src)
        names.append(man["cname"])
        total_instr += man["instructions"]

    body = ["#include \"ppc_rt.h\"\n"]
    body.append("uint32_t gf_host_mfspr(ppc_ctx *c, int n);\n"
                "void gf_host_mtspr(ppc_ctx *c, int n, uint32_t v);\n"
                "uint32_t gf_host_timebase(ppc_ctx *c, int n);\n")
    for s in emitted:
        body.append(s.split('#include "ppc_rt.h"', 1)[1])
    Path(wd / "sample.c").write_text("".join(body))

    stub = ['#include "ppc_rt.h"', "#include <stdlib.h>", ""]
    for n in names:
        stub.append("void %s(ppc_ctx *);" % n)
    stub.append("struct e { uint32_t a; ppc_fn f; };")
    stub.append("static const struct e tbl[] = {")
    for e, n in zip([x for x in entries if ("fn_%08x" % x) in names], names):
        stub.append("  { 0x%08xu, %s }," % (e, n))
    stub.append("};")
    stub.append("ppc_fn ppc_lookup(uint32_t a){ for(unsigned i=0;i<sizeof(tbl)/sizeof(tbl[0]);i++) "
                "if(tbl[i].a==a) return tbl[i].f; return 0; }")
    stub.append("uint32_t gf_host_mfspr(ppc_ctx *c,int n){(void)c;(void)n;return 0;}")
    stub.append("void gf_host_mtspr(ppc_ctx *c,int n,uint32_t v){(void)c;(void)n;(void)v;}")
    stub.append("uint32_t gf_host_timebase(ppc_ctx *c,int n){(void)c;(void)n;return 0;}")
    stub.append("void gf_host_wgpipe(ppc_ctx *c,uint32_t v,int w,int f)"
                "{(void)c;(void)v;(void)w;(void)f;}")
    stub.append("uint32_t gf_host_mmio_load(ppc_ctx *c,uint32_t e,int w)"
                "{(void)c;(void)e;(void)w;return 0;}")
    stub.append("int main(void){ ppc_mem1=(uint8_t*)calloc(1,PPC_MEM1_SIZE); "
                "ppc_ctx c; memset(&c,0,sizeof c); "
                "for(unsigned i=0;i<sizeof(tbl)/sizeof(tbl[0]);i++) "
                "if((uintptr_t)tbl[i].f==1) tbl[i].f(&c); return 0; }")
    Path(wd / "stub.c").write_text("\n".join(stub) + "\n")

    rt = Path(__file__).resolve().parent / "rt"
    out_wasm = wd / "sample.wasm"
    cmd = [a.python, a.emcc, str(wd / "sample.c"), str(wd / "stub.c"),
           str(rt / "ppc_rt.c"), "-I", str(rt), "-O2", "-std=c11",
           "-sINITIAL_MEMORY=33554432", "-sALLOW_MEMORY_GROWTH=0",
           "-o", str(wd / "sample.cjs")]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stderr[-4000:])
        raise SystemExit("emcc failed")
    sizes, total = wasm_section_sizes(str(out_wasm))
    code = sizes.get(10, 0)

    dol_instr = 699828
    res = {
        "sampled_functions": len(emitted),
        "sampled_instructions": total_instr,
        "wasm_bytes_total": total,
        "wasm_code_section_bytes": code,
        "bytes_per_instruction_code_section": round(code / float(total_instr), 3),
        "bytes_per_instruction_total_module": round(total / float(total_instr), 3),
        "dol_text_instructions": dol_instr,
        "projected_code_section_bytes_whole_dol":
            int(code / float(total_instr) * dol_instr),
        "projected_module_bytes_whole_dol":
            int(total / float(total_instr) * dol_instr),
        "paired_single_functions": ps_fns,
        "paired_single_instructions": ps_instrs,
        "corpus_entry_points": len(entries),
        "optimisation": "-O2",
    }
    Path(a.out).write_text(json.dumps(res, indent=2))
    for k, v in res.items():
        print("%-52s %s" % (k, v))


if __name__ == "__main__":
    main()
