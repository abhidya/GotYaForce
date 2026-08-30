#!/usr/bin/env python3
"""test_capture_transcript.py -- self-test for the transcript_green capture side.

No Dolphin, no emulator, no model server. Two halves:

  * PURE tests (always run): the big-endian -> little-endian FIELD-WISE swap,
    which is the subtlest piece of the capture and the one a wrong answer would
    silently corrupt a whole corpus with; plus callee-name binding.
  * ROM tests (skipped without the retail ISO): decode_function against three
    functions whose shapes were verified by hand from the disassembly, so a
    regression in the decoder is caught rather than shipped into a capture.

Run:  python research/tools/dolphin-trace/test_capture_transcript.py
      (or `python -m unittest` from this directory)
"""
from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from capture_common import Dol, swap_elems  # noqa: E402
from capture_oracle import ASSET_ROOT, unit_functions  # noqa: E402  (main-checkout root, worktree-aware)
from capture_transcript import (  # noqa: E402
    LOAD_OPS, addr_name_candidates, decode_function, function_extents,
    sweep_extent, swap_fields,
)

ISO = ASSET_ROOT / "Gotcha Force.iso"


class FieldSwap(unittest.TestCase):
    """The arena is little-endian; the console is big-endian. A raw struct
    window holds fields of different widths, so one uniform swap is wrong -- see
    capture_transcript.py's `field_widths`."""

    def test_uniform_swap_is_the_default(self):
        raw = bytes(range(8))
        self.assertEqual(swap_fields(raw, {}, 4), swap_elems(raw, 4))

    def test_u16_field_survives_next_to_u32_fields(self):
        # console bytes: a u16 0x0906 at +4, u32 0x000a0000 at +8
        raw = bytearray(16)
        struct.pack_into(">H", raw, 4, 0x0906)
        struct.pack_into(">I", raw, 8, 0x000A0000)
        arena = swap_fields(bytes(raw), {4: 2, 8: 4}, 4)
        self.assertEqual(struct.unpack_from("<H", arena, 4)[0], 0x0906)
        self.assertEqual(struct.unpack_from("<I", arena, 8)[0], 0x000A0000)

    def test_a_uniform_swap_would_get_the_u16_wrong(self):
        # the regression this map exists to prevent: with only a width-4 swap the
        # u16 at +4 reads the ADJACENT half-word instead of its own.
        raw = bytearray(8)
        struct.pack_into(">H", raw, 4, 0x0906)
        struct.pack_into(">H", raw, 6, 0xDEAD)
        uniform = swap_elems(bytes(raw), 4)
        self.assertEqual(struct.unpack_from("<H", uniform, 4)[0], 0xDEAD)
        fieldwise = swap_fields(bytes(raw), {4: 2, 6: 2}, 4)
        self.assertEqual(struct.unpack_from("<H", fieldwise, 4)[0], 0x0906)

    def test_a_field_running_past_the_window_is_ignored_not_truncated(self):
        raw = bytes(range(4))
        self.assertEqual(swap_fields(raw, {2: 8}, 4), swap_elems(raw, 4))

    def test_byte_fields_are_untouched(self):
        raw = bytes(range(4))
        out = swap_fields(raw, {1: 1}, 4)
        self.assertEqual(out[1], raw[1])


class CalleeNaming(unittest.TestCase):
    def test_both_pipeline_shapes(self):
        self.assertEqual(addr_name_candidates(0x800C42A8),
                         ["zz_00c42a8_", "FUN_800c42a8"])


class LoadTable(unittest.TestCase):
    def test_widths_are_the_powerpc_ones(self):
        self.assertEqual(LOAD_OPS[32][1], 4)   # lwz
        self.assertEqual(LOAD_OPS[34][1], 1)   # lbz
        self.assertEqual(LOAD_OPS[40][1], 2)   # lhz
        self.assertEqual(LOAD_OPS[42][1], 2)   # lha
        self.assertEqual(LOAD_OPS[48][1], 4)   # lfs
        self.assertEqual(LOAD_OPS[50][1], 8)   # lfd


@unittest.skipUnless(ISO.is_file(), f"retail ISO not present at {ISO}")
class RomDecode(unittest.TestCase):
    """Shapes verified by hand against the disassembly (see the commit message)."""

    @classmethod
    def setUpClass(cls):
        cls.dol = Dol.from_iso(ISO)

    def test_pure_thunk(self):
        # 800c4448: prologue, `bl 0x80088e50`, epilogue, blr. Sets NO argument
        # register -- it forwards whatever it received.
        sh = decode_function(self.dol, 0x800C4448, 0x800C4468)
        self.assertEqual([c["target"] for c in sh["calls"]], ["0x80088e50"])
        self.assertEqual(sh["indirect_calls"], [])
        self.assertEqual(sh["returns"], ["0x800c4464"])
        self.assertEqual(sh["loads"], [])

    def test_two_calls_and_a_field_load(self):
        # 800c4468: `lwz r3,0xe0(r3)` then two bl's.
        sh = decode_function(self.dol, 0x800C4468, 0x800C44A8)
        self.assertEqual([c["target"] for c in sh["calls"]],
                         ["0x800076d0", "0x800097b4"])
        self.assertIn(("lwz", 0xE0, 4),
                      [(l["op"], l["disp"], l["width"]) for l in sh["loads"]])

    def test_field_widths_of_a_branching_function(self):
        # 801a1bbc: `lhz`-class read at +0x3e8 (u16 borg id) and `lwz` at +0x5b4.
        # A uniform swap cannot serve both; this is where field_widths is born.
        sh = decode_function(self.dol, 0x801A1BBC, 0x801A1C14)
        widths = {l["disp"]: l["width"] for l in sh["loads"]}
        self.assertEqual(widths.get(0x3E8), 2)
        self.assertEqual(widths.get(0x5B4), 4)
        self.assertEqual(sh["indirect_calls"], [])

    def test_an_indirect_call_is_seen_not_missed(self):
        # 800c4838 dispatches through a ROM function-pointer table (`bctrl` at
        # 0x800c48b8); the survey and `sites` both refuse it, so the decoder must
        # actually detect it.
        end = sweep_extent(self.dol, 0x800C4838)
        sh = decode_function(self.dol, 0x800C4838, end)
        self.assertEqual([i["at"] for i in sh["indirect_calls"]], ["0x800c48b8"],
                         "an indirect dispatch must be reported, never silently dropped")

    def test_the_extent_sweep_stops_at_THIS_function_not_a_later_one(self):
        # Regression: taking the LAST `blr` within the search limit ran straight
        # through the neighbouring functions, which would have put their call
        # sites into the plan and let unrelated breakpoints corrupt a capture.
        self.assertEqual(sweep_extent(self.dol, 0x800C4838), 0x800C48D0)
        self.assertEqual(sweep_extent(self.dol, 0x800C4448), 0x800C4468)
        self.assertEqual(sweep_extent(self.dol, 0x800C4468), 0x800C44A8)

    def test_unit_extents_never_overlap(self):
        fns = unit_functions("auto-c0020-007")
        ends = function_extents(fns, self.dol)
        ordered = sorted(a for a, _ in fns)
        for i, a in enumerate(ordered[:-1]):
            self.assertLessEqual(ends[a], ordered[i + 1],
                                 f"{a:#x} decodes into the next function")


if __name__ == "__main__":
    unittest.main(verbosity=2)
