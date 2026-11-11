"""Fail-closed controls for the one supported counted-call loop shape."""
import struct
import unittest
from loop import SeedFail, seed_counted_call


class CountedCallTests(unittest.TestCase):
    words = [0x9421fff0, 0x7c0802a6, 0x90010014, 0x93e1000c,
             0x3be00000, 0x7fe3fb78, 0x48000101, 0x3bff0001,
             0x2c1f0006, 0x4180fff0, 0x80010014, 0x83e1000c,
             0x7c0803a6, 0x38210010, 0x4e800020]

    def emit(self, words=None, name="callee", interior=False, expected_target=None):
        class Map:
            by_name = {}
            def lookup(self, address):
                if expected_target is not None:
                    assert address == expected_target, (address, expected_target)
                return {"addr": address - (4 if interior else 0), "name": name}
        words = self.words if words is None else words
        return seed_counted_call({"addr": 0x80000000, "size": len(words) * 4},
                                 struct.pack(">%dI" % len(words), *words), Map())

    def test_supported_shape(self):
        source = self.emit()
        self.assertIn("int i = 0;", source)
        self.assertIn("callee(i);", source)
        self.assertIn("i += 1;", source)
        self.assertIn("while (i < 6)", source)

    def test_every_fixed_instruction_is_checked(self):
        for i in (0, 1, 2, 3, 5, 9, 10, 11, 12, 13, 14):
            with self.subTest(i=i):
                words = self.words.copy(); words[i] ^= 1
                with self.assertRaises(SeedFail): self.emit(words)

    def test_counter_registers_and_call_kind_are_checked(self):
        for i, bit in ((4, 1 << 21), (7, 1 << 16), (8, 1 << 16), (6, 1), (6, 2)):
            with self.subTest(i=i, bit=bit):
                words = self.words.copy(); words[i] ^= bit
                with self.assertRaises(SeedFail): self.emit(words)

    def test_nonterminating_or_empty_range_refused(self):
        for start, step, stop in ((0, 0, 6), (0, -1, 6), (6, 1, 6), (7, 1, 6)):
            words = self.words.copy()
            for i, value in ((4, start), (7, step), (8, stop)):
                words[i] = (words[i] & 0xffff0000) | (value & 0xffff)
            with self.assertRaises(SeedFail): self.emit(words)

    def test_signed_start_and_positive_stride(self):
        words = self.words.copy(); words[4] = 0x3be0fffe; words[7] = 0x3bff0002
        self.assertIn("int i = -2;", self.emit(words))
        self.assertIn("i += 2;", self.emit(words))

    def test_exact_valid_callee_required(self):
        self.assertIn("FUN_80000118(i);", self.emit(name="not-a-c-symbol"))
        with self.assertRaises(SeedFail): self.emit(interior=True)

    def test_extra_or_missing_instructions_refused(self):
        with self.assertRaises(SeedFail): self.emit(self.words[:-1])
        with self.assertRaises(SeedFail): self.emit(self.words + [0x60000000])

    def test_relative_call_displacements_use_call_instruction_address(self):
        self.emit(expected_target=0x80000118)
        words = self.words.copy(); words[6] = 0x4bffff01
        self.emit(words, expected_target=0x7fffff18)

    def test_signed_immediate_limits(self):
        words = self.words.copy()
        words[4], words[7], words[8] = 0x3be08000, 0x3bff7fff, 0x2c1f7fff
        source = self.emit(words)
        self.assertIn("int i = -32768;", source)
        self.assertIn("i += 32767;", source)
        self.assertIn("while (i < 32767)", source)
