#!/usr/bin/env python3
"""Independent operand fixture and inverse for 380 instructions / 1520 bytes.

Expected operands are hand-written below; no fixture/report generation at test
runtime, no original-code execution, no estimator/runtime imports. Existing
local snapshots are optional and are never fetched.
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

import read_archived_target_preparation_evidence as a

ENTRY, WIDTH = 0x8006ae60, 1520
DIGEST = '6b725b93ac0755d146b4a67fe61ec81127d98afccc77ca5c3fcd990fa199b50a'
TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
EXPECTED_READS = [(21, 415872, 1520, 2796416)]
# Explicit operand convention is defined independently in parse_fixture below.
# Addresses are an independent coverage control, not inferred branch targets.
ASSEMBLY = '''
8006ae60 stwu 1 1 -48
8006ae64 mflr 0
8006ae68 addis 3 0 -32708
8006ae6c stw 0 1 52
8006ae70 addi 0 0 0
8006ae74 stmw 27 1 28
8006ae78 lwz 4 3 20100
8006ae7c lbz 3 4 0
8006ae80 extsb 3 3 1
8006ae84 bc 12 2 8006aea0
8006ae88 stb 0 4 1418
8006ae8c stb 0 4 1419
8006ae90 stb 0 4 1420
8006ae94 stb 0 4 1421
8006ae98 stb 0 4 2002
8006ae9c stb 0 4 2003
8006aea0 lbz 3 4 7680
8006aea4 extsb 3 3 1
8006aea8 bc 12 2 8006aec4
8006aeac stb 0 4 9098
8006aeb0 stb 0 4 9099
8006aeb4 stb 0 4 9100
8006aeb8 stb 0 4 9101
8006aebc stb 0 4 9682
8006aec0 stb 0 4 9683
8006aec4 lbz 3 4 15360
8006aec8 extsb 3 3 1
8006aecc bc 12 2 8006aee8
8006aed0 stb 0 4 16778
8006aed4 stb 0 4 16779
8006aed8 stb 0 4 16780
8006aedc stb 0 4 16781
8006aee0 stb 0 4 17362
8006aee4 stb 0 4 17363
8006aee8 lbz 3 4 23040
8006aeec extsb 3 3 1
8006aef0 bc 12 2 8006af0c
8006aef4 stb 0 4 24458
8006aef8 stb 0 4 24459
8006aefc stb 0 4 24460
8006af00 stb 0 4 24461
8006af04 stb 0 4 25042
8006af08 stb 0 4 25043
8006af0c lbzu 3 4 30720
8006af10 extsb 3 3 1
8006af14 bc 12 2 8006af30
8006af18 stb 0 4 1418
8006af1c stb 0 4 1419
8006af20 stb 0 4 1420
8006af24 stb 0 4 1421
8006af28 stb 0 4 2002
8006af2c stb 0 4 2003
8006af30 lbz 3 4 7680
8006af34 extsb 3 3 1
8006af38 bc 12 2 8006af54
8006af3c stb 0 4 9098
8006af40 stb 0 4 9099
8006af44 stb 0 4 9100
8006af48 stb 0 4 9101
8006af4c stb 0 4 9682
8006af50 stb 0 4 9683
8006af54 addis 3 0 -32708
8006af58 addi 31 0 0
8006af5c lwz 30 3 20100
8006af60 lbz 0 30 0
8006af64 extsb 0 0 1
8006af68 bc 12 2 8006b33c
8006af6c lbz 0 30 24
8006af70 extsb 0 0 0
8006af74 cmpi 0 1
8006af78 bc 12 0 8006b33c
8006af7c or 30 3 30 0
8006af80 bl 8006b450
8006af84 or 30 3 30 0
8006af88 bl 8006b7f4
8006af8c lwz 29 30 1288
8006af90 cmpli 29 0
8006af94 bc 12 2 8006b180
8006af98 lwz 4 30 1284
8006af9c addi 28 30 32
8006afa0 or 28 3 28 0
8006afa4 addi 27 4 100
8006afa8 or 27 4 27 0
8006afac bl 8020bc88
8006afb0 lfs 0 2 -29640
8006afb4 fcmpo 1 0
8006afb8 bc 4 1 8006b008
8006afbc frsqrte 2 1
8006afc0 lfd 4 2 -29632
8006afc4 lfd 3 2 -29624
8006afc8 fmul 0 2 2
8006afcc fmul 2 4 2
8006afd0 fnmsub 0 1 0 3
8006afd4 fmul 2 2 0
8006afd8 fmul 0 2 2
8006afdc fmul 2 4 2
8006afe0 fnmsub 0 1 0 3
8006afe4 fmul 2 2 0
8006afe8 fmul 0 2 2
8006afec fmul 2 4 2
8006aff0 fnmsub 0 1 0 3
8006aff4 fmul 0 2 0
8006aff8 fmul 0 1 0
8006affc frsp 0 0
8006b000 stfs 0 1 20
8006b004 lfs 1 1 20
8006b008 stfs 1 30 1880
8006b00c lfs 0 2 -29640
8006b010 lfs 4 28 0
8006b014 lfs 3 27 0
8006b018 lfs 2 28 8
8006b01c lfs 1 27 8
8006b020 fsubs 3 4 3
8006b024 fsubs 1 2 1
8006b028 fmuls 2 3 3
8006b02c fmuls 1 1 1
8006b030 fadds 4 2 1
8006b034 fcmpo 4 0
8006b038 bc 4 1 8006b088
8006b03c frsqrte 1 4
8006b040 lfd 3 2 -29632
8006b044 lfd 2 2 -29624
8006b048 fmul 0 1 1
8006b04c fmul 1 3 1
8006b050 fnmsub 0 4 0 2
8006b054 fmul 1 1 0
8006b058 fmul 0 1 1
8006b05c fmul 1 3 1
8006b060 fnmsub 0 4 0 2
8006b064 fmul 1 1 0
8006b068 fmul 0 1 1
8006b06c fmul 1 3 1
8006b070 fnmsub 0 4 0 2
8006b074 fmul 0 1 0
8006b078 fmul 0 4 0
8006b07c frsp 0 0
8006b080 stfs 0 1 16
8006b084 lfs 4 1 16
8006b088 stfs 4 30 1884
8006b08c or 30 3 30 0
8006b090 addi 5 0 0
8006b094 lwz 4 30 1288
8006b098 bl 8006d228
8006b09c lbz 0 30 2002
8006b0a0 ori 0 0 1
8006b0a4 stb 0 30 2002
8006b0a8 lbz 3 30 136
8006b0ac lbz 0 29 136
8006b0b0 extsb 3 3 0
8006b0b4 extsb 0 0 0
8006b0b8 cmp 3 0
8006b0bc bc 12 2 8006b0d4
8006b0c0 lbz 0 30 2002
8006b0c4 addi 3 0 0
8006b0c8 ori 0 0 2
8006b0cc stb 0 30 2002
8006b0d0 b 8006b0d8
8006b0d4 addi 3 0 1
8006b0d8 rlwinm 3 3 2 0 29 0
8006b0dc lfs 0 30 1880
8006b0e0 addi 0 3 2068
8006b0e4 lfsx 1 30 0
8006b0e8 fcmpo 1 0
8006b0ec cror 2 1 2
8006b0f0 bc 4 2 8006b100
8006b0f4 lbz 0 30 2002
8006b0f8 ori 0 0 4
8006b0fc stb 0 30 2002
8006b100 lwz 3 30 1504
8006b104 rlwinm 3 0 0 24 24 1
8006b108 bc 12 2 8006b114
8006b10c addi 0 0 2
8006b110 b 8006b128
8006b114 rlwinm 3 0 0 25 25 1
8006b118 bc 12 2 8006b124
8006b11c addi 0 0 1
8006b120 b 8006b128
8006b124 addi 0 0 0
8006b128 lfs 0 30 180
8006b12c rlwinm 0 3 2 0 29 0
8006b130 lfs 2 2 -29616
8006b134 addi 0 3 2104
8006b138 lfsx 3 30 0
8006b13c fcmpo 0 2
8006b140 bc 4 0 8006b14c
8006b144 fmuls 3 3 0
8006b148 b 8006b160
8006b14c bc 4 1 8006b160
8006b150 fsubs 0 0 2
8006b154 lfs 1 2 -29612
8006b158 fmadds 0 1 0 2
8006b15c fmuls 3 3 0
8006b160 lfs 0 30 1880
8006b164 fcmpo 3 0
8006b168 cror 2 1 2
8006b16c bc 4 2 8006b1d0
8006b170 lbz 0 30 2002
8006b174 ori 0 0 8
8006b178 stb 0 30 2002
8006b17c b 8006b1d0
8006b180 lfs 0 2 -29608
8006b184 stfs 0 30 1884
8006b188 stfs 0 30 1880
8006b18c lha 3 30 114
8006b190 bl 80045204
8006b194 lfs 0 30 1884
8006b198 fmuls 0 0 1
8006b19c stfs 0 30 1292
8006b1a0 lwz 3 30 1200
8006b1a4 lbz 0 3 16
8006b1a8 extsb 0 0 0
8006b1ac mulli 3 0 48
8006b1b0 addi 0 3 2288
8006b1b4 lfsx 0 30 0
8006b1b8 stfs 0 30 1296
8006b1bc lha 3 30 114
8006b1c0 bl 80045238
8006b1c4 lfs 0 30 1884
8006b1c8 fmuls 0 0 1
8006b1cc stfs 0 30 1300
8006b1d0 lwz 0 30 204
8006b1d4 cmpli 0 0
8006b1d8 bc 12 2 8006b2ec
8006b1dc lwz 4 30 200
8006b1e0 addi 27 30 32
8006b1e4 or 27 3 27 0
8006b1e8 addi 28 4 100
8006b1ec lwz 5 4 100
8006b1f0 or 28 4 28 0
8006b1f4 lwz 0 28 4
8006b1f8 stw 5 30 1304
8006b1fc stw 0 30 1308
8006b200 lwz 0 28 8
8006b204 stw 0 30 1312
8006b208 bl 8020bc88
8006b20c lfs 0 2 -29640
8006b210 fcmpo 1 0
8006b214 bc 4 1 8006b264
8006b218 frsqrte 2 1
8006b21c lfd 4 2 -29632
8006b220 lfd 3 2 -29624
8006b224 fmul 0 2 2
8006b228 fmul 2 4 2
8006b22c fnmsub 0 1 0 3
8006b230 fmul 2 2 0
8006b234 fmul 0 2 2
8006b238 fmul 2 4 2
8006b23c fnmsub 0 1 0 3
8006b240 fmul 2 2 0
8006b244 fmul 0 2 2
8006b248 fmul 2 4 2
8006b24c fnmsub 0 1 0 3
8006b250 fmul 0 2 0
8006b254 fmul 0 1 0
8006b258 frsp 0 0
8006b25c stfs 0 1 12
8006b260 lfs 1 1 12
8006b264 stfs 1 30 1888
8006b268 lfs 0 2 -29640
8006b26c lfs 4 27 0
8006b270 lfs 3 28 0
8006b274 lfs 2 27 8
8006b278 lfs 1 28 8
8006b27c fsubs 3 4 3
8006b280 fsubs 1 2 1
8006b284 fmuls 2 3 3
8006b288 fmuls 1 1 1
8006b28c fadds 4 2 1
8006b290 fcmpo 4 0
8006b294 bc 4 1 8006b2e4
8006b298 frsqrte 1 4
8006b29c lfd 3 2 -29632
8006b2a0 lfd 2 2 -29624
8006b2a4 fmul 0 1 1
8006b2a8 fmul 1 3 1
8006b2ac fnmsub 0 4 0 2
8006b2b0 fmul 1 1 0
8006b2b4 fmul 0 1 1
8006b2b8 fmul 1 3 1
8006b2bc fnmsub 0 4 0 2
8006b2c0 fmul 1 1 0
8006b2c4 fmul 0 1 1
8006b2c8 fmul 1 3 1
8006b2cc fnmsub 0 4 0 2
8006b2d0 fmul 0 1 0
8006b2d4 fmul 0 4 0
8006b2d8 frsp 0 0
8006b2dc stfs 0 1 8
8006b2e0 lfs 4 1 8
8006b2e4 stfs 4 30 1892
8006b2e8 b 8006b33c
8006b2ec lfs 0 2 -29608
8006b2f0 stfs 0 30 1892
8006b2f4 stfs 0 30 1888
8006b2f8 lha 3 30 114
8006b2fc bl 80045204
8006b300 lfs 0 30 1892
8006b304 fmuls 0 0 1
8006b308 stfs 0 30 1304
8006b30c lwz 3 30 1200
8006b310 lbz 0 3 16
8006b314 extsb 0 0 0
8006b318 mulli 3 0 48
8006b31c addi 0 3 2288
8006b320 lfsx 0 30 0
8006b324 stfs 0 30 1308
8006b328 lha 3 30 114
8006b32c bl 80045238
8006b330 lfs 0 30 1892
8006b334 fmuls 0 0 1
8006b338 stfs 0 30 1312
8006b33c addi 31 31 1
8006b340 addi 30 30 7680
8006b344 cmpi 31 6
8006b348 bc 12 0 8006af60
8006b34c addis 4 0 -32708
8006b350 addi 3 0 0
8006b354 addi 4 4 20100
8006b358 lwz 4 4 0
8006b35c lbz 0 4 0
8006b360 lwz 5 4 1288
8006b364 extsb 0 0 1
8006b368 bc 12 2 8006b42c
8006b36c cmpli 5 0
8006b370 bc 12 2 8006b42c
8006b374 lbz 0 5 131
8006b378 extsb 0 0 1
8006b37c bc 4 2 8006b42c
8006b380 lbz 0 4 2003
8006b384 rlwinm 0 0 0 31 31 1
8006b388 bc 4 2 8006b42c
8006b38c lbz 0 5 136
8006b390 lbz 6 4 136
8006b394 extsb 0 0 0
8006b398 extsb 6 8 0
8006b39c cmp 0 8
8006b3a0 bc 12 2 8006b42c
8006b3a4 lfs 1 4 1884
8006b3a8 lfs 0 4 2068
8006b3ac fcmpo 1 0
8006b3b0 bc 12 1 8006b42c
8006b3b4 addis 6 0 -32708
8006b3b8 addi 0 0 6
8006b3bc lwz 9 6 20100
8006b3c0 addi 10 0 0
8006b3c4 addi 6 0 1
8006b3c8 mtctr 0
8006b3cc cmp 10 3
8006b3d0 bc 12 2 8006b420
8006b3d4 lbz 7 5 1418
8006b3d8 slw 6 0 10 0
8006b3dc extsb 7 7 0
8006b3e0 and 7 0 0 1
8006b3e4 bc 12 2 8006b420
8006b3e8 lbz 0 9 136
8006b3ec extsb 0 0 0
8006b3f0 cmp 0 8
8006b3f4 bc 4 2 8006b420
8006b3f8 lbz 0 4 2003
8006b3fc ori 0 0 1
8006b400 stb 0 4 2003
8006b404 lbz 0 9 2003
8006b408 ori 0 0 1
8006b40c stb 0 9 2003
8006b410 lbz 0 5 2003
8006b414 ori 0 0 2
8006b418 stb 0 5 2003
8006b41c b 8006b42c
8006b420 addi 10 10 1
8006b424 addi 9 9 7680
8006b428 bc 16 0 8006b3cc
8006b42c addi 3 3 1
8006b430 addi 4 4 7680
8006b434 cmpi 3 6
8006b438 bc 12 0 8006b35c
8006b43c lmw 27 1 28
8006b440 lwz 0 1 52
8006b444 mtlr 0
8006b448 addi 1 1 48
8006b44c blr 20 0 0 0
'''


D_FORMS = {
    'lwz': (32, 'rD'), 'lbz': (34, 'rD'), 'lbzu': (35, 'rD'),
    'stw': (36, 'rS'), 'stwu': (37, 'rS'), 'stb': (38, 'rS'),
    'lha': (42, 'rD'), 'lmw': (46, 'rD'), 'stmw': (47, 'rS'),
    'lfs': (48, 'fD'), 'lfd': (50, 'fD'), 'stfs': (52, 'fS'),
}


def parse_fixture():
    result = []
    for line in ASSEMBLY.strip().splitlines():
        pc, name, *args = line.split()
        values = [int(arg) for arg in args] if name not in ('bc', 'b', 'bl') else []
        fields = {
            'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS',
            'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'mulli': 'rD rA immediate',
            'ori': 'rS rA immediate', 'extsb': 'rS rA Rc',
            'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc', 'slw': 'rS rA rB Rc',
            'rlwinm': 'rS rA SH MB ME Rc', 'cmp': 'rA rB', 'cmpi': 'rA immediate',
            'cmpli': 'rA immediate', 'frsqrte': 'fD fB', 'frsp': 'fD fB',
            'fmul': 'fD fA fC', 'fmuls': 'fD fA fC', 'fnmsub': 'fD fA fC fB',
            'fmadds': 'fD fA fC fB', 'fsubs': 'fD fA fB', 'fadds': 'fD fA fB',
            'fcmpo': 'fA fB', 'cror': 'crD crA crB', 'lfsx': 'fD rA rB',
            'blr': 'BO BI BH LK',
        }
        if name in D_FORMS: fields[name] = D_FORMS[name][1] + ' rA displacement'
        row = dict(mnemonic=name)
        if name == 'bc': row.update(BO=int(args[0]), BI=int(args[1]), target=args[2], AA=0, LK=0)
        elif name in ('b', 'bl'): row.update(target=args[0], AA=0, LK=int(name == 'bl'))
        else:
            keys = fields[name].split()
            assert len(keys) == len(values), line
            row.update(zip(keys, values))
        if name in ('cmp', 'cmpi', 'cmpli'): row.update(BF=0, L=0)
        if name == 'fcmpo': row.update(BF=0)
        result.append(dict(address=pc, **row))
    return result


EXPECTED = parse_fixture()


def encode(row, pc):
    """Independent PPC bit placement, never calling the reader's decoder."""
    name = row['mnemonic']
    if name in D_FORMS:
        op, reg = D_FORMS[name]
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['displacement'] & 65535
    if name in ('addi', 'addis', 'mulli', 'ori'):
        op, reg = {'addi': (14, 'rD'), 'addis': (15, 'rD'), 'mulli': (7, 'rD'), 'ori': (24, 'rS')}[name]
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name in ('cmpi', 'cmpli'):
        return (11 if name == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name == 'cmp':
        return 31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['rB'] << 11
    if name == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    if name == 'extsb': return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | 954 << 1 | row['Rc']
    if name in ('or', 'and', 'slw'):
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['rB'] << 11 | {'or': 444, 'and': 28, 'slw': 24}[name] << 1 | row['Rc']
    if name in ('mflr', 'mtlr', 'mtctr'):
        reg, spr, xo = ('rD', 8, 339) if name == 'mflr' else ('rS', 8 if name == 'mtlr' else 9, 467)
        return 31 << 26 | row[reg] << 21 | (spr & 31) << 16 | (spr >> 5) << 11 | xo << 1
    if name == 'bc': return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | (int(row['target'], 16) - pc) & 65532 | row['AA'] << 1 | row['LK']
    if name in ('b', 'bl'): return 18 << 26 | (int(row['target'], 16) - pc) & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name == 'blr': return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    if name == 'cror': return 19 << 26 | row['crD'] << 21 | row['crA'] << 16 | row['crB'] << 11 | 449 << 1
    if name == 'lfsx': return 31 << 26 | row['fD'] << 21 | row['rA'] << 16 | row['rB'] << 11 | 535 << 1
    if name == 'fcmpo': return 63 << 26 | row['BF'] << 23 | row['fA'] << 16 | row['fB'] << 11 | 32 << 1
    if name in ('frsqrte', 'frsp'): return 63 << 26 | row['fD'] << 21 | row['fB'] << 11 | (26 if name == 'frsqrte' else 12) << 1
    if name in ('fmul', 'fmuls'): return (63 if name == 'fmul' else 59) << 26 | row['fD'] << 21 | row['fA'] << 16 | row['fC'] << 6 | 25 << 1
    if name in ('fsubs', 'fadds'): return 59 << 26 | row['fD'] << 21 | row['fA'] << 16 | row['fB'] << 11 | (20 if name == 'fsubs' else 21) << 1
    if name in ('fmadds', 'fnmsub'): return (59 if name == 'fmadds' else 63) << 26 | row['fD'] << 21 | row['fA'] << 16 | row['fB'] << 11 | row['fC'] << 6 | (29 if name == 'fmadds' else 30) << 1
    raise AssertionError(name)


BODY = b''.join(struct.pack('>I', encode(row, int(row['address'], 16))) for row in EXPECTED)


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_independent_source_index_map_extent(self):
        self.assertEqual(a.RANGES, ((ENTRY, WIDTH, DIGEST),))
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual([row['address'] for row in EXPECTED], [f'{pc:08x}' for pc in range(ENTRY, ENTRY+WIDTH, 4)])
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        self.assertEqual(index[1390:1392], ['8006ae60\tzz_006ae60_\tchunk_0009.c', '8006b450\tzz_006b450_\tchunk_0009.c'])
        source = (root / 'research/decomp/ghidra-export/chunk_0009.c').read_text().splitlines()[1222:1437]
        self.assertEqual(source[0], '// ==== 8006ae60  zz_006ae60_ ====')
        self.assertEqual(source[-1], '}')
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text().splitlines()
        self.assertEqual(symbols[833], '8006ae60 000005f0 8006ae60 0 zz_006ae60_')

    def test_all380_operands_independent_inverse_and12160_bit_controls(self):
        self.assertEqual(len(BODY), WIDTH)
        self.assertEqual(hashlib.sha256(BODY).hexdigest(), DIGEST)
        self.assertEqual(a.range_evidence(FakeDB(BODY), TEXT_MAPPING, ENTRY, WIDTH)['instructions'], EXPECTED)
        mutations = 0
        for original in EXPECTED:
            pc = int(original['address'], 16)
            row = {k: v for k, v in original.items() if k != 'address'}
            word = encode(row, pc)
            self.assertEqual(a.decode_selected(word, pc), row)
            for bit in range(32):
                mutations += 1
                changed = word ^ 1 << bit
                try: decoded = a.decode_selected(changed, pc)
                except a.c.FormatError: continue
                if decoded is not None:
                    self.assertNotEqual(decoded, row, (hex(pc), bit))
                    self.assertEqual(encode(decoded, pc), changed, (hex(pc), bit))
        self.assertEqual(mutations, 12160)

    def test_exact_single_read_and12160_payload_bit_refusals_before_decode(self):
        db = FakeDB(BODY)
        a.range_evidence(db, TEXT_MAPPING, ENTRY, WIDTH)
        self.assertEqual(db.calls, EXPECTED_READS)
        mutations = 0
        with patch.object(a, 'decode_selected') as decoder:
            for i in range(WIDTH):
                for bit in range(8):
                    changed = BODY[:i] + bytes([BODY[i] ^ 1 << bit]) + BODY[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(changed), TEXT_MAPPING, ENTRY, WIDTH)
                    mutations += 1
            decoder.assert_not_called()
        self.assertEqual(mutations, 12160)

    def test_complete_flow_and_every_flow_operand_tamper_refused(self):
        flow = [row for row in EXPECTED if row['mnemonic'] in ('bc', 'b', 'bl', 'blr')]
        self.assertEqual(len(flow), 50)
        self.assertEqual(a.expected_flow(), flow)
        self.assertEqual([(row['address'], row['target']) for row in flow if row['mnemonic'] == 'bl'], [
            ('8006af80', '8006b450'), ('8006af88', '8006b7f4'), ('8006afac', '8020bc88'),
            ('8006b098', '8006d228'), ('8006b190', '80045204'), ('8006b1c0', '80045238'),
            ('8006b208', '8020bc88'), ('8006b2fc', '80045204'), ('8006b32c', '80045238')])
        self.assertTrue(all(ENTRY <= int(row['target'], 16) < ENTRY + WIDTH
                            for row in flow if row['mnemonic'] in ('bc', 'b')))
        original = a.decode_selected
        mutations = 0
        for row in flow:
            pc = int(row['address'], 16)
            for field, value in row.items():
                if field == 'address': continue
                replacement = ('addi' if field == 'mnemonic' else f'{int(value, 16) ^ 4:08x}'
                               if field == 'target' else value ^ 1)
                def changed(word, address):
                    decoded = original(word, address)
                    return dict(decoded, **{field: replacement}) if address == pc else decoded
                with patch.object(a, 'decode_selected', changed):
                    with self.assertRaisesRegex(a.c.FormatError, 'complete control-flow mismatch'):
                        a.range_evidence(FakeDB(BODY), TEXT_MAPPING, ENTRY, WIDTH)
                mutations += 1
        self.assertEqual(mutations, 267)

    def test_prefix_clear_order_and_second_pass_guard_before_first_call(self):
        rows = {int(row['address'], 16): row for row in EXPECTED}
        loads = [row for row in EXPECTED if 0x8006ae7c <= int(row['address'], 16) < 0x8006af54
                 and row['mnemonic'] in ('lbz', 'lbzu')]
        self.assertEqual([(row['mnemonic'], row['rA'], row['displacement']) for row in loads],
                         [('lbz', 4, 0), ('lbz', 4, 0x1e00), ('lbz', 4, 0x3c00),
                          ('lbz', 4, 0x5a00), ('lbzu', 4, 0x7800), ('lbz', 4, 0x1e00)])
        clear = [row for row in EXPECTED if int(row['address'], 16) < 0x8006af54
                 and row['mnemonic'] == 'stb']
        self.assertEqual(len(clear), 36)
        for i, base in enumerate((0, 0x1e00, 0x3c00, 0x5a00, 0, 0x1e00)):
            self.assertEqual([(row['rS'], row['rA'], row['displacement']) for row in clear[i*6:i*6+6]],
                [(0, 4, base + offset) for offset in (0x58a, 0x58b, 0x58c, 0x58d, 0x7d2, 0x7d3)])
        for row in loads:
            pc = int(row['address'], 16)
            self.assertEqual({k: rows[pc+4][k] for k in ('mnemonic', 'rS', 'rA', 'Rc')},
                             dict(mnemonic='extsb', rS=3, rA=3, Rc=1))
            self.assertEqual((rows[pc+8]['BO'], rows[pc+8]['BI']), (12, 2))
        self.assertEqual((rows[0x8006ae78]['mnemonic'], rows[0x8006ae78]['displacement']), ('lwz', 0x4e84))
        self.assertEqual((rows[0x8006af5c]['mnemonic'], rows[0x8006af5c]['rD'],
                          rows[0x8006af5c]['displacement']), ('lwz', 30, 0x4e84))
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006af60, 0x8006af84, 4)],
                         ['lbz', 'extsb', 'bc', 'lbz', 'extsb', 'cmpi', 'bc', 'or', 'bl'])
        self.assertEqual(rows[0x8006af6c]['displacement'], 0x18)
        self.assertEqual(rows[0x8006af74]['immediate'], 1)
        self.assertEqual((rows[0x8006af78]['BO'], rows[0x8006af78]['BI']), (12, 0))
        self.assertFalse(any(row['mnemonic'] in ('lfs', 'lfd', 'lfsx', 'frsqrte')
                             for row in EXPECTED if int(row['address'], 16) <= 0x8006af88))
        # Signed status: 0x80..0xff must not become a positive-status actor.
        for byte in range(256):
            signed = byte - 256 if byte & 128 else byte
            self.assertEqual(signed >= 1, 1 <= byte <= 127)

    def test_third_pass_load_order_saved_team_and_sequential_rmw(self):
        rows = {int(row['address'], 16): row for row in EXPECTED}
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006b358, 0x8006b374, 4)],
                         ['lwz', 'lbz', 'lwz', 'extsb', 'bc', 'cmpli', 'bc'])
        self.assertEqual(rows[0x8006b360]['displacement'], 0x508)
        self.assertEqual(rows[0x8006b374]['displacement'], 0x83)
        self.assertEqual(rows[0x8006b380]['displacement'], 0x7d3)
        self.assertEqual([(rows[pc]['rA'], rows[pc]['displacement']) for pc in (0x8006b38c, 0x8006b390)],
                         [(5, 0x88), (4, 0x88)])
        self.assertEqual(rows[0x8006b398]['rA'], 8)
        self.assertEqual(rows[0x8006b3f0]['rB'], 8)
        self.assertEqual(rows[0x8006b3bc]['displacement'], 0x4e84)
        self.assertEqual(rows[0x8006b3d0]['target'], '8006b420')  # excludes own index before mask load
        self.assertEqual((rows[0x8006b3d4]['rA'], rows[0x8006b3d4]['displacement']), (5, 0x58a))
        for start, base, mask in ((0x8006b3f8, 4, 1), (0x8006b404, 9, 1), (0x8006b410, 5, 2)):
            self.assertEqual([rows[start+i*4]['mnemonic'] for i in range(3)], ['lbz', 'ori', 'stb'])
            self.assertEqual((rows[start]['rA'], rows[start]['displacement']), (base, 0x7d3))
            self.assertEqual(rows[start+4]['immediate'], mask)
            self.assertEqual((rows[start+8]['rA'], rows[start+8]['displacement']), (base, 0x7d3))
        self.assertFalse(any(row['mnemonic'] == 'lbz' and row['rA'] == 9 and row['displacement'] in (0, 0x18)
                             for row in EXPECTED))
        self.assertEqual(rows[0x8006b41c]['target'], '8006b42c')  # first match exits inner scan

    def test_float_comparison_bits_estimator_operands_and_unselected_constants(self):
        rows = {int(row['address'], 16): row for row in EXPECTED}
        self.assertEqual([(row['address'], row['fD'], row['fB']) for row in EXPECTED
                          if row['mnemonic'] == 'frsqrte'],
                         [('8006afbc', 2, 1), ('8006b03c', 1, 4), ('8006b218', 2, 1), ('8006b298', 1, 4)])
        self.assertEqual({row['displacement'] for row in EXPECTED
                          if row['mnemonic'] in ('lfs', 'lfd') and row['rA'] == 2},
                         {-29640, -29632, -29624, -29616, -29612, -29608})
        self.assertEqual((rows[0x8006b3b0]['BO'], rows[0x8006b3b0]['BI']), (12, 1))
        for lt, gt, eq, un in ((1,0,0,0), (0,1,0,0), (0,0,1,0), (0,0,0,1)):
            # Third-pass skip is GT, so unordered reaches the inner scan.
            self.assertEqual(not bool(gt), bool(lt or eq or un))
            # Bit4/bit8 checks use cror EQ,GT,EQ, not not-LT.
            self.assertEqual(bool(gt or eq), not bool(lt or un))
        for pc in (0x8006b0ec, 0x8006b168):
            self.assertEqual((rows[pc]['mnemonic'], rows[pc]['crD'], rows[pc]['crA'], rows[pc]['crB']),
                             ('cror', 2, 1, 2))

    def test_decoder_bounds_and_unsupported_instruction_refuse(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        with patch.object(a, 'decode_selected', return_value=None):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(BODY), TEXT_MAPPING, ENTRY, WIDTH)

    def test_addresses_widths_duplicate_ranges_and_exact_typed_maps_refuse(self):
        for pc, width in [(bad, WIDTH) for bad in (ENTRY - 4, ENTRY + 4, ENTRY + 1,
                float(ENTRY), True, -1, 1 << 32, 0x8006b450, 0x8006b7f4, 0x80437658)] + [
                (ENTRY, bad) for bad in (0, WIDTH - 4, WIDTH + 4, -WIDTH, True, float(WIDTH))]:
            db = FakeDB(BODY)
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, width)
            self.assertFalse(db.calls)
        for index, value in enumerate(TEXT_MAPPING):
            for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                changed = list(TEXT_MAPPING); changed[index] = replacement; db = FakeDB(BODY)
                with self.assertRaises(a.c.FormatError):
                    a.range_evidence(db, tuple(changed), ENTRY, WIDTH)
                self.assertFalse(db.calls)
        with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(BODY), list(TEXT_MAPPING), ENTRY, WIDTH)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            db = FakeDB(BODY)
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, ENTRY, WIDTH)
            self.assertFalse(db.calls)
        for raw in (BODY[:-1], BODY + b'\0'):
            with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                a.range_evidence(FakeDB(raw), TEXT_MAPPING, ENTRY, WIDTH)

    def test_authentication_precedes_parser_and_selection(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad'); db.assert_not_called(); code.assert_not_called()

    def test_mapping_refusal_precedes_selection(self):
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
        self.assertEqual(len(cases), 43)
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called()

    def test_no_arbitrary_cli_and_missing_snapshot(self):
        for option in ('--address', '--width', '--pointer', '--target', '--dump', '--state'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/target.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
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

    def test_both_snapshots_exact_operands_coverage_and_ceiling(self):
        for key in ('mappings', 'ranges', 'function_coverage', 'selection_basis'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([row['snapshot'] for row in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([row['snapshot_sha256'] for row in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(report['ranges'][0]['instructions'],
                             EXPECTED)
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (1, 1520, 0))
            for key in ('pointer_following', 'global_payloads_read', 'callee_bodies_read',
                        'globals_runtime_values_established', 'original_execution', 'constants_selected', 'estimator_imported'):
                self.assertFalse(basis[key])
            self.assertIn('not original-DOL identity', report['caveat'])
            row = report['function_coverage'][0]
            self.assertEqual(row['represented_instructions'], 380)
            self.assertEqual(row['unrepresented_instructions'], 0)
            self.assertEqual(row['unrepresented_ranges'], [])
            self.assertEqual(row['selected_width'], row['map_size'])

    def test_exact_single_selected_read_after_unchanged_authentication(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(auth)
            self.assertTrue(all(row[0] == 263 for row in auth))

    def test_physical_span_and_no_raw_output(self):
        for report in self.reports:
            row = report['ranges'][0]
            self.assertEqual(row['spans'], [dict(root_buffer=21, data_buffer=47, chain_offset=415872,
                data_offset=6422, length=1520, obfuscated=True, physical_offset=792860)])
            self.assertEqual(row['end_exclusive'], '8006b450')
            self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
            self.assertFalse(any('word' in item or 'bytes' in item for item in row['instructions']))

    def test_real_snapshot_hash_schema_and_selected_payload_refuse(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes(); digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as code:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            code.assert_not_called()
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
                with patch.object(a.c.GBF, 'tables', tampered_tables), patch.object(a, 'range_evidence') as code:
                    with self.assertRaises(a.c.FormatError): a.inspect(raw, digest)
                    code.assert_not_called()
        original = a.c.GBF.chain
        def tampered(db, *args):
            payload, spans = original(db, *args)
            if args == EXPECTED_READS[0]: payload = bytes([payload[0] ^ 1]) + payload[1:]
            return payload, spans
        with patch.object(a.c.GBF, 'chain', tampered), patch.object(a, 'decode_selected') as decode:
            with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)
            decode.assert_not_called()


if __name__ == '__main__': unittest.main()
