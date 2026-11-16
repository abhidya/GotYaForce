"""Fixed-scope synthetic controls and optional same-snapshot inverse validation. No original words embedded."""
import hashlib,json,re,unittest
from pathlib import Path
import read_archived_jobj_leaf_helpers_evidence as a
from test_archived_loadjoint_foundation_evidence import encode as prior_encode
from test_archived_mass_preparation_evidence import encode as mass_encode
ROOT=Path(__file__).resolve().parents[3]
SNAPS=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
def encode(row,pc):return mass_encode(row,pc)if row['mnemonic']=='mulhwu'else prior_encode(row,pc)
class FakeDB:
 def __init__(self,raw=b''):self.raw=raw;self.calls=[]
 def chain(self,*args):self.calls.append(args);return self.raw,[]
class Tests(unittest.TestCase):
 def test_exact_scope_independent_bounds(self):
  self.assertEqual([(hex(p),n)for p,n,_ in a.RANGES],[('0x8023dae4',152),('0x8025888c',1140),('0x802596a4',236),('0x80258778',276),('0x8023dc4c',108)])
  self.assertEqual(sum(n for _,n,_ in a.RANGES),1912)
  lines=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines();symbols=(ROOT/'research/symbols/GG4E-CSM-20220412.map').read_text()
  for pc,n,_ in a.RANGES:
   i=next(i for i,s in enumerate(lines)if s.startswith(f'{pc:08x}\t'));self.assertTrue(lines[i+1].startswith(f'{pc+n:08x}\t'))
   c=(ROOT/'research/decomp/ghidra-export'/lines[i].split('\t')[2]).read_text();self.assertTrue(c.split(f'// ==== {pc:08x} ',1)[1].split('// ==== ',1)[1].startswith(f'{pc+n:08x} '));self.assertRegex(symbols,rf'(?m)^{pc:08x} {n:08x} {pc:08x} 0 ')
 def test_unlisted_before_io(self):
  for pc,n,_ in a.RANGES:
   for pp,nn in [(pc+4,n),(pc,n+4),(float(pc),n),(pc,True)]:
    db=FakeDB()
    with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.TEXT_MAPPING,pp,nn)
    self.assertEqual(db.calls,[])
 def test_mapping_before_io(self):
  db=FakeDB();m=list(a.TEXT_MAPPING);m[0]+=4
  with self.assertRaises(a.c.FormatError):a.range_evidence(db,tuple(m),*a.RANGES[0][:2])
  self.assertEqual(db.calls,[])
 def test_short_and_wrong_digest(self):
  for raw in [b'',bytes(a.RANGES[0][1])]:
   db=FakeDB(raw)
   with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.TEXT_MAPPING,*a.RANGES[0][:2])
   self.assertEqual(len(db.calls),1)
 def test_mulhwu_inverse_and_bit_controls(self):
  for r in [dict(mnemonic='mulhwu',rD=7,rA=13,rB=29,Rc=0),dict(mnemonic='mulhwu',rD=31,rA=2,rB=11,Rc=1)]:
   w=encode(r,0x10000000);self.assertEqual(a.decode_selected(w,0x10000000),r)
   for bit in range(32):
    v=w^(1<<bit)
    try:d=a.decode_selected(v,0x10000000)
    except a.c.FormatError:continue
    if d is not None:self.assertEqual(encode(d,0x10000000),v)
 def test_decoder_types(self):
  for w,pc in [(True,0),(-1,0),(1<<32,0),(0,1),(0,True)]:
   with self.assertRaises(a.c.FormatError):a.decode_selected(w,pc)
 @unittest.skipUnless((SNAPS/'db.3.gbf').is_file()and(SNAPS/'db.4.gbf').is_file(),'original snapshots remain local; never fetch')
 def test_both_authenticated_snapshots(self):
  common=[]
  for name in ['db.3.gbf','db.4.gbf']:
   data=(SNAPS/name).read_bytes();result=a.inspect(data,hashlib.sha256(data).hexdigest());self.assertEqual(sum(r['represented_instructions']for r in result['ranges']),478);common.append([(r['sha256'],r['operand_sha256'])for r in result['ranges']])
   db=a.c.GBF(data)
   for pc,n,_ in a.RANGES:
    raw,_=db.chain(a.TEXT_MAPPING[-1],pc-a.TEXT_MAPPING[0],n,a.TEXT_MAPPING[-2])
    for off in range(0,n,4):
     word=a.c.integer(raw,off,'I');row=a.decode_selected(word,pc+off);self.assertEqual(encode(row,pc+off),word)
     for bit in range(32):
      changed=word^(1<<bit)
      try:d=a.decode_selected(changed,pc+off)
      except a.c.FormatError:continue
      if d is not None:self.assertEqual(encode(d,pc+off),changed)
  self.assertEqual(common[0],common[1])
if __name__=='__main__':unittest.main()
