#!/usr/bin/env python3
"""Synthetic fixed-reader checks. No archived instruction execution or fixtures."""
import hashlib
import struct
import unittest
from unittest.mock import patch

import read_archived_terrain_query_evidence as t


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, [dict(synthetic=True)]


def d_form(op, d, a, immediate):
    return (op << 26) | (d << 21) | (a << 16) | (immediate & 65535)


def arithmetic(op, xo, d, a, b=0, fc=0):
    return (op << 26) | (d << 21) | (a << 16) | (b << 11) | (fc << 6) | (xo << 1)


def compare(xo, a, b, field=0):
    return (63 << 26) | (field << 23) | (a << 16) | (b << 11) | (xo << 1)


def branch(pc, target, bo, bi):
    return (16 << 26) | (bo << 21) | (bi << 16) | ((target - pc) & 65532)


class EvidenceTests(unittest.TestCase):
    def test_fdivs_operands_and_nonrecord_guard(self):
        word = arithmetic(59, 18, 7, 7, 5)
        self.assertEqual(t.decode_selected(word, 0),
                         dict(mnemonic='fdivs', fD=7, fA=7, fB=5))
        for bad in (word | 1, word | (1 << 6)):
            with self.assertRaises(t.c.FormatError):
                t.decode_selected(bad, 0)

    def test_fcmpu_fields_and_reserved_guard(self):
        word = compare(0, 2, 0, 3)
        self.assertEqual(t.decode_selected(word, 0),
                         dict(mnemonic='fcmpu', BF=3, fA=2, fB=0))
        for bad in (word | 1, word | (1 << 21), word | (1 << 22)):
            with self.assertRaises(t.c.FormatError):
                t.decode_selected(bad, 0)

    def test_cror_operands_preserve_comparison_direction(self):
        for ba in (0, 1):
            word = (19 << 26) | (2 << 21) | (ba << 16) | (2 << 11) | (449 << 1)
            self.assertEqual(t.decode_selected(word, 0),
                             dict(mnemonic='cror', BT=2, BA=ba, BB=2))
            with self.assertRaises(t.c.FormatError):
                t.decode_selected(word | 1, 0)

    def test_existing_fcmpo_and_fmadds_preserve_operands(self):
        self.assertEqual(t.decode_selected(compare(32, 30, 7), 0),
                         dict(mnemonic='fcmpo', BF=0, fA=30, fB=7))
        self.assertEqual(t.decode_selected(arithmetic(59, 29, 30, 3, 0, 1), 0),
                         dict(mnemonic='fmadds', fD=30, fA=3, fC=1, fB=0))

    def test_reject_invalid_word_and_pc(self):
        for word in (-1, 1 << 32, True, 1.0, '0'):
            with self.assertRaises(t.c.FormatError):
                t.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 0.0):
            with self.assertRaises(t.c.FormatError):
                t.decode_selected(0, pc)

    def test_fixed_range_contract(self):
        self.assertEqual([(a, n) for a, n, _ in t.RANGES], [
            (0x8003d6e4, 640), (0x8003f320, 872),
            (0x8003fa68, 152), (0x8003fb00, 88)])
        for a, n, digest in t.RANGES:
            self.assertEqual(len(digest), 64)
            with self.assertRaises(t.c.FormatError):
                t.range_evidence(None, 21, a + 4, n - 4)
            with self.assertRaises(t.c.FormatError):
                t.range_evidence(None, 22, a, n)
            with self.assertRaises(t.c.FormatError):
                t.range_evidence(FakeDB(bytes(n)), 21, a, n)

    def test_synthetic_range_has_derived_fields_and_trace_not_bytes(self):
        words = [d_form(48, 1, 3, 0), d_form(48, 2, 2, -31268),
                 arithmetic(59, 18, 0, 1, 2), arithmetic(63, 15, 0, 0, 0),
                 d_form(54, 0, 1, 32), d_form(32, 3, 1, 36), 0x4e800020]
        raw = struct.pack('>7I', *words)
        start = 0x8003fa68
        digest = hashlib.sha256(raw).hexdigest()
        db = FakeDB(raw)
        with patch.object(t, 'RANGES', ((start, len(raw), digest),)):
            result = t.range_evidence(db, 21, start, len(raw))
        self.assertEqual(result['sha256'], digest)
        self.assertEqual(result['spans'], [dict(synthetic=True)])
        self.assertEqual([i['mnemonic'] for i in result['instructions']],
                         ['lfs', 'lfs', 'fdivs', 'fctiwz', 'stfd', 'lwz', 'blr'])
        self.assertEqual(result['instructions'][1]['displacement'], -31268)
        self.assertEqual(set(result), {'address', 'width', 'sha256', 'spans', 'instructions'})
        self.assertFalse(any('word' in i or 'bytes' in i for i in result['instructions']))
        self.assertEqual(db.calls, [(21, start - t.TEXT_START, len(raw), t.TEXT_LENGTH)])

    def test_independent_width_check(self):
        raw = bytes(8)
        digest = hashlib.sha256(raw).hexdigest()
        with patch.object(t, 'RANGES', ((0x8003fa68, 4, digest),)):
            with self.assertRaisesRegex(t.c.FormatError, 'width'):
                t.range_evidence(FakeDB(raw), 21, 0x8003fa68, 4)

    def test_range_alignment_and_bounds(self):
        for address, width in ((0x8003fa69, 4), (0x8003fa68, 5),
                               (t.TEXT_START - 4, 4),
                               (t.TEXT_START + t.TEXT_LENGTH, 4)):
            with patch.object(t, 'RANGES', ((address, width, '0' * 64),)):
                with self.assertRaises(t.c.FormatError):
                    t.range_evidence(None, 21, address, width)

    def test_synthetic_origin_conversion_uses_single_subtract(self):
        words = [d_form(15, 4, 0, 0x4330), d_form(27, 5, 4, 0x8000),
                 d_form(50, 3, 1, 8), d_form(50, 4, 2, -31384),
                 arithmetic(59, 20, 1, 3, 4),
                 arithmetic(59, 20, 1, 5, 1),
                 arithmetic(59, 18, 1, 1, 2), arithmetic(63, 15, 0, 0, 1)]
        facts = [t.decode_selected(w, i * 4) for i, w in enumerate(words)]
        self.assertEqual([i['mnemonic'] for i in facts],
                         ['addis', 'xoris', 'lfd', 'lfd', 'fsubs', 'fsubs', 'fdivs', 'fctiwz'])
        self.assertEqual(facts[1]['immediate'], 0x8000)
        self.assertEqual(facts[4], dict(mnemonic='fsubs', fD=1, fA=3, fB=4))

    def test_synthetic_plane_keeps_separate_rounding_operations(self):
        words = [arithmetic(59, 25, 7, 4, fc=7), arithmetic(59, 25, 4, 3, fc=6),
                 arithmetic(59, 21, 7, 7, 4), arithmetic(59, 25, 3, 5, fc=3),
                 arithmetic(59, 21, 7, 7, 3), arithmetic(59, 18, 7, 7, 5)]
        facts = [t.decode_selected(w, i * 4) for i, w in enumerate(words)]
        self.assertEqual([i['mnemonic'] for i in facts],
                         ['fmuls', 'fmuls', 'fadds', 'fmuls', 'fadds', 'fdivs'])
        self.assertEqual(facts[-1], dict(mnemonic='fdivs', fD=7, fA=7, fB=5))

    def test_synthetic_comparison_branch_order(self):
        pc, target = 0x8003d8ac, 0x8003d8cc
        words = [compare(32, 30, 7), branch(pc + 4, target, 4, 1),
                 compare(32, 31, 7), branch(pc + 12, target, 4, 1),
                 compare(32, 0, 7),
                 (19 << 26) | (2 << 21) | (0 << 16) | (2 << 11) | (449 << 1),
                 branch(pc + 24, target, 4, 2)]
        facts = [t.decode_selected(w, pc + i * 4) for i, w in enumerate(words)]
        self.assertEqual([i['mnemonic'] for i in facts],
                         ['fcmpo', 'bc', 'fcmpo', 'bc', 'fcmpo', 'cror', 'bc'])
        self.assertEqual([facts[i]['target'] for i in (1, 3, 6)], ['8003d8cc'] * 3)
        self.assertEqual([facts[i]['BI'] for i in (1, 3, 6)], [1, 1, 2])
        self.assertEqual(facts[5], dict(mnemonic='cror', BT=2, BA=0, BB=2))

    def test_synthetic_cell_index_low_word_and_sentinel(self):
        words = [arithmetic(31, 235, 0, 3, 0), arithmetic(31, 266, 0, 3, 0),
                 (21 << 26) | (2 << 11) | (29 << 1),
                 arithmetic(31, 23, 3, 4, 0), d_form(32, 5, 3, 0),
                 d_form(15, 0, 5, 1), d_form(10, 0, 0, 0xffff)]
        facts = [t.decode_selected(w, i * 4) for i, w in enumerate(words)]
        self.assertEqual([i['mnemonic'] for i in facts],
                         ['mullw', 'add', 'rlwinm', 'lwzx', 'lwz', 'addis', 'cmpli'])
        self.assertEqual((facts[2]['SH'], facts[2]['MB'], facts[2]['ME']), (2, 0, 29))
        self.assertEqual(facts[-1]['immediate'], 0xffff)
        for value in (0, 0xfffffffe, 0xffffffff, 0x0000ffff, 0xffff0000):
            self.assertEqual(((value + 0x10000) & 0xffffffff) == 0xffff,
                             value == 0xffffffff)

    def test_fixed_constant_bits_values_and_traces(self):
        expected = {0x80436f68: 0.0, 0x80436f88: 4503601774854144.0,
                    0x80436ffc: 500.0, 0x80437034: -7500.0,
                    0x80437038: 7500.0, 0x80436f70: -0.5}
        self.assertEqual(set(t.TARGETS), set(expected))
        for address, value in expected.items():
            raw = bytes.fromhex(t.TARGETS[address])
            db = FakeDB(raw)
            result = t.constant_evidence(db, address)
            self.assertEqual(result['value'], value)
            self.assertEqual(result['bits'], t.TARGETS[address])
            self.assertEqual(result['spans'], [dict(synthetic=True)])
            self.assertEqual(db.calls, [(263, address - 0x80436a20, len(raw), 27360)])
            corrupted = bytes([raw[0] ^ 1]) + raw[1:]
            for bad in (raw[:-1], raw + b'\0', corrupted):
                with self.assertRaises(t.c.FormatError):
                    t.constant_evidence(FakeDB(bad), address)
        with self.assertRaises(t.c.FormatError):
            t.constant_evidence(None, 0x80436f6c)

    def test_authentication_precedes_query_reads(self):
        with patch.object(t, 'range_evidence') as read:
            with self.assertRaises(t.c.FormatError):
                t.inspect(bytes(32), '0' * 64)
            read.assert_not_called()

    def test_forged_allowlisted_digest_rejected(self):
        with patch.object(t, 'range_evidence') as read:
            for digest in t.c.SNAPSHOTS:
                with self.assertRaises(t.c.FormatError):
                    t.inspect(bytes(32), digest)
            read.assert_not_called()


if __name__ == '__main__':
    unittest.main()
