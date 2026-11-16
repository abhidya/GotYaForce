#!/usr/bin/env python3
"""Fixed scope controls; private snapshots optional and never fetched."""
import copy
import hashlib
import json
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_actor_voice_evidence as a
from test_archived_later_outer_evidence import encode as prior_encode

def helper_encode(row,pc):
    if row["mnemonic"]=="mullw": return 31<<26 | row["rD"]<<21 | row["rA"]<<16 | row["rB"]<<11 | 235<<1 | row["Rc"]
    return prior_encode(row,pc)
from test_archived_target_preparation_evidence import encode as target_encode

ROOT = Path(__file__).resolve().parents[3]
BASE = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
RANGES = ((2148442916, 264, 'e0dcebeeca660396390676cdf27488c21ba21c0f000cdf937ebecbb17f8efb83'), (2148442480, 344, 'be2656ce193e3315726de4cacf3c04e2df1debc2712d0e160e477cde17f5798d'))
CELLS = ((2150735264, 64, 'c3641f8544d7c02f3580b07c0f9887f0c6a27ff5ab1d4a3e29caf197cfc299ae'), (2150735265, 128, '76be8b528d0075f7aae98d6fa57a6d3c83ae480a8469e668d7b0af968995ac71'), (2150735266, 127, '620bfdaa346b088fb49998d92f19a7eaf6bfc2fb0aee015753966da1028cb731'), (2150735267, 0, '6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d'))
READS = [(21, 937284, 264, 2796416), (21, 936848, 344, 2796416), (199, 388928, 1, 1000128), (199, 388929, 1, 1000128), (199, 388930, 1, 1000128), (199, 388931, 1, 1000128)]

class FakeDB:
    def __init__(self, raw=b''): self.raw,self.calls=raw,[]
    def chain(self,*args): self.calls.append(args); return self.raw,[]

class SyntheticTests(unittest.TestCase):
    def test_fixed_scope_and_metadata(self):
        self.assertEqual(a.RANGES,RANGES);self.assertEqual(a.CELLS,CELLS)
        idx=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        for pc,w,_ in RANGES:
            entry=0x800ea2ec if pc==0x800ea324 else pc
            width=340 if pc==0x800ea324 else w
            i=next(i for i,v in enumerate(idx) if v.startswith(f'{entry:08x}\t'))
            self.assertTrue(idx[i+1].startswith(f'{entry+width:08x}\t'))
        self.assertEqual([v for _,v,_ in CELLS],[64,128,127,0])
        self.assertEqual([(x['address'],x['width'],x['read_here']) for x in a.REUSED_EVIDENCE],
                         [('800055fc',52,False),('800ea2ec',56,False),('800ea42c',20,False)])

    def test_refuse_scope_and_map_changes_before_reads(self):
        for pc,w,_ in RANGES:
            for address,width in ((pc+4,w),(pc,w-4),(float(pc),w),(pc,True)):
                db=FakeDB()
                with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.TEXT_MAPPING,address,width)
                self.assertFalse(db.calls)
        for address in (0x80319d9f,0x80319da4,True,float(0x80319da0)):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA3_MAPPING,address)
            self.assertFalse(db.calls)
        for i,v in enumerate(a.DATA3_MAPPING):
            m=list(a.DATA3_MAPPING);m[i]=v+1 if type(v)is int else 'wrong';db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,tuple(m),CELLS[0][0])
            self.assertFalse(db.calls)
        with patch.object(a,'CELLS',CELLS*2):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA3_MAPPING,CELLS[0][0])
            self.assertFalse(db.calls)

    def test_authentication_before_parser(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF') as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()

    def test_cell_bytes_and_target_refuse(self):
        for pc,target,digest in CELLS:
            for raw in (bytes(0),bytes(2),bytes([255])):
                with self.assertRaises(a.c.FormatError):a.cell_evidence(FakeDB(raw),a.DATA3_MAPPING,pc)
            with patch.object(a,'CELLS',((pc,target^4,digest),)):
                with self.assertRaisesRegex(a.c.FormatError,'target mismatch'):
                    a.cell_evidence(FakeDB(target.to_bytes(1,'big')),a.DATA3_MAPPING,pc)

@unittest.skipUnless(all((BASE/n).is_file() for n in ('db.3.gbf','db.4.gbf')),'private snapshots optional')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports=[];cls.rows=[];cls.payloads=[]
        chain,decode=a.c.GBF.chain,a.decode_selected
        for n in ('db.3.gbf','db.4.gbf'):
            data=(BASE/n).read_bytes();digest=hashlib.sha256(data).hexdigest();trace=[];rows={};payloads={}
            def traced(db,*args):
                trace.append(args);result=chain(db,*args)
                if args in READS:payloads[args]=result[0]
                return result
            def decoded(word,pc):
                row=decode(word,pc);rows[pc]=(word,row);return row
            with patch.object(a.c.GBF,'chain',traced):a.c.inspect(data,digest)
            auth=trace[:];trace.clear()
            with patch.object(a.c.GBF,'chain',traced),patch.object(a,'decode_selected',decoded):report=a.inspect(data,digest)
            assert trace==auth+READS
            cls.reports.append(report);cls.rows.append(rows);cls.payloads.append(payloads)

    def test_snapshots_agree_without_listings(self):
        for k in ('ranges','event2_cells','mappings','selection_basis'):self.assertEqual(self.reports[0][k],self.reports[1][k])
        self.assertEqual(self.rows[0],self.rows[1]);self.assertEqual(len(self.rows[0]),152)
        for report in self.reports:
            self.assertEqual(report['selection_basis']['bytes'],612)
            self.assertNotIn('"mnemonic"',json.dumps(report))
            self.assertFalse(report['selection_basis']['pointer_following'])

    def test_all_instruction_inverses_and_bit_controls(self):
        def encode(r,pc):return target_encode(r,pc) if r['mnemonic']=='lfsx' else helper_encode(r,pc)
        count=0
        for pc,(word,row) in self.rows[0].items():
            self.assertEqual(encode(row,pc),word)
            for bit in range(32):
                changed=word^(1<<bit);count+=1
                try:r=a.decode_selected(changed,pc)
                except a.c.FormatError:continue
                if r is not None:self.assertNotEqual(r,row);self.assertEqual(encode(r,pc),changed)
        self.assertEqual(count,4864)

    def test_all_payload_mutations_refuse_before_decode(self):
        count=0
        with patch.object(a,'decode_selected') as decoder:
            for read,body in self.payloads[0].items():
                i=READS.index(read)
                for off in range(len(body)):
                    for bit in range(8):
                        changed=body[:off]+bytes([body[off]^(1<<bit)])+body[off+1:];count+=1
                        with self.assertRaises(a.c.FormatError):
                            if i<2:a.range_evidence(FakeDB(changed),a.TEXT_MAPPING,*RANGES[i][:2])
                            else:a.cell_evidence(FakeDB(changed),a.DATA3_MAPPING,CELLS[i-2][0])
            decoder.assert_not_called()
        self.assertEqual(count,4896)

    def test_rng_capture_and_event_gate_order(self):
        rows={pc:row for pc,(_,row) in self.rows[0].items()}
        self.assertEqual(rows[0x800ea324]['target'],'800055fc')
        self.assertEqual(rows[0x800ea32c]['displacement'],0x438)
        self.assertEqual(rows[0x800ea340]['displacement'],1)
        self.assertEqual(rows[0x800ea35c]['displacement'],-31852)
        self.assertEqual(rows[0x800ea360]['displacement'],0x15dd)
        self.assertEqual(rows[0x800ea378]['displacement'],0x1828)
        self.assertEqual(rows[0x800ea380]['mnemonic'],'slw')
        self.assertEqual(rows[0x800ea398]['displacement'],0x26)
        self.assertEqual(rows[0x800ea3bc]['displacement'],0x4ac)
        self.assertEqual(rows[0x800ea3c0]['displacement'],0x183)
        self.assertEqual(rows[0x800ea3e4]['target'],'800ea170')
        self.assertEqual(rows[0x800ea190]['target'],'800055fc')
        self.assertEqual(a.CALLS[0x800ea324][0],('800ea324','800055fc'))


if __name__=='__main__':unittest.main()
