#!/usr/bin/env python3
"""First input-machine operands, fixed data, authentication and refusal tests."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_input_machine_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def ops(text):
    """Explicit independent expected operands, not an instruction decoder."""
    fields = {
        'stwu': 'rS rA displacement', 'stw': 'rS rA displacement',
        'stb': 'rS rA displacement', 'lwz': 'rD rA displacement',
        'lbz': 'rD rA displacement', 'lhz': 'rD rA displacement',
        'lwzx': 'rD rA rB', 'addi': 'rD rA immediate', 'addis': 'rD rA immediate',
        'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS',
        'rlwinm': 'rS rA SH MB ME Rc', 'extsb': 'rS rA Rc',
        'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc',
        'add': 'rD rA rB Rc', 'subf': 'rD rA rB Rc',
        'neg': 'rD rA Rc', 'cntlzw': 'rS rA Rc',
        'cmp': 'BF L rA rB', 'cmpi': 'BF L rA immediate',
        'cmpli': 'BF L rA immediate', 'blr': '', 'bctrl': 'BO BI BH LK',
        'bc': 'BO BI target', 'bl': 'target', 'b': 'target',
    }
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = fields[name].split()
        assert len(keys) == len(values), line
        item = dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                    for key, value in zip(keys, values)})
        if name in ('bc', 'bl', 'b'):
            item['AA'] = 0
        if name == 'bc':
            item['LK'] = 0
        result.append(item)
    return result


class SyntheticTests(unittest.TestCase):
    def test_extents_and_types(self):
        self.assertEqual([(pc, n) for pc, n, _ in a.RANGES],
                         [(0x80068b8c, 136), (0x80068c14, 112), (0x80068c84, 128), (0x80068d04, 244)])
        self.assertEqual([(pc, n) for pc, n, _ in a.DATA_RANGES], [(0x802d38f8, 12), (0x802d3988, 12)])
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)

    def test_narrow_instruction_forms(self):
        self.assertEqual(a.decode_selected(0x4e800421, 0), dict(mnemonic='bctrl', BO=20, BI=0, BH=0, LK=1))
        for word in (0, d_form(42, 3, 4, 0), d_form(48, 3, 4, 0),
                     0x4e800420, 0x4e800421 | (1 << 11), (31 << 26) | (616 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        for word in ((31 << 26) | (23 << 1) | 1,
                     (31 << 26) | (26 << 1) | (1 << 11),
                     (31 << 26) | (104 << 1) | (1 << 11),
                     (31 << 26) | (954 << 1) | (1 << 11),
                     (31 << 26) | (0 << 1) | (1 << 21),
                     d_form(10, 1, 4, 1), spr_form(339, 1), spr_form(467, 12, 9, 1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_fixed_instruction_reads_fail_before_decode(self):
        pc, size, _ = a.RANGES[0]
        for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4)):
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

    def test_fixed_data_reads_fail_closed(self):
        for pc, size, _ in a.DATA_RANGES:
            for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4)):
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
                a.data_evidence(None, a.DATA3_MAPPING, a.DATA_RANGES[0][0], 12)

    def test_independent_data_value_checks(self):
        for pc, raw, reason in (
            (0x802d38f8, struct.pack('>6H', 1, 0, 0, 2, 0x200, 0), 'descriptor values'),
            (0x802d3988, struct.pack('>3I', 0x80068c14, 0x80068c88, 0x80068d04), 'dispatch targets'),
        ):
            with patch.object(a, 'DATA_RANGES', ((pc, 12, hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.data_evidence(FakeDB(raw), a.DATA3_MAPPING, pc, 12)

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
        for option in (['--address', '80068b8c'], ['--width', '136'], ['--raw'], ['--execute']):
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
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('both existing local archived snapshots required')
        cls.results = []
        cls.databases = []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
            cls.databases.append(a.c.GBF(data))
        cls.facts = {int(f['address'], 16): f for span in cls.results[0]['ranges'] for f in span['instructions']}

    def test_full_coverage_both_archives(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['data_ranges'], self.results[1]['data_ranges'])
        self.assertEqual(sorted(self.facts), [pc for start, width, _ in a.RANGES for pc in range(start, start + width, 4)])
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            for coverage, (_, width, _) in zip(result['function_coverage'], a.RANGES):
                self.assertEqual(coverage['represented_instructions'], width // 4)
                self.assertEqual(coverage['unrepresented_instructions'], 0)
                self.assertEqual(coverage['unrepresented_ranges'], [])
            def no_raw(value):
                if isinstance(value, dict):
                    self.assertTrue(set(value).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))
                    for child in value.values(): no_raw(child)
                elif isinstance(value, list):
                    for child in value: no_raw(child)
            no_raw(result)

    def test_descriptor_table_and_physical_spans(self):
        descriptor, table = self.results[0]['data_ranges']
        self.assertEqual(descriptor['fields'], [dict(offset=i * 2, width=2, type='u16', value=value)
                                                for i, value in enumerate((1, 0, 0, 1, 0x200, 0))])
        self.assertEqual(table['entries'], [dict(index=i, address=f'{0x802d3988 + i * 4:08x}', width=4, target=target)
                                           for i, target in enumerate(('80068c14', '80068c84', '80068d04'))])
        for item, offset, relative, physical in ((descriptor, 101016, 2748, 3394242), (table, 101160, 2892, 3394386)):
            self.assertEqual(item['spans'], [dict(root_buffer=199, data_buffer=206, chain_offset=offset,
                                                data_offset=relative, length=12, obfuscated=True, physical_offset=physical)])
            self.assertEqual(item['block_name'], 'MAIN_.data3')
            self.assertEqual(item['chain_root'], 199)
        for span, offset, relative, physical in zip(self.results[0]['ranges'],
                (406956, 407092, 407204, 407332), (13884, 14020, 14132, 14260), (783938, 784074, 784186, 784314)):
            self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=46, chain_offset=offset,
                                                data_offset=relative, length=span['width'], obfuscated=True, physical_offset=physical)])

    def assert_sequence(self, entry, expected):
        width = next(width for pc, width, _ in a.RANGES if pc == entry)
        self.assertEqual(len(expected), width // 4)
        self.assertEqual([self.facts[entry + i * 4] for i in range(len(expected))],
                         [dict(address=f'{entry + i * 4:08x}', **op) for i, op in enumerate(expected)])

    def test_every_wrapper_operand_in_order(self):
        self.assert_sequence(0x80068b8c, ops('''
            stwu 1 1 -32
            mflr 0
            addis 7 0 -32723
            stw 0 1 36
            addi 7 7 0x3988
            stw 31 1 28
            or 6 31 6 0
            stw 30 1 24
            or 5 30 5 0
            stw 29 1 20
            or 3 29 3 0
            lbz 0 5 0
            rlwinm 0 0 2 0 29 0
            lwzx 12 7 0
            mtctr 12
            bctrl 20 0 0 1
            lbz 3 30 3
            extsb 3 0 1
            bc 4 2 80068be0
            addi 3 0 0
            b 80068bf8
            addi 0 3 -1
            addi 3 0 1
            stb 0 30 3
            lwz 0 29 0x5d4
            or 0 0 31 0
            stw 0 29 0x5d4
            lwz 0 1 36
            lwz 31 1 28
            lwz 30 1 24
            lwz 29 1 20
            mtlr 0
            addi 1 1 32
            blr
        '''))

    def test_every_phase_zero_operand_in_order(self):
        self.assert_sequence(0x80068c14, ops('''
            stwu 1 1 -16
            mflr 0
            stw 0 1 20
            addi 0 0 0
            stb 0 5 2
            lhz 0 4 0
            cmpli 0 0 0 1
            bc 4 2 80068c4c
            addi 6 0 2
            addi 0 0 127
            stb 6 5 0
            stb 0 5 1
            bl 80068d04
            b 80068c74
            lwz 3 3 0x5bc
            lhz 0 4 8
            and 3 0 0 1
            bc 12 2 80068c70
            addi 0 0 1
            stb 0 5 0
            stb 0 5 2
            lhz 0 4 4
            stb 0 5 1
            addi 3 0 0
            lwz 0 1 20
            mtlr 0
            addi 1 1 16
            blr
        '''))

    def test_every_omitted_phase_one_operand_in_order(self):
        self.assert_sequence(0x80068c84, ops('''
            lbz 6 5 1
            addi 6 6 -1
            extsb 6 0 1
            stb 6 5 1
            bc 12 1 80068ca8
            addi 0 0 0
            addi 3 0 0
            stb 0 5 0
            blr
            lbz 0 5 2
            lwz 6 3 0x5bc
            rlwinm 0 0 1 0 30 0
            add 3 4 0 0
            lhz 0 3 8
            and 6 0 0 1
            bc 12 2 80068cfc
            lhz 0 4 4
            stb 0 5 1
            lbz 3 5 2
            addi 0 3 1
            stb 0 5 2
            rlwinm 0 6 0 24 31 0
            lhz 3 4 0
            addi 0 3 -1
            cmp 0 0 6 0
            bc 4 2 80068cfc
            addi 0 0 2
            addi 3 0 0
            stb 0 5 0
            blr
            addi 3 0 0
            blr
        '''))

    def test_every_phase_two_operand_in_order(self):
        self.assert_sequence(0x80068d04, ops('''
            lbz 6 5 1
            addi 6 6 -1
            extsb 6 0 1
            stb 6 5 1
            bc 12 1 80068d28
            addi 0 0 0
            addi 3 0 0
            stb 0 5 0
            blr
            lhz 6 4 2
            rlwinm 6 0 0 30 30 1
            bc 12 2 80068d48
            lwz 0 3 0x5e0
            rlwinm 0 0 0 25 25 1
            bc 12 2 80068d48
            addi 3 0 0
            blr
            rlwinm 6 0 0 29 29 1
            bc 12 2 80068d64
            lwz 0 3 0x5e0
            rlwinm 0 0 0 25 25 1
            bc 4 2 80068d64
            addi 3 0 0
            blr
            rlwinm 6 0 0 28 28 1
            bc 12 2 80068d80
            lwz 0 3 0x5b4
            rlwinm 0 0 0 12 15 1
            bc 4 2 80068d80
            addi 3 0 0
            blr
            rlwinm 6 0 0 31 31 1
            bc 12 2 80068d90
            lwz 7 3 0x5b4
            b 80068d94
            lwz 7 3 0x5bc
            lbz 3 5 2
            rlwinm 6 0 0 27 27 1
            rlwinm 3 0 1 0 30 0
            add 3 4 0 0
            lhz 3 3 8
            bc 12 2 80068dc0
            and 7 3 3 0
            neg 0 3 0
            or 0 0 3 0
            rlwinm 0 0 1 31 31 0
            b 80068dd0
            and 3 0 7 0
            subf 0 3 0 0
            cntlzw 0 0 0
            rlwinm 0 0 27 5 31 0
            cmpi 0 0 0 0
            bc 12 2 80068df0
            addi 0 0 0
            addi 3 0 1
            stb 0 5 0
            lhz 0 4 6
            stb 0 5 3
            blr
            addi 3 0 0
            blr
        '''))

    def test_each_instruction_and_data_byte_mutation_rejected(self):
        db = self.databases[0]  # Same bytes already fully authenticated by setUpClass.
        for pc, width, _ in a.RANGES:
            raw = db.chain(21, pc - a.TEXT_START, width, a.TEXT_LENGTH)[0]
            for offset in range(0, width, 4):
                changed = bytearray(raw); changed[offset + 3] ^= 1
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
