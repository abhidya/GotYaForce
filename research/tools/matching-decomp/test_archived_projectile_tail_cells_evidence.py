#!/usr/bin/env python3
"""Fixed-cell controls and optional local archive proofs; never fetch originals."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import struct
import unittest
from unittest.mock import patch
import read_archived_projectile_tail_cells_evidence as a
import read_archived_actor_mode1_evidence as mode1
import read_archived_projectile_initialization_evidence as initialization
ROOT=Path(__file__).resolve().parents[3]
BASE=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
class FakeDB:
    def __init__(self,raw=b''):self.raw,self.calls=raw,[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]
class SyntheticTests(unittest.TestCase):
    def test_fixed_extent_semantics_and_reuse(self):
        self.assertEqual([(r[1]-0x802d6da0,r[2],r[3],r[4])for r in a.CELLS],[(0,2,'>h',14),(16,4,'>f',40.0),(20,4,'>I',4),(40,4,'>f',0.30000001192092896),(48,4,'>f',2.0)])
        self.assertEqual(0x802d6d68+56,0x802d6da0)
        self.assertEqual(sum(r[2]for r in a.CELLS),18)
        for item,module in zip(a.REUSED_EVIDENCE,[initialization,mode1]):
            self.assertIn((int(item['address'],16),item['width'],item['sha256']),module.RANGES)
            self.assertFalse(item['read_here'])
    def test_scope_types_duplicates_and_mapping_before_read(self):
        for row in a.CELLS:
            _,pc,width,*_=row
            for p,w in [(pc-1,width),(pc+1,width),(pc,width+1),(pc,width-1),(True,width),(float(pc),width),(pc,True),(pc,float(width))]:
                db=FakeDB()
                with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA3_MAPPING,p,w)
                self.assertFalse(db.calls)
            with patch.object(a,'CELLS',a.CELLS*2):
                db=FakeDB()
                with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA3_MAPPING,pc,width)
                self.assertFalse(db.calls)
            for i,v in enumerate(a.DATA3_MAPPING):
                m=list(a.DATA3_MAPPING);m[i]=v+1 if type(v)is int else 'wrong';db=FakeDB()
                with self.assertRaises(a.c.FormatError):a.cell_evidence(db,tuple(m),pc,width)
                self.assertFalse(db.calls)
    def test_wrong_width_and_digest(self):
        for row in a.CELLS:
            for n in [0,row[2]-1,row[2],row[2]+1]:
                with self.assertRaises(a.c.FormatError):a.cell_evidence(FakeDB(bytes(n)),a.DATA3_MAPPING,row[1],row[2])
    def test_independent_endian_signed_and_float_semantics(self):
        for fmt,value,raw in [('>h',-32767,bytes.fromhex('8001')),('>I',0x81234567,bytes.fromhex('81234567')),('>f',-1.5,bytes.fromhex('bfc00000'))]:
            width=len(raw);row=('invented',0x802d6da0,width,fmt,value,hashlib.sha256(raw).hexdigest())
            with patch.object(a,'CELLS',(row,)):
                self.assertEqual(a.cell_evidence(FakeDB(raw),a.DATA3_MAPPING,row[1],width)['value'],value)
            with patch.object(a,'CELLS',(row[:4]+(value+1,row[5]),)):
                with self.assertRaisesRegex(a.c.FormatError,'semantic'):a.cell_evidence(FakeDB(raw),a.DATA3_MAPPING,row[1],width)
    def test_authentication_first(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF')as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()
    def test_cli_closed(self):
        for option in ['--address','--width','--dump','--helper','--pointer']:
            with patch('sys.argv',['reader','none',option,'0']),contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit):a.main()
@unittest.skipUnless(all((BASE/n).is_file()for n in ['db.3.gbf','db.4.gbf']),'optional private snapshots; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports=[];cls.payloads=[];chain=a.c.GBF.chain
        cls.reads=[(a.DATA3_MAPPING[-1],r[1]-a.DATA3_MAPPING[0],r[2],a.DATA3_MAPPING[-2])for r in a.CELLS]
        for name in ['db.3.gbf','db.4.gbf']:
            data=(BASE/name).read_bytes();digest=hashlib.sha256(data).hexdigest();trace=[];payloads={}
            def traced(db,*args):
                trace.append(args);result=chain(db,*args)
                if args in cls.reads:payloads[args]=result[0]
                return result
            with patch.object(a.c.GBF,'chain',traced):a.c.inspect(data,digest)
            auth_trace=trace[:];trace.clear()
            with patch.object(a.c.GBF,'chain',traced):report=a.inspect(data,digest)
            assert trace==auth_trace+cls.reads
            cls.reports.append(report);cls.payloads.append(payloads)
    def test_both_authenticated_snapshots_exact(self):
        self.assertEqual(self.reports[0]['cells'],self.reports[1]['cells'])
        self.assertEqual(self.reports[0]['selection_basis']['bytes'],18)
    def test_all_payload_bit_mutations_refused(self):
        count=0
        for row,args in zip(a.CELLS,self.reads):
            raw=self.payloads[0][args]
            for bit in range(len(raw)*8):
                changed=bytearray(raw);changed[bit//8]^=1<<(bit%8)
                with self.assertRaises(a.c.FormatError):a.cell_evidence(FakeDB(bytes(changed)),a.DATA3_MAPPING,row[1],row[2])
                count+=1
        self.assertEqual(count,144)
    def test_output_is_summary_only(self):
        report=self.reports[0];text=json.dumps(report,allow_nan=False)
        for field in ['instructions','raw','bits','bytes_hex','operands']:
            self.assertNotIn('"'+field+'":',text)
        self.assertTrue(all(set(c)=={'label','address','offset','width','format','value','sha256','spans'}for c in report['cells']))
        self.assertFalse(report['selection_basis']['helpers_read']);self.assertFalse(report['selection_basis']['whole_row_read'])
if __name__=='__main__':unittest.main()
