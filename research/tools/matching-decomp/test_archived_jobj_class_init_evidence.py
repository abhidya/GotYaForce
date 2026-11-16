"""Synthetic bounds/inverse controls; local snapshots optional, no original listing embedded."""
import hashlib,json,re,unittest,sys,io,contextlib
from pathlib import Path
from unittest.mock import patch
import read_archived_jobj_class_init_evidence as a
from test_archived_projectile_resource_evidence import encode as prior_encode,FakeDB,invented_operands
ROOT=Path(__file__).resolve().parents[3]
SNAPS=ROOT/'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
def encode(r,pc):
 if r['mnemonic'] in ('oris','andi.'):
  return (25 if r['mnemonic']=='oris' else 28)<<26|r['rS']<<21|r['rA']<<16|r['immediate']
 if r['mnemonic']=='cntlzw':return 31<<26|r['rS']<<21|r['rA']<<16|26<<1|r['Rc']
 return prior_encode(r,pc)
class Tests(unittest.TestCase):
 def test_fixed_scope_and_independent_bounds(self):
  self.assertEqual([(hex(p),n)for p,n,_ in a.RANGES],[('0x8025acb8',68),('0x8025cfec',156),('0x8025cf48',8)])
  self.assertEqual(sum(n for _,n,_ in a.RANGES),232);self.assertEqual(sum(n for _,n,_ in a.CELLS),20)
  index=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text().splitlines();symbols=(ROOT/'research/symbols/GG4E-CSM-20220412.map').read_text()
  for pc,n,_ in a.RANGES:
   i=next(i for i,s in enumerate(index)if s.startswith(f'{pc:08x}\t'));self.assertTrue(index[i+1].startswith(f'{pc+n:08x}\t'))
   src=(ROOT/'research/decomp/ghidra-export'/index[i].split('\t')[2]).read_text();self.assertTrue(src.split(f'// ==== {pc:08x} ',1)[1].split('// ==== ',1)[1].startswith(f'{pc+n:08x} '));self.assertRegex(symbols,rf'(?m)^{pc:08x} {n:08x} {pc:08x} 0 ')
 def test_composed_forms_inverse(self):
  rows=invented_operands()+[dict(mnemonic='oris',rS=7,rA=9,immediate=321),dict(mnemonic='andi.',rS=13,rA=29,immediate=456),dict(mnemonic='cntlzw',rS=8,rA=11,Rc=0),dict(mnemonic='cntlzw',rS=17,rA=2,Rc=1)]
  for r in rows:
   w=encode(r,0x10000000);self.assertEqual(a.decode_selected(w,0x10000000),r)
   for bit in range(32):
    try:d=a.decode_selected(w^(1<<bit),0x10000000)
    except a.c.FormatError:continue
    if d is not None:self.assertEqual(encode(d,0x10000000),w^(1<<bit))
 def test_reserved_cntlzw_and_types(self):
  with self.assertRaises(a.c.FormatError):a.decode_selected(31<<26|1<<11|26<<1,0)
  for w,pc in [(True,0),(-1,0),(1<<32,0),(0,1),(0,True)]:
   with self.assertRaises(a.c.FormatError):a.decode_selected(w,pc)
 def test_unlisted_before_io(self):
  for pc,n,_ in a.RANGES:
   for pp,nn in [(pc+4,n),(pc,n+4),(float(pc),n),(pc,True)]:
    db=FakeDB()
    with self.assertRaises(a.c.FormatError):a.range_evidence(db,a.TEXT_MAPPING,pp,nn)
    self.assertFalse(db.calls)
  db=FakeDB()
  with self.assertRaises(a.c.FormatError):a.cell_evidence(db,a.normal.DATA3_MAPPING,0x803acc14,4)
  self.assertFalse(db.calls)
 def test_cell_bounds_mappings_and_cli_flags(self):
  for pc,width,_ in a.CELLS:
   mapping=a.normal.DATA3_MAPPING if pc<0x80400000 else a.ceiling.DATA5_MAPPING
   for address,n in [(pc+1,width),(pc,width+1),(float(pc),width),(pc,True)]:
    db=FakeDB()
    with self.assertRaises(a.c.FormatError):a.cell_evidence(db,mapping,address,n)
    self.assertFalse(db.calls)
   for index,value in enumerate(mapping):
    wrong=list(mapping);wrong[index]=value+1 if type(value)is int else 'wrong';db=FakeDB()
    with self.assertRaises(a.c.FormatError):a.cell_evidence(db,tuple(wrong),pc,width)
    self.assertFalse(db.calls)
  for index,value in enumerate(a.TEXT_MAPPING):
   wrong=list(a.TEXT_MAPPING);wrong[index]=value+1 if type(value)is int else 'wrong';db=FakeDB()
   with self.assertRaises(a.c.FormatError):a.range_evidence(db,tuple(wrong),*a.RANGES[0][:2])
   self.assertFalse(db.calls)
  for flag in ['--address','--width','--raw','--instructions','--follow']:
   with patch.object(sys,'argv',['reader',flag,'1']),contextlib.redirect_stderr(io.StringIO()):
    with self.assertRaises(SystemExit)as caught:a.main()
    self.assertEqual(caught.exception.code,2)
 def test_digest_before_decode(self):
  with patch.object(a,'decode_selected')as decode:
   for pc,n,_ in a.RANGES:
    with self.assertRaises(a.c.FormatError):a.range_evidence(FakeDB(bytes(n)),a.TEXT_MAPPING,pc,n)
   decode.assert_not_called()
 def test_auth_before_selection(self):
  with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')),patch.object(a.c,'GBF')as db:
   with self.assertRaises(a.c.FormatError):a.inspect(b'bad','bad')
   db.assert_not_called()
 @unittest.skipUnless((SNAPS/'db.3.gbf').is_file(),'private snapshot unavailable')
 def test_exact_reads_captured_inverse_and_init_effects(self):
  raw=(SNAPS/'db.3.gbf').read_bytes();reads=[];decoded=[]
  decode=a.decode_selected;range_fn=a.range_evidence;cell_fn=a.cell_evidence
  class Proxy:
   def __init__(self,db):self.db=db
   def chain(self,*args):reads.append(args);return self.db.chain(*args)
  def captured(word,pc):
   row=decode(word,pc);decoded.append((pc,word,row));return row
  with patch.object(a,'range_evidence',side_effect=lambda db,*args:range_fn(Proxy(db),*args)),patch.object(a,'cell_evidence',side_effect=lambda db,*args:cell_fn(Proxy(db),*args)),patch.object(a,'decode_selected',side_effect=captured):
   a.inspect(raw,hashlib.sha256(raw).hexdigest())
  expected=[(199,pc-0x802bae60,width,1000128)for pc,width,_ in a.CELLS]
  expected += [(21,pc-0x800055e0,width,2796416)for pc,width,_ in a.RANGES]
  self.assertEqual(reads,expected);self.assertEqual(len(decoded),58)
  for pc,word,row in decoded:
   self.assertEqual(encode(row,pc),word)
   for bit in range(32):
    changed=word^(1<<bit)
    try:other=decode(changed,pc)
    except a.c.FormatError:continue
    if other is not None:self.assertEqual(encode(other,pc),changed)
  at={pc:r for pc,_,r in decoded}
  self.assertEqual(at[0x8025ace8]['target'],'8025c984')
  self.assertEqual([at[p]['immediate'] for p in [0x8025acd4,0x8025acd8,0x8025ace0,0x8025ace4]],[-10936,-10576,60,8])
  self.assertEqual([(at[p]['displacement'],at[p]['rS'])for p in [0x8025d068,0x8025d06c]],[(40,7),(44,6)])
  self.assertEqual(at[0x8025d024]['immediate'],-12560)
  self.assertEqual(at[0x8025d028]['immediate'],-12472)
  self.assertEqual(at[0x8025cf48],dict(mnemonic='addi',rD=3,rA=0,immediate=0))
  self.assertEqual(at[0x8025cf4c]['mnemonic'],'blr')
 @unittest.skipUnless(all((SNAPS/n).is_file()for n in ['db.3.gbf','db.4.gbf']),'private snapshots unavailable')
 def test_both_authenticated_snapshots(self):
  reports=[]
  for name in ['db.3.gbf','db.4.gbf']:
   raw=(SNAPS/name).read_bytes();r=a.inspect(raw,hashlib.sha256(raw).hexdigest());reports.append(r)
   self.assertEqual(sum(x['represented_instructions']for x in r['ranges']),58)
   self.assertEqual([x['value']for x in r['cells']],[0x802524e8,0x8025acb8,0,0x8025cfec,0])
   self.assertTrue(all(set(x)=={'address','end_exclusive','width','sha256','spans','represented_instructions','unrepresented_instructions','operand_sha256','control_flow_count','control_flow_sha256','calls','indirect_call_sites'} for x in r['ranges']))
   self.assertTrue(all(set(x)=={'address','width','sha256','value','spans'}for x in r['cells']))
  for key in ['ranges','cells']:self.assertEqual(reports[0][key],reports[1][key])
if __name__=='__main__':unittest.main()
