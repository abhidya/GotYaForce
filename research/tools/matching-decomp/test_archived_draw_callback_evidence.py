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
import read_archived_draw_callback_evidence as a
from test_archived_later_outer_evidence import encode as prior_encode

ROOT=Path(__file__).resolve().parents[3]
BASE=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
RANGES=((0x80047aa4,404,'d1034c09b0f68dabce25aa8dc2fd55eb99b31ee2e017cf379fad8fa7c23eb779'),)
READS=[(263,0x804370e0-0x80436a20,4,27360),(21,0x80047aa4-0x800055e0,404,2796416)]

encode=prior_encode

class FakeDB:
    def __init__(self,raw=b''):self.raw,self.calls=raw,[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]

class SyntheticTests(unittest.TestCase):
    def test_fixed_scope_and_c_index_provenance(self):
        self.assertEqual(a.RANGES,RANGES)
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
        for i,v in enumerate(a.TEXT_MAPPING):
            changed=list(a.TEXT_MAPPING);changed[i]=v+1 if type(v)is int else 'wrong';db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.range_evidence(db,tuple(changed),*RANGES[0][:2])
            self.assertFalse(db.calls)

    def test_width_and_digest_before_decode(self):
        with patch.object(a,'decode_selected') as decoder:
            for pc,w,_ in RANGES:
                for size in (w-1,w,w+1):
                    with self.assertRaises(a.c.FormatError):a.range_evidence(FakeDB(bytes(size)),a.TEXT_MAPPING,pc,w)
            decoder.assert_not_called()

    def test_auth_precedes_parser(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF') as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()

    def test_constant_scope_mapping_bits(self):
        self.assertEqual(a.CONSTANTS,((0x804370e0,'38c90fdb','signed-angle-to-radians'),))
        for address in (True,float(0x804370e0),0x804370dc):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.constant_evidence(db,a.DATA5_MAPPING,address)
            self.assertFalse(db.calls)
        for i,v in enumerate(a.DATA5_MAPPING):
            changed=list(a.DATA5_MAPPING);changed[i]=v+1 if type(v)is int else 'wrong';db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.constant_evidence(db,tuple(changed),0x804370e0)
            self.assertFalse(db.calls)
        for raw in (bytes(3),bytes(4),bytes(5)):
            with self.assertRaises(a.c.FormatError):a.constant_evidence(FakeDB(raw),a.DATA5_MAPPING,0x804370e0)

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
        self.assertEqual(self.rows[0],self.rows[1]);self.assertEqual(len(self.rows[0]),101)
        for k in ('ranges','constants','mappings','selection_basis'):self.assertEqual(self.reports[0][k],self.reports[1][k])
        for r in self.reports:
            self.assertEqual(r['selection_basis']['bytes'],408)
            for field in ('mnemonic','instructions','raw_words','raw_bytes'):self.assertNotIn('"'+field+'"',json.dumps(r))

    def test_instruction_inverse_and_every_bit(self):
        count=0
        for pc,(word,row) in self.rows[0].items():
            self.assertEqual(encode(row,pc),word)
            for bit in range(32):
                changed=word^(1<<bit);count+=1
                try:r=a.decode_selected(changed,pc)
                except a.c.FormatError:continue
                if r is not None:self.assertNotEqual(r,row);self.assertEqual(encode(r,pc),changed)
        self.assertEqual(count,3232)

    def test_every_payload_bit_refuses(self):
        count=0
        with patch.object(a,'decode_selected') as decode:
            for read,raw in self.payloads[0].items():
                i=READS.index(read)
                for off in range(len(raw)):
                    for bit in range(8):
                        mutated=raw[:off]+bytes([raw[off]^(1<<bit)])+raw[off+1:];count+=1
                        with self.assertRaises(a.c.FormatError):

                            if i==0:a.constant_evidence(FakeDB(mutated),a.DATA5_MAPPING,0x804370e0)
                            else:a.range_evidence(FakeDB(mutated),a.TEXT_MAPPING,*RANGES[0][:2])
            decode.assert_not_called()
        self.assertEqual(count,3264)

    def test_flags_capture_and_translation_order(self):
        r={pc:row for pc,(_,row) in self.rows[0].items()}
        self.assertEqual(r[0x80047abc]['displacement'],0x84)
        self.assertEqual(r[0x80047ad4]['mnemonic'],'extsb')
        self.assertEqual(r[0x80047b0c]['target'],'8020aefc')
        self.assertEqual([r[pc]['displacement'] for pc in range(0x80047b4c,0x80047b64,4)], [0x20,0x120,0x24,0x130,0x28,0x140])
        self.assertEqual([r[pc]['immediate'] for pc in (0x80047b78,0x80047ba8,0x80047bd8)],[122,121,120])

    def test_semantic_and_flow_drift_refuse(self):
        raw=self.payloads[0][READS[1]]
        for attr,value in [('OPERAND_DIGESTS',{0x80047aa4:'bad'}),('FLOW_DIGESTS',{0x80047aa4:(3,'bad')}),('CALLS',{0x80047aa4:()})]:
            with patch.object(a,attr,value):
                with self.assertRaises(a.c.FormatError):a.range_evidence(FakeDB(raw),a.TEXT_MAPPING,0x80047aa4,404)

if __name__=='__main__':unittest.main()
