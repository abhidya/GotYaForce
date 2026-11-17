#!/usr/bin/env python3
"""Manual inverse fixtures:46 instructions,188 bytes,strict three-read scope.

Expected semantic rows are independently authored, never produced by a
reader/report/archive during tests. Optional existing snapshots are not fetched.
"""
import contextlib
import copy
import hashlib
import io
import json
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_projectile_callback_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
RANGES = (
    (0x8007dcec, 152, 'ee9edd0cdc0d53686a872a42378eb638ee4b44fdf26e25f7259f6198f71b815a'),
    (0x8008aff0, 32, '8ea8cac06c446278fad05cfae1dbe3ee6b3a321f4bfd1168269ce88283bef951'),
)
CELLS = (('initial-state0', 0x802d6f98, 0x8007dd84,
          '82ff512b4b2bdffddacade1b434ca6436328ae1014d77deb3f0db087032876cd'),)
FIELDS = {'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement',
          'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement', 'lha': 'rD rA displacement',
          'lwzx': 'rD rA rB', 'addi': 'rD rA immediate', 'addis': 'rD rA immediate',
          'or': 'rS rA rB Rc', 'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS',
          'bl': 'target AA LK', 'bc': 'BO BI LK target AA', 'extsb': 'rS rA Rc',
          'cmpi': 'BF L rA immediate', 'cmp': 'BF L rA rB', 'blr': 'BO BI BH LK',
          'bclr': 'BO BI BH LK', 'bctrl': 'BO BI BH LK', 'rlwinm': 'rS rA SH MB ME Rc'}


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


EXPECTED = {0x8007dcec: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 0x18
lwz 3 3 0x90
extsb 0 0 0
cmpi 0 0 0 2
bc 4 0 0 8007dd4c 0
lbz 0 3 0x18
extsb 0 0 0
cmpi 0 0 0 2
bc 4 0 0 8007dd34 0
lha 3 3 0x3e8
lha 0 31 0x94
cmp 0 0 3 0
bc 12 2 0 8007dd4c 0
addi 0 0 2
or 31 3 31 0
stb 0 31 0x18
bl 8008aff0 0 1
addi 0 0 0
stb 0 31 0x82
lbz 0 31 0x18
addis 3 0 -32723
addi 4 3 28568
or 31 3 31 0
extsb 0 0 0
rlwinm 0 0 2 0 29 0
lwzx 12 4 0
mtctr 12
bctrl 20 0 0 1
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''), 0x8008aff0: ops('''
lbz 4 3 2
cmpi 0 0 4 3
bc 12 2 0 8008b004 0
extsb 4 0 1
bclr 4 2 0 0
addi 0 0 1
stb 0 3 0x1d8
blr 20 0 0 0
''')}


def encode(row, pc):
    """Independent PPC inverse, with no decoder/report dependency."""
    name = row['mnemonic']
    forms = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
             'stb': (38, 'rS', 'displacement'), 'lwz': (32, 'rD', 'displacement'),
             'lbz': (34, 'rD', 'displacement'), 'lha': (42, 'rD', 'displacement'),
             'addi': (14, 'rD', 'immediate'), 'addis': (15, 'rD', 'immediate')}
    if name in forms:
        opcode, reg, imm = forms[name]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name in ('mflr', 'mtlr', 'mtctr'):
        reg = 'rD' if name == 'mflr' else 'rS'
        spr = 9 if name == 'mtctr' else 8
        return 31 << 26 | row[reg] << 21 | (spr & 31) << 16 | (spr >> 5) << 11 | (339 if name == 'mflr' else 467) << 1
    if name in ('or', 'extsb', 'lwzx'):
        reg = 'rD' if name == 'lwzx' else 'rS'
        xo = {'or': 444, 'extsb': 954, 'lwzx': 23}[name]
        return 31 << 26 | row[reg] << 21 | row['rA'] << 16 | row.get('rB', 0) << 11 | xo << 1 | row.get('Rc', 0)
    if name in ('bl', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if name == 'bl':
            return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
        return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc | row['AA'] << 1 | row['LK']
    if name in ('blr', 'bclr', 'bctrl'):
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | (528 if name == 'bctrl' else 16) << 1 | row['LK']
    if name == 'cmpi':
        return 11 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name == 'cmp':
        return 31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['rB'] << 11
    if name == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    raise AssertionError(name)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
PAYLOADS = dict(BODIES)
PAYLOADS[0x802d6f98] = struct.pack('>I', 0x8007dd84)
SELECTIONS = ((a.range_evidence, TEXT_MAPPING, 0x8007dcec, (152,)),
              (a.range_evidence, TEXT_MAPPING, 0x8008aff0, (32,)),
              (a.cell_evidence, DATA3_MAPPING, 0x802d6f98, ()))
EXPECTED_READS = [(21, 493324, 152, 2796416), (21, 547344, 32, 2796416), (199, 115000, 4, 1000128)]


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_exact_inventory_mappings_and_initial_cell_arithmetic(self):
        self.assertEqual(a.RANGES, RANGES)
        self.assertEqual(a.CELLS, CELLS)
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(a.DATA3_MAPPING, DATA3_MAPPING)
        self.assertEqual(sum(map(len, PAYLOADS.values())), 188)
        self.assertEqual(0x802d6f98 + 0 * 4, CELLS[0][1])
        self.assertTrue(set(PAYLOADS).isdisjoint({0x8007dd84, 0x8007e698, 0x802d6f9c, 0x802d6fa0}))

    def test_all46_operands_independent_inverse_and_hashes(self):
        mutations = 0
        for pc, width, digest in RANGES:
            rows, body = EXPECTED[pc], BODIES[pc]
            self.assertEqual(len(rows), width // 4)
            self.assertEqual(len(body), width)
            self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
            result = a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
            self.assertEqual(result['instructions'], [dict(address=f'{pc + i * 4:08x}', **row)
                                                      for i, row in enumerate(rows)])
            for i, row in enumerate(rows):
                address = pc + i * 4
                word = encode(row, address)
                self.assertEqual(a.decode_selected(word, address), row)
                for bit in range(32):
                    mutations += 1
                    changed = word ^ 1 << bit
                    try: decoded = a.decode_selected(changed, address)
                    except a.c.FormatError: continue
                    if decoded is not None:
                        self.assertNotEqual(decoded, row, (hex(address), bit))
                        self.assertEqual(encode(decoded, address), changed, (hex(address), bit))
        self.assertEqual(mutations, 1472)

    def test_guard_source_order_signedness_reload_and_indirect_dispatch(self):
        at = {0x8007dcec + i * 4: row for i, row in enumerate(EXPECTED[0x8007dcec])}
        self.assertEqual(at[0x8007dd04], dict(mnemonic='lwz', rD=3, rA=3, displacement=0x90))
        self.assertEqual([at[pc]['rA'] for pc in (0x8007dd0c, 0x8007dd1c)], [0, 0])
        self.assertEqual([at[pc]['immediate'] for pc in (0x8007dd0c, 0x8007dd1c)], [2, 2])
        self.assertEqual(at[0x8007dd24], dict(mnemonic='lha', rD=3, rA=3, displacement=0x3e8))
        self.assertEqual(at[0x8007dd28], dict(mnemonic='lha', rD=0, rA=31, displacement=0x94))
        self.assertEqual([(pc, row['displacement']) for pc, row in at.items()
                          if row['mnemonic'] == 'stb'], [(0x8007dd3c, 0x18), (0x8007dd48, 0x82)])
        self.assertEqual(at[0x8007dd40]['target'], '8008aff0')
        self.assertEqual(at[0x8007dd4c], dict(mnemonic='lbz', rD=0, rA=31, displacement=0x18))
        self.assertEqual(((at[0x8007dd50]['immediate'] << 16) + at[0x8007dd54]['immediate']) & 0xffffffff, 0x802d6f98)
        self.assertEqual(at[0x8007dd5c], dict(mnemonic='extsb', rS=0, rA=0, Rc=0))
        self.assertEqual(at[0x8007dd60], dict(mnemonic='rlwinm', rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0))
        self.assertEqual(at[0x8007dd64], dict(mnemonic='lwzx', rD=12, rA=4, rB=0))
        self.assertEqual(at[0x8007dd68], dict(mnemonic='mtctr', rS=12))
        self.assertEqual(at[0x8007dd6c], dict(mnemonic='bctrl', BO=20, BI=0, BH=0, LK=1))

    def test_guard_helper_returns_input_and_corrects_stale_c_comment_address(self):
        at = {0x8008aff0 + i * 4: row for i, row in enumerate(EXPECTED[0x8008aff0])}
        self.assertEqual(at[0x8008aff0], dict(mnemonic='lbz', rD=4, rA=3, displacement=2))
        self.assertEqual(at[0x8008aff4]['immediate'], 3)
        self.assertEqual(at[0x8008aff8]['target'], '8008b004')
        self.assertEqual(at[0x8008affc], dict(mnemonic='extsb', rS=4, rA=0, Rc=1))
        self.assertEqual(at[0x8008b000], dict(mnemonic='bclr', BO=4, BI=2, BH=0, LK=0))
        self.assertEqual(at[0x8008b008], dict(mnemonic='stb', rS=0, rA=3, displacement=0x1d8))
        self.assertFalse(any(row.get('rD') == 3 or (row['mnemonic'] == 'extsb' and row['rA'] == 3)
                             for row in at.values()))

    def test_exact_reads_hashes_target_and_all1504_payload_bit_mutations(self):
        mutations = 0
        for (fn, mapping, address, extra), call in zip(SELECTIONS, EXPECTED_READS):
            raw = PAYLOADS[address]
            db = FakeDB(raw)
            result = fn(db, mapping, address, *extra)
            self.assertEqual(db.calls, [call])
            self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
            self.assertEqual(result['width'], len(raw))
            for i in range(len(raw)):
                for bit in range(8):
                    changed = raw[:i] + bytes([raw[i] ^ 1 << bit]) + raw[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        fn(FakeDB(changed), mapping, address, *extra)
                    mutations += 1
        self.assertEqual(mutations, 1504)
        self.assertEqual(a.cell_evidence(FakeDB(PAYLOADS[0x802d6f98]), DATA3_MAPPING, 0x802d6f98)['target'], '8007dd84')

    def test_allowlists_mapping_types_bounds_before_reads(self):
        for fn, mapping, address, extra in SELECTIONS:
            for bad in (address - 1, address + 1, address - 4, address + 4, float(address), True, -1, 1 << 32):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, bad, *extra)
                self.assertFalse(db.calls)
            for index, value in enumerate(mapping):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    bad = list(mapping); bad[index] = replacement
                    db = FakeDB(PAYLOADS[address])
                    with self.assertRaises(a.c.FormatError): fn(db, tuple(bad), address, *extra)
                    self.assertFalse(db.calls)
            db = FakeDB(PAYLOADS[address])
            with self.assertRaises(a.c.FormatError): fn(db, list(mapping), address, *extra)
            self.assertFalse(db.calls)
        for pc, width, _ in RANGES:
            for bad in (0, width - 4, width + 4, -width, True, float(width)):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, bad)
                self.assertFalse(db.calls)
        for pc in (0x8007dd84, 0x8007e698, 0x8008b010):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)
        for pc in (0x802d6f9c, 0x802d6fa0, 0x802d6fa4, 0x802d6f94):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.cell_evidence(db, DATA3_MAPPING, pc)
            self.assertFalse(db.calls)

    def test_truncation_duplicate_allowlists_and_wrong_target_refuse(self):
        for fn, mapping, address, extra in SELECTIONS:
            for raw in (PAYLOADS[address][:-1], PAYLOADS[address] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'): fn(FakeDB(raw), mapping, address, *extra)
            name = 'RANGES' if extra else 'CELLS'
            with patch.object(a, name, getattr(a, name) * 2):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, address, *extra)
                self.assertFalse(db.calls)
        label, pc, target, digest = CELLS[0]
        with patch.object(a, 'CELLS', ((label, pc, target + 4, digest),)):
            with self.assertRaisesRegex(a.c.FormatError, 'cell target mismatch'):
                a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc)

    def test_reserved_forms_unknown_instructions_returns_and_branch_edges_refuse(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x48000002, 0x40800001,
                     0x2c2c0000, 0x94000000, 0x7c0802a7, 0x7c000f75, 0x7c000001, 0x7c00002f):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x8007dcec)
        self.assertIsNone(a.decode_selected(0, 0x8007dcec))
        original = a.decode_selected
        for pc, width, _ in RANGES:
            for row in (None, dict(mnemonic='lbz', rD=0, rA=0, displacement=0)):
                with patch.object(a, 'decode_selected', return_value=row):
                    with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
            def changed_branch(word, address):
                row = original(word, address)
                return dict(row, target=f'{pc + width:08x}') if row['mnemonic'] == 'bc' else row
            with patch.object(a, 'decode_selected', changed_branch):
                with self.assertRaisesRegex(a.c.FormatError, 'branch outside'):
                    a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
        def wrong_call(word, address):
            row = original(word, address)
            return dict(row, target='80000000') if row['mnemonic'] == 'bl' else row
        with patch.object(a, 'decode_selected', wrong_call):
            with self.assertRaisesRegex(a.c.FormatError, 'direct-call mismatch'):
                a.range_evidence(FakeDB(BODIES[0x8007dcec]), TEXT_MAPPING, 0x8007dcec, 152)
        def missing_indirect(word, address):
            row = original(word, address)
            return dict(mnemonic='mtctr', rS=12) if row['mnemonic'] == 'bctrl' else row
        with patch.object(a, 'decode_selected', missing_indirect):
            with self.assertRaisesRegex(a.c.FormatError, 'indirect-call mismatch'):
                a.range_evidence(FakeDB(BODIES[0x8007dcec]), TEXT_MAPPING, 0x8007dcec, 152)

    def test_authentication_precedes_parser_and_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad')
            db.assert_not_called(); code.assert_not_called(); cell.assert_not_called()
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as selected:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(bytes(32), digest)
                db.assert_not_called(); selected.assert_not_called()
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for key, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[key] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as selected:
                db.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'): a.inspect(data, digest)
                db.return_value.rows.assert_not_called(); selected.assert_not_called()

    def test_mapping_refusals_precede_three_selections(self):
        mappings = a.command.MAPPINGS
        blocks = {key: [name, None, None, 0, start, length, 0] for name, key, start, length, root in mappings}
        subs = {key: [key, 2, length, 0, root, 0] for name, key, start, length, root in mappings}
        cases = []
        for key in (1, 5, 7):
            for field in (4, 5, 6):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][field] += 1
                cases.append((bb, ss, '80000000'))
            for field in range(6):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][field] += 1
                cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); bb[99] = copy.deepcopy(bb[key]); cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); ss[99] = copy.deepcopy(ss[key]); cases.append((bb, ss, '80000000'))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]
                cases.append((bb, ss, '80000000'))
        cases.append((blocks, subs, '80000004'))
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called(); cell.assert_not_called()

    def test_independent_extent_sources_no_false_map_claim_and_no_address_cli(self):
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc, end, chunk in (('8007dcec', '8007dd84', 'chunk_0011.c'), ('8008aff0', '8008b010', 'chunk_0013.c')):
            markers = (root / 'research/decomp/ghidra-export' / chunk).read_text()
            for address in (pc, end):
                self.assertIn(f'// ==== {address} ', markers)
                self.assertRegex(index, rf'{address}\t[^\t]+\t{chunk}')
        self.assertIn('8007db5c 00000190 8007db5c 0 zz_007db5c_', symbols)
        self.assertEqual(0x8007db5c + 0x190, 0x8007dcec)
        self.assertEqual(0x8007dd84 - 0x8007dcec, 152)
        self.assertNotRegex(symbols, r'(?m)^8007dcec ')
        self.assertIn('8008aff0 00000020 8008aff0 0 zz_008aff0_', symbols)
        source = (root / 'research/decomp/ghidra-export/chunk_0011.c').read_text()
        callback = source.split('// ==== 8007dcec ')[1].split('// ==== 8007dd84 ')[0]
        for reference in ('param_1 + 0x18', 'param_1 + 0x90', 'param_1 + 0x94', 'PTR_FUN_802d6f98', 'zz_008aff0_'):
            self.assertIn(reference, callback)
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/projectile.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', json.loads(error.getvalue())['error'])


SNAPSHOT_DIR = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports, cls.reads, cls.auth_reads = [], [], []
        original = a.c.GBF.chain
        for name in ('db.3.gbf', 'db.4.gbf'):
            raw = (SNAPSHOT_DIR / name).read_bytes()
            digest = hashlib.sha256(raw).hexdigest()
            reads = []
            def traced(db, *args):
                reads.append(args)
                return original(db, *args)
            with patch.object(a.c.GBF, 'chain', traced): a.c.inspect(raw, digest)
            cls.auth_reads.append(reads[:]); reads.clear()
            with patch.object(a.c.GBF, 'chain', traced): cls.reports.append(a.inspect(raw, digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_all_operands_facts_and_ceiling_agree(self):
        for key in ('mappings', 'ranges', 'cells', 'function_coverage', 'selection_basis'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            for result in report['ranges']:
                pc = int(result['address'], 16)
                self.assertEqual(result['instructions'], [dict(address=f'{pc + i * 4:08x}', **row)
                                                         for i, row in enumerate(EXPECTED[pc])])
            self.assertEqual(report['cells'][0]['target'], '8007dd84')
            basis = report['selection_basis']
            self.assertTrue(basis['guard_must_leave_initial_state_unchanged'])
            self.assertFalse(basis['handler_read_here'])
            self.assertFalse(basis['guard_state_cell_read_here'])

    def test_exact_three_reads_after_unchanged_authenticator(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(all(row[0] == 263 for row in auth))
        for report in self.reports:
            self.assertEqual([r['represented_instructions'] for r in report['function_coverage']], [38, 8])
            self.assertEqual([r['map_size'] for r in report['function_coverage']], [None, 32])
            for row in report['function_coverage']:
                self.assertEqual(row['unrepresented_instructions'], 0)
                self.assertEqual(row['unrepresented_ranges'], [])

    def test_physical_provenance_and_no_raw_output(self):
        expected = {0x8007dcec: (21, 52, 493324, 1984, 152, 870342),
                    0x8008aff0: (21, 55, 547344, 6870, 32, 924380),
                    0x802d6f98: (199, 207, 115000, 354, 4, 3408232)}
        for report in self.reports:
            for row in report['ranges'] + report['cells']:
                root, data, chain_offset, data_offset, length, physical = expected[int(row['address'], 16)]
                self.assertEqual(row['spans'], [dict(root_buffer=root, data_buffer=data, chain_offset=chain_offset,
                    data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)])
                self.assertEqual(row['end_exclusive'], f'{int(row["address"], 16) + row["width"]:08x}')
            for row in report['ranges']:
                self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
                self.assertFalse(any('word' in item for item in row['instructions']))
            self.assertEqual(set(report['cells'][0]), {'label', 'address', 'end_exclusive', 'width', 'target', 'sha256', 'spans'})

    def test_real_archive_and_selected_payload_tamper_refuse(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as selected:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            selected.assert_not_called()
        original = a.c.GBF.chain
        for selected_call in EXPECTED_READS:
            def tampered(db, *args):
                payload, spans = original(db, *args)
                if args == selected_call: payload = bytes([payload[0] ^ 1]) + payload[1:]
                return payload, spans
            with patch.object(a.c.GBF, 'chain', tampered):
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)


if __name__ == '__main__':
    unittest.main()
