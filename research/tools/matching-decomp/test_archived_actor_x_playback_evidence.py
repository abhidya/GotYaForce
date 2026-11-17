#!/usr/bin/env python3
"""All 128 instruction operands, two pointer cells, one row and refusal guards."""
import contextlib
import copy
import hashlib
import io
import json
import os
from pathlib import Path
import re
import struct
import unittest
from unittest.mock import patch

import read_archived_actor_x_playback_evidence as a


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


def d_form(op, d, ra, immediate):
    return op << 26 | d << 21 | ra << 16 | (immediate & 65535)


def spr_form(xo, d=0, spr=8, rc=0):
    return 31 << 26 | d << 21 | (spr & 31) << 16 | (spr >> 5) << 11 | xo << 1 | rc


def ops(text):
    """Explicit independent expected operands, neither decoder nor executor."""
    fields = {
        'stwu': 'rS rA displacement', 'stw': 'rS rA displacement',
        'stb': 'rS rA displacement', 'lwz': 'rD rA displacement',
        'lbz': 'rD rA displacement', 'addi': 'rD rA immediate',
        'mflr': 'rD', 'mtlr': 'rS', 'rlwinm': 'rS rA SH MB ME Rc',
        'or': 'rS rA rB Rc', 'ori': 'rS rA immediate',
        'cmpi': 'BF L rA immediate', 'blr': '',
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
            item.update(AA=0, LK=int(name == 'bl'))
        if name == 'blr':
            item.update(BO=20, BI=0, BH=0, LK=0)
        result.append(item)
    return result


EXPECTED = {
    0x80059cd0: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
addi 0 0 1
stw 31 1 12
or 3 31 3 0
stb 0 3 0x588
lwz 0 3 0x5e0
rlwinm 0 0 0 25 25 1
bc 12 2 80059da4
bl 800699d8
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 80069814
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 80069210
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 800693fc
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 800696f4
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 8006965c
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 800695c4
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 8006952c
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 800691d8
cmpi 0 0 3 0
bc 4 2 80059e1c
lbz 0 31 0x661
cmpi 0 0 0 6
bc 4 2 80059e1c
or 31 3 31 0
bl 80068f9c
cmpi 0 0 3 0
bc 12 2 80059e1c
b 80059e1c
bl 80068df8
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 800699d8
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 80069814
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 800696f4
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 800690a0
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 80069038
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 80069354
cmpi 0 0 3 0
bc 4 2 80059e1c
or 31 3 31 0
bl 80068f9c
cmpi 0 0 3 0
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
    0x800690a0: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 0x57a
rlwinm 0 0 0 25 25 1
bc 4 2 800690c8
addi 3 0 0
b 8006912c
lwz 0 31 0x5d4
rlwinm 0 0 0 31 31 1
bc 4 2 800690dc
addi 3 0 0
b 8006912c
lwz 0 31 0x5b4
rlwinm 0 0 0 23 23 1
bc 4 2 800690f0
addi 3 0 0
b 8006912c
addi 4 0 5
bl 8006a750
cmpi 0 0 3 0
bc 12 2 80069128
lwz 0 31 0x5e0
or 31 3 31 0
rlwinm 0 0 0 8 15 0
stw 0 31 0x5e0
bl 8005c080
lwz 0 31 0x5e0
addi 3 0 1
ori 0 0 0x2000
stw 0 31 0x5e0
b 8006912c
addi 3 0 0
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
}


class SyntheticTests(unittest.TestCase):
    def test_exact_selections_and_witness_counts(self):
        self.assertEqual([(pc, width) for pc, width, _ in a.RANGES],
                         [(0x80059cd0, 352), (0x800690a0, 160)])
        self.assertEqual([(label, pc, target) for label, pc, target, _ in a.CELLS],
                         [('signed-cue44', 0x802d33b0, 0x80059cd0),
                          ('double-constructor-4f0-source', 0x802d3b50, 0x802d3ff8)])
        self.assertEqual([row[:4] for row in a.ROWS], [(0x802d4050, 2, 61, 0)])
        for pc, width, _ in a.RANGES:
            self.assertEqual(len(EXPECTED[pc]), width // 4)
        self.assertEqual(sum(map(len, EXPECTED.values())), 128)

    def test_word_and_pc_bounds(self):
        for word in (-1, 1 << 32, True, 1.0, '0'):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'):
                a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0, '0'):
            with self.assertRaisesRegex(a.c.FormatError, 'PC bounds'):
                a.decode_selected(0, pc)

    def test_scalar_directions_and_signed_immediates(self):
        for op, name, reg in ((32, 'lwz', 'rD'), (34, 'lbz', 'rD'), (36, 'stw', 'rS'),
                              (37, 'stwu', 'rS'), (38, 'stb', 'rS')):
            for value in (-32768, -1, 0, 32767):
                self.assertEqual(a.decode_selected(d_form(op, 7, 3, value), 0),
                                 dict(mnemonic=name, **{reg: 7}, rA=3, displacement=value))
        self.assertEqual(a.decode_selected(d_form(14, 7, 3, -1), 0),
                         dict(mnemonic='addi', rD=7, rA=3, immediate=-1))
        self.assertEqual(a.decode_selected(d_form(24, 7, 3, 65535), 0),
                         dict(mnemonic='ori', rS=7, rA=3, immediate=65535))
        self.assertEqual(a.decode_selected(d_form(11, 0, 3, -1), 0),
                         dict(mnemonic='cmpi', BF=0, L=0, rA=3, immediate=-1))
        for bad in (d_form(37, 1, 0, -16), d_form(11, 1, 3, 0),
                    d_form(11, 2, 3, 0), d_form(11, 4, 3, 0)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)

    def test_branch_fields_and_relative_wrap(self):
        self.assertEqual(a.decode_selected(0x4e800020, 0),
                         dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
        for bad in (0x4e800021, 0x4c820020, 0x4e800820, 0x4e802020):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for lk in (0, 1):
            self.assertEqual(a.decode_selected(0x4bfffffc | lk, 0),
                             dict(mnemonic='bl' if lk else 'b', target='fffffffc', AA=0, LK=lk))
        with self.assertRaises(a.c.FormatError): a.decode_selected(0x48000002, 0)
        for bo in (4, 12):
            word = 16 << 26 | bo << 21 | 2 << 16 | 0xfffc
            self.assertEqual(a.decode_selected(word, 0x80001000),
                             dict(mnemonic='bc', BO=bo, BI=2, LK=0, target='80000ffc', AA=0))
            for bad in (word | 1, word | 2, word ^ (1 << 16)):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)

    def test_rotate_or_link_and_unselected_forms(self):
        word = 21 << 26 | 4 << 21 | 3 << 16 | 2 << 11 | 8 << 6 | 15 << 1 | 1
        self.assertEqual(a.decode_selected(word, 0),
                         dict(mnemonic='rlwinm', rS=4, rA=3, SH=2, MB=8, ME=15, Rc=1))
        word = 31 << 26 | 4 << 21 | 3 << 16 | 5 << 11 | 444 << 1 | 1
        self.assertEqual(a.decode_selected(word, 0), dict(mnemonic='or', rS=4, rA=3, rB=5, Rc=1))
        for xo, name, reg in ((339, 'mflr', 'rD'), (467, 'mtlr', 'rS')):
            self.assertEqual(a.decode_selected(spr_form(xo), 0), dict(mnemonic=name, **{reg: 0}))
            for bad in (spr_form(xo, 1), spr_form(xo, spr=9), spr_form(xo, rc=1)):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for word in (0, 0x4e800421, d_form(10, 0, 4, 0), d_form(15, 3, 4, 0),
                     d_form(40, 3, 4, 0), d_form(42, 3, 4, 0),
                     (31 << 26) | (266 << 1), (59 << 26) | (29 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))

    def test_no_unselected_or_duplicate_reads(self):
        for pc, size, _ in a.RANGES:
            for address, width in ((pc + 4, size - 4), (pc, size + 4), (pc, size - 4),
                                   (pc - 4, 4), (pc + size, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, address, width)
            with patch.object(a, 'RANGES', a.RANGES * 2):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, pc, size)
        for pc in (0x802d33ac, 0x802d33b4, 0x802d3300, 0x80059cd0):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.cell_evidence(None, a.DATA3_MAPPING, pc)
        with patch.object(a, 'CELLS', a.CELLS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.cell_evidence(None, a.DATA3_MAPPING, 0x802d33b0)
        for pc, width in ((0x802d404e, 2), (0x802d4052, 2), (0x802d4050, 4), (0x802d3ff8, 96)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.row_evidence(None, a.DATA3_MAPPING, pc, width)
        with patch.object(a, 'ROWS', a.ROWS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.row_evidence(None, a.DATA3_MAPPING, 0x802d4050, 2)

    def test_types_and_exact_mappings_precede_payload(self):
        for bad in (True, 1.0, '4', None):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.range_evidence(None, a.TEXT_MAPPING, bad, 352)
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.range_evidence(None, a.TEXT_MAPPING, 0x80059cd0, bad)
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.cell_evidence(None, a.DATA3_MAPPING, bad)
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.row_evidence(None, a.DATA3_MAPPING, bad, 2)
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.row_evidence(None, a.DATA3_MAPPING, 0x802d4050, bad)
        for reader, mapping, args in ((a.range_evidence, a.TEXT_MAPPING, (0x80059cd0, 352)),
                                      (a.cell_evidence, a.DATA3_MAPPING, (0x802d33b0,)),
                                      (a.row_evidence, a.DATA3_MAPPING, (0x802d4050, 2))):
            for bad in (list(mapping), mapping[:-1] + (22,), (mapping[0] + 4,) + mapping[1:],
                        mapping[:2] + (float(mapping[2]),) + mapping[3:]):
                with self.assertRaisesRegex(a.c.FormatError, 'mapping'):
                    reader(None, bad, *args)

    def test_width_digest_instruction_and_span_guards(self):
        for pc, width, _ in a.RANGES:
            for raw, reason in ((bytes(width), 'digest'), (bytes(width - 4), 'byte width'),
                                 (bytes(width + 4), 'byte width')):
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, reason):
                        a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, pc, width)
                    decoder.assert_not_called()
        for words, reason in (([0], 'unselected instruction'),
                              ([0x38600000], 'terminal return'),
                              ([0x48001000, 0x4e800020], 'outside fixed span')):
            raw = struct.pack('>' + 'I' * len(words), *words)
            with patch.object(a, 'RANGES', ((0x80059cd0, len(raw), hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x80059cd0, len(raw))
        raw = struct.pack('>I', 0x4e800020)
        with patch.object(a, 'RANGES', ((0x80059cd0, 4, hashlib.sha256(raw).hexdigest()),)):
            db = FakeDB(raw)
            result = a.range_evidence(db, a.TEXT_MAPPING, 0x80059cd0, 4)
            self.assertEqual(db.calls, [(21, 345840, 4, 2796416)])
            self.assertNotIn('raw', result)

    def test_exact_cell_target_no_following(self):
        for _, pc, target, _ in a.CELLS:
            raw = struct.pack('>I', target)
            db = FakeDB(raw)
            self.assertEqual(a.cell_evidence(db, a.DATA3_MAPPING, pc)['target'], f'{target:08x}')
            self.assertEqual(db.calls, [(199, pc - 0x802bae60, 4, 1000128)])
            for bad, reason in ((raw[:-1], 'byte width'), (bytes(4), 'digest')):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.cell_evidence(FakeDB(bad), a.DATA3_MAPPING, pc)
        with patch.object(a, 'CELLS', (('synthetic', 0x802d33b0, 0, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'target mismatch'):
                a.cell_evidence(FakeDB(raw), a.DATA3_MAPPING, 0x802d33b0)

    def test_exact_fixed_row_values_width_hash_and_trace(self):
        raw = bytes((61, 0))
        db = FakeDB(raw)
        result = a.row_evidence(db, a.DATA3_MAPPING, 0x802d4050, 2)
        self.assertEqual((result['full_body_state'], result['upper_body_state']), (61, 0))
        self.assertEqual(result['sha256'], a.ROWS[0][4])
        self.assertEqual(db.calls, [(199, 102896, 2, 1000128)])
        for bad, reason in ((raw[:1], 'byte width'), (raw + bytes(2), 'byte width'),
                            (bytes((61, 62)), 'digest mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.row_evidence(FakeDB(bad), a.DATA3_MAPPING, 0x802d4050, 2)
        with patch.object(a, 'ROWS', ((0x802d4050, 2, 61, 62, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'values mismatch'):
                a.row_evidence(FakeDB(raw), a.DATA3_MAPPING, 0x802d4050, 2)

    def test_authentication_precedes_parsing_and_selection(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as ranges, \
                    patch.object(a, 'cell_evidence') as cells:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'):
                    a.inspect(bytes(32), digest)
                parser.assert_not_called(); ranges.assert_not_called(); cells.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty',
                       'data5 digest mismatch', 'executable metadata SHA/type mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), \
                    patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_actual_schema_failure_precedes_new_reads(self):
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for field, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[field] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'cell_evidence') as cells:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'):
                    a.inspect(data, digest)
                parser.return_value.rows.assert_not_called()
                ranges.assert_not_called(); cells.assert_not_called()

    def test_actual_mapping_failures_precede_new_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image',
                       'data5root', 'data5offset', 'data5length',
                       'data3root', 'data3offset', 'data3length'):
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
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'cell_evidence') as cells:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called(); cells.assert_not_called()

    def test_shared_allowlists_and_cli_remain_narrow(self):
        for pc, width, _ in a.RANGES:
            self.assertNotIn((pc, width), a.c.TARGETS)
            self.assertNotIn((pc, width), [row[:2] for row in a.command.RANGES])
            self.assertNotIn((pc, width), [row[:2] for row in a.normal.RANGES])
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.normal.range_evidence(None, a.TEXT_MAPPING, pc, width)
        for _, pc, _, _ in a.CELLS:
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.normal.cell_evidence(None, a.DATA3_MAPPING, pc)
        self.assertNotIn((0x802d4050, 2), a.c.TARGETS)
        for option in (['--address', '80059cd0'], ['--width', '352'], ['--target', '80059cd0'],
                       ['--raw'], ['--execute'], ['--follow']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2); inspect.assert_not_called()

    def test_independent_c_markers_and_absent_map_entries(self):
        root = Path(__file__).resolve().parents[3]
        text = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        rows = {int(pc, 16): int(size, 16) for pc, size in
                re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ', text, re.M)}
        for chunk, (pc, width, _) in zip(('0007', '0008'), a.RANGES):
            self.assertNotIn(pc, rows)
            source = (root / f'research/decomp/ghidra-export/chunk_{chunk}.c').read_text()
            self.assertIn(f'// ==== {pc:08x}  FUN_{pc:08x} ====', source)
            markers = [int(value, 16) for value in re.findall(r'^// ==== ([0-9a-f]{8}) ', source, re.M)]
            self.assertEqual(markers[markers.index(pc) + 1], pc + width)

    def test_independent_recorded_double_row_selection(self):
        root = Path(__file__).resolve().parents[3]
        recorded = json.loads((root / 'packages/combat/src/data/familyCueTablesFull.json').read_text())
        double = recorded['families']['0x8006f60c']
        self.assertEqual(double['cueTable'], '0x802d3ff8')
        self.assertEqual(double['members'], ['pl0003'])
        self.assertEqual(double['rows'][44], [61, 0])
        self.assertEqual(int(double['cueTable'], 16) + 44 * 2, a.ROWS[0][0])
        # This is a cross-check of existing recorded research, never a dynamic
        # source for the reader's selection or permission to dump another row.
        self.assertEqual(a.CELLS[1][1:3], (0x802d3b50, 0x802d3ff8))


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(path.is_file() for path in paths):
            raise unittest.SkipTest('local archives unavailable; never fetched')
        cls.results = []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))

    def test_every_instruction_every_operand_both_archives(self):
        for result in self.results:
            for span, (pc, width, digest) in zip(result['ranges'], a.RANGES):
                expected = [dict(address=f'{pc + index * 4:08x}', **item)
                            for index, item in enumerate(EXPECTED[pc])]
                self.assertEqual(span['instructions'], expected)
                self.assertEqual(span['sha256'], digest)
                self.assertEqual(span['end_exclusive'], f'{pc + width:08x}')
                self.assertEqual(span['width'], width)
            self.assertEqual(sum(x['represented_instructions'] for x in result['function_coverage']), 128)
            for coverage in result['function_coverage']:
                self.assertEqual(coverage['unrepresented_instructions'], 0)
                self.assertEqual(coverage['unrepresented_ranges'], [])
                self.assertIsNone(coverage['map_size'])

    def test_both_snapshots_agree_and_exact_physical_spans(self):
        self.assertEqual([r['snapshot'] for r in self.results], ['db.3.gbf', 'db.4.gbf'])
        for key in ('cells', 'rows', 'ranges', 'mappings', 'function_coverage'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        expected = ((199, 206, 99664, 1396, 3392890, 4),
                    (199, 206, 101616, 3348, 3394842, 4),
                    (199, 206, 102896, 4628, 3396122, 2),
                    (21, 43, 345840, 1902, 722804, 352),
                    (21, 46, 408256, 15184, 785238, 160))
        for result in self.results:
            selected = result['cells'] + result['rows'] + result['ranges']
            for item, (root, buf, offset, data_offset, physical, width) in zip(selected, expected):
                self.assertEqual(item['spans'], [dict(root_buffer=root, data_buffer=buf,
                    chain_offset=offset, data_offset=data_offset, physical_offset=physical,
                    length=width, obfuscated=True)])
            self.assertEqual(result['cells'][0]['target'], '80059cd0')
            self.assertEqual(result['cells'][0]['sha256'], a.CELLS[0][3])
            self.assertEqual(result['cells'][1]['target'], '802d3ff8')
            self.assertEqual(result['cells'][1]['sha256'], a.CELLS[1][3])
            self.assertEqual((result['rows'][0]['full_body_state'], result['rows'][0]['upper_body_state']), (61, 0))
            self.assertEqual(result['rows'][0]['sha256'], a.ROWS[0][4])

    def test_direct_calls_only_and_explicit_callee_omissions(self):
        for result in self.results:
            ranges = result['ranges']
            calls = [(row['address'], row['target']) for row in ranges[0]['instructions']
                     if row['mnemonic'] == 'bl']
            self.assertEqual(calls, [
                ('80059cf8', '800699d8'), ('80059d08', '80069814'),
                ('80059d18', '80069210'), ('80059d28', '800693fc'),
                ('80059d38', '800696f4'), ('80059d48', '8006965c'),
                ('80059d58', '800695c4'), ('80059d68', '8006952c'),
                ('80059d78', '800691d8'), ('80059d94', '80068f9c'),
                ('80059da4', '80068df8'), ('80059db4', '800699d8'),
                ('80059dc4', '80069814'), ('80059dd4', '800696f4'),
                ('80059de4', '800690a0'), ('80059df4', '80069038'),
                ('80059e04', '80069354'), ('80059e14', '80068f9c')])
            self.assertEqual([(row['address'], row['target']) for row in ranges[1]['instructions']
                              if row['mnemonic'] == 'bl'],
                             [('800690f4', '8006a750'), ('80069110', '8005c080')])
            self.assertEqual([span['address'] for span in ranges], ['80059cd0', '800690a0'])
            self.assertFalse(any(row['mnemonic'] == 'bctrl' for span in ranges for row in span['instructions']))


if __name__ == '__main__':
    unittest.main()
