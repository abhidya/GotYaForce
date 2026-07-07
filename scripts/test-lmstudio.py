#!/usr/bin/env python3
"""LM Studio test: read local file + metadata, call LLM with long timeout."""

import json
import os
import sys
import requests
from pathlib import Path

API_URL = "http://10.0.0.205:1234/v1/chat/completions"
MODEL = "qwen/qwen3.6-35b-a3b"
TIMEOUT = 1500  # 25 min — 22GB model cold start can be ~2 min prompt eval

FUNC_PATH = "D:/GotYaForce/research/decomp/organized/sdk/os/8022ce28_TRKNubWelcome.c"
META_PATH = "D:/GotYaForce/research/decomp/data/identified-functions.json"


def lookup_metadata(func_path: str) -> dict | None:
    """Look up address from filename in identified-functions.json."""
    addr = Path(func_path).stem.split("_")[0]  # "8022ce28"
    full_addr = f"0x{addr}"
    if not os.path.isfile(META_PATH):
        return None
    with open(META_PATH, "r", encoding="utf-8") as f:
        db = json.load(f)
    for entry in db.get("functions", []):
        if entry.get("address") == full_addr:
            return entry
    return None


def main():
    # --- Read local function source ---
    try:
        with open(FUNC_PATH, "r", encoding="utf-8") as f:
            code = f.read()
    except Exception as e:
        print(f"[ERROR] reading {FUNC_PATH}: {e}", file=sys.stderr)
        sys.exit(1)

    # --- Optionally enrich with metadata ---
    meta = lookup_metadata(FUNC_PATH)
    context_parts = [f"Deobfuscate this Ghidra function. Output only valid C code.\n\n```c\n{code}\n```"]
    if meta:
        context_parts.insert(0, f"Known role: {meta['role']} (confidence: {meta['confidence']})")

    user_msg = "\n".join(context_parts)

    print(f"--- Sending {len(code)} chars to LM Studio (timeout={TIMEOUT}s) ---")
    if meta:
        print(f"--- Metadata found: {meta['address']} ({meta.get('name', '?')}) ---")

    payload = {
        "model": MODEL,
        "temperature": 0.1,
        "max_tokens": 8192,
        "messages": [
            {
                "role": "system",
                "content": "You are an expert reverse engineer. Output only valid C code. No markdown, no explanations."
            },
            {"role": "user", "content": user_msg},
        ],
    }

    try:
        resp = requests.post(API_URL, json=payload, timeout=TIMEOUT)
        resp.raise_for_status()
    except requests.exceptions.ConnectionError:
        print("[ERROR] Cannot connect to LM Studio at localhost:1234", file=sys.stderr)
        sys.exit(1)
    except requests.exceptions.Timeout:
        print(f"[ERROR] LM Studio did not respond within {TIMEOUT}s", file=sys.stderr)
        sys.exit(1)
    except requests.exceptions.HTTPError as e:
        print(f"[ERROR] LM Studio returned error: {e}", file=sys.stderr)
        sys.exit(1)

    data = resp.json()
    output = data["choices"][0]["message"]["content"]

    print("\n--- RAW RESPONSE ---")
    print(output)
    print("\n--- END RESPONSE ---")

    clean = output.strip()
    if clean.startswith("```"):
        clean = clean.split("\n", 1)[-1]
    if clean.endswith("```"):
        clean = clean.rsplit("\n", 1)[0]

    print("\n--- CLEANED C CODE ---")
    print(clean)


if __name__ == "__main__":
    main()
