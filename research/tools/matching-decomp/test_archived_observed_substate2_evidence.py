#!/usr/bin/env python3
"""Fixed-scope controls; private snapshots optional, never fetched or published."""
import contextlib
import copy
import hashlib
import io
import json
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_observed_substate2_evidence as a
from test_archived_later_outer_evidence import encode as prior_encode

ROOT=Path(__file__).resolve().parents[3]
BASE=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
RANGES=((0x80054cbc,52,'5031b1cbdf20bc9464eef663b0778abe4c88b6c39931b9b0be6f0feabc0fdb26'),
        (0x80056900,424,'52c4c7e19500682352bbf4503d8973d50f69fed24c5525d5b3ab40bba34bbfa2'),
        (0x8008bbc0,16,'257d48a7d554a62bc9c18c1daf1fa73860c81815999016f64a0a7b01f7cda582'))
CELLS=(('substate_index_2',0x802d327c,0x80054cbc,'2c003f1520860d7999fed1fdbc3ab22879135b1d1b9676583d180e72760579c9'),)
READS=[(21,pc-0x800055e0,w,2796416) for pc,w,_ in RANGES]+[(199,0x802d327c-0x802bae60,4,1000128)]

def encode(row,pc):
    if row['mnemonic']=='andc':return 31<<26|row['rS']<<21|row['rA']<<16|row['rB']<<11|60<<1|row['Rc']
    return prior_encode(row,pc)

class FakeDB:
    def __init__(self,raw=b''):self.raw,self.calls=raw,[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]

class SyntheticTests(unittest.TestCase):
    def test_fixed_scope_and_c_index_provenance(self):
        self.assertEqual(a.RANGES,RANGES);self.assertEqual(a.CELLS,CELLS)
        lines=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        for pc,w,_ in RANGES:
            i=next(i for i,s in enumerate(lines) if s.startswith(f'{pc:08x}\t'))
            self.assertTrue(lines[i+1].startswith(f'{pc+w:08x}\t'))
            chunk=lines[i].split('\t')[-1];s=(ROOT/'research/decomp/ghidra-export'/chunk).read_text()
            body,after=s.split(f'// ==== {pc:08x} ',1)[1].split('// ==== ',1)
            self.assertTrue(body.strip());self.assertTrue(after.startswith(f'{pc+w:08x} '))
        for row in a.REUSED_EVIDENCE:self.assertTrue((ROOT/'research/tools/matching-decomp'/row['source']).is_file())

    def test_scope_types_duplicates_and_mapping_refuse_before_read(self):
        for pc,w,_ in RANGES:
            for address,width in [(pc+4,w),(pc,w-4),(True,w),(float(pc),w),(pc,True)]:
                db=FakeDB()
                with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.TEXT_MAPPING,address,width)
                self.assertFalse(db.calls)
        for pc in [0x802d3278,0x802d3280,True,float(0x802d327c)]:
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA3_MAPPING,pc)
            self.assertFalse(db.calls)
        for mapping,func,args in [(a.TEXT_MAPPING,a.range_evidence,RANGES[0][:2]),(a.DATA3_MAPPING,a.cell_evidence,(0x802d327c,))]:
            for i,v in enumerate(mapping):
                changed=list(mapping);changed[i]=v+1 if type(v)is int else 'wrong';db=FakeDB()
                with self.assertRaises(a.c.FormatError):func(db,tuple(changed),*args)
                self.assertFalse(db.calls)
        with patch.object(a,'CELLS',CELLS*2):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA3_MAPPING,0x802d327c)
            self.assertFalse(db.calls)

    def test_width_and_digest_before_decode(self):
        with patch.object(a,'decode_selected') as decoder:
            for pc,w,_ in RANGES:
                for size in (w-1,w,w+1):
                    with self.assertRaises(a.c.FormatError):a.range_evidence(FakeDB(bytes(size)),a.TEXT_MAPPING,pc,w)
            decoder.assert_not_called()
        for raw in (b'',bytes(3),bytes(4),bytes(5)):
            with self.assertRaises(a.c.FormatError):a.cell_evidence(FakeDB(raw),a.DATA3_MAPPING,0x802d327c)

    def test_auth_precedes_parser(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF') as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()

    def test_reused_andc_operand_direction(self):
        for rs in (0,3,31):
            for ra in (0,9,31):
                for rb in (0,17,31):
                    for rc in (0,1):
                        r=dict(mnemonic='andc',rS=rs,rA=ra,rB=rb,Rc=rc)
                        self.assertEqual(a.decode_selected(encode(r,0),0),r)

    def test_no_general_cli(self):
        for opt in ('--address','--width','--pointer','--dump','--instructions'):
            with patch('sys.argv',['reader','none',opt,'0']),contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit):a.main()

@unittest.skipUnless(all((BASE/n).is_file() for n in ('db.3.gbf','db.4.gbf')),'optional existing private snapshots; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports=[];cls.rows=[];cls.payloads=[]
        chain,decode=a.c.GBF.chain,a.decode_selected
        for name in ('db.3.gbf','db.4.gbf'):
            data=(BASE/name).read_bytes();digest=hashlib.sha256(data).hexdigest();trace=[];rows={};payloads={}
            def traced(db,*args):
                trace.append(args);result=chain(db,*args)
                if args in READS:payloads[args]=result[0]
                return result
            def decoded(word,pc):
                row=decode(word,pc);rows[pc]=(word,row);return row
            with patch.object(a.c.GBF,'chain',traced):a.c.inspect(data,digest)
            auth=trace[:];trace.clear()
            with patch.object(a.c.GBF,'chain',traced),patch.object(a,'decode_selected',decoded):report=a.inspect(data,digest)
            assert trace==auth+READS,(trace[len(auth):],READS)
            cls.reports.append(report);cls.rows.append(rows);cls.payloads.append(payloads)

    def test_complete_agree_no_listing(self):
        self.assertEqual(self.rows[0],self.rows[1]);self.assertEqual(len(self.rows[0]),123)
        for k in ('ranges','cells','mappings','selection_basis'):self.assertEqual(self.reports[0][k],self.reports[1][k])
        for r in self.reports:
            self.assertEqual(r['selection_basis']['bytes'],496)
            for field in ('mnemonic','instructions','raw_words','raw_bytes'):self.assertNotIn('"'+field+'"',json.dumps(r))
            self.assertEqual(r['cells'][0]['target'],'80054cbc')

    def test_instruction_inverse_and_every_bit(self):
        count=0
        for pc,(word,row) in self.rows[0].items():
            self.assertEqual(encode(row,pc),word)
            for bit in range(32):
                changed=word^(1<<bit);count+=1
                try:r=a.decode_selected(changed,pc)
                except a.c.FormatError:continue
                if r is not None:self.assertNotEqual(r,row);self.assertEqual(encode(r,pc),changed)
        self.assertEqual(count,3936)

    def test_every_payload_bit_refuses(self):
        count=0
        with patch.object(a,'decode_selected') as decode:
            for read,raw in self.payloads[0].items():
                i=READS.index(read)
                for off in range(len(raw)):
                    for bit in range(8):
                        mutated=raw[:off]+bytes([raw[off]^(1<<bit)])+raw[off+1:];count+=1
                        with self.assertRaises(a.c.FormatError):
                            if i<3:a.range_evidence(FakeDB(mutated),a.TEXT_MAPPING,*RANGES[i][:2])
                            else:a.cell_evidence(FakeDB(mutated),a.DATA3_MAPPING,0x802d327c)
            decode.assert_not_called()
        self.assertEqual(count,3968)

    def test_exact_calls_and_store_order(self):
        r={pc:row for pc,(_,row) in self.rows[0].items()}
        for pc,target in [(0x80054cd0,'80056900'),(0x80054cd8,'80055568'),(0x800569e4,'8008bbc0'),(0x80056a58,'8001c9d0')]:self.assertEqual(r[pc]['target'],target)
        for pc,offset in [(0x80056918,0x488),(0x8005691c,0x3e6),(0x80056930,0x488),(0x800569ac,0x5c9),(0x800569bc,0x5b8),(0x800569e8,0x5b4),(0x80056a64,0x5c4),(0x80056a74,0x5bc),(0x80056a84,0x5c0),(0x80056a8c,0x5c0),(0x80056a90,0x5bc)]:self.assertEqual(r[pc]['displacement'],offset)
        self.assertEqual(r[0x800569ec]['rA'],31)
        self.assertEqual([r[pc]['displacement'] for pc in range(0x80056a24,0x80056a3c,4)],[0x5cf,0x5ce,0x5cd,0x5cc,0x5cb,0x5ca])

    def test_semantic_and_flow_drift_refuse(self):
        raw=self.payloads[0][READS[0]]
        for attr,value in [('OPERAND_DIGESTS',{0x80054cbc:'bad'}),('FLOW_DIGESTS',{0x80054cbc:(3,'bad')}),('CALLS',{0x80054cbc:()})]:
            with patch.object(a,attr,value):
                with self.assertRaises(a.c.FormatError):a.range_evidence(FakeDB(raw),a.TEXT_MAPPING,0x80054cbc,52)

if __name__=='__main__':unittest.main()
