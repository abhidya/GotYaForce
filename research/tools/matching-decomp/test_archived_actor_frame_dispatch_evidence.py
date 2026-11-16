#!/usr/bin/env python3
"""Synthetic refusal controls and optional local archive checks; no game fixture."""
import contextlib
import io
import hashlib
import json
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_actor_frame_dispatch_evidence as a

ROOT = Path(__file__).resolve().parents[3]
SNAPSHOTS = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'

class FakeDB:
    def __init__(self, raw=b''): self.raw, self.calls = raw, []
    def chain(self, *args): self.calls.append(args); return self.raw, []

class Controls(unittest.TestCase):
    def test_exact_scope(self):
        self.assertEqual([(p,n) for p,n,_ in a.RANGES], [(0x80054070,316),(0x8005475c,128),(0x80054c78,68),(0x8005a580,1896),(0x80006284,592)])
        self.assertEqual(sum(n for _,n,_ in a.RANGES),3000)
        self.assertEqual([r[1:3] for r in a.CELLS],[(0x802d3268,0x8005475c),(0x802d3278,0x80054c78)])
        self.assertEqual(a.CONSTANTS,((0x804373e0,'41a00000','stage_boundary_margin'),))
    def test_bad_code_selection_precedes_read(self):
        for pc,width,_ in a.RANGES:
            for badpc,badwidth in ((pc+4,width),(pc,width+4),(float(pc),width),(pc,True)):
                db=FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db,a.TEXT_MAPPING,badpc,badwidth)
                self.assertFalse(db.calls)
            for i,v in enumerate(a.TEXT_MAPPING):
                mapping=list(a.TEXT_MAPPING); mapping[i]=v+1 if type(v) is int else 'wrong'; db=FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db,tuple(mapping),pc,width)
                self.assertFalse(db.calls)
    def test_width_and_digest_before_decoder(self):
        with patch.object(a,'decode_selected') as decoder:
            for pc,width,_ in a.RANGES:
                for raw in (b'',bytes(width-1),bytes(width),bytes(width+1)):
                    with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(raw),a.TEXT_MAPPING,pc,width)
            decoder.assert_not_called()
    def test_cell_allowlist_mapping_and_endianness(self):
        for _,pc,target,_ in a.CELLS:
            self.assertEqual(a.cell_evidence(FakeDB(target.to_bytes(4,'big')),a.DATA3_MAPPING,pc)['target'],f'{target:08x}')
            for raw in (target.to_bytes(4,'little'),b'',bytes(5)):
                with self.assertRaises(a.c.FormatError): a.cell_evidence(FakeDB(raw),a.DATA3_MAPPING,pc)
            for bad in (pc-4,pc+4,True,float(pc)):
                db=FakeDB()
                with self.assertRaises(a.c.FormatError): a.cell_evidence(db,a.DATA3_MAPPING,bad)
                self.assertFalse(db.calls)
            db=FakeDB()
            with self.assertRaises(a.c.FormatError): a.cell_evidence(db,a.DATA5_MAPPING,pc)
            self.assertFalse(db.calls)
    def test_constant(self):
        pc,bits,_=a.CONSTANTS[0]
        self.assertEqual(a.constant_evidence(FakeDB(bytes.fromhex(bits)),a.DATA5_MAPPING,pc)['value'],20)
        for raw in (bytes(4),bytes(3),bytes(5),bytes.fromhex(bits)[::-1]):
            with self.assertRaises(a.c.FormatError): a.constant_evidence(FakeDB(raw),a.DATA5_MAPPING,pc)
        for bad in (pc-4,pc+4,True,float(pc)):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError): a.constant_evidence(db,a.DATA5_MAPPING,bad)
            self.assertFalse(db.calls)
    def test_word_pc_types(self):
        for word,pc in ((True,0),(-1,0),(1<<32,0),(0,True),(0,1),(0,-4),(0,1<<32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,pc)
    def test_duplicate_allowlists_refuse_before_read(self):
        pc,width,_=a.RANGES[0]; db=FakeDB()
        with patch.object(a,'RANGES',a.RANGES*2):
            with self.assertRaises(a.c.FormatError): a.range_evidence(db,a.TEXT_MAPPING,pc,width)
        self.assertFalse(db.calls)
        with patch.object(a,'CELLS',a.CELLS*2):
            with self.assertRaises(a.c.FormatError): a.cell_evidence(db,a.DATA3_MAPPING,a.CELLS[0][1])
        self.assertFalse(db.calls)
        with patch.object(a,'CONSTANTS',a.CONSTANTS*2):
            with self.assertRaises(a.c.FormatError): a.constant_evidence(db,a.DATA5_MAPPING,a.CONSTANTS[0][0])
        self.assertFalse(db.calls)
    def test_cli_no_arbitrary_selection_or_dump(self):
        for option in ('--address','--width','--pointer','--target','--dump','--instructions'):
            with patch('sys.argv',['reader','none',option,'0']),contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as error: a.main()
                self.assertEqual(error.exception.code,2)
    def test_auth_before_selection(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('auth')),patch.object(a.c,'GBF') as db:
            with self.assertRaises(a.c.FormatError): a.inspect(b'bad','bad')
            db.assert_not_called()

@unittest.skipUnless(all((SNAPSHOTS/n).is_file() for n in ('db.3.gbf','db.4.gbf')),'local snapshots absent')
class Archives(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports=[]; cls.bodies={}; cls.reads=[]
        for name in ('db.3.gbf','db.4.gbf'):
            data=(SNAPSHOTS/name).read_bytes(); original=a.c.GBF.chain
            def record(db,*args):
                raw,spans=original(db,*args)
                if args[2] in [n for _,n,_ in a.RANGES] and hashlib.sha256(raw).hexdigest() in [h for _,_,h in a.RANGES]:
                    cls.bodies[hashlib.sha256(raw).hexdigest()]=raw
                return raw,spans
            with patch.object(a.c.GBF,'chain',record): cls.reports.append(a.inspect(data,hashlib.sha256(data).hexdigest()))
    def test_pair_equal_summary_only(self):
        for key in ('ranges','cells','constants'):
            left=[{k:v for k,v in r.items() if k!='spans'} for r in self.reports[0][key]]
            right=[{k:v for k,v in r.items() if k!='spans'} for r in self.reports[1][key]]
            self.assertEqual(left,right)
        self.assertEqual(sum(r['represented_instructions'] for r in self.reports[0]['ranges']),750)
        for report in self.reports:
            out=json.dumps(report)
            for forbidden in ('"instructions"','"word"','"mnemonic"','"displacement"'): self.assertNotIn(forbidden,out)
    def test_operand_decoder_mutation_rejected(self):
        original=a.decode_selected
        for pc,width,sha in a.RANGES:
            def mutate(word,site):
                result=original(word,site)
                if site==pc: result=dict(result, rA=31)
                return result
            with patch.object(a,'decode_selected',mutate):
                with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(self.bodies[sha]),a.TEXT_MAPPING,pc,width)
    def test_every_selected_payload_corruption_rejected(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes(); original=a.c.GBF.chain
        selections=[(a.TEXT_MAPPING,pc,width) for pc,width,_ in a.RANGES]+[(a.DATA3_MAPPING,pc,4) for _,pc,_,_ in a.CELLS]+[(a.DATA5_MAPPING,pc,4) for pc,_,_ in a.CONSTANTS]
        for mapping,pc,width in selections:
            args_expected=(mapping[-1],pc-mapping[0],width,mapping[-2])
            def damage(db,*args):
                raw,spans=original(db,*args)
                if args==args_expected: raw=bytes([raw[0]^1])+raw[1:]
                return raw,spans
            with patch.object(a.c.GBF,'chain',damage):
                with self.assertRaises(a.c.FormatError): a.inspect(data,hashlib.sha256(data).hexdigest())

if __name__=='__main__': unittest.main()
