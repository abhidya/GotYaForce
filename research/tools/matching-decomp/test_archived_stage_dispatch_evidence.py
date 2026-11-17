#!/usr/bin/env python3
"""Fixed scope controls; private snapshots optional and never fetched."""
import copy
import hashlib
import json
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_stage_dispatch_evidence as a
from test_archived_frame_actor_helpers_evidence import encode as helper_encode
from test_archived_target_preparation_evidence import encode as target_encode

ROOT = Path(__file__).resolve().parents[3]
BASE = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
RANGES = ((0x80087718,252,'1562f9b6cce8ef72042409a77b9bcd96bab9667c7f1eff383c5bfac56496dc43'),
          (0x80087d2c,504,'4af69623be006a38ea38c9184995f6cc3301b09806cd833357466dc3e8331658'))
CELLS = ((0x80433918,0x80087d2c,'095420b255262dcf65d40f5358807b9f38328787e5131c1911ac5c881210283a'),
         (0x8043391c,0x80087f20,'31c457b8b303558c3ea6ddf252b3969a407774c2d2f275c2ef028028ea60a7b0'))
READS = [(21,pc-0x800055e0,w,2796416) for pc,w,_ in RANGES] + [(262,pc-0x804335a0,4,11040) for pc,_,_ in CELLS]

class FakeDB:
    def __init__(self, raw=b''): self.raw,self.calls=raw,[]
    def chain(self,*args): self.calls.append(args); return self.raw,[]

class SyntheticTests(unittest.TestCase):
    def test_fixed_scope_and_metadata(self):
        self.assertEqual(a.RANGES,RANGES);self.assertEqual(a.CELLS,CELLS)
        idx=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        for pc,w,_ in RANGES:
            i=next(i for i,s in enumerate(idx) if s.startswith(f'{pc:08x}\t'))
            self.assertTrue(idx[i+1].startswith(f'{pc+w:08x}\t'))
        # State one deliberately targets a selected return within state-zero, not an invented function.
        self.assertEqual(CELLS[1][1],RANGES[1][0]+RANGES[1][1]-4)

    def test_refuse_scope_and_map_changes_before_reads(self):
        for pc,w,_ in RANGES:
            for address,width in ((pc+4,w),(pc,w-4),(float(pc),w),(pc,True)):
                db=FakeDB()
                with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.TEXT_MAPPING,address,width)
                self.assertFalse(db.calls)
        for address in (0x80433914,0x80433920,True,float(0x80433918)):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA4_MAPPING,address)
            self.assertFalse(db.calls)
        for i,v in enumerate(a.DATA4_MAPPING):
            m=list(a.DATA4_MAPPING);m[i]=v+1 if type(v)is int else 'wrong';db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,tuple(m),CELLS[0][0])
            self.assertFalse(db.calls)
        with patch.object(a,'CELLS',CELLS*2):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA4_MAPPING,CELLS[0][0])
            self.assertFalse(db.calls)

    def test_authentication_before_parser(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF') as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()

    def test_cell_bytes_and_target_refuse(self):
        for pc,target,digest in CELLS:
            for raw in (bytes(3),bytes(5),bytes(4)):
                with self.assertRaises(a.c.FormatError):a.cell_evidence(FakeDB(raw),a.DATA4_MAPPING,pc)
            with patch.object(a,'CELLS',((pc,target^4,digest),)):
                with self.assertRaisesRegex(a.c.FormatError,'target mismatch'):
                    a.cell_evidence(FakeDB(target.to_bytes(4,'big')),a.DATA4_MAPPING,pc)

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
        for k in ('ranges','dispatch_cells','mappings','selection_basis'):self.assertEqual(self.reports[0][k],self.reports[1][k])
        self.assertEqual(self.rows[0],self.rows[1]);self.assertEqual(len(self.rows[0]),189)
        for report in self.reports:
            self.assertEqual(report['selection_basis']['bytes'],764)
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
        self.assertEqual(count,6048)

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
                            else:a.cell_evidence(FakeDB(changed),a.DATA4_MAPPING,CELLS[i-2][0])
            decoder.assert_not_called()
        self.assertEqual(count,6112)

    def test_initialization_increment_and_real_state_one_return(self):
        rows={pc:row for pc,(_,row) in self.rows[0].items()}
        self.assertEqual(rows[0x8008772c],dict(mnemonic='stw',rS=3,rA=13,displacement=-21316))
        self.assertEqual(rows[0x80087720]['immediate'],0);self.assertEqual(rows[0x80087724]['immediate'],256)
        self.assertEqual(rows[0x80087730]['target'],'8000540c')
        self.assertEqual(rows[0x80087d48],dict(mnemonic='lwz',rD=5,rA=13,displacement=-21316))
        self.assertEqual(rows[0x80087d4c],dict(mnemonic='lbz',rD=4,rA=5,displacement=0))
        self.assertEqual(rows[0x80087d50],dict(mnemonic='addi',rD=4,rA=4,immediate=1))
        self.assertEqual(rows[0x80087d54],dict(mnemonic='stb',rS=4,rA=5,displacement=0))
        self.assertEqual(rows[CELLS[1][1]],dict(mnemonic='blr',BO=20,BI=0,BH=0,LK=0))
        self.assertEqual(len(a.CALLS[0x80087d2c]),20)

if __name__=='__main__':unittest.main()
