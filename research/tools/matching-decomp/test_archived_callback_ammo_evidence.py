#!/usr/bin/env python3
"""Independent 112-instruction inverse fixture, 464-byte mutation and scope guards.

Synthetic controls do not need archives. Optional local controls authenticate
both existing snapshots and exactly six new reads. The operand schedules below
are frozen, manually transcribed semantic expectations, never generated from
the tested decoder, its report or an archive during the tests.
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

import read_archived_callback_ammo_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA5_MAPPING = (0x80436a20, 0x8043d500, 7, 'MAIN_.data5', 7, 27360, 263)
RANGES = (
    (0x800715f8, 224, '7735b73fbd6b3149290d56bad8eed6be6202d6afbcb315708646b0717bbda4a8'),
    (0x8006dbe0, 224, '0b2e322f452d317b5f515e0ebd95f821a10cdbee5db9cdbd07678c8d251eed31'),
)
CONSTANTS = (
    (0x80437748, '41200000', 'hSpeed44', 'b9e69238a01189ddad0c70c62fc04d362b55ee6eefaa558dd13fc45ac1d665be'),
    (0x804376e4, '00000000', 'hDecel4c', 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'),
    (0x80437768, '41700000', 'yVel48', '6684130864793326a78b61833fd87b8235a4a62157e3d50ac29ed8a2abaf83c1'),
    (0x804376e0, 'bf800000', 'gravityCoeff50', 'b705efea49cb3296c6f0417c21fe14f10adb140333fd79d7cfc3318904f887ea'),
)
FIELDS = {'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'sth': 'rS rA displacement',
          'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement', 'lha': 'rD rA displacement',
          'lfs': 'fD rA displacement', 'lfd': 'fD rA displacement', 'stfs': 'fS rA displacement',
          'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'xoris': 'rS rA immediate',
          'or': 'rS rA rB Rc', 'mflr': 'rD', 'mtlr': 'rS', 'bl': 'target AA LK', 'b': 'target AA LK',
          'bc': 'BO BI LK target AA', 'extsb': 'rS rA Rc', 'extsh': 'rS rA Rc',
          'cmpi': 'BF L rA immediate', 'cmp': 'BF L rA rB', 'blr': 'BO BI BH LK',
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


EXPECTED = {0x800715f8: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 0x1d0f
extsb 0 0 1
bc 12 2 0 80071648 0
lha 3 31 0x72
lfs 3 2 -29400
addis 3 3 1
lfs 2 2 -29500
addi 0 3 -32768
lfs 1 2 -29368
sth 0 31 0x5ae
lfs 0 2 -29504
stfs 3 31 0x44
stfs 2 31 0x4c
stfs 1 31 0x48
stfs 0 31 0x50
or 31 3 31 0
addi 4 0 2
addi 5 0 1
addi 6 0 1
bl 8006dbe0 0 1
cmpi 0 0 3 0
bc 12 2 0 800716c4 0
lha 3 31 0x3e8
extsh 3 0 1
bc 4 2 0 80071680 0
or 31 3 31 0
addi 4 0 0
bl 8007db5c 0 1
b 800716c4 0 0
cmpi 0 0 3 3
bc 4 2 0 800716b0 0
or 31 3 31 0
addi 4 0 1
bl 8007db5c 0 1
lbz 0 31 0x7c8
extsb 0 0 1
bc 12 2 0 800716c4 0
or 31 3 31 0
addi 4 0 2
bl 8007db5c 0 1
b 800716c4 0 0
cmpi 0 0 3 10
bc 4 2 0 800716c4 0
or 31 3 31 0
addi 4 0 3
bl 8007db5c 0 1
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''), 0x8006dbe0: ops('''
rlwinm 4 0 3 0 28 0
stwu 1 1 -16
add 4 3 0 0 0
lha 0 4 0x774
cmp 0 0 0 5
bc 4 0 0 8006dc00 0
addi 3 0 0
b 8006dcb8 0 0
cmpi 0 0 6 0
bc 4 2 0 8006dc10 0
addi 3 0 1
b 8006dcb8 0 0
sth 0 4 0x776
lha 0 4 0x774
subf 0 5 0 0 0
sth 0 4 0x774
lha 0 4 0x790
cmpi 0 0 0 1
bc 12 2 0 8006dc7c 0
bc 4 0 0 8006dc3c 0
cmpi 0 0 0 0
bc 4 0 0 8006dc48 0
b 8006dcb4 0 0
cmpi 0 0 0 4
bc 4 0 0 8006dcb4 0
b 8006dcac 0 0
lha 0 4 0x774
cmpi 0 0 0 0
bc 4 2 0 8006dcb4 0
lha 3 4 0x792
addis 0 0 0x4330
stw 0 1 8
xoris 3 0 0x8000
lfd 1 2 -29568
stw 0 1 12
lfd 0 1 8
fsubs 0 0 1
stfs 0 4 0x778
b 8006dcb4 0 0
lha 3 4 0x792
addis 0 0 0x4330
stw 0 1 8
xoris 3 0 0x8000
lfd 1 2 -29568
stw 0 1 12
lfs 2 4 0x778
lfd 0 1 8
fsubs 0 0 1
fadds 0 2 0
stfs 0 4 0x778
b 8006dcb4 0 0
lfs 0 2 -29640
stfs 0 4 0x778
addi 3 0 1
addi 1 1 16
blr 20 0 0 0
''')}


def encode(row, pc):
    """PPC inverse authored independently; does not call any reader/decoder."""
    n = row['mnemonic']
    if n in ('stwu', 'stw', 'sth', 'lwz', 'lbz', 'lha', 'lfs', 'lfd', 'stfs', 'addi', 'addis', 'xoris'):
        opcode, reg, imm = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
            'sth': (44, 'rS', 'displacement'), 'lwz': (32, 'rD', 'displacement'),
            'lbz': (34, 'rD', 'displacement'), 'lha': (42, 'rD', 'displacement'),
            'lfs': (48, 'fD', 'displacement'), 'lfd': (50, 'fD', 'displacement'),
            'stfs': (52, 'fS', 'displacement'), 'addi': (14, 'rD', 'immediate'),
            'addis': (15, 'rD', 'immediate'), 'xoris': (27, 'rS', 'immediate')}[n]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if n in ('mflr', 'mtlr'):
        xo, reg = (339, 'rD') if n == 'mflr' else (467, 'rS')
        return 31 << 26 | row[reg] << 21 | 8 << 16 | xo << 1
    if n in ('or', 'extsb', 'extsh'):
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | row.get('rB', 0) << 11 | {'or': 444, 'extsb': 954, 'extsh': 922}[n] << 1 | row['Rc']
    if n in ('add', 'subf'):
        return 31 << 26 | row['rD'] << 21 | row['rA'] << 16 | row['rB'] << 11 | row['OE'] << 10 | (266 if n == 'add' else 40) << 1 | row['Rc']
    if n in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if n != 'bc':
            return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
        return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc | row['AA'] << 1 | row['LK']
    if n == 'blr':
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    if n == 'cmpi':
        return 11 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
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
PAYLOADS.update({0x80437748: struct.pack('>f', 10.0), 0x804376e4: struct.pack('>f', 0.0),
                 0x80437768: struct.pack('>f', 15.0), 0x804376e0: struct.pack('>f', -1.0)})
SELECTIONS = ((a.range_evidence, TEXT_MAPPING, 0x800715f8, (224,)),
              (a.range_evidence, TEXT_MAPPING, 0x8006dbe0, (224,)),
              (a.constant_evidence, DATA5_MAPPING, 0x80437748, ()),
              (a.constant_evidence, DATA5_MAPPING, 0x804376e4, ()),
              (a.constant_evidence, DATA5_MAPPING, 0x80437768, ()),
              (a.constant_evidence, DATA5_MAPPING, 0x804376e0, ()))
EXPECTED_READS = [(21, 442392, 224, 2796416), (21, 427520, 224, 2796416),
                  (263, 3368, 4, 27360), (263, 3268, 4, 27360),
                  (263, 3400, 4, 27360), (263, 3264, 4, 27360)]


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_exact_inventory_and_mappings(self):
        self.assertEqual(a.RANGES, RANGES)
        self.assertEqual(a.CONSTANTS, CONSTANTS)
        for name in ('TEXT_MAPPING', 'DATA5_MAPPING'):
            self.assertEqual(getattr(a, name), globals()[name])
        self.assertEqual(sum(len(raw) for raw in PAYLOADS.values()), 464)
        self.assertTrue(set(PAYLOADS).isdisjoint({0x800716d8, 0x8006dcc0, 0x8007db5c,
            0x80437658, 0x804376a0, 0x800ff418, 0x8031f004, 0x8043386c, 0x8020bb14}))

    def test_all_112_operands_independent_inverse_and_hashes(self):
        controls = 0
        for pc, width, digest in RANGES:
            expected, body = EXPECTED[pc], BODIES[pc]
            self.assertEqual(len(expected), 56)
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
                    try:
                        decoded = a.decode_selected(changed, address)
                    except a.c.FormatError:
                        continue
                    if decoded is not None:
                        self.assertNotEqual(decoded, row, (hex(address), bit))
                        self.assertEqual(encode(decoded, address), changed, (hex(address), bit))
        self.assertEqual(controls, 3584)

    def test_callback_signed_state_write_order_and_return_before_borg(self):
        at = {0x800715f8 + i * 4: row for i, row in enumerate(EXPECTED[0x800715f8])}
        self.assertEqual(at[0x8007160c], dict(mnemonic='lbz', rD=0, rA=3, displacement=0x1d0f))
        self.assertEqual(at[0x80071610], dict(mnemonic='extsb', rS=0, rA=0, Rc=1))
        self.assertEqual(at[0x80071614], dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80071648', AA=0))
        self.assertEqual(at[0x80071618], dict(mnemonic='lha', rD=3, rA=31, displacement=0x72))
        self.assertEqual(at[0x80071620], dict(mnemonic='addis', rD=3, rA=3, immediate=1))
        self.assertEqual(at[0x80071628], dict(mnemonic='addi', rD=0, rA=3, immediate=-32768))
        self.assertEqual([(pc, row['mnemonic'], row.get('displacement')) for pc, row in at.items()
                          if row['mnemonic'] in ('sth', 'stfs')],
                         [(0x80071630, 'sth', 0x5ae), (0x80071638, 'stfs', 0x44),
                          (0x8007163c, 'stfs', 0x4c), (0x80071640, 'stfs', 0x48), (0x80071644, 'stfs', 0x50)])
        self.assertEqual([0x8043ea20 + at[pc]['displacement'] for pc in
                          (0x8007161c, 0x80071624, 0x8007162c, 0x80071634)],
                         [0x80437748, 0x804376e4, 0x80437768, 0x804376e0])
        self.assertEqual([(at[pc]['rD'], at[pc]['rA'], at[pc]['immediate']) for pc in
                          (0x8007164c, 0x80071650, 0x80071654)], [(4, 0, 2), (5, 0, 1), (6, 0, 1)])
        self.assertEqual(at[0x80071658], dict(mnemonic='bl', target='8006dbe0', AA=0, LK=1))
        self.assertEqual(at[0x8007165c], dict(mnemonic='cmpi', BF=0, L=0, rA=3, immediate=0))
        self.assertEqual(at[0x80071660], dict(mnemonic='bc', BO=12, BI=2, LK=0, target='800716c4', AA=0))
        self.assertEqual(at[0x80071664], dict(mnemonic='lha', rD=3, rA=31, displacement=0x3e8))
        self.assertEqual(at[0x80071668], dict(mnemonic='extsh', rS=3, rA=0, Rc=1))
        self.assertEqual([(pc, row['target']) for pc, row in at.items() if row['mnemonic'] == 'bl'],
                         [(0x80071658, '8006dbe0'), (0x80071678, '8007db5c'),
                          (0x80071690, '8007db5c'), (0x800716a8, '8007db5c'), (0x800716c0, '8007db5c')])
        self.assertEqual([at[pc]['immediate'] for pc in (0x80071674, 0x8007168c, 0x800716a4, 0x800716bc)], [0, 1, 2, 3])
        self.assertEqual(at[0x80071694], dict(mnemonic='lbz', rD=0, rA=31, displacement=0x7c8))
        self.assertEqual(at[0x80071698], dict(mnemonic='extsb', rS=0, rA=0, Rc=1))

    def test_ammo_signed_count_mirror_reload_debit_then_mode(self):
        at = {0x8006dbe0 + i * 4: row for i, row in enumerate(EXPECTED[0x8006dbe0])}
        self.assertEqual(at[0x8006dbe0], dict(mnemonic='rlwinm', rS=4, rA=0, SH=3, MB=0, ME=28, Rc=0))
        self.assertEqual(at[0x8006dbe8], dict(mnemonic='add', rD=4, rA=3, rB=0, OE=0, Rc=0))
        self.assertEqual(at[0x8006dbec], dict(mnemonic='lha', rD=0, rA=4, displacement=0x774))
        self.assertEqual(at[0x8006dbf0], dict(mnemonic='cmp', BF=0, L=0, rA=0, rB=5))
        self.assertEqual(at[0x8006dbf4], dict(mnemonic='bc', BO=4, BI=0, LK=0, target='8006dc00', AA=0))
        self.assertEqual(at[0x8006dc00], dict(mnemonic='cmpi', BF=0, L=0, rA=6, immediate=0))
        self.assertEqual(at[0x8006dc10], dict(mnemonic='sth', rS=0, rA=4, displacement=0x776))
        self.assertEqual(at[0x8006dc14], dict(mnemonic='lha', rD=0, rA=4, displacement=0x774))
        self.assertEqual(at[0x8006dc18], dict(mnemonic='subf', rD=0, rA=5, rB=0, OE=0, Rc=0))
        self.assertEqual(at[0x8006dc1c], dict(mnemonic='sth', rS=0, rA=4, displacement=0x774))
        self.assertEqual(at[0x8006dc20], dict(mnemonic='lha', rD=0, rA=4, displacement=0x790))
        self.assertEqual([at[pc]['immediate'] for pc in (0x8006dc24, 0x8006dc30, 0x8006dc3c)], [1, 0, 4])
        self.assertEqual(at[0x8006dc48], dict(mnemonic='lha', rD=0, rA=4, displacement=0x774))
        self.assertEqual(at[0x8006dc4c], dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=0))
        self.assertEqual(at[0x8006dc50], dict(mnemonic='bc', BO=4, BI=2, LK=0, target='8006dcb4', AA=0))
        self.assertEqual([at[pc]['immediate'] for pc in (0x8006dbf8, 0x8006dc08, 0x8006dcb4)], [0, 1, 1])
        self.assertFalse(any(row['mnemonic'] == 'bl' for row in at.values()))
        self.assertEqual({row['displacement'] + 2 * 8 for row in at.values()
                          if row.get('rA') == 4 and 'displacement' in row}, {0x784, 0x786, 0x788, 0x7a0, 0x7a2})

    def test_timer_signed_conversion_load_order_and_single_rounding(self):
        at = {0x8006dbe0 + i * 4: row for i, row in enumerate(EXPECTED[0x8006dbe0])}
        for pc in (0x8006dc54, 0x8006dc7c):
            self.assertEqual(at[pc], dict(mnemonic='lha', rD=3, rA=4, displacement=0x792))
            self.assertEqual(at[pc + 4], dict(mnemonic='addis', rD=0, rA=0, immediate=0x4330))
            self.assertEqual(at[pc + 12], dict(mnemonic='xoris', rS=3, rA=0, immediate=0x8000))
            self.assertEqual(at[pc + 16], dict(mnemonic='lfd', fD=1, rA=2, displacement=-29568))
        for pc in (0x8006dc70, 0x8006dc9c):
            self.assertEqual(at[pc], dict(mnemonic='fsubs', fD=0, fA=0, fB=1))
        self.assertEqual(at[0x8006dc94], dict(mnemonic='lfs', fD=2, rA=4, displacement=0x778))
        self.assertEqual(at[0x8006dc98], dict(mnemonic='lfd', fD=0, rA=1, displacement=8))
        self.assertEqual(at[0x8006dca0], dict(mnemonic='fadds', fD=0, fA=2, fB=0))
        self.assertEqual([at[pc] for pc in (0x8006dc74, 0x8006dca4, 0x8006dcb0)],
                         [dict(mnemonic='stfs', fS=0, rA=4, displacement=0x778)] * 3)
        self.assertEqual(at[0x8006dcac], dict(mnemonic='lfs', fD=0, rA=2, displacement=-29640))
        self.assertEqual(0x8043ea20 - 29568, 0x804376a0)
        self.assertEqual(0x8043ea20 - 29640, 0x80437658)

    def test_constants_hashes_and_six_exact_reads(self):
        hashes = [r[2] for r in RANGES] + [r[3] for r in CONSTANTS]
        for (fn, mapping, address, extra), call, digest in zip(SELECTIONS, EXPECTED_READS, hashes):
            db = FakeDB(PAYLOADS[address])
            result = fn(db, mapping, address, *extra)
            self.assertEqual(db.calls, [call])
            self.assertEqual(result['sha256'], digest)
            self.assertEqual(result['width'], len(PAYLOADS[address]))
        self.assertEqual([a.constant_evidence(FakeDB(PAYLOADS[pc]), DATA5_MAPPING, pc)['value']
                          for pc, _, _, _ in CONSTANTS], [10.0, 0.0, 15.0, -1.0])

    def test_every_selected_byte_and_bit_mutation_refuses(self):
        mutations = 0
        for fn, mapping, address, extra in SELECTIONS:
            raw = PAYLOADS[address]
            for i in range(len(raw)):
                for bit in range(8):
                    changed = raw[:i] + bytes([raw[i] ^ 1 << bit]) + raw[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        fn(FakeDB(changed), mapping, address, *extra)
                    mutations += 1
        self.assertEqual(mutations, 3712)

    def test_allowlists_mapping_types_and_bounds_precede_reads(self):
        for fn, mapping, address, extra in SELECTIONS:
            # +/-4 may itself be another selected constant; exclude only literal selections.
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
        for pc in BODIES:
            for width in (0, 220, 225, 228, -224, True, 224.0):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, width)
                self.assertFalse(db.calls)
        for fn, mapping, pc, extra in ((a.range_evidence, TEXT_MAPPING, 0x8007db5c, (400,)),
                (a.constant_evidence, DATA5_MAPPING, 0x80437658, ()),
                (a.constant_evidence, DATA5_MAPPING, 0x804376a0, ())):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): fn(db, mapping, pc, *extra)
            self.assertFalse(db.calls)

    def test_truncation_duplicate_allowlists_and_constant_meanings_refuse(self):
        for fn, mapping, address, extra in SELECTIONS:
            for raw in (PAYLOADS[address][:-1], PAYLOADS[address] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'): fn(FakeDB(raw), mapping, address, *extra)
            name = 'RANGES' if extra else 'CONSTANTS'
            with patch.object(a, name, getattr(a, name) * 2):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, address, *extra)
                self.assertFalse(db.calls)
        for pc, bits, label, digest in CONSTANTS:
            with patch.object(a, 'CONSTANTS', ((pc, 'ffffffff', label, digest),)):
                with self.assertRaisesRegex(a.c.FormatError, 'constant bits mismatch'):
                    a.constant_evidence(FakeDB(PAYLOADS[pc]), DATA5_MAPPING, pc)

    def test_decoder_bounds_reserved_bits_and_complete_body_fail_closed(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x4c820020, 0x48000002,
                     0x40800001, 0x2c2c0000, 0x94000000, 0x7c0802a7,
                     0x7c000f75, 0xec000029, 0xec000068, 0x7c000001):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x800715f8)
        self.assertIsNone(a.decode_selected(0, 0x800715f8))
        original = a.decode_selected
        for pc, body in BODIES.items():
            for row in (None, dict(mnemonic='lbz', rD=0, rA=0, displacement=0)):
                with patch.object(a, 'decode_selected', return_value=row):
                    with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, 224)
            def outside(word, address):
                row = original(word, address)
                return dict(row, target=f'{pc + 224:08x}') if row['mnemonic'] in ('bc', 'b') else row
            with patch.object(a, 'decode_selected', outside):
                with self.assertRaisesRegex(a.c.FormatError, 'branch outside'):
                    a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, 224)
        def wrong_call(word, address):
            row = original(word, address)
            return dict(row, target='8007db60') if row['mnemonic'] == 'bl' else row
        with patch.object(a, 'decode_selected', wrong_call):
            with self.assertRaisesRegex(a.c.FormatError, 'direct-call mismatch'):
                a.range_evidence(FakeDB(BODIES[0x800715f8]), TEXT_MAPPING, 0x800715f8, 224)

    def test_authentication_precedes_parser_and_all_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, \
             patch.object(a, 'constant_evidence') as constant:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad')
            db.assert_not_called(); code.assert_not_called(); constant.assert_not_called()

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

    def test_mapping_refusals_precede_all_six_selections(self):
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
            bb, ss = copy.deepcopy((blocks, subs)); bb[99] = copy.deepcopy(bb[key])
            cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); ss[99] = copy.deepcopy(ss[key])
            cases.append((bb, ss, '80000000'))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]
                cases.append((bb, ss, '80000000'))
        cases.append((blocks, subs, '80000004'))
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'constant_evidence') as constant:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called(); constant.assert_not_called()

    def test_independent_extent_sources_and_no_address_cli(self):
        root = Path(__file__).resolve().parents[3]
        markers = (root / 'research/decomp/ghidra-export/chunk_0009.c').read_text()
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc, end in (('800715f8', '800716d8'), ('8006dbe0', '8006dcc0')):
            for address in (pc, end):
                self.assertIn(f'// ==== {address} ', markers)
                self.assertIn(f'{address}\tzz_00{address[3:]}_\tchunk_0009.c', index)
            self.assertIn(f'{pc} 000000e0 {pc} 0 zz_00{pc[3:]}_', symbols)
        callback = markers.split('// ==== 800715f8 ')[1].split('// ==== 800716d8 ')[0]
        for pc, _, _, _ in CONSTANTS:
            self.assertIn(f'FLOAT_{pc:08x}', callback)
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/callback-ammo-evidence.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
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
            with patch.object(a.c.GBF, 'chain', traced):
                a.c.inspect(raw, digest)
            cls.auth_reads.append(reads[:])
            reads.clear()
            with patch.object(a.c.GBF, 'chain', traced):
                cls.reports.append(a.inspect(raw, digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_all_operands_and_facts_agree(self):
        for key in ('mappings', 'ranges', 'constants', 'function_coverage', 'reused_evidence', 'recorded_bases'):
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
            self.assertEqual([r['value'] for r in report['constants']], [10.0, 0.0, 15.0, -1.0])

    def test_exact_six_literal_reads_after_unchanged_authenticator(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(all(row[0] == 263 for row in auth))
        report = self.reports[0]
        self.assertTrue(all(not row['read_here'] for row in report['reused_evidence'].values()))
        for row in report['function_coverage']:
            self.assertEqual(row['represented_instructions'], 56)
            self.assertEqual(row['unrepresented_instructions'], 0)
            self.assertEqual(row['map_size'], 224)

    def test_exact_physical_provenance_and_no_raw_output(self):
        expected = {0x800715f8: (21, 49, 442392, 186, 224, 819392),
                    0x8006dbe0: (21, 48, 427520, 1692, 224, 804514),
                    0x80437748: (263, 264, 3368, 3368, 4, 4345134),
                    0x804376e4: (263, 264, 3268, 3268, 4, 4345034),
                    0x80437768: (263, 264, 3400, 3400, 4, 4345166),
                    0x804376e0: (263, 264, 3264, 3264, 4, 4345030)}
        for report in self.reports:
            for row in report['ranges'] + report['constants']:
                root, data, chain_offset, data_offset, length, physical = expected[int(row['address'], 16)]
                self.assertEqual(row['spans'], [dict(root_buffer=root, data_buffer=data, chain_offset=chain_offset,
                    data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)])
                self.assertEqual(row['end_exclusive'], f'{int(row["address"], 16) + row["width"]:08x}')
            for row in report['ranges']:
                self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
                self.assertFalse(any('word' in i for i in row['instructions']))
            for row in report['constants']:
                self.assertEqual(set(row), {'label', 'address', 'end_exclusive', 'width', 'bits', 'value', 'sha256', 'spans'})

    def test_real_archive_tamper_and_selected_payload_tamper_refuse(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as selected:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            selected.assert_not_called()
        original = a.c.GBF.chain
        for target in EXPECTED_READS:
            def altered(db, *args):
                data, spans = original(db, *args)
                return (bytes([data[0] ^ 1]) + data[1:] if args == target else data), spans
            with patch.object(a.c.GBF, 'chain', altered):
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)


if __name__ == '__main__':
    unittest.main()
