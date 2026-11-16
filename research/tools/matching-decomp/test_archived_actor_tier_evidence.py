#!/usr/bin/env python3
"""Complete tier operands, exact fixed rows, and fail-closed archive controls.

Fixtures contain derived operands and selected data, never executable bytes.
"""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_actor_tier_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


# Independently reviewed, complete ordered operand expectations.
EXPECTED = {
    0x8006817c: """
stwu rA=1 displacement=-16 rS=1
mflr rD=0
stw rA=1 displacement=20 rS=0
lwz rD=5 rA=13 displacement=-31852
lbz rD=0 rA=5 displacement=31
extsb rS=0 rA=0 Rc=1
bc BO=4 BI=2 LK=0 target=800681d4 AA=0
lbz rD=0 rA=3 displacement=1866
extsb rS=0 rA=0 Rc=0
add rD=0 rA=0 rB=4 Rc=0
cmpi BF=0 L=0 rA=0 immediate=127
bc BO=4 BI=1 LK=0 target=800681b8 AA=0
addi rD=0 rA=0 immediate=127
stb rS=0 rA=3 displacement=1866
b target=800681d0 AA=0
cmpi BF=0 L=0 rA=0 immediate=-127
bc BO=4 BI=0 LK=0 target=800681cc AA=0
addi rD=0 rA=0 immediate=-127
stb rS=0 rA=3 displacement=1866
b target=800681d0 AA=0
stb rS=0 rA=3 displacement=1866
bl target=8006826c AA=0
lwz rD=0 rA=1 displacement=20
mtlr rS=0
addi rD=1 rA=1 immediate=16
blr
""",
    0x8006826c: """
lwz rD=0 rA=3 displacement=1196
cmpli BF=0 L=0 rA=0 immediate=0
bclr BO=12 BI=2 BH=0 LK=0
lbz rD=6 rA=3 displacement=1866
lbz rD=5 rA=3 displacement=1869
extsb rS=6 rA=4 Rc=0
extsb rS=5 rA=0 Rc=0
cmp BF=0 L=0 rA=4 rB=0
bc BO=4 BI=1 LK=0 target=80068298 AA=0
stb rS=5 rA=3 displacement=1867
b target=800682b4 AA=0
lbz rD=5 rA=3 displacement=1868
extsb rS=5 rA=0 Rc=0
cmp BF=0 L=0 rA=4 rB=0
bc BO=4 BI=0 LK=0 target=800682b0 AA=0
stb rS=5 rA=3 displacement=1867
b target=800682b4 AA=0
stb rS=6 rA=3 displacement=1867
lwz rD=5 rA=3 displacement=1196
addis rD=4 rA=0 immediate=-32701
lbz rD=0 rA=3 displacement=1867
addi rD=4 rA=4 immediate=14816
lbz rD=5 rA=5 displacement=163
extsb rS=0 rA=0 Rc=0
rlwinm rS=5 rA=5 SH=2 MB=0 ME=29 Rc=0
mulli rD=0 rA=0 immediate=12
lwzx rD=4 rA=4 rB=5
add rD=4 rA=4 rB=0 Rc=0
lfs fD=0 rA=4 displacement=0
stfs rA=3 displacement=184 fS=0
lfs fD=0 rA=4 displacement=4
stfs rA=3 displacement=7632 fS=0
lfs fD=0 rA=4 displacement=8
stfs rA=3 displacement=1528 fS=0
blr
""",
}


def expected_facts(entry):
    facts = []
    for index, line in enumerate(EXPECTED[entry].strip().splitlines()):
        mnemonic, *fields = line.split()
        fields = dict(item.split('=') for item in fields)
        fields = {key: value if key == 'target' else int(value) for key, value in fields.items()}
        facts.append(dict(address=f'{entry + index * 4:08x}', mnemonic=mnemonic, **fields))
    return facts


class SyntheticTests(unittest.TestCase):
    def test_exact_selections_and_unchanged_shared_scope(self):
        self.assertEqual([(pc, n) for pc, n, _ in a.RANGES], [(0x8006817c, 0x68), (0x8006826c, 0x8c)])
        self.assertEqual(a.POINTER_CELLS, ((0, 0x804339e0, 0x802dd5a0), (1, 0x804339e4, 0x802dd720)))
        self.assertEqual([(s, t, pc) for s, t, pc, _ in a.ROWS], [
            (0, 15, 0x802dd654), (0, 16, 0x802dd660), (0, 17, 0x802dd66c),
            (1, 15, 0x802dd7d4), (1, 16, 0x802dd7e0), (1, 17, 0x802dd7ec)])
        self.assertEqual([len(expected_facts(pc)) for pc, _, _ in a.RANGES], [26, 35])
        self.assertEqual(len(a.c.TARGETS), 12)
        self.assertEqual(a.command.MAPPINGS, (
            ('MAIN_.text1', 1, 0x20000000000055e0, 2796416, 21),
            ('MAIN_.data3', 5, 0x20000000002bae60, 0xf42c0, 199),
            ('MAIN_.data5', 7, 0x2000000000436a20, 27360, 263)))

    def test_decoder_bounds_and_unselected_forms(self):
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)
        for word in (0, 0x4e800421, d_form(42, 0, 3, 0), d_form(44, 0, 3, 0),
                     d_form(50, 0, 2, 0), (59 << 26) | (25 << 1),
                     (31 << 26) | (87 << 1), (31 << 26) | (922 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))

    def test_reserved_fields_and_non32bit_comparisons_rejected(self):
        words = ((31 << 26) | (954 << 1) | (1 << 11),
                 (31 << 26) | (23 << 1) | 1, (31 << 26) | (1 << 21),
                 (31 << 26) | 1, (11 << 26) | (1 << 21), (10 << 26) | (2 << 21),
                 (19 << 26) | (12 << 21) | (2 << 16) | (16 << 1) | 1,
                 (19 << 26) | (12 << 21) | (2 << 16) | (16 << 1) | (1 << 11),
                 spr_form(339, reg=1), spr_form(467, spr=9), spr_form(339, record=1))
        for word in words:
            with self.subTest(word=word):
                with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_operand_direction_and_signedness_fields(self):
        for op, name, reg in ((32, 'lwz', 'rD'), (34, 'lbz', 'rD'), (36, 'stw', 'rS'),
                              (37, 'stwu', 'rS'), (38, 'stb', 'rS'), (48, 'lfs', 'fD'), (52, 'stfs', 'fS')):
            self.assertEqual(a.decode_selected(d_form(op, 7, 9, -2), 0),
                             dict(mnemonic=name, rA=9, displacement=-2, **{reg: 7}))
        for op, name, value in ((10, 'cmpli', 65535), (11, 'cmpi', -1), (7, 'mulli', -1)):
            expected = dict(mnemonic=name, rA=7, immediate=value)
            expected.update(dict(rD=8) if op == 7 else dict(BF=2, L=0))
            self.assertEqual(a.decode_selected(d_form(op, 8, 7, 65535), 0), expected)
        self.assertEqual(a.decode_selected((31 << 26) | (7 << 21) | (9 << 16) | (11 << 11) | (23 << 1), 0),
                         dict(mnemonic='lwzx', rD=7, rA=9, rB=11))
        self.assertEqual(a.decode_selected((19 << 26) | (12 << 21) | (2 << 16) | (16 << 1), 0),
                         dict(mnemonic='bclr', BO=12, BI=2, BH=0, LK=0))

    def test_ranges_refuse_invalid_selection_before_decode(self):
        for pc, width, _ in a.RANGES:
            for fields in ((21, pc + 4, width - 4), (21, pc, width + 4),
                           (21, pc, width - 4), (21.0, pc, width), (21, True, width), (21, pc, float(width))):
                with self.assertRaises(a.c.FormatError): a.range_evidence(None, *fields)
            with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
                a.range_evidence(None, 22, pc, width)
            for raw, reason in ((bytes(width), 'digest'), (bytes(width - 4), 'byte width')):
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, reason):
                        a.range_evidence(FakeDB(raw), 21, pc, width)
                    decoder.assert_not_called()
        pc, width, _ = a.RANGES[0]
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.range_evidence(None, 21, pc, width)
        raw = bytes(4)
        with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(raw), 21, pc, 4)
        for pc, width in ((a.TEXT_START + 1, 4), (a.TEXT_START, 3), (a.TEXT_START, 0),
                          (a.TEXT_START - 4, 4), (a.TEXT_START + a.TEXT_LENGTH, 4)):
            with patch.object(a, 'RANGES', ((pc, width, 'unused'),)):
                with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
                    a.range_evidence(None, 21, pc, width)

    def test_fixed_pointer_scope_mapping_and_bits(self):
        for selector in (-1, 2, 255, True, 0.0):
            with self.assertRaises(a.c.FormatError): a.pointer_cell_evidence(None, a.DATA4_MAPPING, selector)
        with patch.object(a, 'POINTER_CELLS', a.POINTER_CELLS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.pointer_cell_evidence(None, a.DATA4_MAPPING, 0)
        for mapping in (a.DATA3_MAPPING, list(a.DATA4_MAPPING), a.DATA4_MAPPING[:-1] + (263,)):
            with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                a.pointer_cell_evidence(None, mapping, 0)
        for raw, reason in ((bytes(4), 'value mismatch'), (bytes(3), 'byte width')):
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.pointer_cell_evidence(FakeDB(raw), a.DATA4_MAPPING, 0)
        for address in (0x804339e1, a.DATA4_MAPPING[0] - 4, a.DATA4_MAPPING[1]):
            with patch.object(a, 'POINTER_CELLS', ((0, address, 0x802dd5a0),)):
                with self.assertRaisesRegex(a.c.FormatError, 'alignment/index/bounds'):
                    a.pointer_cell_evidence(None, a.DATA4_MAPPING, 0)
        db = FakeDB(bytes.fromhex('802dd5a0'))
        self.assertEqual(a.pointer_cell_evidence(db, a.DATA4_MAPPING, 0)['target'], '802dd5a0')
        self.assertEqual(db.calls, [(262, 1088, 4, 11040)])  # Exactly one cell; no target read.

    def test_fixed_row_scope_schema_mapping_and_bits(self):
        for selector, tier in ((2, 16), (255, 16), (0, -128), (0, 14), (0, 18), (0, 32),
                               (1, 127), (True, 16), (0, 16.0)):
            with self.assertRaises(a.c.FormatError): a.row_evidence(None, a.DATA3_MAPPING, selector, tier)
        with patch.object(a, 'ROWS', a.ROWS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.row_evidence(None, a.DATA3_MAPPING, 0, 16)
        with patch.object(a, 'POINTER_CELLS', ()):
            with self.assertRaisesRegex(a.c.FormatError, 'identity not allowlisted'):
                a.row_evidence(None, a.DATA3_MAPPING, 0, 16)
        for mapping in (a.DATA4_MAPPING, list(a.DATA3_MAPPING), a.DATA3_MAPPING[:-1] + (200,)):
            with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
                a.row_evidence(None, mapping, 0, 16)
        for raw, reason in ((bytes(12), 'bits mismatch'), (bytes(11), 'byte width')):
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.row_evidence(FakeDB(raw), a.DATA3_MAPPING, 0, 16)
        for address in (0x802dd661, a.DATA3_MAPPING[0] - 4, a.DATA3_MAPPING[1]):
            with patch.object(a, 'ROWS', ((0, 16, address, ('3f800000',) * 3),)):
                with self.assertRaisesRegex(a.c.FormatError, 'alignment/index/bounds'):
                    a.row_evidence(None, a.DATA3_MAPPING, 0, 16)
        for bits in ((), ('3f800000',) * 2, ('3f800000',) * 4, ["3f800000"] * 3, ('bad',) * 3):
            with patch.object(a, 'ROWS', ((0, 16, 0x802dd660, bits),)):
                with self.assertRaisesRegex(a.c.FormatError, 'bits schema'):
                    a.row_evidence(None, a.DATA3_MAPPING, 0, 16)
        db = FakeDB(bytes.fromhex('3f800000' * 3))
        result = a.row_evidence(db, a.DATA3_MAPPING, 0, 16)
        self.assertEqual([x['value'] for x in result['cells']], [1.0] * 3)
        self.assertEqual(db.calls, [(199, 141312, 12, 0xf42c0)])

    def test_authentication_and_schema_precede_parser_and_reads(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as ranges, \
                    patch.object(a, 'pointer_cell_evidence') as pointers, patch.object(a, 'row_evidence') as rows:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                for mocked in (parser, ranges, pointers, rows): mocked.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty', 'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_all_mapping_guards_precede_fixed_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        blocks[6] = ['MAIN_.data4', None, None, 0, 0x20000000004335a0, 11040, 0]
        subs[6] = [6, 2, 11040, 0, 262, 0]
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image', 'data3', 'data5',
                       'data4-missing', 'data4-address', 'data4-length', 'data4-root', 'data4-type', 'data4-offset', 'data4-duplicate'):
            aa, bb, ss = copy.deepcopy((auth, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'data3': ss[5][4] += 1
            if target == 'data5': ss[7][4] += 1
            if target == 'data4-missing': del bb[6]
            if target == 'data4-address': bb[6][4] += 4
            if target == 'data4-length': bb[6][5] -= 4
            if target == 'data4-root': ss[6][4] += 1
            if target == 'data4-type': ss[6][1] += 1
            if target == 'data4-offset': ss[6][5] += 1
            if target == 'data4-duplicate': ss[99] = copy.deepcopy(ss[6])
            with self.subTest(target=target), patch.object(a.c, 'inspect', return_value=aa), \
                    patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as ranges, \
                    patch.object(a, 'pointer_cell_evidence') as pointers, patch.object(a, 'row_evidence') as rows:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                for mocked in (ranges, pointers, rows): mocked.assert_not_called()

    def test_no_arbitrary_cli_or_pointer_following_options(self):
        for option in (['--address', '8006826c'], ['--width', '140'], ['--raw'], ['--execute'],
                       ['--pointer', '804339e0'], ['--follow-pointer'], ['--selector', '0'], ['--tier', '16']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
                inspect.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('both existing local archived snapshots required')
        cls.results, cls.dbs = [], []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
            cls.dbs.append(a.c.GBF(data))
        cls.facts = {int(f['address'], 16): f for span in cls.results[0]['ranges'] for f in span['instructions']}

    def test_both_archives_exact_coverage_and_operands(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        for key in ('ranges', 'pointer_cells', 'rows', 'function_coverage', 'data_mappings', 'table_scope', 'r13_basis'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        self.assertEqual(len(self.facts), 61)
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual([x['represented_instructions'] for x in result['function_coverage']], [26, 35])
            self.assertEqual(result['table_scope'], dict(authenticated_selectors=[0, 1],
                authenticated_tiers=[15, 16, 17], extent_proven=False, descriptor_provenance_proven=False,
                runtime_pointer_ownership_proven=False))
            for coverage in result['function_coverage']:
                self.assertEqual((coverage['unrepresented_instructions'], coverage['unrepresented_ranges']), (0, []))
            for span in result['ranges']:
                self.assertEqual(span['instructions'], expected_facts(int(span['address'], 16)))
                for item in [span] + span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes')))

    def test_extent_map_c_next_and_return_agree(self):
        research = Path(__file__).resolve().parents[2]
        mapping = (research / 'symbols/GG4E-CSM-20220412.map').read_text()
        source = (research / 'decomp/ghidra-export/chunk_0008.c').read_text()
        for entry, width, _ in a.RANGES:
            start = source.index(f'// ==== {entry:08x} ')
            end = source.index('// ==== ', start + 8)
            self.assertTrue(source[end:].startswith(f'// ==== {entry + width:08x} '))
            self.assertIn('void ', source[start:end])
            line = next(line for line in mapping.splitlines() if line.startswith(f'{entry:08x} '))
            self.assertEqual(int(line.split()[1], 16), width)
            self.assertEqual(self.facts[entry + width - 4]['mnemonic'], 'blr')

    def test_pointer_cells_and_exact_float_rows(self):
        result = self.results[0]
        self.assertEqual([(x['selector'], x['address'], x['target']) for x in result['pointer_cells']],
                         [(0, '804339e0', '802dd5a0'), (1, '804339e4', '802dd720')])
        expected = {
            (0, 15): [('3f4f5c29', 0.8100000023841858), ('3f800000', 1.0), ('3f4f5c29', 0.8100000023841858)],
            (0, 16): [('3f800000', 1.0)] * 3,
            (0, 17): [('3fb33333', 1.399999976158142), ('3f7ae148', 0.9800000190734863), ('3fb33333', 1.399999976158142)],
            (1, 15): [('3f4f5c29', 0.8100000023841858), ('3f800000', 1.0), ('3f4f5c29', 0.8100000023841858)],
            (1, 16): [('3f800000', 1.0)] * 3,
            (1, 17): [('3f99999a', 1.2000000476837158), ('3f7ae148', 0.9800000190734863), ('3f99999a', 1.2000000476837158)],
        }
        for row in result['rows']:
            self.assertEqual([(x['bits'], x['value']) for x in row['cells']], expected[row['selector'], row['tier']])
            self.assertEqual([x['offset'] for x in row['cells']], [0, 4, 8])
            self.assertEqual(int(row['address'], 16), int(row['base'], 16) + row['tier'] * 12)
        f = self.facts
        self.assertEqual(((f[0x800682b8]['immediate'] << 16) + f[0x800682c0]['immediate']) & 0xffffffff, 0x804339e0)
        self.assertEqual(f[0x80068188]['displacement'] + 0x8043b5a0, 0x80433934)

    def test_delta_gate_signed_clamp_store_then_call(self):
        f = self.facts
        self.assertEqual((f[0x8006818c]['displacement'], f[0x80068190]['mnemonic'], f[0x80068190]['Rc']), (0x1f, 'extsb', 1))
        self.assertEqual(f[0x80068194]['target'], '800681d4')
        self.assertEqual(f[0x80068198]['displacement'], 0x74a)
        self.assertEqual(f[0x8006819c]['mnemonic'], 'extsb')
        self.assertEqual(f[0x800681a0], dict(address='800681a0', mnemonic='add', rD=0, rA=0, rB=4, Rc=0))
        self.assertEqual([f[pc]['immediate'] for pc in (0x800681a4, 0x800681b8)], [127, -127])
        self.assertEqual([(f[pc]['BO'], f[pc]['BI']) for pc in (0x800681a8, 0x800681bc)], [(4, 1), (4, 0)])
        self.assertEqual([f[pc]['displacement'] for pc in (0x800681b0, 0x800681c4, 0x800681cc)], [0x74a] * 3)
        self.assertEqual(f[0x800681d0], dict(address='800681d0', mnemonic='bl', target='8006826c', AA=0))
        self.assertFalse(any(x.get('rD') == 4 or (x['mnemonic'] == 'extsb' and x.get('rS') == 4)
                             for pc, x in f.items() if 0x8006817c <= pc < 0x800681e4))

    def test_refresh_null_gate_upper_first_clamp_and_lazy_reloads(self):
        f = self.facts
        self.assertEqual(f[0x8006826c]['displacement'], 0x4ac)
        self.assertEqual(f[0x80068270]['mnemonic'], 'cmpli')
        self.assertEqual(f[0x80068274], dict(address='80068274', mnemonic='bclr', BO=12, BI=2, BH=0, LK=0))
        self.assertEqual([f[pc]['displacement'] for pc in (0x80068278, 0x8006827c, 0x80068298)], [0x74a, 0x74d, 0x74c])
        self.assertEqual([(f[pc]['BO'], f[pc]['BI']) for pc in (0x8006828c, 0x800682a4)], [(4, 1), (4, 0)])
        self.assertEqual([f[pc]['displacement'] for pc in (0x80068290, 0x800682a8, 0x800682b0)], [0x74b] * 3)
        self.assertEqual(f[0x80068294]['target'], '800682b4')
        self.assertEqual([f[pc]['displacement'] for pc in (0x800682b4, 0x800682bc, 0x800682c4)], [0x4ac, 0x74b, 0xa3])
        self.assertEqual(f[0x800682c8], dict(address='800682c8', mnemonic='extsb', rS=0, rA=0, Rc=0))
        self.assertEqual(f[0x800682cc], dict(address='800682cc', mnemonic='rlwinm', rS=5, rA=5, SH=2, MB=0, ME=29, Rc=0))
        self.assertEqual(f[0x800682d0]['immediate'], 12)
        self.assertEqual(f[0x800682d4], dict(address='800682d4', mnemonic='lwzx', rD=4, rA=4, rB=5))
        self.assertEqual([f[pc]['mnemonic'] for pc in range(0x800682dc, 0x800682f4, 4)], ['lfs', 'stfs'] * 3)
        self.assertEqual([f[pc]['displacement'] for pc in range(0x800682dc, 0x800682f4, 4)], [0, 0xb8, 4, 0x1dd0, 8, 0x5f8])

    def test_constructor_is_c_context_only_not_selected_instructions_or_defaults(self):
        source = (Path(__file__).resolve().parents[2] / 'decomp/ghidra-export/chunk_0006.c').read_text()
        start = source.index('// ==== 80056180 ')
        # This function is the final entry in chunk_0006.c.
        body = source[start:]
        expected = ('*(undefined1 *)(param_1 + 0x74a) = 0x10;',
                    '*(undefined1 *)(param_1 + 0x74d) = *(undefined1 *)(*(int *)(param_1 + 0x4ac) + 0xa1);',
                    '*(undefined1 *)(param_1 + 0x74c) = *(undefined1 *)(*(int *)(param_1 + 0x4ac) + 0xa2);',
                    'refresh_actor_param_tier_table(param_1);')
        positions = [body.index(line) for line in expected]
        self.assertEqual(positions, sorted(positions))
        self.assertFalse(any(0x80056180 <= pc < 0x800562b8 for pc in self.facts))

    def test_each_instruction_mutation_rejected_before_decode(self):
        for db in self.dbs:
            for pc, width, _ in a.RANGES:
                raw = db.chain(21, pc - a.TEXT_START, width, a.TEXT_LENGTH)[0]
                for offset in range(0, width, 4):
                    changed = bytearray(raw)
                    changed[offset + 3] ^= 1
                    with patch.object(a, 'decode_selected') as decoder:
                        with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                            a.range_evidence(FakeDB(changed), 21, pc, width)
                        decoder.assert_not_called()

    def test_each_fixed_pointer_and_row_byte_mutation_rejected(self):
        for db in self.dbs:
            for selector, address, _ in a.POINTER_CELLS:
                raw = db.chain(262, address - a.DATA4_MAPPING[0], 4, 11040)[0]
                for offset in range(4):
                    changed = bytearray(raw)
                    changed[offset] ^= 1
                    with self.assertRaisesRegex(a.c.FormatError, 'value mismatch'):
                        a.pointer_cell_evidence(FakeDB(changed), a.DATA4_MAPPING, selector)
            for selector, tier, address, _ in a.ROWS:
                raw = db.chain(199, address - a.DATA3_MAPPING[0], 12, 0xf42c0)[0]
                for offset in range(12):
                    changed = bytearray(raw)
                    changed[offset] ^= 1
                    with self.assertRaisesRegex(a.c.FormatError, 'bits mismatch'):
                        a.row_evidence(FakeDB(changed), a.DATA3_MAPPING, selector, tier)


if __name__ == '__main__':
    unittest.main()
