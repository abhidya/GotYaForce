#!/usr/bin/env python3
"""Independent inverse fixtures for204 instructions,832-byte mutation/scope guards.

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

import read_archived_projectile_spawn_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
RANGES = (
    (0x8007db5c, 400, 'd759aaf2c9b38c2924ac451e7b29c4d67ef37c2d01492fc5654f04821eeaa0dc'),
    (0x80088aa0, 416, '800882bf558ba7e7f9e955e1884be71e0c9aad8870807bf7dc0876f56baaeab6'),
)
CELLS = (
    ('variant1-family', 0x802d6dce, 2, '>h', (3,), '583c7dfb7b3055d99465544032a571e10a134b1b6f769422bbb71fd7fa167a5d'),
    ('variant1-joint', 0x802d6da2, 1, '>b', (11,), 'e7cf46a078fed4fafd0b5e3aff144802b853f8ae459a4f0c14add3314b7cc3a6'),
    ('variant1-vector', 0x802d6da4, 12, '>fff', (55.0, 0.0, 0.0), 'f2c4bfd9a4763155499b7a93f506ddae33df56d5c4653e547547bdec2987ea19'),
    ('variant1-offset-flag', 0x802d6dcc, 1, '>b', (0,), '6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d'),
)
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


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


EXPECTED = {0x8007db5c: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
stw 30 1 24
stw 29 1 20
or 3 29 3 0
stw 28 1 16
or 4 28 4 0
rlwinm 28 0 0 24 31 0
addis 4 0 -32723
mulli 5 0 56
addi 0 4 28008
lha 4 3 0x3e8
add 30 0 5 0 0
lha 0 30 0x2e
cmp 0 0 4 0
bc 4 2 0 8007dccc 0
addi 4 0 3
addi 5 0 8
addi 6 0 0
addi 7 0 1
bl 80088aa0 0 1
or 3 31 3 1
bc 12 2 0 8007dccc 0
addi 0 0 1
addis 4 0 -32760
stb 0 31 0
addi 0 0 15
addi 6 4 -8980
addis 3 0 -32760
stb 0 31 0x10
addi 0 3 -6504
addi 4 30 4
addi 5 31 0x20
stb 28 31 0x11
stw 6 31 0xc
stw 0 31 0x10c
stw 29 31 0x8c
lwz 0 29 0x90
stw 0 31 0x90
lhz 0 29 0x94
sth 0 31 0x94
lbz 0 29 0x96
stb 0 31 0x96
lbz 0 29 0x97
stb 0 31 0x97
lbz 0 29 0x88
stb 0 31 0x88
lwz 0 29 0xc8
stw 0 31 0xc8
lwz 0 29 0xcc
stw 0 31 0xcc
lfs 0 29 0xb8
stfs 0 31 0xb8
lfs 0 29 0xb4
stfs 0 31 0xb4
lfs 0 29 0xb4
stfs 0 31 0x58
lfs 0 29 0xb4
stfs 0 31 0x5c
lfs 0 29 0xb4
stfs 0 31 0x60
lfs 0 29 0xc0
stfs 0 31 0xc0
lfs 0 29 0xc4
stfs 0 31 0xc4
lbz 0 29 0xd0
stb 0 31 0xd0
lbz 0 30 2
extsb 0 0 0
mulli 3 0 0x30
addi 3 3 0x8d4
add 3 29 3 0 0
bl 8020b7a8 0 1
lbz 0 30 0x2c
extsb 0 0 1
bc 12 2 0 8007dca4 0
addi 3 31 0x20
addi 4 29 0x7b0
or 3 5 3 0
bl 8020ba54 0 1
lwz 3 29 0x518
lwz 0 29 0x51c
stw 3 31 0x144
stw 0 31 0x148
lwz 0 29 0x520
stw 0 31 0x14c
lbz 0 29 0x1afc
stb 0 31 0x150
lbz 0 29 0x1afd
stb 0 31 0x151
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
lwz 28 1 16
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''), 0x80088aa0: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stmw 26 1 8
or 7 30 7 0
cmpi 0 0 30 8
or 3 26 3 0
or 4 29 4 0
or 5 28 5 0
or 6 27 6 0
bc 4 1 0 80088ad4 0
addi 3 0 0
b 80088c2c 0 0
addi 3 0 0
bl 80197bec 0 1
cmp 0 0 3 30
bc 4 0 0 80088aec 0
addi 3 0 0
b 80088c2c 0 0
or 29 3 29 0
bl 80088d98 0 1
or 3 31 3 1
bc 12 2 0 80088c28 0
stb 28 31 1
addi 0 0 -1
cmpi 0 0 28 -1
stb 0 31 0x85
bc 12 2 0 80088c28 0
cmpi 0 0 28 56
bc 4 0 0 80088b44 0
cmpli 0 0 26 0
bc 12 2 0 80088b44 0
lbz 0 26 0x83
extsb 0 0 1
bc 4 2 0 80088b44 0
rlwinm 28 0 0 29 31 1
bc 4 2 0 80088b44 0
lbz 0 26 0x3e4
extsb 0 0 0
add 28 0 28 0 0
addi 28 28 1
addis 3 0 -32722
stb 28 31 1
addi 3 3 -22784
cmpi 0 0 27 0
lbzx 0 3 28
stb 0 31 0x83
bc 4 2 0 80088ba4 0
addis 3 0 -32708
rlwinm 28 4 2 0 29 0
addi 3 3 28780
addi 0 0 0
lwzx 5 3 4
stwx 31 3 4
cmpli 0 0 5 0
stw 0 31 4
bc 4 2 0 80088b98 0
addis 3 0 -32708
addi 3 3 28524
stwx 31 3 4
stw 0 31 8
b 80088be4 0 0
stw 5 31 8
stw 31 5 4
b 80088be4 0 0
addis 3 0 -32708
rlwinm 28 4 2 0 29 0
addi 3 3 28524
addi 0 0 0
lwzx 5 3 4
stwx 31 3 4
cmpli 0 0 5 0
stw 0 31 8
bc 4 2 0 80088bdc 0
addis 3 0 -32708
addi 3 3 28780
stwx 31 3 4
stw 0 31 4
b 80088be4 0 0
stw 5 31 4
stw 31 5 8
lbz 0 31 2
cmpi 0 0 0 4
bc 12 2 0 80088c28 0
or 31 28 31 0
addi 27 0 0
addi 29 0 0
cmp 0 0 27 30
bc 4 0 0 80088c10 0
bl 80006d4c 0 1
stw 3 28 0xe0
b 80088c14 0 0
stw 29 28 0xe0
addi 27 27 1
addi 28 28 4
cmpi 0 0 27 8
bc 12 0 0 80088bfc 0
stb 30 31 0x99
or 31 3 31 0
lmw 26 1 8
lwz 0 1 36
mtlr 0
addi 1 1 32
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
        'stfs': (52, 'fS', 'displacement'), 'addi': (14, 'rD', 'immediate'),
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
    if n == 'blr':
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    if n in ('cmpi', 'cmpli'):
        return (11 if n == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if n == 'cmp':
        return 31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['rB'] << 11
    if n == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    if n in ('fsubs', 'fadds'):
        return 59 << 26 | row['fD'] << 21 | row['fA'] << 16 | row['fB'] << 11 | (20 if n == 'fsubs' else 21) << 1
    raise AssertionError(n)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
PAYLOADS = dict(BODIES)
PAYLOADS.update({0x802d6dce: struct.pack('>h', 3), 0x802d6da2: struct.pack('>b', 11),
                 0x802d6da4: struct.pack('>fff', 55.0, 0.0, 0.0), 0x802d6dcc: struct.pack('>b', 0)})
SELECTIONS = ((a.range_evidence, TEXT_MAPPING, 0x8007db5c, (400,)),
              (a.range_evidence, TEXT_MAPPING, 0x80088aa0, (416,)),
              (a.cell_evidence, DATA3_MAPPING, 0x802d6dce, ()),
              (a.cell_evidence, DATA3_MAPPING, 0x802d6da2, ()),
              (a.cell_evidence, DATA3_MAPPING, 0x802d6da4, ()),
              (a.cell_evidence, DATA3_MAPPING, 0x802d6dcc, ()))
EXPECTED_READS = [(21, 492924, 400, 2796416), (21, 537792, 416, 2796416),
                  (199, 114542, 2, 1000128), (199, 114498, 1, 1000128),
                  (199, 114500, 12, 1000128), (199, 114540, 1, 1000128)]


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_exact_inventory_mappings_and_row1_arithmetic(self):
        self.assertEqual(a.RANGES, RANGES)
        self.assertEqual(a.CELLS, CELLS)
        for name in ('TEXT_MAPPING', 'DATA3_MAPPING'):
            self.assertEqual(getattr(a, name), globals()[name])
        self.assertEqual(sum(len(raw) for raw in PAYLOADS.values()), 832)
        self.assertEqual(0x802d6d68 + 1 * 0x38, 0x802d6da0)
        self.assertEqual([(0x802d6da0 + offset, width) for offset, width in ((46, 2), (2, 1), (4, 12), (44, 1))],
                         [(pc, width) for _, pc, width, _, _, _ in CELLS])
        self.assertTrue(set(PAYLOADS).isdisjoint({0x8007dcec, 0x8007e698, 0x80088c40,
            0x80197bec, 0x80088d98, 0x80006d4c, 0x802d6d68, 0x802d6da0, 0x802da700,
            0x8020b7a8, 0x8020ba54}))

    def test_all_204_operands_independent_inverse_and_hashes(self):
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
        self.assertEqual(controls, 6528)

    def test_family_gate_allocation_argument_order_and_metadata_before_transform(self):
        at = {0x8007db5c + i * 4: row for i, row in enumerate(EXPECTED[0x8007db5c])}
        self.assertEqual(at[0x8007db80], dict(mnemonic='rlwinm', rS=28, rA=0, SH=0, MB=24, ME=31, Rc=0))
        self.assertEqual(at[0x8007db88], dict(mnemonic='mulli', rD=5, rA=0, immediate=56))
        self.assertEqual(at[0x8007db90], dict(mnemonic='lha', rD=4, rA=3, displacement=0x3e8))
        self.assertEqual(at[0x8007db98], dict(mnemonic='lha', rD=0, rA=30, displacement=0x2e))
        self.assertEqual(at[0x8007dba0]['target'], '8007dccc')
        self.assertEqual([(at[pc]['rD'], at[pc]['immediate']) for pc in
                          (0x8007dba4, 0x8007dba8, 0x8007dbac, 0x8007dbb0)], [(4, 3), (5, 8), (6, 0), (7, 1)])
        self.assertEqual(at[0x8007dbb4]['target'], '80088aa0')
        self.assertEqual(at[0x8007dbb8], dict(mnemonic='or', rS=3, rA=31, rB=3, Rc=1))
        self.assertEqual(at[0x8007dbbc]['target'], '8007dccc')
        stores = [(pc, r['mnemonic'], r['displacement']) for pc, r in at.items()
                  if r['mnemonic'] in ('stb', 'stw', 'sth', 'stfs') and r['rA'] == 31]
        self.assertEqual([offset for _, _, offset in stores], [0, 0x10, 0x11, 0xc, 0x10c, 0x8c,
            0x90, 0x94, 0x96, 0x97, 0x88, 0xc8, 0xcc, 0xb8, 0xb4, 0x58, 0x5c, 0x60,
            0xc0, 0xc4, 0xd0, 0x144, 0x148, 0x14c, 0x150, 0x151])
        self.assertEqual(((at[0x8007dbc4]['immediate'] << 16) + at[0x8007dbd0]['immediate']) & 0xffffffff, 0x8007dcec)
        self.assertEqual(((at[0x8007dbd4]['immediate'] << 16) + at[0x8007dbdc]['immediate']) & 0xffffffff, 0x8007e698)
        self.assertEqual([pc for pc, r in at.items() if r['mnemonic'] == 'lfs' and r.get('displacement') == 0xb4],
                         [0x8007dc38, 0x8007dc40, 0x8007dc48, 0x8007dc50])
        self.assertEqual(at[0x8007dc70], dict(mnemonic='lbz', rD=0, rA=30, displacement=2))
        self.assertEqual(at[0x8007dc74], dict(mnemonic='extsb', rS=0, rA=0, Rc=0))
        self.assertEqual(at[0x8007dc78]['immediate'], 0x30)
        self.assertEqual(at[0x8007dc7c]['immediate'], 0x8d4)
        self.assertEqual(at[0x8007dc84]['target'], '8020b7a8')
        self.assertEqual(at[0x8007dc88], dict(mnemonic='lbz', rD=0, rA=30, displacement=0x2c))
        self.assertEqual(at[0x8007dc90]['target'], '8007dca4')
        self.assertEqual(at[0x8007dca0]['target'], '8020ba54')
        self.assertEqual([(pc, r['mnemonic'], r.get('displacement')) for pc, r in at.items()
                          if 0x8007dca4 <= pc <= 0x8007dcc8],
                         [(0x8007dca4, 'lwz', 0x518), (0x8007dca8, 'lwz', 0x51c),
                          (0x8007dcac, 'stw', 0x144), (0x8007dcb0, 'stw', 0x148),
                          (0x8007dcb4, 'lwz', 0x520), (0x8007dcb8, 'stw', 0x14c),
                          (0x8007dcbc, 'lbz', 0x1afc), (0x8007dcc0, 'stb', 0x150),
                          (0x8007dcc4, 'lbz', 0x1afd), (0x8007dcc8, 'stb', 0x151)])

    def test_allocator_capacity_pool_remap_link_and_descriptor_order(self):
        at = {0x80088aa0 + i * 4: row for i, row in enumerate(EXPECTED[0x80088aa0])}
        self.assertEqual(at[0x80088ab4], dict(mnemonic='cmpi', BF=0, L=0, rA=30, immediate=8))
        self.assertEqual(at[0x80088ac8], dict(mnemonic='bc', BO=4, BI=1, LK=0, target='80088ad4', AA=0))
        self.assertEqual([(pc, r['target']) for pc, r in at.items() if r['mnemonic'] == 'bl'],
                         [(0x80088ad8, '80197bec'), (0x80088af0, '80088d98'), (0x80088c04, '80006d4c')])
        self.assertEqual(at[0x80088adc], dict(mnemonic='cmp', BF=0, L=0, rA=3, rB=30))
        self.assertEqual(at[0x80088b20], dict(mnemonic='lbz', rD=0, rA=26, displacement=0x83))
        self.assertEqual(at[0x80088b34], dict(mnemonic='lbz', rD=0, rA=26, displacement=0x3e4))
        self.assertEqual(at[0x80088b38], dict(mnemonic='extsb', rS=0, rA=0, Rc=0))
        for high, low, expected in ((0x80088b44, 0x80088b4c, 0x802da700),
                                    (0x80088b60, 0x80088b68, 0x803c706c),
                                    (0x80088b84, 0x80088b88, 0x803c6f6c)):
            self.assertEqual(((at[high]['immediate'] << 16) + at[low]['immediate']) & 0xffffffff, expected)
        self.assertEqual(at[0x80088b54], dict(mnemonic='lbzx', rD=0, rA=3, rB=28))
        self.assertEqual(at[0x80088b74], dict(mnemonic='stwx', rS=31, rA=3, rB=4))
        self.assertEqual(at[0x80088b7c], dict(mnemonic='stw', rS=0, rA=31, displacement=4))
        self.assertEqual(at[0x80088be4], dict(mnemonic='lbz', rD=0, rA=31, displacement=2))
        self.assertEqual(at[0x80088be8]['immediate'], 4)
        self.assertEqual(at[0x80088bfc], dict(mnemonic='cmp', BF=0, L=0, rA=27, rB=30))
        self.assertEqual(at[0x80088c08], dict(mnemonic='stw', rS=3, rA=28, displacement=0xe0))
        self.assertEqual(at[0x80088c10], dict(mnemonic='stw', rS=29, rA=28, displacement=0xe0))
        self.assertEqual(at[0x80088c1c]['immediate'], 8)
        self.assertEqual(at[0x80088c20], dict(mnemonic='bc', BO=12, BI=0, LK=0, target='80088bfc', AA=0))
        self.assertEqual(at[0x80088c24], dict(mnemonic='stb', rS=30, rA=31, displacement=0x99))

    def test_six_exact_reads_hashes_and_values(self):
        hashes = [r[2] for r in RANGES] + [r[5] for r in CELLS]
        for (fn, mapping, address, extra), call, digest in zip(SELECTIONS, EXPECTED_READS, hashes):
            db = FakeDB(PAYLOADS[address])
            result = fn(db, mapping, address, *extra)
            self.assertEqual(db.calls, [call])
            self.assertEqual(result['sha256'], digest)
            self.assertEqual(result['width'], len(PAYLOADS[address]))
        self.assertEqual([a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc)['values']
                          for _, pc, _, _, _, _ in CELLS], [[3], [11], [55.0, 0.0, 0.0], [0]])

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
        self.assertEqual(mutations, 6656)

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
        for pc in (0x8007dcec, 0x8007e698, 0x80088d98, 0x80197bec, 0x80006d4c, 0x8020b7a8, 0x8020ba54):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)
        for pc in (0x802d6d68, 0x802d6da0, 0x802d6dd8, 0x802d6e10, 0x802da700):
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

    def test_mapping_refusals_precede_six_selections(self):
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

    def test_independent_extent_sources_row_fields_and_no_address_cli(self):
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc, end, chunk, width in (('8007db5c', '8007dcec', 'chunk_0011.c', 400),
                                      ('80088aa0', '80088c40', 'chunk_0012.c', 416)):
            markers = (root / 'research/decomp/ghidra-export' / chunk).read_text()
            for address in (pc, end):
                self.assertIn(f'// ==== {address} ', markers)
                self.assertRegex(index, rf'{address}\t[^\t]+\t{chunk}')
            self.assertIn(f'{pc} {width:08x} {pc} 0 zz_00{pc[3:]}_', symbols)
        markers = (root / 'research/decomp/ghidra-export/chunk_0011.c').read_text()
        spawn = markers.split('// ==== 8007db5c ')[1].split('// ==== 8007dcec ')[0]
        for reference in ('* 0x38', 'DAT_802d6d96', 'DAT_802d6d6a', '-0x7fd29294', 'DAT_802d6d94'):
            self.assertIn(reference, spawn)
        self.assertEqual(-0x7fd29294 & 0xffffffff, 0x802d6d6c)
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
            self.assertEqual([r['values'] for r in report['cells']], [[3], [11], [55.0, 0.0, 0.0], [0]])

    def test_exact_six_reads_after_unchanged_authenticator(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(all(row[0] == 263 for row in auth))
        report = self.reports[0]
        self.assertTrue(all(not row['read_here'] for row in report['reused_evidence'].values()))
        self.assertEqual([row['represented_instructions'] for row in report['function_coverage']], [100, 104])
        for row in report['function_coverage']:
            self.assertEqual(row['unrepresented_instructions'], 0)
            self.assertEqual(row['map_size'], row['selected_width'])

    def test_physical_provenance_and_no_raw_output(self):
        expected = {0x8007db5c: (21, 52, 492924, 1584, 400, 869942),
                    0x80088aa0: (21, 54, 537792, 13696, 416, 914822),
                    0x802d6dce: (199, 206, 114542, 16274, 2, 3407768),
                    0x802d6da2: (199, 206, 114498, 16230, 1, 3407724),
                    0x802d6da4: (199, 206, 114500, 16232, 12, 3407726),
                    0x802d6dcc: (199, 206, 114540, 16272, 1, 3407766)}
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
