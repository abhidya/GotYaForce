#!/usr/bin/env python3
"""Charge helper full operands, fixed data, authentication and refusal tests."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_charge_helper_evidence as a
import read_archived_tenth_input_machine_evidence as tenth
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def ops(text):
    """Independent explicit expected operands, not a decoder or executor."""
    fields = {
        'stwu': 'rS rA displacement', 'stw': 'rS rA displacement',
        'stb': 'rS rA displacement', 'lwz': 'rD rA displacement',
        'lbz': 'rD rA displacement', 'lbzx': 'rD rA rB',
        'addi': 'rD rA immediate', 'addis': 'rD rA immediate',
        'lmw': 'rD rA displacement', 'stmw': 'rS rA displacement',
        'lfs': 'fD rA displacement', 'lfd': 'fD rA displacement',
        'stfs': 'fS rA displacement', 'stfd': 'fS rA displacement',
        'psq_l': 'fD rA displacement W I', 'psq_st': 'fS rA displacement W I',
        'lfsx': 'fD rA rB', 'mflr': 'rD', 'mtlr': 'rS',
        'fmuls': 'fD fA fC', 'fadds': 'fD fA fB', 'fsubs': 'fD fA fB',
        'fnmsubs': 'fD fA fC fB', 'fcmpo': 'crD fA fB', 'cror': 'crD crA crB',
        'rlwinm': 'rS rA SH MB ME Rc', 'extsb': 'rS rA Rc',
        'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc', 'andc': 'rS rA rB Rc',
        'slw': 'rS rA rB Rc', 'cmp': 'BF L rA rB', 'cmpi': 'BF L rA immediate',
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


EXPECTED = ops('''
stwu 1 1 -64
mflr 0
stw 0 1 68
stfd 31 1 48
psq_st 31 1 56 0 0
stmw 24 1 16
lwz 4 13 -31852
or 3 25 3 0
lbz 0 4 0x1829
extsb 0 0 1
bc 4 2 80068964
lbz 0 25 0x6fc
lfs 31 25 0x768
extsb 0 0 1
bc 12 2 80068734
lfs 0 2 -29688
fmuls 31 31 0
lbz 26 25 0x655
addi 29 0 0
addis 4 0 -32723
addis 3 0 -32723
stb 29 25 0x655
addi 30 4 0x3970
addi 28 3 0x397c
or 25 31 25 0
addi 27 0 0
lwz 3 25 0x4b0
addi 0 27 0xbb
lbzx 0 3 0
extsb 0 0 0
cmpi 0 0 0 -1
bc 12 2 8006890c
lwz 0 25 0x5e0
rlwinm 0 0 0 30 31 1
bc 12 2 800687b4
lbz 3 25 0x584
addi 0 27 3
extsb 3 3 0
cmp 0 0 3 0
bc 4 2 800687b4
lfs 0 2 -29684
addi 0 0 1
slw 0 0 27 0
stfs 0 31 0x63c
stfs 0 31 0x648
lbz 3 25 0x654
andc 3 0 0 0
stb 0 25 0x654
b 8006890c
addi 0 27 3
addi 4 0 1
lbz 3 25 0x58e
slw 4 0 0 0
and 3 0 0 1
bc 12 2 800687ec
lfs 0 2 -29684
slw 4 0 27 0
stfs 0 31 0x63c
stfs 0 31 0x648
lbz 3 25 0x654
andc 3 0 0 0
stb 0 25 0x654
b 8006890c
lwz 3 25 0x5b4
lwz 0 30 0
and 3 0 0 1
bc 12 2 8006889c
lfs 1 31 0x63c
lfs 2 2 -29688
fcmpo 0 1 2
cror 2 1 2
bc 4 2 8006886c
lfs 0 31 0x648
slw 4 24 27 0
or 25 3 25 0
addi 4 0 1
fadds 0 0 31
addi 5 0 4
stfs 0 31 0x648
lbz 0 25 0x654
or 0 0 24 0
stb 0 25 0x654
bl 800f0104
lwz 3 25 0x4ac
addi 0 29 0x184
lfs 0 31 0x648
lfsx 1 3 0
fcmpo 0 0 1
cror 2 1 2
bc 4 2 8006890c
stfs 1 31 0x648
lbz 0 25 0x655
or 0 0 24 0
stb 0 25 0x655
b 8006890c
lfs 0 2 -29680
fadds 0 1 0
stfs 0 31 0x63c
lfs 0 31 0x63c
fcmpo 0 0 2
bc 4 1 8006890c
fsubs 0 0 2
lfs 1 31 0x648
fadds 0 1 0
stfs 0 31 0x648
stfs 2 31 0x63c
b 8006890c
lwz 3 25 0x4ac
addi 0 29 0x184
lfs 1 31 0x648
lfsx 0 3 0
fcmpo 0 1 0
cror 2 1 2
bc 4 2 800688c8
lwz 3 25 0x5d4
lwz 0 28 0
or 3 0 0 0
stw 0 25 0x5d4
lfs 3 2 -29684
addi 0 0 1
lfs 2 2 -29676
slw 0 0 27 0
stfs 3 31 0x63c
lfs 1 25 0x768
lfs 0 31 0x648
fnmsubs 0 2 1 0
stfs 0 31 0x648
lbz 3 25 0x654
andc 3 0 0 0
stb 0 25 0x654
lfs 0 31 0x648
fcmpo 0 0 3
cror 2 0 2
bc 4 2 8006890c
stfs 3 31 0x648
addi 27 27 1
addi 30 30 4
cmpi 0 0 27 3
addi 29 29 4
addi 28 28 4
addi 31 31 4
bc 12 0 80068758
extsb 26 0 1
bc 4 2 8006894c
lbz 0 25 0x655
extsb 0 0 1
bc 12 2 80068964
or 25 3 25 0
addi 4 0 0x13
bl 800061cc
b 80068964
lbz 0 25 0x655
extsb 0 0 1
bc 4 2 80068964
or 25 3 25 0
addi 4 0 0x14
bl 800061cc
psq_l 31 1 56 0 0
lfd 31 1 48
lmw 24 1 16
lwz 0 1 68
mtlr 0
addi 1 1 64
blr
''')


class SyntheticTests(unittest.TestCase):
    def test_extents_and_types(self):
        self.assertEqual(a.RANGES, ((0x800686f0, 656,
                         '55523dd4f938a0f11bb9f7a26ae31de5d5eb3647354af3315ba37979340f3817'),))
        self.assertEqual(a.DATA_RANGES, ((0x802d3970, 24,
                         '57b950110534ba512d9dc0bc63a304c0c8b37bff19ae889779618d3109cd2ae0'),
                         (0x80437628, 16,
                         '339a9072dd04453256cb6f8826245e04de4e202128dc8a7cc54cf4654b06e03c')))
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)

    def test_full_register_save_restore_forms(self):
        self.assertEqual(a.decode_selected(d_form(47, 24, 1, 16), 0),
                         dict(mnemonic='stmw', rS=24, rA=1, displacement=16))
        self.assertEqual(a.decode_selected(d_form(46, 24, 1, -16), 0),
                         dict(mnemonic='lmw', rD=24, rA=1, displacement=-16))
        for op, name, key in ((56, 'psq_l', 'fD'), (60, 'psq_st', 'fS')):
            self.assertEqual(a.decode_selected(d_form(op, 31, 1, 56), 0),
                             dict(mnemonic=name, **{key: 31}, rA=1, displacement=56, W=0, I=0))
            self.assertEqual(a.decode_selected((op << 26) | (31 << 21) | (1 << 16) | 0xff0, 0)['displacement'], -16)
            for flag in (1 << 15, 1 << 12, 7 << 12):
                with self.assertRaisesRegex(a.c.FormatError, 'quantization'):
                    a.decode_selected(d_form(op, 31, 1, 56) | flag, 0)

    def test_fused_and_indexed_forms(self):
        fma = (59 << 26) | (5 << 21) | (2 << 16) | (7 << 11) | (3 << 6) | (30 << 1)
        self.assertEqual(a.decode_selected(fma, 0), dict(mnemonic='fnmsubs', fD=5, fA=2, fC=3, fB=7))
        with self.assertRaisesRegex(a.c.FormatError, 'record'): a.decode_selected(fma | 1, 0)
        lfsx = (31 << 26) | (2 << 21) | (3 << 16) | (4 << 11) | (535 << 1)
        self.assertEqual(a.decode_selected(lfsx, 0), dict(mnemonic='lfsx', fD=2, rA=3, rB=4))
        with self.assertRaisesRegex(a.c.FormatError, 'reserved'): a.decode_selected(lfsx | 1, 0)

    def test_unsupported_and_reserved_forms(self):
        for word in (0, 0x4e800421, d_form(10, 0, 4, 0), d_form(40, 0, 4, 0),
                     d_form(42, 0, 4, 0), (31 << 26) | (23 << 1),
                     (31 << 26) | (26 << 1), (59 << 26) | (29 << 1),
                     (63 << 26) | (30 << 1), (63 << 26) | (15 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        for word in ((31 << 26) | (87 << 1) | 1,
                     (31 << 26) | (954 << 1) | (1 << 11),
                     (31 << 26) | (0 << 1) | (1 << 21),
                     d_form(11, 1, 4, 1), spr_form(339, 1), spr_form(467, 0, 9),
                     (19 << 26) | (449 << 1) | 1,
                     (63 << 26) | (32 << 1) | (1 << 21),
                     (59 << 26) | (25 << 1) | (1 << 11),
                     (59 << 26) | (21 << 1) | (1 << 6)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_fixed_instruction_reads_fail_before_decode(self):
        pc, size, _ = a.RANGES[0]
        for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                               (0x800686d8, 4), (0x80068980, 4)):
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

    def test_fixed_data_reads_fail_before_interpretation(self):
        for pc, size, _ in a.DATA_RANGES:
            mapping = a.DATA3_MAPPING if pc == 0x802d3970 else a.DATA5_MAPPING
            for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                                   (0x802d3964, 12), (0x802d3988, 12), (0x80437638, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.data_evidence(None, mapping, address, width)
            for address, width in ((float(pc), size), (pc, True), (pc, float(size))):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    a.data_evidence(None, mapping, address, width)
            for index in (0, 1, 2, 4, 5, 6):
                for value in (mapping[index] + 4, float(mapping[index])):
                    changed = list(mapping); changed[index] = value
                    with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                        a.data_evidence(None, tuple(changed), pc, size)
            for changed in (list(mapping), a.DATA5_MAPPING if mapping == a.DATA3_MAPPING else a.DATA3_MAPPING):
                with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                    a.data_evidence(None, changed, pc, size)
            for raw, reason in ((bytes(size), 'digest'), (bytes(size - 1), 'byte width'), (bytes(size + 2), 'byte width')):
                with patch.object(a.c, 'integer') as interpreter:
                    with self.assertRaisesRegex(a.c.FormatError, reason): a.data_evidence(FakeDB(raw), mapping, pc, size)
                    interpreter.assert_not_called()
            with patch.object(a, 'DATA_RANGES', a.DATA_RANGES * 2):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.data_evidence(None, mapping, pc, size)

    def test_every_fixed_value_independently_checked(self):
        for pc, values, mapping, reason in (
            (0x802d3970, [0x200, 0x200, 0x400, 0x400, 0x800, 0x1000], a.DATA3_MAPPING, 'mask values'),
            (0x80437628, [0x41200000, 0, 0x3f800000, 0x40000000], a.DATA5_MAPPING, 'constant values'),
        ):
            for index in range(len(values)):
                changed = values.copy(); changed[index] ^= 0x80000000 if values[index] == 0 else 1
                raw = struct.pack('>' + str(len(values)) + 'I', *changed)
                with patch.object(a, 'DATA_RANGES', ((pc, len(raw), hashlib.sha256(raw).hexdigest()),)):
                    with self.assertRaisesRegex(a.c.FormatError, reason): a.data_evidence(FakeDB(raw), mapping, pc, len(raw))

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

    def test_schema_rejected_before_new_reads(self):
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for field, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[field] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'data_evidence') as data_reader:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'): a.inspect(data, digest)
                parser.return_value.rows.assert_not_called(); ranges.assert_not_called(); data_reader.assert_not_called()

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
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'data_evidence') as data_reader:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called(); data_reader.assert_not_called()

    def test_shared_allowlists_unchanged(self):
        for address, width, _ in a.RANGES:
            self.assertNotIn((address, width), a.c.TARGETS)
            for reader in (a.command, a.machine, tenth):
                self.assertNotIn((address, width), [row[:2] for row in reader.RANGES])
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.command.read_range(None, address, width, 0x80000000)
            for reader in (a.machine, tenth):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): reader.range_evidence(None, 21, address, width)
        for address, width, _ in a.DATA_RANGES:
            self.assertNotIn((address, width), a.c.TARGETS)
            self.assertNotIn((address, width), [row[:2] for row in a.command.RANGES])
            for reader in (a.machine, tenth):
                self.assertNotIn((address, width), [row[:2] for row in reader.DATA_RANGES])
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    reader.data_evidence(None, a.DATA3_MAPPING, address, width)

    def test_no_arbitrary_cli(self):
        for option in (['--address', '800686f0'], ['--width', '656'], ['--raw'], ['--execute']):
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
        cls.results = []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))

    def test_every_instruction_and_operand_both_archives(self):
        self.assertEqual(len(EXPECTED), 164)
        expected = [dict(address=f'{0x800686f0 + index * 4:08x}', **item) for index, item in enumerate(EXPECTED)]
        for result in self.results:
            self.assertEqual(result['ranges'][0]['instructions'], expected)
            self.assertEqual(result['function_coverage'], dict(entry='800686f0', end_exclusive='80068980',
                             selected_width=656, represented_instructions=164, unrepresented_instructions=0,
                             unrepresented_ranges=[]))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['data_ranges'], self.results[1]['data_ranges'])

    def test_fixed_tables_and_physical_spans(self):
        table, constants = self.results[0]['data_ranges']
        self.assertEqual([f['value'] for f in table['fields']], [0x200, 0x200, 0x400, 0x400, 0x800, 0x1000])
        self.assertEqual([f['slot'] for f in table['fields']], [0, 1, 2, 0, 1, 2])
        self.assertEqual([f['type'] for f in table['fields']], ['u32'] * 6)
        self.assertEqual([f['value'] for f in constants['fields']], [10, 0, 1, 2])
        self.assertEqual([f['type'] for f in constants['fields']], ['f32'] * 4)
        self.assertEqual(table['spans'], [dict(root_buffer=199, data_buffer=206, chain_offset=101136,
                             data_offset=2868, length=24, obfuscated=True, physical_offset=3394362)])
        self.assertEqual(constants['spans'], [dict(root_buffer=263, data_buffer=264, chain_offset=3080,
                             data_offset=3080, length=16, obfuscated=True, physical_offset=4344846)])
        self.assertEqual(self.results[0]['ranges'][0]['spans'],
                         [dict(root_buffer=21, data_buffer=46, chain_offset=405776, data_offset=12704,
                               length=656, obfuscated=True, physical_offset=782758)])
        self.assertEqual(self.results[0]['r2_basis']['displacements'],
                         {'80437628': -29688, '8043762c': -29684, '80437630': -29680, '80437634': -29676})

    def test_branch_and_effect_boundaries(self):
        ins = self.results[0]['ranges'][0]['instructions']; bypc = {i['address']: i for i in ins}
        self.assertEqual([(i['address'], i['target']) for i in ins if i['mnemonic'] == 'bl'],
                         [('80068838', '800f0104'), ('80068944', '800061cc'), ('80068960', '800061cc')])
        self.assertEqual(bypc['80068718']['target'], '80068964')
        self.assertEqual(bypc['8006876c']['target'], '8006890c')
        self.assertEqual(bypc['80068838']['mnemonic'], 'bl')
        self.assertEqual(bypc['80068834']['displacement'], 0x654)
        self.assertEqual(bypc['8006883c']['displacement'], 0x4ac)
        self.assertEqual(bypc['800688e4'], dict(address='800688e4', mnemonic='fnmsubs', fD=0, fA=2, fC=1, fB=0))
        self.assertEqual(bypc['80068700']['mnemonic'], 'psq_st')
        self.assertEqual(bypc['80068964']['mnemonic'], 'psq_l')
        self.assertEqual(bypc['8006897c']['mnemonic'], 'blr')

    def test_no_raw_output_and_authenticated_metadata(self):
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(len(result['ranges']), 1); self.assertEqual(len(result['data_ranges']), 2)
            def no_raw(value):
                if isinstance(value, dict):
                    self.assertTrue(set(value).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))
                    for child in value.values(): no_raw(child)
                elif isinstance(value, list):
                    for child in value: no_raw(child)
            no_raw(result)


if __name__ == '__main__': unittest.main()
