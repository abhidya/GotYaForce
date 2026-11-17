#!/usr/bin/env python3
"""All 307 operands, exact boundaries and adversarial fixed-reader controls."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import re
import unittest
from unittest.mock import patch

import read_archived_actor_input_testers_evidence as a
import read_archived_charge_helper_evidence as charge
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def ops(text):
    """Independent explicit expected operands, not a decoder or executor."""
    fields = {
        'stwu': 'rS rA displacement', 'stw': 'rS rA displacement',
        'stb': 'rS rA displacement', 'lwz': 'rD rA displacement',
        'lbz': 'rD rA displacement', 'addi': 'rD rA immediate',
        'mflr': 'rD', 'mtlr': 'rS', 'neg': 'rD rA Rc',
        'rlwinm': 'rS rA SH MB ME Rc', 'extsb': 'rS rA Rc',
        'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc',
        'slw': 'rS rA rB Rc', 'add': 'rD rA rB Rc',
        'ori': 'rS rA immediate', 'cmpi': 'BF L rA immediate',
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
    0x800699d8: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
bl 80069cb0
cmpi 0 0 3 0
bc 12 2 80069a00
addi 3 0 1
b 80069a74
or 31 3 31 0
bl 80069c50
cmpi 0 0 3 0
bc 12 2 80069a18
addi 3 0 1
b 80069a74
or 31 3 31 0
bl 80069bf0
cmpi 0 0 3 0
bc 12 2 80069a30
addi 3 0 1
b 80069a74
or 31 3 31 0
bl 80069b98
cmpi 0 0 3 0
bc 12 2 80069a48
addi 3 0 1
b 80069a74
or 31 3 31 0
bl 80069b10
cmpi 0 0 3 0
bc 12 2 80069a60
addi 3 0 1
b 80069a74
or 31 3 31 0
bl 80069a88
neg 0 3 0
or 0 0 3 0
rlwinm 0 3 1 31 31 0
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
    0x80069a88: ops('''
stwu 1 1 -16
mflr 0
addi 4 0 0
stw 0 1 20
stb 4 3 0x595
lwz 0 3 0x5d4
rlwinm 0 0 0 26 26 1
bc 4 2 80069ab0
addi 3 0 0
b 80069b00
lbz 0 3 0x748
cmpi 0 0 0 2
bc 12 2 80069ac8
lbz 0 3 0x58e
rlwinm 0 0 0 31 31 1
bc 12 2 80069ad4
addi 0 0 1
stb 0 3 0x585
b 80069ad8
stb 4 3 0x585
lbz 0 3 0x585
addi 4 0 1
lbz 5 3 0x58e
extsb 0 0 0
slw 4 0 0 0
and 5 0 0 1
bc 12 2 80069afc
addi 3 0 0
b 80069b00
bl 80069dd0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x80069b10: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
addi 0 0 0
stb 0 3 0x595
lwz 0 3 0x5d4
rlwinm 0 0 0 25 25 1
bc 4 2 80069b38
addi 3 0 0
b 80069b88
lbz 0 3 0x748
cmpi 0 0 0 1
bc 4 2 80069b4c
addi 3 0 0
b 80069b88
lbz 4 3 0x58e
rlwinm 4 0 0 30 30 1
bc 12 2 80069b60
addi 3 0 0
b 80069b88
rlwinm 4 0 0 31 31 1
bc 4 2 80069b7c
lbz 0 3 0x7d2
rlwinm 0 0 0 28 28 1
bc 4 2 80069b7c
addi 3 0 0
b 80069b88
addi 0 0 1
stb 0 3 0x585
bl 80069dd0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x80069b98: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
addi 0 0 0
stb 0 3 0x595
lbz 0 3 0x58e
rlwinm 0 0 0 29 29 1
bc 12 2 80069bc0
addi 3 0 0
b 80069be0
lwz 0 3 0x5d4
rlwinm 0 0 0 24 24 1
bc 4 2 80069bd4
addi 3 0 0
b 80069be0
addi 0 0 2
stb 0 3 0x585
bl 80069dd0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x80069bf0: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
addi 0 0 0
stb 0 3 0x595
lbz 0 3 0x58e
rlwinm 0 0 0 28 28 1
bc 12 2 80069c18
addi 3 0 0
b 80069c40
lwz 0 3 0x5d4
rlwinm 0 0 0 21 21 1
bc 4 2 80069c2c
addi 3 0 0
b 80069c40
addi 4 0 3
addi 0 0 1
stb 4 3 0x585
stb 0 3 0x595
bl 80069dd0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x80069c50: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
addi 0 0 0
stb 0 3 0x595
lbz 0 3 0x58e
rlwinm 0 0 0 26 26 1
bc 12 2 80069c78
addi 3 0 0
b 80069ca0
lwz 0 3 0x5d4
rlwinm 0 0 0 19 19 1
bc 4 2 80069c8c
addi 3 0 0
b 80069ca0
addi 4 0 5
addi 0 0 1
stb 4 3 0x585
stb 0 3 0x595
bl 80069dd0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x80069cb0: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
addi 0 0 0
stw 31 1 12
or 3 31 3 0
stb 0 3 0x595
lbz 0 3 0x4a0
extsb 0 0 1
bc 4 2 80069ce0
addi 3 0 0
b 80069dbc
lwz 0 31 0x5e0
rlwinm 0 0 0 30 30 1
bc 12 2 80069d00
lbz 0 31 0x584
cmpi 0 0 0 5
bc 4 2 80069d00
addi 3 0 0
b 80069dbc
lbz 0 31 0x593
extsb 0 0 1
bc 12 1 80069d3c
lbz 0 31 0x58e
rlwinm 0 0 0 26 26 1
bc 12 2 80069d20
addi 3 0 0
b 80069dbc
lwz 0 31 0x5d4
rlwinm 0 0 0 19 19 1
bc 4 2 80069d34
addi 3 0 0
b 80069dbc
addi 0 0 6
stb 0 31 0x593
lbz 0 31 0x4a0
cmpi 0 0 0 2
bc 4 2 80069d50
addi 3 0 1
b 80069dbc
lwz 3 31 0x4a4
lbz 0 3 0x3e6
extsb 0 0 1
bc 4 2 80069d74
lbz 0 3 0x593
extsb 0 0 1
bc 12 1 80069d74
addi 3 0 1
b 80069dbc
addi 3 0 5
addi 0 0 1
stb 3 31 0x585
or 31 3 31 0
stb 0 31 0x595
bl 80069dd0
cmpi 0 0 3 0
bc 12 2 80069db8
lwz 4 31 0x4a4
addi 0 0 5
addi 3 0 1
stb 0 4 0x585
stb 0 4 0x584
lwz 0 4 0x5e0
ori 0 0 3
stw 0 4 0x5e0
b 80069dbc
addi 3 0 0
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
    0x80069dd0: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 4 3 0x585
lwz 0 3 0x4b0
extsb 4 5 0
add 4 0 5 0
lbz 0 4 0xb8
extsb 0 0 0
cmpi 0 0 0 -1
bc 4 2 80069e0c
addi 3 0 0
b 80069e90
lwz 0 31 0x5e0
rlwinm 0 0 0 30 31 1
bc 12 2 80069e44
lbz 4 31 0x57a
addi 0 0 1
slw 0 0 5 0
extsb 4 4 0
and 4 0 0 1
bc 4 2 80069e38
addi 3 0 0
b 80069e90
bl 8005c080
addi 0 0 1
stb 0 31 0x595
lbz 0 31 0x585
lwz 3 31 0x4b0
extsb 0 0 0
add 3 3 0 0
lbz 0 3 0xb8
extsb 0 0 0
cmpi 0 0 0 1
bc 12 2 80069e74
bc 4 0 80069e8c
cmpi 0 0 0 0
bc 4 0 80069e80
b 80069e8c
or 31 3 31 0
bl 80069ea4
b 80069e90
or 31 3 31 0
bl 80069fe0
b 80069e90
addi 3 0 0
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
}


class SyntheticTests(unittest.TestCase):
    def test_extents_and_types(self):
        self.assertEqual([(pc, size) for pc, size, _ in a.RANGES],
                         [(0x800699d8, 176), (0x80069a88, 136), (0x80069b10, 136),
                          (0x80069b98, 88), (0x80069bf0, 96), (0x80069c50, 96),
                          (0x80069cb0, 288), (0x80069dd0, 212)])
        for pc, size, _ in a.RANGES: self.assertEqual(len(EXPECTED[pc]), size // 4)
        self.assertEqual(sum(map(len, EXPECTED.values())), 307)
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)

    def test_new_forms_and_reserved_fields(self):
        neg = (31 << 26) | (4 << 21) | (3 << 16) | (104 << 1)
        self.assertEqual(a.decode_selected(neg, 0), dict(mnemonic='neg', rD=4, rA=3, Rc=0))
        self.assertEqual(a.decode_selected(neg | 1, 0)['Rc'], 1)
        with self.assertRaisesRegex(a.c.FormatError, 'reserved neg'): a.decode_selected(neg | (1 << 11), 0)
        self.assertIsNone(a.decode_selected(neg | (1 << 10), 0))  # unselected overflow-enabled neg
        self.assertEqual(a.decode_selected(d_form(24, 5, 4, 0xffff), 0),
                         dict(mnemonic='ori', rS=5, rA=4, immediate=65535))
        for word in (0, 0x4e800421, d_form(10, 0, 4, 0), d_form(40, 0, 4, 0),
                     d_form(42, 0, 4, 0), (31 << 26) | (87 << 1), (31 << 26) | (26 << 1),
                     (59 << 26) | (29 << 1), (63 << 26) | (15 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        for word in ((31 << 26) | (954 << 1) | (1 << 11),
                     d_form(11, 1, 4, 1), spr_form(339, 1), spr_form(467, 0, 9), spr_form(339, record=1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

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
            for reader in (a.status, charge):
                self.assertNotIn((address, width), [row[:2] for row in reader.RANGES])
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): reader.range_evidence(None, 21, address, width)

    def test_no_arbitrary_cli(self):
        for option in (['--address', '800699d8'], ['--width', '176'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2); inspect.assert_not_called()

    def test_map_and_c_marker_extent_basis(self):
        root = Path(__file__).resolve().parents[3]
        text = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        rows = {int(pc, 16): int(size, 16) for pc, size in re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ', text, re.M)}
        self.assertNotIn(0x800699d8, rows)
        for pc, size, _ in a.RANGES[1:]: self.assertEqual(rows[pc], size)
        source = (root / 'research/decomp/ghidra-export/chunk_0009.c').read_text()
        markers = [int(pc, 16) for pc in re.findall(r'^// ==== ([0-9a-f]{8}) ', source, re.M)]
        for pc, size, _ in a.RANGES: self.assertEqual(markers[markers.index(pc) + 1], pc + size)


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
            self.assertEqual(sum(x['represented_instructions'] for x in result['function_coverage']), 307)
            for index, coverage in enumerate(result['function_coverage']):
                self.assertEqual(coverage['unrepresented_instructions'], 0)
                self.assertEqual(coverage['unrepresented_ranges'], [])
                self.assertEqual(coverage['map_size'], None if index == 0 else a.RANGES[index][1])
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['function_coverage'], self.results[1]['function_coverage'])

    def test_physical_spans_and_returns(self):
        for span, (pc, size, _) in zip(self.results[0]['ranges'], a.RANGES):
            delta = pc - 0x800699d8
            self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=47,
                             chain_offset=410616 + delta, data_offset=1166 + delta,
                             length=size, obfuscated=True, physical_offset=787604 + delta)])
            self.assertEqual(span['instructions'][-1], dict(address=f'{pc + size - 4:08x}', mnemonic='blr'))

    def test_ordered_calls_and_external_boundaries(self):
        ranges = self.results[0]['ranges']
        self.assertEqual([(x['address'], x['target']) for x in ranges[0]['instructions'] if x['mnemonic'] == 'bl'],
                         [('800699ec', '80069cb0'), ('80069a04', '80069c50'), ('80069a1c', '80069bf0'),
                          ('80069a34', '80069b98'), ('80069a4c', '80069b10'), ('80069a64', '80069a88')])
        for span in ranges[1:7]:
            self.assertEqual([x['target'] for x in span['instructions'] if x['mnemonic'] == 'bl'], ['80069dd0'])
        self.assertEqual([(x['address'], x['target']) for x in ranges[7]['instructions'] if x['mnemonic'] == 'bl'],
                         [('80069e38', '8005c080'), ('80069e78', '80069ea4'), ('80069e84', '80069fe0')])
        for span in ranges[1:7]:
            fields = [x for x in span['instructions'] if x['mnemonic'] in ('lwz', 'lbz', 'stb') and x['rA'] != 1]
            self.assertEqual((fields[0]['mnemonic'], fields[0]['displacement']), ('stb', 0x595))

    def test_reloads_retained_values_and_signed_predicates(self):
        ins = {x['address']: x for span in self.results[0]['ranges'] for x in span['instructions']}
        for pc, register, field in (('80069ad8', 0, 0x585), ('80069ae0', 5, 0x58e),
                                    ('80069b4c', 4, 0x58e), ('80069d3c', 0, 0x4a0),
                                    ('80069de4', 4, 0x585), ('80069e44', 0, 0x585)):
            self.assertEqual((ins[pc]['mnemonic'], ins[pc]['rD'], ins[pc]['displacement']), ('lbz', register, field))
        self.assertEqual(ins['80069b60']['rS'], 4)  # retained 58e, no second load
        for pc in ('80069d04', '80069d64'):
            self.assertEqual(ins[pc]['mnemonic'], 'extsb'); self.assertEqual(ins[pc]['Rc'], 1)
        for pc in ('80069d08', '80069d68'):
            self.assertEqual((ins[pc]['BO'], ins[pc]['BI']), (12, 1))  # signed greater than zero
        self.assertEqual(ins['80069e20']['rB'], 5)  # retained first signed585
        self.assertEqual(ins['80069dfc']['immediate'], -1)
        self.assertEqual(ins['80069e00']['target'], '80069e0c')
        self.assertEqual(ins['80069e08']['target'], '80069e90')

    def test_no_raw_output_and_authenticated_metadata(self):
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(len(result['ranges']), 8)
            def no_raw(value):
                if isinstance(value, dict):
                    self.assertTrue(set(value).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))
                    for child in value.values(): no_raw(child)
                elif isinstance(value, list):
                    for child in value: no_raw(child)
            no_raw(result)


if __name__ == '__main__': unittest.main()
