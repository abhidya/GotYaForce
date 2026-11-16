#!/usr/bin/env python3
"""Synthetic refusal/field checks and optional fixed-snapshot source assertions."""
import contextlib
import hashlib
import io
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_actor_normal_evidence as a


def d_form(op, d, ra, immediate):
    return (op << 26) | (d << 21) | (ra << 16) | (immediate & 65535)


def x_form(xo, d=3, ra=4, rb=5, rc=0):
    return (31 << 26) | (d << 21) | (ra << 16) | (rb << 11) | (xo << 1) | rc


def spr_form(xo, d=0, spr=8, rc=0):
    return x_form(xo, d, spr & 31, spr >> 5, rc)


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_input_types_bounds(self):
        for word in (-1, 1 << 32, True, 1.0, '0'):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'):
                a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaisesRegex(a.c.FormatError, 'PC bounds'):
                a.decode_selected(0, pc)

    def test_memory_signedness_width_and_direction(self):
        for op, name, reg in ((32, 'lwz', 'rD'), (34, 'lbz', 'rD'), (36, 'stw', 'rS'),
                              (37, 'stwu', 'rS'), (38, 'stb', 'rS'), (42, 'lha', 'rD'),
                              (44, 'sth', 'rS'), (48, 'lfs', 'fD'), (50, 'lfd', 'fD'),
                              (54, 'stfd', 'fS')):
            for offset in (-32768, -1, 0, 32767):
                self.assertEqual(a.decode_selected(d_form(op, 7, 3, offset), 0),
                                 dict(mnemonic=name, **{reg: 7}, rA=3, displacement=offset))
        with self.assertRaises(a.c.FormatError): a.decode_selected(d_form(37, 1, 0, -16), 0)
        self.assertIsNone(a.decode_selected(d_form(40, 3, 4, 5), 0))

    def test_immediates_and_comparisons(self):
        for op, name in ((7, 'mulli'), (14, 'addi'), (15, 'addis')):
            self.assertEqual(a.decode_selected(d_form(op, 3, 4, 0xffff), 0),
                             dict(mnemonic=name, rD=3, rA=4, immediate=-1))
        for op, name, value in ((10, 'cmpli', 65535), (11, 'cmpi', -1)):
            self.assertEqual(a.decode_selected(d_form(op, 0, 4, 0xffff), 0),
                             dict(mnemonic=name, BF=0, L=0, rA=4, immediate=value))
            for d in (1, 2, 4):
                with self.assertRaises(a.c.FormatError): a.decode_selected(d_form(op, d, 4, 0), 0)
        self.assertEqual(a.decode_selected(x_form(0, 0), 0), dict(mnemonic='cmp', BF=0, L=0, rA=4, rB=5))
        for word in (x_form(0, 1), x_form(0, 0, rc=1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_integer_forms_and_reserved_fields(self):
        for xo, name in ((23, 'lwzx'), (87, 'lbzx')):
            self.assertEqual(a.decode_selected(x_form(xo), 0), dict(mnemonic=name, rD=3, rA=4, rB=5))
            with self.assertRaises(a.c.FormatError): a.decode_selected(x_form(xo, rc=1), 0)
        for xo, name in ((922, 'extsh'), (954, 'extsb')):
            self.assertEqual(a.decode_selected(x_form(xo, rb=0, rc=1), 0), dict(mnemonic=name, rS=3, rA=4, Rc=1))
            with self.assertRaises(a.c.FormatError): a.decode_selected(x_form(xo), 0)
        for xo, name in ((28, 'and'), (444, 'or')):
            self.assertEqual(a.decode_selected(x_form(xo, rc=1), 0), dict(mnemonic=name, rS=3, rA=4, rB=5, Rc=1))
        self.assertEqual(a.decode_selected(x_form(266), 0), dict(mnemonic='add', rD=3, rA=4, rB=5, Rc=0))
        self.assertIsNone(a.decode_selected(x_form(266 + 512), 0))  # no overflow-enable fallback
        self.assertEqual(a.decode_selected(d_form(27, 4, 0, 0x8000), 0),
                         dict(mnemonic='xoris', rS=4, rA=0, immediate=32768))
        self.assertEqual(a.decode_selected((21 << 26) | (24 << 6) | (27 << 1) | 1, 0),
                         dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=24, ME=27, Rc=1))

    def test_branch_fields_and_rejected_variants(self):
        for word, name, bo, bi, lk in ((0x4e800020, 'blr', 20, 0, 0),
                                       (0x4c820020, 'bclr', 4, 2, 0),
                                       (0x4e800421, 'bctrl', 20, 0, 1)):
            self.assertEqual(a.decode_selected(word, 0), dict(mnemonic=name, BO=bo, BI=bi, BH=0, LK=lk))
            for bad in (word ^ 1, word | (1 << 11), word | (1 << 13)):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        self.assertEqual(a.decode_selected((18 << 26) | 0x3fffffc, 0x80001000),
                         dict(mnemonic='b', target='80000ffc', AA=0))
        self.assertEqual(a.decode_selected((18 << 26) | 0x101, 0x80001000),
                         dict(mnemonic='bl', target='80001100', AA=0))
        with self.assertRaises(a.c.FormatError): a.decode_selected((18 << 26) | 2, 0)
        for bo, bi in ((4, 0), (4, 1), (4, 2), (12, 1), (12, 2), (16, 0)):
            word = (16 << 26) | (bo << 21) | (bi << 16) | 0xfffc
            self.assertEqual(a.decode_selected(word, 0x80001000),
                             dict(mnemonic='bc', BO=bo, BI=bi, LK=0, target='80000ffc', AA=0))
            for bad in (word | 1, word | 2):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)

    def test_spr_forms(self):
        self.assertEqual(a.decode_selected(spr_form(339), 0), dict(mnemonic='mflr', rD=0))
        self.assertEqual(a.decode_selected(spr_form(467), 0), dict(mnemonic='mtlr', rS=0))
        self.assertEqual(a.decode_selected(spr_form(467, 12, 9), 0), dict(mnemonic='mtctr', rS=12))
        for word in (spr_form(339, 0, 9), spr_form(467, 1, 8), spr_form(467, 0, 256), spr_form(467, rc=1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_floats_are_single_fused_or_truncating_as_encoded(self):
        sub = (59 << 26) | (2 << 21) | (1 << 16) | (3 << 11) | (20 << 1)
        mul = (59 << 26) | (2 << 21) | (1 << 16) | (3 << 6) | (25 << 1)
        fused = (59 << 26) | (2 << 21) | (3 << 16) | (2 << 6) | (29 << 1)
        conv = (63 << 26) | (2 << 21) | (3 << 11) | (15 << 1)
        self.assertEqual(a.decode_selected(sub, 0), dict(mnemonic='fsubs', fD=2, fA=1, fB=3))
        self.assertEqual(a.decode_selected(mul, 0), dict(mnemonic='fmuls', fD=2, fA=1, fC=3))
        self.assertEqual(a.decode_selected(fused, 0), dict(mnemonic='fmadds', fD=2, fA=3, fC=2, fB=0))
        self.assertEqual(a.decode_selected(conv, 0), dict(mnemonic='fctiwz', fD=2, fB=3))
        for bad in (sub | 1, sub | (1 << 6), mul | (1 << 11), fused | 1, conv | (1 << 16), conv | 1):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        self.assertIsNone(a.decode_selected((sub & ~(63 << 26)) | (63 << 26), 0))

    def test_mapping_exact_types_before_payload(self):
        for mapping in (list(a.TEXT_MAPPING), a.TEXT_MAPPING[:-1] + (22,),
                        a.TEXT_MAPPING[:2] + (True,) + a.TEXT_MAPPING[3:]):
            with self.assertRaisesRegex(a.c.FormatError, 'mapping'):
                a.range_evidence(None, mapping, 0x80059138, 4)
        with self.assertRaisesRegex(a.c.FormatError, 'mapping'):
            a.cell_evidence(None, a.TEXT_MAPPING, 0x802d3324)

    def test_fixed_selection_only_before_payload(self):
        for address, width in ((0x8005913c, 4), (0x80059138, 8), (0x8018cd38, 8), (0, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, address, width)
        for address, width in ((True, 4), (0x80059138, 4.0)):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.range_evidence(None, a.TEXT_MAPPING, address, width)
        for address in (0x802d3320, 0x80365550, 0):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.cell_evidence(None, a.DATA3_MAPPING, address)
        with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
            a.cell_evidence(None, a.DATA3_MAPPING, True)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, 0x80059138, 4)
        with patch.object(a, 'CELLS', a.CELLS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.cell_evidence(None, a.DATA3_MAPPING, 0x802d3324)

    def test_hash_width_before_decoder(self):
        for raw, error in ((bytes(4), 'digest'), (bytes(8), 'byte width')):
            with patch.object(a, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, error):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x80059138, 4)
                decoder.assert_not_called()
        for raw, error in ((bytes(4), 'digest'), (bytes(3), 'byte width')):
            with self.assertRaisesRegex(a.c.FormatError, error):
                a.cell_evidence(FakeDB(raw), a.DATA3_MAPPING, 0x802d3324)

    def test_cells_exact_target_and_no_follow(self):
        for label, address, target, _ in a.CELLS:
            db = FakeDB(struct.pack('>I', target))
            result = a.cell_evidence(db, a.DATA3_MAPPING, address)
            self.assertEqual(result['target'], f'{target:08x}')
            self.assertEqual(db.calls, [(199, address - 0x802bae60, 4, 1000128)])
        raw = struct.pack('>I', 0x80059138)
        with patch.object(a, 'CELLS', (('synthetic', 0x802d3324, 0x8005913c, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'target mismatch'):
                a.cell_evidence(FakeDB(raw), a.DATA3_MAPPING, 0x802d3324)

    def test_complete_decode_no_omission(self):
        raw = struct.pack('>I', 0)
        with patch.object(a, 'RANGES', ((0x80059138, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x80059138, 4)
        db = FakeDB(struct.pack('>I', 0x4e800020))
        result = a.range_evidence(db, a.TEXT_MAPPING, 0x80059138, 4)
        self.assertEqual(result['instructions'], [dict(address='80059138', mnemonic='blr', BO=20, BI=0, BH=0, LK=0)])
        self.assertEqual(db.calls, [(21, 0x80059138 - 0x800055e0, 4, 2796416)])

    def test_authentication_and_mapping_precede_selected_reads(self):
        with patch.object(a, 'cell_evidence') as cells, patch.object(a, 'range_evidence') as ranges:
            with self.assertRaisesRegex(a.c.FormatError, 'SHA256'):
                a.inspect(bytes(32), '0' * 64)
            cells.assert_not_called(); ranges.assert_not_called()
        with patch.object(a.c, 'inspect', return_value={'image_offset': '80000000'}), \
             patch.object(a.c, 'GBF') as db, \
             patch.object(a.command, 'mappings', side_effect=a.c.FormatError('mapping control')), \
             patch.object(a, 'cell_evidence') as cells, patch.object(a, 'range_evidence') as ranges:
            db.return_value.tables.return_value = {'Memory Blocks': {}, 'Sub Memory Blocks': {}}
            with self.assertRaisesRegex(a.c.FormatError, 'mapping control'): a.inspect(bytes(32), '0' * 64)
            cells.assert_not_called(); ranges.assert_not_called()

    def test_cli_has_no_selection_or_raw_flags(self):
        for flag in ('--address', '--width', '--target', '--raw', '--execute'):
            with patch.object(a.sys, 'argv', ['reader', 'snapshot', flag, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as error: a.main()
                self.assertEqual(error.exception.code, 2)


SNAPSHOT_DIR = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing local snapshots are optional and never fetched')
class ArchivedSourceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports = []
        for name in ('db.3.gbf', 'db.4.gbf'):
            data = (SNAPSHOT_DIR / name).read_bytes()
            cls.reports.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
        cls.facts = {item['address']: item for span in cls.reports[0]['ranges'] for item in span['instructions']}

    def fact(self, pc):
        return {key: value for key, value in self.facts[f'{pc:08x}'].items() if key != 'address'}

    def test_snapshots_all_operands_values_hashes_traces_agree(self):
        for key in ('cells', 'ranges', 'mappings'):
            self.assertEqual(self.reports[0][key], self.reports[1][key])
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual(len(self.facts), 281)
        for span in self.reports[0]['ranges']:
            self.assertEqual([x['address'] for x in span['instructions']],
                             [f'{pc:08x}' for pc in range(int(span['address'], 16), int(span['end_exclusive'], 16), 4)])

    def test_independent_leaves_are_single_return(self):
        for pc in (0x80059138, 0x8018cfe4, 0x8006f950, 0x8006f954, 0x8006f958):
            self.assertEqual(self.fact(pc), dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
        self.assertNotIn('8005913c', self.facts)
        self.assertEqual([(cell['address'], cell['target']) for cell in self.reports[0]['cells']],
                         [('802d3324', '80059138'), ('802d3300', '8005913c'),
                          ('8036554c', '8018cfe4'), ('802d3b28', '8006f950')])

    def test_constructors_keep_each_copy_and_correct_4c8_source(self):
        for entry, hi, lo, copy_start in ((0x8018ccfc, -32714, 0x5538, 0x8018cd10),
                                          (0x8006f60c, -32723, 0x3b14, 0x8006f620)):
            self.assertEqual(self.fact(entry), dict(mnemonic='addi', rD=0, rA=0, immediate=0))
            self.assertEqual(self.fact(entry + 4), dict(mnemonic='addis', rD=4, rA=0, immediate=hi))
            self.assertEqual(self.fact(entry + 8), dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=16))
            self.assertEqual(self.fact(entry + 12), dict(mnemonic='addi', rD=4, rA=4, immediate=lo))
            self.assertEqual(self.fact(entry + 16), dict(mnemonic='bc', BO=4, BI=0, LK=0,
                                                         target=f'{copy_start + 128:08x}', AA=0))
            for index in range(16):
                self.assertEqual(self.fact(copy_start + index * 8),
                                 dict(mnemonic='lwz', rD=0, rA=4, displacement=index * 4))
                self.assertEqual(self.fact(copy_start + index * 8 + 4),
                                 dict(mnemonic='stw', rS=0, rA=3, displacement=0x4b4 + index * 4))
        self.assertEqual(self.fact(0x8018cdfc), dict(mnemonic='bclr', BO=4, BI=2, BH=0, LK=0))
        for pc in (0x8018ce18, 0x8006f704):
            self.assertEqual(self.fact(pc), dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
        self.assertEqual(self.fact(0x8006f6d4), dict(mnemonic='addi', rD=0, rA=9, immediate=-20616))
        self.assertEqual(self.fact(0x8006f6e0), dict(mnemonic='stw', rS=0, rA=3, displacement=0x4b0))

    def test_postcallback_flags_and_cue_gates(self):
        expected = {
            0x80059f64: dict(mnemonic='addis', rD=4, rA=0, immediate=-32512),
            0x80059f6c: dict(mnemonic='addi', rD=0, rA=4, immediate=3),
            0x80059f78: dict(mnemonic='lwz', rD=5, rA=3, displacement=0x5e0),
            0x80059f7c: dict(mnemonic='and', rS=5, rA=0, rB=0, Rc=1),
            0x80059f80: dict(mnemonic='bc', BO=4, BI=2, LK=0, target='8005a114', AA=0),
            0x80059f84: dict(mnemonic='lbz', rD=4, rA=31, displacement=0x5e4),
            0x80059f88: dict(mnemonic='lbz', rD=0, rA=31, displacement=0x5e5),
            0x80059f8c: dict(mnemonic='extsb', rS=4, rA=4, Rc=0),
            0x80059f90: dict(mnemonic='extsb', rS=0, rA=0, Rc=0),
            0x80059f94: dict(mnemonic='cmp', BF=0, L=0, rA=4, rB=0),
            0x80059f98: dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80059fa0', AA=0),
            0x80059f9c: dict(mnemonic='bl', target='8006a6fc', AA=0),
            0x80059fa0: dict(mnemonic='lbz', rD=0, rA=31, displacement=0x661),
            0x80059fa4: dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=10),
            0x80059fa8: dict(mnemonic='bc', BO=12, BI=2, LK=0, target='8005a130', AA=0),
            0x8005a114: dict(mnemonic='lbz', rD=0, rA=31, displacement=0x1d9),
            0x8005a118: dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=24, ME=27, Rc=1),
            0x8005a11c: dict(mnemonic='bc', BO=12, BI=2, LK=0, target='8005a130', AA=0),
            0x8005a120: dict(mnemonic='lbz', rD=3, rA=31, displacement=0x57a),
            0x8005a124: dict(mnemonic='lbz', rD=0, rA=31, displacement=0x57b),
            0x8005a128: dict(mnemonic='or', rS=3, rA=0, rB=0, Rc=0),
            0x8005a12c: dict(mnemonic='stb', rS=0, rA=31, displacement=0x57a),
        }
        for pc, fact in expected.items(): self.assertEqual(self.fact(pc), fact, f'{pc:08x}')

    def test_rotations_are_not_a_false_noop(self):
        self.assertEqual(self.fact(0x80059fac), dict(mnemonic='lfs', fD=1, rA=2, displacement=-30296))
        self.assertEqual(self.fact(0x80059fb4), dict(mnemonic='lfs', fD=0, rA=31, displacement=0x1dc8))
        self.assertEqual(self.fact(0x80059fd0), dict(mnemonic='fmadds', fD=2, fA=3, fC=2, fB=0))
        self.assertEqual(self.fact(0x80059fd8), dict(mnemonic='lwz', rD=4, rA=31, displacement=0x4b0))
        self.assertEqual(self.fact(0x80059fec), dict(mnemonic='bc', BO=12, BI=2, LK=0, target='8005a084', AA=0))
        self.assertEqual(self.fact(0x8005a080), dict(mnemonic='bc', BO=16, BI=0, LK=0, target='80059fd8', AA=0))
        for pc, displacement in ((0x8005a0bc, 0x18da), (0x8005a0e4, 0x18dc), (0x8005a10c, 0x18de)):
            self.assertEqual(self.fact(pc), dict(mnemonic='sth', rS=0, rA=31, displacement=displacement))
        branches = [(pc, fact['target']) for pc, fact in self.facts.items()
                    if 0x80059f5c <= int(pc, 16) < 0x8005a144 and fact['mnemonic'] in ('b', 'bc')]
        self.assertTrue(all(0x80059f5c <= int(target, 16) < 0x8005a144 for _, target in branches))
        self.assertEqual([pc for pc, fact in self.facts.items()
                          if 0x80059f5c <= int(pc, 16) < 0x8005a144 and fact['mnemonic'] == 'blr'], ['8005a140'])

    def test_complete_countdown_schedule(self):
        expected = [
            dict(mnemonic='stwu', rS=1, rA=1, displacement=-16),
            dict(mnemonic='mflr', rD=0),
            dict(mnemonic='stw', rS=0, rA=1, displacement=20),
            dict(mnemonic='lha', rD=4, rA=3, displacement=0x6bc),
            dict(mnemonic='cmpi', BF=0, L=0, rA=4, immediate=0),
            dict(mnemonic='bc', BO=4, BI=1, LK=0, target='8005a180', AA=0),
            dict(mnemonic='addi', rD=4, rA=4, immediate=-1),
            dict(mnemonic='extsh', rS=4, rA=0, Rc=1),
            dict(mnemonic='sth', rS=4, rA=3, displacement=0x6bc),
            dict(mnemonic='bc', BO=12, BI=1, LK=0, target='8005a180', AA=0),
            dict(mnemonic='lwz', rD=12, rA=3, displacement=0x4dc),
            dict(mnemonic='cmpli', BF=0, L=0, rA=12, immediate=0),
            dict(mnemonic='bc', BO=12, BI=2, LK=0, target='8005a180', AA=0),
            dict(mnemonic='mtctr', rS=12),
            dict(mnemonic='bctrl', BO=20, BI=0, BH=0, LK=1),
            dict(mnemonic='lwz', rD=0, rA=1, displacement=20),
            dict(mnemonic='mtlr', rS=0),
            dict(mnemonic='addi', rD=1, rA=1, immediate=16),
            dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0),
        ]
        self.assertEqual([self.fact(pc) for pc in range(0x8005a144, 0x8005a190, 4)], expected)


if __name__ == '__main__':
    unittest.main()
