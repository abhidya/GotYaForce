#!/usr/bin/env python3
"""Fixed single-cell controls; existing dispatch/stub validation, no original fixtures."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_full_selector_zero_evidence as a
import read_archived_actor_mode1_evidence as mode1

ROOT=Path(__file__).resolve().parents[3]
BASE=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
READ=(199,0x802d36a8-0x802bae60,4,1000128)
class FakeDB:
    def __init__(self,raw=b''):self.raw,self.calls=raw,[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]

class SyntheticTests(unittest.TestCase):
    def test_fixed_cell_and_reused_ranges(self):
        self.assertEqual(a.CELL,('full0',0x802d36a8,0x8005f238,'8868a8515e4b649802f66057c61600c1899cea349f7d393786d886caaff607a4'))
        self.assertIn((0x80055568,292,a.REUSED_EVIDENCE[0]['sha256']),mode1.RANGES)
        self.assertIn((0x8005f238,4,a.REUSED_EVIDENCE[1]['sha256']),a.prior.RANGES)
        self.assertEqual(((-32723<<16)+13992)&0xffffffff,0x802d36a8)
        self.assertTrue(all(x['read_here'] is False for x in a.REUSED_EVIDENCE))

    def test_unselected_address_and_map_refuse_before_read(self):
        for address in (True,float(0x802d36a8),0x802d36a4,0x802d36ac,0x802d37a8,-1):
            db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.DATA3_MAPPING,address)
            self.assertFalse(db.calls)
        for i,v in enumerate(a.DATA3_MAPPING):
            m=list(a.DATA3_MAPPING);m[i]=v+1 if type(v)is int else 'wrong';db=FakeDB()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,tuple(m),0x802d36a8)
            self.assertFalse(db.calls)

    def test_width_digest_and_target_fail_closed(self):
        for n in (0,3,4,5):
            with self.assertRaises(a.c.FormatError):a.cell_evidence(FakeDB(bytes(n)),a.DATA3_MAPPING,0x802d36a8)
        # Synthetic pin makes target validation independently reachable without original bytes.
        raw=bytes.fromhex('12345678')
        with patch.object(a,'CELL',('full0',0x802d36a8,0x11111111,hashlib.sha256(raw).hexdigest())):
            with self.assertRaisesRegex(a.c.FormatError,'target'):a.cell_evidence(FakeDB(raw),a.DATA3_MAPPING,0x802d36a8)

    def test_authentication_precedes_parser(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF') as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()

    def test_cli_no_general_options(self):
        for opt in ('--address','--width','--dump','--pointer','--instructions'):
            with patch('sys.argv',['reader','none',opt,'0']),contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit):a.main()

@unittest.skipUnless(all((BASE/n).is_file() for n in ('db.3.gbf','db.4.gbf')),'optional private snapshots; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports=[];cls.cells=[];cls.dispatch=[];cls.stubs=[]
        chain=a.c.GBF.chain
        for name in ('db.3.gbf','db.4.gbf'):
            data=(BASE/name).read_bytes();digest=hashlib.sha256(data).hexdigest();trace=[];cells=[]
            def traced(db,*args):
                trace.append(args);result=chain(db,*args)
                if args==READ:cells.append(result[0])
                return result
            with patch.object(a.c.GBF,'chain',traced):auth=a.c.inspect(data,digest)
            auth_trace=trace[:];trace.clear()
            with patch.object(a.c.GBF,'chain',traced):report=a.inspect(data,digest)
            assert trace==auth_trace+[READ]
            cls.reports.append(report);cls.cells.append(cells[0])
            # Revalidate only already-selected whole55568 and bare-return ranges, not new bodies.
            db=a.c.GBF(data);t=db.tables();bs,ss=db.rows(t['Memory Blocks']),db.rows(t['Sub Memory Blocks'])
            m,_=a.normal.mapping_evidence(bs,ss,int(auth['image_offset'],16),mode1.TEXT_MAPPING)
            raw,_=db.chain(m[-1],0x80055568-m[0],292,m[-2]);assert hashlib.sha256(raw).hexdigest()==a.REUSED_EVIDENCE[0]['sha256']
            cls.dispatch.append({pc:mode1.decode_selected(int.from_bytes(raw[pc-0x80055568:pc-0x80055568+4],'big'),pc) for pc in range(0x80055568,0x8005568c,4)})
            stub,_=db.chain(m[-1],0x8005f238-m[0],4,m[-2]);assert hashlib.sha256(stub).hexdigest()==a.REUSED_EVIDENCE[1]['sha256']
            cls.stubs.append(a.prior.decode_selected(int.from_bytes(stub,'big'),0x8005f238))

    def test_both_snapshots_and_summary_boundary(self):
        self.assertEqual(self.cells[0],self.cells[1]);self.assertEqual(int.from_bytes(self.cells[0],'big'),0x8005f238)
        for k in ('mappings','cells','selection_basis','reused_evidence'):self.assertEqual(self.reports[0][k],self.reports[1][k])
        for r in self.reports:
            self.assertEqual((r['selection_basis']['reads'],r['selection_basis']['bytes']),(1,4))
            for forbidden in ('instructions','mnemonic','raw_bytes','raw_words'):self.assertNotIn('"'+forbidden+'"',json.dumps(r))

    def test_existing_dispatch_resolves_exact_base(self):
        for rows in self.dispatch:
            self.assertEqual(rows[0x800555fc],dict(mnemonic='addis',rD=4,rA=0,immediate=-32723))
            self.assertEqual(rows[0x8005560c],dict(mnemonic='addi',rD=4,rA=4,immediate=13992))
            self.assertEqual(rows[0x800555f8],dict(mnemonic='extsb',rS=30,rA=0,Rc=0))
            self.assertEqual(rows[0x80055604],dict(mnemonic='rlwinm',rS=0,rA=0,SH=2,MB=0,ME=29,Rc=0))
            self.assertEqual(rows[0x80055610],dict(mnemonic='lwzx',rD=12,rA=4,rB=0))
            self.assertEqual(rows[0x80055618]['mnemonic'],'bctrl')
            self.assertEqual(rows[0x800555cc]['displacement'],0x5da)

    def test_reused_target_is_actual_bare_return(self):
        for r in self.stubs:self.assertEqual(r,dict(mnemonic='blr',BO=20,BI=0,BH=0,LK=0))

    def test_every_cell_bit_mutation_refuses(self):
        raw=self.cells[0];count=0
        for off in range(4):
            for bit in range(8):
                mutated=raw[:off]+bytes([raw[off]^(1<<bit)])+raw[off+1:];count+=1
                with self.assertRaises(a.c.FormatError):a.cell_evidence(FakeDB(mutated),a.DATA3_MAPPING,0x802d36a8)
        self.assertEqual(count,32)

if __name__=='__main__':unittest.main()
