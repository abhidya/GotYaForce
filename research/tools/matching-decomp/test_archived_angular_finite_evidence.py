#!/usr/bin/env python3
"""Finite angular evidence authentication and decoder controls, not execution."""
import contextlib
import copy
import hashlib
import io
import json
import os
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_angular_finite_evidence as a
from test_archived_actor_attribute_evidence import FakeDB


def a_form(form, d=1, aa=2, b=3, fc=4, record=0):
    return (63 << 26) | (d << 21) | (aa << 16) | (b << 11) | (fc << 6) | (form << 1) | record


class SyntheticTests(unittest.TestCase):
    def test_fixed_scope_and_separate_allowlist(self):
        self.assertEqual([(pc, n) for pc, n, _ in a.RANGES], [(0x80239a78, 392), (0x8023c240, 536)])
        self.assertEqual(sum(n for _, n, _ in a.RANGES), 928)
        self.assertEqual(len(a.TARGETS)*8 + a.TABLE_WIDTH, 200)
        self.assertEqual(a.TABLE_ADDRESS + a.TABLE_WIDTH, 0x802b5200)
        self.assertEqual(len(a.TABLE_BITS), 19)
        self.assertTrue(set(pc for pc, _, _ in a.TARGETS).isdisjoint(pc for pc, _ in a.c.TARGETS))
        self.assertTrue(set(pc for pc, _, _ in a.TARGETS).isdisjoint(pc for pc, _, _ in a.axis.TARGETS))

    def test_double_fused_forms_and_operands(self):
        for form, name in ((28, 'fmsub'), (29, 'fmadd'), (30, 'fnmsub')):
            self.assertEqual(a.decode_selected(a_form(form), 0x8023c338),
                             dict(mnemonic=name, fD=1, fA=2, fC=4, fB=3))
            with self.assertRaisesRegex(a.c.FormatError, 'record bit'):
                a.decode_selected(a_form(form, record=1), 0x8023c338)
        self.assertIsNone(a.decode_selected(a_form(31), 0x8023c338))

    def test_double_binary_and_multiply_forms(self):
        for form, name in ((18, 'fdiv'), (20, 'fsub'), (21, 'fadd')):
            self.assertEqual(a.decode_selected(a_form(form, fc=0), 0x8023c338),
                             dict(mnemonic=name, fD=1, fA=2, fB=3))
            with self.assertRaisesRegex(a.c.FormatError, 'binary fields'):
                a.decode_selected(a_form(form), 0x8023c338)
        self.assertEqual(a.decode_selected(a_form(25, b=0), 0x8023c338),
                         dict(mnemonic='fmul', fD=1, fA=2, fC=4))
        with self.assertRaisesRegex(a.c.FormatError, 'multiply fields'):
            a.decode_selected(a_form(25), 0x8023c338)
        for form in (18, 20, 21, 25):
            with self.assertRaisesRegex(a.c.FormatError, 'record bit'):
                a.decode_selected(a_form(form, b=0, fc=0, record=1), 0x8023c338)

    def test_unary_compare_and_indexed_load(self):
        for xo, name in ((40, 'fneg'), (264, 'fabs')):
            word = (63 << 26) | (1 << 21) | (3 << 11) | (xo << 1)
            self.assertEqual(a.decode_selected(word, 0x8023c240), dict(mnemonic=name, fD=1, fB=3))
            for bad in (word | 1, word | (1 << 16)):
                with self.assertRaisesRegex(a.c.FormatError, 'unary float fields'):
                    a.decode_selected(bad, 0x8023c240)
        compare = (63 << 26) | (2 << 16) | (32 << 1)
        self.assertEqual(a.decode_selected(compare, 0x8023c2f4), dict(mnemonic='fcmpo', crD=0, fA=2, fB=0))
        for bad in (compare | 1, compare | (1 << 21)):
            with self.assertRaisesRegex(a.c.FormatError, 'fcmpo fields'): a.decode_selected(bad, 0x8023c2f4)
        load = (31 << 26) | (2 << 21) | (3 << 16) | (599 << 1)
        self.assertEqual(a.decode_selected(load, 0x8023c438), dict(mnemonic='lfdx', fD=2, rA=3, rB=0))
        with self.assertRaisesRegex(a.c.FormatError, 'lfdx record bit'): a.decode_selected(load | 1, 0x8023c438)

    def test_type_bounds_and_unknown_forms(self):
        for word in (-1, 1 << 32, True, False, 1.0, '0', None):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'): a.decode_selected(word, 0x8023c240)
        for pc in (-1, 1, 1 << 32, True, False, 1.0, '0', None):
            with self.assertRaisesRegex(a.c.FormatError, 'PC bounds'): a.decode_selected(0, pc)
        for word in (0, 0x4e800021, 0x4e800421, 34 << 26, 52 << 26):
            self.assertIsNone(a.decode_selected(word, 0x8023c240))

    def test_range_refusals_precede_read_and_decode(self):
        pc, n, _ = a.RANGES[0]
        for args in ((21, pc+4, n-4), (21, pc, n-4), (21, pc, n+4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.range_evidence(None, *args)
        for args in ((21.0, pc, n), (21, True, n), (21, pc, float(n))):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'): a.range_evidence(None, *args)
        with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'): a.range_evidence(None, 22, pc, n)
        with patch.object(a, 'RANGES', a.RANGES*2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.range_evidence(None, 21, pc, n)
        for raw, reason in ((bytes(n-1), 'byte width'), (bytes(n), 'digest mismatch')):
            with patch.object(a, 'decode_selected') as decode:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.range_evidence(FakeDB(raw), 21, pc, n)
                decode.assert_not_called()
        raw = bytes(4)
        with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(raw), 21, pc, 4)

    def test_data_guards_precede_reads(self):
        pc, n, _ = a.TARGETS[0]
        for addr, width in ((pc+4, n), (pc, n+4), (True, n), (pc, 8.0)):
            with self.assertRaises(a.c.FormatError): a.constant_evidence(None, a.axis.DATA5_MAPPING, addr, width)
        with self.assertRaisesRegex(a.c.FormatError, 'data5 mapping'):
            a.constant_evidence(None, a.DATA2_MAPPING, pc, n)
        for mapping in (a.axis.DATA5_MAPPING, a.DATA2_MAPPING):
            for index in (0, 1, 2, 4, 5, 6):
                malformed = list(mapping); malformed[index] = float(malformed[index])
                with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                    if mapping == a.axis.DATA5_MAPPING:
                        a.constant_evidence(None, tuple(malformed), pc, n)
                    else:
                        a.table_evidence(None, tuple(malformed))
                malformed[index] = True
                with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                    if mapping == a.axis.DATA5_MAPPING:
                        a.constant_evidence(None, tuple(malformed), pc, n)
                    else:
                        a.table_evidence(None, tuple(malformed))
        for raw, reason in ((bytes(n-1), 'byte width'), (bytes(n), 'bits mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.constant_evidence(FakeDB(raw), a.axis.DATA5_MAPPING, pc, n)
        for raw, reason in ((bytes(151), 'byte width'), (bytes(152), 'digest mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, reason): a.table_evidence(FakeDB(raw), a.DATA2_MAPPING)
        with self.assertRaisesRegex(a.c.FormatError, 'data2 mapping'): a.table_evidence(None, a.axis.DATA5_MAPPING)
        with patch.object(a, 'TABLE_SHA256', hashlib.sha256(bytes(152)).hexdigest()):
            with self.assertRaisesRegex(a.c.FormatError, 'values mismatch'):
                a.table_evidence(FakeDB(bytes(152)), a.DATA2_MAPPING)

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
            1: ['MAIN_.text1', None, None, 0, 0x20000000000055e0, a.axis.wait.TEXT_LENGTH, 0],
            4: ['MAIN_.data2', None, None, 0, 0x20000000002b01a0, 44224, 0],
            6: ['MAIN_.data4', None, None, 0, 0x20000000004335a0, 11040, 0],
            7: ['MAIN_.data5', None, None, 0, 0x2000000000436a20, 27360, 0],
        }
        subs = {1: [1, 2, a.axis.wait.TEXT_LENGTH, 0, 21, 0], 4: [4, 2, 44224, 0, 195, 0],
                6: [6, 2, 11040, 0, 262, 0], 7: [7, 2, 27360, 0, 263, 0]}
        a.mappings(blocks, subs, 0x80000000)
        cases = []
        for index in (1, 2, 3, 4, 5):
            bb, ss = copy.deepcopy((blocks, subs)); ss[4][index] += 1; cases.append((bb, ss, '80000000'))
        for index in (4, 5, 6):
            bb, ss = copy.deepcopy((blocks, subs)); bb[4][index] += 1; cases.append((bb, ss, '80000000'))
        bb = copy.deepcopy(blocks); bb[99] = bb[4].copy(); cases.append((bb, subs, '80000000'))
        ss = copy.deepcopy(subs); ss[99] = ss[4].copy(); cases.append((blocks, ss, '80000000'))
        cases.append((blocks, subs, '80000004'))
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as text, patch.object(a, 'constant_evidence') as const, \
                    patch.object(a, 'table_evidence') as table:
                parser.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                parser.return_value.rows.side_effect = [bb, ss]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                text.assert_not_called(); const.assert_not_called(); table.assert_not_called()

    def test_cli_rejects_arbitrary_reads_and_execution(self):
        for option in (['--address', '8023c240'], ['--width', '536'], ['--raw'], ['--execute']):
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
        cls.results, cls.fixed_text, cls.fixed_constants = [], [], []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
            if not cls.fixed_text:
                # Same fixed authenticated spans, retained only for corruption tests.
                db = a.c.GBF(data)
                cls.fixed_text = [(pc, n, db.chain(21, pc-a.axis.wait.TEXT_START, n, a.axis.wait.TEXT_LENGTH)[0])
                                  for pc, n, _ in a.RANGES]
                cls.fixed_constants = [(pc, n, db.chain(263, pc-0x80436a20, n, 27360)[0])
                                       for pc, n, _ in a.TARGETS]
                cls.fixed_table = db.chain(195, a.TABLE_ADDRESS-0x802b01a0, a.TABLE_WIDTH, 44224)[0]
        cls.by_pc = {item['address']: {k: v for k, v in item.items() if k != 'address'}
                     for span in cls.results[0]['ranges'] for item in span['instructions']}

    def test_cross_snapshot_identity_and_complete_coverage(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        for key in ('ranges', 'constants', 'atan_table', 'function_coverage'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            for span, (pc, n, digest) in zip(result['ranges'], a.RANGES):
                self.assertEqual(span['sha256'], digest)
                self.assertEqual([x['address'] for x in span['instructions']], [f'{x:08x}' for x in range(pc, pc+n, 4)])
                self.assertEqual(sum(x['length'] for x in span['spans']), n)
                for item in [span] + span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes')))
            self.assertEqual(sum(x['represented_instructions'] for x in result['function_coverage']), 232)
            self.assertEqual(result['function_coverage'][0]['combined_unrepresented_ranges'], [])
            json.dumps(result, allow_nan=False)

    def test_atan2_ratio_and_quadrant_order(self):
        expected = {
            '80239b44': dict(mnemonic='subf', rD=0, rA=6, rB=7, Rc=0),
            '80239b48': dict(mnemonic='srawi', rS=0, rA=0, SH=20, Rc=0),
            '80239b4c': dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=60),
            '80239b68': dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=-60),
            '80239b84': dict(mnemonic='fdiv', fD=0, fA=1, fB=0),
            '80239b88': dict(mnemonic='fabs', fD=1, fB=0),
            '80239b8c': dict(mnemonic='bl', target='8023c240', AA=0),
            '80239bc4': dict(mnemonic='xoris', rS=0, rA=0, immediate=32768),
            '80239bd8': dict(mnemonic='lfd', fD=0, rA=2, displacement=-7256),
            '80239bdc': dict(mnemonic='lfd', fD=2, rA=2, displacement=-7336),
            '80239be0': dict(mnemonic='fsub', fD=0, fA=1, fB=0),
            '80239be4': dict(mnemonic='fsub', fD=1, fA=2, fB=0),
            '80239bf0': dict(mnemonic='lfd', fD=1, rA=2, displacement=-7256),
            '80239bf4': dict(mnemonic='lfd', fD=0, rA=2, displacement=-7336),
            '80239bf8': dict(mnemonic='fsub', fD=1, fA=2, fB=1),
            '80239bfc': dict(mnemonic='fsub', fD=1, fA=1, fB=0),
        }
        for pc, value in expected.items(): self.assertEqual(self.by_pc[pc], value)

    def test_atan_reduction_branches_and_small_zero_path(self):
        expected = {
            '8023c250': dict(mnemonic='addi', rD=5, rA=3, immediate=20840),
            '8023c248': dict(mnemonic='addis', rD=0, rA=0, immediate=17424),
            '8023c2d0': dict(mnemonic='addis', rD=0, rA=0, immediate=16348),
            '8023c2dc': dict(mnemonic='addis', rD=0, rA=0, immediate=15904),
            '8023c2e8': dict(mnemonic='lfd', fD=2, rA=2, displacement=-6392),
            '8023c2ec': dict(mnemonic='lfd', fD=0, rA=2, displacement=-6384),
            '8023c2f0': dict(mnemonic='fadd', fD=2, fA=2, fB=1),
            '8023c2f4': dict(mnemonic='fcmpo', crD=0, fA=2, fB=0),
            '8023c30c': dict(mnemonic='addis', rD=0, rA=0, immediate=16371),
            '8023c31c': dict(mnemonic='addis', rD=0, rA=0, immediate=16358),
            '8023c334': dict(mnemonic='fadd', fD=0, fA=2, fB=3),
            '8023c338': dict(mnemonic='fmsub', fD=1, fA=2, fC=3, fB=1),
            '8023c350': dict(mnemonic='fsub', fD=1, fA=3, fB=0),
            '8023c354': dict(mnemonic='fadd', fD=0, fA=0, fB=3),
            '8023c380': dict(mnemonic='fsub', fD=1, fA=3, fB=2),
            '8023c384': dict(mnemonic='fmadd', fD=0, fA=2, fC=3, fB=0),
            '8023c39c': dict(mnemonic='fdiv', fD=0, fA=0, fB=3),
        }
        for pc, value in expected.items(): self.assertEqual(self.by_pc[pc], value)

    def test_polynomial_fused_order_and_reconstruction(self):
        expected = [
            ('8023c3b4', 'fmul', 11, 9, 9, None), ('8023c3c8', 'fmul', 10, 11, 11, None),
            ('8023c3d8', 'fmadd', 8, 10, 4, 1), ('8023c3e4', 'fmadd', 3, 10, 3, 0),
            ('8023c3ec', 'fmadd', 7, 10, 8, 7), ('8023c3f0', 'fmadd', 2, 10, 3, 2),
            ('8023c3f4', 'fmadd', 3, 10, 7, 6), ('8023c3f8', 'fmadd', 1, 10, 2, 1),
            ('8023c3fc', 'fmadd', 2, 10, 3, 5), ('8023c400', 'fmadd', 0, 10, 1, 0),
            ('8023c404', 'fmadd', 1, 10, 2, 4), ('8023c408', 'fmul', 2, 10, 0, None),
            ('8023c40c', 'fmul', 0, 11, 1, None), ('8023c418', 'fnmsub', 1, 9, 0, 9),
            ('8023c43c', 'fmsub', 0, 9, 1, 0),
        ]
        for pc, name, d, aa, fc, b in expected:
            item = dict(mnemonic=name, fD=d, fA=aa, fC=fc)
            if b is not None: item['fB'] = b
            self.assertEqual(self.by_pc[pc], item)
        self.assertEqual(self.by_pc['8023c42c'], dict(mnemonic='lfdx', fD=0, rA=3, rB=0))
        self.assertEqual(self.by_pc['8023c438'], dict(mnemonic='lfdx', fD=2, rA=3, rB=0))
        self.assertEqual(self.by_pc['8023c440'], dict(mnemonic='fsub', fD=0, fA=0, fB=9))
        self.assertEqual(self.by_pc['8023c444'], dict(mnemonic='fsub', fD=1, fA=2, fB=0))
        self.assertEqual(self.by_pc['8023c44c'], dict(mnemonic='fneg', fD=1, fB=1))

    def test_constants_and_table_exact_bits(self):
        result = self.results[0]
        self.assertEqual([(int(x['address'], 16), x['width'], x['bits']) for x in result['constants']], list(a.TARGETS))
        table = result['atan_table']
        self.assertEqual([entry['bits'] for entry in table['entries']], list(a.TABLE_BITS))
        self.assertEqual(table['block_name'], 'MAIN_.data2')
        self.assertEqual(table['chain_root'], 195)
        self.assertEqual([x['address'] for x in table['entries']], [f'{x:08x}' for x in range(0x802b5168, 0x802b5200, 8)])
        self.assertEqual(sum(x['length'] for x in table['spans']), 152)

    def test_every_selected_text_bit_mutation_rejected_before_decode(self):
        with patch.object(a, 'decode_selected') as decode:
            for pc, n, raw in self.fixed_text:
                for bit in range(n*8):
                    mutated = bytearray(raw); mutated[bit//8] ^= 1 << (bit%8)
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(mutated), 21, pc, n)
            decode.assert_not_called()

    def test_every_selected_data_bit_mutation_rejected(self):
        for pc, n, raw in self.fixed_constants:
            for bit in range(n*8):
                mutated = bytearray(raw); mutated[bit//8] ^= 1 << (bit%8)
                with self.assertRaisesRegex(a.c.FormatError, 'bits mismatch'):
                    a.constant_evidence(FakeDB(mutated), a.axis.DATA5_MAPPING, pc, n)
        for bit in range(a.TABLE_WIDTH*8):
            mutated = bytearray(self.fixed_table); mutated[bit//8] ^= 1 << (bit%8)
            with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                a.table_evidence(FakeDB(mutated), a.DATA2_MAPPING)


if __name__ == '__main__':
    unittest.main()
