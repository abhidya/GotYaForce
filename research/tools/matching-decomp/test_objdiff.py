"""ROM/compiler-free negative controls for the matching oracle.

Run: python3 -m unittest discover -s research/tools/matching-decomp -p 'test_*.py'
These synthetic instructions prove comparator behavior, not retail matches.
"""
import struct
import unittest

from objdiff import compare, Elf32BE, SHT_REL
from match import expected_symbols
from datareloc import retail_data_addresses


class BranchRelocationTests(unittest.TestCase):
    retail = struct.pack(">II", 0x48000101, 0x4e800020)
    candidate = struct.pack(">II", 0x48000001, 0x4e800020)

    def verdict(self, relocs, resolver=False, expected=True):
        kwargs = {"expected_syms": {0: "callee"} if expected else None}
        if resolver:
            kwargs.update(retail_addrs={},
                          resolve_symbol=lambda name: (None, None, "synthetic"))
        return compare(self.retail, self.candidate, relocs, **kwargs)

    def test_correct_callee(self):
        for resolver in (False, True):
            with self.subTest(resolver=resolver):
                self.assertEqual(self.verdict([(0, 10, "callee", 0)], resolver)["verdict"], "MATCH")

    def test_expected_symbols_requires_exact_entry(self):
        class Map:
            def lookup(self, address):
                return {"addr": 0x80000100, "name": "callee"}
        base = 0x80000000
        exact = struct.pack(">I", 0x48000101)
        interior = struct.pack(">I", 0x48000105)
        self.assertEqual(expected_symbols(Map(), exact, base), {0: "callee"})
        self.assertEqual(expected_symbols(Map(), interior, base), {})

    def test_wrong_callee(self):
        self.assertEqual(self.verdict([(0, 10, "other", 0)])["verdict"], "MISMATCH")

    def test_nonzero_branch_addend(self):
        for addend in (-4, 4):
            for resolver in (False, True):
                with self.subTest(addend=addend, resolver=resolver):
                    result = self.verdict([(0, 10, "callee", addend)], resolver)
                    self.assertEqual(result["verdict"], "MISMATCH")
                    self.assertEqual(result["reloc_symbol_errors"][0]["addend"], addend)

    def test_nonbranch_type_cannot_borrow_branch_verification(self):
        for relocation_type in (1, 255):
            for resolver in (False, True):
                with self.subTest(relocation_type=relocation_type, resolver=resolver):
                    self.assertEqual(self.verdict([(0, relocation_type, "callee", 0)], resolver)["verdict"], "MATCH_UNVERIFIED")

    def test_second_relocation_at_verified_offset_still_needs_check(self):
        for resolver in (False, True):
            with self.subTest(resolver=resolver):
                result = self.verdict([(0, 10, "callee", 0), (0, 255, "callee", 0)], resolver)
                self.assertEqual(result["verdict"], "MATCH_UNVERIFIED")
                self.assertEqual(len(result["unchecked_relocs"]), 1)

    def test_missing_expected_symbol_stays_unverified(self):
        self.assertEqual(self.verdict([(0, 10, "callee", 0)], expected=False)["verdict"], "MATCH_UNVERIFIED")

    def test_verified_data_relocation_is_unchanged(self):
        retail = struct.pack(">II", 0x906dab20, 0x4e800020)
        candidate = struct.pack(">II", 0x90600000, 0x4e800020)
        result = compare(retail, candidate, [(0, 109, "global", 0)],
                         retail_addrs={0: (0x804360c0, "sda")},
                         resolve_symbol=lambda name: (0x804360c0, "synthetic", ""))
        self.assertEqual(result["verdict"], "MATCH")
        self.assertEqual(len(result["data_relocs_verified"]), 1)

    def test_misaligned_sda21_cannot_borrow_word_address(self):
        retail = struct.pack(">II", 0x906dab20, 0x4e800020)
        candidate = struct.pack(">II", 0x90600000, 0x4e800020)
        result = compare(retail, candidate, [(2, 109, "global", 0)],
                         retail_addrs={0: (0x804360c0, "sda")},
                         resolve_symbol=lambda name: (0x804360c0, "synthetic", ""))
        self.assertEqual(result["verdict"], "MATCH_UNVERIFIED")

    def test_wrong_branch_does_not_become_merely_unverified(self):
        result = self.verdict([(0, 10, "callee", 4), (0, 255, "callee", 0)])
        self.assertEqual(result["verdict"], "MISMATCH")
        self.assertEqual(len(result["unchecked_relocs"]), 1)

    def test_unmasked_instruction_difference_stays_mismatch(self):
        candidate = struct.pack(">II", 0x48000001, 0x60000000)
        result = compare(self.retail, candidate, [(0, 10, "callee", 0)], expected_syms={0: "callee"})
        self.assertEqual(result["verdict"], "MISMATCH")
        self.assertEqual(result["first_diff"]["offset"], 4)


class AbsoluteRelocationTests(unittest.TestCase):
    def check(self, address=0x8043b5a0, hi_type=6, low_type=4,
              symbol_address=None, addend=0, offsets=(2, 6)):
        hi = ((address + 0x8000) >> 16) & 0xffff
        retail = struct.pack(">III", 0x3c600000 | hi,
                             0x38630000 | (address & 0xffff), 0x4e800020)
        candidate = struct.pack(">III", 0x3c600000, 0x38630000, 0x4e800020)
        return compare(retail, candidate,
                       [(offsets[0], hi_type, "global", addend),
                        (offsets[1], low_type, "global", addend)],
                       retail_addrs=retail_data_addresses(retail, 0x80000000, {}),
                       resolve_symbol=lambda name: (symbol_address if symbol_address is not None else address,
                                                    "synthetic", ""))

    def test_standard_elf_ha_lo_at_halfword_offsets(self):
        for address in (0x804360c0, 0x8043b5a0):
            self.assertEqual(self.check(address=address)["verdict"], "MATCH")

    def test_wrong_global(self):
        self.assertEqual(self.check(symbol_address=0x8043b5a4)["verdict"], "MISMATCH")

    def test_wrong_addend(self):
        self.assertEqual(self.check(addend=4)["verdict"], "MISMATCH")

    def test_correct_addend(self):
        self.assertEqual(self.check(symbol_address=0x8043b59c, addend=4)["verdict"], "MATCH")

    def test_hi_is_not_ha_for_negative_low_half(self):
        self.assertEqual(self.check(hi_type=5)["verdict"], "MISMATCH")

    def test_wrong_low_half_type(self):
        self.assertEqual(self.check(low_type=5)["verdict"], "MISMATCH")

    def test_word_offsets_are_not_halfword_offsets(self):
        self.assertEqual(self.check(offsets=(0, 4))["verdict"], "MATCH_UNVERIFIED")

    def test_plain_addr16_does_not_truncate_full_addresses(self):
        self.assertEqual(self.check(low_type=3)["verdict"], "MISMATCH")

    def test_addr24_is_not_a_data_halfword(self):
        self.assertNotEqual(self.check(low_type=2)["verdict"], "MATCH")

    def test_addr14_is_not_ha(self):
        self.assertNotEqual(self.check(hi_type=7)["verdict"], "MATCH")


class OracleBoundaryTests(unittest.TestCase):
    def test_partial_words_are_not_verified(self):
        word = struct.pack(">I", 0x4e800020)
        for a, b in ((word, word + b"x"), (word + b"x", word + b"y"),
                     (word + b"x", word + b"x")):
            self.assertEqual(compare(a, b)["verdict"], "MISMATCH")

    def test_addr32_requires_aligned_complete_word(self):
        retail = struct.pack(">II", 0x804360c0, 0x4e800020)
        for offset in (-4, 1, 2, 6, 8):
            result = compare(retail, retail, [(offset, 1, "global", 0)],
                             retail_addrs={},
                             resolve_symbol=lambda name: (0x804360c0, "synthetic", ""))
            self.assertNotEqual(result["verdict"], "MATCH")

    def test_implicit_addends_are_not_silently_discarded(self):
        elf = object.__new__(Elf32BE)
        elf.sh = [{"type": SHT_REL, "name": ".rel.text"}]
        elf.symbols = lambda: []
        with self.assertRaisesRegex(ValueError, "implicit addends"):
            elf.relocs_for(".text")


if __name__ == "__main__":
    unittest.main()
