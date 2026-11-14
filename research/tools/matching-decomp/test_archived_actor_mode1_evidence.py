#!/usr/bin/env python3
"""Frozen all-operand witnesses, independent inverse encodings, and refusal guards.

Synthetic checks need no archive. Local tests authenticate both known snapshots;
missing local inputs skip rather than fetch. No runtime execution or raw output.
"""
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

import read_archived_actor_mode1_evidence as a


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


# Explicit fixed operand columns, including condition/record/overflow fields.
FIELDS = {'add': 'rD rA rB OE Rc',
 'addi': 'rD rA immediate',
 'addis': 'rD rA immediate',
 'b': 'target AA LK',
 'bc': 'BO BI LK target AA',
 'bctrl': 'BO BI BH LK',
 'bl': 'target AA LK',
 'blr': 'BO BI BH LK',
 'cmp': 'BF L rA rB',
 'cmpi': 'BF L rA immediate',
 'cror': 'BT BA BB',
 'extsb': 'rS rA Rc',
 'fadds': 'fD fA fB Rc',
 'fcmpo': 'BF fA fB',
 'fdivs': 'fD fA fB Rc',
 'fmr': 'fD fB Rc',
 'fmuls': 'fD fA fC Rc',
 'fneg': 'fD fB Rc',
 'fsubs': 'fD fA fB Rc',
 'lbz': 'rD rA displacement',
 'lbzx': 'rD rA rB',
 'lfd': 'fD rA displacement',
 'lfs': 'fD rA displacement',
 'lmw': 'rD rA displacement',
 'lwz': 'rD rA displacement',
 'lwzx': 'rD rA rB',
 'mflr': 'rD',
 'mtctr': 'rS',
 'mtlr': 'rS',
 'mulli': 'rD rA immediate',
 'or': 'rS rA rB Rc',
 'ps_muls0': 'fD fA fC Rc',
 'psq_l': 'fD rA displacement W I',
 'psq_st': 'fS rA displacement W I',
 'rlwinm': 'rS rA SH MB ME Rc',
 'stb': 'rS rA displacement',
 'stfd': 'fS rA displacement',
 'stfs': 'fS rA displacement',
 'stmw': 'rS rA displacement',
 'stw': 'rS rA displacement',
 'stwu': 'rS rA displacement',
 'xori': 'rS rA immediate',
 'xoris': 'rS rA immediate'}


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


# Frozen complete schedule, reviewed against instruction forms and C boundaries.
# encode() below is separate from the reader and reconstitutes each span digest.
EXPECTED = {
    0x80055568: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
addi 0 0 2
stw 31 1 28
or 3 31 3 0
stw 30 1 24
stb 0 3 1400
bl 80055dcc 0 1
or 31 3 31 0
bl 8005568c 0 1
or 31 3 31 0
bl 80059068 0 1
lwz 5 31 32
or 31 3 31 0
lwz 4 31 36
lwz 0 31 40
lwz 12 31 1212
stw 5 1 8
stw 4 1 12
stw 0 1 16
mtctr 12
bctrl 20 0 0 1
lbz 0 31 1499
addis 3 0 -32723
lbz 30 31 1498
addi 5 0 1
extsb 0 0 0
addi 4 3 14248
stb 5 31 1400
rlwinm 0 0 2 0 29 0
or 31 3 31 0
lwzx 12 4 0
mtctr 12
bctrl 20 0 0 1
addi 3 0 0
extsb 30 0 0
addis 4 0 -32723
stb 3 31 1400
rlwinm 0 0 2 0 29 0
or 31 3 31 0
addi 4 4 13992
lwzx 12 4 0
mtctr 12
bctrl 20 0 0 1
addi 0 0 2
or 31 3 31 0
stb 0 31 1400
lwz 12 31 1216
mtctr 12
bctrl 20 0 0 1
or 31 3 31 0
bl 80055ee4 0 1
lwz 0 31 1504
rlwinm 0 0 0 25 25 1
bc 4 2 0 8005566c 0
lbz 0 31 1432
extsb 0 0 1
bc 12 2 0 8005566c 0
lwz 0 1 8
lwz 3 1 12
stw 0 31 32
lwz 0 1 16
stw 3 31 36
stw 0 31 40
or 31 3 31 0
bl 8005b880 0 1
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
    0x800487ec: ops('''
stwu 1 1 -64
mflr 0
stw 0 1 68
stfd 31 1 48
psq_st 31 1 56 0 0
stmw 26 1 24
or 7 30 7 1
fmr 31 1 0
or 3 26 3 0
or 4 27 4 0
or 5 28 5 0
or 6 29 6 0
bc 4 2 0 80048828 0
bl 8004871c 0 1
b 80048910 0 0
or 27 5 27 0
addi 4 0 0
addi 6 0 0
bl 8004b94c 0 1
or 26 3 26 0
or 28 4 28 0
or 29 5 29 0
bl 8004d1f4 0 1
rlwinm 27 4 6 0 25 0
or 3 0 3 0
addi 31 4 6868
or 26 3 26 0
add 31 26 31 0 0
or 0 6 0 0
stb 28 31 40
or 27 4 27 0
or 31 5 31 0
stb 29 31 41
bl 8004d244 0 1
addi 0 30 1
lbz 3 31 42
xoris 0 0 32768
addis 4 0 17200
stw 0 1 12
rlwinm 3 0 25 31 31 0
addi 5 0 1
lfd 1 2 -31016
stb 0 31 49
addi 0 0 0
lfs 3 2 -31024
or 26 3 26 0
stw 4 1 8
or 27 6 27 0
addi 4 0 0
stb 5 31 47
addi 5 0 0
lfd 0 1 8
lfs 2 26 7624
fsubs 1 0 1 0
lfs 0 2 -31020
stfs 2 31 28
stfs 1 31 24
lfs 2 31 28
lfs 1 31 24
fdivs 1 2 1 0
fsubs 1 3 1 0
stfs 1 31 32
stb 0 31 54
stfs 0 31 16
stfs 31 31 20
stfs 0 31 8
stfs 31 31 12
lfs 1 31 12
bl 8004a754 0 1
lfs 1 31 32
or 26 3 26 0
or 27 4 27 0
bl 8004a8cc 0 1
psq_l 31 1 56 0 0
lfd 31 1 48
lmw 26 1 24
lwz 0 1 68
mtlr 0
addi 1 1 64
blr 20 0 0 0
'''),
    0x8004a00c: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
or 5 31 5 0
stw 30 1 24
or 4 30 4 0
stw 29 1 20
or 3 29 3 0
lfs 1 4 8
lfs 0 3 7624
fadds 0 1 0 0
stfs 0 4 8
lfs 1 4 28
lfs 0 3 7624
fadds 0 1 0 0
stfs 0 4 28
lfs 1 4 28
lfs 0 4 24
fcmpo 0 1 0
bc 4 0 0 8004a098 0
fdivs 0 1 0 0
lfs 1 2 -31024
or 31 6 31 0
addi 4 0 0
addi 5 0 0
addi 7 0 0
fsubs 0 1 0 0
stfs 0 30 32
bl 8004a830 0 1
lfs 1 30 32
or 29 3 29 0
or 31 4 31 0
bl 8004a8cc 0 1
b 8004a0c4 0 0
fsubs 0 1 0 0
lfs 1 30 12
or 31 6 31 0
addi 4 0 0
addi 5 0 0
addi 7 0 1
fadds 0 1 0 0
stfs 0 30 12
bl 8004a830 0 1
addi 0 0 0
stb 0 30 47
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
    0x8004b94c: ops('''
stwu 1 1 -32
mflr 0
rlwinm 5 8 6 0 25 0
cmpi 0 0 5 0
stw 0 1 36
rlwinm 4 0 8 0 23 0
stw 31 1 28
stw 30 1 24
or 4 30 4 0
xori 30 31 1
stw 29 1 20
or 3 29 3 0
add 3 0 8 0 0
rlwinm 31 7 8 0 23 0
addi 0 3 6868
add 4 29 0 0 0
add 3 7 8 0 0
addi 7 3 6868
lwz 3 4 0
lwz 0 4 4
add 7 29 7 0 0
stw 3 7 0
stw 0 7 4
lwz 3 4 8
lwz 0 4 12
stw 3 7 8
stw 0 7 12
lwz 3 4 16
lwz 0 4 20
stw 3 7 16
stw 0 7 20
lwz 3 4 24
lwz 0 4 28
stw 3 7 24
stw 0 7 28
lwz 3 4 32
lwz 0 4 36
stw 3 7 32
stw 0 7 36
lwz 3 4 40
lwz 0 4 44
stw 3 7 40
stw 0 7 44
lwz 3 4 48
lwz 0 4 52
stw 3 7 48
stw 0 7 52
lwz 3 4 56
lwz 0 4 60
stw 3 7 56
stw 0 7 60
stb 31 7 51
bc 4 2 0 8004ba40 0
rlwinm 30 0 1 0 30 0
rlwinm 31 3 1 0 30 0
add 4 29 0 0 0
lbz 0 4 7540
add 3 29 3 0 0
stb 0 3 7540
lbz 0 4 7541
stb 0 3 7541
cmpi 0 0 6 0
bc 4 2 0 8004baf8 0
or 29 3 29 0
or 5 4 5 0
addi 5 1 8
bl 8004b8f4 0 1
mulli 4 30 384
rlwinm 30 0 9 0 22 0
rlwinm 31 5 9 0 22 0
lwz 3 1 8
add 9 29 0 0 0
mulli 0 31 384
add 10 29 5 0 0
add 11 29 4 0 0
add 12 29 0 0 0
b 8004baec 0 0
lwz 4 29 1200
addi 0 3 140
addi 3 3 1
lbzx 6 4 0
extsb 6 6 0
rlwinm 6 4 4 0 27 0
addi 5 4 3796
add 7 9 5 0 0
lwz 0 7 0
add 8 10 5 0 0
lwz 4 7 4
mulli 6 6 12
stw 0 8 0
addi 0 6 4820
stw 4 8 4
add 5 11 0 0 0
add 6 12 0 0 0
lwz 4 7 8
lwz 0 7 12
stw 4 8 8
stw 0 8 12
lwz 4 5 0
lwz 0 5 4
stw 4 6 0
stw 0 6 4
lwz 0 5 8
stw 0 6 8
lwz 0 1 12
cmp 0 0 3 0
bc 12 0 0 8004ba80 0
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
    0x8004a8cc: ops('''
stwu 1 1 -128
mflr 0
stw 0 1 132
stfd 31 1 112
psq_st 31 1 120 0 0
stfd 30 1 96
psq_st 30 1 104 0 0
stmw 27 1 76
fmr 30 1 0
lfs 0 2 -31024
or 3 29 3 0
addi 5 1 8
fsubs 31 0 30 0
bl 8004b8f4 0 1
lwz 31 1 8
b 8004aab0 0 0
lwz 3 29 1200
addi 0 31 140
fmr 1 31 0
addi 4 1 60
lbzx 30 3 0
extsb 30 30 0
mulli 0 30 12
add 28 29 0 0 0
addi 27 28 4820
or 27 3 27 0
bl 8020ba9c 0 1
fmr 1 30 0
addi 3 28 5204
addi 4 1 48
bl 8020ba9c 0 1
or 27 5 27 0
addi 3 1 60
addi 4 1 48
bl 8020ba54 0 1
rlwinm 30 0 4 0 27 0
add 5 29 0 0 0
lwz 3 5 3796
lwz 0 5 3800
stw 3 1 32
stw 0 1 36
lfs 1 1 32
lwz 3 5 3804
lwz 0 5 3808
lfs 0 1 36
stw 3 1 40
stw 0 1 44
lfs 4 1 40
lwz 3 5 4308
lwz 0 5 4312
lfs 6 1 44
stw 3 1 16
stw 0 1 20
lfs 8 1 16
lfs 7 1 20
fsubs 3 1 8 0
lwz 3 5 4316
lwz 0 5 4320
fsubs 2 0 7 0
fadds 1 1 8 0
stw 3 1 24
fadds 0 0 7 0
lfs 9 1 24
fmuls 3 3 3 0
stw 0 1 28
fmuls 2 2 2 0
fsubs 10 4 9 0
lfs 11 1 28
fadds 5 4 9 0
fmuls 1 1 1 0
fmuls 0 0 0 0
fsubs 12 6 11 0
fadds 6 6 11 0
fmuls 4 10 10 0
fadds 3 3 2 0
fmuls 2 5 5 0
fadds 0 1 0 0
fmuls 5 12 12 0
fadds 3 4 3 0
fmuls 1 6 6 0
fadds 0 2 0 0
fadds 2 5 3 0
fadds 0 1 0 0
fcmpo 0 2 0
bc 4 1 0 8004aa40 0
fneg 3 8 0
fneg 2 7 0
fneg 1 9 0
fneg 0 11 0
stfs 3 1 16
stfs 2 1 20
stfs 1 1 24
stfs 0 1 28
fmr 1 30 0
addi 3 1 32
addi 4 1 16
addi 5 5 3796
bl 8020bf08 0 1
addi 0 0 2
addi 4 0 0
mtctr 0
lwz 3 29 1200
addi 0 4 66
lbzx 0 3 0
extsb 0 0 0
cmp 0 0 0 30
bc 4 2 0 8004aaa4 0
lfs 0 2 -31004
fcmpo 0 30 0
bc 4 1 0 8004aa94 0
add 3 29 4 0 0
lbz 0 3 7542
stb 0 3 7572
b 8004aaac 0 0
add 3 29 4 0 0
lbz 0 3 7540
stb 0 3 7572
b 8004aaac 0 0
addi 4 4 1
bc 16 0 0 8004aa60 0
addi 31 31 1
lwz 0 1 12
cmp 0 0 31 0
bc 12 0 0 8004a90c 0
psq_l 31 1 120 0 0
lfd 31 1 112
psq_l 30 1 104 0 0
lfd 30 1 96
lmw 27 1 76
lwz 0 1 132
mtlr 0
addi 1 1 128
blr 20 0 0 0
'''),
    0x8020ba9c: ops('''
psq_l 0 3 0 0 0
psq_l 2 3 8 1 0
ps_muls0 0 0 1 0
psq_st 0 4 0 0 0
ps_muls0 0 2 1 0
psq_st 0 4 8 1 0
blr 20 0 0 0
'''),
    0x8020bf08: ops('''
mflr 0
stw 0 1 4
stwu 1 1 -80
stfd 31 1 72
stfd 30 1 64
stfd 29 1 56
fmr 29 1 0
stfd 28 1 48
stfd 27 1 40
stw 31 1 36
or 5 31 5 0
stw 30 1 32
or 4 30 4 0
stw 29 1 28
or 3 29 3 0
lfs 4 3 0
lfs 3 4 0
lfs 2 3 4
lfs 1 4 4
fmuls 3 4 3 0
lfs 4 3 8
fmuls 1 2 1 0
lfs 2 4 8
lfs 6 3 12
fmuls 2 4 2 0
lfs 5 4 12
fadds 1 3 1 0
lfs 0 2 -8064
fmuls 3 6 5 0
lfs 30 2 -8040
fadds 1 2 1 0
fadds 1 3 1 0
fcmpo 0 1 0
bc 4 0 0 8020bf98 0
fneg 1 1 0
fneg 30 30 0
lfs 0 2 -8032
fcmpo 0 1 0
cror 2 0 2
bc 4 2 0 8020bfe0 0
bl 8023cc8c 0 1
fmr 27 1 0
bl 8023cc44 0 1
lfs 0 2 -8040
fmr 28 1 0
fsubs 0 0 29 0
fmuls 1 0 27 0
bl 8023cc44 0 1
fdivs 31 1 28 0
fmuls 1 29 27 0
bl 8023cc44 0 1
fdivs 0 1 28 0
fmuls 30 30 0 0
b 8020bfec 0 0
lfs 0 2 -8040
fmuls 30 30 29 0
fsubs 31 0 29 0
lfs 1 29 0
lfs 0 30 0
fmuls 1 31 1 0
fmuls 0 30 0 0
fadds 0 1 0 0
stfs 0 31 0
lfs 1 29 4
lfs 0 30 4
fmuls 1 31 1 0
fmuls 0 30 0 0
fadds 0 1 0 0
stfs 0 31 4
lfs 1 29 8
lfs 0 30 8
fmuls 1 31 1 0
fmuls 0 30 0 0
fadds 0 1 0 0
stfs 0 31 8
lfs 1 29 12
lfs 0 30 12
fmuls 1 31 1 0
fmuls 0 30 0 0
fadds 0 1 0 0
stfs 0 31 12
lwz 0 1 84
lfd 31 1 72
lfd 30 1 64
lfd 29 1 56
lfd 28 1 48
lfd 27 1 40
lwz 31 1 36
lwz 30 1 32
lwz 29 1 28
addi 1 1 80
mtlr 0
blr 20 0 0 0
'''),
}


def d_form(op, d, ra, value):
    return (op << 26) | (d << 21) | (ra << 16) | (value & 65535)


def encode(row, pc):
    """Independent inverse encoding of the fixed witness, never calls decoder."""
    n = row['mnemonic']
    dops = {'mulli': 7, 'cmpi': 11, 'addi': 14, 'addis': 15, 'xori': 26, 'xoris': 27,
            'lwz': 32, 'lbz': 34, 'stw': 36, 'stwu': 37, 'stb': 38, 'lmw': 46,
            'stmw': 47, 'lfs': 48, 'lfd': 50, 'stfs': 52, 'stfd': 54}
    if n in dops:
        d = next((row[k] for k in ('rD', 'rS', 'fD', 'fS') if k in row), 0)
        if n == 'cmpi': d = (row['BF'] << 2) | row['L']
        return d_form(dops[n], d, row['rA'], row.get('displacement', row.get('immediate')))
    if n in ('b', 'bl'):
        return 18 << 26 | ((int(row['target'], 16) - pc) & 0x3fffffc) | row['AA'] << 1 | row['LK']
    if n == 'bc':
        return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | \
            ((int(row['target'], 16) - pc) & 65532) | row['AA'] << 1 | row['LK']
    if n in ('blr', 'bctrl'):
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | \
            (16 if n == 'blr' else 528) << 1 | row['LK']
    if n == 'cror':
        return 19 << 26 | row['BT'] << 21 | row['BA'] << 16 | row['BB'] << 11 | 449 << 1
    if n == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | \
            row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    if n in ('mflr', 'mtlr', 'mtctr'):
        spr = 9 if n == 'mtctr' else 8
        return 31 << 26 | row.get('rD', row.get('rS')) << 21 | (spr & 31) << 16 | \
            (spr >> 5) << 11 | (339 if n == 'mflr' else 467) << 1
    if n in ('lwzx', 'lbzx', 'or', 'add', 'extsb', 'cmp'):
        d = (row['BF'] << 2 | row['L']) if n == 'cmp' else row.get('rD', row.get('rS'))
        xo = {'lwzx': 23, 'lbzx': 87, 'or': 444, 'add': 266, 'extsb': 954, 'cmp': 0}[n]
        return 31 << 26 | d << 21 | row['rA'] << 16 | row.get('rB', 0) << 11 | xo << 1 | \
            row.get('OE', 0) << 10 | row.get('Rc', 0)
    if n in ('psq_l', 'psq_st'):
        return (56 if n == 'psq_l' else 60) << 26 | row.get('fD', row.get('fS')) << 21 | \
            row['rA'] << 16 | row['W'] << 15 | row['I'] << 12 | (row['displacement'] & 4095)
    if n in ('fdivs', 'fsubs', 'fadds', 'fmuls', 'ps_muls0'):
        op = 4 if n == 'ps_muls0' else 59
        xo = {'fdivs': 18, 'fsubs': 20, 'fadds': 21, 'fmuls': 25, 'ps_muls0': 12}[n]
        return op << 26 | row['fD'] << 21 | row['fA'] << 16 | row.get('fB', 0) << 11 | \
            row.get('fC', 0) << 6 | xo << 1 | row['Rc']
    if n in ('fneg', 'fmr', 'fcmpo'):
        d = row['BF'] << 2 if n == 'fcmpo' else row['fD']
        return 63 << 26 | d << 21 | row.get('fA', 0) << 16 | row['fB'] << 11 | \
            {'fneg': 40, 'fmr': 72, 'fcmpo': 32}[n] << 1 | row.get('Rc', 0)
    raise AssertionError(n)


class SyntheticTests(unittest.TestCase):
    def test_exact_scope_and_complete_frozen_witnesses(self):
        self.assertEqual([(pc, width) for pc, width, _ in a.RANGES], [
            (0x80055568, 292), (0x800487ec, 320), (0x8004a00c, 212),
            (0x8004b94c, 456), (0x8004a8cc, 532), (0x8020ba9c, 28), (0x8020bf08, 372)])
        self.assertEqual([(pc, bits) for pc, bits, _ in a.CONSTANTS], [
            (0x804370f0, '3f800000'), (0x804370f4, '00000000'),
            (0x804370f8, '4330000080000000'), (0x80437104, '3f000000'),
            (0x8043cab8, '3f800000'), (0x8043caa0, '00000000'), (0x8043cac0, '3f7fff58')])
        self.assertEqual(sum(map(len, EXPECTED.values())), 553)
        for pc, width, digest in a.RANGES:
            self.assertEqual(len(EXPECTED[pc]), width // 4)
            # Independent field-to-word encoding verifies every witness bit.
            words = [encode(row, pc + i*4) for i, row in enumerate(EXPECTED[pc])]
            raw = struct.pack('>' + 'I' * len(words), *words)
            self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
            for i, word in enumerate(words):
                self.assertEqual(a.decode_selected(word, pc + i*4), EXPECTED[pc][i])

    def test_word_and_pc_bounds(self):
        for word in (-1, 1 << 32, True, 1.0, '0'):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0, '0'):
            with self.assertRaisesRegex(a.c.FormatError, 'PC bounds'): a.decode_selected(0, pc)

    def test_signed_d_forms_and_register_directions(self):
        for op, name, reg in ((32, 'lwz', 'rD'), (34, 'lbz', 'rD'), (36, 'stw', 'rS'),
                              (37, 'stwu', 'rS'), (38, 'stb', 'rS'), (46, 'lmw', 'rD'),
                              (47, 'stmw', 'rS'), (48, 'lfs', 'fD'), (50, 'lfd', 'fD'),
                              (52, 'stfs', 'fS'), (54, 'stfd', 'fS')):
            for val in (-32768, -1, 0, 32767):
                self.assertEqual(a.decode_selected(d_form(op, 7, 3, val), 0),
                                 dict(mnemonic=name, **{reg: 7}, rA=3, displacement=val))
        for op, name in ((7, 'mulli'), (14, 'addi'), (15, 'addis')):
            self.assertEqual(a.decode_selected(d_form(op, 5, 3, -1), 0),
                             dict(mnemonic=name, rD=5, rA=3, immediate=-1))
        for op, name in ((26, 'xori'), (27, 'xoris')):
            self.assertEqual(a.decode_selected(d_form(op, 5, 3, 65535), 0),
                             dict(mnemonic=name, rS=5, rA=3, immediate=65535))
        for word in (d_form(37, 1, 0, -16), d_form(46, 3, 3, 16), d_form(11, 1, 0, 0)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_branches_and_condition_register_fields(self):
        for lk in (0, 1):
            self.assertEqual(a.decode_selected(0x4bfffffc | lk, 0),
                             dict(mnemonic='bl' if lk else 'b', target='fffffffc', AA=0, LK=lk))
        for bo, bi in ((4, 0), (4, 1), (4, 2), (12, 0), (12, 1), (12, 2), (16, 0)):
            word = 16 << 26 | bo << 21 | bi << 16 | 0xfffc
            self.assertEqual(a.decode_selected(word, 0x80001000),
                             dict(mnemonic='bc', BO=bo, BI=bi, LK=0, target='80000ffc', AA=0))
            for bad in (word | 1, word | 2):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for word in (0x48000002, 0x4e800021, 0x4e800420, 0x4e800820, 0x4e802020,
                     16 << 26 | 4 << 21 | 3 << 16):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        word = 19 << 26 | 2 << 21 | 0 << 16 | 2 << 11 | 449 << 1
        self.assertEqual(a.decode_selected(word, 0), dict(mnemonic='cror', BT=2, BA=0, BB=2))
        with self.assertRaises(a.c.FormatError): a.decode_selected(word | 1, 0)

    def test_spr_indexed_rotate_and_xo_guards(self):
        for name, spr, xo, reg in (('mflr', 8, 339, 'rD'), ('mtlr', 8, 467, 'rS'), ('mtctr', 9, 467, 'rS')):
            word = 31 << 26 | spr << 16 | xo << 1
            self.assertEqual(a.decode_selected(word, 0), dict(mnemonic=name, **{reg: 0}))
            for bad in (word | 1, word ^ 1 << 17):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for xo in (23, 87):
            word = 31 << 26 | 7 << 21 | 3 << 16 | 5 << 11 | xo << 1
            self.assertEqual(a.decode_selected(word, 0),
                             dict(mnemonic='lwzx' if xo == 23 else 'lbzx', rD=7, rA=3, rB=5))
            with self.assertRaises(a.c.FormatError): a.decode_selected(word | 1, 0)
        for word in (31 << 26 | 1 << 21, 31 << 26 | 954 << 1 | 1 << 11):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        row = dict(mnemonic='rlwinm', rS=5, rA=3, SH=11, MB=8, ME=27, Rc=1)
        self.assertEqual(a.decode_selected(encode(row, 0), 0), row)
        row = dict(mnemonic='add', rD=5, rA=3, rB=7, OE=0, Rc=1)
        self.assertEqual(a.decode_selected(encode(row, 0), 0), row)
        self.assertIsNone(a.decode_selected(encode(row, 0) | 1 << 10, 0))

    def test_float_and_paired_fields(self):
        for n in ('fdivs', 'fsubs', 'fadds', 'fmuls', 'ps_muls0'):
            row = dict(mnemonic=n, fD=7, fA=5, **({'fC': 3} if n in ('fmuls', 'ps_muls0') else {'fB': 3}), Rc=0)
            word = encode(row, 0)
            self.assertEqual(a.decode_selected(word, 0), row)
            for bad in (word | 1, word | (1 << 11 if n in ('fmuls', 'ps_muls0') else 1 << 6)):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for op, n, reg in ((56, 'psq_l', 'fD'), (60, 'psq_st', 'fS')):
            for val in (-2048, -1, 0, 2047):
                row = dict(mnemonic=n, **{reg: 7}, rA=3, displacement=val, W=1, I=5)
                self.assertEqual(a.decode_selected(encode(row, 0), 0), row)
        for n in ('fneg', 'fmr'):
            row = dict(mnemonic=n, fD=7, fB=5, Rc=0)
            word = encode(row, 0)
            self.assertEqual(a.decode_selected(word, 0), row)
            for bad in (word | 1, word | 1 << 16):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for bad in (63 << 26 | 32 << 1 | 1, 63 << 26 | 32 << 1 | 1 << 21):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for word in (0, 59 << 26 | 29 << 1, 63 << 26 | 12 << 1, 4 << 26 | 13 << 1):
            self.assertIsNone(a.decode_selected(word, 0))

    def test_unselected_duplicate_and_wrong_type_refusals(self):
        for pc, size, _ in a.RANGES:
            for address, width in ((pc + 4, size - 4), (pc, size + 4), (pc, size - 4), (pc - 4, 4), (pc + size, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, address, width)
            with patch.object(a, 'RANGES', a.RANGES * 2):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, pc, size)
        for pc in (0x80437100, 0x80437108, 0x8043cab4, 0x8043cabc, 0x802d0d74):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, pc)
        with patch.object(a, 'CONSTANTS', a.CONSTANTS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, 0x804370f0)
        for bad in (True, 1.0, '4', None):
            for args in ((bad, 292), (0x80055568, bad)):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    a.range_evidence(None, a.TEXT_MAPPING, *args)
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.constant_evidence(None, a.DATA5_MAPPING, bad)

    def test_exact_mappings_precede_selection(self):
        for reader, mapping, args in ((a.range_evidence, a.TEXT_MAPPING, (0x80055568, 292)),
                                      (a.constant_evidence, a.DATA5_MAPPING, (0x804370f0,))):
            for bad in (list(mapping), mapping[:-1] + (22,), (mapping[0] + 4,) + mapping[1:],
                        mapping[:2] + (float(mapping[2]),) + mapping[3:]):
                with self.assertRaisesRegex(a.c.FormatError, 'mapping'): reader(None, bad, *args)

    def test_width_digest_instruction_and_span_guards(self):
        for pc, width, _ in a.RANGES:
            for raw, reason in ((bytes(width), 'digest'), (bytes(width-4), 'byte width'), (bytes(width+4), 'byte width')):
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, reason):
                        a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, pc, width)
                    decoder.assert_not_called()
        for words, reason in (([0], 'unselected instruction'), ([0x38600000], 'terminal return'),
                              ([0x48001000, 0x4e800020], 'outside fixed span')):
            raw = struct.pack('>' + 'I'*len(words), *words)
            with patch.object(a, 'RANGES', ((0x80055568, len(raw), hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x80055568, len(raw))
        raw = struct.pack('>I', 0x4e800020)
        with patch.object(a, 'RANGES', ((0x80055568, 4, hashlib.sha256(raw).hexdigest()),)):
            db = FakeDB(raw); result = a.range_evidence(db, a.TEXT_MAPPING, 0x80055568, 4)
            self.assertEqual(db.calls, [(21, 327560, 4, 2796416)])
            self.assertNotIn('raw', result)

    def test_constants_width_bits_value_hash_and_no_following(self):
        for pc, bits, label in a.CONSTANTS:
            raw = bytes.fromhex(bits); db = FakeDB(raw)
            result = a.constant_evidence(db, a.DATA5_MAPPING, pc)
            self.assertEqual(db.calls, [(263, pc - 0x80436a20, len(raw), 27360)])
            self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
            self.assertEqual(result['bits'], bits)
            self.assertEqual(result['label'], label)
            self.assertEqual(result['value'], struct.unpack('>f' if len(raw) == 4 else '>d', raw)[0])
            for bad, reason in ((raw[:-1], 'byte width'), (raw + bytes(1), 'byte width'),
                                (bytes([raw[0] ^ 1]) + raw[1:], 'bits mismatch')):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.constant_evidence(FakeDB(bad), a.DATA5_MAPPING, pc)

    def test_authentication_precedes_parsing_and_selection(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as ranges, \
                    patch.object(a, 'constant_evidence') as constants:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); ranges.assert_not_called(); constants.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty',
                       'data5 digest mismatch', 'executable metadata SHA/type mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_actual_schema_failure_precedes_new_reads(self):
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for field, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[field] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'constant_evidence') as constants:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'): a.inspect(data, digest)
                parser.return_value.rows.assert_not_called(); ranges.assert_not_called(); constants.assert_not_called()

    def test_actual_mapping_failures_precede_new_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image',
                       'data5root', 'data5offset', 'data5length', 'data3root'):
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
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'constant_evidence') as constants:
                db = parser.return_value; db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called(); constants.assert_not_called()

    def test_no_shared_allowlist_changes_or_arbitrary_cli(self):
        for pc, width, _ in a.RANGES:
            self.assertNotIn((pc, width), a.c.TARGETS)
            self.assertNotIn((pc, width), [x[:2] for x in a.command.RANGES])
            self.assertNotIn((pc, width), [x[:2] for x in a.normal.RANGES])
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.normal.range_evidence(None, a.TEXT_MAPPING, pc, width)
        for opt in (['--address', '80055568'], ['--width', '292'], ['--target', '80055568'],
                    ['--raw'], ['--execute'], ['--follow']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + opt), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2); inspect.assert_not_called()

    def test_independent_source_boundaries_and_only_real_map_sizes(self):
        root = Path(__file__).resolve().parents[3]
        text = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        rows = {int(pc, 16): int(size, 16) for pc, size in re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ', text, re.M)}
        chunks = ('0006', '0005', '0006', '0006', '0006', '0064', '0064')
        for chunk, (pc, width, _) in zip(chunks, a.RANGES):
            source = (root / f'research/decomp/ghidra-export/chunk_{chunk}.c').read_text()
            markers = [int(v, 16) for v in re.findall(r'^// ==== ([0-9a-f]{8}) ', source, re.M)]
            self.assertEqual(markers[markers.index(pc) + 1], pc + width)
            if pc in (0x8020ba9c, 0x8020bf08): self.assertEqual(rows[pc], width)
            else: self.assertNotIn(pc, rows)

    def test_reuse_existing_dispatch_and_add_evidence_without_reads(self):
        import read_archived_normal_matrix_evidence as matrix
        import read_archived_actor_traversal_evidence as traversal
        self.assertEqual(matrix.TABLE_ADDRESS + 5*4, 0x802d0d74)
        self.assertEqual(matrix.TABLE_TARGETS[5], 0x800487ec)
        self.assertEqual(matrix.TABLE_ADDRESS + 10*4, 0x802d0d88)
        self.assertEqual(matrix.TABLE_TARGETS[10], 0x8004a00c)
        self.assertIn((0x8020ba54, 36, 'c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab'), traversal.RANGES)
        self.assertNotIn(0x8020ba54, [pc for pc, _, _ in a.RANGES])

    def test_state_snapshots_before_upper_handler_and_ordered_envelope(self):
        pc = 0x80055568; by_pc = {pc + i*4: row for i,row in enumerate(EXPECTED[pc])}
        self.assertEqual(by_pc[0x800555c4], dict(mnemonic='lbz', rD=0, rA=31, displacement=0x5db))
        self.assertEqual(by_pc[0x800555cc], dict(mnemonic='lbz', rD=30, rA=31, displacement=0x5da))
        self.assertEqual(by_pc[0x800555dc], dict(mnemonic='stb', rS=5, rA=31, displacement=0x578))
        self.assertEqual(by_pc[0x800555f8], dict(mnemonic='extsb', rS=30, rA=0, Rc=0))
        self.assertEqual([f'{pc + i*4:08x}' for i,row in enumerate(EXPECTED[pc]) if row['mnemonic'] == 'bctrl'],
                         ['800555c0', '800555f0', '80055618', '80055630'])
        self.assertEqual([row['target'] for row in EXPECTED[pc] if row['mnemonic'] == 'bl'],
                         ['80055dcc', '8005568c', '80059068', '80055ee4', '8005b880'])

    def test_linear_quaternion_is_not_fused_or_inclusive_threshold(self):
        pc = 0x8020bf08; by_pc = {pc + i*4: row for i,row in enumerate(EXPECTED[pc])}
        self.assertFalse(any(row['mnemonic'] == 'fmadds' for row in EXPECTED[pc]))
        self.assertEqual(by_pc[0x8020bfa0], dict(mnemonic='cror', BT=2, BA=0, BB=2))
        self.assertEqual(by_pc[0x8020bfa4], dict(mnemonic='bc', BO=4, BI=2, LK=0, target='8020bfe0', AA=0))
        self.assertEqual(by_pc[0x8020bfe4], dict(mnemonic='fmuls', fD=30, fA=30, fC=29, Rc=0))
        self.assertEqual(by_pc[0x8020bfe8], dict(mnemonic='fsubs', fD=31, fA=0, fB=29, Rc=0))
        self.assertEqual([row['target'] for row in EXPECTED[pc] if row['mnemonic'] == 'bl'],
                         ['8023cc8c', '8023cc44', '8023cc44', '8023cc44'])


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
                expected = [dict(address=f'{pc+i*4:08x}', **row) for i,row in enumerate(EXPECTED[pc])]
                self.assertEqual(span['instructions'], expected)
                self.assertEqual(span['sha256'], digest)
                self.assertEqual(span['end_exclusive'], f'{pc+width:08x}')
                self.assertEqual(span['width'], width)
            self.assertEqual(sum(x['represented_instructions'] for x in result['function_coverage']), 553)
            self.assertEqual([x['map_size'] for x in result['function_coverage']], [None]*5 + [28,372])
            for coverage in result['function_coverage']:
                self.assertEqual(coverage['unrepresented_instructions'], 0)
                self.assertEqual(coverage['unrepresented_ranges'], [])

    def test_both_archives_agree_and_exact_physical_spans(self):
        self.assertEqual([r['snapshot'] for r in self.results], ['db.3.gbf', 'db.4.gbf'])
        for key in ('ranges', 'constants', 'mappings', 'function_coverage', 'dispatch_basis'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        expected = ((21,42,327560,0,704518,292), (21,38,274956,12908,651890,320),
                    (21,39,281132,2706,658072,212), (21,39,287596,9170,664536,456),
                    (21,39,283372,4946,660312,532), (21,151,2122940,10178,2500552,28),
                    (21,151,2124072,11310,2501684,372),
                    (263,264,1744,1744,4343510,4), (263,264,1748,1748,4343514,4),
                    (263,264,1752,1752,4343518,8), (263,264,1764,1764,4343530,4),
                    (263,265,24728,8350,4366500,4), (263,265,24704,8326,4366476,4),
                    (263,265,24736,8358,4366508,4))
        for result in self.results:
            for item, (root,buf,offset,data_offset,physical,width) in zip(result['ranges'] + result['constants'], expected):
                self.assertEqual(item['spans'], [dict(root_buffer=root, data_buffer=buf, chain_offset=offset,
                                 data_offset=data_offset, physical_offset=physical, length=width, obfuscated=True)])
            self.assertEqual([(x['address'],x['bits']) for x in result['constants']],
                             [(f'{pc:08x}',bits) for pc,bits,_ in a.CONSTANTS])
            self.assertFalse('cells' in result or 'dispatch_window' in result)

    def test_literal_span_and_constant_reads_only_after_shared_controls(self):
        # Trace reader selections, not authentication's established shared reads.
        result = self.results[0]
        self.assertEqual([x['address'] for x in result['ranges']], [f'{pc:08x}' for pc,_,_ in a.RANGES])
        self.assertEqual([x['address'] for x in result['constants']], [f'{pc:08x}' for pc,_,_ in a.CONSTANTS])
        self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
        self.assertEqual(result['data5_sha256'], a.c.DATA5_SHA)
        self.assertEqual(result['executable_sha256_property_type'], 2)


if __name__ == '__main__':
    unittest.main()
