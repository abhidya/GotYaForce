"""Fixed allocator evidence: synthetic inverse tests and optional local snapshots."""
import contextlib,hashlib,io,json,re,sys,unittest
from pathlib import Path
from unittest.mock import patch
import read_archived_jobj_allocator_evidence as a
from test_archived_loadjoint_foundation_evidence import encode as prior_encode
from test_archived_projectile_resource_evidence import FakeDB,invented_operands
ROOT=Path(__file__).resolve().parents[3]
SNAPS=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
def encode(r,pc):
 if r['mnemonic']=='addze':return 31<<26|r['rD']<<21|r['rA']<<16|r['OE']<<10|202<<1|r['Rc']
 if r['mnemonic']=='addic.':return 13<<26|r['rD']<<21|r['rA']<<16|(r['immediate']&65535)
 return prior_encode(r,pc)
class Tests(unittest.TestCase):
 def test_frozen_independent_extents(self):
  self.assertEqual([(hex(p),n)for p,n,_ in a.RANGES],[('0x8025cef0',88),('0x8025ccd0',456),('0x8025ca6c',612)])
  index=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines();symbols=(ROOT/'research/symbols/GG4E-CSM-20220412.map').read_text()
  for pc,n,_ in a.RANGES:
   i=next(i for i,s in enumerate(index)if s.startswith(f'{pc:08x}\t'));self.assertTrue(index[i+1].startswith(f'{pc+n:08x}\t'))
   src=(ROOT/'research/decomp/ghidra-export'/index[i].split('\t')[2]).read_text();self.assertTrue(src.split(f'// ==== {pc:08x} ',1)[1].split('// ==== ',1)[1].startswith(f'{pc+n:08x} '));self.assertRegex(symbols,rf'(?m)^{pc:08x} {n:08x} {pc:08x} 0 ')
 def test_new_forms_independent_inverse_bits(self):
  rows=invented_operands()+[dict(mnemonic='addze',rD=7,rA=19,OE=0,Rc=rc)for rc in [0,1]]+[dict(mnemonic='addic.',rD=11,rA=22,immediate=-123)]
  for row in rows:
   word=encode(row,0x10000000);self.assertEqual(a.decode_selected(word,0x10000000),row)
   for bit in range(32):
    changed=word^(1<<bit)
    try:other=a.decode_selected(changed,0x10000000)
    except a.c.FormatError:continue
    if other is not None:self.assertEqual(encode(other,0x10000000),changed)
 def test_new_form_reserved_and_oe_refuse(self):
  for word in [31<<26|202<<1|1<<11,31<<26|202<<1|1<<10]:
   with self.assertRaises(a.c.FormatError):a.decode_selected(word,0)
  for w,p in [(True,0),(-1,0),(1<<32,0),(0,1),(0,True)]:
   with self.assertRaises(a.c.FormatError):a.decode_selected(w,p)
 def test_bounds_maps_before_io(self):
  for pc,n,_ in a.RANGES:
   for p,size in [(pc+4,n),(pc,n+4),(float(pc),n),(pc,True)]:
    db=FakeDB()
    with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.TEXT_MAPPING,p,size)
    self.assertFalse(db.calls)
   for k,v in enumerate(a.TEXT_MAPPING):
    m=list(a.TEXT_MAPPING);m[k]=v+1 if type(v)is int else 'wrong';db=FakeDB()
    with self.assertRaises(a.c.FormatError):a.range_evidence(db,tuple(m),pc,n)
    self.assertFalse(db.calls)
 def test_digest_before_decode(self):
  with patch.object(a,'decode_selected')as decode:
   for p,n,_ in a.RANGES:
    with self.assertRaises(a.c.FormatError):a.range_evidence(FakeDB(bytes(n)),a.TEXT_MAPPING,p,n)
   decode.assert_not_called()
 def test_auth_first(self):
  with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF')as db:
   with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
   db.assert_not_called()
 def test_closed_cli(self):
  for flag in ['--address','--width','--heap','--globals','--raw','--instructions']:
   with patch.object(sys,'argv',['reader',flag,'1']),contextlib.redirect_stderr(io.StringIO()):
    with self.assertRaises(SystemExit)as e:a.main()
    self.assertEqual(e.exception.code,2)
 @unittest.skipUnless(all((SNAPS/n).is_file()for n in ['db.3.gbf','db.4.gbf']),'private snapshots absent')
 def test_both_snapshots_inverse_exact_reads_effects(self):
  reports=[]
  for name in ['db.3.gbf','db.4.gbf']:
   raw=(SNAPS/name).read_bytes();reads=[];rows=[];fn=a.range_evidence;decode=a.decode_selected
   class Proxy:
    def __init__(self,db):self.db=db
    def chain(self,*args):reads.append(args);return self.db.chain(*args)
   def capture(w,p):
    r=decode(w,p);rows.append((p,w,r));return r
   with patch.object(a,'range_evidence',side_effect=lambda db,*args:fn(Proxy(db),*args)),patch.object(a,'decode_selected',side_effect=capture):report=a.inspect(raw,hashlib.sha256(raw).hexdigest())
   self.assertEqual(reads,[(21,p-0x800055e0,n,2796416)for p,n,_ in a.RANGES]);self.assertEqual(len(rows),289)
   for pc,word,row in rows:
    self.assertEqual(encode(row,pc),word)
    for bit in range(32):
     changed=word^(1<<bit)
     try:other=decode(changed,pc)
     except a.c.FormatError:continue
     if other is not None:self.assertEqual(encode(other,pc),changed)
   at={p:r for p,_,r in rows}
   self.assertEqual(at[0x8025cd00]['target'],'8025ca6c')
   self.assertEqual([(at[p]['mnemonic'],at[p]['displacement'])for p in [0x8025cd14,0x8025cd20,0x8025cd24,0x8025cd28,0x8025cd30]],[('lwz',12),('lwz',0),('stw',12),('lwz',8),('stw',8)])
   self.assertEqual(at[0x8025cd2c]['immediate'],-1);self.assertEqual(at[0x8025cd34]['target'],'8025ce78')
   self.assertEqual(at[0x8025cba4]['displacement'],-19352);self.assertEqual(at[0x8025cca8]['displacement'],-19352)
   self.assertEqual(at[0x8025cbac]['mnemonic'],'lwzx');self.assertEqual(at[0x8025ccac]['mnemonic'],'lwzx')
   self.assertEqual([(at[p]['mnemonic'],at[p]['displacement'])for p in [0x8025cf14,0x8025cf1c,0x8025cf20,0x8025cf24,0x8025cf30]],[('lwz',32),('stw',32),('lwz',32),('lwz',36),('stw',36)])
   self.assertEqual(at[0x8025cf28]['mnemonic'],'cmpl')
   self.assertTrue(all('instructions'not in r for r in report['ranges']));self.assertEqual(report['selection_basis']['selected_data_cells'],0);self.assertEqual(report['selection_basis']['reads'],3)
   reports.append(report)
  self.assertEqual(reports[0]['ranges'],reports[1]['ranges'])
if __name__=='__main__':unittest.main()
