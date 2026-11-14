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

import read_archived_double_action_evidence as a


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


FIELDS.update({'cmpli':'BF L rA immediate','ori':'rS rA immediate','andi.':'rS rA immediate',
               'lhz':'rD rA displacement','lha':'rD rA displacement','sth':'rS rA displacement',
               'extsh':'rS rA Rc','neg':'rD rA OE Rc','subf':'rD rA rB OE Rc',
               'fctiwz':'fD fB Rc','ps_sub':'fD fA fB Rc','ps_add':'fD fA fB Rc'})

def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


# Frozen complete schedules; inverse encoding below independently checks each digest.
EXPECTED = {
    0x8006f7c0: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lha 0 3 1000
cmpi 0 0 0 3
bc 4 2 0 8006f7ec 0
addi 0 0 1
stb 0 31 1410
b 8006f7f4 0 0
addi 0 0 0
stb 0 31 1410
lwz 0 31 1504
rlwinm 0 0 0 31 31 1
bc 4 2 0 8006f80c 0
addi 0 0 0
sth 0 31 7676
stb 0 31 1774
lwz 0 31 1504
rlwinm 0 0 0 19 19 1
bc 4 2 0 8006f824 0
lha 0 31 626
rlwinm 0 0 0 30 28 0
sth 0 31 626
lbz 0 31 1422
rlwinm 0 0 0 27 25 0
stb 0 31 1422
lha 0 31 1000
cmpi 0 0 0 3
bc 4 2 0 8006f878 0
lbz 0 31 1992
extsb 0 0 1
bc 12 2 0 8006f878 0
lbz 0 31 1422
addi 3 31 1968
or 3 4 3 0
ori 0 0 32
stb 0 31 1422
bl 8004538c 0 1
lfs 1 2 -29480
addi 3 31 1968
lfs 0 31 180
or 3 4 3 0
fmuls 1 1 0 0
bl 8020ba9c 0 1
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x8005f238: ops('''
blr 20 0 0 0
'''),
    0x80065dfc: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lwz 12 3 1204
mtctr 12
bctrl 20 0 0 1
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x8006facc: ops('''
stwu 1 1 -16
mflr 0
addis 4 0 -32723
stw 0 1 20
addi 4 4 15208
lbz 0 3 1408
extsb 0 0 0
rlwinm 0 0 2 0 29 0
lwzx 12 4 0
mtctr 12
bctrl 20 0 0 1
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x80071598: ops('''
stwu 1 1 -16
mflr 0
addis 4 0 -32723
stw 0 1 20
addi 4 4 15432
lbz 0 3 1409
extsb 0 0 0
rlwinm 0 0 2 0 29 0
lwzx 12 4 0
mtctr 12
bctrl 20 0 0 1
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x800715d4: ops('''
stwu 1 1 -16
mflr 0
addi 4 13 -32056
stw 0 1 20
bl 800ff2bc 0 1
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x800ff2bc: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lbz 0 3 1345
extsb 0 0 1
bc 12 2 0 800ff2dc 0
addi 0 0 0
stw 0 3 204
lbz 0 3 1344
addis 5 0 -32718
addi 5 5 -4096
extsb 0 0 0
rlwinm 0 0 2 0 29 0
lwzx 12 5 0
mtctr 12
bctrl 20 0 0 1
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x800ff30c: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 4 31 4 0
stw 30 1 8
or 3 30 3 0
lbz 3 3 1344
addi 0 3 1
stb 0 30 1344
lwz 0 30 204
cmpli 0 0 0 0
bc 4 2 0 800ff348 0
lha 0 30 114
sth 0 30 1452
or 30 3 30 0
addi 4 0 193
bl 8006d144 0 1
lfs 0 2 -22380
addi 0 0 0
addi 3 30 32
addi 4 30 1512
stfs 0 30 80
addi 5 30 56
stfs 0 30 72
stfs 0 30 76
stfs 0 30 68
sth 0 30 128
sth 0 30 126
sth 0 30 124
bl 8020ba78 0 1
addi 3 30 56
lfs 1 2 -22352
or 3 4 3 0
bl 8020ba9c 0 1
addi 3 30 32
addi 4 30 56
or 3 5 3 0
bl 8020ba54 0 1
or 30 3 30 0
bl 800677b0 0 1
lha 0 31 0
stb 0 30 1770
lwz 0 30 1504
rlwinm 0 0 0 25 25 1
bc 12 2 0 800ff3cc 0
lha 0 31 2
stb 0 30 1770
lbz 5 30 1770
or 30 3 30 0
lfs 1 2 -22376
addi 4 0 15
addi 0 5 1
extsb 5 6 0
stb 0 30 1770
addi 5 0 4
addi 7 0 -1
addi 8 0 -1
bl 8004beb8 0 1
lfs 0 2 -22380
stfs 0 30 2060
lwz 0 1 20
lwz 31 1 12
lwz 30 1 8
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x8006d144: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 4 31 4 0
stw 30 1 8
or 3 30 3 0
lwz 0 3 204
cmpli 0 0 0 0
bc 12 2 0 8006d174 0
bl 8006660c 0 1
b 8006d184 0 0
lha 3 30 114
lha 0 30 1452
subf 0 3 0 0 0
sth 0 30 1450
or 30 3 30 0
or 31 4 31 0
bl 800669d0 0 1
lwz 0 1 20
lwz 31 1 12
lwz 30 1 8
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x800669d0: ops('''
stwu 1 1 -32
mflr 0
rlwinm 4 5 1 27 30 0
lfd 2 2 -29784
stw 0 1 36
addis 0 0 17200
lwz 6 3 1196
stw 0 1 8
add 5 6 5 0 0
lfs 0 3 7624
lha 0 5 172
xoris 0 0 32768
stw 0 1 12
lfd 1 1 8
fsubs 1 1 2 0
fmuls 0 1 0 0
fctiwz 0 0 0
stfd 0 1 16
lwz 5 1 20
bl 80066a30 0 1
lwz 0 1 36
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
    0x8020ba78: ops('''
psq_l 2 3 0 0 0
psq_l 4 4 0 0 0
ps_sub 6 2 4 0
psq_st 6 5 0 0 0
psq_l 3 3 8 1 0
psq_l 5 4 8 1 0
ps_sub 7 3 5 0
psq_st 7 5 8 1 0
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
    0x8020ba54: ops('''
psq_l 2 3 0 0 0
psq_l 4 4 0 0 0
ps_add 6 2 4 0
psq_st 6 5 0 0 0
psq_l 3 3 8 1 0
psq_l 5 4 8 1 0
ps_add 7 3 5 0
psq_st 7 5 8 1 0
blr 20 0 0 0
'''),
    0x80066a30: ops('''
lha 6 3 1450
lha 8 3 114
extsh 6 0 1
or 6 0 6 0
bc 4 0 0 80066a48 0
neg 0 6 0 0
extsh 5 7 0
cmp 0 0 0 7
bc 4 1 0 80066a94 0
extsh 6 0 1
bc 4 0 0 80066a64 0
neg 0 7 0 0
extsh 0 5 0
lha 6 3 1450
rlwinm 4 0 0 25 25 1
add 8 8 5 0 0
subf 0 5 6 0 0
sth 0 3 1450
bc 12 2 0 80066a80 0
sth 8 3 1454
rlwinm 4 0 0 24 24 1
bc 12 2 0 80066a8c 0
sth 8 3 114
addi 3 0 0
blr 20 0 0 0
addi 5 0 0
rlwinm 4 0 0 25 25 1
sth 5 3 1450
add 8 8 6 0 0
bc 12 2 0 80066aac 0
sth 8 3 1454
rlwinm 4 0 0 24 24 1
bc 12 2 0 80066ab8 0
sth 8 3 114
addi 3 0 1
blr 20 0 0 0
'''),
}

def d_form(op, d, ra, value):
    return (op << 26) | (d << 21) | (ra << 16) | (value & 65535)


def encode(row, pc):
    """Independent inverse encoding of the fixed witness, never calls decoder."""
    n = row['mnemonic']
    dops = {'mulli': 7, 'cmpli':10, 'cmpi': 11, 'ori':24, 'andi.':28, 'lhz':40, 'lha':42, 'sth':44, 'addi': 14, 'addis': 15, 'xori': 26, 'xoris': 27,
            'lwz': 32, 'lbz': 34, 'stw': 36, 'stwu': 37, 'stb': 38, 'lmw': 46,
            'stmw': 47, 'lfs': 48, 'lfd': 50, 'stfs': 52, 'stfd': 54}
    if n in dops:
        d = next((row[k] for k in ('rD', 'rS', 'fD', 'fS') if k in row), 0)
        if n in ('cmpi','cmpli'): d = (row['BF'] << 2) | row['L']
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
    if n in ('lwzx', 'lbzx', 'or', 'add', 'extsb', 'cmp','extsh','neg','subf'):
        d = (row['BF'] << 2 | row['L']) if n == 'cmp' else row.get('rD', row.get('rS'))
        xo = {'lwzx': 23, 'lbzx': 87, 'or': 444, 'add': 266, 'extsb': 954, 'cmp': 0,'extsh':922,'neg':104,'subf':40}[n]
        return 31 << 26 | d << 21 | row['rA'] << 16 | row.get('rB', 0) << 11 | xo << 1 | \
            row.get('OE', 0) << 10 | row.get('Rc', 0)
    if n in ('psq_l', 'psq_st'):
        return (56 if n == 'psq_l' else 60) << 26 | row.get('fD', row.get('fS')) << 21 | \
            row['rA'] << 16 | row['W'] << 15 | row['I'] << 12 | (row['displacement'] & 4095)
    if n in ('fdivs', 'fsubs', 'fadds', 'fmuls', 'ps_muls0','ps_sub','ps_add'):
        op = 4 if n.startswith('ps_') else 59
        xo = {'fdivs': 18, 'fsubs': 20, 'fadds': 21, 'fmuls': 25, 'ps_muls0': 12,'ps_sub':20,'ps_add':21}[n]
        return op << 26 | row['fD'] << 21 | row['fA'] << 16 | row.get('fB', 0) << 11 | \
            row.get('fC', 0) << 6 | xo << 1 | row['Rc']
    if n in ('fneg', 'fmr', 'fcmpo','fctiwz'):
        d = row['BF'] << 2 if n == 'fcmpo' else row['fD']
        return 63 << 26 | d << 21 | row.get('fA', 0) << 16 | row['fB'] << 11 | \
            {'fneg': 40, 'fmr': 72, 'fcmpo': 32,'fctiwz':15}[n] << 1 | row.get('Rc', 0)
    raise AssertionError(n)


PHYSICAL = {'8006f7c0': [{'root_buffer': 21,
               'data_buffer': 48,
               'chain_offset': 434656,
               'data_offset': 8828,
               'length': 204,
               'obfuscated': True,
               'physical_offset': 811650}],
 '8005f238': [{'root_buffer': 21,
               'data_buffer': 44,
               'chain_offset': 367704,
               'data_offset': 7388,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 744674}],
 '80065dfc': [{'root_buffer': 21,
               'data_buffer': 46,
               'chain_offset': 395292,
               'data_offset': 2220,
               'length': 40,
               'obfuscated': True,
               'physical_offset': 772274}],
 '8006facc': [{'root_buffer': 21,
               'data_buffer': 48,
               'chain_offset': 435436,
               'data_offset': 9608,
               'length': 60,
               'obfuscated': True,
               'physical_offset': 812430}],
 '80071598': [{'root_buffer': 21,
               'data_buffer': 49,
               'chain_offset': 442296,
               'data_offset': 90,
               'length': 60,
               'obfuscated': True,
               'physical_offset': 819296}],
 '800715d4': [{'root_buffer': 21,
               'data_buffer': 49,
               'chain_offset': 442356,
               'data_offset': 150,
               'length': 36,
               'obfuscated': True,
               'physical_offset': 819356}],
 '800ff2bc': [{'root_buffer': 21,
               'data_buffer': 84,
               'chain_offset': 1023196,
               'data_offset': 7760,
               'length': 80,
               'obfuscated': True,
               'physical_offset': 1400406}],
 '800ff30c': [{'root_buffer': 21,
               'data_buffer': 84,
               'chain_offset': 1023276,
               'data_offset': 7840,
               'length': 268,
               'obfuscated': True,
               'physical_offset': 1400486}],
 '8006d144': [{'root_buffer': 21,
               'data_buffer': 47,
               'chain_offset': 424804,
               'data_offset': 15354,
               'length': 100,
               'obfuscated': True,
               'physical_offset': 801792}],
 '800669d0': [{'root_buffer': 21,
               'data_buffer': 46,
               'chain_offset': 398320,
               'data_offset': 5248,
               'length': 96,
               'obfuscated': True,
               'physical_offset': 775302}],
 '8020ba78': [{'root_buffer': 21,
               'data_buffer': 151,
               'chain_offset': 2122904,
               'data_offset': 10142,
               'length': 36,
               'obfuscated': True,
               'physical_offset': 2500516}],
 '8020ba9c': [{'root_buffer': 21,
               'data_buffer': 151,
               'chain_offset': 2122940,
               'data_offset': 10178,
               'length': 28,
               'obfuscated': True,
               'physical_offset': 2500552}],
 '8020ba54': [{'root_buffer': 21,
               'data_buffer': 151,
               'chain_offset': 2122868,
               'data_offset': 10106,
               'length': 36,
               'obfuscated': True,
               'physical_offset': 2500480}],
 '80066a30': [{'root_buffer': 21,
               'data_buffer': 46,
               'chain_offset': 398416,
               'data_offset': 5344,
               'length': 144,
               'obfuscated': True,
               'physical_offset': 775398}],
 '802d3b1c': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 101564,
               'data_offset': 3296,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3394790}],
 '802d37a8': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 100680,
               'data_offset': 2412,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3393906}],
 '802d379c': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 100668,
               'data_offset': 2400,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3393894}],
 '802d3b14': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 101556,
               'data_offset': 3288,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3394782}],
 '802d3b70': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 101648,
               'data_offset': 3380,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3394874}],
 '802d3c48': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 101864,
               'data_offset': 3596,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3395090}],
 '8031f000': [{'root_buffer': 199,
               'data_buffer': 225,
               'chain_offset': 410016,
               'data_offset': 566,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3703356}],
 '804376f8': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 3288,
               'data_offset': 3288,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4345054}],
 '804375c8': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 2984,
               'data_offset': 2984,
               'length': 8,
               'obfuscated': True,
               'physical_offset': 4344750}],
 '804392b4': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 10388,
               'data_offset': 10388,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4352154}],
 '804392b8': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 10392,
               'data_offset': 10392,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4352158}],
 '804392d0': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 10416,
               'data_offset': 10416,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4352182}],
 '80433868': [{'root_buffer': 262,
               'data_buffer': 262,
               'chain_offset': 712,
               'data_offset': 712,
               'length': 2,
               'obfuscated': True,
               'physical_offset': 4309714}],
 '8043386a': [{'root_buffer': 262,
               'data_buffer': 262,
               'chain_offset': 714,
               'data_offset': 714,
               'length': 2,
               'obfuscated': True,
               'physical_offset': 4309716}]}

class SyntheticTests(unittest.TestCase):
    def test_all_operands_inverse_encode_exact_hashes(self):
        self.assertEqual(len(a.RANGES),14)
        self.assertEqual(len(a.CELLS),7)
        self.assertEqual(len(a.CONSTANTS),5)
        self.assertEqual(len(a.CONFIG_SCALARS),2)
        for pc,width,digest in a.RANGES:
            rows=EXPECTED[pc]
            self.assertEqual(len(rows),width//4)
            raw=struct.pack('>'+'I'*len(rows),*(encode(row,pc+4*i) for i,row in enumerate(rows)))
            self.assertEqual(hashlib.sha256(raw).hexdigest(),digest)
            db=FakeDB(raw); result=a.range_evidence(db,a.TEXT_MAPPING,pc,width)
            self.assertEqual(result['instructions'],[dict(address=f'{pc+i*4:08x}',**row) for i,row in enumerate(rows)])
            self.assertEqual(db.calls,[(21,pc-0x800055e0,width,2796416)])
            self.assertEqual(result['instructions'][-1]['mnemonic'],'blr')
            for row in rows:self.assertEqual(set(row),{'mnemonic',*FIELDS[row['mnemonic']].split()})

    def test_range_selection_duplicate_and_type_guards(self):
        for pc,width,_ in a.RANGES:
            for args in ((pc+4,width-4),(pc,width+4),(pc,width-4),(pc-4,4),(pc+width,4)):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.range_evidence(None,a.TEXT_MAPPING,*args)
            with patch.object(a,'RANGES',a.RANGES*2):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.range_evidence(None,a.TEXT_MAPPING,pc,width)
        for bad in (True,1.0,'4',None):
            for args in ((bad,204),(0x8006f7c0,bad)):
                with self.assertRaisesRegex(a.c.FormatError,'integer fields'):a.range_evidence(None,a.TEXT_MAPPING,*args)
            for fn,m in ((a.cell_evidence,a.DATA3_MAPPING),(a.constant_evidence,a.DATA5_MAPPING),(a.config_evidence,a.DATA4_MAPPING)):
                with self.assertRaisesRegex(a.c.FormatError,'integer fields'):fn(None,m,bad)

    def test_fixed_mapping_guards_before_reads(self):
        for fn,m,args in ((a.range_evidence,a.TEXT_MAPPING,(0x8006f7c0,204)),
                          (a.cell_evidence,a.DATA3_MAPPING,(0x802d3b1c,)),
                          (a.constant_evidence,a.DATA5_MAPPING,(0x804376f8,)),
                          (a.config_evidence,a.DATA4_MAPPING,(0x80433868,))):
            for bad in (list(m),m[:-1]+(22,),(m[0]+4,)+m[1:],m[:2]+(float(m[2]),)+m[3:]):
                with self.assertRaisesRegex(a.c.FormatError,'mapping'):fn(None,bad,*args)

    def test_width_hash_and_complete_decode_guards(self):
        for pc,width,_ in a.RANGES:
            for raw,reason in ((bytes(width),'digest'),(bytes(width-4),'byte width'),(bytes(width+4),'byte width')):
                with patch.object(a,'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError,reason):a.range_evidence(FakeDB(raw),a.TEXT_MAPPING,pc,width)
                    decoder.assert_not_called()
        for words,reason in (([0],'unselected instruction'),([0x38600000],'terminal return'),
                             ([0x48001000,0x4e800020],'outside fixed span')):
            raw=struct.pack('>'+'I'*len(words),*words)
            with patch.object(a,'RANGES',((0x8006f7c0,len(raw),hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError,reason):a.range_evidence(FakeDB(raw),a.TEXT_MAPPING,0x8006f7c0,len(raw))

    def test_cells_exact_values_digests_no_following(self):
        for label,pc,target,digest in a.CELLS:
            raw=struct.pack('>I',target); db=FakeDB(raw)
            result=a.cell_evidence(db,a.DATA3_MAPPING,pc)
            self.assertEqual(db.calls,[(199,pc-0x802bae60,4,1000128)])
            self.assertEqual((result['target'],result['sha256'],result['label']),(f'{target:08x}',digest,label))
            for bad,reason in ((raw[:3],'byte width'),(raw+bytes(1),'byte width'),(bytes(4),'digest')):
                with self.assertRaisesRegex(a.c.FormatError,reason):a.cell_evidence(FakeDB(bad),a.DATA3_MAPPING,pc)
            wrong=((label,pc,target+4,digest),)
            with patch.object(a,'CELLS',wrong):
                with self.assertRaisesRegex(a.c.FormatError,'target mismatch'):a.cell_evidence(FakeDB(raw),a.DATA3_MAPPING,pc)
        for pc in (0x802d37ac,0x802d3b20,0x802d3c4c,0x8031f004,0x80433868):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.cell_evidence(None,a.DATA3_MAPPING,pc)
        with patch.object(a,'CELLS',a.CELLS*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.cell_evidence(None,a.DATA3_MAPPING,0x802d3b1c)

    def test_scalar_bits_types_and_config_halfwords(self):
        for pc,bits,label in a.CONSTANTS:
            raw=bytes.fromhex(bits);db=FakeDB(raw);result=a.constant_evidence(db,a.DATA5_MAPPING,pc)
            self.assertEqual(db.calls,[(263,pc-0x80436a20,len(raw),27360)])
            self.assertEqual((result['bits'],result['label']),(bits,label))
            self.assertEqual(result['value'],struct.unpack('>f' if len(raw)==4 else '>d',raw)[0])
            for bad,reason in ((raw[:-1],'byte width'),(raw+bytes(1),'byte width'),(bytes([raw[0]^1])+raw[1:],'bits mismatch')):
                with self.assertRaisesRegex(a.c.FormatError,reason):a.constant_evidence(FakeDB(bad),a.DATA5_MAPPING,pc)
        for pc,value,label in a.CONFIG_SCALARS:
            raw=struct.pack('>H',value);db=FakeDB(raw);result=a.config_evidence(db,a.DATA4_MAPPING,pc)
            self.assertEqual(db.calls,[(262,pc-0x804335a0,2,11040)])
            self.assertEqual((result['value'],result['label']),(value,label))
            for bad,reason in ((raw[:1],'byte width'),(raw+bytes(1),'byte width'),(struct.pack('>H',value+1),'value mismatch')):
                with self.assertRaisesRegex(a.c.FormatError,reason):a.config_evidence(FakeDB(bad),a.DATA4_MAPPING,pc)
        for fn,m,attr,pc,bad in ((a.constant_evidence,a.DATA5_MAPPING,'CONSTANTS',0x804376f8,0x804392bc),
                              (a.config_evidence,a.DATA4_MAPPING,'CONFIG_SCALARS',0x80433868,0x8043386c)):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):fn(None,m,bad)
            with patch.object(a,attr,getattr(a,attr)*2):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):fn(None,m,pc)

    def test_authentication_before_parser_and_selections(self):
        for digest in ('0'*64,hashlib.sha256(bytes(32)).hexdigest(),next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c,'GBF') as parser,patch.object(a,'range_evidence') as read:
                with self.assertRaisesRegex(a.c.FormatError,'SHA256 not allowlisted'):a.inspect(bytes(32),digest)
                parser.assert_not_called();read.assert_not_called()
        for reason in ('unsupported schema','language mismatch','File Bytes table is not empty',
                       'data5 digest mismatch','executable metadata SHA/type mismatch'):
            with patch.object(a.c,'inspect',side_effect=a.c.FormatError(reason)),patch.object(a.c,'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError,reason):a.inspect(b'synthetic','synthetic')
                parser.assert_not_called()

    def test_actual_schema_failure_before_reads(self):
        data=b'synthetic schema fixture';digest=hashlib.sha256(data).hexdigest()
        schema=dict(version=0,keytype=4,types=[4],fields='Key;Value;')
        for key,value in (('version',1),('keytype',3),('types',[2]),('fields','Wrong;')):
            changed=dict(schema);changed[key]=value
            with patch.dict(a.c.SNAPSHOTS,{digest:'synthetic'}),patch.object(a.c,'GBF') as parser,patch.object(a,'range_evidence') as read:
                parser.return_value.tables.return_value={'Program':changed}
                with self.assertRaisesRegex(a.c.FormatError,'unsupported schema: Program'):a.inspect(data,digest)
                parser.return_value.rows.assert_not_called();read.assert_not_called()

    def test_actual_mapping_failure_before_reads(self):
        blocks={key:[name,None,None,0,encoded,length,0] for name,key,encoded,length,root in a.command.MAPPINGS}
        subs={key:[key,2,length,0,root,0] for name,key,encoded,length,root in a.command.MAPPINGS}
        blocks[6]=['MAIN_.data4',None,None,6,0x20000000004335a0,11040,0];subs[6]=[6,2,11040,0,262,0]
        for target in ('text-root','text-offset','data3-root','data5-root','data4-root','data4-offset','data4-type','data4-length','data4-duplicate','data4-duplicate-sub','image','overlap'):
            aa,bb,ss=copy.deepcopy(({'image_offset':'80000000'},blocks,subs))
            if target=='text-root':ss[1][4]+=1
            if target=='text-offset':ss[1][5]+=1
            if target=='data3-root':ss[5][4]+=1
            if target=='data5-root':ss[7][4]+=1
            if target=='data4-root':ss[6][4]+=1
            if target=='data4-offset':ss[6][5]+=1
            if target=='data4-type':ss[6][1]+=1
            if target=='data4-length':bb[6][5]-=2
            if target=='data4-duplicate':bb[99]=copy.deepcopy(bb[6])
            if target=='data4-duplicate-sub':ss[99]=copy.deepcopy(ss[6])
            if target=='image':aa['image_offset']='80000004'
            if target=='overlap':bb[99]=['other',None,None,0,0x2000000000433868,4,0]
            with patch.object(a.c,'inspect',return_value=aa),patch.object(a.c,'GBF') as parser, \
                    patch.object(a,'range_evidence') as ranges,patch.object(a,'cell_evidence') as cells, \
                    patch.object(a,'constant_evidence') as constants,patch.object(a,'config_evidence') as config:
                db=parser.return_value;db.tables.return_value={'Memory Blocks':'b','Sub Memory Blocks':'s'}
                db.rows.side_effect=lambda key:{'b':bb,'s':ss}[key]
                with self.assertRaises(a.c.FormatError):a.inspect(b'synthetic','synthetic')
                ranges.assert_not_called();cells.assert_not_called();constants.assert_not_called();config.assert_not_called()

    def test_decoder_added_forms_and_reserved_fields(self):
        for n,op in (('lhz',40),('lha',42),('sth',44)):
            for value in (-32768,-1,0,32767):
                row=dict(mnemonic=n,**{'rS' if n=='sth' else 'rD':7},rA=5,displacement=value)
                self.assertEqual(a.decode_selected(encode(row,0),0),row)
        for n in ('ps_sub','ps_add'):
            row=dict(mnemonic=n,fD=7,fA=5,fB=3,Rc=0);word=encode(row,0)
            self.assertEqual(a.decode_selected(word,0),row)
            for bad in (word|1,word|64):
                with self.assertRaises(a.c.FormatError):a.decode_selected(bad,0)
        for row in (dict(mnemonic='extsh',rS=7,rA=5,Rc=1),dict(mnemonic='neg',rD=7,rA=5,OE=0,Rc=1),
                    dict(mnemonic='subf',rD=7,rA=5,rB=3,OE=0,Rc=1),dict(mnemonic='fctiwz',fD=7,fB=5,Rc=0)):
            self.assertEqual(a.decode_selected(encode(row,0),0),row)
        for word in (31<<26|922<<1|1<<11,31<<26|104<<1|1<<11,63<<26|15<<1|1,63<<26|15<<1|1<<16,10<<26|1<<21):
            with self.assertRaises(a.c.FormatError):a.decode_selected(word,0)
        for word in (0,31<<26|104<<1|1<<10,31<<26|40<<1|1<<10):self.assertIsNone(a.decode_selected(word,0))
        for bad in (True,-1,1<<32,1.0):
            with self.assertRaises(a.c.FormatError):a.decode_selected(bad,0)
        for bad in (True,-4,1<<32,2,1.0):
            with self.assertRaises(a.c.FormatError):a.decode_selected(0,bad)

    def test_source_boundaries_real_maps_and_separate_posthook(self):
        root=Path(__file__).resolve().parents[3]
        text=(root/'research/symbols/GG4E-CSM-20220412.map').read_text()
        maps={int(pc,16):int(width,16) for pc,width in re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ',text,re.M)}
        chunks={0x8006f7c0:'0009',0x8005f238:'0007',0x80065dfc:'0008',0x8006facc:'0009',0x80071598:'0009',0x800715d4:'0009',
                0x800ff2bc:'0028',0x800ff30c:'0028',0x8006d144:'0009',0x800669d0:'0008',0x80066a30:'0008',
                0x8020ba78:'0064',0x8020ba9c:'0064',0x8020ba54:'0064'}
        for pc,width,_ in a.RANGES:
            src=(root/f'research/decomp/ghidra-export/chunk_{chunks[pc]}.c').read_text()
            markers=[int(v,16) for v in re.findall(r'^// ==== ([0-9a-f]{8}) ',src,re.M)]
            if pc==0x8006f7c0:
                self.assertEqual(markers[markers.index(pc)+1],0x8006f8d4)
                self.assertEqual(pc+width,0x8006f88c)
                self.assertNotIn(0x8006f88c,markers)
            elif pc==0x8005f238:
                self.assertNotIn(pc,markers);self.assertIn(pc+width,markers)
                self.assertEqual(0x8005f188+maps[0x8005f188],pc)
            else:self.assertEqual(markers[markers.index(pc)+1],pc+width)
            if pc in a.MAP_SIZES:self.assertEqual(maps[pc],width)
            else:self.assertNotIn(pc,maps)

    def test_existing_envelope_captures(self):
        import test_archived_actor_mode1_evidence as envelope
        pc=0x80055568;by={pc+i*4:row for i,row in enumerate(envelope.EXPECTED[pc])}
        self.assertEqual(by[0x800555c4],dict(mnemonic='lbz',rD=0,rA=31,displacement=0x5db))
        self.assertEqual(by[0x800555cc],dict(mnemonic='lbz',rD=30,rA=31,displacement=0x5da))

    def test_ordered_prehook_and_phase0(self):
        def at(pc):return {pc+i*4:row for i,row in enumerate(EXPECTED[pc])}
        p=at(0x8006f7c0)
        self.assertEqual([pc for pc,row in p.items() if row.get('rA')==31 and row.get('displacement')==0x5e0],[0x8006f7f4,0x8006f80c])
        self.assertEqual(p[0x8006f818]['mnemonic'],'lha')
        self.assertEqual(p[0x8006f804],dict(mnemonic='sth',rS=0,rA=31,displacement=0x1dfc))
        self.assertEqual(p[0x8006f808],dict(mnemonic='stb',rS=0,rA=31,displacement=0x6ee))
        q=at(0x800ff30c)
        self.assertEqual([row['displacement'] for pc,row in q.items() if 0x800ff364<=pc<=0x800ff380 and row['mnemonic'] in ('stfs','sth')],
                         [0x50,0x48,0x4c,0x44,0x80,0x7e,0x7c])
        self.assertEqual([row['target'] for row in q.values() if row['mnemonic']=='bl'],
                         ['8006d144','8020ba78','8020ba9c','8020ba54','800677b0','8004beb8'])
        self.assertEqual(q[0x800ff3b0],dict(mnemonic='lha',rD=0,rA=31,displacement=0))
        self.assertEqual(q[0x800ff3c4],dict(mnemonic='lha',rD=0,rA=31,displacement=2))

    def test_turn_helpers_capture_and_return_order(self):
        q={0x800669d0+i*4:r for i,r in enumerate(EXPECTED[0x800669d0])}
        self.assertEqual(q[0x800669f4],dict(mnemonic='lfs',fD=0,rA=3,displacement=0x1dc8))
        self.assertEqual(q[0x800669f8],dict(mnemonic='lha',rD=0,rA=5,displacement=0xac))
        self.assertEqual(q[0x80066a0c],dict(mnemonic='fmuls',fD=0,fA=1,fC=0,Rc=0))
        self.assertEqual(q[0x80066a10],dict(mnemonic='fctiwz',fD=0,fB=0,Rc=0))
        q={0x80066a30+i*4:r for i,r in enumerate(EXPECTED[0x80066a30])}
        self.assertEqual(q[0x80066a34],dict(mnemonic='lha',rD=8,rA=3,displacement=0x72))
        self.assertEqual(q[0x80066a64],dict(mnemonic='lha',rD=6,rA=3,displacement=0x5aa))
        self.assertEqual([p for p,r in q.items() if r['mnemonic']=='blr'],[0x80066a90,0x80066abc])

    def test_vector_pair_store_and_z_load_order(self):
        for pc,op in ((0x8020ba78,'ps_sub'),(0x8020ba54,'ps_add')):
            rows=EXPECTED[pc]
            self.assertEqual([r['mnemonic'] for r in rows],['psq_l','psq_l',op,'psq_st','psq_l','psq_l',op,'psq_st','blr'])
            self.assertEqual([r['W'] for r in rows if r['mnemonic'].startswith('psq_')],[0,0,0,1,1,1])
        rows=EXPECTED[0x8020ba9c]
        self.assertEqual([r['mnemonic'] for r in rows],['psq_l','psq_l','ps_muls0','psq_st','ps_muls0','psq_st','blr'])
        self.assertTrue(all(r['I']==0 for rows in (EXPECTED[x] for x in (0x8020ba78,0x8020ba9c,0x8020ba54)) for r in rows if 'I' in r))

    def test_no_arbitrary_cli_or_shared_allowlist_widening(self):
        for pc,width,_ in a.RANGES:self.assertNotIn((pc,width),a.c.TARGETS)
        self.assertNotIn((0x8006f7c0,204),[x[:2] for x in a.normal.RANGES])
        for args in (['--address','8006f7c0'],['--width','204'],['--target','800ff30c'],['--raw'],['--execute'],['--follow']):
            with patch.object(a.sys,'argv',['reader','fixture.gbf']+args),contextlib.redirect_stderr(io.StringIO()),patch.object(a,'inspect') as inspect:
                with self.assertRaises(SystemExit) as ex:a.main()
                self.assertEqual(ex.exception.code,2);inspect.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base=Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR',str(default)))
        paths=[base/f'db.{n}.gbf' for n in (3,4)]
        if not all(p.is_file() for p in paths):raise unittest.SkipTest('local archives unavailable; never fetched')
        cls.results=[]
        for p in paths:
            a.c.require(32<=p.stat().st_size<=a.c.MAX_FILE,'snapshot size bounds')
            with p.open('rb') as stream:data=stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data)<=a.c.MAX_FILE,'snapshot size bounds')
            cls.results.append(a.inspect(data,hashlib.sha256(data).hexdigest()))

    def test_full_operands_both_snapshots(self):
        for result in self.results:
            for span,(pc,width,digest) in zip(result['ranges'],a.RANGES):
                self.assertEqual(span['instructions'],[dict(address=f'{pc+i*4:08x}',**row) for i,row in enumerate(EXPECTED[pc])])
                self.assertEqual((span['width'],span['sha256'],span['end_exclusive']),(width,digest,f'{pc+width:08x}'))
            self.assertEqual(sum(c['represented_instructions'] for c in result['function_coverage']),298)
            for cov in result['function_coverage']:
                self.assertEqual((cov['unrepresented_instructions'],cov['unrepresented_ranges']),(0,[]))
                self.assertEqual(cov['map_size'],a.MAP_SIZES.get(int(cov['entry'],16)))

    def test_identical_results_and_exact_physical_spans(self):
        self.assertEqual([r['snapshot'] for r in self.results],['db.3.gbf','db.4.gbf'])
        for key in ('ranges','cells','constants','config_scalars','mappings','function_coverage','recorded_bases','float_preconditions'):
            self.assertEqual(self.results[0][key],self.results[1][key])
        for result in self.results:
            for key in ('ranges','cells','constants','config_scalars'):
                for item in result[key]:self.assertEqual(item['spans'],PHYSICAL[item['address']])
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            self.assertEqual(result['data5_sha256'],a.c.DATA5_SHA)
            self.assertEqual(result['executable_sha256_property_type'],2)

    def test_literal_selections_only(self):
        for result in self.results:
            self.assertEqual([r['address'] for r in result['ranges']],[f'{pc:08x}' for pc,_,_ in a.RANGES])
            self.assertEqual([r['address'] for r in result['cells']],[f'{pc:08x}' for _,pc,_,_ in a.CELLS])
            self.assertEqual([(r['address'],r['width']) for r in result['config_scalars']],[('80433868',2),('8043386a',2)])
            self.assertNotIn('raw',json.dumps(result))


if __name__=='__main__':unittest.main()
