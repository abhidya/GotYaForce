"""Canonical call names preserve exact entry/type/addend proof."""
import struct
import unittest
from dolsym import function_c_name
from match import expected_symbols
from objdiff import compare
from loop import seed_wrapper, SeedFail
from seed_cfg import Lifter, SeedFail as CfgSeedFail


class Map:
    def __init__(self, name="gnt4-OSDisableInterrupts-bl", address=0x80000100, collision=None):
        self.record = {"name": name, "addr": address}
        self.by_name = {name: self.record}
        if collision is not None:
            self.by_name["FUN_80000100"] = {"name": "FUN_80000100", "addr": collision}
    def lookup(self, address):
        return self.record


class CallAliasTests(unittest.TestCase):
    base = 0x80000000
    retail = struct.pack(">II", 0x48000101, 0x4e800020)
    candidate = struct.pack(">II", 0x48000001, 0x4e800020)

    def check(self, name="FUN_80000100", addend=0, rtype=10, smap=None):
        return compare(self.retail, self.candidate, [(0, rtype, name, addend)],
                       expected_syms=expected_symbols(smap or Map(), self.retail, self.base))

    def test_valid_map_name_unchanged(self):
        m = Map(name="OSDisableInterrupts")
        self.assertEqual(function_c_name(m.record, m), "OSDisableInterrupts")

    def test_invalid_name_encodes_exact_entry(self):
        self.assertEqual(expected_symbols(Map(), self.retail, self.base), {0: "FUN_80000100"})
        self.assertEqual(self.check()["verdict"], "MATCH")

    def test_wrong_alias_address_mismatches(self):
        self.assertEqual(self.check(name="FUN_80000104")["verdict"], "MISMATCH")

    def test_alias_does_not_relax_addend_or_type(self):
        self.assertEqual(self.check(addend=4)["verdict"], "MISMATCH")
        self.assertNotEqual(self.check(rtype=255)["verdict"], "MATCH")

    def test_interior_target_stays_unverified(self):
        self.assertEqual(self.check(smap=Map(address=0x800000fc))["verdict"], "MATCH_UNVERIFIED")

    def test_collision_at_other_entry_stays_unverified(self):
        m = Map(collision=0x80000200)
        self.assertIsNone(function_c_name(m.record, m))
        self.assertEqual(self.check(smap=m)["verdict"], "MATCH_UNVERIFIED")

    def test_same_entry_alias_is_not_a_collision(self):
        self.assertEqual(self.check(smap=Map(collision=0x80000100))["verdict"], "MATCH")

    def test_wrapper_emits_same_alias_as_oracle(self):
        # Call at +12 branches to +0x100, so displacement is +0xf4.
        words = [0x9421fff0, 0x7c0802a6, 0x90010014, 0x480000f5,
                 0x80010014, 0x7c0803a6, 0x38210010, 0x4e800020]
        source = seed_wrapper({"addr": self.base, "size": 32}, struct.pack(">8I", *words), Map())
        self.assertIn("FUN_80000100(", source)

    def test_wrapper_refuses_interior_targets_and_collisions(self):
        words = [0x9421fff0, 0x7c0802a6, 0x90010014, 0x480000f5,
                 0x80010014, 0x7c0803a6, 0x38210010, 0x4e800020]
        for m in (Map(address=0x800000fc), Map(collision=0x80000200)):
            with self.assertRaises(SeedFail):
                seed_wrapper({"addr": self.base, "size": 32}, struct.pack(">8I", *words), m)

    def test_cfg_refuses_interior_targets_and_collisions_before_argument_inference(self):
        for m in (Map(address=0x800000fc), Map(collision=0x80000200)):
            lifter = object.__new__(Lifter)
            lifter.smap = m
            with self.assertRaises(CfgSeedFail):
                lifter.do_call(self.base, {"li": 0x100}, {"g": {}, "f": {}}, [])

    def test_alias_requires_symbol_index_for_collision_check(self):
        m = Map()
        del m.by_name
        self.assertIsNone(function_c_name(m.record, m))
        self.assertEqual(self.check(smap=m)["verdict"], "MATCH_UNVERIFIED")
