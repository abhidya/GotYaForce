import copy
import hashlib
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_contact_adjust_evidence as a
ROOT=Path(__file__).resolve().parents[3]
SNAPSHOTS=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
class Fake:
    def __init__(self,raw=b''):self.raw=raw;self.calls=[]
    def chain(self,*args):self.calls.append(args);return self.raw,[]
class Synthetic(unittest.TestCase):
    def test_exact_scope_and_mapping(self):
        for address,width in [(0x8003a05c,116),(0x8003a05c,108),(0x8003a0cc,112),(True,112)]:
            db=Fake()
            with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.base.TEXT_MAPPING,address,width)
            self.assertEqual(db.calls,[])
        m=list(a.base.TEXT_MAPPING);m[0]+=4;db=Fake()
        with self.assertRaises(a.c.FormatError):a.range_evidence(db,tuple(m),*a.RANGE)
        self.assertEqual(db.calls,[])
    def test_corruption_before_decoder(self):
        with patch.object(a.base,'decode_selected')as decode:
            for raw in [b'',bytes(112),bytes(113)]:
                with self.assertRaises(a.c.FormatError):a.range_evidence(Fake(raw),a.base.TEXT_MAPPING,*a.RANGE)
            decode.assert_not_called()
    def test_auth_first(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF')as db:
            with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
            db.assert_not_called()
    def test_index_extent(self):
        lines=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        i=next(i for i,line in enumerate(lines)if line.startswith('8003a05c\t'))
        self.assertTrue(lines[i+1].startswith('8003a0cc\t'))
        self.assertEqual(0x8003a0cc-0x8003a05c,112)
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
            self.assertEqual(calls,auth+[(21,0x8003a05c-a.base.TEXT_MAPPING[0],112,a.base.TEXT_MAPPING[-2])])
            self.assertEqual(r['ranges'][0]['represented_instructions'],28)
            self.assertTrue(r['ranges'][0]['semantics']['zero_flags_return'])
            results.append(r['ranges'])
        self.assertEqual(*results)
    def test_existing_selections_separately(self):
        # Separate explicit revalidation: never broadens main112-byte inspect.
        import read_archived_double_action_evidence as double
        import read_archived_initial_contact_evidence as contact
        for name in ['db.3.gbf','db.4.gbf']:
            data=(SNAPSHOTS/name).read_bytes();auth=a.c.inspect(data,hashlib.sha256(data).hexdigest())
            db=a.c.GBF(data);t=db.tables();b,s=db.rows(t['Memory Blocks']),db.rows(t['Sub Memory Blocks'])
            im=int(auth['image_offset'],16);a.base.command.mappings(b,s,im)
            mapping,_=a.base.normal.mapping_evidence(b,s,im,a.base.TEXT_MAPPING)
            for reader,pc,width,summary in [(double,0x8020ba54,36,a.summarize_vector_add),
                                           (contact,0x8002cf80,536,a.summarize_post_adjust)]:
                rows=[];calls=[];decode=reader.decode_selected;chain=a.c.GBF.chain
                def capture(w,site):
                    r=decode(w,site);rows.append(dict(address=f'{site:08x}',**r));return r
                def trace(obj,*args):calls.append(args);return chain(obj,*args)
                with patch.object(reader,'decode_selected',capture),patch.object(a.c.GBF,'chain',trace):
                    reader.range_evidence(db,mapping,pc,width)
                self.assertEqual(calls,[(mapping[-1],pc-mapping[0],width,mapping[-2])])
                summary(rows)
                mutations=([(3,'W',1),(4,'displacement',0),(5,'I',1),(2,'fA',4)]if width==36 else
                    [(next(i for i,r in enumerate(rows)if r['address']==site),key,value)for site,key,value in
                     [('8002d094','displacement',0x83),('8002d0a0','displacement',0x30),
                      ('8002d0a8','displacement',0x10),('8002d0b4','fA',0),('8002d0cc','target','8003a05c')]])
                for i,key,value in mutations:
                    changed=copy.deepcopy(rows);changed[i][key]=value
                    with self.assertRaises(a.c.FormatError):summary(changed)
    def test_semantic_mutations(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes();rows=[];original=a.summarize
        def capture(r):rows.extend(copy.deepcopy(r));return original(r)
        with patch.object(a,'summarize',capture):a.inspect(data,hashlib.sha256(data).hexdigest())
        for pc,key,value in [('8003a06c','rS',5),('8003a074','rS',3),('8003a078','displacement',0x1dc),
            ('8003a07c','Rc',0),('8003a080','BO',4),('8003a084','immediate',0),
            ('8003a088','immediate',0x1d0),('8003a08c','rB',3),('8003a090','target','8003a0cc'),
            ('8003a094','rA',5),('8003a09c','target','8003a0c4'),('8003a0a0','rA',3),
            ('8003a0a4','immediate',0x1d0),('8003a0a8','rA',6),('8003a0ac','target','8003a0cc')]:
            changed=copy.deepcopy(rows);next(r for r in changed if r['address']==pc)[key]=value
            with self.assertRaises(a.c.FormatError):a.summarize(changed)
if __name__=='__main__':unittest.main()
