#!/usr/bin/env python3
"""Synthetic fixed-reader tests, not archived execution or hardware parity."""
import hashlib
import struct
import unittest
from unittest.mock import patch

import read_archived_terrain_orientation_evidence as t


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, [dict(synthetic=True)]


def d_form(op, d, a, displacement):
    return (op << 26) | (d << 21) | (a << 16) | (displacement & 65535)


def a_form(op, xo, d, a, b=0, fc=0):
    return (op << 26) | (d << 21) | (a << 16) | (b << 11) | (fc << 6) | (xo << 1)


class EvidenceTests(unittest.TestCase):
    def test_estimate_has_no_implicit_sqrt_or_single_suffix(self):
        word = a_form(63, 26, 5, 0, 4)
        self.assertEqual(t.decode_selected(word, 0), dict(mnemonic='frsqrte', fD=5, fB=4))
        for bad in (word | 1, word | (1 << 16), word | (1 << 6)):
            with self.assertRaises(t.c.FormatError): t.decode_selected(bad, 0)

    def test_fnmsubs_multiplier_and_subtrahend_order(self):
        word = a_form(59, 30, 6, 6, 1, 4)
        self.assertEqual(t.decode_selected(word, 0),
                         dict(mnemonic='fnmsubs', fD=6, fA=6, fC=4, fB=1))
        with self.assertRaises(t.c.FormatError): t.decode_selected(word | 1, 0)

    def test_magnitude_refinement_sequence(self):
        words = [a_form(63, 26, 0, 0, 1), d_form(48, 3, 2, -8076),
                 a_form(59, 25, 2, 0, fc=0), a_form(59, 25, 0, 0, fc=4),
                 a_form(59, 30, 2, 2, 3, 1), a_form(59, 25, 0, 2, fc=0),
                 a_form(59, 25, 1, 1, fc=0)]
        facts = [t.decode_selected(w, 0x8020bb38 + 4*i) for i, w in enumerate(words)]
        self.assertEqual([f['mnemonic'] for f in facts],
                         ['frsqrte', 'lfs', 'fmuls', 'fmuls', 'fnmsubs', 'fmuls', 'fmuls'])
        self.assertEqual(facts[4], dict(mnemonic='fnmsubs', fD=2, fA=2, fC=1, fB=3))
        self.assertEqual((facts[6]['fA'], facts[6]['fC']), (1, 0))

    def test_normalize_refinement_and_distinct_output_stores(self):
        words = [a_form(63, 26, 5, 0, 4), a_form(59, 25, 6, 5, fc=5),
                 a_form(59, 25, 0, 5, fc=0), a_form(59, 30, 6, 6, 1, 4),
                 a_form(59, 25, 5, 6, fc=0), a_form(4, 12, 2, 2, fc=5),
                 d_form(60, 2, 4, 0), a_form(4, 12, 3, 3, fc=5),
                 d_form(60, 3, 4, 0x8008)]
        facts = [t.decode_selected(w, 0x8020bad4 + 4*i) for i, w in enumerate(words)]
        self.assertEqual([f['mnemonic'] for f in facts],
                         ['frsqrte', 'fmuls', 'fmuls', 'fnmsubs', 'fmuls',
                          'ps_muls0', 'psq_st', 'ps_muls0', 'psq_st'])
        self.assertEqual([(facts[i]['W'], facts[i]['I'], facts[i]['displacement']) for i in (6, 8)],
                         [(0, 0, 0), (1, 0, 8)])

    def test_squared_norm_preserves_fused_pair_and_sum_operands(self):
        words = [a_form(4, 25, 5, 2, fc=2), a_form(4, 29, 4, 3, 5, 3),
                 a_form(4, 10, 4, 4, 5, 3)]
        facts = [t.decode_selected(w, 0) for w in words]
        self.assertEqual([f['mnemonic'] for f in facts], ['ps_mul', 'ps_madd', 'ps_sum0'])
        self.assertEqual(facts[-1], dict(mnemonic='ps_sum0', fD=4, fA=4, fC=3, fB=5))

    def test_link_register_forms(self):
        for xo, name, key in ((339, 'mflr', 'rD'), (467, 'mtlr', 'rS')):
            word = a_form(31, xo, 0, 8)
            self.assertEqual(t.decode_selected(word, 0), dict(mnemonic=name, **{key: 0}))
            with self.assertRaises(t.c.FormatError): t.decode_selected(word | 1, 0)

    def test_integer_absolute_value_and_lookup_forms(self):
        words = [a_form(31, 824, 29, 3, 31), a_form(31, 316, 3, 0, 29),
                 a_form(31, 40, 0, 3, 0), a_form(31, 104, 30, 30),
                 a_form(31, 87, 4, 30, 0)]
        expected = [dict(mnemonic='srawi', rS=29, rA=3, SH=31),
                    dict(mnemonic='xor', rS=3, rA=0, rB=29),
                    dict(mnemonic='subf', rD=0, rA=3, rB=0),
                    dict(mnemonic='neg', rD=30, rA=30),
                    dict(mnemonic='lbzx', rD=4, rA=30, rB=0)]
        self.assertEqual([t.decode_selected(w, 0) for w in words], expected)
        for word in words:
            with self.assertRaises(t.c.FormatError): t.decode_selected(word | 1, 0)
        with self.assertRaises(t.c.FormatError): t.decode_selected(words[3] | (1 << 11), 0)

    def test_invalid_inputs(self):
        for word in (-1, 1 << 32, True, 1.0, '0'):
            with self.assertRaises(t.c.FormatError): t.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 0.0):
            with self.assertRaises(t.c.FormatError): t.decode_selected(0, pc)

    def test_fixed_text_domain(self):
        self.assertEqual([(a, n) for a, n, _ in t.RANGES], [
            (0x8004784c, 184), (0x8003de80, 552), (0x80045918, 688),
            (0x80045ef4, 212), (0x80046158, 200), (0x8020b7a8, 84),
            (0x8020bab8, 68), (0x8020bb14, 68), (0x8020bb78, 60)])
        for address, width, digest in t.RANGES:
            self.assertEqual(len(digest), 64)
            with self.assertRaises(t.c.FormatError): t.range_evidence(None, 21, address+4, width-4)
            with self.assertRaises(t.c.FormatError): t.range_evidence(None, 22, address, width)
            with self.assertRaises(t.c.FormatError): t.range_evidence(FakeDB(bytes(width)), 21, address, width)
        with self.assertRaises(t.c.FormatError): t.range_evidence(None, 21, 0x80047368, 1252)

    def test_synthetic_range_outputs_only_derived_fields(self):
        raw = struct.pack('>2I', a_form(63, 26, 5, 0, 4), 0x4e800020)
        address = 0x8020bab8
        db = FakeDB(raw)
        with patch.object(t, 'RANGES', ((address, len(raw), hashlib.sha256(raw).hexdigest()),)):
            result = t.range_evidence(db, 21, address, len(raw))
        self.assertEqual(set(result), {'address', 'width', 'sha256', 'spans', 'instructions'})
        self.assertEqual(result['spans'], [dict(synthetic=True)])
        self.assertEqual(result['instructions'][0], dict(address='8020bab8', mnemonic='frsqrte', fD=5, fB=4))
        self.assertFalse(any('word' in fact or 'bytes' in fact for fact in result['instructions']))
        self.assertEqual(db.calls, [(21, address-t.TEXT_START, 8, t.TEXT_LENGTH)])

    def test_independent_range_width_check(self):
        raw = bytes(8)
        with patch.object(t, 'RANGES', ((0x8020bab8, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(t.c.FormatError, 'width'):
                t.range_evidence(FakeDB(raw), 21, 0x8020bab8, 4)

    def test_range_bounds_and_alignment(self):
        for address, width in ((t.TEXT_START-4, 4), (t.TEXT_START+t.TEXT_LENGTH, 4),
                               (0x8020bab9, 4), (0x8020bab8, 5)):
            with patch.object(t, 'RANGES', ((address, width, '0'*64),)):
                with self.assertRaises(t.c.FormatError): t.range_evidence(None, 21, address, width)

    def test_exact_table_domains(self):
        self.assertEqual([(a, n) for a, n, _ in t.TABLES], [(0x802d0d38, 9), (0x802d0d4c, 4)])
        for address, width in ((0x802d0d34, 16), (0x802d0d44, 28), (0x802d0d38, 8), (0x802d0d50, 4)):
            with self.assertRaises(t.c.FormatError): t.table_evidence(None, address, width)

    def test_positive_axis_window_and_selected_dispatch(self):
        db = FakeDB(bytes(t.AXIS_SELECTORS))
        result = t.table_evidence(db, 0x802d0d38, 9)
        self.assertEqual(result['lookup_base'], '802d0d34')
        self.assertEqual(result['entries'][3], dict(normal_axis=2, reference_axis=1, index=7, selector=2))
        self.assertEqual(result['entries'][4]['selector'], 0)
        self.assertEqual(db.calls, [(199, 0x802d0d38-0x802bae60, 9, 0xf42c0)])
        db = FakeDB(struct.pack('>I', 0x80046158))
        result = t.table_evidence(db, 0x802d0d4c, 4)
        self.assertEqual((result['dispatch_base'], result['selector'], result['target']),
                         ('802d0d44', 2, '80046158'))

    def test_table_width_and_digest_guards(self):
        for address, width, _ in t.TABLES:
            for raw in (bytes(width), bytes(width-1), bytes(width+1)):
                with self.assertRaises(t.c.FormatError): t.table_evidence(FakeDB(raw), address, width)
        raw = bytes(8)
        with patch.object(t, 'TABLES', ((0x802d0d4c, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(t.c.FormatError, 'width'): t.table_evidence(FakeDB(raw), 0x802d0d4c, 4)

    def test_selector_and_target_guards_independent_of_digest(self):
        for address, raw, error in ((0x802d0d38, bytes(9), 'selectors'),
                                    (0x802d0d4c, struct.pack('>I', 0x80045fc8), 'constructor')):
            with patch.object(t, 'TABLES', ((address, len(raw), hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(t.c.FormatError, error): t.table_evidence(FakeDB(raw), address, len(raw))

    def test_fixed_constants(self):
        expected = {0x80436f78: 1.0, 0x80437080: 9.999999439624929e-11,
                    0x8043ca90: 0.5, 0x8043ca94: 3.0}
        self.assertEqual(set(t.TARGETS), set(expected))
        for address, value in expected.items():
            raw = bytes.fromhex(t.TARGETS[address]); db = FakeDB(raw)
            self.assertEqual(t.constant_evidence(db, address)['value'], value)
            self.assertEqual(db.calls, [(263, address-0x80436a20, 4, 27360)])
            for bad in (bytes(4), raw[:-1], raw+b'\0'):
                with self.assertRaises(t.c.FormatError): t.constant_evidence(FakeDB(bad), address)
        for address in (0x80437088, 0x804370c0):
            with self.assertRaises(t.c.FormatError): t.constant_evidence(None, address)

    def test_default_normal_stores_precede_bounds_call(self):
        words = [d_form(48, 1, 2, -31416), d_form(48, 0, 2, -31400),
                 d_form(52, 1, 31, 0), d_form(52, 0, 31, 4), d_form(52, 1, 31, 8)]
        facts = [t.decode_selected(w, 0) for w in words]
        self.assertEqual([f['mnemonic'] for f in facts], ['lfs', 'lfs', 'stfs', 'stfs', 'stfs'])
        self.assertEqual([(f['fD'], f['displacement']) for f in facts[2:]], [(1, 0), (0, 4), (1, 8)])

    def test_selected_normal_write_order_has_no_reload(self):
        words = [d_form(36, 5, 31, 0), a_form(63, 72, 9, 0, 3),
                 d_form(36, 4, 31, 4), d_form(36, 0, 31, 8)]
        facts = [t.decode_selected(w, 0) for w in words]
        self.assertEqual([f['mnemonic'] for f in facts], ['stw', 'fmr', 'stw', 'stw'])
        self.assertEqual([facts[i]['rD'] for i in (0, 2, 3)], [5, 4, 0])

    def test_authentication_precedes_selected_reads(self):
        with patch.object(t, 'table_evidence') as table, patch.object(t, 'range_evidence') as text:
            with self.assertRaises(t.c.FormatError): t.inspect(bytes(32), '0'*64)
            table.assert_not_called(); text.assert_not_called()
            with self.assertRaises(t.c.FormatError):
                t.inspect(bytes(32), next(iter(t.c.SNAPSHOTS)))
            table.assert_not_called(); text.assert_not_called()


if __name__ == '__main__':
    unittest.main()
