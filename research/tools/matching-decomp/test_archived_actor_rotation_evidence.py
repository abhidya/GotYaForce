#!/usr/bin/env python3
"""Synthetic fail-closed checks and optional authenticated rotation schedules."""
import contextlib
import hashlib
import io
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_actor_rotation_evidence as a


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_only_two_existing_ranges(self):
        self.assertEqual(a.RANGES, ((0x80059f5c, 488), (0x8006f60c, 252)))
        for address, width in ((0x80059fac, 360), (0x80059f5c, 484),
                               (0x80059138, 4), (0x8005a144, 76)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, address, width)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, *a.RANGES[0])

    def test_selection_types_before_read(self):
        for bad in (True, 1.0, '4', None):
            for reader, mapping, address, width in (
                    (a.range_evidence, a.TEXT_MAPPING, 0x80059f5c, 488),
                    (a.constant_evidence, a.DATA5_MAPPING, 0x804373c0, 4),
                    (a.descriptor_evidence, a.DATA3_MAPPING, 0x8033b028, 8)):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    reader(None, mapping, bad, width)
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    reader(None, mapping, address, bad)

    def test_fixed_data_only(self):
        for address, width in ((0x804373cc, 4), (0x804373c0, 8), (0x804373d0, 4), (0, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, address, width)
        for address, width in ((0x8033af78, 8), (0x8033b028, 1), (0x8033b029, 8),
                               (0x8033b028, 9), (0x8033b030, 8)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.descriptor_evidence(None, a.DATA3_MAPPING, address, width)
        with patch.object(a, 'CONSTANTS', a.CONSTANTS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, 0x804373c0, 4)

    def test_exact_mapping_and_types_before_read(self):
        for reader, mapping, address, width in (
                (a.range_evidence, a.TEXT_MAPPING, 0x80059f5c, 488),
                (a.constant_evidence, a.DATA5_MAPPING, 0x804373c0, 4),
                (a.descriptor_evidence, a.DATA3_MAPPING, 0x8033b028, 8)):
            for altered in (list(mapping), mapping[:-1] + (mapping[-1] + 1,),
                            mapping[:2] + (float(mapping[2]),) + mapping[3:],
                            (mapping[0] - 4,) + mapping[1:]):
                with self.assertRaisesRegex(a.c.FormatError, 'mapping'):
                    reader(None, altered, address, width)

    def test_constants_exact_bits_width_and_traces(self):
        for address, width, bits in a.CONSTANTS:
            raw = bytes.fromhex(bits)
            db = FakeDB(raw)
            result = a.constant_evidence(db, a.DATA5_MAPPING, address, width)
            self.assertEqual(result['bits'], bits)
            self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
            self.assertEqual(result['value'], struct.unpack('>f' if width == 4 else '>d', raw)[0])
            self.assertEqual(db.calls, [(263, address - 0x80436a20, width, 27360)])
            for bad, message in ((raw[:-1], 'byte width'), (bytes(width), 'bits mismatch')):
                with self.assertRaisesRegex(a.c.FormatError, message):
                    a.constant_evidence(FakeDB(bad), a.DATA5_MAPPING, address, width)
        with self.assertRaisesRegex(a.c.FormatError, 'bits mismatch'):
            a.constant_evidence(FakeDB(struct.pack('>f', 0.1)), a.DATA5_MAPPING, 0x804373c4, 4)

    def test_descriptor_signedness_hash_and_no_pointer_follow(self):
        raw = struct.pack('>8b', 12, 2, 7, 11, -1, -1, -1, -1)
        db = FakeDB(raw)
        result = a.descriptor_evidence(db, a.DATA3_MAPPING, 0x8033b028, 8)
        self.assertEqual(db.calls, [(199, 0x8033b028 - 0x802bae60, 8, 1000128)])
        self.assertEqual(result['values'], [12, 2, 7, 11, -1, -1, -1, -1])
        self.assertEqual(result['traversed_indices'], [12, 2, 7, 11])
        self.assertEqual(result['first_sentinel_position'], 4)
        self.assertFalse(result['extent_proven'])
        self.assertNotIn('bits', result)
        for bad, error in ((raw[:-1], 'byte width'), (bytes(8), 'digest mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, error):
                a.descriptor_evidence(FakeDB(bad), a.DATA3_MAPPING, 0x8033b028, 8)
        with patch.object(a, 'DESCRIPTOR_VALUES', (12, 2, 7, 11, 255, 255, 255, 255)):
            with self.assertRaisesRegex(a.c.FormatError, 'signed values mismatch'):
                a.descriptor_evidence(FakeDB(raw), a.DATA3_MAPPING, 0x8033b028, 8)

    def test_reused_range_authentication_strict_decode(self):
        for raw, error in ((bytes(488), 'digest mismatch'), (bytes(484), 'byte width')):
            with patch.object(a.normal, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, error):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x80059f5c, 488)
                decoder.assert_not_called()
        raw = bytes(488)
        selected = ((0x80059f5c, 488, hashlib.sha256(raw).hexdigest()),)
        with patch.object(a.normal, 'RANGES', selected):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x80059f5c, 488)

    def test_full_authentication_precedes_selections(self):
        with patch.object(a, 'range_evidence') as code, \
             patch.object(a, 'constant_evidence') as constants, \
             patch.object(a, 'descriptor_evidence') as descriptor:
            for digest in ('0' * 64, next(iter(a.c.SNAPSHOTS))):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256'):
                    a.inspect(bytes(32), digest)
            code.assert_not_called(); constants.assert_not_called(); descriptor.assert_not_called()

    def test_all_mappings_precede_selections(self):
        for gate in ('command', 'exact'):
            with patch.object(a.c, 'inspect', return_value={'image_offset': '80000000'}), \
                 patch.object(a.c, 'GBF') as db, \
                 patch.object(a.command, 'mappings') as maps, \
                 patch.object(a.normal, 'mapping_evidence') as exact, \
                 patch.object(a, 'range_evidence') as code, \
                 patch.object(a, 'constant_evidence') as constants, \
                 patch.object(a, 'descriptor_evidence') as descriptor:
                db.return_value.tables.return_value = {'Memory Blocks': {}, 'Sub Memory Blocks': {}}
                if gate == 'command':
                    maps.side_effect = a.c.FormatError('command mapping control')
                else:
                    exact.side_effect = [(a.TEXT_MAPPING, {}), (a.DATA3_MAPPING, {}),
                                         a.c.FormatError('exact mapping control')]
                with self.assertRaisesRegex(a.c.FormatError, 'mapping control'):
                    a.inspect(bytes(32), '0' * 64)
                code.assert_not_called(); constants.assert_not_called(); descriptor.assert_not_called()

    def test_no_address_width_pointer_raw_execute_cli(self):
        for flag in ('--address', '--width', '--pointer', '--raw', '--execute'):
            with patch.object(a.sys, 'argv', ['reader', 'snapshot', flag, '0']), \
                 contextlib.redirect_stderr(io.StringIO()):
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

    def assert_schedule(self, pc, expected):
        for offset, fact in enumerate(expected):
            self.assertEqual(self.fact(pc + offset * 4), fact, f'{pc + offset * 4:08x}')

    def test_both_snapshots_all_derived_evidence_agrees(self):
        for key in ('mappings', 'ranges', 'constants', 'descriptor_window', 'r2_basis', 'function_coverage'):
            self.assertEqual(self.reports[0][key], self.reports[1][key])
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual(len(self.facts), 185)
        for span in self.reports[0]['ranges']:
            self.assertEqual([item['address'] for item in span['instructions']],
                             [f'{pc:08x}' for pc in range(int(span['address'], 16), int(span['end_exclusive'], 16), 4)])

    def test_exact_constants_recorded_r2_and_bounded_window(self):
        report = self.reports[0]
        self.assertEqual([(item['address'], item['bits']) for item in report['constants']],
                         [('804373c0', '3f666666'), ('804373c4', '3dccccd0'),
                          ('804373c8', '3f800000'), ('804373d0', '4330000080000000')])
        self.assertEqual([item['value'] for item in report['constants']],
                         [0.8999999761581421, 0.10000002384185791, 1.0, float(2 ** 52 + 2 ** 31)])
        self.assertEqual(report['r2_basis']['displacements'],
                         {'804373c0': -30304, '804373c4': -30300,
                          '804373c8': -30296, '804373d0': -30288})
        window = report['descriptor_window']
        self.assertEqual((window['address'], window['width']), ('8033b028', 8))
        self.assertEqual(window['values'], [12, 2, 7, 11, -1, -1, -1, -1])
        self.assertFalse(window['extent_proven'])
        self.assertEqual(int(window['descriptor_base'], 16) + window['descriptor_offset'], 0x8033b028)

    def test_constructor_descriptor_producer_is_not_pointer_following(self):
        self.assertEqual(self.fact(0x8006f6a8), dict(mnemonic='addis', rD=9, rA=0, immediate=-32716))
        self.assertEqual(self.fact(0x8006f6d4), dict(mnemonic='addi', rD=0, rA=9, immediate=-20616))
        self.assertEqual(self.fact(0x8006f6e0), dict(mnemonic='stw', rS=0, rA=3, displacement=0x4b0))
        self.assertEqual(((-32716 << 16) - 20616) & 0xffffffff, 0x8033af78)

    def test_factor_load_order_and_single_fusion(self):
        self.assert_schedule(0x80059fac, [
            dict(mnemonic='lfs', fD=1, rA=2, displacement=-30296),
            dict(mnemonic='addi', rD=0, rA=0, immediate=8),
            dict(mnemonic='lfs', fD=0, rA=31, displacement=0x1dc8),
            dict(mnemonic='addi', rD=5, rA=0, immediate=0),
            dict(mnemonic='lfs', fD=3, rA=2, displacement=-30300),
            dict(mnemonic='addis', rD=3, rA=0, immediate=0x4330),
            dict(mnemonic='fsubs', fD=2, fA=1, fB=0),
            dict(mnemonic='lfs', fD=0, rA=2, displacement=-30304),
            dict(mnemonic='lfd', fD=1, rA=2, displacement=-30288),
            dict(mnemonic='fmadds', fD=2, fA=3, fC=2, fB=0),
            dict(mnemonic='mtctr', rS=0),
        ])

    def test_signed_list_access_sentinel_order_and_eight_limit(self):
        self.assert_schedule(0x80059fd8, [
            dict(mnemonic='lwz', rD=4, rA=31, displacement=0x4b0),
            dict(mnemonic='addi', rD=0, rA=5, immediate=0xb0),
            dict(mnemonic='lbzx', rD=0, rA=4, rB=0),
            dict(mnemonic='extsb', rS=0, rA=0, Rc=0),
            dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=-1),
            dict(mnemonic='bc', BO=12, BI=2, LK=0, target='8005a084', AA=0),
            dict(mnemonic='mulli', rD=0, rA=0, immediate=6),
            dict(mnemonic='stw', rS=3, rA=1, displacement=8),
            dict(mnemonic='addi', rD=5, rA=5, immediate=1),
            dict(mnemonic='stw', rS=3, rA=1, displacement=24),
            dict(mnemonic='add', rD=4, rA=31, rB=0, Rc=0),
        ])
        self.assertEqual(self.fact(0x8005a080),
                         dict(mnemonic='bc', BO=16, BI=0, LK=0, target='80059fd8', AA=0))
        # There is no deduplication or "index < count" branch in the complete loop.
        self.assertEqual([pc for pc, fact in self.facts.items() if 0x80059fd8 <= int(pc, 16) <= 0x8005a080
                          and fact['mnemonic'] in ('b', 'bc', 'bl')], ['80059fec', '8005a080'])

    def test_each_list_axis_conversion_and_immediate_store(self):
        for load_pc, offset, input_stack, output_stack in (
                (0x8005a004, 0x18d4, 8, 16),
                (0x8005a030, 0x18d6, 24, 32),
                (0x8005a058, 0x18d8, 40, 48)):
            schedule = [dict(mnemonic='lha', rD=0, rA=4, displacement=offset)]
            if load_pc == 0x8005a004:
                schedule.append(dict(mnemonic='stw', rS=3, rA=1, displacement=40))
            schedule.extend([
                dict(mnemonic='xoris', rS=0, rA=0, immediate=0x8000),
                dict(mnemonic='stw', rS=0, rA=1, displacement=input_stack + 4),
                dict(mnemonic='lfd', fD=0, rA=1, displacement=input_stack),
                dict(mnemonic='fsubs', fD=0, fA=0, fB=1),
                dict(mnemonic='fmuls', fD=0, fA=0, fC=2),
                dict(mnemonic='fctiwz', fD=0, fB=0),
                dict(mnemonic='stfd', fS=0, rA=1, displacement=output_stack),
                dict(mnemonic='lwz', rD=0, rA=1, displacement=output_stack + 4),
                dict(mnemonic='sth', rS=0, rA=4, displacement=offset),
            ])
            self.assert_schedule(load_pc, schedule)

    def test_trailing_first_axis_still_executes_after_sentinel(self):
        self.assert_schedule(0x8005a084, [
            dict(mnemonic='lha', rD=3, rA=31, displacement=0x18da),
            dict(mnemonic='addis', rD=0, rA=0, immediate=0x4330),
            dict(mnemonic='stw', rS=0, rA=1, displacement=48),
            dict(mnemonic='xoris', rS=3, rA=3, immediate=0x8000),
            dict(mnemonic='lfd', fD=1, rA=2, displacement=-30288),
            dict(mnemonic='stw', rS=3, rA=1, displacement=52),
            dict(mnemonic='lfd', fD=0, rA=1, displacement=48),
            dict(mnemonic='stw', rS=0, rA=1, displacement=32),
            dict(mnemonic='fsubs', fD=0, fA=0, fB=1),
            dict(mnemonic='stw', rS=0, rA=1, displacement=16),
            dict(mnemonic='fmuls', fD=0, fA=0, fC=2),
            dict(mnemonic='fctiwz', fD=0, fB=0),
            dict(mnemonic='stfd', fS=0, rA=1, displacement=40),
            dict(mnemonic='lwz', rD=0, rA=1, displacement=44),
            dict(mnemonic='sth', rS=0, rA=31, displacement=0x18da),
        ])

    def test_remaining_trailing_axes_are_ordered_then_exit(self):
        for pc, offset, input_stack, output_stack in (
                (0x8005a0c0, 0x18dc, 32, 24), (0x8005a0e8, 0x18de, 16, 8)):
            self.assert_schedule(pc, [
                dict(mnemonic='lha', rD=0, rA=31, displacement=offset),
                dict(mnemonic='xoris', rS=0, rA=0, immediate=0x8000),
                dict(mnemonic='stw', rS=0, rA=1, displacement=input_stack + 4),
                dict(mnemonic='lfd', fD=0, rA=1, displacement=input_stack),
                dict(mnemonic='fsubs', fD=0, fA=0, fB=1),
                dict(mnemonic='fmuls', fD=0, fA=0, fC=2),
                dict(mnemonic='fctiwz', fD=0, fB=0),
                dict(mnemonic='stfd', fS=0, rA=1, displacement=output_stack),
                dict(mnemonic='lwz', rD=0, rA=1, displacement=output_stack + 4),
                dict(mnemonic='sth', rS=0, rA=31, displacement=offset),
            ])
        self.assertEqual(self.fact(0x8005a110), dict(mnemonic='b', target='8005a130', AA=0))


if __name__ == '__main__':
    unittest.main()
