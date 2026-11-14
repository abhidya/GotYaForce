#!/usr/bin/env python3
"""Fifth descriptor, exact caller operands, authentication and refusal tests."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_fifth_input_machine_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form
from test_archived_input_machine_evidence import ops


class SyntheticTests(unittest.TestCase):
    def test_extents_and_types(self):
        self.assertEqual([(pc, n) for pc, n, _ in a.RANGES], [(0x80068644, 48)])
        self.assertEqual([(pc, n) for pc, n, _ in a.DATA_RANGES], [(0x802d3928, 12)])
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)

    def test_only_selected_caller_instruction_forms(self):
        for word in (0, 0x4e800020, 0x4e800421, 0x48000000, 0x48000003,
                     d_form(32, 3, 4, 0), d_form(36, 3, 4, 0),
                     (31 << 26) | (444 << 1) | 1, (31 << 26) | (28 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        self.assertEqual(a.decode_selected(d_form(14, 5, 31, 0x600), 0),
                         dict(mnemonic='addi', rD=5, rA=31, immediate=0x600))
        self.assertEqual(a.decode_selected(d_form(15, 4, 0, -32723), 0),
                         dict(mnemonic='addis', rD=4, rA=0, immediate=-32723))
        self.assertEqual(a.decode_selected((31 << 26) | (31 << 21) | (3 << 16) |
                                          (31 << 11) | (444 << 1), 0),
                         dict(mnemonic='or', rS=31, rA=3, rB=31, Rc=0))
        self.assertEqual(a.decode_selected(0x48000005, 0),
                         dict(mnemonic='bl', target='00000004', AA=0))

    def test_fixed_instruction_reads_fail_before_decode(self):
        pc, size, _ = a.RANGES[0]
        for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                               (0x800685c0, 0x130), (0x80068674, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, address, width)
        for fields in ((21.0, pc, size), (21, True, size), (21, pc, float(size))):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'): a.range_evidence(None, *fields)
        with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
            a.range_evidence(None, 22, pc, size)
        for raw, reason in ((bytes(size), 'digest'), (bytes(size - 4), 'byte width')):
            with patch.object(a, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.range_evidence(FakeDB(raw), 21, pc, size)
                decoder.assert_not_called()
        with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(bytes(4)).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(bytes(4)), 21, pc, 4)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.range_evidence(None, 21, pc, size)

    def test_fixed_descriptor_reads_fail_closed(self):
        pc, size, _ = a.DATA_RANGES[0]
        for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                               (0x802d38f8, 12), (0x802d3904, 12), (0x802d3910, 12),
                               (0x802d391c, 12), (0x802d3934, 12), (0x802d3988, 12)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.data_evidence(None, a.DATA3_MAPPING, address, width)
        for address, width in ((float(pc), size), (pc, True), (pc, float(size))):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.data_evidence(None, a.DATA3_MAPPING, address, width)
        for index in (0, 1, 2, 4, 5, 6):
            mapping = list(a.DATA3_MAPPING); mapping[index] += 4
            with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                a.data_evidence(None, tuple(mapping), pc, size)
            mapping = list(a.DATA3_MAPPING); mapping[index] = float(mapping[index])
            with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                a.data_evidence(None, tuple(mapping), pc, size)
        with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
            a.data_evidence(None, list(a.DATA3_MAPPING), pc, size)
        for raw, reason in ((bytes(size), 'digest'), (bytes(size - 1), 'byte width')):
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.data_evidence(FakeDB(raw), a.DATA3_MAPPING, pc, size)
        with patch.object(a, 'DATA_RANGES', a.DATA_RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.data_evidence(None, a.DATA3_MAPPING, pc, size)

    def test_independent_descriptor_value_checks(self):
        pc, size, _ = a.DATA_RANGES[0]
        for index in range(6):
            values = [1, 0, 0, 16, 0x100, 0]; values[index] ^= 1
            raw = struct.pack('>6H', *values)
            with patch.object(a, 'DATA_RANGES', ((pc, size, hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, 'descriptor values'):
                    a.data_evidence(FakeDB(raw), a.DATA3_MAPPING, pc, size)

    def test_authentication_precedes_parsing(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as reader, \
                    patch.object(a, 'data_evidence') as data_reader:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); reader.assert_not_called(); data_reader.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty', 'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_mapping_guards_precede_fixed_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image', 'data5', 'data3root', 'data3offset', 'data3length'):
            aa, bb, ss = copy.deepcopy((auth, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'data5': ss[7][4] += 1
            if target == 'data3root': ss[5][4] += 1
            if target == 'data3offset': ss[5][5] += 4
            if target == 'data3length': bb[5][5] -= 4
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'data_evidence') as data_reader:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called(); data_reader.assert_not_called()

    def test_no_arbitrary_cli(self):
        for option in (['--address', '802d3928'], ['--width', '12'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2); inspect.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('local archives unavailable')
        cls.results, cls.databases = [], []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
            cls.databases.append(a.c.GBF(data))

    def test_full_selected_coverage_both_archives(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['data_ranges'], self.results[1]['data_ranges'])
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(result['selected_coverage'], dict(address='80068644', end_exclusive='80068674',
                             selected_width=48, represented_instructions=12, unrepresented_instructions=0,
                             unrepresented_ranges=[]))
            self.assertEqual(len(result['ranges']), 1)
            self.assertEqual(len(result['data_ranges']), 1)
            def no_raw(value):
                if isinstance(value, dict):
                    self.assertTrue(set(value).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))
                    for child in value.values(): no_raw(child)
                elif isinstance(value, list):
                    for child in value: no_raw(child)
            no_raw(result)

    def test_descriptor_and_physical_spans(self):
        descriptor = self.results[0]['data_ranges'][0]
        self.assertEqual(descriptor['end_exclusive'], '802d3934')
        self.assertEqual(descriptor['fields'], [dict(offset=i * 2, width=2, type='u16', value=value)
                                                for i, value in enumerate((1, 0, 0, 16, 0x100, 0))])
        self.assertEqual(descriptor['spans'], [dict(root_buffer=199, data_buffer=206, chain_offset=101064,
                             data_offset=2796, length=12, obfuscated=True, physical_offset=3394290)])
        self.assertEqual(descriptor['block_name'], 'MAIN_.data3')
        self.assertEqual(descriptor['chain_root'], 199)
        span = self.results[0]['ranges'][0]
        self.assertEqual(span['end_exclusive'], '80068674')
        self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=46, chain_offset=405604,
                             data_offset=12532, length=48, obfuscated=True, physical_offset=782586)])

    def test_every_caller_operand_and_return_discard_in_order(self):
        expected = ops('''
            addis 4 0 -32723
            or 31 3 31 0
            addi 4 4 0x3928
            addi 5 31 0x600
            addi 6 0 0x1
            bl 80068b8c
            addis 4 0 -32723
            or 31 3 31 0
            addi 4 4 0x3934
            addi 5 31 0x604
            addi 6 0 0x2
            bl 80068b8c
        ''')
        self.assertEqual(len(expected), 12)
        actual = self.results[0]['ranges'][0]['instructions']
        self.assertEqual(actual, [dict(address=f'{0x80068644 + i * 4:08x}', **op)
                                  for i, op in enumerate(expected)])
        # Explicitly no caller return-dependent store, branch, or load exists
        # between fifth and sixth calls. The source return in r3 is discarded.
        self.assertEqual([x['mnemonic'] for x in actual[6:]], ['addis', 'or', 'addi', 'addi', 'addi', 'bl'])
        self.assertEqual(actual[7], dict(address='80068660', mnemonic='or', rS=31, rA=3, rB=31, Rc=0))

    def test_caller_bounds_descriptor_and_keeps_masks_distinct(self):
        for result in self.results:
            instructions = result['ranges'][0]['instructions']
            descriptor = result['data_ranges'][0]
            fifth_address = ((instructions[0]['immediate'] << 16) +
                             instructions[2]['immediate']) & 0xffffffff
            sixth_address = ((instructions[6]['immediate'] << 16) +
                             instructions[8]['immediate']) & 0xffffffff
            self.assertEqual(fifth_address, int(descriptor['address'], 16))
            self.assertEqual(sixth_address, int(descriptor['end_exclusive'], 16))
            self.assertEqual(sixth_address - fifth_address, descriptor['width'])
            self.assertEqual(instructions[3]['immediate'], 0x600)
            self.assertEqual(instructions[9]['immediate'], 0x604)
            self.assertEqual(instructions[4]['immediate'], 1)
            self.assertEqual(instructions[10]['immediate'], 2)
            self.assertEqual(descriptor['fields'][3]['value'], 16)
            self.assertEqual(descriptor['fields'][4]['value'], 0x100)

    def test_each_instruction_and_descriptor_byte_mutation_rejected(self):
        db = self.databases[0]
        for pc, width, _ in a.RANGES:
            raw = db.chain(21, pc - a.TEXT_START, width, a.TEXT_LENGTH)[0]
            for offset in range(width):
                changed = bytearray(raw); changed[offset] ^= 1
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(changed), 21, pc, width)
                    decoder.assert_not_called()
        for pc, width, _ in a.DATA_RANGES:
            raw = db.chain(199, pc - a.DATA3_MAPPING[0], width, a.DATA3_MAPPING[5])[0]
            for offset in range(width):
                changed = bytearray(raw); changed[offset] ^= 1
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                    a.data_evidence(FakeDB(changed), a.DATA3_MAPPING, pc, width)


if __name__ == '__main__': unittest.main()
