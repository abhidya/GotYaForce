"""ROM/compiler-free negative controls for the matching oracle.

Run: python3 -m unittest discover -s research/tools/matching-decomp -p 'test_*.py'
These synthetic instructions prove comparator behavior, not retail matches.
"""
import struct
import unittest

from objdiff import compare
from match import expected_symbols


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

    def test_wrong_branch_does_not_become_merely_unverified(self):
        result = self.verdict([(0, 10, "callee", 4), (0, 255, "callee", 0)])
        self.assertEqual(result["verdict"], "MISMATCH")
        self.assertEqual(len(result["unchecked_relocs"]), 1)

    def test_unmasked_instruction_difference_stays_mismatch(self):
        candidate = struct.pack(">II", 0x48000001, 0x60000000)
        result = compare(self.retail, candidate, [(0, 10, "callee", 0)], expected_syms={0: "callee"})
        self.assertEqual(result["verdict"], "MISMATCH")
        self.assertEqual(result["first_diff"]["offset"], 4)


if __name__ == "__main__":
    unittest.main()
