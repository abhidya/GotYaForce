#!/usr/bin/env python3
"""Independent inverse fixtures for429 instructions,1717-byte mutation/scope guards.

The semantic schedules below are frozen manual expectations. Tests do not
produce them from a decoder, its report, or an archive. Local snapshot controls
are optional and never fetch inputs. No model/runtime code is imported.
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

import read_archived_projectile_initialization_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
RANGES = (
    (0x8007dd84, 1148, 'e8732a065c806b75274606baf717082e907c68db87400e1a4299b77820148ec2'),
    (0x80089100, 568, 'aa8525094a1010f6a9580f8d8d8413754b0204b809fb9f18536f97a640d650e5'),
)
CELLS = (('variant1-hit-kind', 0x802d6da3, 1, '>b', (1,),
          '4bf5122f344554c53bde2ebb8cd2b7e3d1600ad631c385a5d7cce23c7785459a'),)
FIELDS = {'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'sth': 'rS rA displacement',
          'stb': 'rS rA displacement', 'stmw': 'rS rA displacement', 'lmw': 'rD rA displacement',
          'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement', 'lha': 'rD rA displacement',
          'lhz': 'rD rA displacement', 'lwzx': 'rD rA rB', 'lbzx': 'rD rA rB', 'stwx': 'rS rA rB',
          'lfs': 'fD rA displacement', 'lfd': 'fD rA displacement', 'stfs': 'fS rA displacement',
          'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'xoris': 'rS rA immediate',
          'mulli': 'rD rA immediate', 'or': 'rS rA rB Rc', 'mflr': 'rD', 'mtlr': 'rS',
          'bl': 'target AA LK', 'b': 'target AA LK', 'bc': 'BO BI LK target AA',
          'extsb': 'rS rA Rc', 'extsh': 'rS rA Rc', 'cmpi': 'BF L rA immediate',
          'cmpli': 'BF L rA immediate', 'cmp': 'BF L rA rB', 'blr': 'BO BI BH LK',
          'rlwinm': 'rS rA SH MB ME Rc', 'add': 'rD rA rB OE Rc', 'subf': 'rD rA rB OE Rc',
          'fadds': 'fD fA fB', 'fsubs': 'fD fA fB'}

FIELDS.update({'stfd': 'fS rA displacement', 'psq_st': 'fS rA displacement W I',
    'psq_l': 'fD rA displacement W I', 'bclr': 'BO BI BH LK', 'cror': 'BT BA BB',
    'frsp': 'fD fB', 'frsqrte': 'fD fB', 'fneg': 'fD fB', 'fmr': 'fD fB',
    'fcmpo': 'BF fA fB', 'fmuls': 'fD fA fC', 'fmul': 'fD fA fC',
    'fnmsub': 'fD fA fC fB', 'fdivs': 'fD fA fB'})


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


# Hand-authored semantic schedules, not decoder/report-generated fixtures.
EXPECTED = {0x8007dd84: ops('''
stwu 1 1 -272
mflr 0
stw 0 1 276
stfd 31 1 256
psq_st 31 1 264 0 0
stfd 30 1 240
psq_st 30 1 248 0 0
stmw 27 1 220
or 3 29 3 0
addis 4 0 -32764
lbz 0 3 0x11
addis 6 0 -32723
lwz 31 3 0x90
addi 5 0 1
extsb 0 7 0
addi 0 4 31396
rlwinm 7 4 0 24 31 0
stb 5 3 0x18
mulli 7 4 0x38
addi 6 6 28008
stw 0 3 0x100
addi 4 0 0
addi 5 0 1
add 30 6 7 0 0
bl 80089100 0 1
addi 0 0 0x14
or 29 3 29 0
stb 0 29 0x84
lha 0 31 0x72
sth 0 29 0x72
lbz 4 30 3
extsb 4 4 0
bl 8008ac80 0 1
cmpi 0 0 3 0
bc 4 2 0 8007de1c 0
addi 0 0 2
stb 0 29 0x18
b 8007e1dc 0 0
lbz 0 30 2
addi 4 30 4
addi 5 29 0x20
extsb 0 0 0
mulli 3 0 0x30
addi 3 3 0x8d4
add 3 31 3 0 0
bl 8020b7a8 0 1
lbz 0 30 0x2c
extsb 0 0 1
bc 12 2 0 8007de58 0
addi 3 29 0x20
addi 4 31 0x7b0
or 3 5 3 0
bl 8020ba54 0 1
lha 4 31 0x72
addis 3 0 0x4330
lwz 0 31 0xc8
xoris 4 4 0x8000
stw 3 1 200
lfd 1 2 -28744
cmpli 0 0 0 0
stw 4 1 204
lfs 2 2 -28788
lfd 0 1 200
lfs 31 2 -28792
fsubs 0 0 1
fmuls 30 2 0
bc 12 2 0 8007e024 0
addi 3 29 0x144
addi 4 29 0x20
addi 5 1 40
bl 8020ba78 0 1
lfs 0 1 40
lfs 1 1 48
fmuls 2 0 0
lfs 0 2 -28792
fmuls 1 1 1
fadds 4 2 1
fcmpo 0 4 0
bc 4 1 0 8007df0c 0
frsqrte 1 4
lfd 3 2 -28784
lfd 2 2 -28776
fmul 0 1 1
fmul 1 3 1
fnmsub 0 4 0 2
fmul 1 1 0
fmul 0 1 1
fmul 1 3 1
fnmsub 0 4 0 2
fmul 1 1 0
fmul 0 1 1
fmul 1 3 1
fnmsub 0 4 0 2
fmul 0 1 0
fmul 0 4 0
frsp 0 0
stfs 0 1 12
lfs 4 1 12
lfs 0 2 -28768
stfs 4 1 40
fcmpo 0 4 0
bc 4 0 0 8007df20 0
stfs 0 1 40
lfs 1 1 40
lfs 5 30 0x10
lfs 0 2 -28764
fmuls 6 1 1
lfs 1 30 0x28
fmuls 3 0 5
lfs 2 2 -28760
fmuls 4 1 6
lfs 1 1 44
lfs 0 2 -28792
fmuls 3 3 5
fdivs 4 4 3
fmuls 2 2 4
fadds 1 4 1
fmuls 1 2 1
fsubs 5 6 1
fcmpo 0 5 0
bc 4 0 0 8007df6c 0
fmr 5 0
lfs 0 2 -28792
fcmpo 0 5 0
bc 4 1 0 8007dfc8 0
frsqrte 1 5
lfd 3 2 -28784
lfd 2 2 -28776
fmul 0 1 1
fmul 1 3 1
fnmsub 0 5 0 2
fmul 1 1 0
fmul 0 1 1
fmul 1 3 1
fnmsub 0 5 0 2
fmul 1 1 0
fmul 0 1 1
fmul 1 3 1
fnmsub 0 5 0 2
fmul 0 1 0
fmul 0 5 0
frsp 0 0
stfs 0 1 8
lfs 2 1 8
b 8007dfcc 0 0
fmr 2 5
lfs 1 1 40
lfs 0 2 -28764
fsubs 1 1 2
fmuls 0 0 4
fdivs 1 1 0
bl 8023c240 0 1
frsp 1 1
lfs 0 2 -28756
fcmpo 0 1 0
fmr 31 1
cror 2 1 2
bc 4 2 0 8007e000 0
fmr 31 0
addi 3 29 0x144
addi 4 29 0x20
addi 5 1 28
bl 8020ba78 0 1
lfs 1 1 28
lfs 2 1 36
bl 8023cb78 0 1
frsp 0 1
fmr 30 0
fneg 1 31
addi 3 1 148
addi 4 0 120
bl 8020b238 0 1
fmr 1 30
addi 3 1 100
addi 4 0 121
bl 8020b238 0 1
addi 4 1 148
addi 3 1 100
or 4 5 4 0
bl 8020af5c 0 1
lfs 0 1 156
addi 3 29 0x38
or 3 4 3 0
stfs 0 29 0x38
lfs 0 1 172
stfs 0 29 0x3c
lfs 0 1 188
stfs 0 29 0x40
bl 8020bab8 0 1
addi 3 29 0x38
lfs 1 30 0x10
or 3 4 3 0
bl 8020ba9c 0 1
lfs 1 30 0x10
addi 3 0 1
lfs 0 2 -28792
addi 0 0 600
stfs 1 29 0x44
stfs 0 29 0x48
lfs 0 30 0x28
stfs 0 29 0x50
lwz 4 30 0x14
sth 4 29 0x1e
stb 3 29 0x19
sth 0 29 0x1c
lfs 0 30 0x30
stfs 0 29 0x154
lha 27 30 0
rlwinm 27 0 0 17 17 1
bc 12 2 0 8007e118 0
addis 3 0 -32708
lwz 4 29 0xe0
addi 28 3 -19668
rlwinm 27 5 0 18 31 0
lwz 3 28 72
bl 80006fb4 0 1
lbz 0 29 0x88
lfs 1 2 -28752
extsb 0 0 1
bc 12 2 0 8007e0f8 0
lfs 1 2 -28748
lwz 3 28 72
lwz 4 29 0xe0
bl 800086b8 0 1
lwz 3 29 0xe0
bl 80007c30 0 1
lwz 3 29 0xe0
bl 80007d40 0 1
b 8007e150 0 0
rlwinm 27 0 0 16 16 1
bc 12 2 0 8007e13c 0
addis 3 0 -32708
lwz 4 29 0xe0
addi 3 3 -19668
rlwinm 27 5 0 18 31 0
lwz 3 3 72
bl 80006fb4 0 1
b 8007e150 0 0
or 29 3 29 0
bl 80006f78 0 1
lwz 4 29 0xe0
or 27 5 27 0
bl 80006fb4 0 1
lbz 3 29 0x96
addi 0 3 49
stb 0 29 0x82
lbz 0 30 0x34
extsb 0 0 1
bc 12 0 0 8007e1cc 0
lfs 1 29 0x40
addi 3 1 52
lfs 0 2 -28792
addi 5 29 0x38
stfs 1 1 16
addi 6 1 16
addi 4 0 5
stfs 0 1 20
lfs 0 29 0x38
fneg 0 0
stfs 0 1 24
bl 80045ef4 0 1
lfs 0 29 0x20
or 31 3 31 0
lbz 5 30 0x34
addi 4 1 52
stfs 0 1 64
extsb 5 5 0
lfs 0 29 0x24
stfs 0 1 80
lfs 0 29 0x28
stfs 0 1 96
lbz 6 29 0x88
extsb 6 6 0
bl 800aedc0 0 1
or 29 3 29 0
bl 80047aa4 0 1
or 29 3 29 0
bl 8007e200 0 1
psq_l 31 1 264 0 0
lfd 31 1 256
psq_l 30 1 248 0 0
lfd 30 1 240
lmw 27 1 220
lwz 0 1 276
mtlr 0
addi 1 1 272
blr 20 0 0 0
'''), 0x80089100: ops('''
lwz 0 3 0x100
cmpli 0 0 0 0
bclr 12 2 0 0
rlwinm 4 0 0 25 25 1
stb 4 3 0x85
bc 12 2 0 80089198 0
cmpi 0 0 5 0
bc 4 2 0 8008915c 0
rlwinm 4 5 2 26 29 0
addi 4 13 -21280
lwzx 6 4 5
addi 0 0 0
stwx 3 4 5
cmpli 0 0 6 0
stw 0 3 0x104
bc 4 2 0 80089150 0
addi 4 13 -21288
stwx 3 4 5
stw 0 3 0x108
blr 20 0 0 0
stw 6 3 0x108
stw 3 6 0x104
blr 20 0 0 0
rlwinm 4 5 2 26 29 0
addi 4 13 -21288
lwzx 6 4 5
addi 0 0 0
stwx 3 4 5
cmpli 0 0 6 0
stw 0 3 0x108
bc 4 2 0 8008918c 0
addi 4 13 -21280
stwx 3 4 5
stw 0 3 0x104
blr 20 0 0 0
stw 6 3 0x104
stw 3 6 0x108
blr 20 0 0 0
rlwinm 4 0 0 26 26 1
bc 12 2 0 80089220 0
cmpi 0 0 5 0
bc 4 2 0 800891e4 0
rlwinm 4 5 2 26 29 0
addi 4 13 -21296
lwzx 6 4 5
addi 0 0 0
stwx 3 4 5
cmpli 0 0 6 0
stw 0 3 0x104
bc 4 2 0 800891d8 0
addi 4 13 -21304
stwx 3 4 5
stw 0 3 0x108
blr 20 0 0 0
stw 6 3 0x108
stw 3 6 0x104
blr 20 0 0 0
rlwinm 4 5 2 26 29 0
addi 4 13 -21304
lwzx 6 4 5
addi 0 0 0
stwx 3 4 5
cmpli 0 0 6 0
stw 0 3 0x108
bc 4 2 0 80089214 0
addi 4 13 -21296
stwx 3 4 5
stw 0 3 0x104
blr 20 0 0 0
stw 6 3 0x104
stw 3 6 0x108
blr 20 0 0 0
rlwinm 4 0 0 27 27 1
bc 12 2 0 800892b8 0
cmpi 0 0 5 0
bc 4 2 0 80089274 0
addis 5 0 -32708
rlwinm 4 6 2 26 29 0
addi 4 5 28500
addi 0 0 0
lwzx 5 4 6
stwx 3 4 6
cmpli 0 0 5 0
stw 0 3 0x104
bc 4 2 0 80089268 0
addis 4 0 -32708
addi 4 4 28476
stwx 3 4 6
stw 0 3 0x108
blr 20 0 0 0
stw 5 3 0x108
stw 3 5 0x104
blr 20 0 0 0
addis 5 0 -32708
rlwinm 4 6 2 26 29 0
addi 4 5 28476
addi 0 0 0
lwzx 5 4 6
stwx 3 4 6
cmpli 0 0 5 0
stw 0 3 0x108
bc 4 2 0 800892ac 0
addis 4 0 -32708
addi 4 4 28500
stwx 3 4 6
stw 0 3 0x104
blr 20 0 0 0
stw 5 3 0x104
stw 3 5 0x108
blr 20 0 0 0
cmpi 0 0 5 0
bc 4 2 0 800892fc 0
rlwinm 4 5 2 0 29 0
addi 4 13 -21264
lwzx 6 4 5
addi 0 0 0
stwx 3 4 5
cmpli 0 0 6 0
stw 0 3 0x104
bc 4 2 0 800892f0 0
addi 4 13 -21272
stwx 3 4 5
stw 0 3 0x108
blr 20 0 0 0
stw 6 3 0x108
stw 3 6 0x104
blr 20 0 0 0
rlwinm 4 5 2 0 29 0
addi 4 13 -21272
lwzx 6 4 5
addi 0 0 0
stwx 3 4 5
cmpli 0 0 6 0
stw 0 3 0x108
bc 4 2 0 8008932c 0
addi 4 13 -21264
stwx 3 4 5
stw 0 3 0x104
blr 20 0 0 0
stw 6 3 0x104
stw 3 6 0x108
blr 20 0 0 0
''')}


def encode(row, pc):
    """Independent PPC inverse; neither decoder nor tested report is consulted."""
    n = row['mnemonic']
    dforms = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
        'sth': (44, 'rS', 'displacement'), 'stb': (38, 'rS', 'displacement'),
        'stmw': (47, 'rS', 'displacement'), 'lmw': (46, 'rD', 'displacement'),
        'lwz': (32, 'rD', 'displacement'), 'lbz': (34, 'rD', 'displacement'),
        'lha': (42, 'rD', 'displacement'), 'lhz': (40, 'rD', 'displacement'),
        'lfs': (48, 'fD', 'displacement'), 'lfd': (50, 'fD', 'displacement'),
        'stfs': (52, 'fS', 'displacement'), 'stfd': (54, 'fS', 'displacement'), 'addi': (14, 'rD', 'immediate'),
        'addis': (15, 'rD', 'immediate'), 'xoris': (27, 'rS', 'immediate'),
        'mulli': (7, 'rD', 'immediate')}
    if n in dforms:
        opcode, reg, imm = dforms[n]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if n in ('mflr', 'mtlr'):
        xo, reg = (339, 'rD') if n == 'mflr' else (467, 'rS')
        return 31 << 26 | row[reg] << 21 | 8 << 16 | xo << 1
    if n in ('or', 'extsb', 'extsh', 'lwzx', 'lbzx', 'stwx'):
        reg = 'rD' if n in ('lwzx', 'lbzx') else 'rS'
        xo = {'or': 444, 'extsb': 954, 'extsh': 922, 'lwzx': 23, 'lbzx': 87, 'stwx': 151}[n]
        return 31 << 26 | row[reg] << 21 | row['rA'] << 16 | row.get('rB', 0) << 11 | xo << 1 | row.get('Rc', 0)
    if n in ('add', 'subf'):
        return 31 << 26 | row['rD'] << 21 | row['rA'] << 16 | row['rB'] << 11 | row['OE'] << 10 | (266 if n == 'add' else 40) << 1 | row['Rc']
    if n in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if n != 'bc':
            return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
        return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc | row['AA'] << 1 | row['LK']
    if n in ('blr', 'bclr'):
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    if n in ('cmpi', 'cmpli'):
        return (11 if n == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if n == 'cmp':
        return 31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['rB'] << 11
    if n == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    if n in ('fsubs', 'fadds'):
        return 59 << 26 | row['fD'] << 21 | row['fA'] << 16 | row['fB'] << 11 | (20 if n == 'fsubs' else 21) << 1
    if n in ('psq_l', 'psq_st'):
        op, reg = (56, 'fD') if n == 'psq_l' else (60, 'fS')
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['W'] << 15 | row['I'] << 12 | row['displacement'] & 4095
    if n == 'cror':
        return 19 << 26 | row['BT'] << 21 | row['BA'] << 16 | row['BB'] << 11 | 449 << 1
    if n in ('frsp', 'frsqrte', 'fneg', 'fmr'):
        xo = {'frsp': 12, 'frsqrte': 26, 'fneg': 40, 'fmr': 72}[n]
        return 63 << 26 | row['fD'] << 21 | row['fB'] << 11 | xo << 1
    if n == 'fcmpo':
        return 63 << 26 | row['BF'] << 23 | row['fA'] << 16 | row['fB'] << 11 | 32 << 1
    if n in ('fmul', 'fmuls', 'fnmsub', 'fdivs'):
        op = 59 if n in ('fmuls', 'fdivs') else 63
        xo = 30 if n == 'fnmsub' else 18 if n == 'fdivs' else 25
        return op << 26 | row['fD'] << 21 | row['fA'] << 16 | row.get('fB', 0) << 11 | row.get('fC', 0) << 6 | xo << 1
    raise AssertionError(n)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
PAYLOADS = dict(BODIES)
PAYLOADS[0x802d6da3] = struct.pack('>b', 1)
SELECTIONS = ((a.range_evidence, TEXT_MAPPING, 0x8007dd84, (1148,)),
              (a.range_evidence, TEXT_MAPPING, 0x80089100, (568,)),
              (a.cell_evidence, DATA3_MAPPING, 0x802d6da3, ()))
EXPECTED_READS = [(21, 493476, 1148, 2796416), (21, 539424, 568, 2796416),
                  (199, 114499, 1, 1000128)]


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_exact_inventory_mapping_and_signed_row1_arithmetic(self):
        self.assertEqual(a.RANGES, RANGES)
        self.assertEqual(a.CELLS, CELLS)
        for name in ('TEXT_MAPPING', 'DATA3_MAPPING'):
            self.assertEqual(getattr(a, name), globals()[name])
        self.assertEqual(sum(len(raw) for raw in PAYLOADS.values()), 1717)
        self.assertEqual(0x802d6d68 + 1 * 0x38 + 3, 0x802d6da3)
        self.assertEqual(CELLS[0][2:5], (1, '>b', (1,)))
        self.assertTrue(set(PAYLOADS).isdisjoint({0x8008ac80, 0x8007dcec, 0x8007e200,
            0x80047aa4, 0x802d6f98, 0x802d6da0, 0x802d6da2, 0x802d6da4,
            0x802d6d6b, 0x802d6ddb, 0x80436288, 0x80436290}))

    def test_all_429_operands_independent_inverse_and_hashes(self):
        controls = 0
        for pc, width, digest in RANGES:
            expected, body = EXPECTED[pc], BODIES[pc]
            self.assertEqual(len(expected), width // 4)
            self.assertEqual(len(body), width)
            self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
            result = a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
            self.assertEqual(result['instructions'], [dict(address=f'{pc + i * 4:08x}', **row)
                                                      for i, row in enumerate(expected)])
            for i, row in enumerate(expected):
                address = pc + i * 4
                word = encode(row, address)
                self.assertEqual(a.decode_selected(word, address), row)
                for bit in range(32):
                    changed = word ^ 1 << bit
                    controls += 1
                    try: decoded = a.decode_selected(changed, address)
                    except a.c.FormatError: continue
                    if decoded is not None:
                        self.assertNotEqual(decoded, row, (hex(address), bit))
                        self.assertEqual(encode(decoded, address), changed, (hex(address), bit))
        self.assertEqual(controls, 13728)

    def test_initializer_prefix_load_store_call_order_and_rejected_reordering(self):
        at = {0x8007dd84 + i * 4: row for i, row in enumerate(EXPECTED[0x8007dd84])}
        self.assertEqual(at[0x8007ddac], dict(mnemonic='lbz', rD=0, rA=3, displacement=0x11))
        self.assertEqual(at[0x8007ddb4], dict(mnemonic='lwz', rD=31, rA=3, displacement=0x90))
        self.assertEqual(at[0x8007ddc4], dict(mnemonic='rlwinm', rS=7, rA=4, SH=0, MB=24, ME=31, Rc=0))
        self.assertEqual(at[0x8007ddcc], dict(mnemonic='mulli', rD=7, rA=4, immediate=56))
        self.assertEqual(((at[0x8007dda8]['immediate'] << 16) + at[0x8007ddc0]['immediate']) & 0xffffffff,
                         0x80047aa4)
        self.assertEqual(((at[0x8007ddb0]['immediate'] << 16) + at[0x8007ddd0]['immediate']) & 0xffffffff,
                         0x802d6d68)
        self.assertEqual([(at[pc]['rD'], at[pc]['immediate']) for pc in (0x8007ddd8, 0x8007dddc)],
                         [(4, 0), (5, 1)])
        events = [(pc, row['mnemonic'], row.get('displacement'), row.get('target')) for pc, row in at.items()
                  if pc <= 0x8007de04 and (row['mnemonic'] == 'bl' or
                     row['mnemonic'] in ('stb', 'stw', 'sth') and row['rA'] != 1)]
        self.assertEqual(events, [(0x8007ddc8, 'stb', 24, None), (0x8007ddd4, 'stw', 256, None),
            (0x8007dde4, 'bl', None, '80089100'), (0x8007ddf0, 'stb', 132, None),
            (0x8007ddf8, 'sth', 114, None), (0x8007de04, 'bl', None, '8008ac80')])
        self.assertEqual(at[0x8007ddf4], dict(mnemonic='lha', rD=0, rA=31, displacement=0x72))
        self.assertEqual(at[0x8007ddfc], dict(mnemonic='lbz', rD=4, rA=30, displacement=3))
        self.assertEqual(at[0x8007de00], dict(mnemonic='extsb', rS=4, rA=4, Rc=0))
        self.assertEqual(at[0x8007de0c]['target'], '8007de1c')
        self.assertEqual(at[0x8007de14], dict(mnemonic='stb', rS=0, rA=29, displacement=24))
        self.assertEqual(at[0x8007de18]['target'], '8007e1dc')
        # Reordering two otherwise valid instructions must fail the payload hash.
        body = bytearray(BODIES[0x8007dd84])
        i, j = 0x8007ddac - 0x8007dd84, 0x8007ddb4 - 0x8007dd84
        body[i:i+4], body[j:j+4] = body[j:j+4], body[i:i+4]
        with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
            a.range_evidence(FakeDB(bytes(body)), TEXT_MAPPING, 0x8007dd84, 1148)

    def test_draw_list_actual01_sequence_separate_links_and_return_sites(self):
        at = {0x80089100 + i * 4: row for i, row in enumerate(EXPECTED[0x80089100])}
        self.assertEqual(at[0x80089100], dict(mnemonic='lwz', rD=0, rA=3, displacement=256))
        self.assertEqual(at[0x80089108], dict(mnemonic='bclr', BO=12, BI=2, BH=0, LK=0))
        self.assertEqual(at[0x80089110], dict(mnemonic='stb', rS=4, rA=3, displacement=133))
        self.assertEqual(at[0x800892bc]['target'], '800892fc')
        self.assertEqual(at[0x800892fc], dict(mnemonic='rlwinm', rS=4, rA=5, SH=2, MB=0, ME=29, Rc=0))
        self.assertEqual(at[0x80089300], dict(mnemonic='addi', rD=4, rA=13, immediate=-21272))
        self.assertEqual(at[0x80089304], dict(mnemonic='lwzx', rD=6, rA=4, rB=5))
        self.assertEqual(at[0x8008930c], dict(mnemonic='stwx', rS=3, rA=4, rB=5))
        self.assertEqual(at[0x80089314], dict(mnemonic='stw', rS=0, rA=3, displacement=264))
        self.assertEqual(at[0x80089318]['target'], '8008932c')
        self.assertEqual(at[0x8008931c], dict(mnemonic='addi', rD=4, rA=13, immediate=-21264))
        self.assertEqual(at[0x80089320], dict(mnemonic='stwx', rS=3, rA=4, rB=5))
        self.assertEqual(at[0x80089324], dict(mnemonic='stw', rS=0, rA=3, displacement=260))
        self.assertEqual(at[0x8008932c], dict(mnemonic='stw', rS=6, rA=3, displacement=260))
        self.assertEqual(at[0x80089330], dict(mnemonic='stw', rS=3, rA=6, displacement=264))
        self.assertEqual([r['displacement'] for r in at.values() if r['mnemonic'] == 'stw'],
                         [0x104, 0x108, 0x108, 0x104, 0x108, 0x104, 0x104, 0x108] * 4)
        self.assertFalse(any(row['mnemonic'] == 'bl' for row in at.values()))
        self.assertEqual(sum(row['mnemonic'] in ('blr', 'bclr') for row in at.values()), 17)

    def test_three_exact_reads_hashes_and_values(self):
        hashes = [r[2] for r in RANGES] + [r[5] for r in CELLS]
        for (fn, mapping, address, extra), call, digest in zip(SELECTIONS, EXPECTED_READS, hashes):
            db = FakeDB(PAYLOADS[address])
            result = fn(db, mapping, address, *extra)
            self.assertEqual(db.calls, [call])
            self.assertEqual(result['sha256'], digest)
            self.assertEqual(result['width'], len(PAYLOADS[address]))
        self.assertEqual([a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc)['values']
                          for _, pc, _, _, _, _ in CELLS], [[1]])

    def test_every_selected_byte_bit_mutation_refuses(self):
        mutations = 0
        for fn, mapping, address, extra in SELECTIONS:
            raw = PAYLOADS[address]
            for i in range(len(raw)):
                for bit in range(8):
                    changed = raw[:i] + bytes([raw[i] ^ 1 << bit]) + raw[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        fn(FakeDB(changed), mapping, address, *extra)
                    mutations += 1
        self.assertEqual(mutations, 13736)

    def test_allowlists_mapping_types_bounds_before_reads(self):
        for fn, mapping, address, extra in SELECTIONS:
            for bad in (address - 1, address + 1, address - 8, address + 8, float(address), True, -1, 1 << 32):
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
            for bad in (0, width - 4, width + 1, width + 4, -width, True, float(width)):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, bad)
                self.assertFalse(db.calls)
        for pc in (0x8008ac80, 0x8007dcec, 0x8007e200, 0x80047aa4, 0x80088d98, 0x8020b7a8, 0x8020ba54):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)
        for pc in (0x802d6d68, 0x802d6da0, 0x802d6da2, 0x802d6da4, 0x802d6f98):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.cell_evidence(db, DATA3_MAPPING, pc)
            self.assertFalse(db.calls)

    def test_truncation_duplicates_semantic_values_refuse(self):
        for fn, mapping, address, extra in SELECTIONS:
            for raw in (PAYLOADS[address][:-1], PAYLOADS[address] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'): fn(FakeDB(raw), mapping, address, *extra)
            name = 'RANGES' if extra else 'CELLS'
            with patch.object(a, name, getattr(a, name) * 2):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, address, *extra)
                self.assertFalse(db.calls)
        for label, pc, width, fmt, expected, digest in CELLS:
            with patch.object(a, 'CELLS', ((label, pc, width, fmt, (999,), digest),)):
                with self.assertRaisesRegex(a.c.FormatError, 'cell value mismatch'):
                    a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc)

    def test_reserved_bits_and_complete_body_fail_closed(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x4c820020, 0x48000002,
                     0x40800001, 0x2c2c0000, 0x28200000, 0x94000000, 0x7c0802a7,
                     0x7c000f75, 0xec000029, 0xec000068, 0x7c000001, 0x7c00002f):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x8007db5c)
        self.assertIsNone(a.decode_selected(0, 0x8007db5c))
        original = a.decode_selected
        for pc, width, _ in RANGES:
            body = BODIES[pc]
            for row in (None, dict(mnemonic='lbz', rD=0, rA=0, displacement=0)):
                with patch.object(a, 'decode_selected', return_value=row):
                    with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
            def outside(word, address):
                row = original(word, address)
                return dict(row, target=f'{pc + width:08x}') if row['mnemonic'] in ('bc', 'b') else row
            with patch.object(a, 'decode_selected', outside):
                with self.assertRaisesRegex(a.c.FormatError, 'branch outside'):
                    a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
            def wrong_call(word, address):
                row = original(word, address)
                return dict(row, target='80000000') if row['mnemonic'] == 'bl' else row
            if pc == 0x80089100: continue
            with patch.object(a, 'decode_selected', wrong_call):
                with self.assertRaisesRegex(a.c.FormatError, 'direct-call mismatch'):
                    a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)

    def test_authentication_precedes_parser_and_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, \
             patch.object(a, 'cell_evidence') as cell:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad')
            db.assert_not_called(); code.assert_not_called(); cell.assert_not_called()

    def test_real_hash_and_schema_refusals_precede_selections(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as selected:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(bytes(32), digest)
                db.assert_not_called(); selected.assert_not_called()
        data = b'synthetic schema fixture'
        digest = hashlib.sha256(data).hexdigest()
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

    def test_independent_extent_sources_row_and_no_address_cli(self):
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc, end, chunk in (('8007dd84', '8007e200', 'chunk_0011.c'),
                                ('80089100', '80089338', 'chunk_0013.c')):
            markers = (root / 'research/decomp/ghidra-export' / chunk).read_text()
            for address in (pc, end):
                self.assertIn(f'// ==== {address} ', markers)
                self.assertRegex(index, rf'{address}\t[^\t]+\t{chunk}')
            rows = [row for row in index.splitlines() if row.startswith((pc, end))]
            self.assertEqual(len(rows), 2)
            self.assertEqual(index.splitlines().index(rows[1]) - index.splitlines().index(rows[0]), 1)
        self.assertNotRegex(symbols, r'(?m)^8007dd84 ')
        self.assertIn('80089100 00000238 80089100 0 zz_0089100_', symbols)
        markers = (root / 'research/decomp/ghidra-export/chunk_0011.c').read_text()
        handler = markers.split('// ==== 8007dd84 ')[1].split('// ==== 8007e200 ')[0]
        for reference in ('* 0x38', 'DAT_802d6d68', 'zz_0089100_(param_9,0,1)',
                          'zz_008ac80_(param_9,(int)(char)(&DAT_802d6d6b)[iVar5])'):
            self.assertIn(reference, handler)
        self.assertEqual(0x802d6d6b + 0x38, 0x802d6da3)
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/projectile.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', json.loads(error.getvalue())['error'])

    def test_additional_FP_CR_and_quantized_forms_refuse_or_invert(self):
        for word in (0xfc010018, 0xfc000019, 0xfc200040, 0xfc000041, 0xfc000033,
                     0xec000064, 0xfc000832, 0x4c000383, 0x4d820021, 0x4d820820):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x8007dd84)
        for row in (dict(mnemonic='psq_l', fD=13, rA=17, displacement=-2048, W=1, I=7),
                    dict(mnemonic='psq_st', fS=21, rA=0, displacement=2047, W=1, I=4)):
            self.assertEqual(a.decode_selected(encode(row, 0x8007dd84), 0x8007dd84), row)


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

    def test_both_snapshots_all_operands_and_facts_agree(self):
        for key in ('mappings', 'ranges', 'cells', 'function_coverage', 'reused_evidence', 'row_selection'):
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
            self.assertEqual([r['values'] for r in report['cells']], [[1]])

    def test_exact_three_reads_after_unchanged_authenticator(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(all(row[0] == 263 for row in auth))
        report = self.reports[0]
        self.assertTrue(all(not row['read_here'] for row in report['reused_evidence'].values()))
        self.assertEqual([row['represented_instructions'] for row in report['function_coverage']], [287, 142])
        self.assertEqual([row['map_size'] for row in report['function_coverage']], [None, 568])
        for row in report['function_coverage']:
            self.assertEqual(row['unrepresented_instructions'], 0)
            self.assertEqual(row['unrepresented_ranges'], [])

    def test_physical_provenance_and_no_raw_output(self):
        expected = {0x8007dd84: (21, 52, 493476, 2136, 1148, 870494),
                    0x80089100: (21, 54, 539424, 15328, 568, 916454),
                    0x802d6da3: (199, 206, 114499, 16231, 1, 3407725)}
        for report in self.reports:
            for row in report['ranges'] + report['cells']:
                root, data, chain_offset, data_offset, length, physical = expected[int(row['address'], 16)]
                self.assertEqual(row['spans'], [dict(root_buffer=root, data_buffer=data, chain_offset=chain_offset,
                    data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)])
                self.assertEqual(row['end_exclusive'], f'{int(row["address"], 16) + row["width"]:08x}')
            for row in report['ranges']:
                self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
                self.assertFalse(any('word' in i for i in row['instructions']))
            for row in report['cells']:
                self.assertEqual(set(row), {'label', 'address', 'end_exclusive', 'width', 'values', 'sha256', 'spans'})

    def test_real_archive_tamper_and_selected_payload_tamper_refuse(self):
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
