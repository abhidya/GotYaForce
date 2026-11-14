#!/usr/bin/env python3
"""Fixed-reader admission/operand tests, not archived execution or parity."""
import copy
import hashlib
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_primary_terrain_evidence as t


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, [dict(synthetic=True)]


def a_form(op, xo, d, a, b=0, fc=0):
    return (op << 26) | (d << 21) | (a << 16) | (b << 11) | (fc << 6) | (xo << 1)


class EvidenceTests(unittest.TestCase):
    def test_double_multiply_preserves_multiplier_order(self):
        word = a_form(63, 25, 2, 4, fc=2)
        self.assertEqual(t.decode_selected(word, 0), dict(mnemonic='fmul', fD=2, fA=4, fC=2))
        for bad in (word | 1, word | (1 << 11)):
            with self.assertRaises(t.c.FormatError): t.decode_selected(bad, 0)

    def test_double_fused_negative_subtract_is_not_single(self):
        word = a_form(63, 30, 0, 1, 3, 0)
        self.assertEqual(t.decode_selected(word, 0),
                         dict(mnemonic='fnmsub', fD=0, fA=1, fC=0, fB=3))
        with self.assertRaises(t.c.FormatError): t.decode_selected(word | 1, 0)

    def test_single_fused_sine_expression_keeps_operands(self):
        word = a_form(59, 30, 5, 2, 1, 2)
        self.assertEqual(t.decode_selected(word, 0),
                         dict(mnemonic='fnmsubs', fD=5, fA=2, fC=2, fB=1))

    def test_paired_subtract_validates_reserved_fields(self):
        word = a_form(4, 20, 6, 2, 4)
        self.assertEqual(t.decode_selected(word, 0), dict(mnemonic='ps_sub', fD=6, fA=2, fB=4))
        for bad in (word | 1, word | (1 << 6)):
            with self.assertRaises(t.c.FormatError): t.decode_selected(bad, 0)

    def test_invalid_inputs(self):
        for word in (-1, 1 << 32, True, 1.0, '0'):
            with self.assertRaises(t.c.FormatError): t.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 0.0):
            with self.assertRaises(t.c.FormatError): t.decode_selected(0, pc)

    def test_fixed_text_domain_and_root(self):
        self.assertEqual([(a, n) for a, n, _ in t.RANGES],
                         [(0x80047368, 1252), (0x8020ba78, 36), (0x8020bc88, 40)])
        for address, width, digest in t.RANGES:
            self.assertEqual(len(digest), 64)
            with self.assertRaises(t.c.FormatError): t.range_evidence(None, 21, address + 4, width - 4)
            with self.assertRaises(t.c.FormatError): t.range_evidence(None, 22, address, width)
            with self.assertRaises(t.c.FormatError): t.range_evidence(FakeDB(bytes(width)), 21, address, width)
        with self.assertRaises(t.c.FormatError): t.range_evidence(None, 21, 0x8020b2a8, 176)

    def test_synthetic_range_emits_only_derived_fields(self):
        raw = struct.pack('>2I', a_form(63, 30, 0, 1, 3, 0), 0x4e800020)
        address = 0x80047368
        db = FakeDB(raw)
        with patch.object(t, 'RANGES', ((address, len(raw), hashlib.sha256(raw).hexdigest()),)):
            result = t.range_evidence(db, 21, address, len(raw))
        self.assertEqual(set(result), {'address', 'width', 'sha256', 'spans', 'instructions'})
        self.assertEqual(result['spans'], [dict(synthetic=True)])
        self.assertEqual(result['instructions'][0],
                         dict(address='80047368', mnemonic='fnmsub', fD=0, fA=1, fC=0, fB=3))
        self.assertFalse(any('word' in f or 'bytes' in f for f in result['instructions']))
        self.assertEqual(db.calls, [(21, address - t.TEXT_START, 8, t.TEXT_LENGTH)])

    def test_range_width_and_alignment_guards_independent_of_digest(self):
        raw = bytes(8)
        with patch.object(t, 'RANGES', ((0x80047368, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(t.c.FormatError, 'width'):
                t.range_evidence(FakeDB(raw), 21, 0x80047368, 4)
        for address, width in ((t.TEXT_START - 4, 4), (t.TEXT_START + t.TEXT_LENGTH, 4),
                               (0x80047369, 4), (0x80047368, 5)):
            with patch.object(t, 'RANGES', ((address, width, '0' * 64),)):
                with self.assertRaises(t.c.FormatError): t.range_evidence(None, 21, address, width)

    def test_only_selected_bend_indices(self):
        self.assertEqual((t.TABLE_ADDRESS, t.TABLE_WIDTH), (0x804336a9, 3))
        for address, width in ((0x804336a8, 4), (0x804336a8, 3), (0x804336aa, 2), (0x804336a9, 4)):
            with self.assertRaises(t.c.FormatError): t.table_evidence(None, address, width)
        db = FakeDB(bytes((120, 121, 122)))
        result = t.table_evidence(db)
        self.assertEqual(result['element_type'], 'signed8')
        self.assertEqual(result['lookup_base'], '804336a8')
        self.assertEqual(result['entries'], [dict(index=1, selector=120, axis='x'),
                                           dict(index=2, selector=121, axis='y'),
                                           dict(index=3, selector=122, axis='z')])
        self.assertEqual(db.calls, [(262, 265, 3, 11040)])

    def test_bend_table_width_digest_and_typed_value_guards(self):
        for raw in (b'xy', b'xyz\0', b'abc'):
            with self.assertRaises(t.c.FormatError): t.table_evidence(FakeDB(raw))
        raw = b'\x80yz'
        with patch.object(t, 'TABLE_SHA', hashlib.sha256(raw).hexdigest()):
            with self.assertRaisesRegex(t.c.FormatError, 'axes'): t.table_evidence(FakeDB(raw))

    def test_constants_exact_type_width_and_values(self):
        expected = {0x804370a0: ('f32', 4, 0.0), 0x804370c0: ('f64', 8, 0.5),
                    0x804370c8: ('f64', 8, 3.0), 0x804370d0: ('f32', 4, 0.9990000128746033),
                    0x804370d4: ('f32', 4, 1.0), 0x804370d8: ('f32', 4, -1.0)}
        self.assertEqual(set(t.TARGETS), set(expected))
        for address, wanted in expected.items():
            raw = bytes.fromhex(t.TARGETS[address][2]); db = FakeDB(raw)
            result = t.constant_evidence(db, address)
            self.assertEqual((result['type'], result['width'], result['value']), wanted)
            self.assertEqual(db.calls, [(263, address - 0x80436a20, wanted[1], 27360)])
            for bad in (raw[:-1], raw + b'\0', bytes([raw[0] ^ 1]) + raw[1:]):
                with self.assertRaises(t.c.FormatError): t.constant_evidence(FakeDB(bad), address)
        for address in (0x804370a4, 0x804370c4, 0x804370dc):
            with self.assertRaises(t.c.FormatError): t.constant_evidence(None, address)

    def test_constant_type_width_guard(self):
        with patch.dict(t.TARGETS, {0x804370c0: ('f32', 8, '3fe0000000000000')}):
            with self.assertRaisesRegex(t.c.FormatError, 'type/width'): t.constant_evidence(None, 0x804370c0)

    def test_data4_exact_mapping_and_subblocks(self):
        blocks = {6: ['MAIN_.data4', None, None, 0, 0x20000000004335a0, 11040, 0]}
        subs = {6: [6, 2, 11040, 0, 262, 0]}
        t.data4_mapping(blocks, subs, 0x80000000)
        for index, value in ((4, 0x20000000004335a4), (5, 11039), (6, 1)):
            bad = copy.deepcopy(blocks); bad[6][index] = value
            with self.assertRaises(t.c.FormatError): t.data4_mapping(bad, subs, 0x80000000)
        for index, value in ((1, 1), (2, 11039), (3, 4), (4, 263), (5, 4)):
            bad = copy.deepcopy(subs); bad[6][index] = value
            with self.assertRaises(t.c.FormatError): t.data4_mapping(blocks, bad, 0x80000000)
        bad = copy.deepcopy(blocks); bad[8] = bad[6][:]
        with self.assertRaises(t.c.FormatError): t.data4_mapping(bad, subs, 0x80000000)
        with self.assertRaises(t.c.FormatError): t.data4_mapping({8: blocks[6]}, subs, 0x80000000)
        with self.assertRaises(t.c.FormatError): t.data4_mapping(blocks, {**subs, 9: subs[6]}, 0x80000000)

    def test_authentication_precedes_any_selected_reads(self):
        with patch.object(t, 'range_evidence') as text, patch.object(t, 'table_evidence') as table, \
                patch.object(t, 'constant_evidence') as constants, \
                patch.object(t.traversal, 'range_evidence') as reused:
            for digest in ('0' * 64, next(iter(t.c.SNAPSHOTS))):
                with self.assertRaises(t.c.FormatError): t.inspect(bytes(32), digest)
            text.assert_not_called(); table.assert_not_called()
            constants.assert_not_called(); reused.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    """Optional archived-data integration; no archived instructions execute."""
    @classmethod
    def setUpClass(cls):
        base = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(path.is_file() for path in paths):
            raise unittest.SkipTest('both local archived snapshots are not present')
        cls.results = []
        for path in paths:
            data = path.read_bytes()
            cls.results.append(t.inspect(data, hashlib.sha256(data).hexdigest()))
        cls.primary = {f['address']: f for f in cls.results[0]['ranges'][0]['instructions']}

    def fact(self, address, **fields):
        result = self.primary[f'{address:08x}']
        for key, value in fields.items(): self.assertEqual(result[key], value)

    def test_both_snapshots_same_selected_evidence(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(t.c.SNAPSHOTS))
        for key in ('ranges', 'bend_axes', 'constants', 'reused_evidence'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        self.assertEqual([len(r['instructions']) for r in self.results[0]['ranges']], [311, 9, 10])

    def test_actual_constant_load_types(self):
        for pc, address, name in ((0x8004743c, 0x804370a0, 'lfs'),
                                  (0x8004744c, 0x804370c0, 'lfd'),
                                  (0x80047450, 0x804370c8, 'lfd'),
                                  (0x80047570, 0x804370d0, 'lfs'),
                                  (0x80047590, 0x804370d4, 'lfs'),
                                  (0x800475d0, 0x804370d8, 'lfs')):
            self.fact(pc, mnemonic=name, rA=2, displacement=address - 0x8043ea20)

    def test_three_double_refinements_then_one_single_round(self):
        self.fact(0x80047448, mnemonic='frsqrte', fD=2, fB=1)
        for start in (0x80047454, 0x80047464, 0x80047474):
            self.fact(start, mnemonic='fmul', fD=0, fA=2, fC=2)
            self.fact(start + 4, mnemonic='fmul', fD=2, fA=4, fC=2)
            self.fact(start + 8, mnemonic='fnmsub', fD=0, fA=1, fC=0, fB=3)
        self.fact(0x80047460, mnemonic='fmul', fD=2, fA=2, fC=0)
        self.fact(0x80047470, mnemonic='fmul', fD=2, fA=2, fC=0)
        self.fact(0x80047480, mnemonic='fmul', fD=0, fA=2, fC=0)
        self.fact(0x80047484, mnemonic='fmul', fD=0, fA=1, fC=0)
        self.fact(0x80047488, mnemonic='frsp', fD=0, fB=0)
        self.fact(0x8004748c, mnemonic='stfs', fD=0, rA=1, displacement=28)
        self.fact(0x80047490, mnemonic='lfs', fD=31, rA=1, displacement=28)
        names = [f['mnemonic'] for a, f in self.primary.items() if '80047454' <= a <= '80047484']
        self.assertEqual(set(names), {'fmul', 'fnmsub'})

    def test_single_cosine_order_and_ordered_clamps(self):
        names = ['fmuls', 'lfs', 'fmuls', 'lfs', 'fmuls', 'fmuls', 'fadds', 'fadds',
                 'fmuls', 'fsubs', 'fmuls', 'fsubs', 'fmuls', 'fdivs', 'fneg', 'fcmpo', 'fdivs']
        self.assertEqual([self.primary[f'{pc:08x}']['mnemonic'] for pc in range(0x80047584, 0x800475c8, 4)], names)
        self.fact(0x800475b8, fA=4, fB=3)
        self.fact(0x800475c4, fA=1, fB=0)
        for pc, bi in ((0x800475c8, 1), (0x800475d8, 0), (0x800475ec, 1), (0x800475fc, 0)):
            self.fact(pc, mnemonic='bc', BO=4, BI=bi)

    def test_signed_bend_reload_and_opposite_sine_signs(self):
        self.fact(0x8004760c, mnemonic='extsb', Rc=1)
        self.fact(0x800476d8, mnemonic='lbz', displacement=15)
        self.fact(0x800476e0, mnemonic='fneg', fD=31, fB=6)
        self.fact(0x800476e4, mnemonic='extsb', rS=3, rA=3)
        self.fact(0x800476e8, mnemonic='subf', rD=3, rA=3, rB=0)
        self.fact(0x80047758, mnemonic='fneg', fD=1, fB=5)
        self.fact(0x800477b8, mnemonic='lbz', displacement=15)
        self.fact(0x800477bc, mnemonic='fmr', fD=31, fB=6)
        self.fact(0x800477c4, mnemonic='extsb', rS=0, rA=0)
        self.fact(0x800477c8, mnemonic='lbzx', rD=0, rA=3, rB=0)
        self.fact(0x800477cc, mnemonic='extsb', rS=0, rA=31)

    def test_sine_zero_bypasses_estimate(self):
        for pc in (0x8004761c, 0x80047680, 0x800476fc, 0x80047760):
            self.fact(pc, mnemonic='fnmsubs')
            self.fact(pc + 4, mnemonic='fcmpo', BF=0)
            self.fact(pc + 8, mnemonic='bc', BO=4, BI=1)
            self.fact(pc + 12, mnemonic='frsqrte')

    def test_snapshot_and_store_call_order(self):
        for pc, offset in ((0x800473d8, 12), (0x800473dc, 16), (0x800473e0, 20)):
            self.fact(pc, mnemonic='lwz', rA=6, displacement=offset)
        for pc, offset in ((0x80047530, 12), (0x80047538, 28), (0x80047540, 44)):
            self.fact(pc, mnemonic='stfs', rA=30, displacement=offset)
        for pc, target in ((0x80047544, '8020ba78'), (0x80047560, '80045918'),
                            (0x80047568, '8020bb14'), (0x800477d8, '8020b2a8'),
                            (0x800477e8, '8020af5c'), (0x800477fc, '8020b2a8'),
                            (0x80047824, '8020af5c')):
            self.fact(pc, mnemonic='bl', target=target)
        self.fact(0x800473d4, mnemonic='addi', rD=29, rA=30, immediate=48)
        self.fact(0x8004780c, mnemonic='or', rS=29, rA=5, rB=29)
        for pc, offset in ((0x80047818, 104), (0x8004781c, 120), (0x80047820, 136)):
            self.fact(pc, mnemonic='stfs', rA=1, displacement=offset)

    def test_square_distance_tree_and_subtract_store_order(self):
        subtract = self.results[0]['ranges'][1]['instructions']
        self.assertEqual([f['mnemonic'] for f in subtract],
                         ['psq_l', 'psq_l', 'ps_sub', 'psq_st', 'psq_l', 'psq_l', 'ps_sub', 'psq_st', 'blr'])
        self.assertEqual([(f['displacement'], f['W'], f['I']) for f in subtract if f['mnemonic'] == 'psq_st'],
                         [(0, 0, 0), (8, 1, 0)])
        square = self.results[0]['ranges'][2]['instructions']
        self.assertEqual([f['mnemonic'] for f in square],
                         ['psq_l', 'psq_l', 'ps_sub', 'psq_l', 'psq_l', 'ps_mul', 'ps_sub', 'ps_madd', 'ps_sum0', 'blr'])
        self.assertEqual([f['displacement'] for f in square if f['mnemonic'] == 'psq_l'], [4, 4, 0, 0])
        self.assertEqual(square[7], dict(address='8020bca4', mnemonic='ps_madd', fD=1, fA=0, fC=0, fB=2))
        self.assertEqual(square[8], dict(address='8020bca8', mnemonic='ps_sum0', fD=1, fA=1, fC=2, fB=2))

    def test_reused_rot_trig_sine_cosine_identity(self):
        facts = {f['address']: f for f in self.results[0]['reused_evidence']['rot_trig']['instructions']}
        self.assertEqual(facts['8020b2a8'], dict(address='8020b2a8', mnemonic='frsp', fD=5, fB=1))
        self.assertEqual(facts['8020b2ac'], dict(address='8020b2ac', mnemonic='frsp', fD=4, fB=2))
        self.assertEqual(facts['8020b2bc'], dict(address='8020b2bc', mnemonic='ps_neg', fD=2, fB=5))
        # z arm stores [s,c] in row1 and [c,-s] in row0, rather than the
        # decompiler's misleading scalar duplicate-cosine assignment.
        self.assertEqual((facts['8020b334']['fA'], facts['8020b334']['fB']), (5, 4))
        self.assertEqual((facts['8020b338']['fA'], facts['8020b338']['fB']), (4, 2))
        self.assertEqual((facts['8020b348']['fD'], facts['8020b348']['displacement']), (3, 16))
        self.assertEqual((facts['8020b34c']['fD'], facts['8020b34c']['displacement']), (2, 0))


if __name__ == '__main__':
    unittest.main()
