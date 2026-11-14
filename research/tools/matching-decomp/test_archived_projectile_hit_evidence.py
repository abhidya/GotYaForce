#!/usr/bin/env python3
"""Manual inverse fixture:100 instructions,410 bytes,exact five-read scope.

Semantic expectations are independently authored, never generated from a
reader, report or archive during tests. Existing snapshots are never fetched.
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

import read_archived_projectile_hit_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
RANGES = ((0x8008ac80, 400, '88d16df3bda187ed3cb011269a356a7d0646ca1c946dcd194664a5abf4a317d0'),)
CELLS = (
    ('object-type4-size', 0x802da668, 2, '>H', (448,), '32444d1ca2314b6449d98ed53575e1d1dca3e826e1d622fee4502e355a21dd85'),
    ('group48-classification', 0x802da730, 1, '>b', (26,), '58f7b0780592032e4d8602a3e8690fb2c701b2e1dd546e703445aabd6469734d'),
    ('pool4-type', 0x802da674, 1, '>b', (4,), 'e52d9c508c502347344d8c07ad91cbd6068afc75ff6292f062a09ca381c89e71'),
    ('groups49-through54-classification', 0x802da731, 6, '>6b', (26, 26, 26, 26, 26, 26), 'e605937264e19250f2777c6c637c32f173428ed770f4f9a2134eb52ef2c21e24'),
)
FIELDS = {'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement',
          'sth': 'rS rA displacement', 'stmw': 'rS rA displacement', 'lmw': 'rD rA displacement',
          'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement', 'lha': 'rD rA displacement',
          'lhz': 'rD rA displacement', 'addi': 'rD rA immediate', 'addis': 'rD rA immediate',
          'mulli': 'rD rA immediate', 'or': 'rS rA rB Rc', 'mflr': 'rD', 'mtlr': 'rS',
          'add': 'rD rA rB OE Rc', 'bl': 'target AA LK', 'b': 'target AA LK',
          'bc': 'BO BI LK target AA', 'extsb': 'rS rA Rc', 'cmpi': 'BF L rA immediate',
          'cmpli': 'BF L rA immediate', 'blr': 'BO BI BH LK', 'rlwinm': 'rS rA SH MB ME Rc'}


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


EXPECTED = {0x8008ac80: ops('''
stwu 1 1 -48
mflr 0
stw 0 1 52
stmw 25 1 20
or 3 25 3 0
or 4 26 4 0
addi 28 0 0
lwz 31 3 0x90
cmpli 0 0 31 0
bc 4 2 0 8008acb0 0
addi 3 0 0
b 8008adfc 0 0
lwz 3 31 0x27c
rlwinm 26 0 2 0 29 0
addi 27 0 0
stw 3 25 0x27c
lwz 30 31 0x3fc
addi 29 30 0xaa0
addi 30 30 0xa20
add 30 30 0 0 0
b 8008ade4 0 0
or 31 3 31 0
addi 4 0 4
addi 5 0 0x30
addi 6 0 0
addi 7 0 0
bl 80088aa0 0 1
cmpli 0 0 3 0
bc 12 2 0 8008addc 0
addi 0 0 1
addis 4 0 -32759
stb 0 3 0
addi 0 4 -22948
stw 0 3 0xc
stw 25 3 0x20
stb 26 3 0x14
lwz 0 25 0x90
cmpli 0 0 0 0
bc 12 2 0 8008ad24 0
stw 0 3 0x24
b 8008ad2c 0 0
lwz 0 25 0x8c
stw 0 3 0x24
lbz 0 30 0
extsb 0 0 0
mulli 0 0 0x50
add 4 29 0 0 0
stw 4 3 0x28
lbz 0 25 0x83
extsb 0 0 1
bc 4 2 0 8008ad94 0
lbz 5 4 1
rlwinm 5 0 0 24 24 1
bc 12 2 0 8008ad64 0
addi 0 25 0x1aa4
stw 0 3 0x60
b 8008ad74 0 0
mulli 5 5 0x30
addi 0 5 0x8d4
add 0 25 0 0 0
stw 0 3 0x60
lbz 0 25 0x1cec
lbz 5 25 0x1ced
extsb 0 0 0
extsb 5 5 0
rlwinm 0 0 12 0 19 0
add 0 5 0 0 0
sth 0 3 0x4c
b 8008ad9c 0 0
addi 0 25 0x114
stw 0 3 0x60
stw 3 3 0x5c
addi 5 0 1
addi 0 0 0
addi 28 0 1
lwz 6 25 0x27c
stw 6 3 0x2c
lhz 6 4 4
stb 6 3 0x11
lha 6 4 6
sth 6 3 0x48
lha 4 4 8
sth 4 3 0x4a
stb 5 25 0x86
stb 0 25 0x1d8
lbz 0 30 0
stb 0 3 0x12
addi 30 30 1
addi 27 27 1
lbz 0 30 0
extsb 0 0 1
bc 12 0 0 8008adf8 0
cmpi 0 0 27 4
bc 12 0 0 8008acd4 0
or 28 3 28 0
lmw 25 1 20
lwz 0 1 52
mtlr 0
addi 1 1 48
blr 20 0 0 0
''')}


def encode(row, pc):
    """Independent inverse: no decoder, report or archive dependencies."""
    name = row['mnemonic']
    forms = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
             'stb': (38, 'rS', 'displacement'), 'sth': (44, 'rS', 'displacement'),
             'stmw': (47, 'rS', 'displacement'), 'lmw': (46, 'rD', 'displacement'),
             'lwz': (32, 'rD', 'displacement'), 'lbz': (34, 'rD', 'displacement'),
             'lha': (42, 'rD', 'displacement'), 'lhz': (40, 'rD', 'displacement'),
             'addi': (14, 'rD', 'immediate'), 'addis': (15, 'rD', 'immediate'),
             'mulli': (7, 'rD', 'immediate')}
    if name in forms:
        opcode, reg, imm = forms[name]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name in ('mflr', 'mtlr'):
        return 31 << 26 | row['rD' if name == 'mflr' else 'rS'] << 21 | 8 << 16 | (339 if name == 'mflr' else 467) << 1
    if name in ('or', 'extsb', 'add'):
        reg = 'rD' if name == 'add' else 'rS'
        return (31 << 26 | row[reg] << 21 | row['rA'] << 16 | row.get('rB', 0) << 11 |
                {'or': 444, 'extsb': 954, 'add': 266}[name] << 1 | row.get('OE', 0) << 10 | row['Rc'])
    if name in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if name != 'bc':
            return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
        return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc | row['AA'] << 1 | row['LK']
    if name == 'blr':
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    if name in ('cmpi', 'cmpli'):
        return (11 if name == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    raise AssertionError(name)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
PAYLOADS = dict(BODIES)
PAYLOADS.update({0x802da668: struct.pack('>H', 448), 0x802da730: bytes([26]),
                 0x802da674: bytes([4]), 0x802da731: bytes([26, 26, 26, 26, 26, 26])})
SELECTIONS = ((a.range_evidence, TEXT_MAPPING, 0x8008ac80, (400,)),) + tuple(
    (a.cell_evidence, DATA3_MAPPING, pc, ()) for pc in (0x802da668, 0x802da730, 0x802da674, 0x802da731))
EXPECTED_READS = [(21, 546464, 400, 2796416), (199, 129032, 2, 1000128),
                  (199, 129232, 1, 1000128), (199, 129044, 1, 1000128), (199, 129233, 6, 1000128)]


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_exact_inventory_and_address_derivation(self):
        self.assertEqual(a.RANGES, RANGES)
        self.assertEqual(a.CELLS, CELLS)
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(a.DATA3_MAPPING, DATA3_MAPPING)
        self.assertEqual(sum(map(len, PAYLOADS.values())), 410)
        self.assertEqual(0x802da660 + 2 * 4, CELLS[0][1])
        self.assertEqual(0x802da700 + 0x30, CELLS[1][1])
        self.assertEqual(0x802da670 + 0 * 0x18 + 4, CELLS[2][1])
        self.assertEqual([0x30 + 1 + slot for slot in range(6)], list(range(49, 55)))
        self.assertEqual(0x802da700 + 49, CELLS[3][1])

    def test_all100_operands_independent_inverse_and3200_bit_controls(self):
        rows, body = EXPECTED[0x8008ac80], BODIES[0x8008ac80]
        self.assertEqual(len(rows), 100)
        self.assertEqual(hashlib.sha256(body).hexdigest(), RANGES[0][2])
        report = a.range_evidence(FakeDB(body), TEXT_MAPPING, 0x8008ac80, 400)
        self.assertEqual(report['instructions'], [dict(address=f'{0x8008ac80 + i * 4:08x}', **row)
                                                  for i, row in enumerate(rows)])
        mutations = 0
        for i, row in enumerate(rows):
            pc = 0x8008ac80 + i * 4; word = encode(row, pc)
            self.assertEqual(a.decode_selected(word, pc), row)
            for bit in range(32):
                mutations += 1; changed = word ^ 1 << bit
                try: decoded = a.decode_selected(changed, pc)
                except a.c.FormatError: continue
                if decoded is not None:
                    self.assertNotEqual(decoded, row, (hex(pc), bit))
                    self.assertEqual(encode(decoded, pc), changed, (hex(pc), bit))
        self.assertEqual(mutations, 3200)

    def test_frozen_order_capture_alloc_reload_loop_and_returns(self):
        at = {0x8008ac80 + i * 4: row for i, row in enumerate(EXPECTED[0x8008ac80])}
        self.assertEqual(at[0x8008ac9c], dict(mnemonic='lwz', rD=31, rA=3, displacement=0x90))
        self.assertEqual(at[0x8008aca8], dict(mnemonic='addi', rD=3, rA=0, immediate=0))
        self.assertEqual(at[0x8008acac]['target'], '8008adfc')
        self.assertEqual([at[pc]['displacement'] for pc in (0x8008acb0, 0x8008acbc, 0x8008acc0)], [0x27c, 0x27c, 0x3fc])
        self.assertEqual(at[0x8008acb4], dict(mnemonic='rlwinm', rS=26, rA=0, SH=2, MB=0, ME=29, Rc=0))
        self.assertEqual([at[pc]['immediate'] for pc in (0x8008acd8, 0x8008acdc, 0x8008ace0, 0x8008ace4)], [4, 48, 0, 0])
        self.assertEqual(at[0x8008ace8]['target'], '80088aa0')
        self.assertEqual(at[0x8008acf0]['target'], '8008addc')
        self.assertEqual(((at[0x8008acf8]['immediate'] << 16) + at[0x8008ad00]['immediate']) & 0xffffffff, 0x8008a65c)
        self.assertEqual(at[0x8008ad10], dict(mnemonic='lwz', rD=0, rA=25, displacement=0x90))
        self.assertEqual(at[0x8008ad24], dict(mnemonic='lwz', rD=0, rA=25, displacement=0x8c))
        self.assertEqual([pc for pc, row in at.items() if row == dict(mnemonic='lbz', rD=0, rA=30, displacement=0)],
                         [0x8008ad2c, 0x8008add4, 0x8008ade4])
        self.assertEqual(at[0x8008ad30], dict(mnemonic='extsb', rS=0, rA=0, Rc=0))
        self.assertEqual(at[0x8008ad34], dict(mnemonic='mulli', rD=0, rA=0, immediate=0x50))
        self.assertEqual(at[0x8008adac], dict(mnemonic='lwz', rD=6, rA=25, displacement=0x27c))
        self.assertEqual([at[pc]['displacement'] for pc in (0x8008adcc, 0x8008add0)], [0x86, 0x1d8])
        self.assertEqual(at[0x8008addc], dict(mnemonic='addi', rD=30, rA=30, immediate=1))
        self.assertEqual(at[0x8008ade0], dict(mnemonic='addi', rD=27, rA=27, immediate=1))
        self.assertEqual(at[0x8008ade8], dict(mnemonic='extsb', rS=0, rA=0, Rc=1))
        self.assertEqual(at[0x8008adec], dict(mnemonic='bc', BO=12, BI=0, LK=0, target='8008adf8', AA=0))
        self.assertEqual(at[0x8008adf0], dict(mnemonic='cmpi', BF=0, L=0, rA=27, immediate=4))
        self.assertEqual(at[0x8008adf4]['target'], '8008acd4')
        self.assertEqual(at[0x8008adf8], dict(mnemonic='or', rS=28, rA=3, rB=28, Rc=0))
        self.assertEqual([(pc, row['immediate']) for pc, row in at.items() if row.get('rD') == 28],
                         [(0x8008ac98, 0), (0x8008ada8, 1)])

    def test_frozen_joint_branches_sign_widths_and_store_schedule(self):
        at = {0x8008ac80 + i * 4: row for i, row in enumerate(EXPECTED[0x8008ac80])}
        self.assertEqual(at[0x8008ad40], dict(mnemonic='lbz', rD=0, rA=25, displacement=0x83))
        self.assertEqual(at[0x8008ad50], dict(mnemonic='rlwinm', rS=5, rA=0, SH=0, MB=24, ME=24, Rc=1))
        self.assertEqual([at[pc]['immediate'] for pc in (0x8008ad58, 0x8008ad64, 0x8008ad68, 0x8008ad94)],
                         [0x1aa4, 0x30, 0x8d4, 0x114])
        self.assertEqual([at[pc]['displacement'] for pc in (0x8008ad74, 0x8008ad78)], [0x1cec, 0x1ced])
        self.assertEqual([at[pc]['mnemonic'] for pc in (0x8008ad7c, 0x8008ad80, 0x8008ad84, 0x8008ad88, 0x8008ad8c)],
                         ['extsb', 'extsb', 'rlwinm', 'add', 'sth'])
        self.assertEqual(at[0x8008ad84], dict(mnemonic='rlwinm', rS=0, rA=0, SH=12, MB=0, ME=19, Rc=0))
        self.assertEqual([(pc, row['mnemonic'], row['displacement']) for pc, row in at.items()
                          if row['mnemonic'] in ('stw', 'stb', 'sth') and row['rA'] == 3], [
            (0x8008acfc, 'stb', 0), (0x8008ad04, 'stw', 0xc), (0x8008ad08, 'stw', 0x20),
            (0x8008ad0c, 'stb', 0x14), (0x8008ad1c, 'stw', 0x24), (0x8008ad28, 'stw', 0x24),
            (0x8008ad3c, 'stw', 0x28), (0x8008ad5c, 'stw', 0x60), (0x8008ad70, 'stw', 0x60),
            (0x8008ad8c, 'sth', 0x4c), (0x8008ad98, 'stw', 0x60), (0x8008ad9c, 'stw', 0x5c),
            (0x8008adb0, 'stw', 0x2c), (0x8008adb8, 'stb', 0x11), (0x8008adc0, 'sth', 0x48),
            (0x8008adc8, 'sth', 0x4a), (0x8008add8, 'stb', 0x12)])
        self.assertEqual([(at[pc]['mnemonic'], at[pc]['displacement']) for pc in (0x8008adb4, 0x8008adbc, 0x8008adc4)],
                         [('lhz', 4), ('lha', 6), ('lha', 8)])

    def test_exact_reads_hashes_typed_values_and3280_payload_bit_refusals(self):
        mutations = 0
        for (fn, mapping, address, extra), call in zip(SELECTIONS, EXPECTED_READS):
            raw = PAYLOADS[address]; db = FakeDB(raw)
            result = fn(db, mapping, address, *extra)
            self.assertEqual(db.calls, [call])
            self.assertEqual(result['width'], len(raw))
            self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
            for i in range(len(raw)):
                for bit in range(8):
                    changed = raw[:i] + bytes([raw[i] ^ 1 << bit]) + raw[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        fn(FakeDB(changed), mapping, address, *extra)
                    mutations += 1
        self.assertEqual(mutations, 3280)
        for _, pc, _, _, values, _ in CELLS:
            self.assertEqual(a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc)['values'], list(values))

    def test_scope_mapping_types_widths_duplicates_and_wrong_values_refuse(self):
        for fn, mapping, address, extra in SELECTIONS:
            for bad in (-1, True, float(address), 1 << 32, address - 100, address + 100):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, bad, *extra)
                self.assertFalse(db.calls)
            for index, value in enumerate(mapping):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    bad = list(mapping); bad[index] = replacement; db = FakeDB(PAYLOADS[address])
                    with self.assertRaises(a.c.FormatError): fn(db, tuple(bad), address, *extra)
                    self.assertFalse(db.calls)
            with self.assertRaises(a.c.FormatError): fn(FakeDB(b''), list(mapping), address, *extra)
            for raw in (PAYLOADS[address][:-1], PAYLOADS[address] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'): fn(FakeDB(raw), mapping, address, *extra)
            name = 'RANGES' if extra else 'CELLS'
            with patch.object(a, name, getattr(a, name) * 2):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, address, *extra)
                self.assertFalse(db.calls)
        for bad in (0, 396, 404, -400, True, 400.0):
            db = FakeDB(BODIES[0x8008ac80])
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, 0x8008ac80, bad)
            self.assertFalse(db.calls)
        for pc in (0x8008a65c, 0x8008ae10, 0x80088aa0):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)
        for pc in (0x802da666, 0x802da675, 0x802da676, 0x802da680, 0x802da72f, 0x802da732, 0x802da737):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.cell_evidence(db, DATA3_MAPPING, pc)
            self.assertFalse(db.calls)
        label, pc, width, fmt, values, digest = CELLS[0]
        with patch.object(a, 'CELLS', ((label, pc, width, fmt, (449,), digest),)):
            with self.assertRaisesRegex(a.c.FormatError, 'cell value mismatch'):
                a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc)
        with patch.object(a, 'CELLS', ((label, pc, width, '>I', values, digest),)):
            db = FakeDB(b'')
            with self.assertRaisesRegex(a.c.FormatError, 'cell width/bounds'): a.cell_evidence(db, DATA3_MAPPING, pc)
            self.assertFalse(db.calls)

    def test_reserved_forms_control_flow_and_no_arbitrary_cli(self):
        pc, width, _ = RANGES[0]
        for word, addr in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, addr)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x48000002, 0x40800001,
                     0x2c2c0000, 0x94000000, 0x7c0802a7, 0x7c000f75):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        self.assertIsNone(a.decode_selected(0, pc))
        self.assertIsNone(a.decode_selected(0x7c000614, pc))  # add OE=1 not selected
        original = a.decode_selected
        for row in (None, dict(mnemonic='lbz', rD=0, rA=0, displacement=0)):
            with patch.object(a, 'decode_selected', return_value=row):
                with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
        for mnemonic, error in (('bc', 'branch outside'), ('b', 'branch outside'), ('bl', 'direct-call mismatch')):
            def changed(word, addr):
                row = original(word, addr)
                return dict(row, target='8008ae10') if row['mnemonic'] == mnemonic else row
            with patch.object(a, 'decode_selected', changed):
                with self.assertRaisesRegex(a.c.FormatError, error): a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/hit.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', json.loads(error.getvalue())['error'])

    def test_authentication_precedes_parser_and_all_selections(self):
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

    def test_mapping_refusals_precede_five_selections(self):
        mappings = a.command.MAPPINGS
        blocks = {key: [name, None, None, 0, start, length, 0] for name, key, start, length, root in mappings}
        subs = {key: [key, 2, length, 0, root, 0] for name, key, start, length, root in mappings}
        cases = []
        for key in (1, 5, 7):
            for field in (4, 5, 6):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][field] += 1; cases.append((bb, ss, '80000000'))
            for field in range(6):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][field] += 1; cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); bb[99] = copy.deepcopy(bb[key]); cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); ss[99] = copy.deepcopy(ss[key]); cases.append((bb, ss, '80000000'))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]; cases.append((bb, ss, '80000000'))
        cases.append((blocks, subs, '80000004'))
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called(); cell.assert_not_called()

    def test_independent_c_index_map_extent_and_typed_metadata_sources(self):
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        markers = (root / 'research/decomp/ghidra-export/chunk_0013.c').read_text()
        for pc in ('8008ac80', '8008ae10'):
            self.assertIn(f'// ==== {pc} ', markers)
            self.assertRegex(index, rf'{pc}\t[^\t]+\tchunk_0013.c')
        self.assertIn('8008ac80 00000190 8008ac80 0 zz_008ac80_', symbols)
        self.assertEqual(0x8008ac80 + 0x190, 0x8008ae10)
        hit = markers.split('// ==== 8008ac80 ')[1].split('// ==== 8008ae10 ')[0]
        for phrase in ('zz_0088aa0_(iVar7,4,0x30,0,0)', 'iVar5 + 0xa20 + param_2 * 4',
                       '(-1 < *pcVar6 && (iVar3 < 4))', 'iVar5 + 0xaa0 + *pcVar6 * 0x50', 'FUN_8008a65c'):
            self.assertIn(phrase, hit)
        allocator = (root / 'research/decomp/ghidra-export/chunk_0012.c').read_text()
        for phrase in ('pcVar6 = &DAT_802da670 + param_3 * 0x18;',
                       '(ushort *)(&DAT_802da660 + cVar1 * 2)', '(&DAT_802da700)[param_3]',
                       'param_3 = (int)*(char *)(param_1 + 0x3e4) + param_3 + 1;'):
            self.assertIn(phrase, allocator)
        slots = (root / 'research/decomp/ghidra-export/chunk_0006.c').read_text().split('// ==== 800536b0 ')[1].split('// ==== 800537a8 ')[0]
        for phrase in ('iVar2 = 0;', 'param_1[0x3e4] = (char)iVar2;', 'while (iVar2 < 6)'):
            self.assertIn(phrase, slots)
        for text in ('800536b0 000000f8', '80088398 000001a4', '80088aa0 000001a0', '80088d98 000000b8'):
            self.assertIn(text, symbols)


SNAPSHOT_DIR = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports, cls.reads, cls.auth_reads = [], [], []
        original = a.c.GBF.chain
        for name in ('db.3.gbf', 'db.4.gbf'):
            raw = (SNAPSHOT_DIR / name).read_bytes(); digest = hashlib.sha256(raw).hexdigest(); reads = []
            def traced(db, *args):
                reads.append(args)
                return original(db, *args)
            with patch.object(a.c.GBF, 'chain', traced): a.c.inspect(raw, digest)
            cls.auth_reads.append(reads[:]); reads.clear()
            with patch.object(a.c.GBF, 'chain', traced): cls.reports.append(a.inspect(raw, digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_operands_metadata_ceiling_and_exact_read_trace(self):
        for key in ('mappings', 'ranges', 'cells', 'function_coverage', 'selection_basis'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports], [
            '7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
            '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report, reads, auth in zip(self.reports, self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(all(row[0] == 263 for row in auth))
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(report['ranges'][0]['instructions'], [dict(address=f'{0x8008ac80 + i * 4:08x}', **row)
                                                                  for i, row in enumerate(EXPECTED[0x8008ac80])])
            self.assertEqual([row['values'] for row in report['cells']], [[448], [26], [4], [26] * 6])
            coverage = report['function_coverage'][0]
            self.assertEqual((coverage['represented_instructions'], coverage['map_size']), (100, 400))
            self.assertEqual((coverage['unrepresented_instructions'], coverage['unrepresented_ranges']), (0, []))
            for key in ('constructor_instructions_authenticated_here', 'pool_capacity_read_here', 'hit_payloads_read_here', 'callback_body_read_here'):
                self.assertFalse(report['selection_basis'][key])

    def test_physical_provenance_and_no_raw_output(self):
        expected = {0x8008ac80: (21, 55, 546464, 5990, 400, 923500),
                    0x802da668: (199, 207, 129032, 14386, 2, 3422264),
                    0x802da730: (199, 207, 129232, 14586, 1, 3422464),
                    0x802da674: (199, 207, 129044, 14398, 1, 3422276),
                    0x802da731: (199, 207, 129233, 14587, 6, 3422465)}
        for report in self.reports:
            for row in report['ranges'] + report['cells']:
                root, data, chain_offset, data_offset, length, physical = expected[int(row['address'], 16)]
                self.assertEqual(row['spans'], [dict(root_buffer=root, data_buffer=data, chain_offset=chain_offset,
                    data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)])
                self.assertEqual(row['end_exclusive'], f'{int(row["address"], 16) + row["width"]:08x}')
            for row in report['ranges']:
                self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
                self.assertFalse(any('word' in item for item in row['instructions']))
            for row in report['cells']:
                self.assertEqual(set(row), {'label', 'address', 'end_exclusive', 'width', 'values', 'sha256', 'spans'})

    def test_real_archive_and_each_selected_payload_tamper_refuse(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes(); digest = hashlib.sha256(raw).hexdigest()
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
