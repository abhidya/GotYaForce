#!/usr/bin/env python3
"""model_loop.py — POC §5 model-tier experiment (35B vs 27B compile-fix loop).

Replays design stage 3 with a local model as the fixer: the model receives the
VERBATIM Ghidra C (never editable) plus a support header degraded by removing the
four definitions the human loop had to supply (stdbool include, CONCAT44,
countLeadingZeros, ABS). Each iteration: emcc build -> exact compiler errors fed
back -> model returns the complete corrected header -> repeat until link or budget.
After link, the wasm is judged by the oracle corpus (stage 4) — a header that
compiles but breaks PPC semantics (e.g. CONCAT44 as numeric conversion) fails there.

Usage: python model_loop.py <tag> <model-id> [max_iters]
"""
import json
import os
import re
import shutil
import subprocess
import sys
import time
import urllib.request

# Windows console defaults to cp1252; model output contains emoji/unicode.
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

HERE = os.path.dirname(os.path.abspath(__file__))
ENDPOINT = "http://127.0.0.1:8888/v1/chat/completions"
API_KEY = "sk-unsloth-34e759c3cc616609c5ef87dd22bcbc0e"

TAG, MODEL = sys.argv[1], sys.argv[2]
MAX_ITERS = int(sys.argv[3]) if len(sys.argv) > 3 else 8
RUN = os.path.join(HERE, f"model-run-{TAG}")
os.makedirs(RUN, exist_ok=True)
shutil.copy(os.path.join(HERE, "unit_poc.c"), os.path.join(RUN, "unit_poc.c"))

# Degrade the header: strip exactly what the human compile loop had to supply.
with open(os.path.join(HERE, "gnt4_shim.h")) as f:
    header = f.read()
header = header.replace('#include <stdbool.h>  /* Ghidra emits `bool` for cr-bit results */\n', "")
header = re.sub(r"/\* PPC int->double magic.*?\n\n", "", header, flags=re.S)
header = re.sub(r"/\* PPC cntlzw.*?\n\n", "", header, flags=re.S)
header = header.replace("#define ABS(x) __builtin_fabs(x)\n", "")
with open(os.path.join(RUN, "gnt4_shim.h"), "w", newline="\n") as f:
    f.write(header)

EMCC = os.path.join(HERE, "..", "..", "..", "tools", "emsdk")

def build():
    bash = shutil.which("bash") or r"C:\Program Files\Git\bin\bash.exe"
    script = (
        f'source "$(cygpath -u \'{EMCC}\')/emsdk_env.sh" >/dev/null 2>&1; '
        f'cd "$(cygpath -u \'{RUN}\')" && '
        "emcc unit_poc.c -O1 -fno-strict-aliasing --no-entry "
        "-Wno-implicit-function-declaration -Wno-int-conversion "
        "-sERROR_ON_UNDEFINED_SYMBOLS=0 -sINITIAL_MEMORY=2155479040 -sALLOW_MEMORY_GROWTH=0 "
        "-sEXPORTED_FUNCTIONS=_zz_003cd5c_,_zz_003d344_,_zz_0066298_,_FUN_80031634 "
        "-o unit_model.wasm"
    )
    p = subprocess.run([bash, "-lc", script], capture_output=True, text=True, timeout=300)
    if p.returncode != 0:
        return False, (p.stderr + p.stdout)[-6000:]
    # Post-link gate (design: auto-stub + LOG unresolved imports, and the log feeds
    # the loop): only the gnt4_* SDK seam may remain an undefined import. Anything
    # else (e.g. an undefined CONCAT44 becoming an implicit function -> env import)
    # links "successfully" but is semantically dead — feed it back as an error.
    chk = subprocess.run(
        [sys.executable, "-c", (
            "import sys,json;"
            "d=open(sys.argv[1],'rb').read();"
            "import re;"
            "names=[m.decode('utf8','ignore') for m in re.findall(rb'env.([\\x20-\\x7e]{2,40})', d)];"
            "print(json.dumps(sorted(set(n.split('\\x00')[0] for n in names))))"
        ), os.path.join(RUN, "unit_model.wasm")],
        capture_output=True, text=True)
    try:
        imports = [n for n in json.loads(chk.stdout or "[]") if not n.startswith("gnt4_")]
    except Exception:
        imports = []
    bad = [n for n in imports if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", n) and n not in (
        "memory", "__memory_base", "__table_base", "__indirect_function_table", "__stack_pointer")]
    if bad:
        return False, (
            "link gate: these symbols are UNDEFINED and became wasm imports, but they are "
            "not gnt4_* SDK functions, so they must be DEFINED in gnt4_shim.h with correct "
            f"PowerPC semantics: {', '.join(bad)}\n"
            "(Ghidra decompiler helper idioms like CONCAT44 must behave exactly as the "
            "original PPC code did.)")
    return True, ""

CHAT_CALLS = {"n": 0}

def chat(messages):
    # 32k output budget: thinking models (27B) spend reasoning tokens before the
    # answer; owner explicitly accepts slow generations. Reasoning is persisted
    # per call for the "does reasoning help the port" question.
    # STREAMING for liveness proof: every SSE chunk is evidence of life; a heartbeat
    # line prints every 20s, and >300s with no chunk at all raises (socket timeout)
    # instead of hanging opaquely for an hour.
    body = json.dumps({
        "model": MODEL, "messages": messages, "temperature": 0.6, "max_tokens": 32768,
        "stream": True,
    }).encode()
    req = urllib.request.Request(ENDPOINT, data=body, headers={
        "Content-Type": "application/json", "Authorization": f"Bearer {API_KEY}"})
    reasoning_parts, content_parts = [], []
    finish_reason = None
    t0 = last_hb = time.time()
    try:
        # timeout must cover CPU-bound prefill: the server sends nothing (not even
        # headers) until the first token, which can take >5 min on this unit.
        with urllib.request.urlopen(req, timeout=3600) as r:
            for raw in r:
                line = raw.decode("utf-8", "ignore").strip()
                if not line.startswith("data:"):
                    continue
                payload = line[5:].strip()
                if payload == "[DONE]":
                    break
                try:
                    d = json.loads(payload)
                except ValueError:
                    continue
                if "error" in d:  # SSE error events must be loud, not silently dropped
                    raise RuntimeError(f"stream error: {json.dumps(d['error'])[:600]}")
                choice = (d.get("choices") or [{}])[0]
                finish_reason = choice.get("finish_reason") or finish_reason
                delta = choice.get("delta") or {}
                # stream the raw tokens to stdout as they arrive
                if delta.get("reasoning_content"):
                    if not reasoning_parts:
                        sys.stdout.write(f"\n===== [{TAG}] reasoning =====\n")
                    reasoning_parts.append(delta["reasoning_content"])
                    sys.stdout.write(delta["reasoning_content"])
                    sys.stdout.flush()
                if delta.get("content"):
                    if not content_parts:
                        sys.stdout.write(f"\n===== [{TAG}] answer =====\n")
                    content_parts.append(delta["content"])
                    sys.stdout.write(delta["content"])
                    sys.stdout.flush()
    except urllib.error.HTTPError as e:
        raise RuntimeError(f"HTTP {e.code}: {e.read().decode()[:800]}")
    CHAT_CALLS["n"] += 1
    with open(os.path.join(RUN, f"call{CHAT_CALLS['n']}-meta.json"), "w") as f:
        json.dump({"finish_reason": finish_reason,
                   "wall_seconds": round(time.time() - t0, 1),
                   "reasoning_chars": sum(map(len, reasoning_parts)),
                   "content_chars": sum(map(len, content_parts))}, f, indent=2)
    if reasoning_parts:
        with open(os.path.join(RUN, f"call{CHAT_CALLS['n']}-reasoning.md"), "w",
                  encoding="utf-8", newline="\n") as f:
            f.write("".join(reasoning_parts))
    print(f"[{TAG}] call done in {int(time.time() - t0)}s, finish={finish_reason}", flush=True)
    return "".join(content_parts)

SYSTEM = """You are the compile-fix stage of a Ghidra-C -> wasm port pipeline for a
GameCube (PowerPC, big-endian) game. A verbatim Ghidra-decompiled C file fails to
compile with emscripten (clang, wasm32). You may ONLY change the support header
gnt4_shim.h — the .c file is verbatim decompiler output and must never be edited.

Fix the header so the C compiles AND keeps the original PowerPC runtime semantics
(Ghidra decompiler idioms must behave exactly as they did on the GameCube).
Output the COMPLETE corrected gnt4_shim.h in a single ```c code block. No other text
is used by the pipeline."""

with open(os.path.join(RUN, "unit_poc.c")) as f:
    unit_c = f.read()

log = {"tag": TAG, "model": MODEL, "iterations": [], "linked": False}
t0 = time.time()
for i in range(1, MAX_ITERS + 1):
    ok, out = build()
    print(f"[{TAG}] iter {i}: build {'OK' if ok else 'FAIL'}", flush=True)
    if ok:
        log["linked"] = True
        log["iterations"].append({"i": i, "result": "linked"})
        break
    with open(os.path.join(RUN, "gnt4_shim.h")) as f:
        cur = f.read()
    reply = chat([
        {"role": "system", "content": SYSTEM},
        {"role": "user", "content":
            f"Verbatim decompiled C (read-only):\n```c\n{unit_c}\n```\n\n"
            f"Current gnt4_shim.h:\n```c\n{cur}\n```\n\n"
            f"Exact compiler output:\n```\n{out}\n```\n\n"
            "Return the complete corrected gnt4_shim.h."},
    ])
    m = re.findall(r"```(?:c|cpp|h)?\s*\n(.*?)```", reply, flags=re.S)
    if not m:
        log["iterations"].append({"i": i, "result": "no-code-block", "reply_head": reply[:400]})
        print(f"[{TAG}] iter {i}: model returned no code block", flush=True)
        continue
    new_header = max(m, key=len)
    with open(os.path.join(RUN, "gnt4_shim.h"), "w", newline="\n") as f:
        f.write(new_header)
    with open(os.path.join(RUN, f"header-iter{i}.h"), "w", newline="\n") as f:
        f.write(new_header)
    log["iterations"].append({"i": i, "result": "patched", "errors_head": out[:600]})

log["wall_seconds"] = round(time.time() - t0, 1)
with open(os.path.join(RUN, "loop-log.json"), "w") as f:
    json.dump(log, f, indent=2)
print(f"[{TAG}] done: linked={log['linked']} iters={len(log['iterations'])} wall={log['wall_seconds']}s", flush=True)
sys.exit(0 if log["linked"] else 1)
