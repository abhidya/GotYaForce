#!/usr/bin/env python3
"""Axis evidence authentication and synthetic decoder controls, not execution."""
import contextlib
import copy
import hashlib
import io
import json
import os
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_angular_axis_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


class SyntheticTests(unittest.TestCase):
    def test_fixed_extents_do_not_claim_general_atan2(self):
        self.assertEqual([(pc, n) for pc, n, _ in a.RANGES],
                         [(0x800452a0, 68), (0x8023cb78, 32), (0x80239984, 244), (0x80239c00, 20)])
        self.assertEqual(sum(n for _, n, _ in a.RANGES), 364)
        self.assertEqual(a.RANGES[2][0] + a.RANGES[2][1], 0x80239a78)
        self.assertNotIn((a.TABLE_ADDRESS, a.TABLE_WIDTH), a.c.TARGETS)
        self.assertTrue(set(pc for pc, _, _ in a.TARGETS).isdisjoint(pc for pc, _ in a.c.TARGETS))

    def test_quantized_forms_preserve_both_lanes_type_index_and_signed_offset(self):
        for op, name, register in ((56, 'psq_l', 'fD'), (60, 'psq_st', 'fS')):
            for offset in (-2048, -1, 0, 8, 24, 2047):
                for w, i in ((0, 0), (1, 4), (1, 5), (0, 7)):
                    word = (op << 26) | (31 << 21) | (1 << 16) | (w << 15) | (i << 12) | (offset & 4095)
                    self.assertEqual(a.decode_selected(word, 0x800452b0),
                                     dict(mnemonic=name, **{register: 31}, rA=1,
                                          displacement=offset, W=w, I=i))

    def test_frsp_fmuls_and_nan_branch_fadd_are_distinct(self):
        frsp = (63 << 26) | (1 << 21) | (1 << 11) | (12 << 1)
        multiply = (59 << 26) | (31 << 21) | (1 << 6) | (25 << 1)
        add = (63 << 26) | (1 << 21) | (1 << 16) | (21 << 1)
        self.assertEqual(a.decode_selected(frsp, 0x800452b8), dict(mnemonic='frsp', fD=1, fB=1))
        self.assertEqual(a.decode_selected(multiply, 0x800452c0), dict(mnemonic='fmuls', fD=31, fA=0, fC=1))
        self.assertEqual(a.decode_selected(add, 0x802399f0), dict(mnemonic='fadd', fD=1, fA=1, fB=0))
        for word in (frsp | 1, frsp | (1 << 16), multiply | 1, multiply | (1 << 11),
                     add | 1, add | (1 << 6)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x800452b8)
        self.assertIsNone(a.decode_selected((63 << 26) | (25 << 1), 0x800452c0))
        self.assertIsNone(a.decode_selected((59 << 26) | (29 << 1), 0x800452c0))

    def test_axis_bit_manipulation_and_comparison(self):
        insert = (20 << 26) | (5 << 21) | (31 << 16) | (1 << 11) | (31 << 6) | (31 << 1)
        self.assertEqual(a.decode_selected(insert, 0x80239a18),
                         dict(mnemonic='rlwimi', rS=5, rA=31, SH=1, MB=31, ME=31, Rc=0))
        neg = (31 << 26) | (8 << 16) | (104 << 1)
        self.assertEqual(a.decode_selected(neg, 0x8023999c), dict(mnemonic='neg', rD=0, rA=8, Rc=0))
        compare = (31 << 26) | (3 << 11) | (32 << 1)
        self.assertEqual(a.decode_selected(compare, 0x802399c0),
                         dict(mnemonic='cmpl', BF=0, L=0, rA=0, rB=3))
        for word in (neg | (1 << 11), compare | 1, compare | (1 << 21), compare | (1 << 22)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x802399c0)

    def test_operand_type_and_bounds_guards(self):
        for word in (-1, 1 << 32, True, False, 1.0, '0', None):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'): a.decode_selected(word, 0x800452a0)
        for pc in (-1, 1, 1 << 32, True, False, 1.0, '0', None):
            with self.assertRaisesRegex(a.c.FormatError, 'PC bounds'): a.decode_selected(0, pc)
        for word in (0, 0x4e800021, 0x4e800421, 34 << 26, 52 << 26, 0xfc000050):
            self.assertIsNone(a.decode_selected(word, 0x800452a0))
        for word in (spr_form(339, spr=8, record=1), spr_form(467, reg=1, spr=8)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x800452a0)

    def test_range_refusals_precede_read_and_decode(self):
        pc, n, _ = a.RANGES[0]
        for args in ((21, pc+4, n-4), (21, pc, n-4), (21, pc, n+4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.range_evidence(None, *args)
        for args in ((21.0, pc, n), (21, True, n), (21, pc, float(n))):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'): a.range_evidence(None, *args)
        with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'): a.range_evidence(None, 22, pc, n)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.range_evidence(None, 21, pc, n)
        for raw, reason in ((bytes(n-1), 'byte width'), (bytes(n), 'digest mismatch')):
            with patch.object(a, 'decode_selected') as decode:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.range_evidence(FakeDB(raw), 21, pc, n)
                decode.assert_not_called()
        # An authenticated synthetic range still cannot silently omit unknown words.
        raw = bytes(4)
        with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'): a.range_evidence(FakeDB(raw), 21, pc, 4)

    def test_constant_and_table_guards(self):
        pc, n, _ = a.TARGETS[0]
        for addr, width in ((pc+4, n), (pc, n+4), (True, n), (pc, 4.0)):
            with self.assertRaises(a.c.FormatError): a.constant_evidence(None, a.DATA5_MAPPING, addr, width)
        with self.assertRaisesRegex(a.c.FormatError, 'data5 mapping'): a.constant_evidence(None, a.DATA4_MAPPING, pc, n)
        with self.assertRaisesRegex(a.c.FormatError, 'data4 mapping'): a.table_evidence(None, a.DATA5_MAPPING)
        for raw, reason in ((bytes(n-1), 'byte width'), (bytes(n), 'bits mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, reason): a.constant_evidence(FakeDB(raw), a.DATA5_MAPPING, pc, n)
        for raw, reason in ((bytes(7), 'byte width'), (bytes(8), 'digest mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, reason): a.table_evidence(FakeDB(raw), a.DATA4_MAPPING)
        with patch.object(a, 'TABLE_SHA256', hashlib.sha256(bytes(8)).hexdigest()):
            with self.assertRaisesRegex(a.c.FormatError, 'values mismatch'): a.table_evidence(FakeDB(bytes(8)), a.DATA4_MAPPING)

    def test_authentication_precedes_all_new_reads(self):
        for digest in ('0'*64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); reader.assert_not_called()
        for reason in ('schema', 'language', 'File Bytes table is not empty', 'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_mapping_failures_precede_fixed_reads(self):
        blocks = {
            1: ['MAIN_.text1', None, None, 0, 0x20000000000055e0, a.wait.TEXT_LENGTH, 0],
            6: ['MAIN_.data4', None, None, 0, 0x20000000004335a0, 11040, 0],
            7: ['MAIN_.data5', None, None, 0, 0x2000000000436a20, 27360, 0],
        }
        subs = {1: [1, 2, a.wait.TEXT_LENGTH, 0, 21, 0], 6: [6, 2, 11040, 0, 262, 0], 7: [7, 2, 27360, 0, 263, 0]}
        a.mappings(blocks, subs, 0x80000000)
        cases = []
        for key in (1, 6, 7):
            for index in (1, 2, 3, 4, 5):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][index] += 1; cases.append((bb, ss, '80000000'))
        for key in (6, 7):
            for index in (4, 5, 6):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][index] += 1; cases.append((bb, ss, '80000000'))
        bb = copy.deepcopy(blocks); bb[99] = bb[6].copy(); cases.append((bb, subs, '80000000'))
        cases.append((blocks, subs, '80000004'))
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as text_reader, patch.object(a, 'constant_evidence') as constants, \
                    patch.object(a, 'table_evidence') as table:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                text_reader.assert_not_called(); constants.assert_not_called(); table.assert_not_called()

    def test_no_arbitrary_cli(self):
        for option in (['--address', '800452a0'], ['--width', '68'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as reader:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2); reader.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(path.is_file() for path in paths): raise unittest.SkipTest('both existing archived snapshots required')
        cls.results, cls.fixed_text = [], []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
            if not cls.fixed_text:
                # Only the same authenticated fixed ranges, held in memory for mutation controls.
                db = a.c.GBF(data)
                cls.fixed_text = [(pc, n, db.chain(21, pc-a.wait.TEXT_START, n, a.wait.TEXT_LENGTH)[0])
                                  for pc, n, _ in a.RANGES]
        cls.by_pc = {item['address']: {k: v for k, v in item.items() if k != 'address'}
                     for span in cls.results[0]['ranges'] for item in span['instructions']}

    def test_cross_snapshot_identity_coverage_and_no_raw_output(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        for key in ('ranges', 'constants', 'direction_table', 'function_coverage'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            for span, (pc, n, digest) in zip(result['ranges'], a.RANGES):
                self.assertEqual(span['sha256'], digest)
                self.assertEqual([x['address'] for x in span['instructions']], [f'{x:08x}' for x in range(pc, pc+n, 4)])
                self.assertEqual(sum(x['length'] for x in span['spans']), n)
                for item in [span] + span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes')))
            self.assertEqual(result['function_coverage'][2]['unrepresented_ranges'],
                             [dict(start='80239a78', end_exclusive='80239c00', width=392)])
            self.assertEqual(sum(x['represented_instructions'] for x in result['function_coverage']), 91)
            json.dumps(result, allow_nan=False)

    def test_full_wrapper_and_shim_operands(self):
        expected = [
            dict(mnemonic='stwu', rS=1, rA=1, displacement=-32), dict(mnemonic='mflr', rD=0),
            dict(mnemonic='stw', rS=0, rA=1, displacement=36), dict(mnemonic='stfd', fS=31, rA=1, displacement=16),
            dict(mnemonic='psq_st', fS=31, rA=1, displacement=24, W=0, I=0),
            dict(mnemonic='bl', target='8023cb78', AA=0), dict(mnemonic='frsp', fD=1, fB=1),
            dict(mnemonic='lfs', fD=0, rA=2, displacement=-31140), dict(mnemonic='fmuls', fD=31, fA=0, fC=1),
            dict(mnemonic='psq_st', fS=31, rA=1, displacement=8, W=1, I=5),
            dict(mnemonic='lha', rD=3, rA=1, displacement=8),
            dict(mnemonic='psq_l', fD=31, rA=1, displacement=24, W=0, I=0),
            dict(mnemonic='lwz', rD=0, rA=1, displacement=36), dict(mnemonic='lfd', fD=31, rA=1, displacement=16),
            dict(mnemonic='mtlr', rS=0), dict(mnemonic='addi', rD=1, rA=1, immediate=32), dict(mnemonic='blr'),
        ]
        self.assertEqual([self.by_pc[f'{pc:08x}'] for pc in range(0x800452a0, 0x800452e4, 4)], expected)
        self.assertEqual(self.by_pc['8023cb84'], dict(mnemonic='bl', target='80239984', AA=0))
        self.assertEqual(self.by_pc['8023cb94'], dict(mnemonic='blr'))

    def test_axis_signs_early_returns_and_nonaxis_cut(self):
        expected = {
            '80239990': dict(mnemonic='stfd', fS=2, rA=1, displacement=16),
            '802399a8': dict(mnemonic='stfd', fS=1, rA=1, displacement=8),
            '802399f8': dict(mnemonic='addis', rD=0, rA=4, immediate=-16368),
            '802399fc': dict(mnemonic='or', rS=0, rA=0, rB=8, Rc=1),
            '80239a00': dict(mnemonic='bc', BO=4, BI=2, LK=0, target='80239a0c', AA=0),
            '80239a04': dict(mnemonic='bl', target='8023c240', AA=0),
            '80239a0c': dict(mnemonic='or', rS=7, rA=0, rB=9, Rc=1),
            '80239a10': dict(mnemonic='rlwinm', rS=4, rA=0, SH=2, MB=30, ME=30, Rc=0),
            '80239a18': dict(mnemonic='rlwimi', rS=5, rA=31, SH=1, MB=31, ME=31, Rc=0),
            '80239a1c': dict(mnemonic='bc', BO=4, BI=2, LK=0, target='80239a58', AA=0),
            '80239a30': dict(mnemonic='bc', BO=4, BI=0, LK=0, target='80239c00', AA=0),
            '80239a48': dict(mnemonic='lfd', fD=1, rA=2, displacement=-7336),
            '80239a50': dict(mnemonic='lfd', fD=1, rA=2, displacement=-7328),
            '80239a58': dict(mnemonic='or', rS=6, rA=0, rB=8, Rc=1),
            '80239a5c': dict(mnemonic='bc', BO=4, BI=2, LK=0, target='80239a78', AA=0),
            '80239a60': dict(mnemonic='cmpi', BF=0, L=0, rA=5, immediate=0),
            '80239a68': dict(mnemonic='lfd', fD=1, rA=2, displacement=-7320),
            '80239a70': dict(mnemonic='lfd', fD=1, rA=2, displacement=-7312),
            '80239c10': dict(mnemonic='blr'),
        }
        for pc, operands in expected.items(): self.assertEqual(self.by_pc[pc], operands, pc)
        for pc in ('80239a4c', '80239a54', '80239a6c', '80239a74'):
            self.assertEqual(self.by_pc[pc], dict(mnemonic='b', target='80239c00', AA=0))

    def test_constants_table_and_derived_axis_products(self):
        result = self.results[0]
        values = {int(x['address'], 16): x for x in result['constants']}
        for pc, n, bits in a.TARGETS:
            self.assertEqual(values[pc]['bits'], bits)
            self.assertEqual(values[pc]['width'], n)
        self.assertEqual([x['value'] for x in result['direction_table']['entries']], list(a.TABLE_VALUES))
        f32 = lambda x: struct.unpack('>f', struct.pack('>f', x))[0]
        multiplier = values[0x8043707c]['value']
        for pc, expected_float, expected_s16, expected_index, expected_direction in (
                (0x8043cd78, 32768.0, 32767, 4, 1), (0x8043cd80, -32768.0, -32768, 4, 1),
                (0x8043cd88, -16384.0, -16384, 6, 4), (0x8043cd90, 16384.0, 16384, 2, 8)):
            # Derived host arithmetic check, not an archived-instruction execution oracle.
            product = f32(f32(values[pc]['value']) * multiplier)
            self.assertEqual(product, expected_float)
            converted = max(-32768, min(32767, int(product)))
            self.assertEqual(converted, expected_s16)
            index = (((converted & 65535) + 4096) >> 13) & 7
            self.assertEqual(index, expected_index); self.assertEqual(a.TABLE_VALUES[index], expected_direction)
        for zero in (0.0, -0.0):
            product = f32(f32(zero) * multiplier)
            self.assertEqual(struct.pack('>f', product), struct.pack('>f', zero))
            self.assertEqual(int(product), 0)

    def test_each_selected_text_bit_mutation_fails_before_decode(self):
        checked = 0
        for pc, n, raw in self.fixed_text:
            for offset in range(n):
                for bit in range(8):
                    changed = bytearray(raw); changed[offset] ^= 1 << bit
                    with patch.object(a, 'decode_selected') as decode:
                        with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                            a.range_evidence(FakeDB(changed), 21, pc, n)
                        decode.assert_not_called()
                    checked += 1
        self.assertEqual(checked, 2912)

    def test_each_selected_data_bit_mutation_fails(self):
        checked = 0
        for pc, n, bits in a.TARGETS:
            raw = bytes.fromhex(bits)
            for offset in range(n):
                for bit in range(8):
                    changed = bytearray(raw); changed[offset] ^= 1 << bit
                    with self.assertRaisesRegex(a.c.FormatError, 'bits mismatch'):
                        a.constant_evidence(FakeDB(changed), a.DATA5_MAPPING, pc, n)
                    checked += 1
        for offset in range(8):
            for bit in range(8):
                changed = bytearray(a.TABLE_VALUES); changed[offset] ^= 1 << bit
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                    a.table_evidence(FakeDB(changed), a.DATA4_MAPPING)
                checked += 1
        self.assertEqual(checked, 352)


if __name__ == '__main__':
    unittest.main()
