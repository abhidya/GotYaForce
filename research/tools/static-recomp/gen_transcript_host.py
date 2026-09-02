#!/usr/bin/env python3
"""gen_transcript_host.py -- embedder that replays a `transcript_green` console
capture against a statically recompiled function.

This is the spike's SECOND verification, against a different standard, a
different capture tool and a function with real control flow, memory reads and
an out-of-unit callee boundary.

The transcript standard's replay contract (research/decomp/oracle-harness/
run-transcript.mjs) is reproduced exactly:
  * each case is independent -- the seed windows are re-applied before it;
  * the port must make the same calls, in the same order, to the same callees,
    with the same argument values;
  * after each call the console's recorded `deltas` are APPLIED to memory,
    because the out-of-unit callee is stubbed and its memory effect has to be
    replayed rather than computed (run-transcript.mjs:255, `applyDeltas`).

WHERE THE ARGUMENT LIST COMES FROM, and why it is worth reading carefully.
`capture_transcript.py` binds a ROM call site to a wasm import and runs the
PowerPC EABI allocator over that import's signature -- a signature emcc induced
from Ghidra's parameter list for the function.  For this corpus that list is
Ghidra's varargs-assert mis-lift: an `i64` plus seven `f64`s that the machine
code never mentions.  The recorded values are still the console's REAL register
and stack contents at those boundaries; only the claim that they are
"arguments" is fiction.

A static recompiler has no signature at all, so it cannot inherit the fiction.
It has a register file.  Reproducing all sixteen recorded slots therefore means
reproducing the console's register state -- INCLUDING the residue registers the
function never writes, which the project records as an unreproducible class.
"""
from __future__ import annotations

import argparse
import base64
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "dolphin-trace"))
from capture_common import eabi_allocate, wasm_signatures  # noqa: E402


def unswap(b64, elem=4):
    raw = base64.b64decode(b64)
    return b"".join(raw[i:i + elem][::-1] for i in range(0, len(raw), elem))


def carr(name, data):
    return "static const unsigned char %s[] = {%s};" % (
        name, ",".join(str(x) for x in data))


def reader(slot, t):
    """C expression reading one EABI slot out of the register file."""
    if slot.startswith("f"):
        return ("f64", "c->f[%d]" % int(slot[1:]))
    if ":" in slot:
        a, b = slot.split(":")
        return ("i64", "(((uint64_t)c->r[%d] << 32) | c->r[%d])"
                % (int(a[1:]), int(b[1:])))
    if slot.startswith("stack+"):
        off = int(slot.split("+")[1])
        if t == "f64":
            return ("f64", "ppc_u642d(ppc_r64(c, c->r[1] + %d))" % off)
        if t == "i64":
            return ("i64", "ppc_r64(c, c->r[1] + %d)" % off)
        return ("i32", "ppc_r32(c, c->r[1] + %d)" % off)
    return ("i32", "c->r[%d]" % int(slot[1:]))


def writer(slot, t, expr):
    """C statement writing one EABI slot into the register file at entry."""
    if slot.startswith("f"):
        return "c.f[%d] = %s;" % (int(slot[1:]), expr)
    if ":" in slot:
        a, b = slot.split(":")
        return ("c.r[%d] = (uint32_t)((%s) >> 32); c.r[%d] = (uint32_t)(%s);"
                % (int(a[1:]), expr, int(b[1:]), expr))
    if slot.startswith("stack+"):
        off = int(slot.split("+")[1])
        return "ppc_w32(&c, c.r[1] + %d, (uint32_t)(%s));" % (off, expr)
    return "c.r[%d] = (uint32_t)(%s);" % (int(slot[1:]), expr)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--capture", required=True)
    ap.add_argument("--unit-wasm", required=True)
    ap.add_argument("--manifest", required=True)
    ap.add_argument("--sda", default="0x8043b5a0")
    ap.add_argument("--sda2", default="0x8043ea20")
    ap.add_argument("--stack", default="0x81200000")
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    lines = Path(a.capture).read_text().splitlines()
    header = json.loads(lines[0])
    cases = [json.loads(l) for l in lines[1:]
             if l.strip() and json.loads(l)["kind"] == "case"]
    manifest = json.loads(Path(a.manifest).read_text())
    imports, _ = wasm_signatures(Path(a.unit_wasm))
    sigs = {i["name"]: i["params"] for i in imports}

    entry_alloc = eabi_allocate(header["fn"]["params"])

    # ---- callee adapters -------------------------------------------------
    callees = {}
    for cs in cases:
        for k in cs["calls"]:
            callees[k["callee"]] = int(k["callee_addr"], 16)

    ad = []
    for name, addr in sorted(callees.items()):
        params = sigs.get(name)
        if params is None:
            raise SystemExit("no wasm import signature for %s" % name)
        alloc = eabi_allocate(params)
        body = ['printf("{\\"k\\":\\"call\\",\\"callee\\":\\"%s\\",\\"args\\":[");' % name]
        for j, sl in enumerate(alloc):
            kind, expr = reader(sl["src"], sl["t"])
            sep = "" if j == 0 else '","'
            if sep:
                body.append('printf(",");')
            if kind == "f64":
                body.append('printf("%%.17g", %s);' % expr)
            elif kind == "i64":
                body.append('printf("\\"%%llu\\"", (unsigned long long)(%s));' % expr)
            else:
                body.append('printf("%%u", %s);' % expr)
        body.append('printf("]}\\n");')
        body.append("gf_apply_deltas(c);")
        ad.append("static void ad_%s(ppc_ctx *c) {\n    %s\n}"
                  % (name, "\n    ".join(body)))

    # ---- per-case data ---------------------------------------------------
    blobs, case_rows = [], []
    for ci, cs in enumerate(cases):
        seeds = []
        for si, s in enumerate(cs.get("seed", [])):
            b = unswap(s["b64"], header["source"].get("seed_elem_width", 4))
            blobs.append(carr("seed_%d_%d" % (ci, si), b))
            seeds.append("    { 0x%08xu, %d, seed_%d_%d }," % (int(s["addr"], 16),
                                                               len(b), ci, si))
        blobs.append("static const struct region seeds_%d[] = {\n%s\n};"
                     % (ci, "\n".join(seeds) if seeds else "    {0,0,0},"))
        # deltas, flattened per call index
        dlists = []
        for k in cs["calls"]:
            rows = []
            for di, d in enumerate(k.get("deltas", [])):
                b = unswap(d["b64"], header["source"].get("seed_elem_width", 4))
                blobs.append(carr("d_%d_%d_%d" % (ci, k["i"], di), b))
                rows.append("    { 0x%08xu, %d, d_%d_%d_%d }," % (
                    int(d["addr"], 16), len(b), ci, k["i"], di))
            blobs.append("static const struct region dl_%d_%d[] = {\n%s\n};"
                         % (ci, k["i"], "\n".join(rows) if rows else "    {0,0,0},"))
            dlists.append("    { dl_%d_%d, %d }," % (ci, k["i"],
                                                     len(k.get("deltas", []))))
        blobs.append("static const struct dset dsets_%d[] = {\n%s\n};"
                     % (ci, "\n".join(dlists) if dlists else "    {0,0},"))
        args = []
        for sl, v in zip(entry_alloc, cs["args"]):
            if sl["t"] in ("f32", "f64"):
                args.append(writer(sl["src"], sl["t"], repr(float(v))))
            elif sl["t"] == "i64":
                args.append(writer(sl["src"], sl["t"], "%sull" % v))
            else:
                args.append(writer(sl["src"], sl["t"], "%uu" % (int(v) & 0xFFFFFFFF)))
        case_rows.append((ci, len(cs.get("seed", [])), len(cs["calls"]),
                          "\n        ".join(args)))

    cases_c = []
    for ci, nseed, ncall, argsetup in case_rows:
        cases_c.append("""    {
        memset(&c, 0, sizeof c);
        c.r[13] = GF_SDA; c.r[2] = GF_SDA2; c.r[1] = GF_STACK; c.lr = 0xDEADBEEFu;
        gf_load(seeds_%d, %d);
        %s
        g_dsets = dsets_%d; g_ndset = %d; g_call = 0;
        printf("{\\"k\\":\\"case\\",\\"n\\":%d}\\n");
        %s(&c);
        printf("{\\"k\\":\\"case_end\\",\\"n\\":%d}\\n");
    }""" % (ci, nseed, argsetup, ci, ncall, ci, manifest["cname"], ci))

    src = TEMPLATE % {
        "fn": header["fn"]["export"],
        "cname": manifest["cname"],
        "entry": manifest["entry"],
        "adapters": "\n".join(ad),
        "entries": "\n".join('    { 0x%08xu, ad_%s },' % (v, k)
                             for k, v in sorted(callees.items()))
                   + '\n    { %su, %s },' % (manifest["entry"], manifest["cname"]),
        "blobs": "\n".join(blobs),
        "cases": "\n".join(cases_c),
        "sda": int(a.sda, 16), "sda2": int(a.sda2, 16), "stack": int(a.stack, 16),
    }
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(src)
    print("wrote %s: %d cases, %d callee adapters"
          % (a.out, len(cases), len(callees)))


TEMPLATE = r"""/* GENERATED by research/tools/static-recomp/gen_transcript_host.py. */
#include "ppc_rt.h"
#include <stdio.h>
#include <stdlib.h>

void %(cname)s(ppc_ctx *);

struct region { uint32_t addr; uint32_t len; const unsigned char *bytes; };
struct dset  { const struct region *r; int n; };

static const struct dset *g_dsets; static int g_ndset; static int g_call;

static void gf_load(const struct region *r, int n)
{
    for (int i = 0; i < n; i++)
        for (uint32_t j = 0; j < r[i].len; j++)
            ppc_mem1[(r[i].addr & 0x03FFFFFFu) + j] = r[i].bytes[j];
}

/* The console's out-of-unit callee is stubbed, so its memory effect is
 * REPLAYED from the capture -- run-transcript.mjs:255 does the same. */
static void gf_apply_deltas(ppc_ctx *c)
{
    (void)c;
    if (g_call < g_ndset) gf_load(g_dsets[g_call].r, g_dsets[g_call].n);
    g_call++;
}

void gf_host_wgpipe(ppc_ctx *c, uint32_t v, int w, int f)
{ (void)c;(void)v;(void)w;(void)f; }
uint32_t gf_host_mmio_load(ppc_ctx *c, uint32_t e, int w)
{ ppc_fault("unmodelled MMIO load", e, (uint32_t)w); return 0; }
uint32_t gf_host_mfspr(ppc_ctx *c, int n){(void)c;(void)n;return 0;}
void gf_host_mtspr(ppc_ctx *c, int n, uint32_t v){(void)c;(void)n;(void)v;}
uint32_t gf_host_timebase(ppc_ctx *c, int n){(void)c;(void)n;return 0;}

%(adapters)s

struct ppc_entry { uint32_t addr; ppc_fn fn; };
static const struct ppc_entry ppc_entries[] = {
%(entries)s
};
ppc_fn ppc_lookup(uint32_t a)
{
    for (unsigned i = 0; i < sizeof(ppc_entries)/sizeof(ppc_entries[0]); i++)
        if (ppc_entries[i].addr == a) return ppc_entries[i].fn;
    return 0;
}

%(blobs)s

#define GF_SDA   0x%(sda)08xu
#define GF_SDA2  0x%(sda2)08xu
#define GF_STACK 0x%(stack)08xu

int main(void)
{
    ppc_mem1 = (uint8_t *)calloc(1, PPC_MEM1_SIZE);
    if (!ppc_mem1) return 1;
    ppc_ctx c;
%(cases)s
    return 0;
}
"""


if __name__ == "__main__":
    main()
