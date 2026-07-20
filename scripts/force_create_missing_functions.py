# force_create_missing_functions.py
# Run in Ghidra (Script Manager or analyzeHeadless) to force-create the 8 functions
# that the OGhidra coverage scan flagged as Ghidra-side gaps.
#
# Source: research/decomp/ogh-coverage-<date>.json -> ghidra_missing_true_gaps
# Plus the 3 Borg-constructor template entries that the prologue scan can't see.
#
# After running: save the project, then re-run ogh-scan-coverage.ps1 — gaps should drop to 0.
#
# Headless invocation:
#   analyzeHeadless.bat D:\GotYaForce\research\decomp GotchaForce ^
#       -process boot.dol ^
#       -scriptPath D:\GotYaForce\scripts ^
#       -postScript force_create_missing_functions.py ^
#       -deleteProject

# @category OGhidra
# @runtime Jython

import json
import os
import re

from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.app.cmd.function import CreateFunctionCmd


# Hand-curated template-ctor entries (no prologue; reached via function-pointer table).
# These are the 3 Borg-family constructor dispatchers cited in the port files.
TEMPLATE_CTORS = [
    "0x8007ca5c",  # NORMAL TANK / LEOPARD ctor
    "0x800cfe9c",  # ARROW NINJA / SHIJIMA ctor
    "0x80129608",  # EAGLE ROBOT / PROTO EAGLE ctor
]

# Repo root resolved from this file's location (works in both GUI and headless modes).
SCRIPT_PATH = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.dirname(SCRIPT_PATH)


def load_gaps_from_latest_report():
    """Find the newest ogh-coverage-*.json and return its ghidra_missing_true_gaps list."""
    decomp_dir = os.path.join(REPO_ROOT, "research", "decomp")
    if not os.path.isdir(decomp_dir):
        return [], None
    reports = [f for f in os.listdir(decomp_dir) if re.match(r"ogh-coverage-\d{4}-\d{2}-\d{2}\.json$", f)]
    if not reports:
        return [], None
    reports.sort(reverse=True)
    with open(os.path.join(decomp_dir, reports[0])) as f:
        data = json.load(f)
    return data.get("ghidra_missing_true_gaps", []), reports[0]


def force_create(address_hex, monitor):
    """Disassemble + create a function at the given address. Idempotent."""
    addr = currentProgram.getAddressFactory().getAddress(address_hex)
    if addr is None:
        return "skip: bad address"

    fm = currentProgram.getFunctionManager()
    existing = fm.getFunctionAt(addr)
    if existing is not None:
        return "exists: already defined as '%s'" % existing.getName()

    # Clear any data typing at the address, then disassemble.
    listing = currentProgram.getListing()
    cu = listing.getCodeUnitAt(addr)
    if cu is not None and not cu.isInstruction():
        cu.clearCodeUnits()

    DisassembleCommand(addr, None, True).applyTo(currentProgram, monitor)
    CreateFunctionCmd(addr).applyTo(currentProgram, monitor)

    new_fn = fm.getFunctionAt(addr)
    if new_fn is not None:
        return "created: '%s'" % new_fn.getName()
    return "fail: createFunction returned null"


def run():
    gap_list, report_name = load_gaps_from_latest_report()
    print("Loaded %d gaps from %s" % (len(gap_list), report_name or "(no report)"))

    # Merge gap list with hand-curated template ctors (dedup, preserve order).
    all_hex = []
    seen = set()
    for h in gap_list + TEMPLATE_CTORS:
        canonical = h.lower() if h.startswith("0x") else "0x" + h
        if canonical not in seen:
            seen.add(canonical)
            all_hex.append(canonical)

    print("Force-creating %d functions:" % len(all_hex))
    monitor.initialize(len(all_hex))
    created = 0
    skipped = 0
    failed = 0
    for h in all_hex:
        msg = force_create(h, monitor)
        print("  %s : %s" % (h, msg))
        if msg.startswith("created"):
            created += 1
        elif msg.startswith("exists"):
            skipped += 1
        else:
            failed += 1
        monitor.incrementProgress(1)

    print()
    print("Summary: created=%d  existing=%d  failed=%d" % (created, skipped, failed))

    # Save the project so the changes survive a Ghidra restart.
    try:
        currentProgram.save("force-create %d missing functions" % created, monitor)
        print("Program saved.")
    except Exception as e:
        print("WARN: save failed: %s" % str(e))


run()
