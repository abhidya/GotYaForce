#!/usr/bin/env python3
"""Fixed literal operand fixture and independent bit inverse for target dispatch.

No test-time fixture generation from reader output, original execution, runtime
or estimator imports. Existing local snapshots are optional and never fetched.
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

import read_archived_target_dispatch_evidence as a

INVENTORY = (
    (0x8006b7f4,92,'227945853f20b8b08ef9f71c6dde02a0ea8136652eb1e4e5d034fdab962d5b12'),
    (0x8006b850,528,'8a01e4c3f1a21269d2b9fb98b2d6c71ab2d46859d9670049069db7c6eafabb51'),
)
TEXT_MAPPING = (0x800055e0,0x802b0160,1,'MAIN_.text1',1,2796416,21)
DATA3_MAPPING = (0x802bae60,0x803af120,5,'MAIN_.data3',5,1000128,199)
EXPECTED_READS = [(21,418324,92,2796416),(21,418416,528,2796416)]
CELL_ADDRESS,CELL_WIDTH,CELL_TARGET = 0x802d39a0,4,0x8006b850
CELL_DIGEST = 'a1f65fe8b7d29bda8e482aabf099797030ea8959dbd1559665487fb793a5b9ad'
CELL_BYTES = struct.pack('>I',CELL_TARGET)
ALL_READS = EXPECTED_READS+[(199,101184,4,1000128)]
# Fixed operands from the first bounded inspections, never read from an output
# report at test runtime. The independent inverse below reconstructs each bit.
ASSEMBLY = '''
8006b7f4 stwu 1 1 -16
8006b7f8 mflr 0
8006b7fc stw 0 1 20
8006b800 lbz 0 3 0
8006b804 extsb 0 0 1
8006b808 bc 4 2 8006b820
8006b80c addi 0 0 0
8006b810 stb 0 3 1282
8006b814 stw 0 3 1288
8006b818 stw 0 3 1284
8006b81c b 8006b840
8006b820 lbz 0 3 1282
8006b824 addis 4 0 -32723
8006b828 addi 4 4 14752
8006b82c extsb 0 0 0
8006b830 rlwinm 0 0 2 0 29 0
8006b834 lwzx 12 4 0
8006b838 mtctr 12
8006b83c bctrl 20 0 0 1
8006b840 lwz 0 1 20
8006b844 mtlr 0
8006b848 addi 1 1 16
8006b84c blr 20 0 0 0
8006b850 stwu 1 1 -64
8006b854 mflr 0
8006b858 stw 0 1 68
8006b85c stfd 31 1 48
8006b860 psq_st 31 1 56 0 0
8006b864 stmw 27 1 28
8006b868 or 3 30 3 0
8006b86c lbz 0 3 1855
8006b870 extsb 0 0 1
8006b874 bc 4 2 8006ba44
8006b878 lhz 4 13 -21342
8006b87c addis 3 0 -32708
8006b880 addi 0 0 0
8006b884 addi 6 3 7548
8006b888 stw 0 13 -21504
8006b88c mtctr 4
8006b890 cmpi 4 0
8006b894 bc 4 1 8006b918
8006b898 lwz 7 6 0
8006b89c cmpli 7 0
8006b8a0 bc 12 2 8006b910
8006b8a4 lwz 5 7 32
8006b8a8 cmpli 5 0
8006b8ac bc 12 2 8006b910
8006b8b0 lbz 0 5 0
8006b8b4 extsb 0 0 1
8006b8b8 bc 12 2 8006b910
8006b8bc cmpl 30 5
8006b8c0 bc 12 2 8006b910
8006b8c4 lbz 0 30 136
8006b8c8 lbz 4 5 136
8006b8cc extsb 0 3 0
8006b8d0 extsb 4 0 0
8006b8d4 cmp 3 0
8006b8d8 bc 12 2 8006b910
8006b8dc cmpi 0 4
8006b8e0 bc 12 2 8006b910
8006b8e4 lbz 0 5 24
8006b8e8 extsb 0 0 0
8006b8ec cmpi 0 2
8006b8f0 bc 4 0 8006b910
8006b8f4 lwz 5 13 -21504
8006b8f8 addis 3 0 -32709
8006b8fc addi 3 3 8712
8006b900 addi 4 5 1
8006b904 rlwinm 5 0 2 0 29 0
8006b908 stw 4 13 -21504
8006b90c stwx 7 3 0
8006b910 addi 6 6 4
8006b914 bc 16 0 8006b898
8006b918 lwz 0 13 -21504
8006b91c cmpi 0 0
8006b920 bc 12 2 8006ba44
8006b924 lwz 5 30 1200
8006b928 addis 3 0 -32709
8006b92c addi 4 3 8712
8006b930 addi 3 1 8
8006b934 lbz 0 5 16
8006b938 lwz 4 4 0
8006b93c extsb 0 0 0
8006b940 mulli 0 0 48
8006b944 or 4 31 4 0
8006b948 addi 4 4 100
8006b94c add 5 30 0 0
8006b950 lfs 0 5 2272
8006b954 stfs 0 1 8
8006b958 lfs 0 5 2288
8006b95c stfs 0 1 12
8006b960 lfs 0 5 2304
8006b964 stfs 0 1 16
8006b968 bl 8020bc88
8006b96c addis 3 0 -32709
8006b970 fmr 31 1
8006b974 addi 3 3 8712
8006b978 addi 28 0 1
8006b97c addi 29 3 4
8006b980 b 8006b9ac
8006b984 lwz 27 29 0
8006b988 addi 3 1 8
8006b98c addi 4 27 100
8006b990 bl 8020bc88
8006b994 fcmpo 1 31
8006b998 bc 12 1 8006b9a4
8006b99c or 27 31 27 0
8006b9a0 fmr 31 1
8006b9a4 addi 29 29 4
8006b9a8 addi 28 28 1
8006b9ac lwz 5 13 -21504
8006b9b0 cmp 28 5
8006b9b4 bc 12 0 8006b984
8006b9b8 lwz 6 31 32
8006b9bc cmpli 6 0
8006b9c0 bc 12 2 8006ba18
8006b9c4 lwz 3 31 40
8006b9c8 lhz 0 3 2
8006b9cc rlwinm 0 0 0 22 22 1
8006b9d0 bc 4 2 8006ba18
8006b9d4 addis 3 0 -32709
8006b9d8 addi 4 3 8712
8006b9dc mtctr 5
8006b9e0 cmpi 5 0
8006b9e4 bc 4 1 8006ba18
8006b9e8 lwz 5 4 0
8006b9ec lwz 0 5 32
8006b9f0 cmpl 6 0
8006b9f4 bc 4 2 8006ba10
8006b9f8 lwz 3 5 40
8006b9fc lhz 0 3 2
8006ba00 rlwinm 0 0 0 22 22 1
8006ba04 bc 12 2 8006ba10
8006ba08 or 5 31 5 0
8006ba0c b 8006ba18
8006ba10 addi 4 4 4
8006ba14 bc 16 0 8006b9e8
8006ba18 addi 0 0 1
8006ba1c stb 0 30 1282
8006ba20 stw 31 30 1284
8006ba24 lwz 0 31 32
8006ba28 stw 0 30 1288
8006ba2c lwz 3 31 100
8006ba30 lwz 0 31 104
8006ba34 stw 3 30 1292
8006ba38 stw 0 30 1296
8006ba3c lwz 0 31 108
8006ba40 stw 0 30 1300
8006ba44 psq_l 31 1 56 0 0
8006ba48 lfd 31 1 48
8006ba4c lmw 27 1 28
8006ba50 lwz 0 1 68
8006ba54 mtlr 0
8006ba58 addi 1 1 64
8006ba5c blr 20 0 0 0
'''

D_FORMS = {'lwz': (32, 'rD'), 'lbz': (34, 'rD'), 'stw': (36, 'rS'), 'stwu': (37, 'rS'),
           'stb': (38, 'rS'), 'lhz': (40, 'rD'), 'lmw': (46, 'rD'), 'stmw': (47, 'rS'),
           'lfs': (48, 'fD'), 'lfd': (50, 'fD'), 'stfs': (52, 'fS'), 'stfd': (54, 'fS')}


def parse_fixture():
    result = []
    for line in ASSEMBLY.strip().splitlines():
        pc, name, *args = line.split()
        values = [int(arg) for arg in args] if name not in ('bc', 'b', 'bl') else []
        fields = {
            'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS',
            'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'mulli': 'rD rA immediate',
            'ori': 'rS rA immediate', 'oris': 'rS rA immediate', 'extsb': 'rS rA Rc',
            'or': 'rS rA rB Rc', 'add': 'rD rA rB Rc', 'rlwinm': 'rS rA SH MB ME Rc',
            'cmp': 'rA rB', 'cmpl': 'rA rB', 'cmpi': 'rA immediate', 'cmpli': 'rA immediate',
            'fcmpo': 'fA fB', 'fmr': 'fD fB', 'lwzx': 'rD rA rB', 'stwx': 'rS rA rB',
            'psq_st': 'fS rA displacement W I', 'psq_l': 'fD rA displacement W I',
            'blr': 'BO BI BH LK', 'bctr': 'BO BI BH LK', 'bctrl': 'BO BI BH LK',
        }
        if name in D_FORMS: fields[name] = D_FORMS[name][1] + ' rA displacement'
        row = dict(mnemonic=name)
        if name == 'bc': row.update(BO=int(args[0]), BI=int(args[1]), target=args[2], AA=0, LK=0)
        elif name in ('b', 'bl'): row.update(target=args[0], AA=0, LK=int(name == 'bl'))
        else:
            keys = fields[name].split(); assert len(keys) == len(values), line
            row.update(zip(keys, values))
        if name in ('cmp', 'cmpl', 'cmpi', 'cmpli'): row.update(BF=0, L=0)
        if name == 'fcmpo': row.update(BF=0)
        result.append(dict(address=pc, **row))
    return result


def encode(row, pc):
    """Independent PPC bit placement, never calling the reader's decoder."""
    name = row['mnemonic']
    if name in D_FORMS:
        op, reg = D_FORMS[name]
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['displacement'] & 65535
    if name in ('psq_st', 'psq_l'):
        op, reg = (60, 'fS') if name == 'psq_st' else (56, 'fD')
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['W'] << 15 | row['I'] << 12 | row['displacement'] & 4095
    if name in ('addi', 'addis', 'mulli', 'ori', 'oris'):
        op, reg = {'addi': (14, 'rD'), 'addis': (15, 'rD'), 'mulli': (7, 'rD'), 'ori': (24, 'rS'), 'oris': (25, 'rS')}[name]
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name in ('cmpi', 'cmpli'):
        return (11 if name == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name in ('cmp', 'cmpl'):
        return 31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['rB'] << 11 | (32 if name == 'cmpl' else 0) << 1
    if name == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    if name == 'extsb': return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | 954 << 1 | row['Rc']
    if name in ('or', 'add'):
        return 31 << 26 | row['rD' if name == 'add' else 'rS'] << 21 | row['rA'] << 16 | row['rB'] << 11 | (444 if name == 'or' else 266) << 1 | row['Rc']
    if name in ('lwzx', 'stwx'):
        return 31 << 26 | row['rD' if name == 'lwzx' else 'rS'] << 21 | row['rA'] << 16 | row['rB'] << 11 | (23 if name == 'lwzx' else 151) << 1
    if name in ('mflr', 'mtlr', 'mtctr'):
        reg, spr, xo = ('rD', 8, 339) if name == 'mflr' else ('rS', 8 if name == 'mtlr' else 9, 467)
        return 31 << 26 | row[reg] << 21 | (spr & 31) << 16 | (spr >> 5) << 11 | xo << 1
    if name == 'bc': return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | (int(row['target'], 16) - pc) & 65532 | row['AA'] << 1 | row['LK']
    if name in ('b', 'bl'): return 18 << 26 | (int(row['target'], 16) - pc) & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name in ('blr', 'bctr', 'bctrl'): return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | (16 if name == 'blr' else 528) << 1 | row['LK']
    if name == 'fcmpo': return 63 << 26 | row['BF'] << 23 | row['fA'] << 16 | row['fB'] << 11 | 32 << 1
    if name == 'fmr': return 63 << 26 | row['fD'] << 21 | row['fB'] << 11 | 72 << 1
    raise AssertionError(name)


ALL_EXPECTED = parse_fixture()
EXPECTED = {pc: [r for r in ALL_EXPECTED if pc <= int(r['address'],16) < pc+width] for pc,width,_ in INVENTORY}
BODIES = {pc: b''.join(struct.pack('>I', encode(row, int(row['address'], 16))) for row in EXPECTED[pc]) for pc,_,_ in INVENTORY}


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args): self.calls.append(args); return self.raw, []

class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_source_boundaries_and_honest_map_ceiling(self):
        self.assertEqual(a.RANGES,INVENTORY)
        self.assertEqual((a.TEXT_MAPPING,a.DATA3_MAPPING),(TEXT_MAPPING,DATA3_MAPPING))
        self.assertEqual(a.CELL,(CELL_ADDRESS,CELL_WIDTH,CELL_TARGET,CELL_DIGEST))
        self.assertEqual(len(ALL_EXPECTED),155)
        root=Path(__file__).resolve().parents[3]
        index=(root/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols=(root/'research/symbols/GG4E-CSM-20220412.map').read_text().splitlines()
        source=(root/'research/decomp/ghidra-export/chunk_0009.c').read_text().splitlines()
        self.assertEqual(index[1392:1395],['8006b7f4\tzz_006b7f4_\tchunk_0009.c','8006b850\tFUN_8006b850\tchunk_0009.c','8006ba60\tFUN_8006ba60\tchunk_0009.c'])
        self.assertEqual(symbols[835],'8006b7f4 0000005c 8006b7f4 0 zz_006b7f4_')
        self.assertFalse(any(row.startswith(('8006b850 ','8006ba60 ')) for row in symbols))
        for start,end,marker in [(1586,1606,'// ==== 8006b7f4  zz_006b7f4_ ===='),(1610,1687,'// ==== 8006b850  FUN_8006b850 ====')]:
            self.assertEqual(source[start-1],marker);self.assertEqual(source[end-1],'}')
        for pc,width,_ in INVENTORY:
            self.assertEqual([r['address'] for r in EXPECTED[pc]],[f'{p:08x}' for p in range(pc,pc+width,4)])

    def test155_operands_inverse_and4960_instruction_bit_controls(self):
        count=0
        for pc,width,digest in INVENTORY:
            body=BODIES[pc]
            self.assertEqual((len(body),hashlib.sha256(body).hexdigest()),(width,digest))
            self.assertEqual(a.range_evidence(FakeDB(body),TEXT_MAPPING,pc,width)['instructions'],EXPECTED[pc])
            for original in EXPECTED[pc]:
                address=int(original['address'],16);row={k:v for k,v in original.items() if k!='address'}
                word=encode(row,address)
                self.assertEqual(a.decode_selected(word,address),row)
                for bit in range(32):
                    count+=1;changed=word ^ 1<<bit
                    try: decoded=a.decode_selected(changed,address)
                    except a.c.FormatError: continue
                    if decoded is not None:
                        self.assertNotEqual(decoded,row,(hex(address),bit))
                        self.assertEqual(encode(decoded,address),changed,(hex(address),bit))
        self.assertEqual(count,4960)

    def test4960_payload_mutations_refused_before_decode_and_exact_reads(self):
        count=0
        for (pc,width,_),expected in zip(INVENTORY,EXPECTED_READS):
            body=BODIES[pc];db=FakeDB(body)
            a.range_evidence(db,TEXT_MAPPING,pc,width);self.assertEqual(db.calls,[expected])
            with patch.object(a,'decode_selected') as decode:
                for index in range(width):
                    for bit in range(8):
                        changed=body[:index]+bytes([body[index]^1<<bit])+body[index+1:]
                        with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'):
                            a.range_evidence(FakeDB(changed),TEXT_MAPPING,pc,width)
                        count+=1
                decode.assert_not_called()
        self.assertEqual(count,4960)

    def test_cell_inverse32_bit_refusals_and_target_control(self):
        self.assertEqual(hashlib.sha256(CELL_BYTES).hexdigest(),CELL_DIGEST)
        db=FakeDB(CELL_BYTES);row=a.cell_evidence(db,DATA3_MAPPING,CELL_ADDRESS,CELL_WIDTH)
        self.assertEqual(db.calls,[ALL_READS[-1]])
        self.assertEqual((row['target'],row['signed_index']),('8006b850',0))
        with patch.object(a.c,'integer') as integer:
            for bit in range(32):
                changed=struct.pack('>I',CELL_TARGET^1<<bit)
                with self.assertRaisesRegex(a.c.FormatError,'cell digest mismatch'):
                    a.cell_evidence(FakeDB(changed),DATA3_MAPPING,CELL_ADDRESS,CELL_WIDTH)
            integer.assert_not_called()
        with patch.object(a,'CELL',(CELL_ADDRESS,4,CELL_TARGET+4,CELL_DIGEST)):
            with self.assertRaisesRegex(a.c.FormatError,'cell target mismatch'):
                a.cell_evidence(FakeDB(CELL_BYTES),DATA3_MAPPING,CELL_ADDRESS,4)

    def test_complete_flow_metadata_mutations_rejected(self):
        count=0;controls=[]
        for pc,width,_ in INVENTORY:
            body=BODIES[pc]
            controls.extend(r for r in EXPECTED[pc] if r['mnemonic'] in a.FLOW_NAMES)
            for original in EXPECTED[pc]:
                if original['mnemonic'] not in a.FLOW_NAMES: continue
                for field,value in original.items():
                    if field=='address': continue
                    changed={k:v for k,v in original.items() if k!='address'}
                    changed[field]=value+1 if type(value) is int else 'bad'
                    decode=a.decode_selected
                    def corrupted(word,address):
                        return changed if address==int(original['address'],16) else decode(word,address)
                    with patch.object(a,'decode_selected',corrupted):
                        with self.assertRaisesRegex(a.c.FormatError,'control-flow mismatch'):
                            a.range_evidence(FakeDB(body),TEXT_MAPPING,pc,width)
                    count+=1
        self.assertEqual(len(controls),28)
        self.assertEqual(count,155)
        self.assertEqual([(r['address'],r['target']) for r in controls if r['mnemonic']=='bl'],[('8006b968','8020bc88'),('8006b990','8020bc88')])

    def test_dispatch_signed_index_actor_argument_and_word_clear_order(self):
        rows={int(r['address'],16):r for r in EXPECTED[0x8006b7f4]}
        self.assertEqual([(rows[p]['mnemonic'],rows[p]['displacement']) for p in (0x8006b810,0x8006b814,0x8006b818)],[('stb',0x502),('stw',0x508),('stw',0x504)])
        self.assertEqual((rows[0x8006b804]['mnemonic'],rows[0x8006b804]['Rc']),('extsb',1))
        self.assertEqual((rows[0x8006b808]['BO'],rows[0x8006b808]['BI'],rows[0x8006b808]['target']),(4,2,'8006b820'))
        self.assertEqual(rows[0x8006b820]['displacement'],0x502)
        self.assertEqual(rows[0x8006b82c]['mnemonic'],'extsb')
        self.assertEqual((rows[0x8006b830]['SH'],rows[0x8006b830]['MB'],rows[0x8006b830]['ME']),(2,0,29))
        self.assertEqual(((rows[0x8006b824]['immediate']<<16)+rows[0x8006b828]['immediate'])&0xffffffff,CELL_ADDRESS)
        self.assertEqual(rows[0x8006b834],dict(address='8006b834',mnemonic='lwzx',rD=12,rA=4,rB=0))
        self.assertEqual((rows[0x8006b838]['rS'],rows[0x8006b83c]['mnemonic']),(12,'bctrl'))
        # No source instruction changes r3 before the indirect call; it remains actor.
        self.assertFalse(any(r.get('rD')==3 for p,r in rows.items() if p<0x8006b83c))
        self.assertEqual([r['address'] for r in rows.values() if r['mnemonic']=='bc'],['8006b808'])
        addresses=[]
        for byte in range(256):
            signed=byte if byte<128 else byte-256
            addresses.append((CELL_ADDRESS+4*signed)&0xffffffff)
        self.assertEqual((min(addresses),max(addresses)),(CELL_ADDRESS-512,CELL_ADDRESS+508))
        self.assertEqual(addresses[128],0x802d37a0)
        # Reachable address arithmetic is NOT an authorized selection/table extent.
        self.assertEqual(a.CELL[:2],(CELL_ADDRESS,4))

    def test_housekeeping_guard_zero_count_read_reset_reload_and_full_return(self):
        rows={int(r['address'],16):r for r in EXPECTED[0x8006b850]}
        self.assertEqual(rows[0x8006b86c]['displacement'],0x73f)
        self.assertEqual(rows[0x8006b870]['Rc'],1)
        self.assertEqual(rows[0x8006b874]['target'],'8006ba44')
        self.assertEqual((rows[0x8006b878]['mnemonic'],rows[0x8006b878]['rA'],rows[0x8006b878]['displacement']),('lhz',13,-21342))
        self.assertEqual((rows[0x8006b888]['mnemonic'],rows[0x8006b888]['rA'],rows[0x8006b888]['displacement']),('stw',13,-21504))
        self.assertEqual((rows[0x8006b894]['BO'],rows[0x8006b894]['BI'],rows[0x8006b894]['target']),(4,1,'8006b918'))
        self.assertEqual((rows[0x8006b918]['mnemonic'],rows[0x8006b918]['displacement']),('lwz',-21504))
        self.assertEqual((rows[0x8006b920]['BO'],rows[0x8006b920]['BI'],rows[0x8006b920]['target']),(12,2,'8006ba44'))
        # Straight guarded path skips every object/scratch-list payload load.
        zero_path=list(range(0x8006b850,0x8006b898,4))+list(range(0x8006b918,0x8006b924,4))+list(range(0x8006ba44,0x8006ba60,4))
        payload_reads=[(rows[p]['mnemonic'],rows[p].get('rA'),rows[p].get('displacement')) for p in zero_path if rows[p]['mnemonic'] in ('lwz','lbz','lhz') and rows[p].get('rA')!=1]
        self.assertEqual(payload_reads,[('lbz',3,0x73f),('lhz',13,-21342),('lwz',13,-21504)])
        self.assertEqual([rows[p]['mnemonic'] for p in range(0x8006ba44,0x8006ba60,4)],['psq_l','lfd','lmw','lwz','mtlr','addi','blr'])
        self.assertEqual(rows[0x8006b860]['mnemonic'],'psq_st')
        pending,reached=[0x8006b850],set()
        while pending:
            pc=pending.pop()
            if pc in reached: continue
            reached.add(pc);r=rows[pc]
            if r['mnemonic']=='blr': continue
            if r['mnemonic'] in ('bc','b'): pending.append(int(r['target'],16))
            if r['mnemonic']!='b': pending.append(pc+4)
        self.assertEqual(reached,set(rows))

    def test_scan_nearest_unordered_redirect_and_commit_order(self):
        rows={int(r['address'],16):r for r in EXPECTED[0x8006b850]}
        self.assertEqual((rows[0x8006b908]['mnemonic'],rows[0x8006b90c]['mnemonic']),('stw','stwx'))
        self.assertEqual((rows[0x8006b8ec]['immediate'],rows[0x8006b8f0]['BO'],rows[0x8006b8f0]['BI']),(2,4,0))
        self.assertEqual([rows[p]['mnemonic'] for p in range(0x8006b950,0x8006b96c,4)],['lfs','stfs','lfs','stfs','lfs','stfs','bl'])
        self.assertEqual((rows[0x8006b998]['BO'],rows[0x8006b998]['BI']),(12,1))
        self.assertEqual(rows[0x8006b9ac]['displacement'],-21504)
        self.assertEqual((rows[0x8006b9b8]['displacement'],rows[0x8006b9c4]['displacement'],rows[0x8006b9c8]['displacement']),(0x20,0x28,2))
        self.assertEqual((rows[0x8006b9cc]['MB'],rows[0x8006ba00]['MB']),(22,22))
        self.assertEqual([(rows[p]['mnemonic'],rows[p].get('displacement')) for p in range(0x8006ba1c,0x8006ba44,4)],
            [('stb',0x502),('stw',0x504),('lwz',0x20),('stw',0x508),('lwz',0x64),('lwz',0x68),('stw',0x50c),('stw',0x510),('lwz',0x6c),('stw',0x514)])

    def test_candidate_scan_register_order_signed_gates_and_original_pointer_store(self):
        rows={int(r['address'],16):r for r in EXPECTED[0x8006b850]}
        loads=[(r['address'],r['mnemonic'],r.get('rD'),r.get('rA'),r.get('displacement'))
               for r in EXPECTED[0x8006b850] if 0x8006b898<=int(r['address'],16)<0x8006b918 and r['mnemonic'] in ('lwz','lbz','lhz')]
        self.assertEqual(loads,[('8006b898','lwz',7,6,0),('8006b8a4','lwz',5,7,0x20),
            ('8006b8b0','lbz',0,5,0),('8006b8c4','lbz',0,30,0x88),
            ('8006b8c8','lbz',4,5,0x88),('8006b8e4','lbz',0,5,0x18),
            ('8006b8f4','lwz',5,13,-21504)])
        self.assertEqual((rows[0x8006b8bc]['mnemonic'],rows[0x8006b8bc]['rA'],rows[0x8006b8bc]['rB']),('cmpl',30,5))
        self.assertEqual((rows[0x8006b8cc]['rS'],rows[0x8006b8cc]['rA']), (0,3))
        self.assertEqual((rows[0x8006b8d0]['rS'],rows[0x8006b8d0]['rA']), (4,0))
        self.assertEqual((rows[0x8006b8d4]['rA'],rows[0x8006b8d4]['rB']), (3,0))
        self.assertEqual((rows[0x8006b8dc]['rA'],rows[0x8006b8dc]['immediate']), (0,4))
        self.assertEqual(rows[0x8006b8e8]['mnemonic'],'extsb')
        self.assertEqual((rows[0x8006b8f0]['BO'],rows[0x8006b8f0]['BI'],rows[0x8006b8f0]['target']), (4,0,'8006b910'))
        admitted=[raw for raw in range(256) if (raw if raw<128 else raw-256)<2]
        self.assertEqual(admitted,[0,1]+list(range(128,256)))
        self.assertEqual((rows[0x8006b900]['rD'],rows[0x8006b900]['rA'],rows[0x8006b900]['immediate']), (4,5,1))
        self.assertEqual((rows[0x8006b904]['rS'],rows[0x8006b904]['rA'],rows[0x8006b904]['SH']), (5,0,2))
        self.assertEqual((rows[0x8006b908]['rS'],rows[0x8006b908]['rA'],rows[0x8006b908]['displacement']), (4,13,-21504))
        self.assertEqual((rows[0x8006b90c]['rS'],rows[0x8006b90c]['rA'],rows[0x8006b90c]['rB']), (7,3,0))
        # r7 remains the original list object. r5 became actor, then old count.
        writes7=[r['address'] for r in EXPECTED[0x8006b850] if 0x8006b898<=int(r['address'],16)<=0x8006b90c and r.get('rD')==7]
        self.assertEqual(writes7,['8006b898'])
        self.assertEqual((rows[0x8006b88c]['mnemonic'],rows[0x8006b88c]['rS']),('mtctr',4))
        self.assertEqual((rows[0x8006b914]['BO'],rows[0x8006b914]['BI'],rows[0x8006b914]['target']), (16,0,'8006b898'))
        self.assertEqual((rows[0x8006b910]['rD'],rows[0x8006b910]['rA'],rows[0x8006b910]['immediate']), (6,6,4))

    def test_invalid_ranges_widths_mappings_and_decoder_bounds(self):
        for pc,width,_ in INVENTORY:
            for address,size in [(bad,width) for bad in (pc-4,pc+4,pc+1,float(pc),True,-1,1<<32,CELL_ADDRESS)]+[(pc,bad) for bad in (0,width-4,width+4,-width,True,float(width))]:
                db=FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db,TEXT_MAPPING,address,size)
                self.assertFalse(db.calls)
            for raw in (BODIES[pc][:-1],BODIES[pc]+b'\0'):
                with self.assertRaisesRegex(a.c.FormatError,'byte width'): a.range_evidence(FakeDB(raw),TEXT_MAPPING,pc,width)
            with patch.object(a,'RANGES',a.RANGES*2):
                db=FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db,TEXT_MAPPING,pc,width)
                self.assertFalse(db.calls)
            with patch.object(a,'decode_selected',return_value=None):
                with self.assertRaisesRegex(a.c.FormatError,'unselected instruction'):a.range_evidence(FakeDB(BODIES[pc]),TEXT_MAPPING,pc,width)
        for address,width in [(bad,4) for bad in (CELL_ADDRESS-4,CELL_ADDRESS+4,float(CELL_ADDRESS),True)]+[(CELL_ADDRESS,bad) for bad in (0,8,True,4.0)]:
            db=FakeDB(CELL_BYTES)
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,DATA3_MAPPING,address,width)
            self.assertFalse(db.calls)
        for raw in (CELL_BYTES[:-1],CELL_BYTES+b'\0'):
            with self.assertRaisesRegex(a.c.FormatError,'byte width'):a.cell_evidence(FakeDB(raw),DATA3_MAPPING,CELL_ADDRESS,4)
        for mapping,call,raw,pc,width in ((TEXT_MAPPING,a.range_evidence,BODIES[0x8006b7f4],0x8006b7f4,92),(DATA3_MAPPING,a.cell_evidence,CELL_BYTES,CELL_ADDRESS,4)):
            variants=[list(mapping)]
            for index,value in enumerate(mapping):
                for replacement in (value+1,float(value)) if type(value) is int else ('wrong',):
                    changed=list(mapping);changed[index]=replacement;variants.append(tuple(changed))
            for changed in variants:
                db=FakeDB(raw)
                with self.assertRaises(a.c.FormatError):call(db,changed,pc,width)
                self.assertFalse(db.calls)
        for word,pc in ((True,0),(-1,0),(1<<32,0),(0,True),(0,1),(0,-4),(0,1<<32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,pc)

    def test_authentication_precedes_parser_and_all_selection(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('auth stop')) as auth,patch.object(a.c,'GBF') as db,patch.object(a,'range_evidence') as code,patch.object(a,'cell_evidence') as cell:
            with self.assertRaisesRegex(a.c.FormatError,'auth stop'): a.inspect(b'bad','bad')
            auth.assert_called_once_with(b'bad','bad');db.assert_not_called();code.assert_not_called();cell.assert_not_called()

    def test_mapping_refusal_precedes_selection(self):
        blocks,subs={},{}
        for name,key,start,length,root in a.command.MAPPINGS:
            blocks[key]=[name,None,None,15,start,length,0];subs[key]=[key,2,length,0,root,0]
        cases=[]
        for key in (1,5,7):
            for field,value in ((0,'wrong'),(4,blocks[key][4]+4),(5,blocks[key][5]+4),(6,1)):
                bb,ss=copy.deepcopy((blocks,subs));bb[key][field]=value;cases.append((bb,ss,'80000000'))
            for field in range(6):
                bb,ss=copy.deepcopy((blocks,subs));ss[key][field]+=1;cases.append((bb,ss,'80000000'))
            bb,ss=copy.deepcopy((blocks,subs));bb[99]=copy.deepcopy(bb[key]);cases.append((bb,ss,'80000000'))
            bb,ss=copy.deepcopy((blocks,subs));ss[99]=copy.deepcopy(ss[key]);cases.append((bb,ss,'80000000'))
            for kind in ('block','sub'):
                bb,ss=copy.deepcopy((blocks,subs));del (bb if kind=='block' else ss)[key];cases.append((bb,ss,'80000000'))
        cases.append((blocks,subs,'80000004'));self.assertEqual(len(cases),43)
        for bb,ss,image in cases:
            with patch.object(a.c,'inspect',return_value={'image_offset':image}),patch.object(a.c,'GBF') as db,patch.object(a,'range_evidence') as code,patch.object(a,'cell_evidence') as cell:
                db.return_value.tables.return_value={'Memory Blocks':'b','Sub Memory Blocks':'s'}
                db.return_value.rows.side_effect=lambda key:{'b':bb,'s':ss}[key]
                with self.assertRaises(a.c.FormatError):a.inspect(b'synthetic','synthetic')
                code.assert_not_called();cell.assert_not_called()

    def test_no_arbitrary_cli_and_missing_snapshot(self):
        for option in ('--address','--width','--pointer','--target','--table','--dump','--state'):
            with patch('sys.argv',['reader','none',option,'0']),contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc:a.main()
                self.assertEqual(exc.exception.code,2)
        with patch('sys.argv',['reader','/nonexistent/target.gbf']),contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(),1);self.assertIn('not a regular file',json.loads(error.getvalue())['error'])


SNAPSHOT_DIR=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR/name).is_file() for name in ('db.3.gbf','db.4.gbf')),'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports,cls.reads,cls.auth_reads=[],[],[]
        original=a.c.GBF.chain
        for name in ('db.3.gbf','db.4.gbf'):
            raw=(SNAPSHOT_DIR/name).read_bytes();digest=hashlib.sha256(raw).hexdigest();reads=[]
            def traced(db,*args):reads.append(args);return original(db,*args)
            with patch.object(a.c.GBF,'chain',traced):a.c.inspect(raw,digest)
            cls.auth_reads.append(reads[:]);reads.clear()
            with patch.object(a.c.GBF,'chain',traced):cls.reports.append(a.inspect(raw,digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_exact_operands_cell_coverage_ceiling(self):
        for key in ('mappings','ranges','cell','function_coverage','selection_basis'):
            self.assertEqual(self.reports[0][key],self.reports[1][key],key)
        self.assertEqual([r['snapshot'] for r in self.reports],['db.3.gbf','db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports],['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0','1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'],dict(version=0,root=-1,count=0))
            for row,(pc,width,_) in zip(report['ranges'],INVENTORY):self.assertEqual(row['instructions'],EXPECTED[pc])
            self.assertEqual(report['cell']['target'],'8006b850')
            basis=report['selection_basis'];self.assertEqual((basis['reads'],basis['bytes'],basis['selected_code_bytes'],basis['selected_data_cells']),(3,624,620,1))
            for key in ('pointer_driven_reads','global_payloads_read','globals_runtime_values_established','original_execution','constants_selected','estimator_imported','table_extent_established'):
                self.assertFalse(basis[key])
            self.assertEqual(basis['selected_signed_indices'],[0])
            self.assertEqual([r['map_size'] for r in report['function_coverage']],[92,None])
            self.assertEqual([r['represented_instructions'] for r in report['function_coverage']],[23,132])
            self.assertIn('not original-DOL identity',report['caveat'])
            self.assertIn('not map-size-proven',report['caveat'])

    def test_exact_three_selected_reads_after_unchanged_authentication(self):
        for reads,auth in zip(self.reads,self.auth_reads):
            self.assertEqual(reads,auth+ALL_READS);self.assertTrue(auth)
            self.assertTrue(all(row[0]==263 for row in auth))

    def test_physical_spans_and_no_raw_output(self):
        for report in self.reports:
            for row,chain,data,physical,width in zip(report['ranges'],(418324,418416),(8874,8966),(795312,795404),(92,528)):
                self.assertEqual(row['spans'],[dict(root_buffer=21,data_buffer=47,chain_offset=chain,data_offset=data,length=width,obfuscated=True,physical_offset=physical)])
                self.assertEqual(set(row),{'address','end_exclusive','width','sha256','spans','instructions'})
                self.assertFalse(any('word' in item or 'bytes' in item for item in row['instructions']))
            self.assertEqual(report['cell']['spans'],[dict(root_buffer=199,data_buffer=206,chain_offset=101184,data_offset=2916,length=4,obfuscated=True,physical_offset=3394410)])
            self.assertEqual(report['cell']['end_exclusive'],'802d39a4')

    def test_snapshot_hash_schema_and_each_selected_payload_refuse(self):
        raw=(SNAPSHOT_DIR/'db.3.gbf').read_bytes();digest=hashlib.sha256(raw).hexdigest()
        with patch.object(a,'range_evidence') as code,patch.object(a,'cell_evidence') as cell:
            for changed,claimed in ((raw,'0'*64),(raw[:-1]+bytes([raw[-1]^1]),digest)):
                with self.assertRaisesRegex(a.c.FormatError,'SHA256 not allowlisted'):a.inspect(changed,claimed)
            code.assert_not_called();cell.assert_not_called()
        original_tables=a.c.GBF.tables
        for name in ('Program','Property Table','File Bytes','ADDRESS MAP','Memory Blocks','Sub Memory Blocks'):
            for field in ('version','keytype','types','fields','missing'):
                def changed_tables(db):
                    tables=copy.deepcopy(original_tables(db))
                    if field=='missing':del tables[name]
                    elif field=='types':tables[name][field]=[99]
                    elif field=='fields':tables[name][field]='Wrong;'
                    else:tables[name][field]+=1
                    return tables
                with patch.object(a.c.GBF,'tables',changed_tables),patch.object(a,'range_evidence') as code,patch.object(a,'cell_evidence') as cell:
                    with self.assertRaises(a.c.FormatError):a.inspect(raw,digest)
                    code.assert_not_called();cell.assert_not_called()
        original=a.c.GBF.chain
        for target in ALL_READS:
            def tampered(db,*args):
                payload,spans=original(db,*args)
                if args==target:payload=bytes([payload[0]^1])+payload[1:]
                return payload,spans
            with patch.object(a.c.GBF,'chain',tampered):
                with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'):a.inspect(raw,digest)


if __name__=='__main__':unittest.main()
