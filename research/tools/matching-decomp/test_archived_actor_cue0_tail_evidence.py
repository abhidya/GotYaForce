#!/usr/bin/env python3
"""All 159 operands, exact extents and adversarial fixed-reader controls."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import re
import unittest
from unittest.mock import patch

import read_archived_actor_cue0_tail_evidence as a
import read_archived_actor_input_testers_evidence as testers
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def ops(text):
    """Independent explicit expected operands, not a decoder or executor."""
    fields = {
        'stwu': 'rS rA displacement', 'stw': 'rS rA displacement',
        'stb': 'rS rA displacement', 'sth': 'rS rA displacement',
        'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement',
        'lhz': 'rD rA displacement', 'lha': 'rD rA displacement',
        'addi': 'rD rA immediate', 'mulli': 'rD rA immediate',
        'mflr': 'rD', 'mtlr': 'rS', 'neg': 'rD rA Rc',
        'rlwinm': 'rS rA SH MB ME Rc', 'extsb': 'rS rA Rc',
        'or': 'rS rA rB Rc', 'andc': 'rS rA rB Rc',
        'add': 'rD rA rB Rc', 'cmpi': 'BF L rA immediate',
        'blr': '', 'bc': 'BO BI target', 'bl': 'target', 'b': 'target',
    }
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = fields[name].split()
        assert len(keys) == len(values), line
        item = dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                    for key, value in zip(keys, values)})
        if name in ('bc', 'bl', 'b'): item['AA'] = 0
        if name == 'bc': item['LK'] = 0
        result.append(item)
    return result


EXPECTED = {
    0x80069814: ops('''
lbz 0 3 0x88
lwz 4 13 -31852
extsb 0 0 0
mulli 0 0 60
add 4 4 0 0
lbz 0 4 0x103
extsb 0 0 1
bc 4 2 8006983c
addi 3 0 0
blr
lwz 0 3 0x5d4
rlwinm 0 0 0 22 22 1
bc 4 2 80069850
addi 3 0 0
blr
addi 0 0 6
stb 0 3 0x6fb
addi 3 0 0
blr
'''),
    0x800696f4: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 0x661
extsb 0 0 0
cmpi 0 0 0 2
bc 12 2 80069728
cmpi 0 0 0 5
bc 12 2 80069728
addi 3 0 0
b 80069774
or 31 3 31 0
bl 800694c0
cmpi 0 0 3 0
bc 4 2 80069740
addi 3 0 0
b 80069774
lwz 0 31 0x5e0
rlwinm 0 0 0 30 31 1
bc 12 2 80069754
addi 3 0 0
b 80069774
lwz 0 31 0x5d4
rlwinm 0 0 0 24 24 1
bc 12 2 80069770
or 31 3 31 0
addi 4 0 0x20
bl 8006a750
b 80069774
addi 3 0 0
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
    0x80069038: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lwz 0 3 0x5e0
rlwinm 0 0 0 30 30 1
bc 12 2 80069058
addi 3 0 0
b 80069090
lwz 0 3 0x5d4
rlwinm 0 0 0 31 31 1
bc 4 2 8006906c
addi 3 0 0
b 80069090
lwz 0 3 0x5b4
rlwinm 0 0 0 23 23 1
bc 4 2 80069080
addi 3 0 0
b 80069090
addi 0 0 0
addi 4 0 4
stb 0 3 0x57c
bl 8006a750
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x80069354: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lwz 0 3 0x5e0
rlwinm 0 0 0 31 31 1
bc 12 2 8006937c
addi 3 0 0
b 800693e8
lhz 0 31 0x5d8
rlwinm 0 0 0 24 27 1
bc 4 2 80069390
addi 3 0 0
b 800693e8
lbz 0 31 0x661
cmpi 0 0 0 6
bc 12 2 800693b4
addi 4 0 0xc
bl 8006a750
cmpi 0 0 3 0
bc 4 2 800693cc
addi 3 0 0
b 800693e8
addi 4 0 0x25
bl 8006a750
cmpi 0 0 3 0
bc 4 2 800693cc
addi 3 0 0
b 800693e8
lhz 0 31 0x5d8
addi 3 0 1
rlwinm 0 0 28 28 31 0
stb 0 31 0x58f
lhz 0 31 0x5d8
rlwinm 0 0 0 28 23 0
sth 0 31 0x5d8
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
    0x80068f9c: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lwz 0 3 0x5e0
rlwinm 0 0 0 30 30 1
bc 12 2 80068fbc
addi 3 0 0
b 80068ff0
lwz 0 3 0x5b4
rlwinm 0 0 0 12 15 1
bc 4 2 80068fd0
addi 3 0 0
b 80068ff0
lbz 0 3 0x661
cmpi 0 0 0 6
bc 12 2 80068fe8
addi 4 0 1
bl 8006a750
b 80068ff0
addi 4 0 0x1d
bl 8006a750
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x800694c0: ops('''
lbz 0 3 0x7cd
extsb 0 0 1
bc 4 2 800694d4
addi 3 0 1
blr
lha 3 3 0x736
neg 0 3 0
andc 0 0 3 0
rlwinm 0 3 1 31 31 0
blr
'''),
}


class SyntheticTests(unittest.TestCase):
    def test_extents_and_types(self):
        self.assertEqual([(pc, size) for pc, size, _ in a.RANGES],
                         [(0x80069814, 76), (0x800696f4, 148), (0x80069038, 104),
                          (0x80069354, 168), (0x80068f9c, 100), (0x800694c0, 40)])
        for pc, size, _ in a.RANGES: self.assertEqual(len(EXPECTED[pc]), size // 4)
        self.assertEqual(sum(map(len, EXPECTED.values())), 159)
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)

    def test_forms_and_reserved_fields(self):
        neg = (31 << 26) | (4 << 21) | (3 << 16) | (104 << 1)
        self.assertEqual(a.decode_selected(neg, 0), dict(mnemonic='neg', rD=4, rA=3, Rc=0))
        self.assertEqual(a.decode_selected(neg | 1, 0)['Rc'], 1)
        with self.assertRaisesRegex(a.c.FormatError, 'reserved neg'): a.decode_selected(neg | (1 << 11), 0)
        self.assertIsNone(a.decode_selected(neg | (1 << 10), 0))
        for op, name in ((40, 'lhz'), (42, 'lha'), (44, 'sth')):
            register = 'rS' if op == 44 else 'rD'
            self.assertEqual(a.decode_selected(d_form(op, 5, 4, 0xfffc), 0),
                             dict(mnemonic=name, **{register: 5}, rA=4, displacement=-4))
        self.assertEqual(a.decode_selected(d_form(7, 0, 0, 0xffc4), 0),
                         dict(mnemonic='mulli', rD=0, rA=0, immediate=-60))
        for word in (0, 0x4e800421, d_form(10, 0, 4, 0), d_form(24, 0, 4, 0),
                     (31 << 26) | (87 << 1), (31 << 26) | (26 << 1),
                     (59 << 26) | (29 << 1), (63 << 26) | (15 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        for word in ((31 << 26) | (954 << 1) | (1 << 11),
                     d_form(11, 1, 4, 1), spr_form(339, 1), spr_form(467, 0, 9), spr_form(339, record=1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_branch_fields_and_signed_displacements(self):
        self.assertEqual(a.decode_selected((16 << 26) | (4 << 21) | (2 << 16) | 0xfffc, 0x1000),
                         dict(mnemonic='bc', BO=4, BI=2, LK=0, target='00000ffc', AA=0))
        self.assertEqual(a.decode_selected((16 << 26) | (12 << 21) | (2 << 16) | 0xfffe, 0x1000),
                         dict(mnemonic='bc', BO=12, BI=2, LK=0, target='fffffffc', AA=1))
        self.assertEqual(a.decode_selected((18 << 26) | 0x3fffffd, 0x1000),
                         dict(mnemonic='bl', target='00000ffc', AA=0))
        self.assertEqual(a.decode_selected((18 << 26) | 0x3fffffe, 0x1000),
                         dict(mnemonic='b', target='fffffffc', AA=1))

    def test_fixed_reads_fail_before_decode(self):
        for pc, size, _ in a.RANGES:
            for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                                   (pc - 4, 4), (pc + size, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, 21, address, width)
            for fields in ((21.0, pc, size), (21, True, size), (21, pc, float(size))):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'): a.range_evidence(None, *fields)
            with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'): a.range_evidence(None, 22, pc, size)
            for raw, reason in ((bytes(size), 'digest'), (bytes(size - 4), 'byte width'), (bytes(size + 4), 'byte width')):
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, reason): a.range_evidence(FakeDB(raw), 21, pc, size)
                    decoder.assert_not_called()
            with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(bytes(4)).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                    a.range_evidence(FakeDB(bytes(4)), 21, pc, 4)
            with patch.object(a, 'RANGES', a.RANGES * 2):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.range_evidence(None, 21, pc, size)

    def test_authentication_precedes_parsing(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); reader.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty', 'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_schema_rejected_before_new_reads(self):
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for field, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[field] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'): a.inspect(data, digest)
                parser.return_value.rows.assert_not_called(); ranges.assert_not_called()

    def test_mapping_guards_precede_fixed_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image', 'data5root',
                       'data5offset', 'data5length', 'data3root', 'data3offset', 'data3length'):
            aa, bb, ss = copy.deepcopy((auth, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'data5root': ss[7][4] += 1
            if target == 'data5offset': ss[7][5] += 4
            if target == 'data5length': bb[7][5] -= 4
            if target == 'data3root': ss[5][4] += 1
            if target == 'data3offset': ss[5][5] += 4
            if target == 'data3length': bb[5][5] -= 4
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called()

    def test_shared_allowlists_unchanged(self):
        for address, width, _ in a.RANGES:
            self.assertNotIn((address, width), a.c.TARGETS)
            self.assertNotIn((address, width), [row[:2] for row in a.command.RANGES])
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.command.read_range(None, address, width, 0x80000000)
            for reader in (a.status, testers):
                self.assertNotIn((address, width), [row[:2] for row in reader.RANGES])
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    reader.range_evidence(None, 21, address, width)
        for pointer in (0x80433934, 0x103, 0x4a4, 0x4b0):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, pointer, 4)

    def test_no_arbitrary_cli(self):
        for option in (['--address', '80069814'], ['--width', '76'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2); inspect.assert_not_called()

    def test_map_and_c_marker_extent_basis(self):
        root = Path(__file__).resolve().parents[3]
        text = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        rows = {int(pc, 16): int(size, 16) for pc, size in re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ', text, re.M)}
        for pc, size, _ in a.RANGES:
            if pc in a.MAP_SIZES: self.assertEqual(rows[pc], size)
            else: self.assertNotIn(pc, rows)
        source = '\n'.join((root / f'research/decomp/ghidra-export/chunk_000{n}.c').read_text() for n in (8, 9))
        markers = [int(pc, 16) for pc in re.findall(r'^// ==== ([0-9a-f]{8}) ', source, re.M)]
        for pc, size, _ in a.RANGES: self.assertEqual(markers[markers.index(pc) + 1], pc + size)

    def test_wraparound_masks_and_signed_short_formula(self):
        # Independent PPC MSB-zero mask numbering, including MB > ME wrapping.
        def mask(mb, me):
            bits = range(mb, me + 1) if mb <= me else list(range(mb, 32)) + list(range(me + 1))
            return sum(1 << (31 - bit) for bit in bits)
        for mb, me, expected in ((22, 22, 0x200), (30, 31, 3), (24, 24, 0x80),
                                 (30, 30, 2), (31, 31, 1), (23, 23, 0x100),
                                 (24, 27, 0xf0), (28, 31, 0xf),
                                 (28, 23, 0xffffff0f), (12, 15, 0xf0000)):
            self.assertEqual(mask(mb, me), expected)
        # A 16-bit signed value cannot hit the 32-bit NEG overflow case.
        for short in range(-32768, 32768):
            result = (((-short) & ~short) & 0xffffffff) >> 31
            self.assertEqual(result, int(short > 0))


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('local archives unavailable')
        cls.results = []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))

    def test_every_instruction_and_operand_both_archives(self):
        for result in self.results:
            for span, (pc, size, digest) in zip(result['ranges'], a.RANGES):
                expected = [dict(address=f'{pc + index * 4:08x}', **item) for index, item in enumerate(EXPECTED[pc])]
                self.assertEqual(span['instructions'], expected)
                self.assertEqual(span['sha256'], digest)
                self.assertEqual(span['end_exclusive'], f'{pc + size:08x}')
            self.assertEqual(sum(x['represented_instructions'] for x in result['function_coverage']), 159)
            for coverage, (pc, size, _) in zip(result['function_coverage'], a.RANGES):
                self.assertEqual(coverage['unrepresented_instructions'], 0)
                self.assertEqual(coverage['unrepresented_ranges'], [])
                self.assertEqual(coverage['map_size'], a.MAP_SIZES.get(pc))
                self.assertEqual(coverage['selected_width'], size)
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['function_coverage'], self.results[1]['function_coverage'])

    def test_physical_spans_and_returns(self):
        expected = [(47, 410164, 714, 787152), (47, 409876, 426, 786864),
                    (46, 408152, 15080, 785134), (46, 408948, 15876, 785930),
                    (46, 407996, 14924, 784978), (46, 409312, 16240, 786294)]
        for span, (pc, size, _), (buffer, chain, offset, physical) in zip(self.results[0]['ranges'], a.RANGES, expected):
            self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=buffer,
                             chain_offset=chain, data_offset=offset, length=size,
                             obfuscated=True, physical_offset=physical)])
            self.assertEqual(span['instructions'][-1], dict(address=f'{pc + size - 4:08x}', mnemonic='blr'))
        self.assertEqual([x['address'] for x in self.results[0]['ranges'][0]['instructions'] if x['mnemonic'] == 'blr'],
                         ['80069838', '8006984c', '8006985c'])
        self.assertEqual([x['address'] for x in self.results[0]['ranges'][5]['instructions'] if x['mnemonic'] == 'blr'],
                         ['800694d0', '800694e4'])

    def test_calls_and_cue_arguments(self):
        expected = [[], [('8006972c', '800694c0'), ('80069768', '8006a750')],
                    [('8006908c', '8006a750')],
                    [('800693a0', '8006a750'), ('800693b8', '8006a750')],
                    [('80068fe0', '8006a750'), ('80068fec', '8006a750')], []]
        for span, calls in zip(self.results[0]['ranges'], expected):
            self.assertEqual([(x['address'], x['target']) for x in span['instructions'] if x['mnemonic'] == 'bl'], calls)
        instructions = {x['address']: x for span in self.results[0]['ranges'] for x in span['instructions']}
        for pc, cue in (('80069764', 0x20), ('80069084', 4), ('8006939c', 0xc),
                        ('800693b4', 0x25), ('80068fdc', 1), ('80068fe8', 0x1d)):
            self.assertEqual(instructions[pc], dict(address=pc, mnemonic='addi', rD=4, rA=0, immediate=cue))

    def test_exact_nonstack_memory_order(self):
        expected = [
            [('80069814', 'lbz', 3, 0x88), ('80069818', 'lwz', 13, -31852),
             ('80069828', 'lbz', 4, 0x103), ('8006983c', 'lwz', 3, 0x5d4), ('80069854', 'stb', 3, 0x6fb)],
            [('80069708', 'lbz', 3, 0x661), ('80069740', 'lwz', 31, 0x5e0), ('80069754', 'lwz', 31, 0x5d4)],
            [('80069044', 'lwz', 3, 0x5e0), ('80069058', 'lwz', 3, 0x5d4),
             ('8006906c', 'lwz', 3, 0x5b4), ('80069088', 'stb', 3, 0x57c)],
            [('80069368', 'lwz', 3, 0x5e0), ('8006937c', 'lhz', 31, 0x5d8), ('80069390', 'lbz', 31, 0x661),
             ('800693cc', 'lhz', 31, 0x5d8), ('800693d8', 'stb', 31, 0x58f),
             ('800693dc', 'lhz', 31, 0x5d8), ('800693e4', 'sth', 31, 0x5d8)],
            [('80068fa8', 'lwz', 3, 0x5e0), ('80068fbc', 'lwz', 3, 0x5b4), ('80068fd0', 'lbz', 3, 0x661)],
            [('800694c0', 'lbz', 3, 0x7cd), ('800694d4', 'lha', 3, 0x736)],
        ]
        for span, accesses in zip(self.results[0]['ranges'], expected):
            actual = [(x['address'], x['mnemonic'], x['rA'], x['displacement']) for x in span['instructions']
                      if x['mnemonic'] in ('lbz', 'lwz', 'lhz', 'lha', 'stb', 'sth', 'stw', 'stwu') and x['rA'] != 1]
            self.assertEqual(actual, accesses)

    def test_signed_index_predicate_and_retained_values(self):
        spans = self.results[0]['ranges']
        ins = {x['address']: x for span in spans for x in span['instructions']}
        self.assertEqual([x['mnemonic'] for x in spans[0]['instructions'][:7]],
                         ['lbz', 'lwz', 'extsb', 'mulli', 'add', 'lbz', 'extsb'])
        self.assertEqual(ins['8006981c']['rS'], 0)
        self.assertEqual(ins['80069820']['immediate'], 60)
        for pc, target in (('80069714', '80069728'), ('8006971c', '80069728')):
            self.assertEqual((ins[pc]['BO'], ins[pc]['BI'], ins[pc]['target']), (12, 2, target))
        self.assertEqual(ins['8006970c']['mnemonic'], 'extsb')
        # Equality-to-six helpers use zero-extended lbz, without an extsb.
        for index in (3, 4): self.assertNotIn('extsb', [x['mnemonic'] for x in spans[index]['instructions']])
        self.assertEqual(ins['800694dc']['rB'], 3)  # the sole retained signed736 load
        self.assertEqual((ins['800694e0']['SH'], ins['800694e0']['MB'], ins['800694e0']['ME']), (1, 31, 31))
        for pc in ('800693a8', '800693c0'):
            self.assertEqual((ins[pc]['BO'], ins[pc]['BI'], ins[pc]['target']), (4, 2, '800693cc'))
        self.assertEqual((ins['800693e0']['SH'], ins['800693e0']['MB'], ins['800693e0']['ME']), (0, 28, 23))
        self.assertEqual(ins['80069088']['rS'], 0)  # store-before-call is not optional

    def test_no_raw_output_and_authenticated_metadata(self):
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(len(result['ranges']), 6)
            def no_raw(value):
                if isinstance(value, dict):
                    self.assertTrue(set(value).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))
                    for child in value.values(): no_raw(child)
                elif isinstance(value, list):
                    for child in value: no_raw(child)
            no_raw(result)


if __name__ == '__main__': unittest.main()
