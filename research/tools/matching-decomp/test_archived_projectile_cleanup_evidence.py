#!/usr/bin/env python3
"""Independent semantic/inverse fixtures:273 instructions,1100 bytes,9 reads.

Expected operands are manually authored, never loaded from reader output,
an archive or its decoder. Optional existing snapshots are used in place.
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

import read_archived_projectile_cleanup_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
RANGES = (
    (0x8007e678, 32, '3e7f2e5665b4173038c13f23df183d62e6483e1258dff141a07504568b6ef994'),
    (0x80088e50, 328, 'c747b919f60eaad0d8b255db2b1fdc9ecb0bd22cea33c4930d1085dcdf34d3f4'),
    (0x80089444, 272, '662fe9d92fabf618cf21cc81fdcc266d090bda7b674bc9ad28266a89be6e2bf2'),
    (0x80006d80, 72, 'af3ef03d2ff4dfbd26b5e33794ffac72543f7b6b70aaa2a0c7f7af14cdf13768'),
    (0x80197ad8, 188, 'e3650544ce98694f5c3a5ca208c4dfe1479fbc02f46712a3a8a75d8d210c9082'),
    (0x80089814, 132, '1bb689f99364d17b27d89cf9d15ceb89ffde7be29dc90d4bba30b495975710dd'),
    (0x80006ed8, 68, 'cedb8b8e89d09bc76af3e72117c07093a720afee20d40d3d397737a9353c2492'),
)
CELLS = (
    ('cleanup-state3', 0x802d6fa4, 4, 0x8007e678,
     'a6c03f0cd98471891b5199d09bdedc269455f2281a76e92818c15baaef0ed389'),
    ('descriptor0-release-callback', 0x8036f65c, 4, 0x80006ed8,
     '6146361b1fa0fc8c864ab07ecfd5700f34b9dee55187fc418c57c1403c63a484'),
)
FIELDS = {
    'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement',
    'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement',
    'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'mulli': 'rD rA immediate',
    'or': 'rS rA rB Rc', 'add': 'rD rA rB Rc', 'extsb': 'rS rA Rc',
    'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS', 'lwzx': 'rD rA rB',
    'stwx': 'rS rA rB', 'lhzx': 'rD rA rB', 'lhax': 'rD rA rB', 'sthx': 'rS rA rB',
    'bl': 'target AA LK', 'b': 'target AA LK', 'bc': 'BO BI target AA LK',
    'blr': 'BO BI BH LK', 'bclr': 'BO BI BH LK', 'bctrl': 'BO BI BH LK',
    'rlwinm': 'rS rA SH MB ME Rc', 'cmpi': 'BF L rA immediate',
    'cmpli': 'BF L rA immediate', 'cmp': 'BF L rA rB',
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


EXPECTED = {
    0x8007e678: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
bl 80088e50 0 1
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x80088e50: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
or 3 31 3 0
stw 30 1 24
stw 29 1 20
lbz 3 3 1
extsb 3 0 0
cmpi 0 0 0 -1
bc 12 2 80088f74 0 0
lwz 5 31 4
lwz 6 31 8
cmpli 0 0 5 0
bc 4 2 80088ec4 0 0
cmpli 0 0 6 0
bc 4 2 80088ec4 0 0
addis 4 0 -32708
addis 3 0 -32708
rlwinm 0 0 2 0 29 0
addi 5 0 0
addi 4 4 28780
addi 3 3 28524
stwx 5 4 0
lbz 0 31 1
extsb 0 0 0
rlwinm 0 0 2 0 29 0
stwx 5 3 0
b 80088f2c 0 0
cmpli 0 0 5 0
bc 4 2 80088ef4 0 0
cmpli 0 0 6 0
bc 12 2 80088ef4 0 0
extsb 3 0 0
addis 3 0 -32708
rlwinm 0 4 2 0 29 0
addi 0 0 0
addi 3 3 28780
stwx 6 3 4
stw 0 6 4
b 80088f2c 0 0
cmpli 0 0 5 0
bc 12 2 80088f24 0 0
cmpli 0 0 6 0
bc 4 2 80088f24 0 0
extsb 3 0 0
addis 3 0 -32708
rlwinm 0 4 2 0 29 0
addi 0 0 0
addi 3 3 28524
stwx 5 3 4
stw 0 5 8
b 80088f2c 0 0
stw 6 5 8
stw 5 6 4
lbz 0 31 2
cmpi 0 0 0 4
bc 12 2 80088f74 0 0
or 31 3 31 0
bl 80089444 0 1
or 31 30 31 0
addi 29 0 0
b 80088f64 0 0
lwz 3 30 0xe0
cmpli 0 0 3 0
bc 12 2 80088f5c 0 0
bl 80006d80 0 1
addi 30 30 4
addi 29 29 1
lbz 0 31 0x99
extsb 0 0 0
cmp 0 0 29 0
bc 12 0 80088f4c 0 0
or 31 3 31 0
bl 80089814 0 1
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
    0x80089444: ops('''
lbz 0 3 0x85
extsb 0 6 0
cmpi 0 0 6 -1
bclr 12 2 0 0
rlwinm 6 0 0 25 25 1
lwz 7 3 0x104
lwz 8 3 0x108
bc 12 2 8008947c 0 0
rlwinm 6 0 2 26 29 0
addi 4 13 -21280
addi 5 13 -21288
add 4 4 0 0
add 5 5 0 0
b 800894d8 0 0
rlwinm 6 0 0 26 26 1
bc 12 2 8008949c 0 0
rlwinm 6 0 2 26 29 0
addi 4 13 -21296
addi 5 13 -21304
add 4 4 0 0
add 5 5 0 0
b 800894d8 0 0
rlwinm 6 0 0 27 27 1
bc 12 2 800894c4 0 0
addis 5 0 -32708
addis 4 0 -32708
rlwinm 6 6 2 26 29 0
addi 5 5 28500
addi 0 4 28476
add 4 5 6 0
add 5 0 6 0
b 800894d8 0 0
rlwinm 6 0 2 0 29 0
addi 4 13 -21264
addi 5 13 -21272
add 4 4 0 0
add 5 5 0 0
cmpli 0 0 7 0
bc 4 2 800894f8 0 0
cmpli 0 0 8 0
bc 4 2 800894f8 0 0
addi 0 0 0
stw 0 4 0
stw 0 5 0
b 80089540 0 0
cmpli 0 0 7 0
bc 4 2 80089518 0 0
cmpli 0 0 8 0
bc 12 2 80089518 0 0
stw 8 4 0
addi 0 0 0
stw 0 8 0x104
b 80089540 0 0
cmpli 0 0 7 0
bc 12 2 80089538 0 0
cmpli 0 0 8 0
bc 4 2 80089538 0 0
stw 7 5 0
addi 0 0 0
stw 0 7 0x108
b 80089540 0 0
stw 8 7 0x108
stw 7 8 0x104
addi 4 0 0
addi 0 0 -1
stw 4 3 0x100
stb 0 3 0x85
blr 20 0 0 0
'''),
    0x80006d80: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lwz 3 3 0xc
cmpli 0 0 3 0
bc 12 2 80006dac 0 0
bl 8024fd74 0 1
addi 0 0 0
stw 0 31 0xc
or 31 3 31 0
bl 80197ad8 0 1
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x80197ad8: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
stw 30 1 24
stw 29 1 20
or 3 29 3 1
bc 12 2 80197b78 0 0
lbz 5 29 8
lwz 4 13 -21024
extsb 5 5 0
mulli 0 5 28
or 5 30 5 0
add 31 4 0 0
lwz 12 31 0x18
cmpli 0 0 12 0
bc 12 2 80197b24 0 0
mtctr 12
bctrl 20 0 0 1
lwz 4 29 0
lwz 3 29 4
cmpli 0 0 4 0
bc 12 2 80197b3c 0 0
stw 3 4 4
b 80197b40 0 0
stw 3 31 8
cmpli 0 0 3 0
bc 12 2 80197b4c 0 0
stw 4 3 0
lwz 4 31 0xc
addi 0 0 0
or 30 3 30 0
stw 4 29 0
stw 29 31 0xc
stb 0 29 9
bl 80197bec 0 1
or 3 4 3 0
or 30 3 30 0
addi 4 4 1
bl 80197bd8 0 1
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
    0x80089814: ops('''
lbz 0 3 3
addis 4 0 -32708
addi 4 4 29068
extsb 0 0 0
rlwinm 0 0 2 0 29 0
lwzx 5 4 0
cmpli 0 0 5 0
bc 4 2 80089854 0 0
stwx 3 4 0
addis 4 0 -32708
addi 4 4 29036
lbz 0 3 3
extsb 0 0 0
rlwinm 0 0 2 0 29 0
stwx 3 4 0
b 80089868 0 0
stw 3 5 4
lbz 0 3 3
extsb 0 0 0
rlwinm 0 0 2 0 29 0
stwx 3 4 0
lbz 6 3 3
addis 4 0 -32708
addi 5 4 29100
addi 0 0 0
extsb 6 4 0
rlwinm 4 6 1 0 30 0
lhzx 4 5 6
addi 4 4 1
sthx 4 5 6
stb 0 3 0
stw 0 3 4
blr 20 0 0 0
'''),
    0x80006ed8: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lwz 3 3 0xc
cmpli 0 0 3 0
bc 12 2 80006f04 0 0
bl 8024fd74 0 1
addi 0 0 0
stw 0 31 0xc
lwz 0 1 20
addi 3 0 0
lwz 31 1 12
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
}


def encode(row, pc):
    """Independent PPC inverse; no decoder, reader report or archive inputs."""
    name = row['mnemonic']
    forms = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
             'stb': (38, 'rS', 'displacement'), 'lwz': (32, 'rD', 'displacement'),
             'lbz': (34, 'rD', 'displacement'), 'addi': (14, 'rD', 'immediate'),
             'addis': (15, 'rD', 'immediate'), 'mulli': (7, 'rD', 'immediate')}
    if name in forms:
        opcode, reg, imm = forms[name]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name in ('mflr', 'mtlr', 'mtctr'):
        return (31 << 26 | row['rD' if name == 'mflr' else 'rS'] << 21 |
                (9 if name == 'mtctr' else 8) << 16 | (339 if name == 'mflr' else 467) << 1)
    if name in ('or', 'add', 'lwzx', 'stwx', 'lhzx', 'lhax', 'sthx'):
        xo, reg = {'or': (444, 'rS'), 'add': (266, 'rD'), 'lwzx': (23, 'rD'),
                   'stwx': (151, 'rS'), 'lhzx': (279, 'rD'), 'lhax': (343, 'rD'), 'sthx': (407, 'rS')}[name]
        return (31 << 26 | row[reg] << 21 | row['rA'] << 16 | row['rB'] << 11 |
                xo << 1 | row.get('Rc', 0))
    if name == 'extsb':
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | 954 << 1 | row['Rc']
    if name in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if name == 'bc':
            return (16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc |
                    row['AA'] << 1 | row['LK'])
        return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name in ('blr', 'bclr', 'bctrl'):
        return (19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 |
                (528 if name == 'bctrl' else 16) << 1 | row['LK'])
    if name == 'rlwinm':
        return (21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 |
                row['MB'] << 6 | row['ME'] << 1 | row['Rc'])
    if name in ('cmpi', 'cmpli', 'cmp'):
        return ((31 if name == 'cmp' else 11 if name == 'cmpi' else 10) << 26 |
                row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 |
                (row['rB'] << 11 if name == 'cmp' else row['immediate'] & 65535))
    raise AssertionError(name)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
PAYLOADS = dict(BODIES)
PAYLOADS.update({pc: struct.pack('>I', target) for _, pc, _, target, _ in CELLS})
SELECTIONS = tuple((a.cell_evidence, DATA3_MAPPING, pc, width) for _, pc, width, _, _ in CELLS) + \
             tuple((a.range_evidence, TEXT_MAPPING, pc, width) for pc, width, _ in RANGES)
EXPECTED_READS = [(199, 115012, 4, 1000128), (199, 739324, 4, 1000128),
                  (21, 495768, 32, 2796416), (21, 538736, 328, 2796416),
                  (21, 540260, 272, 2796416), (21, 6048, 72, 2796416),
                  (21, 1647864, 188, 2796416), (21, 541236, 132, 2796416),
                  (21, 6392, 68, 2796416)]


def at(entry):
    return {entry + i * 4: row for i, row in enumerate(EXPECTED[entry])}


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_derivations_and_two_independent_identity_joins(self):
        self.assertEqual(a.RANGES, RANGES); self.assertEqual(a.CELLS, CELLS)
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING); self.assertEqual(a.DATA3_MAPPING, DATA3_MAPPING)
        self.assertEqual((a.TABLE_ROOT, a.SIGNED_STATE, a.ENTRY_WIDTH), (0x802d6f98, 3, 4))
        self.assertEqual((a.DESCRIPTOR_ROOT, a.DESCRIPTOR_ROW, a.DESCRIPTOR_STRIDE, a.RELEASE_OFFSET),
                         (0x8036f644, 0, 28, 24))
        self.assertEqual(0x802d6f98 + 3 * 4, CELLS[0][1])
        self.assertEqual(0x8036f644 + 0 * 28 + 24, CELLS[1][1])
        self.assertEqual(CELLS[0][3], RANGES[0][0]); self.assertEqual(CELLS[1][3], RANGES[6][0])
        self.assertEqual(len(SELECTIONS), 9); self.assertEqual(sum(map(len, PAYLOADS.values())), 1100)
        self.assertEqual(sum(map(len, EXPECTED.values())), 273)
        self.assertTrue(set(PAYLOADS).isdisjoint({0x8008aff0, 0x80197bec, 0x80197bd8,
                                                 0x8024fd74, 0x802d6fa0, 0x8036f658}))

    def test_all273_operands_independent_inverse_hash_and8736_bit_controls(self):
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
        self.assertEqual(mutations, 8736)

    def test_exact_reads_and8800_selected_payload_bit_refusals(self):
        mutations = 0
        for (fn, mapping, pc, width), call in zip(SELECTIONS, EXPECTED_READS):
            raw = PAYLOADS[pc]; db = FakeDB(raw)
            result = fn(db, mapping, pc, width)
            self.assertEqual(db.calls, [call]); self.assertEqual(result['width'], width)
            self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
            for i in range(len(raw)):
                for bit in range(8):
                    changed = raw[:i] + bytes([raw[i] ^ 1 << bit]) + raw[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        fn(FakeDB(changed), mapping, pc, width)
                    mutations += 1
        self.assertEqual(mutations, 8800)

    def test_complete_branches_returns_calls_indirect_dispatch_and_local_targets(self):
        counts = []
        for pc, width, _ in RANGES:
            rows = [dict(address=f'{site:08x}', **row) for site, row in at(pc).items()
                    if row['mnemonic'] in ('b', 'bc', 'bl', 'blr', 'bclr', 'bctrl')]
            self.assertEqual(a.expected_flow(pc), rows)
            self.assertEqual(rows[-1], dict(address=f'{pc + width - 4:08x}',
                                           mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
            self.assertTrue(all(pc <= int(row['target'], 16) < pc + width
                                for row in rows if row['mnemonic'] in ('b', 'bc')))
            counts.append(len(rows))
        self.assertEqual(counts, [2, 18, 17, 4, 9, 3, 3])
        self.assertEqual([(hex(pc), r['mnemonic']) for entry in EXPECTED for pc, r in at(entry).items()
                          if r['mnemonic'] in ('bctrl', 'bclr')],
                         [('0x80089450', 'bclr'), ('0x80197b20', 'bctrl')])

    def test_group_gate_four_link_cases_and_descriptor_loop_order(self):
        rows = at(0x80088e50)
        self.assertEqual(rows[0x80088e74], ops('cmpi 0 0 0 -1')[0])
        self.assertEqual(rows[0x80088e78], ops('bc 12 2 80088f74 0 0')[0])
        self.assertEqual(rows[0x80088f34], ops('bc 12 2 80088f74 0 0')[0])
        stores = [(pc, r) for pc, r in rows.items() if r['mnemonic'] in ('stw', 'stwx') and pc >= 0x80088eac]
        self.assertEqual(stores, [(0x80088eac, ops('stwx 5 4 0')[0]),
            (0x80088ebc, ops('stwx 5 3 0')[0]), (0x80088ee8, ops('stwx 6 3 4')[0]),
            (0x80088eec, ops('stw 0 6 4')[0]), (0x80088f18, ops('stwx 5 3 4')[0]),
            (0x80088f1c, ops('stw 0 5 8')[0]), (0x80088f24, ops('stw 6 5 8')[0]),
            (0x80088f28, ops('stw 5 6 4')[0])])
        self.assertEqual([r['target'] for r in rows.values() if r['mnemonic'] == 'bl'],
                         ['80089444', '80006d80', '80089814'])
        self.assertEqual([rows[pc] for pc in range(0x80088f4c, 0x80088f74, 4)], ops('''
lwz 3 30 0xe0
cmpli 0 0 3 0
bc 12 2 80088f5c 0 0
bl 80006d80 0 1
addi 30 30 4
addi 29 29 1
lbz 0 31 0x99
extsb 0 0 0
cmp 0 0 29 0
bc 12 0 80088f4c 0 0
'''))

    def test_draw_unlink_early_return_precedence_and_final_store_order(self):
        rows = at(0x80089444)
        self.assertEqual(rows[0x80089450], ops('bclr 12 2 0 0')[0])
        self.assertEqual([rows[pc] for pc in (0x80089454, 0x8008947c, 0x8008949c)],
                         ops('rlwinm 6 0 0 25 25 1\nrlwinm 6 0 0 26 26 1\nrlwinm 6 0 0 27 27 1'))
        self.assertEqual([rows[pc] for pc in range(0x80089540, 0x80089554, 4)],
                         ops('addi 4 0 0\naddi 0 0 -1\nstw 4 3 0x100\nstb 0 3 0x85\nblr 20 0 0 0'))
        self.assertFalse(any(r['mnemonic'] in ('bl', 'bctrl') for r in rows.values()))
        self.assertFalse(any(r.get('rD') == 3 or r['mnemonic'] == 'or' and r['rA'] == 3
                             for r in rows.values()))

    def test_unref_clear_then_callback_and_indirect_argument_identity(self):
        wrapper, callback, release = at(0x80006d80), at(0x80006ed8), at(0x80197ad8)
        self.assertEqual([wrapper[pc] for pc in range(0x80006d94, 0x80006db4, 4)], ops('''
lwz 3 3 0xc
cmpli 0 0 3 0
bc 12 2 80006dac 0 0
bl 8024fd74 0 1
addi 0 0 0
stw 0 31 0xc
or 31 3 31 0
bl 80197ad8 0 1
'''))
        self.assertEqual(callback[0x80006eec], ops('lwz 3 3 0xc')[0])
        self.assertEqual(callback[0x80006ef8], ops('bl 8024fd74 0 1')[0])
        self.assertEqual(callback[0x80006f00], ops('stw 0 31 0xc')[0])
        self.assertEqual(callback[0x80006f08], ops('addi 3 0 0')[0])
        self.assertEqual(release[0x80197af0], ops('or 3 29 3 1')[0])
        self.assertEqual(release[0x80197b04], ops('mulli 0 5 28')[0])
        self.assertEqual(release[0x80197b10], ops('lwz 12 31 0x18')[0])
        self.assertEqual(release[0x80197b1c], ops('mtctr 12')[0])
        self.assertEqual(release[0x80197b20], ops('bctrl 20 0 0 1')[0])
        # Incoming descriptor remains r3 at bctrl, not descriptor type or JObj.
        self.assertFalse(any(r.get('rD') == 3 or r['mnemonic'] == 'or' and r['rA'] == 3
                             for pc, r in release.items() if 0x80197af0 <= pc < 0x80197b20))
        self.assertEqual([release[pc] for pc in range(0x80197b4c, 0x80197b78, 4)], ops('''
lwz 4 31 0xc
addi 0 0 0
or 30 3 30 0
stw 4 29 0
stw 29 31 0xc
stb 0 29 9
bl 80197bec 0 1
or 3 4 3 0
or 30 3 30 0
addi 4 4 1
bl 80197bd8 0 1
'''))

    def test_pool_append_unsigned16_then_active_clear_preserves_child_return(self):
        rows = at(0x80089814)
        self.assertEqual(rows[0x80089834], ops('stwx 3 4 0')[0])
        self.assertEqual(rows[0x8008984c], ops('stwx 3 4 0')[0])
        self.assertEqual(rows[0x80089854], ops('stw 3 5 4')[0])
        self.assertEqual(rows[0x80089864], ops('stwx 3 4 0')[0])
        self.assertEqual([rows[pc] for pc in range(0x80089880, 0x80089898, 4)],
                         ops('lhzx 4 5 6\naddi 4 4 1\nsthx 4 5 6\nstb 0 3 0\nstw 0 3 4\nblr 20 0 0 0'))
        for entry in (0x8007e678, 0x80089814):
            self.assertFalse(any(r.get('rD') == 3 or r['mnemonic'] == 'or' and r['rA'] == 3
                                 for r in EXPECTED[entry]))
        cleanup = at(0x80088e50)
        self.assertFalse(any(r.get('rD') == 3 or r['mnemonic'] == 'or' and r['rA'] == 3
                             for pc, r in cleanup.items() if pc > 0x80088f78))
        import read_archived_projectile_callback_evidence as upstream
        import read_archived_object_allocator_evidence as allocator
        available = dict((pc, (width, digest)) for pc, width, digest in upstream.RANGES + allocator.RANGES)
        self.assertEqual([r['address'] for r in a.REUSED_EVIDENCE], ['8008aff0', '80197bec', '80197bd8'])
        for row in a.REUSED_EVIDENCE:
            self.assertEqual((row['width'], row['sha256']), available[int(row['address'], 16)])
            self.assertIs(row['read_here'], False)
        # Independently restate the already authenticated helper operands. No
        # new archive read: the hashes join these semantics to reused evidence.
        reused_counts = {
            0x80197bec: ops('mulli 3 3 28\nlwz 4 13 -21024\naddi 0 3 18\nlhax 3 4 0\nblr 20 0 0 0'),
            0x80197bd8: ops('mulli 3 3 28\nlwz 5 13 -21024\naddi 0 3 18\nsthx 4 5 0\nblr 20 0 0 0'),
        }
        for entry, rows in reused_counts.items():
            body = b''.join(struct.pack('>I', encode(row, entry + i * 4)) for i, row in enumerate(rows))
            self.assertEqual((len(body), hashlib.sha256(body).hexdigest()), available[entry])
        self.assertEqual(reused_counts[0x80197bd8][0], ops('mulli 3 3 28')[0])
        self.assertFalse(any(row.get('rD') == 3 or row.get('rA') == 3 and row['mnemonic'] == 'or'
                             for row in reused_counts[0x80197bd8][1:]))

    def test_addresses_widths_exact_typed_maps_and_neighbors_refuse_before_reads(self):
        for fn, mapping, pc, width in SELECTIONS:
            for bad in (pc - 1, pc + 1, pc - 4, pc + 4, float(pc), True, -1, 1 << 32):
                db = FakeDB(PAYLOADS[pc])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, bad, width)
                self.assertFalse(db.calls)
            for bad in (0, width - 4, width + 4, -width, True, float(width)):
                db = FakeDB(PAYLOADS[pc])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, pc, bad)
                self.assertFalse(db.calls)
            for index, value in enumerate(mapping):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    changed = list(mapping); changed[index] = replacement; db = FakeDB(PAYLOADS[pc])
                    with self.assertRaises(a.c.FormatError): fn(db, tuple(changed), pc, width)
                    self.assertFalse(db.calls)
            db = FakeDB(PAYLOADS[pc])
            with self.assertRaises(a.c.FormatError): fn(db, list(mapping), pc, width)
            self.assertFalse(db.calls)
        for pc in (0x8007e63c, 0x8007e698, 0x8008aff0, 0x80197bec, 0x80197bd8, 0x8024fd74, 0x80006f1c):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)
        for pc in (0x802d6f98, 0x802d6f9c, 0x802d6fa0, 0x802d6fa8, 0x8036f658, 0x8036f660):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.cell_evidence(db, DATA3_MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_truncation_duplicate_allowlists_and_wrong_cell_targets_fail(self):
        for fn, mapping, pc, width in SELECTIONS:
            for raw in (PAYLOADS[pc][:-1], PAYLOADS[pc] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'): fn(FakeDB(raw), mapping, pc, width)
            name = 'RANGES' if fn == a.range_evidence else 'CELLS'
            with patch.object(a, name, getattr(a, name) * 2):
                db = FakeDB(PAYLOADS[pc])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, pc, width)
                self.assertFalse(db.calls)
        for index, (label, pc, width, target, digest) in enumerate(CELLS):
            changed = list(CELLS); changed[index] = (label, pc, width, target + 4, digest)
            with patch.object(a, 'CELLS', tuple(changed)):
                with self.assertRaisesRegex(a.c.FormatError, 'cell target mismatch'):
                    a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc, width)

    def test_decoder_bounds_reserved_bits_and_all_control_metadata_mutations(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4d820820, 0x48000003, 0x94000000, 0x7c0802a7):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x8007e678)
        original = a.decode_selected
        mutations = 0
        for pc, width, _ in RANGES:
            with patch.object(a, 'decode_selected', return_value=None):
                with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                    a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
            for site, expected in at(pc).items():
                if expected['mnemonic'] not in ('bc', 'b', 'bl', 'blr', 'bclr', 'bctrl'): continue
                for field in expected:
                    value = expected[field]
                    replacement = 'addi' if field == 'mnemonic' else '80000000' if field == 'target' else value ^ 1
                    def changed(word, address):
                        row = original(word, address)
                        return dict(row, **{field: replacement}) if address == site else row
                    with patch.object(a, 'decode_selected', changed):
                        with self.assertRaisesRegex(a.c.FormatError, 'complete control-flow mismatch'):
                            a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
                    mutations += 1
        self.assertGreater(mutations, 250)

    def test_authentication_precedes_parser_and_all_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad'); db.assert_not_called()
            code.assert_not_called(); cell.assert_not_called()
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(bytes(32), digest)
                db.assert_not_called(); code.assert_not_called(); cell.assert_not_called()
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for key, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[key] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
                db.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'): a.inspect(data, digest)
                db.return_value.rows.assert_not_called(); code.assert_not_called(); cell.assert_not_called()

    def test_mapping_refusals_precede_all_selections(self):
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

    def test_cell_results_never_select_reads_and_both_identity_mismatches_fail(self):
        for index, error in ((0, 'independently selected candidate'), (1, 'independently selected body')):
            cells = [dict(target='8007e678'), dict(target='80006ed8')]
            cells[index] = dict(target='8024fd74')
            with patch.object(a.c, 'inspect', return_value={'image_offset': '80000000'}), \
                 patch.object(a.c, 'GBF') as db, patch.object(a.command, 'mappings'), \
                 patch.object(a.normal, 'mapping_evidence', side_effect=[(TEXT_MAPPING, {}), (DATA3_MAPPING, {})]), \
                 patch.object(a, 'cell_evidence', side_effect=cells) as cell, \
                 patch.object(a, 'range_evidence', side_effect=[dict(address=f'{pc:08x}') for pc, _, _ in RANGES]) as code:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                with self.assertRaisesRegex(a.c.FormatError, error): a.inspect(b'x', 'x')
                self.assertEqual([call.args[2:] for call in code.call_args_list], [(pc, width) for pc, width, _ in RANGES])
                self.assertEqual([call.args[2:] for call in cell.call_args_list], [(pc, width) for _, pc, width, _, _ in CELLS])

    def test_independent_source_extents_and_no_arbitrary_cli(self):
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        source = (root / 'research/decomp/ghidra-export/chunk_0011.c').read_text()
        start = index.index('8007e678\tFUN_8007e678\tchunk_0011.c')
        self.assertEqual(index[start + 1], '8007e698\tFUN_8007e698\tchunk_0011.c')
        candidate, suffix = source.split('// ==== 8007e678 ', 1)[1].split('// ==== ', 1)
        self.assertTrue(suffix.startswith('8007e698 ')); self.assertIn('zz_0088e50_(', candidate)
        self.assertNotRegex(symbols, r'(?m)^8007e678 ')
        callback_source = (root / 'research/decomp/ghidra-export/chunk_0000.c').read_text()
        callback, suffix = callback_source.split('// ==== 80006ed8 ', 1)[1].split('// ==== ', 1)
        self.assertTrue(suffix.startswith('80006f1c ')); self.assertIn('return 0;', callback)
        start = index.index('80006ed8\tzz_0006ed8_\tchunk_0000.c')
        self.assertEqual(index[start + 1], '80006f1c\tzz_0006f1c_\tchunk_0000.c')
        for pc, width, _ in RANGES[1:]:
            self.assertRegex(symbols, rf'(?m)^{pc:08x} {width:08x} {pc:08x} 0 ')
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/cleanup.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
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

    def test_both_snapshots_all_operands_cells_complete_coverage_and_ceiling(self):
        for key in ('mappings', 'ranges', 'cells', 'function_coverage', 'selection_basis', 'reused_evidence'):
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
            self.assertEqual([row['target'] for row in report['cells']], ['8007e678', '80006ed8'])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_state']), (9, 1100, 3))
            self.assertTrue(basis['target_equals_independent_candidate'])
            self.assertTrue(basis['release_callback_body_read']); self.assertTrue(basis['callback_extent_independently_selected'])
            for key in ('pointer_following', 'unref_body_read', 'reused_helpers_read', 'other_state_cells_read'):
                self.assertFalse(basis[key])
            self.assertIn('not original-DOL identity', report['caveat']); self.assertIn('unselected JObjUnref', report['caveat'])
            self.assertEqual(sum(row['represented_instructions'] for row in report['function_coverage']), 273)
            for row in report['function_coverage']:
                self.assertEqual(row['unrepresented_instructions'], 0); self.assertEqual(row['unrepresented_ranges'], [])
            self.assertIsNone(report['function_coverage'][0]['map_size'])

    def test_exact_nine_reads_after_full_unchanged_authentication(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(auth); self.assertTrue(all(row[0] == 263 for row in auth))

    def test_all_physical_spans_including_split_instruction_and_no_raw_output(self):
        expected = {
            0x802d6fa4: [(199, 207, 115012, 366, 4, 3408244)],
            0x8036f65c: [(199, 245, 739324, 2314, 4, 4032784)],
            0x8007e678: [(21, 52, 495768, 4428, 32, 872786)],
            0x80088e50: [(21, 54, 538736, 14640, 328, 915766)],
            0x80089444: [(21, 54, 540260, 16164, 214, 917290), (21, 55, 540474, 0, 58, 917510)],
            0x80006d80: [(21, 22, 6048, 6048, 72, 382886)],
            0x80197ad8: [(21, 122, 1647864, 10064, 188, 2025302)],
            0x80089814: [(21, 55, 541236, 762, 132, 918272)],
            0x80006ed8: [(21, 22, 6392, 6392, 68, 383230)],
        }
        for report in self.reports:
            for row in report['cells'] + report['ranges']:
                self.assertEqual(row['spans'], [dict(root_buffer=root, data_buffer=data, chain_offset=offset,
                    data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)
                    for root, data, offset, data_offset, length, physical in expected[int(row['address'], 16)]])
                self.assertEqual(row['end_exclusive'], f'{int(row["address"], 16) + row["width"]:08x}')
            for row in report['ranges']:
                self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
                self.assertFalse(any('word' in item for item in row['instructions']))
            for row in report['cells']:
                self.assertEqual(set(row), {'label', 'address', 'end_exclusive', 'width', 'target', 'sha256', 'spans'})

    def test_real_snapshot_and_every_selected_payload_tamper_fail_closed(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes(); digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            code.assert_not_called(); cell.assert_not_called()
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
