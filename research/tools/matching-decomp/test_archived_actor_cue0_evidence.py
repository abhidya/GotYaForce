#!/usr/bin/env python3
"""Synthetic fail-closed tests and optional archived cue0/terrain schedules."""
import contextlib
import hashlib
import io
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_actor_cue0_evidence as a


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


def fp(op, d, aa, b, fc, xo, rc=0):
    return op << 26 | d << 21 | aa << 16 | b << 11 | fc << 6 | xo << 1 | rc


class SyntheticTests(unittest.TestCase):
    def test_exact_independent_ranges(self):
        self.assertEqual([(address, width) for address, width, _ in a.RANGES],
                         [(0x8005913c, 180), (0x80068df8, 420)])
        for address, width in ((0x80059138, 4), (0x8005913c, 176), (0x80059140, 180),
                               (0x80068df8, 416), (0x8006a5a4, 196), (0, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, address, width)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, 0x8005913c, 180)

    def test_only_existing_cue0_cell(self):
        raw = struct.pack('>I', 0x8005913c)
        db = FakeDB(raw)
        result = a.cell_evidence(db, a.DATA3_MAPPING, 0x802d3300)
        self.assertEqual(result['target'], '8005913c')
        self.assertEqual(db.calls, [(199, 99488, 4, 1000128)])
        for address in (0x802d3324, 0x802d3304, 0x8005913c, 0):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.cell_evidence(None, a.DATA3_MAPPING, address)
        for raw, reason in ((raw[:-1], 'byte width'), (struct.pack('>I', 0x80059138), 'digest mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.cell_evidence(FakeDB(raw), a.DATA3_MAPPING, 0x802d3300)

    def test_selection_types_before_read(self):
        for bad in (True, 1.0, '4', None):
            for reader, mapping, address, width in (
                    (a.range_evidence, a.TEXT_MAPPING, 0x8005913c, 180),
                    (a.constant_evidence, a.DATA5_MAPPING, 0x8043762c, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    reader(None, mapping, bad, width)
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    reader(None, mapping, address, bad)
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.cell_evidence(None, a.DATA3_MAPPING, bad)

    def test_exact_mapping_values_and_types(self):
        for reader, mapping, args in (
                (a.range_evidence, a.TEXT_MAPPING, (0x8005913c, 180)),
                (a.constant_evidence, a.DATA5_MAPPING, (0x8043762c, 4)),
                (a.cell_evidence, a.DATA3_MAPPING, (0x802d3300,))):
            for altered in (list(mapping), mapping[:-1] + (mapping[-1] + 1,),
                            mapping[:2] + (float(mapping[2]),) + mapping[3:],
                            (mapping[0] - 4,) + mapping[1:]):
                with self.assertRaisesRegex(a.c.FormatError, 'mapping'):
                    reader(None, altered, *args)

    def test_constants_only_fixed_addresses_and_widths(self):
        for address, width in ((0x80437630, 4), (0x8043762c, 8), (0x80437638, 4),
                               (0x80437640, 4), (0x80437648, 8), (0, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, address, width)
        with patch.object(a, 'CONSTANTS', a.CONSTANTS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, 0x8043762c, 4)

    def test_exact_constant_bits_width_and_trace(self):
        for address, width, bits in a.CONSTANTS:
            raw = bytes.fromhex(bits)
            db = FakeDB(raw)
            result = a.constant_evidence(db, a.DATA5_MAPPING, address, width)
            self.assertEqual(result['bits'], bits)
            self.assertEqual(result['value'], struct.unpack('>f' if width == 4 else '>d', raw)[0])
            self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
            self.assertEqual(db.calls, [(263, address - 0x80436a20, width, 27360)])
            for altered, reason in ((raw[:-1], 'byte width'), (bytes([255]) * width, 'bits mismatch')):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.constant_evidence(FakeDB(altered), a.DATA5_MAPPING, address, width)
        with self.assertRaisesRegex(a.c.FormatError, 'bits mismatch'):
            a.constant_evidence(FakeDB(bytes.fromhex('80000000')), a.DATA5_MAPPING, 0x8043762c, 4)

    def test_range_width_digest_precede_decode(self):
        for raw, reason in ((bytes(180), 'digest mismatch'), (bytes(176), 'byte width')):
            with patch.object(a, 'decode_selected') as decode:
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x8005913c, 180)
                decode.assert_not_called()

    def test_range_unknown_instruction_refuses(self):
        raw = bytes(180)
        with patch.object(a, 'RANGES', ((0x8005913c, 180, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x8005913c, 180)

    def test_range_terminal_and_internal_branch_checks(self):
        for words, reason in (([0x38600000] * 45, 'terminal return'),
                              ([0x48001000] + [0x4e800020] * 44, 'outside fixed span')):
            raw = struct.pack('>45I', *words)
            with patch.object(a, 'RANGES', ((0x8005913c, 180, hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x8005913c, 180)
        raw = struct.pack('>45I', *([0x4e800020] * 45))
        with patch.object(a, 'RANGES', ((0x8005913c, 180, hashlib.sha256(raw).hexdigest()),)):
            db = FakeDB(raw)
            result = a.range_evidence(db, a.TEXT_MAPPING, 0x8005913c, 180)
            self.assertEqual(len(result['instructions']), 45)
            self.assertEqual(db.calls, [(21, 342876, 180, 2796416)])
            self.assertNotIn('raw', result)

    def test_float_decoder_preserves_operands_and_fusion(self):
        cases = (
            (fp(63, 0, 1, 2, 0, 32), dict(mnemonic='fcmpo', BF=0, fA=1, fB=2)),
            (fp(63, 0, 1, 0, 0, 0), dict(mnemonic='fcmpu', BF=0, fA=1, fB=0)),
            (fp(63, 0, 0, 2, 0, 40), dict(mnemonic='fneg', fD=0, fB=2)),
            (fp(63, 3, 0, 6, 0, 26), dict(mnemonic='frsqrte', fD=3, fB=6)),
            (fp(63, 0, 0, 0, 0, 12), dict(mnemonic='frsp', fD=0, fB=0)),
            (fp(63, 3, 5, 0, 3, 25), dict(mnemonic='fmul', fD=3, fA=5, fC=3)),
            (fp(63, 0, 6, 4, 0, 30), dict(mnemonic='fnmsub', fD=0, fA=6, fC=0, fB=4)),
            (fp(59, 3, 6, 3, 0, 18), dict(mnemonic='fdivs', fD=3, fA=6, fB=3)),
            (fp(59, 6, 1, 3, 1, 29), dict(mnemonic='fmadds', fD=6, fA=1, fC=1, fB=3)),
        )
        for word, expected in cases:
            self.assertEqual(a.decode_selected(word, 0x80068df8), expected)
        self.assertEqual(a.decode_selected(52 << 26 | 31 << 21 | 31 << 16 | 36, 0x80068e88),
                         dict(mnemonic='stfs', fS=31, rA=31, displacement=36))
        self.assertEqual(a.decode_selected(16 << 26 | 12 << 21 | 12, 0x80068e7c),
                         dict(mnemonic='bc', BO=12, BI=0, LK=0, target='80068e88', AA=0))

    def test_float_decoder_rejects_reserved_and_unselected_fields(self):
        cases = (
            (fp(63, 1, 1, 2, 0, 32), 'comparison'),
            (fp(63, 0, 1, 2, 0, 32, 1), 'comparison'),
            (fp(63, 3, 1, 6, 0, 26), 'unary'),
            (fp(63, 0, 0, 2, 0, 40, 1), 'unary'),
            (fp(63, 3, 5, 1, 3, 25), 'double-multiply'),
            (fp(63, 0, 6, 4, 0, 30, 1), 'double-fused'),
            (fp(59, 3, 6, 3, 1, 18), 'single-division'),
            (16 << 26 | 12 << 21 | 13, 'conditional branch'),
        )
        for word, reason in cases:
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.decode_selected(word, 0x80068df8)
        self.assertIsNone(a.decode_selected(0, 0x80068df8))
        for bad in (True, -1, 1 << 32, 1.5):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'):
                a.decode_selected(bad, 0x80068df8)
        for bad in (True, -4, 1 << 32, 0x80068dfa):
            with self.assertRaisesRegex(a.c.FormatError, 'PC bounds'):
                a.decode_selected(0, bad)

    def test_paired_single_abi_forms_not_dropped(self):
        for op, name, reg in ((56, 'psq_l', 'fD'), (60, 'psq_st', 'fS')):
            word = op << 26 | 31 << 21 | 1 << 16 | 40
            self.assertEqual(a.decode_selected(word, 0x80068df8),
                             dict(mnemonic=name, **{reg: 31}, rA=1, W=0, I=0, displacement=40))
            for altered in (word | 1 << 15, word | 1 << 12, word ^ 1, word ^ 1 << 21,
                            word ^ 1 << 16):
                with self.assertRaisesRegex(a.c.FormatError, 'paired-single ABI'):
                    a.decode_selected(altered, 0x80068df8)

    def test_full_authentication_precedes_selections(self):
        with patch.object(a, 'range_evidence') as code, \
             patch.object(a, 'constant_evidence') as constants, \
             patch.object(a, 'cell_evidence') as cell:
            for digest in ('0' * 64, next(iter(a.c.SNAPSHOTS))):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256'):
                    a.inspect(bytes(32), digest)
            code.assert_not_called(); constants.assert_not_called(); cell.assert_not_called()

    def test_all_mappings_precede_selections(self):
        for gate in ('command', 'exact'):
            with patch.object(a.c, 'inspect', return_value={'image_offset': '80000000'}), \
                 patch.object(a.c, 'GBF') as db, \
                 patch.object(a.command, 'mappings') as maps, \
                 patch.object(a.normal, 'mapping_evidence') as exact, \
                 patch.object(a, 'range_evidence') as code, \
                 patch.object(a, 'constant_evidence') as constants, \
                 patch.object(a, 'cell_evidence') as cell:
                db.return_value.tables.return_value = {'Memory Blocks': {}, 'Sub Memory Blocks': {}}
                if gate == 'command':
                    maps.side_effect = a.c.FormatError('command mapping control')
                else:
                    exact.side_effect = [(a.TEXT_MAPPING, {}), (a.DATA3_MAPPING, {}),
                                         a.c.FormatError('exact mapping control')]
                with self.assertRaisesRegex(a.c.FormatError, 'mapping control'):
                    a.inspect(bytes(32), '0' * 64)
                code.assert_not_called(); constants.assert_not_called(); cell.assert_not_called()

    def test_no_address_width_pointer_raw_execute_cli(self):
        for flag in ('--address', '--width', '--pointer', '--raw', '--execute'):
            with patch.object(a.sys, 'argv', ['reader', 'snapshot', flag, '0']), \
                 contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as error:
                    a.main()
                self.assertEqual(error.exception.code, 2)


ROOT = Path(__file__).resolve().parents[3]
SNAPSHOT_DIR = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


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

    def test_both_snapshots_agree_and_all_instructions_represented(self):
        for key in ('mappings', 'cells', 'ranges', 'constants', 'r2_basis', 'function_coverage'):
            self.assertEqual(self.reports[0][key], self.reports[1][key])
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual(len(self.facts), 150)
        for span, coverage in zip(self.reports[0]['ranges'], self.reports[0]['function_coverage']):
            start, end = int(span['address'], 16), int(span['end_exclusive'], 16)
            self.assertEqual([item['address'] for item in span['instructions']],
                             [f'{pc:08x}' for pc in range(start, end, 4)])
            self.assertEqual(coverage['represented_instructions'], (end - start) // 4)
            self.assertEqual(coverage['unrepresented_instructions'], 0)
            self.assertEqual(coverage['unrepresented_ranges'], [])
            self.assertEqual([item['address'] for item in span['instructions'] if item['mnemonic'] == 'blr'],
                             [f'{end - 4:08x}'])
            self.assertTrue(all(start <= int(item['target'], 16) < end
                                for item in span['instructions'] if item['mnemonic'] in ('bc', 'b')))

    def test_source_extent_markers_and_no_invented_map_extent(self):
        for file, entry, end in (('chunk_0007.c', '8005913c', '800591f0'),
                                 ('chunk_0008.c', '80068df8', '80068f9c')):
            source = (ROOT / 'research/decomp/ghidra-export' / file).read_text()
            marker = source.index('// ==== ' + entry + ' ')
            following = source.index('// ==== ', marker + 10)
            self.assertTrue(source[following:].startswith('// ==== ' + end + ' '))
        symbol_map = (ROOT / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        self.assertFalse(any(line.startswith(('8005913c ', '80068df8 ')) for line in symbol_map.splitlines()))
        self.assertIn('80068d04 000000f4 80068d04 0 zz_0068d04_', symbol_map)

    def test_reused_table_cell_does_not_select_body_or_helpers(self):
        self.assertEqual([(cell['address'], cell['target']) for cell in self.reports[0]['cells']],
                         [('802d3300', '8005913c')])
        self.assertEqual([span['address'] for span in self.reports[0]['ranges']], ['8005913c', '80068df8'])
        for address in ('8003d6e4', '800452a0', '8006a5a4', '8006a750', '8006a6fc', '800699d8'):
            self.assertNotIn(address, self.facts)

    def test_cue0_movement3_two_ordered_calls(self):
        self.assert_schedule(0x80059150, [
            dict(mnemonic='lbz', rD=0, rA=3, displacement=0x661),
            dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=3),
            dict(mnemonic='bc', BO=4, BI=2, LK=0, target='80059174', AA=0),
            dict(mnemonic='addi', rD=4, rA=0, immediate=0x1b),
            dict(mnemonic='bl', target='8006a750', AA=0),
            dict(mnemonic='or', rS=31, rA=3, rB=31, Rc=0),
            dict(mnemonic='addi', rD=4, rA=0, immediate=0x1b),
            dict(mnemonic='bl', target='8006a6fc', AA=0),
            dict(mnemonic='b', target='800591dc', AA=0),
        ])
        self.assertFalse(any(self.fact(pc)['mnemonic'] == 'extsb' for pc in range(0x8005913c, 0x800591f0, 4)))

    def test_cue0_ordered_short_circuit_not_noop_on_terrain_zero(self):
        for pc, target in ((0x80059174, '80068df8'), (0x80059184, '800699d8'),
                           (0x80059194, '80069814'), (0x800591a4, '800696f4'),
                           (0x800591b4, '80069038'), (0x800591c4, '80069354')):
            self.assert_schedule(pc, [
                dict(mnemonic='bl', target=target, AA=0),
                dict(mnemonic='cmpi', BF=0, L=0, rA=3, immediate=0),
                dict(mnemonic='bc', BO=4, BI=2, LK=0, target='800591dc', AA=0),
                dict(mnemonic='or', rS=31, rA=3, rB=31, Rc=0),
            ])
        self.assert_schedule(0x800591d4, [dict(mnemonic='bl', target='80068f9c', AA=0),
                                         dict(mnemonic='cmpi', BF=0, L=0, rA=3, immediate=0)])

    def test_terrain_flag_and_mode_guards_precede_sample(self):
        self.assert_schedule(0x80068e10, [
            dict(mnemonic='lwz', rD=0, rA=3, displacement=0x5e0),
            dict(mnemonic='or', rS=3, rA=31, rB=3, Rc=0),
            dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=25, ME=25, Rc=1),
            dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80068e28', AA=0),
            dict(mnemonic='addi', rD=3, rA=0, immediate=0),
            dict(mnemonic='b', target='80068f80', AA=0),
            dict(mnemonic='lbz', rD=0, rA=31, displacement=0x4a0),
            dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=2),
            dict(mnemonic='bc', BO=4, BI=2, LK=0, target='80068e3c', AA=0),
            dict(mnemonic='addi', rD=3, rA=0, immediate=0),
            dict(mnemonic='b', target='80068f80', AA=0),
        ])

    def test_genuine_terrain_call_store_and_byte732_order(self):
        self.assert_schedule(0x80068e3c, [
            dict(mnemonic='lfs', fD=31, rA=31, displacement=0x24),
            dict(mnemonic='addi', rD=4, rA=31, immediate=0x20),
            dict(mnemonic='lfs', fD=1, rA=31, displacement=0x668),
            dict(mnemonic='bl', target='8003d6e4', AA=0),
            dict(mnemonic='stfs', fS=1, rA=31, displacement=0x24),
            dict(mnemonic='addi', rD=3, rA=0, immediate=0),
            dict(mnemonic='lbz', rD=0, rA=31, displacement=0x732),
            dict(mnemonic='lfs', fD=1, rA=31, displacement=0x24),
            dict(mnemonic='lfs', fD=0, rA=31, displacement=0x30),
            dict(mnemonic='extsb', rS=0, rA=0, Rc=1),
            dict(mnemonic='lfs', fD=2, rA=31, displacement=0x674),
            dict(mnemonic='fsubs', fD=1, fA=1, fB=0),
            dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80068e74', AA=0),
            dict(mnemonic='addi', rD=3, rA=0, immediate=1),
            dict(mnemonic='fneg', fD=0, fB=2),
            dict(mnemonic='fcmpo', BF=0, fA=1, fB=0),
            dict(mnemonic='bc', BO=12, BI=0, LK=0, target='80068e88', AA=0),
            dict(mnemonic='cmpi', BF=0, L=0, rA=3, immediate=0),
            dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80068f3c', AA=0),
        ])

    def test_active_restores_y_before_exact_fused_squared_distance(self):
        self.assert_schedule(0x80068e88, [
            dict(mnemonic='stfs', fS=31, rA=31, displacement=0x24),
            dict(mnemonic='lfs', fD=0, rA=2, displacement=-29684),
            dict(mnemonic='lfs', fD=2, rA=31, displacement=0x28),
            dict(mnemonic='lfs', fD=1, rA=31, displacement=0x34),
            dict(mnemonic='lfs', fD=3, rA=31, displacement=0x20),
            dict(mnemonic='fsubs', fD=2, fA=2, fB=1),
            dict(mnemonic='lfs', fD=1, rA=31, displacement=0x2c),
            dict(mnemonic='fsubs', fD=1, fA=3, fB=1),
            dict(mnemonic='fmuls', fD=3, fA=2, fC=2),
            dict(mnemonic='fmadds', fD=6, fA=1, fC=1, fB=3),
            dict(mnemonic='fcmpo', BF=0, fA=6, fB=0),
            dict(mnemonic='bc', BO=4, BI=1, LK=0, target='80068f04', AA=0),
        ])

    def test_positive_distance_uses_estimate_and_double_fused_refinement(self):
        expected = [dict(mnemonic='frsqrte', fD=3, fB=6),
                    dict(mnemonic='lfd', fD=5, rA=2, displacement=-29672),
                    dict(mnemonic='lfd', fD=4, rA=2, displacement=-29664)]
        for _ in range(2):
            expected.extend([dict(mnemonic='fmul', fD=0, fA=3, fC=3),
                             dict(mnemonic='fmul', fD=3, fA=5, fC=3),
                             dict(mnemonic='fnmsub', fD=0, fA=6, fC=0, fB=4),
                             dict(mnemonic='fmul', fD=3, fA=3, fC=0)])
        expected.extend([dict(mnemonic='fmul', fD=0, fA=3, fC=3),
                         dict(mnemonic='fmul', fD=3, fA=5, fC=3),
                         dict(mnemonic='fnmsub', fD=0, fA=6, fC=0, fB=4),
                         dict(mnemonic='fmul', fD=0, fA=3, fC=0),
                         dict(mnemonic='fmul', fD=0, fA=6, fC=0),
                         dict(mnemonic='frsp', fD=0, fB=0),
                         dict(mnemonic='stfs', fS=0, rA=1, displacement=8),
                         dict(mnemonic='lfs', fD=6, rA=1, displacement=8)])
        self.assert_schedule(0x80068eb8, expected)
        self.assertEqual(len(expected), 19)

    def test_zero_distance_division_speed_write_then_angle_boundary(self):
        self.assert_schedule(0x80068f04, [
            dict(mnemonic='lfs', fD=3, rA=31, displacement=0x5f8),
            dict(mnemonic='lfs', fD=0, rA=31, displacement=0x44),
            dict(mnemonic='fdivs', fD=3, fA=6, fB=3),
            dict(mnemonic='fcmpo', BF=0, fA=3, fB=0),
            dict(mnemonic='bc', BO=4, BI=1, LK=0, target='80068f24', AA=0),
            dict(mnemonic='stfs', fS=3, rA=31, displacement=0x44),
            dict(mnemonic='bl', target='800452a0', AA=0),
            dict(mnemonic='sth', rS=3, rA=31, displacement=0x5ae),
        ])

    def test_slope30_store_before_helper_and_success_return(self):
        self.assert_schedule(0x80068f24, [
            dict(mnemonic='lfs', fD=0, rA=2, displacement=-29656),
            dict(mnemonic='or', rS=31, rA=3, rB=31, Rc=0),
            dict(mnemonic='stfs', fS=0, rA=31, displacement=0x698),
            dict(mnemonic='bl', target='8006a5a4', AA=0),
            dict(mnemonic='addi', rD=3, rA=0, immediate=1),
            dict(mnemonic='b', target='80068f80', AA=0),
        ])

    def test_upper_step_compares_x_then_z_only_if_equal(self):
        self.assert_schedule(0x80068f3c, [
            dict(mnemonic='fcmpo', BF=0, fA=1, fB=2),
            dict(mnemonic='bc', BO=4, BI=1, LK=0, target='80068f7c', AA=0),
            dict(mnemonic='lfs', fD=1, rA=31, displacement=0x20),
            dict(mnemonic='lfs', fD=0, rA=31, displacement=0x2c),
            dict(mnemonic='fcmpu', BF=0, fA=1, fB=0),
            dict(mnemonic='bc', BO=4, BI=2, LK=0, target='80068f64', AA=0),
            dict(mnemonic='lfs', fD=1, rA=31, displacement=0x28),
            dict(mnemonic='lfs', fD=0, rA=31, displacement=0x34),
            dict(mnemonic='fcmpu', BF=0, fA=1, fB=0),
            dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80068f7c', AA=0),
        ])

    def test_raw_rollback_load_store_interleave(self):
        self.assert_schedule(0x80068f64, [
            dict(mnemonic='lwz', rD=3, rA=31, displacement=0x2c),
            dict(mnemonic='lwz', rD=0, rA=31, displacement=0x30),
            dict(mnemonic='stw', rS=3, rA=31, displacement=0x20),
            dict(mnemonic='stw', rS=0, rA=31, displacement=0x24),
            dict(mnemonic='lwz', rD=0, rA=31, displacement=0x34),
            dict(mnemonic='stw', rS=0, rA=31, displacement=0x28),
            dict(mnemonic='addi', rD=3, rA=0, immediate=0),
        ])

    def test_abi_instructions_including_c_removed_unreachable_blocks(self):
        self.assert_schedule(0x80068df8, [
            dict(mnemonic='stwu', rS=1, rA=1, displacement=-48),
            dict(mnemonic='mflr', rD=0),
            dict(mnemonic='stw', rS=0, rA=1, displacement=52),
            dict(mnemonic='stfd', fS=31, rA=1, displacement=32),
            dict(mnemonic='psq_st', fS=31, rA=1, W=0, I=0, displacement=40),
            dict(mnemonic='stw', rS=31, rA=1, displacement=28),
        ])
        self.assert_schedule(0x80068f80, [
            dict(mnemonic='psq_l', fD=31, rA=1, W=0, I=0, displacement=40),
            dict(mnemonic='lwz', rD=0, rA=1, displacement=52),
            dict(mnemonic='lfd', fD=31, rA=1, displacement=32),
            dict(mnemonic='lwz', rD=31, rA=1, displacement=28),
            dict(mnemonic='mtlr', rS=0),
            dict(mnemonic='addi', rD=1, rA=1, immediate=48),
            dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0),
        ])

    def test_constants_and_recorded_r2_are_exact(self):
        report = self.reports[0]
        self.assertEqual([(item['address'], item['bits'], item['value']) for item in report['constants']],
                         [('8043762c', '00000000', 0.0), ('80437638', '3fe0000000000000', 0.5),
                          ('80437640', '4008000000000000', 3.0), ('80437648', '41f00000', 30.0)])
        self.assertEqual(report['r2_basis']['displacements'],
                         {'8043762c': -29684, '80437638': -29672, '80437640': -29664, '80437648': -29656})
        self.assertEqual(report['r2_basis']['recorded_value'], '8043ea20')


if __name__ == '__main__':
    unittest.main()
