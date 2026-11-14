#!/usr/bin/env python3
"""Independent126-instruction inverse fixture and526-byte selected mutation checks.

Semantic schedules are frozen manual expectations; tests never generate them
from the reader, decoder, reports or archives. Local archives are optional.
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

import read_archived_object_allocator_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
RANGES = (
    (0x80088d98, 184, 'a134e40d302eb33d6ebc1c3dd371228809562bdc533d833bebf095b19180ab44'),
    (0x80197bec, 20, 'cdcbfde48212824dc444a6b18aab2c256ffdcb4fec35ad9a18b332b9529c0995'),
    (0x80197bd8, 20, '8a8dd5a501652fd1370ed64d05ed17044aada0fa4bf21eecf6b6f13f0809eaea'),
    (0x80197a0c, 204, '96222c5bda44dae9f8bb740618f6f8c5d08d455044410156499752c80db51a82'),
    (0x80006d4c, 52, 'ac9afd93b2bee5eca79b75684fcff6a276cadb29e4509e2d0db46a38c42dc3e2'),
    (0x80006f60, 24, '0070931fd4199aa0583862fedea3296041d962fd44af91ecdc761c907a85f6a0'),
)
CELLS = (
    ('battle-descriptor-root', 0x8036fa1c, 4, '>I', (0x8036f644,), '9013485b6a5daf0c7505ce80059edadf81f64480ebe7c725e1e71ec34f576aa6'),
    ('pool3-type', 0x802da673, 1, '>b', (3,), '084fed08b978af4d7d196a7446a86b58009e636b611db16211b65a9aadff29c5'),
    ('pool3-capacity', 0x802da67e, 2, '>H', (512,), '99be5efb88ca2013bd8e4eb035fd42d5245468fe9afa70d8ba9c1c419a48c4e8'),
    ('descriptor0-stride', 0x8036f654, 2, '>h', (44,), '59b94638773b642b87af5d2478ec16fbeb99d878d318561ce058787ce46bb46e'),
    ('descriptor0-init-callback', 0x8036f658, 4, '>I', (0x80006f60,), '7c9a350375faea6aeb1a90130cee6f8b49293167cabd747aa6d5520705b85a3f'),
    ('object-type3-size', 0x802da666, 2, '>H', (740,), '12edb515547ea77eb8d10532d4901e878a52732d60408d9960513e6946c5e3d5'),
    ('group8-classification', 0x802da708, 1, '>b', (16,), 'c555eab45d08845ae9f10d452a99bfcb06f74a50b988fe7e48dd323789b88ee3'),
    ('groups9-through14-classification', 0x802da709, 6, '>6b', (16, 16, 16, 16, 16, 16), '39dda76eea065c7cb80b4b9b82c279acd5e5aa5f145114a96dddf5e00c4fc46b'),
)
FIELDS = {
    'stwu':'rS rA displacement', 'stw':'rS rA displacement', 'stb':'rS rA displacement',
    'lwz':'rD rA displacement', 'lbz':'rD rA displacement', 'lwzx':'rD rA rB',
    'lhzx':'rD rA rB', 'lhax':'rD rA rB', 'sthx':'rS rA rB', 'stwx':'rS rA rB',
    'addi':'rD rA immediate', 'addis':'rD rA immediate', 'mulli':'rD rA immediate',
    'or':'rS rA rB Rc', 'extsb':'rS rA Rc', 'mflr':'rD', 'mtlr':'rS', 'mtctr':'rS',
    'bl':'target AA', 'b':'target AA', 'bc':'BO BI LK target AA',
    'cmpi':'BF L rA immediate', 'cmpli':'BF L rA immediate',
    'blr':'BO BI BH LK', 'bctrl':'BO BI BH LK', 'rlwinm':'rS rA SH MB ME Rc',
    'add':'rD rA rB Rc',
}


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split(); keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{k: v if k == 'target' else int(v, 0)
                                            for k, v in zip(keys, values)}))
    return result


EXPECTED = {0x80088d98: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
or 3 31 3 0
addis 3 0 -32708
stw 30 1 24
rlwinm 31 7 2 0 29 0
addi 6 3 29036
stw 29 1 20
lwzx 30 6 7
cmpli 0 0 30 0
bc 12 2 0 80088e30 0
addis 3 0 -32708
rlwinm 31 5 1 0 30 0
addi 4 3 29100
lhzx 3 4 5
addi 0 3 -1
sthx 0 4 5
lwz 0 30 4
cmpli 0 0 0 0
stwx 0 6 7
bc 4 2 0 80088e04 0
addis 3 0 -32708
addi 0 0 0
addi 3 3 29068
stwx 0 3 7
lbz 29 30 2
addis 3 0 -32722
addi 5 3 -22944
or 30 3 30 0
extsb 29 0 0
addi 4 0 0
rlwinm 0 0 1 0 30 0
lhzx 5 5 0
bl 8000540c 0
stb 29 30 2
stb 31 30 3
lwz 0 1 36
or 30 3 30 0
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''), 0x80197bec: ops('''
mulli 3 3 28
lwz 4 13 -21024
addi 0 3 18
lhax 3 4 0
blr 20 0 0 0
'''), 0x80197bd8: ops('''
mulli 3 3 28
lwz 5 13 -21024
addi 0 3 18
sthx 4 5 0
blr 20 0 0 0
'''), 0x80197a0c: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
stw 30 1 24
addi 30 0 0
stw 29 1 20
or 3 29 3 0
mulli 0 29 28
lwz 4 13 -21024
add 31 4 0 0
bl 80197bec 0
or 3 4 3 1
bc 4 1 0 80197ab8 0
or 29 3 29 0
addi 4 4 -1
bl 80197bd8 0
lwz 30 31 12
addi 3 0 0
addi 0 0 1
lwz 4 30 0
stw 4 31 12
stw 3 30 0
stb 0 30 9
stb 3 30 10
lwz 0 31 8
cmpli 0 0 0 0
stw 0 30 4
bc 12 2 0 80197a88 0
lwz 3 31 8
stw 30 3 0
stw 30 31 8
lwz 12 31 20
cmpli 0 0 12 0
bc 12 2 0 80197ab8 0
or 30 3 30 0
mtctr 12
bctrl 20 0 0 1
cmpi 0 0 3 0
bc 12 2 0 80197ab8 0
or 30 3 30 0
bl 80197ad8 0
addi 30 0 0
lwz 0 1 36
or 30 3 30 0
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''), 0x80006d4c: ops('''
stwu 1 1 -16
mflr 0
addi 3 0 0
stw 0 1 20
bl 80197a0c 0
cmpli 0 0 3 0
bc 12 2 0 80006d70 0
addi 0 0 0
stw 0 3 12
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''), 0x80006f60: ops('''
addi 0 0 0
stw 0 3 32
stw 0 3 36
stw 0 3 40
addi 3 0 0
blr 20 0 0 0
''')}


def encode(row, pc):
    """Independent PPC inverse; never invokes the tested decoder."""
    n = row['mnemonic']
    if n in ('stwu', 'stw', 'stb', 'lwz', 'lbz', 'addi', 'addis', 'mulli'):
        opcode, reg, imm = {'stwu':(37,'rS','displacement'), 'stw':(36,'rS','displacement'),
            'stb':(38,'rS','displacement'), 'lwz':(32,'rD','displacement'),
            'lbz':(34,'rD','displacement'), 'addi':(14,'rD','immediate'),
            'addis':(15,'rD','immediate'), 'mulli':(7,'rD','immediate')}[n]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if n in ('mflr', 'mtlr', 'mtctr'):
        xo, reg = (339,'rD') if n == 'mflr' else (467,'rS')
        return 31 << 26 | row[reg] << 21 | (9 if n == 'mtctr' else 8) << 16 | xo << 1
    if n in ('or', 'extsb', 'add', 'lwzx', 'lhzx', 'lhax', 'stwx', 'sthx'):
        reg = 'rS' if n in ('or','extsb','stwx','sthx') else 'rD'
        xo = {'or':444,'extsb':954,'add':266,'lwzx':23,'lhzx':279,'lhax':343,'stwx':151,'sthx':407}[n]
        return 31 << 26 | row[reg] << 21 | row['rA'] << 16 | row.get('rB',0) << 11 | xo << 1 | row.get('Rc',0)
    if n in ('bl', 'b', 'bc'):
        displacement = int(row['target'],16) - (0 if row['AA'] else pc)
        if n != 'bc': return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | (n == 'bl')
        return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc | row['AA'] << 1 | row['LK']
    if n in ('blr','bctrl'):
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | (16 if n == 'blr' else 528) << 1 | row['LK']
    if n in ('cmpi','cmpli'):
        return (11 if n == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if n == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    raise AssertionError(n)


BODIES = {pc:b''.join(struct.pack('>I',encode(row,pc+i*4)) for i,row in enumerate(rows))
          for pc,rows in EXPECTED.items()}
PAYLOADS = dict(BODIES)
PAYLOADS.update({0x8036fa1c:struct.pack('>I',0x8036f644),0x802da673:struct.pack('>b',3),
    0x802da67e:struct.pack('>H',512),0x8036f654:struct.pack('>h',44),
    0x8036f658:struct.pack('>I',0x80006f60),0x802da666:struct.pack('>H',740),
    0x802da708:struct.pack('>b',16),0x802da709:struct.pack('>6b',16,16,16,16,16,16)})
SELECTIONS = tuple((a.range_evidence,TEXT_MAPPING,pc,(width,)) for pc,width,_ in RANGES) + \
    tuple((a.cell_evidence,DATA3_MAPPING,pc,()) for _,pc,_,_,_,_ in CELLS)
EXPECTED_READS = [(21,538552,184,2796416),(21,1648140,20,2796416),(21,1648120,20,2796416),
    (21,1647660,204,2796416),(21,5996,52,2796416),(21,6528,24,2796416),
    (199,740284,4,1000128),(199,129043,1,1000128),(199,129054,2,1000128),
    (199,739316,2,1000128),(199,739320,4,1000128),(199,129030,2,1000128),(199,129192,1,1000128),(199,129193,6,1000128)]


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args): self.calls.append(args); return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_inventory_values_and_fourteen_exact_reads(self):
        self.assertEqual(a.RANGES,RANGES); self.assertEqual(a.CELLS,CELLS)
        self.assertEqual(a.TEXT_MAPPING,TEXT_MAPPING); self.assertEqual(a.DATA3_MAPPING,DATA3_MAPPING)
        self.assertEqual(sum(len(raw) for raw in PAYLOADS.values()),526)
        for (fn,mapping,pc,args),call in zip(SELECTIONS,EXPECTED_READS):
            db=FakeDB(PAYLOADS[pc]); result=fn(db,mapping,pc,*args)
            self.assertEqual(db.calls,[call]); self.assertEqual(result['width'],len(PAYLOADS[pc]))
        for _,pc,_,_,values,_ in CELLS:
            self.assertEqual(a.cell_evidence(FakeDB(PAYLOADS[pc]),DATA3_MAPPING,pc)['values'],list(values))

    def test_all_126_instruction_operands_and_4032_single_bit_controls(self):
        controls=0
        for pc,width,digest in RANGES:
            self.assertEqual(len(BODIES[pc]),width)
            self.assertEqual(hashlib.sha256(BODIES[pc]).hexdigest(),digest)
            result=a.range_evidence(FakeDB(BODIES[pc]),TEXT_MAPPING,pc,width)
            self.assertEqual(result['instructions'],[dict(address=f'{pc+i*4:08x}',**row) for i,row in enumerate(EXPECTED[pc])])
            for i,row in enumerate(EXPECTED[pc]):
                address=pc+i*4; word=encode(row,address)
                self.assertEqual(a.decode_selected(word,address),row)
                for bit in range(32):
                    controls+=1; changed=word ^ 1 << bit
                    try: decoded=a.decode_selected(changed,address)
                    except a.c.FormatError: continue
                    if decoded is not None:
                        self.assertNotEqual(decoded,row,(hex(address),bit))
                        self.assertEqual(encode(decoded,address),changed,(hex(address),bit))
        self.assertEqual(controls,4032)

    def test_every_selected_byte_bit_mutation_rejected(self):
        count=0
        for fn,mapping,pc,args in SELECTIONS:
            raw=PAYLOADS[pc]
            for i in range(len(raw)):
                for bit in range(8):
                    changed=raw[:i]+bytes([raw[i]^1<<bit])+raw[i+1:]
                    with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'): fn(FakeDB(changed),mapping,pc,*args)
                    count+=1
        self.assertEqual(count,4208)

    def test_allocator_order_widths_and_pointer_return(self):
        at={pc+i*4:row for pc,rows in EXPECTED.items() for i,row in enumerate(rows)}
        self.assertEqual(at[0x80088dd8],dict(mnemonic='lhzx',rD=3,rA=4,rB=5))
        self.assertEqual(at[0x80088de0],dict(mnemonic='sthx',rS=0,rA=4,rB=5))
        self.assertEqual(at[0x80088de4],dict(mnemonic='lwz',rD=0,rA=30,displacement=4))
        self.assertEqual(at[0x80088dec],dict(mnemonic='stwx',rS=0,rA=6,rB=7))
        self.assertEqual(at[0x80088e04],dict(mnemonic='lbz',rD=29,rA=30,displacement=2))
        self.assertEqual(at[0x80088e20],dict(mnemonic='lhzx',rD=5,rA=5,rB=0))
        self.assertEqual(at[0x80088e24],dict(mnemonic='bl',target='8000540c',AA=0))
        self.assertEqual([at[pc]['displacement'] for pc in (0x80088e28,0x80088e2c)],[2,3])
        self.assertEqual(at[0x80197bf8],dict(mnemonic='lhax',rD=3,rA=4,rB=0))
        self.assertEqual(at[0x80197be4],dict(mnemonic='sthx',rS=4,rA=5,rB=0))
        self.assertEqual([at[pc]['displacement'] for pc in (0x80197a60,0x80197a64,0x80197a68,0x80197a6c,0x80197a78,0x80197a84,0x80197a88)],[12,0,9,10,4,0,8])
        self.assertEqual(at[0x80197a8c],dict(mnemonic='lwz',rD=12,rA=31,displacement=20))
        self.assertEqual(at[0x80197aa0],dict(mnemonic='bctrl',BO=20,BI=0,BH=0,LK=1))
        self.assertEqual(at[0x80197abc],dict(mnemonic='or',rS=30,rA=3,rB=30,Rc=0))
        self.assertEqual([at[pc]['displacement'] for pc in (0x80006f64,0x80006f68,0x80006f6c)],[32,36,40])
        self.assertEqual(at[0x80006f70],dict(mnemonic='addi',rD=3,rA=0,immediate=0))
        self.assertEqual(at[0x80006d6c],dict(mnemonic='stw',rS=0,rA=3,displacement=12))
        # No instruction after descriptor call writes r3; the returned descriptor survives.
        for row in EXPECTED[0x80006d4c][5:]:
            self.assertNotEqual(row.get('rD'),3)
            self.assertFalse(row['mnemonic'] in ('or','add','addi') and row.get('rA')==3)

    def test_no_adjacent_read_scope_mapping_and_types(self):
        for fn,mapping,pc,args in SELECTIONS:
            for bad in (pc-1,pc+1,True,float(pc),-1,1<<32):
                if type(bad) is int and not args and any(row[1]==bad for row in CELLS):
                    continue  # Neighboring group8/group9 selections are independently fixed.
                db=FakeDB(PAYLOADS[pc])
                with self.assertRaises(a.c.FormatError): fn(db,mapping,bad,*args)
                self.assertFalse(db.calls)
            for index,value in enumerate(mapping):
                for replacement in (value+1,float(value)) if type(value) is int else ('wrong',):
                    altered=list(mapping); altered[index]=replacement; db=FakeDB(PAYLOADS[pc])
                    with self.assertRaises(a.c.FormatError): fn(db,tuple(altered),pc,*args)
                    self.assertFalse(db.calls)
            with self.assertRaises(a.c.FormatError): fn(None,list(mapping),pc,*args)
        for pc,width,_ in RANGES:
            for bad in (width-4,width+4,float(width),True,0,-width):
                db=FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db,TEXT_MAPPING,pc,bad)
                self.assertFalse(db.calls)
        for pc in (0x8036f644,0x8036f648,0x8036f64c,0x8036f650,0x8036f656,0x8036f65c,0x802da70f):
            with self.assertRaises(a.c.FormatError): a.cell_evidence(None,DATA3_MAPPING,pc)
        for pc,width in ((0x80197ad8,188),(0x80197950,188),(0x80088aa0,416),(0x8007db5c,400)):
            with self.assertRaises(a.c.FormatError): a.range_evidence(None,TEXT_MAPPING,pc,width)

    def test_width_duplicates_values_and_decode_fail_closed(self):
        for fn,mapping,pc,args in SELECTIONS:
            for raw in (PAYLOADS[pc][:-1],PAYLOADS[pc]+b'\0'):
                with self.assertRaisesRegex(a.c.FormatError,'byte width'): fn(FakeDB(raw),mapping,pc,*args)
            field='RANGES' if args else 'CELLS'
            with patch.object(a,field,getattr(a,field)*2):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'): fn(None,mapping,pc,*args)
        for label,pc,width,fmt,values,digest in CELLS:
            with patch.object(a,'CELLS',((label,pc,width,fmt,(999999,),digest),)):
                with self.assertRaisesRegex(a.c.FormatError,'value mismatch'): a.cell_evidence(FakeDB(PAYLOADS[pc]),DATA3_MAPPING,pc)
        for word,pc in ((True,0),(-1,0),(1<<32,0),(0,True),(0,1),(0,-4),(0,1<<32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,pc)
        for xo in (151,279,343,407):
            with self.assertRaisesRegex(a.c.FormatError,'indexed Rc'): a.decode_selected(31<<26|xo<<1|1,0)
        self.assertIsNone(a.decode_selected(0,0))
        for pc,width,_ in RANGES:
            for decoded in (None,dict(mnemonic='lwz',rD=0,rA=0,displacement=0)):
                with patch.object(a,'decode_selected',return_value=decoded):
                    with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(BODIES[pc]),TEXT_MAPPING,pc,width)
        original=a.decode_selected
        for mnemonic,error in (('bc','branch outside'),('bl','direct-call'),('bctrl','indirect-call')):
            def changed(word,pc):
                row=original(word,pc)
                if row['mnemonic']==mnemonic:
                    return dict(row,target='90000000') if mnemonic!='bctrl' else dict(mnemonic='addi',rD=0,rA=0,immediate=0)
                return row
            with patch.object(a,'decode_selected',changed):
                with self.assertRaisesRegex(a.c.FormatError,error): a.range_evidence(FakeDB(BODIES[0x80197a0c]),TEXT_MAPPING,0x80197a0c,204)

    def test_authentication_and_mapping_precede_all_selections(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('auth stop')),patch.object(a.c,'GBF') as db,patch.object(a,'range_evidence') as code,patch.object(a,'cell_evidence') as cell:
            with self.assertRaisesRegex(a.c.FormatError,'auth stop'): a.inspect(b'bad','bad')
            db.assert_not_called();code.assert_not_called();cell.assert_not_called()
        mappings=a.command.MAPPINGS
        blocks={key:[name,None,None,0,start,length,0] for name,key,start,length,root in mappings}
        subs={key:[key,2,length,0,root,0] for name,key,start,length,root in mappings}
        cases=[]
        for key in (1,5,7):
            for field in (4,5,6):
                bb,ss=copy.deepcopy((blocks,subs));bb[key][field]+=1;cases.append((bb,ss,'80000000'))
            for field in range(6):
                bb,ss=copy.deepcopy((blocks,subs));ss[key][field]+=1;cases.append((bb,ss,'80000000'))
        cases.append((blocks,subs,'80000004'))
        for bb,ss,image in cases:
            with patch.object(a.c,'inspect',return_value={'image_offset':image}),patch.object(a.c,'GBF') as db,patch.object(a,'range_evidence') as code,patch.object(a,'cell_evidence') as cell:
                db.return_value.tables.return_value={'Memory Blocks':'b','Sub Memory Blocks':'s'}
                db.return_value.rows.side_effect=lambda key:{'b':bb,'s':ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic','synthetic')
                code.assert_not_called();cell.assert_not_called()

    def test_schema_and_actual_digest_controls_precede_payload(self):
        for digest in ('0'*64,hashlib.sha256(bytes(32)).hexdigest(),next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c,'GBF') as db,patch.object(a,'range_evidence') as selected:
                with self.assertRaisesRegex(a.c.FormatError,'SHA256 not allowlisted'):a.inspect(bytes(32),digest)
                db.assert_not_called();selected.assert_not_called()
        data=b'synthetic schema fixture';digest=hashlib.sha256(data).hexdigest()
        schema=dict(version=0,keytype=4,types=[4],fields='Key;Value;')
        for key,value in (('version',1),('keytype',3),('types',[2]),('fields','Wrong;')):
            changed=dict(schema);changed[key]=value
            with patch.dict(a.c.SNAPSHOTS,{digest:'synthetic'}),patch.object(a.c,'GBF') as db,patch.object(a,'range_evidence') as selected:
                db.return_value.tables.return_value={'Program':changed}
                with self.assertRaisesRegex(a.c.FormatError,'unsupported schema: Program'):a.inspect(data,digest)
                db.return_value.rows.assert_not_called();selected.assert_not_called()

    def test_independent_source_bounds_and_two_stage_selection_basis(self):
        root=Path(__file__).resolve().parents[3]
        index=(root/'research/decomp/ghidra-export/_index.tsv').read_text()
        symbols=(root/'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc,end,chunk in ((0x80088d98,0x80088e50,'0012'),(0x80197bec,0x80197c00,'0048'),(0x80197bd8,0x80197bec,'0048'),(0x80197a0c,0x80197ad8,'0048'),(0x80006d4c,0x80006d80,'0000')):
            text=(root/f'research/decomp/ghidra-export/chunk_{chunk}.c').read_text()
            for address in (pc,end):
                self.assertIn(f'// ==== {address:08x} ',text);self.assertIn(f'{address:08x}\t',index)
            self.assertIn(f'{pc:08x} {end-pc:08x} {pc:08x} ',symbols)
        # Callback is deliberately not a named map/C function; gap bounds are independent.
        self.assertNotIn('80006f60\t',index)
        self.assertIn('80006f1c 00000044 80006f1c ',symbols)
        self.assertIn('80006f78\t',index);self.assertEqual(0x80006f1c+0x44,0x80006f60)
        battle=(root/'research/decomp/ghidra-export/chunk_0003.c').read_text().split('// ==== 8002844c ')[1].split('// ==== 800286d8 ')[0]
        self.assertIn('zz_0197854_(1)',battle)
        self.assertIn('zz_0088398_(DAT_80436238 + 0xfe800,0xe0000,0)',battle)
        constructor=(root/'research/decomp/ghidra-export/chunk_0048.c').read_text().split('// ==== 80197854 ')[1].split('// ==== 801978d0 ')[0]
        self.assertIn('(&PTR_DAT_8036fa18)[param_1]',constructor)
        self.assertEqual(0x8036fa18+4,0x8036fa1c)
        self.assertEqual(0x8036f644+0x10,0x8036f654);self.assertEqual(0x8036f644+0x14,0x8036f658)
        self.assertEqual(0x802da660+2*3,0x802da666)
        actors=(root/'research/decomp/ghidra-export/chunk_0006.c').read_text().split('// ==== 800536b0 ')[1].split('// ==== 800537a8 ')[0]
        for expression in ('iVar2 = 0;', 'param_1[0x3e4] = (char)iVar2;', 'while (iVar2 < 6)'):
            self.assertIn(expression,actors)
        self.assertEqual([0x802da700+8+1+slot for slot in range(6)],list(range(0x802da709,0x802da70f)))
        for option in ('--address','--width','--pointer','--target','--raw','--execute'):
            with patch('sys.argv',['reader','none',option,'0']),contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc:a.main()
                self.assertEqual(exc.exception.code,2)


SNAPSHOT_DIR=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR/name).is_file() for name in ('db.3.gbf','db.4.gbf')),'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports,cls.reads,cls.auth_reads=[],[],[]; original=a.c.GBF.chain
        for name in ('db.3.gbf','db.4.gbf'):
            raw=(SNAPSHOT_DIR/name).read_bytes();digest=hashlib.sha256(raw).hexdigest();reads=[]
            def traced(db,*args): reads.append(args);return original(db,*args)
            with patch.object(a.c.GBF,'chain',traced): a.c.inspect(raw,digest)
            cls.auth_reads.append(reads[:]);reads.clear()
            with patch.object(a.c.GBF,'chain',traced):cls.reports.append(a.inspect(raw,digest))
            cls.reads.append(reads[:])

    def test_snapshot_agreement_all_operands_exact_trace(self):
        for key in ('mappings','ranges','cells','function_coverage','selection_basis'):self.assertEqual(self.reports[0][key],self.reports[1][key])
        self.assertEqual([r['snapshot'] for r in self.reports],['db.3.gbf','db.4.gbf'])
        for reads,auth in zip(self.reads,self.auth_reads):
            self.assertEqual(reads,auth+EXPECTED_READS);self.assertTrue(all(row[0]==263 for row in auth))
        for report in self.reports:
            for row in report['ranges']:
                pc=int(row['address'],16)
                self.assertEqual(row['instructions'],[dict(address=f'{pc+i*4:08x}',**item) for i,item in enumerate(EXPECTED[pc])])
            self.assertEqual(sum(row['represented_instructions'] for row in report['function_coverage']),126)
            self.assertIsNone(report['function_coverage'][-1]['map_size'])
            self.assertEqual(report['file_bytes_table'],dict(version=0,root=-1,count=0))

    def test_exact_physical_spans_and_no_payload_output(self):
        expected={0x80088d98:(21,54,538552,14456,184,915582),0x80197bec:(21,122,1648140,10340,20,2025578),
            0x80197bd8:(21,122,1648120,10320,20,2025558),0x80197a0c:(21,122,1647660,9860,204,2025098),
            0x80006d4c:(21,22,5996,5996,52,382834),0x80006f60:(21,22,6528,6528,24,383366),
            0x8036fa1c:(199,245,740284,3274,4,4033744),0x802da673:(199,207,129043,14397,1,3422275),
            0x802da67e:(199,207,129054,14408,2,3422286),0x8036f654:(199,245,739316,2306,2,4032776),
            0x8036f658:(199,245,739320,2310,4,4032780),0x802da666:(199,207,129030,14384,2,3422262),
            0x802da708:(199,207,129192,14546,1,3422424),
            0x802da709:(199,207,129193,14547,6,3422425)}
        for report in self.reports:
            for row in report['ranges']+report['cells']:
                root,data,chain,offset,width,physical=expected[int(row['address'],16)]
                self.assertEqual(row['spans'],[dict(root_buffer=root,data_buffer=data,chain_offset=chain,data_offset=offset,length=width,obfuscated=True,physical_offset=physical)])
                self.assertEqual(row['end_exclusive'],f'{int(row["address"],16)+width:08x}')
                self.assertNotIn('raw',row)
                if 'instructions' in row:self.assertTrue(all('word' not in item for item in row['instructions']))

    def test_real_hash_schema_and_selected_tamper_refuse(self):
        raw=(SNAPSHOT_DIR/'db.3.gbf').read_bytes();digest=hashlib.sha256(raw).hexdigest()
        with patch.object(a,'range_evidence') as selected:
            for changed,claimed in ((raw,'0'*64),(raw[:-1]+bytes([raw[-1]^1]),digest)):
                with self.assertRaisesRegex(a.c.FormatError,'SHA256 not allowlisted'):a.inspect(changed,claimed)
            selected.assert_not_called()
        original=a.c.GBF.chain
        for target in EXPECTED_READS:
            def altered(db,*args):
                data,spans=original(db,*args)
                return (bytes([data[0]^1])+data[1:] if args==target else data),spans
            with patch.object(a.c.GBF,'chain',altered):
                with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'):a.inspect(raw,digest)


if __name__=='__main__':unittest.main()
