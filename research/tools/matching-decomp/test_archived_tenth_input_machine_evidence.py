#!/usr/bin/env python3
"""Tenth descriptor, exact caller operands, authentication and refusal tests."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_tenth_input_machine_evidence as a
import read_archived_ninth_input_machine_evidence as ninth
from test_archived_actor_attribute_evidence import FakeDB, d_form
from test_archived_input_machine_evidence import ops


class SyntheticTests(unittest.TestCase):
    def test_extents_and_types(self):
        self.assertEqual(a.RANGES, ((0x800686bc, 32,
                         'b3f8753f8e804506c11f8526c07fb9342f3d6c73d027d09f97eb1bc1c5926910'),
                         (0x8006873c, 16,
                         '799ae73e3ca0635845461e1a27808be23d7c0c6a9315d364e90cc69e00d5ea88')))
        self.assertEqual(a.DATA_RANGES, ((0x802d3964, 12,
                         '41b4ea8d72d6fe7021bbd9244afb1994333dd286eb483a0b60a573bfafb2cc26'),))
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)

    def test_only_selected_caller_instruction_forms(self):
        for word in (0, 0x4e800020, 0x4e800421, 0x48000000, 0x48000003,
                     d_form(32, 3, 4, 0), d_form(36, 3, 4, 0),
                     (31 << 26) | (444 << 1) | 1, (31 << 26) | (28 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        self.assertEqual(a.decode_selected(d_form(14, 5, 31, 0x628), 0),
                         dict(mnemonic='addi', rD=5, rA=31, immediate=0x628))
        self.assertEqual(a.decode_selected(d_form(15, 4, 0, -32723), 0),
                         dict(mnemonic='addis', rD=4, rA=0, immediate=-32723))
        self.assertEqual(a.decode_selected((31 << 26) | (31 << 21) | (3 << 16) |
                                          (31 << 11) | (444 << 1), 0),
                         dict(mnemonic='or', rS=31, rA=3, rB=31, Rc=0))
        self.assertEqual(a.decode_selected(0x48000005, 0),
                         dict(mnemonic='bl', target='00000004', AA=0))

    def test_selected_boundary_store_form(self):
        self.assertEqual(a.decode_selected(d_form(38, 29, 25, 0x655), 0),
                         dict(mnemonic='stb', rS=29, rA=25, displacement=0x655))

    def test_fixed_instruction_reads_fail_before_decode(self):
        for pc, size, _ in a.RANGES:
            for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                                   (0x800685c0, 0x130), (0x800686d4, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, 21, address, width)
            for fields in ((21.0, pc, size), (21, True, size), (21, pc, float(size))):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'): a.range_evidence(None, *fields)
            with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
                a.range_evidence(None, 22, pc, size)
            for raw, reason in ((bytes(size), 'digest'), (bytes(size - 4), 'byte width'),
                                (bytes(size + 4), 'byte width')):
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
                               (0x802d391c, 12), (0x802d3928, 12), (0x802d3934, 12),
                               (0x802d3940, 12), (0x802d394c, 12),
                               (0x802d3958, 12), (0x802d3970, 12), (0x802d3988, 12)):
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
        for raw, reason in ((bytes(size), 'digest'), (bytes(size - 1), 'byte width'),
                            (bytes(size + 2), 'byte width')):
            with patch.object(a.c, 'integer') as interpreter:
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.data_evidence(FakeDB(raw), a.DATA3_MAPPING, pc, size)
                interpreter.assert_not_called()
        with patch.object(a, 'DATA_RANGES', a.DATA_RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.data_evidence(None, a.DATA3_MAPPING, pc, size)

    def test_independent_descriptor_value_checks(self):
        pc, size, _ = a.DATA_RANGES[0]
        variants = []
        for index in range(6):
            values = [1, 0x10, 0, 1, 0x0f, 0]; values[index] ^= 1
            variants.append(values)
        # Every field is independently checked, including phase-2 any-bit flags.
        variants.extend(([1, 0, 0, 1, 0x0f, 0], [1, 4, 0, 1, 0x0f, 0],
                         [1, 0x10, 0, 16, 0x0f, 0], [1, 0x10, 0, 1, 0x10, 0],
                         [1, 0x10, 0, 1, 0x2000, 0], [1, 0x10, 0, 1, 0x40, 0],
                         [1, 0x10, 0, 1, 0x20, 0], [1, 0x10, 0, 1, 0x100, 0]))
        for values in variants:
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

    def test_full_authenticator_rejects_synthetic_schema_before_reads(self):
        data = b'synthetic schema fixture'
        digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for field, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[field] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'data_evidence') as descriptors:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'):
                    a.inspect(data, digest)
                parser.return_value.rows.assert_not_called()
                ranges.assert_not_called(); descriptors.assert_not_called()

    def test_shared_allowlists_do_not_admit_new_spans(self):
        for address, width, _ in a.RANGES:
            self.assertNotIn((address, width), a.c.TARGETS)
            self.assertNotIn((address, width), [row[:2] for row in a.command.RANGES])
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.command.read_range(None, address, width, 0x80000000)
            for reader in (a.machine, ninth):
                self.assertNotIn((address, width), [row[:2] for row in reader.RANGES])
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    reader.range_evidence(None, 21, address, width)
        for address, width, _ in a.DATA_RANGES:
            self.assertNotIn((address, width), a.c.TARGETS)
            self.assertNotIn((address, width), [row[:2] for row in a.command.RANGES])
            for reader in (a.machine, ninth):
                self.assertNotIn((address, width), [row[:2] for row in reader.DATA_RANGES])
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    reader.data_evidence(None, a.DATA3_MAPPING, address, width)

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
        for option in (['--address', '802d3964'], ['--width', '12'], ['--raw'], ['--execute']):
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

    def test_full_selected_coverage_both_archives_and_no_raw_output(self):
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['data_ranges'], self.results[1]['data_ranges'])
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(result['selected_coverage'], dict(address='800686bc', end_exclusive='800686dc',
                             selected_width=32, represented_instructions=8, unrepresented_instructions=0,
                             unrepresented_ranges=[]))
            self.assertEqual(result['boundary_coverage'], dict(address='8006873c', end_exclusive='8006874c',
                             selected_width=16, represented_instructions=4, unrepresented_instructions=0,
                             unrepresented_ranges=[]))
            self.assertEqual(len(result['ranges']), 2)
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
        self.assertEqual(descriptor['end_exclusive'], '802d3970')
        self.assertEqual(descriptor['fields'], [dict(offset=i * 2, width=2, type='u16', value=value)
                                               for i, value in enumerate((1, 0x10, 0, 1, 0x0f, 0))])
        self.assertEqual(descriptor['spans'], [dict(root_buffer=199, data_buffer=206, chain_offset=101124,
                             data_offset=2856, length=12, obfuscated=True, physical_offset=3394350)])
        self.assertEqual(descriptor['block_name'], 'MAIN_.data3')
        self.assertEqual(descriptor['chain_root'], 199)
        self.assertEqual(self.results[0]['ranges'][0]['spans'],
                         [dict(root_buffer=21, data_buffer=46, chain_offset=405724,
                               data_offset=12652, length=32, obfuscated=True, physical_offset=782706)])
        self.assertEqual(self.results[0]['ranges'][1]['spans'],
                         [dict(root_buffer=21, data_buffer=46, chain_offset=405852,
                               data_offset=12780, length=16, obfuscated=True, physical_offset=782834)])

    def test_every_caller_operand_and_return_discard_in_order(self):
        expected = ops('''
            addis 4 0 -32723
            or 31 3 31 0
            addi 4 4 0x3964
            addi 5 31 0x628
            addi 6 0 0x2000
            bl 80068b8c
            or 31 3 31 0
            bl 800686f0
        ''')
        self.assertEqual(len(expected), 8)
        for result in self.results:
            actual = result['ranges'][0]['instructions']
            self.assertEqual(actual, [dict(address=f'{0x800686bc + i * 4:08x}', **op)
                                      for i, op in enumerate(expected)])
            # No return-dependent caller branch, store, load or compare exists.
            self.assertEqual([x['mnemonic'] for x in actual[6:]], ['or', 'bl'])
            self.assertEqual(actual[6], dict(address='800686d4', mnemonic='or', rS=31, rA=3, rB=31, Rc=0))
            self.assertEqual(actual[7], dict(address='800686d8', mnemonic='bl', target='800686f0', AA=0))

    def test_independent_charge_table_address_bounds_descriptor(self):
        # The bound is not an inferred continuation of the preceding descriptor stride.
        expected = ops('''
            addis 4 0 -32723
            addis 3 0 -32723
            stb 29 25 0x655
            addi 30 4 0x3970
        ''')
        for result in self.results:
            caller = result['ranges'][0]['instructions']
            boundary = result['ranges'][1]['instructions']
            descriptor = result['data_ranges'][0]
            self.assertEqual(boundary, [dict(address=f'{0x8006873c + i * 4:08x}', **op)
                                        for i, op in enumerate(expected)])
            descriptor_address = ((caller[0]['immediate'] << 16) + caller[2]['immediate']) & 0xffffffff
            table_address = ((boundary[0]['immediate'] << 16) + boundary[3]['immediate']) & 0xffffffff
            self.assertEqual(descriptor_address, 0x802d3964)
            self.assertEqual(table_address, 0x802d3970)
            self.assertEqual(table_address - descriptor_address, descriptor['width'])
            self.assertEqual(table_address, int(descriptor['end_exclusive'], 16))
            self.assertEqual(result['descriptor_bound'], dict(address='802d3964', end_exclusive='802d3970',
                             width=12, next_object='charge input-mask table', high_instruction='8006873c',
                             low_instruction='80068748', table_bytes_read=False))
            self.assertEqual([row['address'] for row in result['data_ranges']], ['802d3964'])
            for address, width in ((0x802d3970, 12), (0x802d3964, 16), (0x802d397c, 12)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.data_evidence(None, a.DATA3_MAPPING, address, width)
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, 0x800686f0, 0x290)

    def test_descriptor_flags_input_mask_and_result_mask_are_distinct(self):
        for result in self.results:
            caller = result['ranges'][0]['instructions']
            values = [field['value'] for field in result['data_ranges'][0]['fields']]
            self.assertEqual(caller[3]['immediate'], 0x628)
            self.assertNotEqual(caller[3]['immediate'], 0x614)
            self.assertEqual(values, [1, 0x10, 0, 1, 0x0f, 0])
            self.assertEqual(caller[4]['immediate'], 0x2000)
            self.assertEqual(values[1] & 0x0e, 0)  # No flags 2/4/8 control gates.
            self.assertEqual(values[1] & 1, 0)  # Match source is actor+5bc.
            self.assertNotEqual(values[1] & 0x10, 0)  # Any-bit phase-2 path.
            self.assertNotEqual(values[4], caller[4]['immediate'])
            self.assertNotEqual(values[4], values[1])

    def test_fixed_reads_touch_only_declared_chain_spans(self):
        db = self.databases[0]
        for pc, width, _ in a.RANGES:
            fake = FakeDB(db.chain(21, pc - a.TEXT_START, width, a.TEXT_LENGTH)[0])
            a.range_evidence(fake, 21, pc, width)
            self.assertEqual(fake.calls, [(21, pc - a.TEXT_START, width, a.TEXT_LENGTH)])
        fake = FakeDB(db.chain(199, 101124, 12, a.DATA3_MAPPING[5])[0])
        a.data_evidence(fake, a.DATA3_MAPPING, 0x802d3964, 12)
        self.assertEqual(fake.calls, [(199, 101124, 12, a.DATA3_MAPPING[5])])

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
