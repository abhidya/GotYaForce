import copy
import hashlib
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_contact_pairing_evidence as a
ROOT=Path(__file__).resolve().parents[3]
SNAPSHOTS=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
class Fake:
    def __init__(self,raw=b''):self.raw=raw;self.calls=[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]
class Synthetic(unittest.TestCase):
    def test_exact_scope_and_mapping(self):
        for address,width in [(0x8002d35c,564),(0x8002d35c,556),(0x8002d58c,560),(True,560)]:
            db=Fake()
            with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.prior.TEXT_MAPPING,address,width)
            self.assertEqual(db.calls,[])
        m=list(a.prior.TEXT_MAPPING);m[0]+=4;db=Fake()
        with self.assertRaises(a.c.FormatError):a.range_evidence(db,tuple(m),*a.RANGE)
        self.assertEqual(db.calls,[])
    def test_corruption_before_decoder(self):
        with patch.object(a.prior,'decode_selected')as decode:
            for raw in [b'',bytes(560),bytes(561)]:
                with self.assertRaises(a.c.FormatError):a.range_evidence(Fake(raw),a.prior.TEXT_MAPPING,*a.RANGE)
            decode.assert_not_called()
    def test_auth_first(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF')as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()
    def test_index_extent(self):
        lines=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        i=next(i for i,line in enumerate(lines)if line.startswith('8002d35c\t'))
        self.assertTrue(lines[i+1].startswith('8002d58c\t'))
        self.assertEqual(0x8002d58c-0x8002d35c,560)
@unittest.skipUnless(all((SNAPSHOTS/n).is_file()for n in ['db.3.gbf','db.4.gbf']),'local snapshots absent')
class Archives(unittest.TestCase):
    def test_both_exact_reads(self):
        results=[]
        for name in ['db.3.gbf','db.4.gbf']:
            data=(SNAPSHOTS/name).read_bytes();digest=hashlib.sha256(data).hexdigest();calls=[];original=a.c.GBF.chain
            def trace(db,*args):calls.append(args);return original(db,*args)
            with patch.object(a.c.GBF,'chain',trace):a.c.inspect(data,digest)
            auth=calls[:];calls.clear()
            with patch.object(a.c.GBF,'chain',trace):r=a.inspect(data,digest)
            self.assertEqual(calls,auth+[(21,0x8002d35c-a.prior.TEXT_MAPPING[0],560,a.prior.TEXT_MAPPING[-2])])
            self.assertEqual(r['ranges'][0]['represented_instructions'],140)
            self.assertTrue(r['ranges'][0]['semantics']['support_pointer_compares_hit'])
            results.append(r['ranges'])
        self.assertEqual(*results)
    def test_semantic_mutations_and_caller_order(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes();rows=[];original=a.summarize
        def capture(r):rows.extend(copy.deepcopy(r));return original(r)
        with patch.object(a,'summarize',capture):a.inspect(data,hashlib.sha256(data).hexdigest())
        for pc,key,value in [('8002d568','displacement',-21340),('8002d56c','immediate',0),
            ('8002d3b0','immediate',0),('8002d384','displacement',0x20),('8002d38c','MB',19),
            ('8002d39c','mnemonic','extsh'),('8002d3a8','immediate',24),('8002d3d0','rA',28),
            ('8002d40c','rA',0),('8002d424','rB',26),('8002d43c','rB',27),
            ('8002d448','immediate',44),('8002d460','mnemonic','lwz'),('8002d468','rS',3),
            ('8002d4b4','target','80039f6c'),('8002d4d0','BI',1),('8002d4dc','rA',28),
            ('8002d4e4','displacement',0x54)]:
            changed=copy.deepcopy(rows);next(r for r in changed if r['address']==pc)[key]=value
            with self.assertRaises(a.c.FormatError):a.summarize(changed)
        # Separate revalidation of already-selected caller, not main reader scope.
        caller=a.prior.base;captured=[];decode=caller.decode_selected
        def read(w,pc):
            r=decode(w,pc)
            if 0x8002bd98<=pc<=0x8002bda0:captured.append((pc,r))
            return r
        with patch.object(caller,'decode_selected',read):caller.inspect(data,hashlib.sha256(data).hexdigest())
        self.assertEqual([(pc,r['mnemonic'],r['target'])for pc,r in captured],
            [(0x8002bd98,'bl','8002cf80'),(0x8002bd9c,'bl','8002d35c'),(0x8002bda0,'bl','8002d58c')])
if __name__=='__main__':unittest.main()
