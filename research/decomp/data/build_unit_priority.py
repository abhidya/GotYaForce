"""Generate unit-priority.json: the product_priority sidecar for the wasm-unit queue.

Design: research/tools/OGhidra/docs/compile-fix-loop-design.md section 2.14
[V4-2] -- pending units were served in chunk order, an accident of the
address-space walk uncorrelated with what a playable game needs. This sidecar
gives the driver's `_next_unit` a leading product_priority component (HIGHER
serves first); an absent file means all-zero priorities, i.e. the previous
(attempts, queue-order) behaviour unchanged.

Location note: the sidecar lives HERE in research/decomp/data/ (tracked),
not next to the queue under research/decomp/generated/finish-game-port/ --
that directory is wholesale-gitignored (.gitignore) and a `!file` negation
cannot rescue a path whose parent directory is excluded. The driver
(research/tools/OGhidra/src/port_wasm_units.py) reads this path directly.

Priority formula, per unit, computed from oracle-registry.json (built by
build_oracle_registry.py in this directory):

    priority = gap_partial_slots * 100          # 0-3: partially-implemented
                                                # action slots in the unit's
                                                # family-ctor neighborhood --
                                                # the dominant combat-fidelity
                                                # gap (strategy doc option C)
             + min(port_citations, 9) * 10      # capped: TS-port citations
                                                # graded "port" across the
                                                # unit's functions (existing
                                                # browser-port evidence)
             + CHEAPNESS[max_structural_class]  # A=5 B=4 C=3 D=2 E=1: a unit
                                                # is as expensive as its most
                                                # entangled function, so
                                                # structurally cheaper units
                                                # break ties first

Deterministic: same registry in, byte-identical JSON out (sorted units,
sorted keys, fixed indent). Regenerate after every oracle-registry rebuild:

    python research/decomp/data/build_unit_priority.py
"""

from __future__ import annotations

import json
from pathlib import Path

from oracle_registry_schema import load_oracle_registry_v1

DATA_DIR = Path(__file__).resolve().parent
PRODUCT_ROOT = DATA_DIR.parents[2]
REGISTRY_PATH = DATA_DIR / "oracle-registry.json"
OUTPUT_PATH = DATA_DIR / "unit-priority.json"

# Structural cheapness bonus: class A (leaf, value-returning, no globals or
# pointer args) is the cheapest to port, class E (3+ callees) the dearest.
CHEAPNESS = {"A": 5, "B": 4, "C": 3, "D": 2, "E": 1}
CLASS_RANK = {"A": 0, "B": 1, "C": 2, "D": 3, "E": 4}


def build_priorities(registry: dict) -> dict[str, int]:
    per_unit: dict[str, dict] = {}
    for fn in registry["functions"]:
        agg = per_unit.setdefault(
            fn["unit"], {"gap": 0, "port_citations": 0, "max_rank": 0}
        )
        gap = fn.get("gap_alignment")
        if gap:
            agg["gap"] = max(agg["gap"], int(gap.get("partial_slots", 0)))
        agg["port_citations"] += sum(
            1 for cite in (fn.get("ts_citations") or []) if cite.get("grade") == "port"
        )
        agg["max_rank"] = max(
            agg["max_rank"], CLASS_RANK.get(fn.get("structural_class", "E"), 4)
        )
    return {
        unit: (
            agg["gap"] * 100
            + min(agg["port_citations"], 9) * 10
            + CHEAPNESS["ABCDE"[agg["max_rank"]]]
        )
        for unit, agg in per_unit.items()
    }


def load_registry_for_priority() -> dict:
    """Load only a complete, source-corroborated schema-1 owner registry."""

    return load_oracle_registry_v1(REGISTRY_PATH, PRODUCT_ROOT)


def main() -> int:
    registry = load_registry_for_priority()
    priorities = build_priorities(registry)
    payload = {
        "generated_by": "research/decomp/data/build_unit_priority.py",
        "source": "research/decomp/data/oracle-registry.json",
        "source_generated_at": registry.get("meta", {}).get("generated_at"),
        "formula": (
            "gap_partial_slots*100 + min(port_citations,9)*10 "
            "+ cheapness(max_structural_class: A=5 B=4 C=3 D=2 E=1); higher first"
        ),
        "units_total": len(priorities),
        "priorities": {unit: priorities[unit] for unit in sorted(priorities)},
    }
    with OUTPUT_PATH.open("w", encoding="utf-8", newline="\n") as fh:
        fh.write(json.dumps(payload, indent=1, sort_keys=False) + "\n")
    nonzero = sum(1 for value in priorities.values() if value > 0)
    top = sorted(priorities.items(), key=lambda kv: (-kv[1], kv[0]))[:5]
    print(f"wrote {OUTPUT_PATH} ({len(priorities)} units, {nonzero} nonzero)")
    for unit, value in top:
        print(f"  {unit}: {value}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
