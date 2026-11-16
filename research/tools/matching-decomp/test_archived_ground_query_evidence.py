#!/usr/bin/env python3
"""Frozen all-operand witnesses, inverse encodings and fixed-reader refusal guards.

Synthetic tests need no archive. Local cases authenticate both known snapshots
without fetching inputs. No archived instruction execution or raw-byte fixture.
"""
import contextlib
import copy
import hashlib
import importlib
import io
import json
import os
from pathlib import Path
import re
import struct
import unittest
from unittest.mock import patch

import read_archived_ground_query_evidence as a
import test_archived_double_action_evidence as previous

FakeDB = previous.FakeDB
FIELDS = dict(previous.FIELDS, fcmpu='BF fA fB', frsp='fD fB Rc',
              frsqrte='fD fB Rc', fmul='fD fA fC Rc', fnmsub='fD fA fC fB Rc')


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


# Fixed schedules, not generated during tests; every operand is explicit.
EXPECTED = {
    0x8003e0a8: ops('''
stwu 1 1 -128
mflr 0
stw 0 1 132
stfd 31 1 112
psq_st 31 1 120 0 0
stfd 30 1 96
psq_st 30 1 104 0 0
stw 31 1 92
stw 30 1 88
stw 29 1 84
stw 28 1 80
or 3 28 3 0
fmr 30 1 0
lbz 0 3 475
or 4 29 4 0
or 5 30 5 0
extsb 0 0 1
bc 12 2 0 8003e124 0
lwz 3 28 480
addi 4 28 504
addi 5 1 56
lwz 3 3 96
bl 8020b7a8 0 1
lwz 3 28 492
lwz 0 28 496
stw 3 30 0
stw 0 30 4
lwz 0 28 500
stw 0 30 8
lfs 1 1 60
b 8003e3c4 0 0
lfs 1 2 -31416
or 29 3 29 0
lfs 0 2 -31400
stfs 1 30 0
stfs 0 30 4
stfs 1 30 8
bl 8003fb00 0 1
cmpi 0 0 3 0
bc 4 2 0 8003e150 0
lfs 1 2 -31220
b 8003e3c4 0 0
lwz 3 13 -21316
addi 31 0 0
lfs 0 3 52
fcmpo 0 30 0
cror 2 1 2
bc 4 2 0 8003e16c 0
addi 31 0 1
lfs 0 29 0
addi 3 1 44
stfs 0 1 44
lfs 1 29 4
lfs 0 28 1744
fadds 0 1 0 0
stfs 0 1 48
lfs 0 29 8
stfs 0 1 52
lfs 1 28 48
lfs 0 28 1748
fadds 1 1 0 0
bl 8003f320 0 1
lfs 3 28 48
fmr 31 1 0
lfs 2 28 1748
lfs 1 28 36
lfs 0 28 1744
fadds 2 3 2 0
lfs 3 2 -31416
fadds 0 1 0 0
fsubs 0 2 0 0
fcmpo 0 3 0
bc 4 0 0 8003e1d0 0
fadds 30 30 0 0
lfs 0 29 4
or 29 3 29 0
fadds 30 30 0 0
bl 8003fa68 0 1
lwz 4 13 -21316
lfs 4 2 -31416
lfs 0 4 104
lfs 3 2 -31400
fmr 1 0 0
stfs 4 1 20
lfs 2 4 52
stfs 3 1 24
stfs 4 1 28
stfs 4 1 8
stfs 3 1 12
stfs 4 1 16
b 8003e344 0 0
lfs 3 6 4
lfs 9 1 44
lfs 7 1 52
fsubs 8 3 9 0
stfs 8 1 56
lfs 3 6 12
fsubs 6 3 7 0
stfs 6 1 64
lfs 3 6 16
lfs 4 6 24
fsubs 10 3 9 0
lfs 3 6 28
fsubs 11 4 7 0
lfs 5 6 36
fsubs 9 3 9 0
fmuls 4 6 10 0
fmuls 3 8 11 0
fsubs 5 5 7 0
fcmpo 0 4 3
bc 12 0 0 8003e340 0
fmuls 4 11 9 0
fmuls 3 10 5 0
fcmpo 0 4 3
bc 12 0 0 8003e340 0
fmuls 4 5 8 0
fmuls 3 9 6 0
fcmpo 0 4 3
bc 12 0 0 8003e340 0
lwz 5 6 40
lwz 0 6 48
stw 5 1 32
lwz 4 6 44
stw 0 1 40
lfs 4 1 32
lfs 3 1 40
stw 4 1 36
fmuls 7 4 8 0
fmuls 4 3 6 0
lfs 3 6 8
lfs 5 1 36
fadds 7 7 4 0
fmuls 3 5 3 0
fadds 7 7 3 0
fdivs 7 7 5 0
fcmpo 0 30 7
bc 4 1 0 8003e2f0 0
fcmpo 0 31 7
bc 4 1 0 8003e2f0 0
fcmpo 0 0 7
cror 2 0 2
bc 4 2 0 8003e2f0 0
stw 5 30 0
fmr 0 7 0
stw 4 30 4
stw 0 30 8
fcmpo 0 2 7
cror 2 1 2
bc 4 2 0 8003e318 0
lwz 5 1 32
fmr 2 7 0
lwz 4 1 36
lwz 0 1 40
stw 5 1 20
stw 4 1 24
stw 0 1 28
fcmpo 0 1 7
cror 2 0 2
bc 4 2 0 8003e340 0
lwz 5 1 32
fmr 1 7 0
lwz 4 1 36
lwz 0 1 40
stw 5 1 8
stw 4 1 12
stw 0 1 16
addi 3 3 4
lwz 6 3 0
addis 0 6 1
cmpli 0 0 0 65535
bc 4 2 0 8003e214 0
cmpi 0 0 31 0
bc 12 2 0 8003e378 0
lwz 0 1 8
lwz 3 1 12
stw 0 30 0
lwz 0 1 16
stw 3 30 4
stw 0 30 8
b 8003e3c4 0 0
lwz 3 13 -21316
lfs 1 3 104
fcmpu 0 0 1
bc 12 2 0 8003e390 0
fmr 1 0 0
b 8003e3c4 0 0
lwz 0 1 20
lwz 3 1 24
stw 0 30 0
lwz 0 1 28
stw 3 30 4
stw 0 30 8
lwz 3 13 -21316
lfs 0 3 52
fcmpu 0 2 0
bc 4 2 0 8003e3c0 0
lfs 1 3 104
b 8003e3c4 0 0
fmr 1 2 0
psq_l 31 1 120 0 0
lfd 31 1 112
psq_l 30 1 104 0 0
lfd 30 1 96
lwz 31 1 92
lwz 30 1 88
lwz 29 1 84
lwz 0 1 132
lwz 28 1 80
mtlr 0
addi 1 1 128
blr 20 0 0 0
'''),
    0x800677b0: ops('''
stwu 1 1 -64
mflr 0
stw 0 1 68
stfd 31 1 48
psq_st 31 1 56 0 0
stw 31 1 44
stw 30 1 40
or 3 30 3 0
lbz 0 3 1993
extsb 0 0 1
bc 12 2 0 800677e4 0
addi 3 0 0
b 800679b0 0 0
lfs 1 30 1640
addi 4 30 32
addi 5 1 24
bl 8003e0a8 0 1
lfs 2 30 36
fmr 31 1 0
lfs 0 30 1744
fadds 0 2 0 0
fcmpo 0 0 31
bc 4 1 0 80067814 0
addi 3 0 0
b 800679b0 0 0
lbz 0 30 475
extsb 0 0 1
bc 4 2 0 80067888 0
addi 3 30 32
addi 4 30 44
addi 5 1 12
bl 8020ba78 0 1
lfs 1 1 12
lfs 0 1 16
fmuls 2 1 1 0
lfs 3 1 20
fmuls 1 0 0 0
lfs 0 2 -29736
fmuls 3 3 3 0
fadds 1 2 1 0
fadds 1 3 1 0
fcmpo 0 1 0
bc 4 1 0 80067888 0
addi 3 1 12
or 3 4 3 0
bl 8020bab8 0 1
addi 3 1 12
addi 4 1 24
bl 8020bb58 0 1
lfs 0 2 -29776
fcmpo 0 1 0
bc 4 1 0 80067888 0
addi 3 0 0
b 800679b0 0 0
lfs 1 30 1688
lfs 0 2 -29776
fcmpo 0 1 0
bc 4 1 0 800678a4 0
lwz 3 30 1200
lha 31 3 174
b 800678ac 0 0
lwz 3 30 1200
lha 31 3 172
lfs 0 1 24
lfs 1 1 32
fmuls 2 0 0 0
lfs 0 2 -29776
fmuls 1 1 1 0
fadds 1 2 1 0
fcmpo 0 1 0
bc 4 1 0 80067918 0
frsqrte 2 1 0
lfd 4 2 -29728
lfd 3 2 -29720
fmul 0 2 2 0
fmul 2 4 2 0
fnmsub 0 1 0 3 0
fmul 2 2 0 0
fmul 0 2 2 0
fmul 2 4 2 0
fnmsub 0 1 0 3 0
fmul 2 2 0 0
fmul 0 2 2 0
fmul 2 4 2 0
fnmsub 0 1 0 3 0
fmul 0 2 0 0
fmul 0 1 0 0
frsp 0 0 0
stfs 0 1 8
lfs 1 1 8
lfs 2 1 28
bl 800452a0 0 1
extsh 3 4 0
extsh 31 0 0
cmp 0 0 4 0
bc 4 1 0 80067988 0
bl 80045238 0 1
lfs 0 30 36
addi 3 1 24
or 3 4 3 0
fsubs 0 31 0 0
fmuls 1 0 1 0
bl 8020ba9c 0 1
addi 3 30 32
addi 4 1 24
or 3 5 3 0
bl 8020ba54 0 1
lfs 0 2 -29776
addi 3 0 0
lfs 1 2 -29772
stfs 0 30 76
lfs 0 30 68
fmuls 0 0 1 0
stfs 0 30 68
lfs 0 30 72
fmuls 0 0 1 0
stfs 0 30 72
b 800679b0 0 0
lfs 0 30 1744
fsubs 0 31 0 0
stfs 0 30 36
lwz 12 30 1876
cmpli 0 0 12 0
bc 12 2 0 800679ac 0
or 30 3 30 0
mtctr 12
bctrl 20 0 0 1
addi 3 0 1
psq_l 31 1 56 0 0
lwz 0 1 68
lfd 31 1 48
lwz 31 1 44
lwz 30 1 40
mtlr 0
addi 1 1 64
blr 20 0 0 0
'''),
}


def encode(row, pc):
    """Inverse encodings independent of the reader and its decoder."""
    n = row['mnemonic']
    if n == 'fcmpu':
        return 63 << 26 | row['BF'] << 23 | row['fA'] << 16 | row['fB'] << 11
    if n in ('frsp', 'frsqrte'):
        return 63 << 26 | row['fD'] << 21 | row['fB'] << 11 | \
            (12 if n == 'frsp' else 26) << 1 | row['Rc']
    if n in ('fmul', 'fnmsub'):
        return 63 << 26 | row['fD'] << 21 | row['fA'] << 16 | row.get('fB', 0) << 11 | \
            row['fC'] << 6 | (25 if n == 'fmul' else 30) << 1 | row['Rc']
    return previous.encode(row, pc)


PHYSICAL = {'8003e0a8': [{'root_buffer': 21,
               'data_buffer': 36,
               'chain_offset': 232136,
               'data_offset': 2844,
               'length': 844,
               'obfuscated': True,
               'physical_offset': 609058}],
 '800677b0': [{'root_buffer': 21,
               'data_buffer': 46,
               'chain_offset': 401872,
               'data_offset': 8800,
               'length': 544,
               'obfuscated': True,
               'physical_offset': 778854}],
 '8043702c': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 1548,
               'data_offset': 1548,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4343314}],
 '804375f8': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 3032,
               'data_offset': 3032,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4344798}],
 '804375d4': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 2996,
               'data_offset': 2996,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4344762}],
 '80437600': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 3040,
               'data_offset': 3040,
               'length': 8,
               'obfuscated': True,
               'physical_offset': 4344806}],
 '80437608': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 3048,
               'data_offset': 3048,
               'length': 8,
               'obfuscated': True,
               'physical_offset': 4344814}]}


def at(entry):
    return {entry + i * 4: row for i, row in enumerate(EXPECTED[entry])}


class SyntheticTests(unittest.TestCase):
    def test_all_operands_inverse_encode_exact_hashes(self):
        self.assertEqual([(p,w) for p,w,_ in a.RANGES], [(0x8003e0a8,844),(0x800677b0,544)])
        self.assertEqual(len(a.CONSTANTS),5)
        for pc,width,digest in a.RANGES:
            rows=EXPECTED[pc]
            self.assertEqual(len(rows),width//4)
            raw=struct.pack('>'+'I'*len(rows),*(encode(row,pc+4*i) for i,row in enumerate(rows)))
            self.assertEqual(hashlib.sha256(raw).hexdigest(),digest)
            db=FakeDB(raw); result=a.range_evidence(db,a.TEXT_MAPPING,pc,width)
            self.assertEqual(result['instructions'],[dict(address=f'{pc+i*4:08x}',**row) for i,row in enumerate(rows)])
            self.assertEqual(db.calls,[(21,pc-0x800055e0,width,2796416)])
            for row in rows:self.assertEqual(set(row),{'mnemonic',*FIELDS[row['mnemonic']].split()})

    def test_selection_duplicate_and_type_guards_before_reads(self):
        for pc,width,_ in a.RANGES:
            for args in ((pc+4,width-4),(pc,width+4),(pc,width-4),(pc-4,4),(pc+width,4)):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.range_evidence(None,a.TEXT_MAPPING,*args)
            with patch.object(a,'RANGES',a.RANGES*2):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.range_evidence(None,a.TEXT_MAPPING,pc,width)
        for bad in (True,1.0,'4',None):
            for args in ((bad,844),(0x8003e0a8,bad)):
                with self.assertRaisesRegex(a.c.FormatError,'integer fields'):a.range_evidence(None,a.TEXT_MAPPING,*args)
            with self.assertRaisesRegex(a.c.FormatError,'integer fields'):a.constant_evidence(None,a.DATA5_MAPPING,bad)
        for pc in (0x80437028,0x80437030,0x804375fc,0x80437604,0x80437610):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.constant_evidence(None,a.DATA5_MAPPING,pc)
        with patch.object(a,'CONSTANTS',a.CONSTANTS*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):a.constant_evidence(None,a.DATA5_MAPPING,0x8043702c)

    def test_fixed_mapping_guards_before_reads(self):
        for fn,m,args in ((a.range_evidence,a.TEXT_MAPPING,(0x8003e0a8,844)),
                          (a.constant_evidence,a.DATA5_MAPPING,(0x8043702c,))):
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
            with patch.object(a,'RANGES',((0x8003e0a8,len(raw),hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError,reason):a.range_evidence(FakeDB(raw),a.TEXT_MAPPING,0x8003e0a8,len(raw))

    def test_exact_scalar_bits_widths_and_values(self):
        for pc,bits,label in a.CONSTANTS:
            raw=bytes.fromhex(bits);db=FakeDB(raw);result=a.constant_evidence(db,a.DATA5_MAPPING,pc)
            self.assertEqual(db.calls,[(263,pc-0x80436a20,len(raw),27360)])
            self.assertEqual((result['bits'],result['label']),(bits,label))
            self.assertEqual(result['value'],struct.unpack('>f' if len(raw)==4 else '>d',raw)[0])
            self.assertEqual(result['sha256'],hashlib.sha256(raw).hexdigest())
            for bad,reason in ((raw[:-1],'byte width'),(raw+bytes(1),'byte width'),(bytes([raw[0]^1])+raw[1:],'bits mismatch')):
                with self.assertRaisesRegex(a.c.FormatError,reason):a.constant_evidence(FakeDB(bad),a.DATA5_MAPPING,pc)
        self.assertEqual(a.constant_evidence(FakeDB(bytes.fromhex('c59c4000')),a.DATA5_MAPPING,0x8043702c)['value'],-5000)

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
        for target in ('text-root','text-offset','text-type','text-length','data3-root','data5-root','data5-offset',
                       'text-duplicate','data5-duplicate-sub','image','overlap'):
            aa,bb,ss=copy.deepcopy(({'image_offset':'80000000'},blocks,subs))
            if target=='text-root':ss[1][4]+=1
            if target=='text-offset':ss[1][5]+=1
            if target=='text-type':ss[1][1]+=1
            if target=='text-length':bb[1][5]-=4
            if target=='data3-root':ss[5][4]+=1
            if target=='data5-root':ss[7][4]+=1
            if target=='data5-offset':ss[7][3]+=1
            if target=='text-duplicate':bb[99]=copy.deepcopy(bb[1])
            if target=='data5-duplicate-sub':ss[99]=copy.deepcopy(ss[7])
            if target=='image':aa['image_offset']='80000004'
            if target=='overlap':bb[99]=['other',None,None,0,0x200000000003e0a8,4,0]
            with patch.object(a.c,'inspect',return_value=aa),patch.object(a.c,'GBF') as parser, \
                    patch.object(a,'range_evidence') as ranges,patch.object(a,'constant_evidence') as constants:
                db=parser.return_value;db.tables.return_value={'Memory Blocks':'b','Sub Memory Blocks':'s'}
                db.rows.side_effect=lambda key:{'b':bb,'s':ss}[key]
                with self.assertRaises(a.c.FormatError):a.inspect(b'synthetic','synthetic')
                ranges.assert_not_called();constants.assert_not_called()

    def test_added_floating_forms_and_reserved_fields(self):
        for row in (dict(mnemonic='fcmpu',BF=0,fA=7,fB=3),
                    dict(mnemonic='frsp',fD=7,fB=3,Rc=0),dict(mnemonic='frsqrte',fD=7,fB=3,Rc=0),
                    dict(mnemonic='fmul',fD=7,fA=5,fC=3,Rc=0),
                    dict(mnemonic='fnmsub',fD=7,fA=5,fC=3,fB=2,Rc=0)):
            word=encode(row,0);self.assertEqual(a.decode_selected(word,0),row)
            with self.assertRaises(a.c.FormatError):a.decode_selected(word|1,0)
            if row['mnemonic'] in ('frsp','frsqrte'):
                with self.assertRaises(a.c.FormatError):a.decode_selected(word|1<<16,0)
                self.assertIsNone(a.decode_selected(word|1<<6,0))
            if row['mnemonic']=='fcmpu':
                for mask in (1<<21,1<<22,1<<23):
                    with self.assertRaises(a.c.FormatError):a.decode_selected(word|mask,0)
            if row['mnemonic']=='fmul':
                with self.assertRaises(a.c.FormatError):a.decode_selected(word|1<<11,0)
        for bad in (True,-1,1<<32,1.0):
            with self.assertRaises(a.c.FormatError):a.decode_selected(bad,0)
        for bad in (True,-4,1<<32,2,1.0):
            with self.assertRaises(a.c.FormatError):a.decode_selected(0,bad)

    def test_source_extent_markers_and_ground_map(self):
        root=Path(__file__).resolve().parents[3]
        text=(root/'research/symbols/GG4E-CSM-20220412.map').read_text()
        maps={int(pc,16):int(width,16) for pc,width in re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ',text,re.M)}
        for pc,width,_ in a.RANGES:
            chunk='0004' if pc==0x8003e0a8 else '0008'
            src=(root/f'research/decomp/ghidra-export/chunk_{chunk}.c').read_text()
            markers=[int(v,16) for v in re.findall(r'^// ==== ([0-9a-f]{8}) ',src,re.M)]
            self.assertEqual(markers[markers.index(pc)+1],pc+width)
            if pc in a.MAP_SIZES:self.assertEqual(maps[pc],width)
            else:self.assertNotIn(pc,maps)

    def test_reused_exact_witnesses_not_new_selections(self):
        for reader,pc,width,sha in a.REUSED_RANGES:
            old=importlib.import_module(f'read_archived_{reader}_evidence')
            self.assertIn((pc,width,sha),old.RANGES)
            self.assertNotIn((pc,width),[r[:2] for r in a.RANGES])
        for reader,pc,bits in a.REUSED_CONSTANTS:
            old=importlib.import_module(f'read_archived_{reader}_evidence')
            if isinstance(old.TARGETS,dict):self.assertEqual(old.TARGETS[pc],bits)
            else:self.assertIn((pc,len(bits)//2,bits),old.TARGETS)
            self.assertNotIn(pc,[r[0] for r in a.CONSTANTS])

    def test_query_default_outside_and_fresh_scalar_order(self):
        q=at(0x8003e0a8)
        self.assertEqual([q[p]['displacement'] for p in (0x8003e130,0x8003e134,0x8003e138)],[0,4,8])
        self.assertEqual(q[0x8003e13c]['target'],'8003fb00')
        self.assertEqual(q[0x8003e148],dict(mnemonic='lfs',fD=1,rA=2,displacement=0x8043702c-0x8043ea20))
        self.assertEqual(q[0x8003e19c]['target'],'8003f320')
        self.assertEqual([q[p]['displacement'] for p in (0x8003e1a0,0x8003e1a8,0x8003e1ac,0x8003e1b0)],
                         [0x30,0x6d4,0x24,0x6d0])
        self.assertEqual(q[0x8003e1dc]['target'],'8003fa68')
        self.assertEqual([q[p]['displacement'] for p in (0x8003e1e8,0x8003e1f8)],[0x68,0x34])

    def test_query_triangle_arithmetic_and_equal_normal_replacement(self):
        q=at(0x8003e0a8)
        self.assertFalse(any(r['mnemonic'] in ('fmadds','fmadd','fnmsub') for r in q.values()))
        self.assertEqual([q[p]['mnemonic'] for p in (0x8003e2a4,0x8003e2a8,0x8003e2b4,0x8003e2b8,0x8003e2bc,0x8003e2c0)],
                         ['fmuls','fmuls','fadds','fmuls','fadds','fdivs'])
        self.assertEqual([q[p]['displacement'] for p in (0x8003e284,0x8003e288,0x8003e290)],[0x28,0x30,0x2c])
        self.assertEqual([q[p]['displacement'] for p in (0x8003e2e0,0x8003e2e8,0x8003e2ec)],[0,4,8])
        for pc,ba in ((0x8003e2d8,0),(0x8003e2f4,1),(0x8003e31c,0)):
            self.assertEqual(q[pc],dict(mnemonic='cror',BT=2,BA=ba,BB=2))
        for pc in (0x8003e2c8,0x8003e2d0):
            self.assertEqual((q[pc]['BO'],q[pc]['BI']),(4,1))

    def test_query_fallback_copy_and_fresh_owner_order(self):
        q=at(0x8003e0a8)
        for start,source in ((0x8003e35c,8),(0x8003e390,20)):
            rows=[q[start+i*4] for i in range(6)]
            self.assertEqual([r['mnemonic'] for r in rows],['lwz','lwz','stw','lwz','stw','stw'])
            self.assertEqual([r['displacement'] for r in rows],[source,source+4,0,source+8,4,8])
        self.assertEqual(q[0x8003e380],dict(mnemonic='fcmpu',BF=0,fA=0,fB=1))
        self.assertEqual(q[0x8003e3a8],dict(mnemonic='lwz',rD=3,rA=13,displacement=-21316))
        self.assertEqual(q[0x8003e3b0],dict(mnemonic='fcmpu',BF=0,fA=2,fB=0))
        self.assertEqual(q[0x8003e3b8]['displacement'],0x68)

    def test_ground_early_return_and_squared_displacement_order(self):
        q=at(0x800677b0)
        self.assertEqual(q[0x800677d0]['displacement'],0x7c9)
        self.assertEqual(q[0x800677f0]['target'],'8003e0a8')
        self.assertEqual(q[0x800677f4]['displacement'],0x24)
        self.assertEqual(q[0x800677fc]['displacement'],0x6d0)
        self.assertEqual(q[0x80067800],dict(mnemonic='fadds',fD=0,fA=2,fB=0,Rc=0))
        self.assertEqual(q[0x80067808],dict(mnemonic='bc',BO=4,BI=1,LK=0,target='80067814',AA=0))
        self.assertEqual(q[0x80067814]['displacement'],0x1db)
        self.assertEqual([q[p]['target'] for p in (0x8006782c,0x80067864,0x80067870)],['8020ba78','8020bab8','8020bb58'])
        self.assertEqual(q[0x8006784c],dict(mnemonic='fadds',fD=1,fA=2,fB=1,Rc=0))
        self.assertEqual(q[0x80067850],dict(mnemonic='fadds',fD=1,fA=3,fB=1,Rc=0))

    def test_ground_fused_sqrt_and_landing_store_before_callback(self):
        q=at(0x800677b0)
        self.assertEqual([q[p]['mnemonic'] for p in range(0x800678cc,0x80067910,4)],
                         ['frsqrte','lfd','lfd','fmul','fmul','fnmsub','fmul','fmul','fmul','fnmsub',
                          'fmul','fmul','fmul','fnmsub','fmul','fmul','frsp'])
        for pc in (0x800678e0,0x800678f0,0x80067900):
            self.assertEqual(q[pc],dict(mnemonic='fnmsub',fD=0,fA=1,fC=0,fB=3,Rc=0))
        self.assertEqual([q[p]['displacement'] for p in (0x8006789c,0x800678a8)],[0xae,0xac])
        self.assertEqual(q[0x8006791c]['target'],'800452a0')
        self.assertEqual(q[0x80067990],dict(mnemonic='stfs',fS=0,rA=30,displacement=0x24))
        self.assertEqual(q[0x80067994],dict(mnemonic='lwz',rD=12,rA=30,displacement=0x754))
        self.assertEqual(q[0x800679a8]['mnemonic'],'bctrl')

    def test_reused_phase0_postground_and_paired_order(self):
        q={0x800ff30c+i*4:r for i,r in enumerate(previous.EXPECTED[0x800ff30c])}
        self.assertEqual(q[0x800ff3ac]['target'],'800677b0')
        self.assertEqual(q[0x800ff3b0]['mnemonic'],'lha')
        self.assertEqual(q[0x800ff3c4]['mnemonic'],'lha')
        self.assertEqual(q[0x800ff3dc],dict(mnemonic='addi',rD=0,rA=5,immediate=1))
        self.assertEqual(q[0x800ff3e0],dict(mnemonic='extsb',rS=5,rA=6,Rc=0))
        self.assertEqual(q[0x800ff3e4],dict(mnemonic='stb',rS=0,rA=30,displacement=0x6ea))
        self.assertEqual(q[0x800ff3f4]['target'],'8004beb8')
        self.assertEqual(q[0x800ff3fc],dict(mnemonic='stfs',fS=0,rA=30,displacement=0x80c))
        rows=previous.EXPECTED[0x8020ba78]
        self.assertEqual([r['mnemonic'] for r in rows],['psq_l','psq_l','ps_sub','psq_st','psq_l','psq_l','ps_sub','psq_st','blr'])
        self.assertEqual([r['W'] for r in rows if r['mnemonic'].startswith('psq_')],[0,0,0,1,1,1])

    def test_no_arbitrary_cli_or_shared_allowlist_widening(self):
        for pc,width,_ in a.RANGES:
            self.assertNotIn((pc,width),a.c.TARGETS)
            self.assertNotIn((pc,width),[x[:2] for x in a.double.RANGES])
        for args in (['--address','8003e0a8'],['--width','844'],['--target','800677b0'],['--raw'],['--execute'],['--follow']):
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
        cls.results=[];cls.reused=[]
        for p in paths:
            a.c.require(32<=p.stat().st_size<=a.c.MAX_FILE,'snapshot size bounds')
            with p.open('rb') as stream:data=stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data)<=a.c.MAX_FILE,'snapshot size bounds')
            # New reads finish whole-file/schema/map authentication first.
            cls.results.append(a.inspect(data,hashlib.sha256(data).hexdigest()))
            db=a.c.GBF(data);reuse=[]
            for reader,pc,width,sha in a.REUSED_RANGES:
                old=importlib.import_module(f'read_archived_{reader}_evidence')
                mapping=21 if reader=='terrain_query' else old.TEXT_MAPPING
                reuse.append(old.range_evidence(db,mapping,pc,width))
            for reader,pc,bits in a.REUSED_CONSTANTS:
                old=importlib.import_module(f'read_archived_{reader}_evidence')
                if reader=='actor_ceiling':reuse.append(old.constant_evidence(db,old.DATA5_MAPPING,pc,len(bits)//2))
                else:reuse.append(old.constant_evidence(db,pc))
            cls.reused.append(reuse)

    def test_full_operands_both_snapshots(self):
        for result in self.results:
            for span,(pc,width,digest) in zip(result['ranges'],a.RANGES):
                self.assertEqual(span['instructions'],[dict(address=f'{pc+i*4:08x}',**row) for i,row in enumerate(EXPECTED[pc])])
                self.assertEqual((span['width'],span['sha256'],span['end_exclusive']),(width,digest,f'{pc+width:08x}'))
            self.assertEqual(sum(c['represented_instructions'] for c in result['function_coverage']),347)
            for cov in result['function_coverage']:
                self.assertEqual((cov['unrepresented_instructions'],cov['unrepresented_ranges']),(0,[]))
                self.assertEqual(cov['map_size'],a.MAP_SIZES.get(int(cov['entry'],16)))

    def test_identical_results_and_exact_physical_spans(self):
        self.assertEqual([r['snapshot'] for r in self.results],['db.3.gbf','db.4.gbf'])
        for key in ('ranges','constants','mappings','function_coverage','recorded_bases','float_preconditions','reused_evidence'):
            self.assertEqual(self.results[0][key],self.results[1][key])
        for result in self.results:
            for key in ('ranges','constants'):
                for item in result[key]:self.assertEqual(item['spans'],PHYSICAL[item['address']])
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            self.assertEqual(result['data5_sha256'],a.c.DATA5_SHA)
            self.assertEqual(result['executable_sha256_property_type'],2)

    def test_prior_fixed_witnesses_still_identical(self):
        self.assertEqual(self.reused[0],self.reused[1])
        for reuse in self.reused:
            self.assertEqual(len(reuse),len(a.REUSED_RANGES)+len(a.REUSED_CONSTANTS))
            for item,(_,pc,width,digest) in zip(reuse,a.REUSED_RANGES):
                self.assertEqual((item['address'],item['width'],item['sha256']),(f'{pc:08x}',width,digest))
            for item,(_,pc,bits) in zip(reuse[len(a.REUSED_RANGES):],a.REUSED_CONSTANTS):
                self.assertEqual((item['address'],item['bits']),(f'{pc:08x}',bits))

    def test_literal_selections_only(self):
        for result in self.results:
            self.assertEqual([r['address'] for r in result['ranges']],[f'{pc:08x}' for pc,_,_ in a.RANGES])
            self.assertEqual([r['address'] for r in result['constants']],[f'{pc:08x}' for pc,_,_ in a.CONSTANTS])
            self.assertNotIn('raw',json.dumps(result))
            self.assertEqual(sum(r['width'] for k in ('ranges','constants') for r in result[k]),1416)


if __name__=='__main__':unittest.main()
