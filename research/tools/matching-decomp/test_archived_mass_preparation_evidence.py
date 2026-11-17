#!/usr/bin/env python3
"""Independent semantic operands/inverse:336 instructions,1344 code bytes,4 reads.

Literal fixtures below are manually authored, never loaded from reader/report/
archive output by tests. Existing private snapshots optional; never fetched.
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

import read_archived_mass_preparation_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
RANGES = ((0x80053b30, 1344, '8c5a0b248d9fa0b131b7ff20346ee5af01ea3453ae1c8c9a18012ff8839a6890'),)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
CONSTANTS = (
    (0x80437250, 4, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119', 0.0),
    (0x80437254, 4, '2b6153d08dad36fbfbc33c125e7c858acc13a4a989168279c710896032141f98', 50000.0),
    (0x80437258, 4, 'de620abd6d3615746360c1d15ce3a56291236d37424124054a49d25e947ffc4d', 1.0),
)
CONSTANT_BYTES = {pc: struct.pack('>f', value) for pc, _, _, value in CONSTANTS}
FIELDS = {
    'lwzu': 'rD rA displacement', 'lfs': 'fD rA displacement', 'stfs': 'fS rA displacement',
    'mulli': 'rD rA immediate', 'mulhwu': 'rD rA rB Rc', 'mulhw': 'rD rA rB Rc',
    'subf': 'rD rA rB Rc', 'andi.': 'rS rA immediate', 'stwx': 'rS rA rB',
    'lwzx': 'rD rA rB', 'fadds': 'fD fA fB', 'fcmpo': 'BF fA fB',
    'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement',
    'sth': 'rS rA displacement', 'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement',
    'lhz': 'rD rA displacement', 'lha': 'rD rA displacement',
    'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'xoris': 'rS rA immediate',
    'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc', 'slw': 'rS rA rB Rc',
    'add': 'rD rA rB Rc', 'extsb': 'rS rA Rc', 'extsh': 'rS rA Rc',
    'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS', 'lbzx': 'rD rA rB', 'stbx': 'rS rA rB',
    'bl': 'target AA LK', 'b': 'target AA LK', 'bc': 'BO BI target AA LK',
    'blr': 'BO BI BH LK', 'bclr': 'BO BI BH LK',
    'rlwinm': 'rS rA SH MB ME Rc', 'cmpi': 'BF L rA immediate', 'cmpli': 'BF L rA immediate',
    'cmp': 'BF L rA rB', 'cmpl': 'BF L rA rB',
    'lfd': 'fD rA displacement', 'stfd': 'fS rA displacement',
    'fsubs': 'fD fA fB', 'fdivs': 'fD fA fB', 'fmuls': 'fD fA fC', 'fctiwz': 'fD fB',
}


def ops(text):
    rows = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        rows.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                          for key, value in zip(keys, values)}))
    return rows


# Manually reviewed full source operands. Tests never read reports to make fixtures.
EXPECTED = {0x80053b30: ops('''
stwu 1 1 -32
mflr 0
addis 4 0 -32708
addi 7 13 -21308
stw 0 1 36
addi 5 4 0x6dec
addi 4 0 0
addis 3 0 -32708
stw 31 1 28
addi 0 0 6
addi 8 1 8
stw 4 5 0
lwz 9 3 0x4e84
stw 4 5 4
stw 4 5 8
stw 4 5 12
stw 4 5 16
stw 4 5 20
stw 4 5 24
stw 4 5 28
stw 4 5 32
stw 4 5 36
stw 4 5 40
stw 4 5 44
stw 4 5 48
stw 4 5 52
stw 4 5 56
stw 4 5 60
stw 4 5 64
stw 4 5 68
stw 4 5 72
stw 4 5 76
stb 4 13 -21308
stw 4 5 80
stb 4 7 1
stw 4 5 84
stb 4 7 2
stw 4 5 88
stw 4 5 92
stb 4 7 3
mtctr 0
lbz 0 9 0
extsb 0 0 1
bc 12 2 80053c78 0 0
lfs 0 2 -30672
addi 0 0 0
stb 0 8 0
stfs 0 9 0x204
lbz 0 9 0x18
extsb 0 0 0
cmpi 0 0 0 1
bc 12 2 80053c08 0 0
cmpi 0 0 0 2
bc 4 2 80053c34 0 0
lwz 3 9 0x4ac
lfs 0 2 -30668
lfs 1 3 0x98
fcmpo 0 1 0
bc 4 0 80053c2c 0 0
lfs 0 9 0xb4
fmuls 0 1 0
stfs 0 9 0x208
b 80053c38 0 0
stfs 1 9 0x208
b 80053c38 0 0
stfs 0 9 0x208
lbz 0 9 0x18
cmpi 0 0 0 1
bc 4 2 80053c78 0 0
lbz 7 9 0x88
addis 3 0 -32708
addi 4 13 -21308
extsb 7 7 0
addi 5 3 0x6dec
lbzx 3 4 7
mulli 6 7 24
extsb 3 0 0
addi 3 3 1
add 5 5 6 0
rlwinm 0 0 2 0 29 0
stbx 3 4 7
stwx 9 5 0
addi 8 8 1
addi 9 9 0x1e00
bc 16 0 80053bd4 0 0
addis 3 0 -32708
addi 0 0 3
addi 6 3 0x4e84
addi 4 1 8
addi 7 0 0
mtctr 0
lwz 8 6 0
lfs 1 8 0x204
or 8 9 8 0
lfs 0 8 0x208
fadds 0 1 0
stfs 0 8 0x204
b 80053cec 0 0
lwz 9 9 0x1e4
lbz 0 9 0x83
extsb 0 0 1
bc 4 2 80053cf8 0 0
lbz 0 9 0x3e4
lfs 1 9 0x204
lfs 0 8 0x208
extsb 0 5 0
lbzx 3 4 5
fadds 0 1 0
addi 0 3 1
stbx 0 4 5
stfs 0 9 0x204
lbz 0 9 0x1db
extsb 0 0 1
bc 4 2 80053cb8 0 0
lwzu 8 6 4
lfs 1 8 0x204
or 8 9 8 0
lfs 0 8 0x208
fadds 0 1 0
stfs 0 8 0x204
b 80053d48 0 0
lwz 9 9 0x1e4
lbz 0 9 0x83
extsb 0 0 1
bc 4 2 80053d54 0 0
lbz 0 9 0x3e4
lfs 1 9 0x204
lfs 0 8 0x208
extsb 0 5 0
lbzx 3 4 5
fadds 0 1 0
addi 0 3 1
stbx 0 4 5
stfs 0 9 0x204
lbz 0 9 0x1db
extsb 0 0 1
bc 4 2 80053d14 0 0
addi 6 6 4
addi 7 7 1
bc 16 0 80053c9c 0 0
bl 800055fc 0 1
addis 4 0 -21845
rlwinm 3 3 30 2 31 0
addi 0 4 -21845
mulhwu 0 0 3 0
rlwinm 0 0 30 2 31 0
mulli 0 0 6
subf 31 0 3 0
bl 800055fc 0 1
rlwinm 3 3 0 28 28 1
addi 0 0 -1
bc 12 2 80053d94 0 0
addi 0 0 1
addi 4 0 0
addis 3 0 -32708
stb 4 13 -21312
addi 3 3 0x4e84
lfs 0 2 -30664
rlwinm 31 5 2 0 29 0
add 31 31 0 1
lwzx 5 3 5
stfs 0 5 0x664
bc 4 0 80053dc4 0 0
addi 31 0 5
b 80053de0 0 0
addis 6 0 10923
addi 6 6 -21845
mulhw 7 6 31 0
rlwinm 7 6 1 31 31 0
add 6 7 6 0
mulli 6 6 6
subf 31 6 31 0
lbz 6 5 0
extsb 6 6 1
bc 12 2 80053f30 0 0
lbz 6 5 0x4a0
cmpi 0 0 6 1
bc 12 2 80053f30 0 0
lbz 12 13 -21312
addis 6 0 -32708
addi 10 6 0x4e6c
addi 9 1 8
extsb 12 11 1
addi 6 0 0
addi 7 11 1
mtctr 7
bc 12 0 80053f30 0 0
cmp 0 0 6 11
bc 4 2 80053e48 0 0
lbz 8 13 -21312
addis 6 0 -32708
addi 6 6 0x4e6c
extsb 8 7 0
addi 8 8 1
rlwinm 7 7 2 0 29 0
stb 8 13 -21312
stwx 5 6 7
b 80053f30 0 0
lwz 8 10 0
lbz 7 5 0x3e4
lbz 8 8 0x3e4
extsb 7 7 0
extsb 8 8 0
lbzx 7 9 7
lbzx 8 9 8
extsb 7 7 0
extsb 8 8 0
cmp 0 0 8 7
bc 4 0 80053f24 0 0
extsb 12 10 0
addis 7 0 -32708
cmp 0 0 10 6
rlwinm 10 8 2 0 29 0
addi 7 7 0x4e6c
add 9 7 8 0
subf 8 6 10 0
bc 4 1 80053f04 0 0
rlwinm 8 7 29 3 31 1
mtctr 7
bc 12 2 80053ef0 0 0
lwz 7 9 -4
stw 7 9 0
lwz 7 9 -8
stw 7 9 -4
lwz 7 9 -12
stw 7 9 -8
lwz 7 9 -16
stw 7 9 -12
lwz 7 9 -20
stw 7 9 -16
lwz 7 9 -24
stw 7 9 -20
lwz 7 9 -28
stw 7 9 -24
lwz 7 9 -32
stw 7 9 -28
addi 9 9 -32
bc 16 0 80053ea0 0 0
andi. 8 8 7
bc 12 2 80053f04 0 0
mtctr 8
lwz 7 9 -4
stw 7 9 0
addi 9 9 -4
bc 16 0 80053ef4 0 0
lbz 7 13 -21312
addis 8 0 -32708
rlwinm 6 9 2 0 29 0
addi 8 8 0x4e6c
addi 6 7 1
stwx 5 8 9
stb 6 13 -21312
b 80053f30 0 0
addi 10 10 4
addi 6 6 1
bc 16 0 80053e1c 0 0
addi 4 4 1
cmpi 0 0 4 6
bc 12 0 80053da8 0 0
addis 3 0 -32708
addi 6 0 0
lwz 8 3 0x4e84
lbz 0 8 0
extsb 0 0 1
bc 12 2 8005404c 0 0
lbz 0 8 0x4a0
cmpi 0 0 0 1
bc 4 2 8005404c 0 0
lbz 5 13 -21312
addis 3 0 -32708
addi 4 3 0x4e6c
addi 7 0 0
extsb 5 3 1
addi 0 3 1
mtctr 0
bc 12 0 8005404c 0 0
lwz 3 4 0
lwz 0 8 0x4a4
cmpl 0 0 3 0
bc 4 2 80054040 0 0
extsb 5 5 0
addis 3 0 -32708
cmp 0 0 5 7
rlwinm 5 4 2 0 29 0
addi 0 3 0x4e6c
add 4 0 4 0
subf 3 7 5 0
bc 4 1 80054020 0 0
rlwinm 3 0 29 3 31 1
mtctr 0
bc 12 2 8005400c 0 0
lwz 0 4 -4
stw 0 4 0
lwz 0 4 -8
stw 0 4 -4
lwz 0 4 -12
stw 0 4 -8
lwz 0 4 -16
stw 0 4 -12
lwz 0 4 -20
stw 0 4 -16
lwz 0 4 -24
stw 0 4 -20
lwz 0 4 -28
stw 0 4 -24
lwz 0 4 -32
stw 0 4 -28
addi 4 4 -32
bc 16 0 80053fbc 0 0
andi. 3 3 7
bc 12 2 80054020 0 0
mtctr 3
lwz 0 4 -4
stw 0 4 0
addi 4 4 -4
bc 16 0 80054010 0 0
lbz 3 13 -21312
addis 4 0 -32708
rlwinm 7 5 2 0 29 0
addi 4 4 0x4e6c
addi 0 3 1
stwx 8 4 5
stb 0 13 -21312
b 8005404c 0 0
addi 4 4 4
addi 7 7 1
bc 16 0 80053f80 0 0
addi 6 6 1
addi 8 8 0x1e00
cmpi 0 0 6 6
bc 12 0 80053f48 0 0
lwz 0 1 36
lwz 31 1 28
mtlr 0
addi 1 1 32
blr 20 0 0 0
''')}


def encode(row, pc):
    """Independent PPC inverse, with no decoder/report/archive inputs."""
    name = row['mnemonic']
    forms = {'lwzu': (33, 'rD', 'displacement'), 'lfs': (48, 'fD', 'displacement'),
             'stfs': (52, 'fS', 'displacement'), 'mulli': (7, 'rD', 'immediate'),
             'andi.': (28, 'rS', 'immediate'),'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
             'stb': (38, 'rS', 'displacement'), 'sth': (44, 'rS', 'displacement'),
             'stmw': (47, 'rS', 'displacement'), 'lmw': (46, 'rD', 'displacement'),
             'lwz': (32, 'rD', 'displacement'), 'lbz': (34, 'rD', 'displacement'),
             'lhz': (40, 'rD', 'displacement'), 'lha': (42, 'rD', 'displacement'),
             'lfd': (50, 'fD', 'displacement'), 'stfd': (54, 'fS', 'displacement'),
             'xoris': (27, 'rS', 'immediate'), 'addi': (14, 'rD', 'immediate'),
             'addis': (15, 'rD', 'immediate')}
    if name in forms:
        opcode, reg, imm = forms[name]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name in ('mflr', 'mtlr', 'mtctr'):
        return (31 << 26 | row['rD' if name == 'mflr' else 'rS'] << 21 |
                (9 if name == 'mtctr' else 8) << 16 | (339 if name == 'mflr' else 467) << 1)
    if name in ('or', 'and', 'slw', 'add', 'lwzx', 'lbzx', 'stbx', 'stwx', 'subf', 'mulhw', 'mulhwu'):
        xo, reg = {'stwx': (151, 'rS'), 'subf': (40, 'rD'), 'mulhw': (75, 'rD'), 'mulhwu': (11, 'rD'), 'or': (444, 'rS'), 'and': (28, 'rS'), 'slw': (24, 'rS'),
                   'add': (266, 'rD'), 'lwzx': (23, 'rD'), 'lbzx': (87, 'rD'), 'stbx': (215, 'rS')}[name]
        return (31 << 26 | row[reg] << 21 | row['rA'] << 16 | row['rB'] << 11 |
                xo << 1 | row.get('Rc', 0))
    if name in ('extsb', 'extsh'):
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | (954 if name == 'extsb' else 922) << 1 | row['Rc']
    if name in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if name == 'bc':
            return (16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc |
                    row['AA'] << 1 | row['LK'])
        return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name in ('blr', 'bclr'):
        return (19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 |
                16 << 1 | row['LK'])
    if name == 'rlwinm':
        return (21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 |
                row['MB'] << 6 | row['ME'] << 1 | row['Rc'])
    if name in ('cmpi', 'cmpli'):
        return ((11 if name == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 |
                row['rA'] << 16 | row['immediate'] & 65535)
    if name in ('cmp', 'cmpl'):
        return (31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 |
                row['rB'] << 11 | (32 if name == 'cmpl' else 0) << 1)
    if name in ('fsubs', 'fdivs', 'fmuls', 'fadds'):
        return (59 << 26 | row['fD'] << 21 | row['fA'] << 16 |
                (row['fC'] << 6 if name == 'fmuls' else row['fB'] << 11) |
                {'fsubs': 20, 'fdivs': 18, 'fmuls': 25, 'fadds': 21}[name] << 1)
    if name == 'fctiwz':
        return 63 << 26 | row['fD'] << 21 | row['fB'] << 11 | 15 << 1
    if name == 'fcmpo':
        return 63 << 26 | row['BF'] << 23 | row['fA'] << 16 | row['fB'] << 11 | 32 << 1
    raise AssertionError(name)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
EXPECTED_READS = [(21, 320848, 1344, 2796416), (263, 2096, 4, 27360),
                  (263, 2100, 4, 27360), (263, 2104, 4, 27360)]


def at(entry=0x80053b30):
    return {entry + i * 4: row for i, row in enumerate(EXPECTED[entry])}


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_independent_extents_and_named_constants(self):
        self.assertEqual(a.RANGES, RANGES); self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(a.CONSTANTS, CONSTANTS); self.assertEqual(a.DATA5_MAPPING, DATA5_MAPPING)
        self.assertEqual(len(BODIES[0x80053b30]), 1344)
        self.assertEqual(len(EXPECTED[0x80053b30]), 336)
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        source = (root / 'research/decomp/ghidra-export/chunk_0006.c').read_text()
        start = index.index('80053b30\tzz_0053b30_\tchunk_0006.c')
        self.assertTrue(index[start + 1].startswith('80054070\t'))
        body, suffix = source.split('// ==== 80053b30 ', 1)[1].split('// ==== ', 1)
        self.assertTrue(suffix.startswith('80054070 '))
        self.assertRegex(symbols, r'(?m)^80053b30 00000540 80053b30 0 ')
        for pc, _, _, _ in CONSTANTS: self.assertIn(f'FLOAT_{pc:08x}', body)
        self.assertEqual([struct.unpack('>I', CONSTANT_BYTES[pc])[0] for pc, *_ in CONSTANTS],
                         [0x00000000, 0x47435000, 0x3f800000])

    def test_all336_operands_independent_inverse_hash_and10752_bit_controls(self):
        mutations = 0
        for pc, width, digest in RANGES:
            body, rows = BODIES[pc], EXPECTED[pc]
            self.assertEqual(len(body), width); self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
            report = a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
            self.assertEqual(report['instructions'], [dict(address=f'{pc + i * 4:08x}', **row)
                                                      for i, row in enumerate(rows)])
            for i, row in enumerate(rows):
                address = pc + i * 4; word = encode(row, address)
                self.assertEqual(a.decode_selected(word, address), row)
                for bit in range(32):
                    mutations += 1; changed = word ^ 1 << bit
                    try: decoded = a.decode_selected(changed, address)
                    except a.c.FormatError: continue
                    if decoded is not None:
                        self.assertNotEqual(decoded, row, (hex(address), bit))
                        self.assertEqual(encode(decoded, address), changed, (hex(address), bit))
        self.assertEqual(mutations, 10752)

    def test_exact_reads_and10752_payload_bit_refusals_before_decode(self):
        pc, width, _ = RANGES[0]; body = BODIES[pc]; db = FakeDB(body)
        report = a.range_evidence(db, TEXT_MAPPING, pc, width)
        self.assertEqual(db.calls, EXPECTED_READS[:1]); self.assertEqual(report['width'], width)
        mutations = 0
        with patch.object(a, 'decode_selected') as decoder:
            for i in range(width):
                for bit in range(8):
                    changed = body[:i] + bytes([body[i] ^ 1 << bit]) + body[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(changed), TEXT_MAPPING, pc, width)
                    mutations += 1
            decoder.assert_not_called()
        self.assertEqual(mutations, 10752)

    def test_constants_exact_reads_hash_values_and96_bit_mutations(self):
        mutations = 0
        for (pc, width, digest, value), call in zip(CONSTANTS, EXPECTED_READS[1:]):
            raw = CONSTANT_BYTES[pc]; db = FakeDB(raw)
            self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
            row = a.constant_evidence(db, DATA5_MAPPING, pc, width)
            self.assertEqual(db.calls, [call]); self.assertEqual(row['value'], value)
            for i in range(4):
                for bit in range(8):
                    changed = raw[:i] + bytes([raw[i] ^ 1 << bit]) + raw[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'constant digest mismatch'):
                        a.constant_evidence(FakeDB(changed), DATA5_MAPPING, pc, width)
                    mutations += 1
        self.assertEqual(mutations, 96)

    def test_all47_control_flow_rows_only_two_direct_rng_calls(self):
        rows = [dict(address=f'{site:08x}', **row) for site, row in at().items()
                if row['mnemonic'] in ('b', 'bc', 'bl', 'blr')]
        self.assertEqual(a.expected_flow(0x80053b30), rows); self.assertEqual(len(rows), 47)
        self.assertEqual(rows[-1], dict(address='8005406c', mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
        self.assertTrue(all(0x80053b30 <= int(row['target'], 16) < 0x80054070
                            for row in rows if row['mnemonic'] in ('b', 'bc')))
        self.assertEqual([(row['address'], row['target']) for row in rows if row['mnemonic'] == 'bl'],
                         [('80053d60', '800055fc'), ('80053d80', '800055fc')])

    def test_clear_interleaving_actor_pointer_capture_and_two_traversals(self):
        rows = at()
        self.assertEqual([rows[pc] for pc in range(0x80053b5c, 0x80053b68, 4)],
                         ops('stw 4 5 0\nlwz 9 3 0x4e84\nstw 4 5 4'))
        self.assertEqual([row['displacement'] for pc, row in rows.items()
                          if pc < 0x80053bd4 and row['mnemonic'] == 'stw' and row['rA'] == 5],
                         list(range(0, 96, 4)))
        self.assertEqual([rows[pc] for pc in range(0x80053bac, 0x80053bd4, 4)], ops('''
stw 4 5 76
stb 4 13 -21308
stw 4 5 80
stb 4 7 1
stw 4 5 84
stb 4 7 2
stw 4 5 88
stw 4 5 92
stb 4 7 3
mtctr 0
'''))
        self.assertEqual(rows[0x80053b54], ops('addi 0 0 6')[0])
        self.assertEqual([rows[pc] for pc in range(0x80053c78, 0x80053ca0, 4)], ops('''
addi 8 8 1
addi 9 9 0x1e00
bc 16 0 80053bd4 0 0
addis 3 0 -32708
addi 0 0 3
addi 6 3 0x4e84
addi 4 1 8
addi 7 0 0
mtctr 0
lwz 8 6 0
'''))
        self.assertEqual(rows[0x80053cf8], ops('lwzu 8 6 4')[0])
        self.assertEqual([rows[pc] for pc in range(0x80053d54, 0x80053d64, 4)],
                         ops('addi 6 6 4\naddi 7 7 1\nbc 16 0 80053c9c 0 0\nbl 800055fc 0 1'))

    def test_mass_status_parameter_scale_and_team_store_order(self):
        rows = at()
        self.assertEqual([rows[pc] for pc in range(0x80053bd4, 0x80053c44, 4)], ops('''
lbz 0 9 0
extsb 0 0 1
bc 12 2 80053c78 0 0
lfs 0 2 -30672
addi 0 0 0
stb 0 8 0
stfs 0 9 0x204
lbz 0 9 0x18
extsb 0 0 0
cmpi 0 0 0 1
bc 12 2 80053c08 0 0
cmpi 0 0 0 2
bc 4 2 80053c34 0 0
lwz 3 9 0x4ac
lfs 0 2 -30668
lfs 1 3 0x98
fcmpo 0 1 0
bc 4 0 80053c2c 0 0
lfs 0 9 0xb4
fmuls 0 1 0
stfs 0 9 0x208
b 80053c38 0 0
stfs 1 9 0x208
b 80053c38 0 0
stfs 0 9 0x208
lbz 0 9 0x18
cmpi 0 0 0 1
bc 4 2 80053c78 0 0
'''))
        self.assertEqual([rows[pc] for pc in range(0x80053c44, 0x80053c78, 4)], ops('''
lbz 7 9 0x88
addis 3 0 -32708
addi 4 13 -21308
extsb 7 7 0
addi 5 3 0x6dec
lbzx 3 4 7
mulli 6 7 24
extsb 3 0 0
addi 3 3 1
add 5 5 6 0
rlwinm 0 0 2 0 29 0
stbx 3 4 7
stwx 9 5 0
'''))

    def test_propagation_add_before_contact_and_passenger_exact_order(self):
        rows = at()
        for base, skip, head in ((0x80053cb8, '80053cf8', '80053cec'),
                                 (0x80053d14, '80053d54', '80053d48')):
            self.assertEqual([rows[pc] for pc in range(base, base + 64, 4)], ops(f'''
lwz 9 9 0x1e4
lbz 0 9 0x83
extsb 0 0 1
bc 4 2 {skip} 0 0
lbz 0 9 0x3e4
lfs 1 9 0x204
lfs 0 8 0x208
extsb 0 5 0
lbzx 3 4 5
fadds 0 1 0
addi 0 3 1
stbx 0 4 5
stfs 0 9 0x204
lbz 0 9 0x1db
extsb 0 0 1
bc 4 2 {base:08x} 0 0
'''))
        for base, target in ((0x80053ca0, '80053cec'), (0x80053cfc, '80053d48')):
            self.assertEqual([rows[pc] for pc in range(base, base + 24, 4)], ops(f'''
lfs 1 8 0x204
or 8 9 8 0
lfs 0 8 0x208
fadds 0 1 0
stfs 0 8 0x204
b {target} 0 0
'''))

    def test_constants_selection_and_mapping_refusals(self):
        for pc, width, _, _ in CONSTANTS:
            for bad, size in ((pc - 1, width), (pc + 1, width), (float(pc), width),
                              (pc, 8), (pc, 0), (pc, True), (pc, float(width))):
                db = FakeDB(CONSTANT_BYTES[pc])
                with self.assertRaises(a.c.FormatError): a.constant_evidence(db, DATA5_MAPPING, bad, size)
                self.assertFalse(db.calls)
            for index, value in enumerate(DATA5_MAPPING):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    changed = list(DATA5_MAPPING); changed[index] = replacement; db = FakeDB(CONSTANT_BYTES[pc])
                    with self.assertRaises(a.c.FormatError): a.constant_evidence(db, tuple(changed), pc, width)
                    self.assertFalse(db.calls)
            db = FakeDB(CONSTANT_BYTES[pc])
            with self.assertRaises(a.c.FormatError):
                a.constant_evidence(db, list(DATA5_MAPPING), pc, width)
            self.assertFalse(db.calls)
            changed = tuple((a0, b0, c0, d0 + 1) if a0 == pc else (a0, b0, c0, d0)
                            for a0, b0, c0, d0 in CONSTANTS)
            with patch.object(a, 'CONSTANTS', changed):
                with self.assertRaisesRegex(a.c.FormatError, 'constant value mismatch'):
                    a.constant_evidence(FakeDB(CONSTANT_BYTES[pc]), DATA5_MAPPING, pc, width)
            with patch.object(a, 'CONSTANTS', CONSTANTS * 2):
                db = FakeDB(CONSTANT_BYTES[pc])
                with self.assertRaises(a.c.FormatError): a.constant_evidence(db, DATA5_MAPPING, pc, width)
                self.assertFalse(db.calls)
            for raw in (CONSTANT_BYTES[pc][:-1], CONSTANT_BYTES[pc] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'constant byte width'):
                    a.constant_evidence(FakeDB(raw), DATA5_MAPPING, pc, width)
        for pc in (0x8043724c, 0x8043725c, 0x803c4e84, 0x803c6dec, 0x80436264, 0x800055fc):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.constant_evidence(db, DATA5_MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_addresses_widths_duplicate_ranges_and_exact_typed_maps_refuse(self):
        for pc, width, _ in RANGES:
            for bad in (pc - 1, pc + 1, pc - 4, pc + 4, float(pc), True, -1, 1 << 32):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, bad, width)
                self.assertFalse(db.calls)
            for bad in (0, width - 4, width + 4, -width, True, float(width)):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, bad)
                self.assertFalse(db.calls)
            for index, value in enumerate(TEXT_MAPPING):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    changed = list(TEXT_MAPPING); changed[index] = replacement; db = FakeDB(BODIES[pc])
                    with self.assertRaises(a.c.FormatError): a.range_evidence(db, tuple(changed), pc, width)
                    self.assertFalse(db.calls)
            with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(BODIES[pc]), list(TEXT_MAPPING), pc, width)
            with patch.object(a, 'RANGES', RANGES * 2):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, width)
                self.assertFalse(db.calls)
            for raw in (BODIES[pc][:-1], BODIES[pc] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                    a.range_evidence(FakeDB(raw), TEXT_MAPPING, pc, width)
        for pc in (0x80053b2c, 0x80054070, 0x800055fc, 0x803c4e84, 0x803c6dec, 0x80436264, 0x80437250):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_decoder_bounds_reserved_bits_and_all_control_metadata_mutations(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x48000003, 0x94000000, 0x7c0802a7,
                     0x41820003, 0x4c000020, 0x4e808020, 0x84000000, 0x84210004):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x80053b30)
        original = a.decode_selected; mutations = 0
        for pc, width, _ in RANGES:
            with patch.object(a, 'decode_selected', return_value=None):
                with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                    a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
            for site, expected in at(pc).items():
                if expected['mnemonic'] not in ('bc', 'b', 'bl', 'blr', 'bclr'): continue
                for field, value in expected.items():
                    replacement = 'addi' if field == 'mnemonic' else '80000000' if field == 'target' else value ^ 1
                    def changed(word, address):
                        row = original(word, address)
                        return dict(row, **{field: replacement}) if address == site else row
                    with patch.object(a, 'decode_selected', changed):
                        with self.assertRaisesRegex(a.c.FormatError, 'complete control-flow mismatch'):
                            a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
                    mutations += 1
        self.assertEqual(mutations, 261)

    def test_authentication_precedes_parser_and_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad'); db.assert_not_called(); code.assert_not_called()

    def test_mapping_refusal_precedes_all_selections(self):
        blocks, subs = {}, {}
        for name, key, start, length, root in a.command.MAPPINGS:
            blocks[key] = [name, None, None, 15, start, length, 0]
            subs[key] = [key, 2, length, 0, root, 0]
        cases = []
        for key in (1, 5, 7):
            for field, value in ((0, 'wrong'), (4, blocks[key][4] + 4), (5, blocks[key][5] + 4), (6, 1)):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][field] = value; cases.append((bb, ss, '80000000'))
            for field in range(6):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][field] += 1; cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); bb[99] = copy.deepcopy(bb[key]); cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); ss[99] = copy.deepcopy(ss[key]); cases.append((bb, ss, '80000000'))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]
                cases.append((bb, ss, '80000000'))
        cases.append((blocks, subs, '80000004'))
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called()

    def test_no_arbitrary_cli_and_missing_snapshot(self):
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/scheduler.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
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
            raw = (SNAPSHOT_DIR / name).read_bytes(); digest = hashlib.sha256(raw).hexdigest(); reads = []
            def traced(db, *args):
                reads.append(args)
                return original(db, *args)
            with patch.object(a.c.GBF, 'chain', traced): a.c.inspect(raw, digest)
            cls.auth_reads.append(reads[:]); reads.clear()
            with patch.object(a.c.GBF, 'chain', traced): cls.reports.append(a.inspect(raw, digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_operands_complete_coverage_and_ceiling(self):
        for key in ('mappings', 'ranges', 'constants', 'function_coverage', 'selection_basis'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            for row in report['ranges']:
                pc = int(row['address'], 16)
                self.assertEqual(row['instructions'], [dict(address=f'{pc + i * 4:08x}', **op)
                                                       for i, op in enumerate(EXPECTED[pc])])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (4, 1356, 3))
            for key in ('pointer_following', 'global_payloads_read', 'callee_bodies_read',
                        'globals_runtime_values_established', 'original_execution'):
                self.assertFalse(basis[key])
            self.assertEqual(basis['first_unresolved_call_site'], '80053d60')
            self.assertIn('not original-DOL identity', report['caveat'])
            self.assertEqual(sum(row['represented_instructions'] for row in report['function_coverage']), 336)
            for row in report['function_coverage']:
                self.assertEqual(row['unrepresented_instructions'], 0); self.assertEqual(row['unrepresented_ranges'], [])
                self.assertEqual(row['selected_width'], row['map_size'])

    def test_exact_four_reads_after_full_unchanged_authentication(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(auth); self.assertTrue(all(row[0] == 263 for row in auth))

    def test_physical_spans_and_no_raw_output(self):
        for report in self.reports:
            row = report['ranges'][0]
            self.assertEqual(row['spans'], [dict(root_buffer=21, data_buffer=41, chain_offset=320848,
                data_offset=9666, length=1344, obfuscated=True, physical_offset=697800)])
            self.assertEqual(row['end_exclusive'], '80054070')
            self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
            self.assertFalse(any('word' in item for item in row['instructions']))
            for i, row in enumerate(report['constants']):
                self.assertEqual(row['spans'], [dict(root_buffer=263, data_buffer=264, chain_offset=2096 + 4 * i,
                    data_offset=2096 + 4 * i, length=4, obfuscated=True, physical_offset=4343862 + 4 * i)])
                self.assertEqual(set(row), {'address', 'width', 'sha256', 'value', 'spans'})

    def test_real_snapshot_hash_schema_and_each_payload_refuse_before_selection_or_decode(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes(); digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as code, patch.object(a, 'constant_evidence') as const:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            code.assert_not_called(); const.assert_not_called()
        original_tables = a.c.GBF.tables
        for name in ('Program', 'Property Table', 'File Bytes', 'ADDRESS MAP', 'Memory Blocks', 'Sub Memory Blocks'):
            for field in ('version', 'keytype', 'types', 'fields', 'missing'):
                def tampered_tables(db):
                    tables = copy.deepcopy(original_tables(db))
                    if field == 'missing': del tables[name]
                    elif field == 'types': tables[name][field] = [99]
                    elif field == 'fields': tables[name][field] = 'Wrong;'
                    else: tables[name][field] += 1
                    return tables
                with patch.object(a.c.GBF, 'tables', tampered_tables), patch.object(a, 'range_evidence') as code, \
                     patch.object(a, 'constant_evidence') as const:
                    with self.assertRaises(a.c.FormatError): a.inspect(raw, digest)
                    code.assert_not_called(); const.assert_not_called()
        original = a.c.GBF.chain
        for selected_call in EXPECTED_READS:
            def tampered(db, *args):
                payload, spans = original(db, *args)
                if args == selected_call: payload = bytes([payload[0] ^ 1]) + payload[1:]
                return payload, spans
            with patch.object(a.c.GBF, 'chain', tampered):
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)


if __name__ == '__main__': unittest.main()
