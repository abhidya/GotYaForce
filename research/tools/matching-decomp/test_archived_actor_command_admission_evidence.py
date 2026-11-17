#!/usr/bin/env python3
"""All 475 new operands, zero-path reuse and fail-closed reader controls."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import re
import unittest
from unittest.mock import patch

import read_archived_actor_command_admission_evidence as a
import read_archived_actor_input_testers_evidence as testers
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def ops(text):
    """Explicit operand witnesses, independent of the reader decoder at runtime."""
    fields = {
        'stwu': 'rS rA displacement', 'stw': 'rS rA displacement',
        'stb': 'rS rA displacement', 'lwz': 'rD rA displacement',
        'lbz': 'rD rA displacement', 'lha': 'rD rA displacement',
        'sth': 'rS rA displacement', 'lmw': 'rD rA displacement', 'stmw': 'rS rA displacement',
        'psq_l': 'fD rA displacement W I',
        'lfs': 'fD rA displacement', 'lfd': 'fD rA displacement',
        'stfs': 'fS rA displacement', 'stfd': 'fS rA displacement', 'addi': 'rD rA immediate',
        'addis': 'rD rA immediate', 'mulli': 'rD rA immediate',
        'mflr': 'rD', 'mtlr': 'rS', 'rlwinm': 'rS rA SH MB ME Rc',
        'extsb': 'rS rA Rc', 'extsh': 'rS rA Rc',
        'or': 'rS rA rB Rc', 'andc': 'rS rA rB Rc', 'add': 'rD rA rB Rc',
        'lwzx': 'rD rA rB', 'lbzx': 'rD rA rB',
        'cmpi': 'BF L rA immediate', 'cmpli': 'BF L rA immediate',
        'cmp': 'BF L rA rB', 'fcmpo': 'crD fA fB',
        'frsqrte': 'fD fB', 'frsp': 'fD fB', 'fctiwz': 'fD fB',
        'fmul': 'fD fA fC', 'fmuls': 'fD fA fC', 'fnmsub': 'fD fA fC fB',
        'fsubs': 'fD fA fB', 'fadds': 'fD fA fB',
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


EXPECTED = {
    0x80069ea4: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 0x595
extsb 0 0 1
bc 4 2 80069edc
lfs 1 31 0x694
lfs 0 2 -29684
fcmpo 0 1 0
bc 4 1 80069edc
addi 3 0 0
b 80069fcc
lwz 3 31 0x5e0
rlwinm 3 0 0 23 23 1
bc 12 2 80069ef4
addi 0 0 5
stb 0 31 0x586
b 80069f84
rlwinm 3 0 0 24 24 1
bc 12 2 80069f08
addi 0 0 4
stb 0 31 0x586
b 80069f84
rlwinm 3 0 0 26 26 1
bc 12 2 80069f48
lbz 0 31 0x7cc
extsb 0 0 1
bc 12 2 80069f28
addi 0 0 2
stb 0 31 0x586
b 80069f84
rlwinm 3 0 0 25 25 1
bc 12 2 80069f3c
addi 0 0 3
stb 0 31 0x586
b 80069f84
addi 0 0 0
stb 0 31 0x586
b 80069f84
rlwinm 3 0 0 25 25 1
bc 4 2 80069f5c
lbz 0 31 0x5e4
cmpi 0 0 0 4
bc 4 2 80069f68
addi 0 0 3
stb 0 31 0x586
b 80069f84
rlwinm 3 0 0 27 27 1
bc 12 2 80069f7c
addi 0 0 1
stb 0 31 0x586
b 80069f84
addi 0 0 0
stb 0 31 0x586
or 31 3 31 0
bl 8006c674
stb 3 31 0x587
or 31 3 31 0
lbz 5 31 0x585
lbz 4 31 0x586
lbz 0 31 0x587
extsb 5 5 0
extsb 4 4 0
lwz 6 31 0x4ec
rlwinm 5 5 2 0 29 0
extsb 0 0 0
rlwinm 4 4 4 0 27 0
lwzx 5 6 5
rlwinm 0 0 2 0 29 0
add 4 4 0 0
add 4 5 4 0
bl 8006a104
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
    0x8006c674: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
or 3 31 3 0
lwz 0 3 0x508
cmpli 0 0 0 0
bc 4 2 8006c69c
addi 3 0 0
b 8006c714
addi 5 31 0x50c
addi 6 1 8
addi 4 0 0
bl 80066408
lfs 1 1 8
lfs 2 1 16
bl 800452a0
lwz 4 31 0x4ac
extsh 3 3 0
lha 0 4 0x15c
cmp 0 0 3 0
bc 4 1 8006c6d4
addi 3 0 2
b 8006c714
lha 0 4 0x158
cmp 0 0 3 0
bc 4 1 8006c6e8
addi 3 0 1
b 8006c714
lha 0 4 0x15a
cmp 0 0 3 0
bc 12 0 8006c6fc
addi 3 0 0
b 8006c714
lha 0 4 0x15e
cmp 0 0 3 0
bc 12 0 8006c710
addi 3 0 3
b 8006c714
addi 3 0 2
lwz 0 1 36
lwz 31 1 28
mtlr 0
addi 1 1 32
blr
'''),
    0x8006a104: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 4 31 4 0
stw 30 1 8
or 3 30 3 0
lbz 0 4 0
extsb 0 0 0
cmpi 0 0 0 -1
bc 4 2 8006a138
addi 3 0 0
b 8006a3b8
lbz 0 30 0x585
stb 0 30 0x584
bl 8006bda8
lwz 3 30 0x5e0
rlwinm 3 0 0 30 31 0
cmpli 0 0 0 3
bc 4 2 8006a1a4
lbz 0 31 1
cmpli 0 0 0 1
bc 4 2 8006a1a4
rlwinm 3 0 0 25 25 1
bc 12 2 8006a178
or 30 3 30 0
addi 4 0 6
bl 8006a750
b 8006a1a4
or 30 3 30 0
addi 4 0 0
bl 8006a750
lfs 1 2 -29652
or 30 3 30 0
addi 4 0 2
addi 5 0 0
addi 6 0 0
addi 7 0 -1
addi 8 0 -1
bl 8004beb8
lbz 0 31 2
lfs 0 2 -29684
stb 0 30 0x580
lbz 0 31 3
stb 0 30 0x581
lwz 0 30 0x5e0
rlwinm 0 0 0 0 29 0
stw 0 30 0x5e0
lwz 3 30 0x5e0
lbz 0 31 1
or 3 0 0 0
stw 0 30 0x5e0
stfs 0 30 0x694
lbz 0 31 1
cmpli 0 0 0 3
bc 4 2 8006a1ec
addi 0 0 0
stb 0 30 0x709
lbz 5 30 0x584
addis 3 0 -32723
addi 4 3 0x3994
addi 0 0 0
extsb 5 3 0
rlwinm 3 3 1 0 30 0
lbzx 3 4 3
stb 3 30 0x57a
lbz 3 30 0x584
extsb 3 3 0
rlwinm 3 3 1 0 30 0
add 3 4 3 0
lbz 3 3 1
stb 3 30 0x57b
stb 0 30 0x1d9a
lbz 0 30 0x584
extsb 0 0 0
cmpi 0 0 0 3
bc 12 0 8006a25c
rlwinm 0 0 2 0 29 0
lfs 0 2 -29684
add 3 30 0 0
stfs 0 3 0x630
lbz 0 30 0x584
extsb 0 0 0
rlwinm 0 0 2 0 29 0
add 3 30 0 0
stfs 0 3 0x63c
addis 3 0 -32708
lbz 0 30 0x3e5
addi 5 3 0x4e84
lwz 4 5 0
lbz 3 4 0x5e6
andc 3 0 0 0
stb 0 4 0x5e6
lwz 4 5 4
lbz 0 30 0x3e5
lbz 3 4 0x5e6
andc 3 0 0 0
stb 0 4 0x5e6
lwz 4 5 8
lbz 0 30 0x3e5
lbz 3 4 0x5e6
andc 3 0 0 0
stb 0 4 0x5e6
lwz 4 5 12
lbz 0 30 0x3e5
lbz 3 4 0x5e6
andc 3 0 0 0
stb 0 4 0x5e6
lwz 4 5 16
lbz 0 30 0x3e5
lbz 3 4 0x5e6
andc 3 0 0 0
stb 0 4 0x5e6
lwz 4 5 20
lbz 0 30 0x3e5
lbz 3 4 0x5e6
andc 3 0 0 0
stb 0 4 0x5e6
lwz 4 30 0xcc
cmpli 0 0 4 0
bc 12 2 8006a304
lbz 0 4 0x83
extsb 0 0 1
bc 4 2 8006a304
lbz 3 4 0x5e6
lbz 0 30 0x3e5
or 3 0 0 0
stb 0 4 0x5e6
lbz 4 31 0
or 30 3 30 0
extsb 4 4 0
bl 8006a6fc
lbz 0 31 1
cmpli 0 0 0 3
bc 4 2 8006a330
lbz 4 31 0
or 30 3 30 0
extsb 4 4 0
bl 8006a750
lbz 3 30 0x584
addi 31 0 0
extsb 3 0 1
bc 12 2 8006a34c
extsb 3 0 0
cmpi 0 0 0 2
bc 4 2 8006a3a0
extsb 3 4 0
rlwinm 4 0 3 0 28 0
add 3 30 0 0
lha 0 3 0x78e
cmpi 0 0 0 0
bc 12 2 8006a3a0
lha 0 3 0x790
cmpi 0 0 0 3
bc 12 2 8006a3a0
or 30 3 30 0
addi 5 0 1
addi 6 0 0
bl 8006dbe0
cmpi 0 0 3 0
bc 4 2 8006a3a0
lbz 3 30 0x3e4
lbz 4 30 0x584
extsb 3 3 0
extsb 4 4 0
bl 80011cc4
addi 31 0 1
cmpi 0 0 31 0
bc 4 2 8006a3b4
or 30 3 30 0
addi 4 0 2
bl 800ea2c8
addi 3 0 1
lwz 0 1 20
lwz 31 1 12
lwz 30 1 8
mtlr 0
addi 1 1 16
blr
'''),
    0x8006bda8: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
or 3 31 3 0
stw 30 1 24
stw 29 1 20
lwz 0 3 0x504
stw 0 3 0xc8
lwz 0 3 0x508
stw 0 3 0xcc
lbz 0 3 0x7d2
stb 0 3 0xd0
lha 0 3 0x6b8
cmpi 0 0 0 0
bc 12 2 8006bdf8
addi 0 0 0
stw 0 31 0xc8
stw 0 31 0xcc
stb 0 31 0xd0
lwz 0 31 0xcc
cmpli 0 0 0 0
bc 12 2 8006bf14
lwz 4 31 0xc8
addi 30 31 0x20
or 30 3 30 0
addi 29 4 0x64
lwz 5 4 0x64
or 29 4 29 0
lwz 0 29 4
stw 5 31 0x518
stw 0 31 0x51c
lwz 0 29 8
stw 0 31 0x520
bl 8020bc88
lfs 0 2 -29640
fcmpo 0 1 0
bc 4 1 8006be8c
frsqrte 2 1
lfd 4 2 -29632
lfd 3 2 -29624
fmul 0 2 2
fmul 2 4 2
fnmsub 0 1 0 3
fmul 2 2 0
fmul 0 2 2
fmul 2 4 2
fnmsub 0 1 0 3
fmul 2 2 0
fmul 0 2 2
fmul 2 4 2
fnmsub 0 1 0 3
fmul 0 2 0
fmul 0 1 0
frsp 0 0
stfs 0 1 12
lfs 1 1 12
stfs 1 31 0x760
lfs 0 2 -29640
lfs 4 30 0
lfs 3 29 0
lfs 2 30 8
lfs 1 29 8
fsubs 3 4 3
fsubs 1 2 1
fmuls 2 3 3
fmuls 1 1 1
fadds 4 2 1
fcmpo 0 4 0
bc 4 1 8006bf0c
frsqrte 1 4
lfd 3 2 -29632
lfd 2 2 -29624
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
stfs 0 1 8
lfs 4 1 8
stfs 4 31 0x764
b 8006bf64
lfs 0 2 -29608
stfs 0 31 0x764
stfs 0 31 0x760
lha 3 31 0x72
bl 80045204
lfs 0 31 0x764
fmuls 0 0 1
stfs 0 31 0x518
lwz 3 31 0x4b0
lbz 0 3 0x10
extsb 0 0 0
mulli 0 0 0x30
add 3 31 0 0
lfs 0 3 0x8f0
stfs 0 31 0x51c
lha 3 31 0x72
bl 80045238
lfs 0 31 0x764
fmuls 0 0 1
stfs 0 31 0x520
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
mtlr 0
addi 1 1 32
blr
'''),
}

SUPPORT_EXPECTED = {
    0x80045204: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
sth 3 1 8
psq_l 1 1 8 1 5
lfs 0 2 -31144
fmuls 1 0 1
bl 8023c9e8
lwz 0 1 20
frsp 1 1
mtlr 0
addi 1 1 16
blr
'''),
    0x80045238: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
sth 3 1 8
psq_l 1 1 8 1 5
lfs 0 2 -31144
fmuls 1 0 1
bl 8023c480
lwz 0 1 20
frsp 1 1
mtlr 0
addi 1 1 16
blr
'''),
    0x800ea2c8: ops('''
stwu 1 1 -16
mflr 0
addi 5 0 -1
stw 0 1 20
bl 800ea2ec
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x800ea2ec: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stmw 27 1 12
or 3 28 3 0
or 4 29 4 0
or 5 30 5 0
lwz 6 13 -31852
lbz 0 6 0x45
extsb 0 0 0
cmpi 0 0 0 4
bc 4 1 800ea324
addi 3 0 -1
b 800ea42c
'''),
    0x800ea42c: ops('''
lmw 27 1 12
lwz 0 1 36
mtlr 0
addi 1 1 32
blr
'''),
}


class SyntheticTests(unittest.TestCase):
    def test_exact_extents_types_and_unselected_forms(self):
        self.assertEqual([(pc, size) for pc, size, _ in a.RANGES],
                         [(0x80069ea4, 316), (0x8006c674, 180),
                          (0x8006a104, 716), (0x8006bda8, 472)])
        for pc, size, _ in a.RANGES: self.assertEqual(len(EXPECTED[pc]), size // 4)
        self.assertEqual(sum(map(len, EXPECTED.values())), 421)
        self.assertEqual(sum(map(len, SUPPORT_EXPECTED.values())), 54)
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)
        for word in (0, 0x4e800421, d_form(40, 0, 4, 0),
                     d_form(54, 0, 4, 0), (31 << 26) | (24 << 1),
                     (59 << 26) | (29 << 1), (63 << 26) | (15 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))

    def test_float_fields_and_reserved_forms(self):
        for xo, name in ((25, 'fmul'), (30, 'fnmsub')):
            word = (63 << 26) | (5 << 21) | (4 << 16) | (3 << 6) | (xo << 1)
            if xo == 30: word |= 2 << 11
            expected = dict(mnemonic=name, fD=5, fA=4, fC=3)
            if xo == 30: expected['fB'] = 2
            self.assertEqual(a.decode_selected(word, 0), expected)
            with self.assertRaises(a.c.FormatError): a.decode_selected(word | 1, 0)
        for xo, name in ((12, 'frsp'), (26, 'frsqrte')):
            word = (63 << 26) | (2 << 21) | (3 << 11) | (xo << 1)
            self.assertEqual(a.decode_selected(word, 0), dict(mnemonic=name, fD=2, fB=3))
            for invalid in (word | 1, word | (1 << 16)):
                with self.assertRaises(a.c.FormatError): a.decode_selected(invalid, 0)
        for word in ((63 << 26) | (1 << 11) | (25 << 1),
                     (63 << 26) | (32 << 1) | (4 << 21),
                     (59 << 26) | (1 << 6) | (20 << 1),
                     (59 << 26) | (1 << 11) | (25 << 1),
                     d_form(37, 1, 0, -16), d_form(11, 1, 4, 1),
                     (31 << 26) | (954 << 1) | (1 << 11),
                     (31 << 26) | (23 << 1) | 1,
                     (31 << 26) | (0 << 1) | 1,
                     spr_form(339, 1), spr_form(467, 0, 9), spr_form(339, record=1),
                     (18 << 26) | 2, (16 << 26) | (4 << 21) | (2 << 16) | 1,
                     (16 << 26) | (12 << 21) | (1 << 16)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        short = (56 << 26) | (1 << 21) | (1 << 16) | (1 << 15) | (5 << 12) | 8
        self.assertEqual(a.decode_selected(short, 0), dict(mnemonic='psq_l', fD=1, rA=1,
                                                         displacement=8, W=1, I=5))
        for invalid in (short ^ (1 << 15), short ^ (1 << 12), short ^ (1 << 21), short ^ 4):
            with self.assertRaisesRegex(a.c.FormatError, 'quantized short'): a.decode_selected(invalid, 0)

    def test_fixed_reads_fail_before_decode(self):
        for pc, size, _ in a.RANGES + a.SUPPORT_RANGES:
            for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                                   (pc - 4, 4), (pc + size, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, address, width)
            for fields in ((True, size), (pc, float(size))):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    a.range_evidence(None, a.TEXT_MAPPING, *fields)
            for index in range(len(a.TEXT_MAPPING)):
                bad = list(a.TEXT_MAPPING)
                bad[index] = 'wrong' if isinstance(bad[index], str) else bad[index] + 1
                with self.assertRaisesRegex(a.c.FormatError, 'exact mapping'):
                    a.range_evidence(None, tuple(bad), pc, size)
            for raw, reason in ((bytes(size), 'digest'), (bytes(size - 4), 'byte width'),
                                (bytes(size + 4), 'byte width')):
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, reason):
                        a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, pc, size)
                    decoder.assert_not_called()
            with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(bytes(4)).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                    a.range_evidence(FakeDB(bytes(4)), a.TEXT_MAPPING, pc, 4)
            with patch.object(a, 'RANGES', a.RANGES * 2), patch.object(a, 'SUPPORT_RANGES', a.SUPPORT_RANGES * 2):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, pc, size)

    def test_constant_and_mask_refusals(self):
        for reader, mapping, items in ((a.constant_evidence, a.DATA5_MAPPING, a.CONSTANTS),
                                      (a.mask_evidence, a.DATA3_MAPPING, (a.MASK_WINDOW,))):
            for pc, size, *_ in items:
                for address, width in ((pc - 1, size), (pc, size - 1), (pc, size + 1),
                                       (pc + size, size), (pc, 1000000)):
                    if (address, width) in [item[:2] for item in items]: continue
                    with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                        reader(None, mapping, address, width)
                for fields in ((True, size), (pc, float(size))):
                    with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                        reader(None, mapping, *fields)
                for bad in (list(mapping), tuple(float(v) if type(v) is int else v for v in mapping),
                            (*mapping[:-1], mapping[-1] + 1)):
                    with self.assertRaisesRegex(a.c.FormatError, 'exact mapping'):
                        reader(None, bad, pc, size)
                for raw, reason in ((bytes(size - 1), 'byte width'),
                                    (bytes(size + 1), 'byte width'), (b'\xff' * size, 'mismatch')):
                    with self.assertRaisesRegex(a.c.FormatError, reason):
                        reader(FakeDB(raw), mapping, pc, size)
        with patch.object(a, 'MASK_SHA', hashlib.sha256(bytes(12)).hexdigest()):
            with self.assertRaisesRegex(a.c.FormatError, 'values mismatch'):
                a.mask_evidence(FakeDB(bytes(12)), a.DATA3_MAPPING, *a.MASK_WINDOW)

    def test_authentication_precedes_parsing(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); reader.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty',
                       'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), \
                    patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_schema_rejected_before_new_reads(self):
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for field, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[field] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'):
                    a.inspect(data, digest)
                parser.return_value.rows.assert_not_called(); ranges.assert_not_called()

    def test_mapping_guards_precede_all_new_reads(self):
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
                    patch.object(a, 'range_evidence') as ranges, \
                    patch.object(a, 'constant_evidence') as constants, patch.object(a, 'mask_evidence') as masks:
                parser.return_value.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                parser.return_value.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called(); constants.assert_not_called(); masks.assert_not_called()

    def test_shared_allowlists_unchanged_and_no_arbitrary_cli(self):
        for address, width, _ in a.RANGES + a.SUPPORT_RANGES:
            self.assertNotIn((address, width), a.c.TARGETS)
            self.assertNotIn((address, width), [row[:2] for row in a.command.RANGES])
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.command.read_range(None, address, width, 0x80000000)
            for reader in (a.status, testers):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    reader.range_evidence(None, 21, address, width)
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.normal.range_evidence(None, a.TEXT_MAPPING, address, width)
        self.assertNotIn(a.MASK_WINDOW, a.c.TARGETS)
        self.assertNotIn(a.MASK_WINDOW, [row[:2] for row in a.command.RANGES])
        for option in (['--address', '80069ea4'], ['--width', '316'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2); inspect.assert_not_called()

    def test_map_and_c_marker_extent_basis(self):
        root = Path(__file__).resolve().parents[3]
        text = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        rows = {int(pc, 16): int(size, 16) for pc, size in
                re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ', text, re.M)}
        source = (root / 'research/decomp/ghidra-export/chunk_0009.c').read_text()
        markers = [int(pc, 16) for pc in re.findall(r'^// ==== ([0-9a-f]{8}) ', source, re.M)]
        for pc, size, _ in a.RANGES:
            self.assertEqual(rows[pc], size)
            self.assertEqual(markers[markers.index(pc) + 1], pc + size)
        for address, width, _ in a.SUPPORT_RANGES[:3]: self.assertEqual(rows[address], width)
        self.assertEqual(rows[0x800ea2ec], 340)
        for chunk, entries in (('0005', (0x80045204, 0x80045238)), ('0025', (0x800ea2c8, 0x800ea2ec))):
            source = (root / f'research/decomp/ghidra-export/chunk_{chunk}.c').read_text()
            markers = [int(pc, 16) for pc in re.findall(r'^// ==== ([0-9a-f]{8}) ', source, re.M)]
            for address in entries:
                self.assertEqual(markers[markers.index(address) + 1], address + rows[address])


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

    def test_all_operands_both_archives_and_coverage(self):
        for result in self.results:
            for span, (pc, size, digest) in zip(result['ranges'], a.RANGES):
                expected = [dict(address=f'{pc + index * 4:08x}', **item)
                            for index, item in enumerate(EXPECTED[pc])]
                self.assertEqual(span['instructions'], expected)
                self.assertEqual(span['sha256'], digest)
                self.assertEqual(span['end_exclusive'], f'{pc + size:08x}')
            self.assertEqual(sum(x['represented_instructions'] for x in result['function_coverage']), 421)
            for coverage, (pc, size, _) in zip(result['function_coverage'], a.RANGES):
                self.assertEqual(coverage['unrepresented_instructions'], 0)
                self.assertEqual(coverage['unrepresented_ranges'], [])
                self.assertEqual(coverage['map_size'], size)
                self.assertEqual(coverage['extent_basis'], 'symbol map, C markers and authenticated return')
            for span, (pc, size, digest) in zip(result['support_ranges'], a.SUPPORT_RANGES):
                self.assertEqual(span['instructions'], [dict(address=f'{pc + i * 4:08x}', **item)
                                 for i, item in enumerate(SUPPORT_EXPECTED[pc])])
                self.assertEqual(span['sha256'], digest)
                self.assertEqual(len(span['instructions']), size // 4)
        for key in ('ranges', 'support_ranges', 'constants', 'mask_window', 'function_coverage',
                    'support_coverage', 'mappings', 'r2_basis', 'r13_basis', 'reused_zero_trig'):
            self.assertEqual(self.results[0][key], self.results[1][key])

    def test_physical_provenance_and_returns(self):
        for span, (pc, size, _) in zip(self.results[0]['ranges'], a.RANGES):
            delta = pc - 0x80069ea4
            self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=47,
                             chain_offset=411844 + delta, data_offset=2394 + delta,
                             length=size, obfuscated=True, physical_offset=788832 + delta)])
            self.assertEqual(span['instructions'][-1], dict(address=f'{pc + size - 4:08x}', mnemonic='blr'))
        for constant, (pc, width, bits) in zip(self.results[0]['constants'], a.CONSTANTS):
            delta = pc - 0x8043762c
            self.assertEqual(constant['bits'], bits)
            self.assertEqual(constant['spans'], [dict(root_buffer=263, data_buffer=264,
                             chain_offset=3084 + delta, data_offset=3084 + delta,
                             length=width, obfuscated=True, physical_offset=4344850 + delta)])
        mask = self.results[0]['mask_window']
        self.assertEqual(mask['spans'], [dict(root_buffer=199, data_buffer=206,
                         chain_offset=101172, data_offset=2904, length=12,
                         obfuscated=True, physical_offset=3394398)])
        self.assertEqual(mask['slots'], [dict(index=i, mask57a=x, mask57b=y)
                                        for i, (x, y) in enumerate(a.MASK_PAIRS)])
        self.assertFalse(mask['extent_proven'])
        physical = ((37, 261156, 15486, 638084), (37, 261208, 15538, 638136),
                    (79, 937192, 3646, 1314372), (79, 937228, 3682, 1314408),
                    (79, 937548, 4002, 1314728))
        for span, (_, width, _), (buffer, chain, data, absolute) in zip(
                self.results[0]['support_ranges'], a.SUPPORT_RANGES, physical):
            self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=buffer,
                             chain_offset=chain, data_offset=data, length=width,
                             obfuscated=True, physical_offset=absolute)])

    def test_voice_gate_is_signed_and_partial_coverage_is_explicit(self):
        result = self.results[0]
        ins = {item['address']: item for span in result['support_ranges'] for item in span['instructions']}
        self.assertEqual(ins['800ea2d0']['immediate'], -1)
        self.assertEqual(ins['800ea2d8']['target'], '800ea2ec')
        self.assertEqual(ins['800ea308'], dict(address='800ea308', mnemonic='lwz', rD=6, rA=13,
                                             displacement=-31852))
        self.assertEqual(ins['800ea30c']['displacement'], 0x45)
        self.assertEqual(ins['800ea310']['mnemonic'], 'extsb')
        self.assertEqual(ins['800ea314']['immediate'], 4)
        self.assertEqual((ins['800ea318']['BO'], ins['800ea318']['BI']), (4, 1))
        self.assertEqual(ins['800ea318']['target'], '800ea324')  # <=4 remains unimplemented
        self.assertEqual(ins['800ea31c']['immediate'], -1)
        self.assertEqual(ins['800ea320']['target'], '800ea42c')
        self.assertFalse(any(x['mnemonic'] == 'bl' for span in result['support_ranges'][3:]
                             for x in span['instructions']))
        coverage = result['support_coverage'][-1]
        self.assertEqual((coverage['map_size'], coverage['selected_width'], coverage['represented_instructions'],
                          coverage['unrepresented_instructions']), (340, 76, 19, 66))
        self.assertEqual(coverage['unrepresented_ranges'],
                         [dict(address='800ea324', end_exclusive='800ea42c', width=264)])
        self.assertEqual(result['r13_basis']['derived_cell_address'], '80433934')

    def test_reused_zero_kernels_preserve_existing_scope_and_report_omissions(self):
        reused = self.results[0]['reused_zero_trig']
        ranges = reused['ranges']
        self.assertEqual([(x['address'], x['width'], x['represented_instructions'], x['unrepresented_instructions'])
                          for x in ranges], [('8023c9e8', 216, 51, 3), ('8023c480', 212, 50, 3),
                                             ('8023bf8c', 160, 27, 13), ('8023b044', 244, 44, 17)])
        for span, (pc, width) in zip(ranges, a.REUSED_ZERO_RANGES):
            self.assertIn((pc, width), [row[:2] for row in a.traversal.RANGES])
            represented = {int(x['address'], 16) for x in span['instructions']}
            omitted = {int(x, 16) for x in span['unrepresented_addresses']}
            self.assertFalse(represented & omitted)
            self.assertEqual(represented | omitted, set(range(pc, pc + width, 4)))
        self.assertEqual(ranges[0]['unrepresented_addresses'], ['8023c9ec', '8023ca2c', '8023cab4'])
        self.assertEqual(ranges[1]['unrepresented_addresses'], ['8023c484', '8023c4c0', '8023c548'])
        ins = {x['address']: x for span in ranges for x in span['instructions']}
        for pc, target in (('8023ca18', '8023bf8c'), ('8023c4ac', '8023b044')):
            self.assertEqual((ins[pc]['mnemonic'], ins[pc]['target']), ('bl', target))
        # These reached kernel prefixes are completely represented by the reused
        # reader. Untaken polynomial instructions are not silently filled in.
        for pc, text in ((0x8023bf8c, '''
stwu 1 1 -32
addis 0 0 15936
stfd 1 1 8
lwz 4 1 8
rlwinm 4 4 0 1 31 0
cmp 0 0 4 0
bc 4 0 8023bfc0
fctiwz 0 1
stfd 0 1 16
lwz 0 1 20
cmpi 0 0 0 0
bc 4 2 8023bfc0
b 8023c024
'''), (0x8023b044, '''
stwu 1 1 -32
addis 0 0 15936
stfd 1 1 8
lwz 3 1 8
rlwinm 3 4 0 1 31 0
cmp 0 0 4 0
bc 4 0 8023b07c
fctiwz 0 1
stfd 0 1 24
lwz 0 1 28
cmpi 0 0 0 0
bc 4 2 8023b07c
lfd 1 2 -6640
b 8023b130
''')):
            for index, item in enumerate(ops(text)):
                address = f'{pc + index * 4:08x}'
                self.assertEqual(ins[address], dict(address=address, **item))
        self.assertEqual([(x['address'], x['bits']) for x in reused['constants']],
                         [('80437078', '38c90fdb'), ('8043d198', '0000000000000000'),
                          ('8043d150', '0000000000000000'), ('8043d030', '3ff0000000000000')])

    def test_no_target_short_circuit_and_admission_order(self):
        ins = {x['address']: x for span in self.results[0]['ranges'] for x in span['instructions']}
        self.assertEqual(ins['8006c688']['displacement'], 0x508)
        self.assertEqual(ins['8006c690']['target'], '8006c69c')
        self.assertEqual(ins['8006c694']['immediate'], 0)
        self.assertEqual(ins['8006c698']['target'], '8006c714')
        self.assertEqual(ins['80069f88']['target'], '8006c674')
        self.assertEqual(ins['80069f8c']['displacement'], 0x587)
        self.assertEqual([ins[pc]['displacement'] for pc in ('80069f94', '80069f98', '80069f9c')],
                         [0x585, 0x586, 0x587])
        self.assertEqual(ins['8006a128']['immediate'], -1)
        self.assertEqual(ins['8006a134']['target'], '8006a3b8')
        self.assertEqual(ins['8006a13c']['displacement'], 0x584)
        self.assertEqual(ins['8006a140']['target'], '8006bda8')
        self.assertEqual([ins[pc]['displacement'] for pc in ('8006bf18', '8006bf1c')], [0x764, 0x760])
        self.assertEqual([ins[pc]['displacement'] for pc in ('8006bf20', '8006bf50')], [0x72, 0x72])
        self.assertEqual([ins[pc]['displacement'] for pc in ('8006bf28', '8006bf58')], [0x764, 0x764])
        self.assertEqual(ins['8006bf38']['displacement'], 0x10)
        self.assertEqual(ins['8006bf3c']['mnemonic'], 'extsb')
        self.assertEqual(ins['8006bf40']['immediate'], 0x30)

    def test_retained_loads_reloads_and_effect_boundaries(self):
        ins = {x['address']: x for span in self.results[0]['ranges'] for x in span['instructions']}
        self.assertEqual([x['address'] for x in self.results[0]['ranges'][0]['instructions']
                          if x['mnemonic'] == 'lwz' and x['displacement'] == 0x5e0], ['80069edc'])
        self.assertEqual([ins[pc]['rS'] for pc in ('80069ee0', '80069ef4', '80069f08',
                                                  '80069f28', '80069f48', '80069f68')], [3] * 6)
        self.assertEqual(ins['8006a160']['rS'], 3)  # retained5e0 froma144
        self.assertEqual(ins['8006a1c4']['displacement'], 0x5e0)  # reload after first store
        self.assertEqual([ins[pc]['displacement'] for pc in ('8006a1ec', '8006a20c', '8006a228', '8006a248')],
                         [0x584] * 4)
        self.assertEqual([ins[pc]['displacement'] for pc in ('8006a268', '8006a278', '8006a28c',
                                                           '8006a2a0', '8006a2b4', '8006a2c8')],
                         [0, 4, 8, 12, 16, 20])
        self.assertEqual([ins[pc]['displacement'] for pc in ('8006a260', '8006a27c', '8006a290',
                                                           '8006a2a4', '8006a2b8', '8006a2cc')], [0x3e5] * 6)
        self.assertEqual([(x['address'], x['target']) for x in self.results[0]['ranges'][2]['instructions']
                          if x['mnemonic'] == 'bl'],
                         [('8006a140', '8006bda8'), ('8006a170', '8006a750'), ('8006a180', '8006a750'),
                          ('8006a1a0', '8004beb8'), ('8006a310', '8006a6fc'), ('8006a32c', '8006a750'),
                          ('8006a37c', '8006dbe0'), ('8006a398', '80011cc4'), ('8006a3b0', '800ea2c8')])
        self.assertEqual([(x['address'], x['target']) for x in self.results[0]['ranges'][3]['instructions']
                          if x['mnemonic'] == 'bl'],
                         [('8006be30', '8020bc88'), ('8006bf24', '80045204'), ('8006bf54', '80045238')])

    def test_arithmetic_schedule_constants_and_no_raw_code(self):
        floats = [x for x in self.results[0]['ranges'][3]['instructions']
                  if x['mnemonic'] in ('frsqrte', 'fnmsub', 'frsp')]
        self.assertEqual([x['address'] for x in floats], ['8006be40', '8006be54', '8006be64',
                         '8006be74', '8006be80', '8006bec0', '8006bed4', '8006bee4',
                         '8006bef4', '8006bf00'])
        self.assertEqual([x['value'] for x in self.results[0]['constants']], [0., -1., 0., .5, 3., 20000.])
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            for span in result['ranges']:
                self.assertTrue(set(span).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))
                for item in span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))


if __name__ == '__main__': unittest.main()
