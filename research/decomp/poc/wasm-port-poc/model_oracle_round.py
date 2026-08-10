#!/usr/bin/env python3
"""model_oracle_round.py — one stage-4 feedback round: the model's linked-but-wrong
unit gets the oracle verdict (mismatch counts + concrete examples, no diagnosis) and
may revise the header. Usage: python model_oracle_round.py <tag> <model-id>
"""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import model_loop as ml  # reuse chat(), build(), RUN/paths (argv already consumed there)

RUN = ml.RUN

with open(os.path.join(RUN, "gnt4_shim.h")) as f:
    cur = f.read()
with open(os.path.join(RUN, "unit_poc.c")) as f:
    unit_c = f.read()

FEEDBACK = """Your header made the unit COMPILE AND LINK, but the behavioral oracle
gate REJECTED it: against a reference implementation known to match the original
GameCube game, zz_003cd5c_ returned wrong damage on 18,505 of 20,000 test cases
(only trivial cases matched). zz_003d344_ and zz_0066298_ and FUN_80031634 all
matched perfectly, so the defect is in something only zz_003cd5c_ uses.

Examples (same inputs, integer damage):
  case A: expected 1,  got 2147483647
  case B: expected 79, got 2147483647
  case C: expected 58, got 2147483647

Remember: this is PowerPC decompiler output; every helper idiom in the header must
reproduce the ORIGINAL machine-level semantics exactly, not merely satisfy the
compiler. Return the complete corrected gnt4_shim.h in one ```c block."""

reply = ml.chat([
    {"role": "system", "content": ml.SYSTEM},
    {"role": "user", "content":
        f"Verbatim decompiled C (read-only):\n```c\n{unit_c}\n```\n\n"
        f"Current gnt4_shim.h:\n```c\n{cur}\n```\n\n" + FEEDBACK},
])
m = re.findall(r"```(?:c|cpp|h)?\s*\n(.*?)```", reply, flags=re.S)
if not m:
    print("NO CODE BLOCK; reply head:", reply[:500])
    sys.exit(1)
with open(os.path.join(RUN, "gnt4_shim.h"), "w", newline="\n") as f:
    f.write(max(m, key=len))
with open(os.path.join(RUN, "header-oracle-round.h"), "w", newline="\n") as f:
    f.write(max(m, key=len))
ok, out = ml.build()
print("rebuild:", "OK" if ok else "FAIL")
if not ok:
    print(out[:1500])
sys.exit(0 if ok else 1)
