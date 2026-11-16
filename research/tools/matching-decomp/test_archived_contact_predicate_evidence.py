import copy
import hashlib
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_contact_predicate_evidence as a
ROOT=Path(__file__).resolve().parents[3]
SNAPSHOTS=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
class Fake:
    def __init__(self,raw=b''):self.raw=raw;self.calls=[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]
class Synthetic(unittest.TestCase):
    def test_exact_scope_and_mapping(self):
        for address,width in [(0x80039f6c,244),(0x80039f6c,236),(0x8003a05c,240),(True,240)]:
            db=Fake()
            with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.base.TEXT_MAPPING,address,width)
            self.assertEqual(db.calls,[])
        m=list(a.base.TEXT_MAPPING);m[0]+=4;db=Fake()
        with self.assertRaises(a.c.FormatError):a.range_evidence(db,tuple(m),*a.RANGE)
        self.assertEqual(db.calls,[])
    def test_corruption_before_decoder(self):
        with patch.object(a,'decode_selected')as decode:
            for raw in [b'',bytes(240),bytes(241)]:
                with self.assertRaises(a.c.FormatError):a.range_evidence(Fake(raw),a.base.TEXT_MAPPING,*a.RANGE)
            decode.assert_not_called()
    def test_cell_scope_and_corruption(self):
        for pc,w in [(0x80436f68,4),(0x80437004,8),(0x80436fd0,4),(True,4)]:
            db=Fake()
            with self.assertRaises(a.c.FormatError):a.cell_evidence(db,pc,w)
            self.assertEqual(db.calls,[])
        for pc,w,_ in a.CELLS:
            with self.assertRaises(a.c.FormatError):a.cell_evidence(Fake(bytes(w)),pc,w)
    def test_auth_first(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF')as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()
    def test_index_extent(self):
        lines=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        i=next(i for i,line in enumerate(lines)if line.startswith('80039f6c\t'))
        self.assertTrue(lines[i+1].startswith('8003a05c\t'))
        self.assertEqual(0x8003a05c-0x80039f6c,240)
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
            self.assertEqual(calls,auth+[(21,0x80039f6c-a.base.TEXT_MAPPING[0],240,a.base.TEXT_MAPPING[-2])]+[(263,pc-0x80436a20,w,27360)for pc,w,_ in a.CELLS])
            self.assertEqual([x['bits']for x in r['cells']],['3dcccccd','3fe0000000000000','4008000000000000'])
            self.assertEqual(r['ranges'][0]['represented_instructions'],60)
            self.assertTrue(r['ranges'][0]['semantics']['reload_radii'])
            results.append(r['ranges'])
        self.assertEqual(*results)
    def test_semantic_mutations(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes();rows=[];original=a.summarize
        def capture(r):rows.extend(copy.deepcopy(r));return original(r)
        with patch.object(a,'summarize',capture):a.inspect(data,hashlib.sha256(data).hexdigest())
        for pc,key,value in [('80039f74','displacement',-31416),('80039f8c','rA',31),
            ('80039fa4','rA',30),('80039f94','BB',1),('80039f98','BO',12),
            ('80039fbc','immediate',0),('80039fc4','target','8020ba54'),
            ('80039fd0','BI',0),('80039fe8','mnemonic','fmadd'),('8003a024','rA',30),
            ('8003a028','fA',0),('8003a038','immediate',0)]:
            changed=copy.deepcopy(rows);next(r for r in changed if r['address']==pc)[key]=value
            with self.assertRaises(a.c.FormatError):a.summarize(changed)
if __name__=='__main__':unittest.main()
