#!/usr/bin/env python3
"""Synthetic normal-matrix evidence tests. No original inputs or execution."""
import hashlib
import struct
import unittest
from unittest.mock import patch

import read_archived_normal_matrix_evidence as n


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class EvidenceTests(unittest.TestCase):
    def decode(self, word, pc=0x80046e7c):
        return n.decode_selected(word, pc)

    def test_byte_stores_and_order(self):
        for word, displacement in ((0x98031d96, 0x1d96), (0x98031d97, 0x1d97)):
            self.assertEqual(self.decode(word), dict(mnemonic='stb', rS=0, rA=3, displacement=displacement))
        self.assertEqual(self.decode((38 << 26) | (7 << 21) | (4 << 16) | 0xffff),
                         dict(mnemonic='stb', rS=7, rA=4, displacement=-1))

    def test_control_bit(self):
        self.assertEqual(self.decode(0x54000085),
                         dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=2, ME=2, Rc=1))

    def test_selector_mask(self):
        self.assertEqual(self.decode(0x540016ba),
                         dict(mnemonic='rlwinm', rS=0, rA=0, SH=2, MB=26, ME=29, Rc=0))

    def test_indexed_dispatch(self):
        self.assertEqual(self.decode(0x7d86002e), dict(mnemonic='lwzx', rD=12, rA=6, rB=0))
        self.assertEqual(self.decode(0x7d8903a6), dict(mnemonic='mtctr', rS=12))
        self.assertEqual(self.decode(0x4e800421), dict(mnemonic='bctrl'))
        self.assertIsNone(self.decode(0x7c0803a6))  # mtlr remains unselected.
        self.assertIsNone(self.decode(0x4e800420))  # bctr is not this fixed call form.

    def test_direct_damping_call(self):
        self.assertEqual(self.decode(0x48000045, 0x80046eb0),
                         dict(mnemonic='bl', target='80046ef4', AA=0))

    def test_source_loads(self):
        for word, register, base, displacement in (
            (0x808304b0, 4, 3, 0x4b0), (0x80e304b0, 7, 3, 0x4b0),
            (0x889b1d96, 4, 27, 0x1d96), (0x887b1d97, 3, 27, 0x1d97)):
            expected = 'lwz' if displacement == 0x4b0 else 'lbz'
            self.assertEqual(self.decode(word), dict(mnemonic=expected, rD=register, rA=base, displacement=displacement))

    def test_sign_extended_counts(self):
        self.assertEqual(self.decode(0x7c840774), dict(mnemonic='extsb', rS=4, rA=4, Rc=0))
        self.assertEqual(self.decode(0x7c630774), dict(mnemonic='extsb', rS=3, rA=3, Rc=0))
        self.assertEqual(self.decode(0x7c000774), dict(mnemonic='extsb', rS=0, rA=0, Rc=0))

    def test_damping_arithmetic(self):
        self.assertEqual(self.decode(0xec010032), dict(mnemonic='fmuls', fD=0, fA=1, fC=0))
        self.assertEqual(self.decode(0xd0031d60), dict(mnemonic='stfs', fD=0, rA=3, displacement=0x1d60))

    def test_invalid_word(self):
        for word in (-1, 1 << 32, True, '0'):
            with self.assertRaises(n.c.FormatError):
                self.decode(word)

    def test_invalid_pc(self):
        for pc in (-1, 1, 1 << 32, True):
            with self.assertRaises(n.c.FormatError):
                self.decode(0, pc)

    def test_range_allowlist_before_read(self):
        with self.assertRaises(n.c.FormatError):
            n.range_evidence(None, 21, 0x80046600, 152)

    def test_range_root_before_read(self):
        with self.assertRaises(n.c.FormatError):
            n.range_evidence(None, 22, 0x800465fc, 156)

    def test_range_digest(self):
        with self.assertRaises(n.c.FormatError):
            n.range_evidence(FakeDB(bytes(156)), 21, 0x800465fc, 156)

    def test_synthetic_range(self):
        raw = struct.pack('>II', 0x98031d96, 0x98031d97)
        db = FakeDB(raw)
        with patch.object(n, 'RANGES', ((0x80046e8c, 8, hashlib.sha256(raw).hexdigest()),)):
            result = n.range_evidence(db, 21, 0x80046e8c, 8)
        self.assertEqual([i['displacement'] for i in result['instructions']], [0x1d96, 0x1d97])
        self.assertEqual([i['address'] for i in result['instructions']], ['80046e8c', '80046e90'])
        self.assertEqual(db.calls, [(21, 0x80046e8c - n.TEXT_START, 8, n.TEXT_LENGTH)])

    def test_range_width(self):
        raw = bytes(8)
        with patch.object(n, 'RANGES', ((0x800465fc, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaises(n.c.FormatError):
                n.range_evidence(FakeDB(raw), 21, 0x800465fc, 4)

    def test_dispatch_targets(self):
        raw = struct.pack('>16I', *n.TABLE_TARGETS)
        db = FakeDB(raw)
        result = n.dispatch_evidence(db)
        self.assertEqual(result['damping_selectors'], [1])
        self.assertEqual(result['entries'][1], dict(selector=1, address='802d0d64', target='80046ef4'))
        self.assertEqual(len(result['entries']), 16)
        self.assertEqual(db.calls, [(199, 0x802d0d60 - 0x802bae60, 64, 0xf42c0)])

    def test_dispatch_width_and_hash(self):
        for raw in (bytes(60), bytes(64), bytes(68)):
            with self.assertRaises(n.c.FormatError):
                n.dispatch_evidence(FakeDB(raw))

    def test_dispatch_targets_independent_of_hash(self):
        raw = struct.pack('>16I', *([0x80046ef4] * 16))
        with patch.object(n, 'TABLE_SHA', hashlib.sha256(raw).hexdigest()):
            with self.assertRaises(n.c.FormatError):
                n.dispatch_evidence(FakeDB(raw))

    def test_damping_constant(self):
        db = FakeDB(bytes.fromhex('3f4ccccd'))
        result = n.constant_evidence(db, 0x8043709c)
        self.assertEqual(result['value'], 0.800000011920929)
        self.assertEqual(result['bits'], '3f4ccccd')
        self.assertEqual(db.calls, [(263, 0x8043709c - 0x80436a20, 4, 27360)])

    def test_constant_allowlist_before_read(self):
        with self.assertRaises(n.c.FormatError):
            n.constant_evidence(None, 0x804370dc)

    def test_constant_width_and_bits(self):
        for raw in (bytes(4), bytes.fromhex('3f4ccccd00'), bytes.fromhex('3f4ccc')):
            with self.assertRaises(n.c.FormatError):
                n.constant_evidence(FakeDB(raw), 0x8043709c)

    def test_authentication_first(self):
        with self.assertRaises(n.c.FormatError):
            n.inspect(bytes(32), '0' * 64)


if __name__ == '__main__':
    unittest.main()
