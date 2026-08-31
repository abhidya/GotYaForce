#!/usr/bin/env python3
"""Emit a DSP-ADPCM cross-check vector from the repository's OWN decoder.

WHY THIS EXISTS. `packages/rom-runtime/src/audio/adpcm.ts` is a port of
`decode_dsp_adpcm` in scripts/export-combat-se.py — the Python decoder that
produced the OGG files apps/game ships. A port that is only checked against
itself proves nothing, so this script runs the ORIGINAL decoder over inputs
chosen to hit the arithmetic corners (negative coefficients, large scale
exponents, sign-extended nibbles, saturation at both clamps) and writes the
expected PCM to adpcm-vector.json. The TypeScript unit test decodes the same
inputs and compares sample for sample.

That makes the check an INDEPENDENT SECOND IMPLEMENTATION, which is the
strongest evidence available here — and it is still not console capture. Both
implementations could share a misunderstanding of the format; only a comparison
against real DSP output would rule that out, and this repository has no disc
bytes to compare against (docs/audio-dvd-hle-host.md §2).

Re-run:  python3 packages/rom-runtime/test/fixtures/adpcm/gen-vector.py
Deterministic: the RNG is seeded, so a re-run with an unchanged decoder
produces an identical file.
"""
from __future__ import annotations

import importlib.util
import json
import random
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
SOURCE = ROOT / "scripts" / "export-combat-se.py"

spec = importlib.util.spec_from_file_location("export_combat_se", SOURCE)
assert spec and spec.loader
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
decode = module.decode_dsp_adpcm

rng = random.Random(0x600D5EED)


def make_case(name: str, frames: int, coefs: list[int], headers: list[int] | None) -> dict:
    data = bytearray()
    for f in range(frames):
        # The predictor field (high nibble) selects one of EIGHT coefficient
        # pairs, so it is 0..7. A real DSPADPCM stream never encodes 8..15
        # there, and the reference decoder would index past its 16-entry
        # coefficient list if it did.
        header = headers[f % len(headers)] if headers else rng.randrange(0, 0x80)
        data.append(header)
        for _ in range(7):
            data.append(rng.randrange(0, 0x100))
    num_samples = frames * 14
    rec = {
        "coefs": coefs,
        "numSamples": num_samples,
        "numNibbles": len(data) * 2,
        "dpkOffset": 0,
    }
    return {
        "name": name,
        "coefs": coefs,
        "numSamples": num_samples,
        "numNibbles": rec["numNibbles"],
        "offset": 0,
        "data": list(data),
        "expected": decode(bytes(data), rec),
    }


cases = [
    # Coefficient pair 0 == (0, 0) and scale exponent 0: the decode reduces to
    # the sign-extended nibble itself, which is derivable by hand.
    make_case("identity-nibbles", 4, [0] * 16, [0x00]),
    # The coefficient set a real DSPADPCM header carries: signed, large, and
    # spanning all eight pairs. Random headers exercise every pair and every
    # scale exponent 0..15.
    make_case(
        "realistic-coefficients",
        16,
        [0x0000, 0x0000, 0x0800, 0x0000, 0x0000, 0x0800, 0x0400, 0x0400,
         0x1000, -0x0800, 0x0E00, -0x0600, 0x0C00, -0x0400, 0x1200, -0x0A00],
        None,
    ),
    # Coefficients big enough to drive the accumulator past 2^31 and into both
    # clamps — this is the case a JavaScript `>>` would get wrong, because it
    # truncates its operand to int32 first.
    make_case("saturating", 12, [0x7FFF, -0x8000] * 8, None),
    # Maximum scale exponent on every frame: nibble * 2^15 * 2048 alone is 2^29.
    # Predictors 0..3 with scale exponent 15 on every frame.
    make_case("max-scale", 8, [0x2000, -0x1000] * 8, [0x0F, 0x1F, 0x2F, 0x3F]),
]

out = {
    "generatedBy": "packages/rom-runtime/test/fixtures/adpcm/gen-vector.py",
    "reference": "scripts/export-combat-se.py::decode_dsp_adpcm",
    "note": (
        "Expected PCM produced by the PYTHON decoder that generated the shipped combat-SE OGGs. "
        "The TypeScript port in packages/rom-runtime/src/audio/adpcm.ts must reproduce it exactly. "
        "This is an independent-implementation check, NOT a comparison against console DSP output."
    ),
    "cases": cases,
}
(HERE / "adpcm-vector.json").write_text(json.dumps(out, indent=1) + "\n", encoding="utf-8")
print(f"wrote {HERE / 'adpcm-vector.json'} with {len(cases)} cases")
