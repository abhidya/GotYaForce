import hashlib
import copy
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_contact_height_evidence as a
ROOT=Path(__file__).resolve().parents[3]
SNAPSHOTS=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
class Fake:
    def __init__(self,raw=b''):self.raw=raw;self.calls=[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]
class Synthetic(unittest.TestCase):
    def test_exact_scope_refuses_before_read(self):
        for address,width in [(0x8002cf80,988),(0x8002cf80,532),(0x8002d198,536),(True,536)]:
            db=Fake()
            with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.prior.TEXT_MAPPING,address,width)
            self.assertEqual(db.calls,[])
        for address,width in [(0x80436f68,4),(0x80436f6c,8),(True,4)]:
            db=Fake()
            with self.assertRaises(a.c.FormatError):a.constant_evidence(db,address,width)
            self.assertEqual(db.calls,[])
    def test_constant_corruption(self):
        for raw in [b'',bytes(4),bytes(5)]:
            with self.assertRaises(a.c.FormatError):a.constant_evidence(Fake(raw),a.CONSTANT)
    def test_auth_first(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF')as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()
    def test_index_extent(self):
        lines=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        i=next(i for i,line in enumerate(lines)if line.startswith('8002cf80\t'))
        self.assertTrue(lines[i+1].startswith('8002d198\t'))
        self.assertEqual(0x8002d198-0x8002cf80,536)
@unittest.skipUnless(all((SNAPSHOTS/n).is_file()for n in ['db.3.gbf','db.4.gbf']),'local snapshots absent')
class Archives(unittest.TestCase):
    def test_semantic_mutations(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes();rows=[];original=a.summarize_prefix
        def capture(r):rows.extend(copy.deepcopy(r));return original(r)
        with patch.object(a,'summarize_prefix',capture):a.inspect(data,hashlib.sha256(data).hexdigest())
        for pc,key,value in [('8002d178','displacement',-21340),('8002d164','mnemonic','lha'),
            ('8002cff4','rA',27),('8002cff8','rA',28),('8002d004','rA',0),
            ('8002cfb4','displacement',0x84),('8002cfc0','displacement',0x88),
            ('8002cfc8','displacement',0x68),('8002cfd0','displacement',0x3e5),
            ('8002cfd4','fA',0),('8002cfe0','fS',1),('8002d014','immediate',44),
            ('8002d028','displacement',8),('8002d02c','mnemonic','lwz'),
            ('8002d030','rS',0),('8002d034','displacement',4),
            ('8002d058','rA',5),('8002d060','rS',3),('8002d080','target','80039f6c')]:
            changed=copy.deepcopy(rows);next(r for r in changed if r['address']==pc)[key]=value
            with self.assertRaises(a.c.FormatError):a.summarize_prefix(changed)
    def test_both_exact_reads(self):
        results=[]
        for name in ['db.3.gbf','db.4.gbf']:
            data=(SNAPSHOTS/name).read_bytes();digest=hashlib.sha256(data).hexdigest();calls=[];original=a.c.GBF.chain
            def trace(db,*args):calls.append(args);return original(db,*args)
            with patch.object(a.c.GBF,'chain',trace):a.c.inspect(data,digest)
            auth=calls[:];calls.clear()
            with patch.object(a.c.GBF,'chain',trace):r=a.inspect(data,digest)
            self.assertEqual(calls,auth+[(21,0x8002cf80-a.prior.TEXT_MAPPING[0],536,a.prior.TEXT_MAPPING[-2]),(263,0x80436f6c-0x80436a20,4,27360)])
            self.assertEqual(r['constants'][0]['value'],-10000.0)
            self.assertEqual(r['ranges'][0]['represented_instructions'],134)
            self.assertEqual(r['ranges'][0]['unrepresented_instructions'],0)
            results.append((r['ranges'],r['constants']))
        self.assertEqual(*results)
if __name__=='__main__':unittest.main()
