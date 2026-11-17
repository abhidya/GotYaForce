#!/usr/bin/env python3
"""Fixed actor-rate operands, constants, cells and fail-closed guards.

Only derived operand expectations and synthetic bytes are stored as fixtures.
"""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_actor_rate_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form


# Reviewed, explicit operand expectations. This string is not decoded at runtime.
EXPECTED = """
lbz rD=0 rA=3 displacement=1185
extsb rS=0 rA=0 Rc=1
bc BO=12 BI=2 LK=0 target=8005a398 AA=0
lfs fD=0 rA=2 displacement=-30296
stfs rA=3 displacement=7624 fS=0
stfs rA=3 displacement=1524 fS=0
stfs rA=3 displacement=1896 fS=0
blr
lbz rD=0 rA=3 displacement=1184
cmpi BF=0 L=0 rA=0 immediate=2
bc BO=4 BI=2 LK=0 target=8005a3c4 AA=0
lwz rD=4 rA=3 displacement=1188
lfs fD=0 rA=4 displacement=1896
stfs rA=3 displacement=1896 fS=0
lfs fD=0 rA=4 displacement=1524
stfs rA=3 displacement=1524 fS=0
lfs fD=0 rA=4 displacement=7624
stfs rA=3 displacement=7624 fS=0
blr
lha rD=4 rA=3 displacement=1808
cmpi BF=0 L=0 rA=4 immediate=0
bc BO=12 BI=2 LK=0 target=8005a3e8 AA=0
addi rD=4 rA=4 immediate=-1
extsh rS=4 rA=0 Rc=1
sth rA=3 displacement=1808 rS=4
bc BO=12 BI=1 LK=0 target=8005a3e8 AA=0
addi rD=0 rA=0 immediate=0
stb rS=0 rA=3 displacement=1806
lha rD=4 rA=3 displacement=1810
cmpi BF=0 L=0 rA=4 immediate=0
bc BO=12 BI=2 LK=0 target=8005a40c AA=0
addi rD=4 rA=4 immediate=-1
extsh rS=4 rA=0 Rc=1
sth rA=3 displacement=1810 rS=4
bc BO=12 BI=1 LK=0 target=8005a40c AA=0
addi rD=0 rA=0 immediate=0
stb rS=0 rA=3 displacement=1807
lfs fD=0 rA=2 displacement=-30296
stfs rA=3 displacement=1896 fS=0
lbz rD=0 rA=3 displacement=1788
extsb rS=0 rA=0 Rc=1
bc BO=12 BI=2 LK=0 target=8005a428 AA=0
lfs fD=0 rA=2 displacement=-30280
stfs rA=3 displacement=1896 fS=0
lbz rD=4 rA=3 displacement=1805
extsb rS=4 rA=0 Rc=1
bc BO=12 BI=2 LK=0 target=8005a458 AA=0
extsb rS=4 rA=0 Rc=0
addis rD=4 rA=0 immediate=-32722
addi rD=4 rA=4 immediate=-10864
lfs fD=1 rA=3 displacement=1896
rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
add rD=4 rA=4 rB=0 Rc=0
lfs fD=0 rA=4 displacement=-4
fmuls fD=0 fA=1 fC=0
stfs rA=3 displacement=1896 fS=0
lbz rD=4 rA=3 displacement=1807
extsb rS=4 rA=0 Rc=1
bc BO=12 BI=2 LK=0 target=8005a488 AA=0
extsb rS=4 rA=0 Rc=0
addis rD=4 rA=0 immediate=-32722
addi rD=4 rA=4 immediate=-10864
lfs fD=1 rA=3 displacement=1896
rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
add rD=4 rA=4 rB=0 Rc=0
lfs fD=0 rA=4 displacement=-4
fmuls fD=0 fA=1 fC=0
stfs rA=3 displacement=1896 fS=0
lwz rD=0 rA=3 displacement=1504
rlwinm rS=0 rA=0 SH=0 MB=7 ME=7 Rc=1
bc BO=4 BI=2 LK=0 target=8005a50c AA=0
lbz rD=0 rA=3 displacement=1788
extsb rS=0 rA=0 Rc=1
bc BO=4 BI=2 LK=0 target=8005a50c AA=0
lbz rD=0 rA=3 displacement=1184
extsb rS=0 rA=0 Rc=1
bc BO=4 BI=2 LK=0 target=8005a50c AA=0
lbz rD=4 rA=3 displacement=1804
extsb rS=4 rA=0 Rc=1
bc BO=12 BI=2 LK=0 target=8005a4dc AA=0
extsb rS=4 rA=0 Rc=0
addis rD=4 rA=0 immediate=-32722
addi rD=4 rA=4 immediate=-10880
lfs fD=1 rA=3 displacement=1896
rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
add rD=4 rA=4 rB=0 Rc=0
lfs fD=0 rA=4 displacement=-4
fmuls fD=0 fA=1 fC=0
stfs rA=3 displacement=1896 fS=0
lbz rD=4 rA=3 displacement=1806
extsb rS=4 rA=0 Rc=1
bc BO=12 BI=2 LK=0 target=8005a50c AA=0
extsb rS=4 rA=0 Rc=0
addis rD=4 rA=0 immediate=-32722
addi rD=4 rA=4 immediate=-10880
lfs fD=1 rA=3 displacement=1896
rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
add rD=4 rA=4 rB=0 Rc=0
lfs fD=0 rA=4 displacement=-4
fmuls fD=0 fA=1 fC=0
stfs rA=3 displacement=1896 fS=0
lbz rD=4 rA=3 displacement=1820
cmpli BF=0 L=0 rA=4 immediate=0
bc BO=12 BI=2 LK=0 target=8005a55c AA=0
addi rD=4 rA=4 immediate=-1
rlwinm rS=4 rA=0 SH=0 MB=24 ME=31 Rc=1
stb rS=4 rA=3 displacement=1820
bc BO=12 BI=2 LK=0 target=8005a538 AA=0
lfs fD=0 rA=2 displacement=-30276
stfs rA=3 displacement=1524 fS=0
stfs rA=3 displacement=7624 fS=0
blr
lfs fD=0 rA=3 displacement=1896
stfs rA=3 displacement=1524 fS=0
lfs fD=1 rA=3 displacement=7628
lfs fD=0 rA=3 displacement=1896
lfs fD=2 rA=3 displacement=7632
fmuls fD=0 fA=1 fC=0
fmuls fD=0 fA=2 fC=0
stfs rA=3 displacement=7624 fS=0
blr
lfs fD=0 rA=3 displacement=1896
stfs rA=3 displacement=1524 fS=0
lfs fD=1 rA=3 displacement=7628
lfs fD=0 rA=3 displacement=1896
lfs fD=2 rA=3 displacement=7632
fmuls fD=0 fA=1 fC=0
fmuls fD=0 fA=2 fC=0
stfs rA=3 displacement=7624 fS=0
blr
"""


def expected_facts():
    facts = []
    for index, line in enumerate(EXPECTED.strip().splitlines()):
        mnemonic, *fields = line.split()
        operands = dict(item.split('=') for item in fields)
        operands = {key: value if key == 'target' else int(value)
                    for key, value in operands.items()}
        facts.append(dict(address=f'{0x8005a378 + index * 4:08x}', mnemonic=mnemonic, **operands))
    return facts


class SyntheticTests(unittest.TestCase):
    def test_exact_selection_and_unchanged_shared_scope(self):
        self.assertEqual([(pc,n) for pc,n,_ in a.RANGES],[(0x8005a378,0x208)])
        self.assertEqual(a.TARGETS,((0x804373c8,4,'3f800000'),
                                   (0x804373d8,4,'3fc00000'),
                                   (0x804373dc,4,'3cf5c28f')))
        self.assertEqual(a.TABLE_CELLS,((0x802dd57c,1,0x802dd580,'3f333333'),
                                      (0x802dd57c,2,0x802dd584,'3ecccccd'),
                                      (0x802dd58c,1,0x802dd590,'3fa00000'),
                                      (0x802dd58c,2,0x802dd594,'3fc00000')))
        self.assertEqual(len(a.c.TARGETS),12)
        for address,_,_ in a.TARGETS:
            self.assertNotIn(address,a.c.EXPECTED_TARGETS)
        self.assertEqual(len(expected_facts()),130)

    def test_decoder_bounds_and_unselected_forms(self):
        for word in (-1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)
        for pc in (-1,1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0,pc)
        for word in (0,0x4e800421,d_form(36,3,4,0),d_form(50,0,2,0),
                     (18<<26), (59<<26)|(21<<1), (31<<26)|(87<<1)):
            self.assertIsNone(a.decode_selected(word,0))

    def test_reserved_fields_rejected(self):
        words = ((31<<26)|(954<<1)|(1<<11), (31<<26)|(922<<1)|(1<<11),
                 (11<<26)|(1<<21), (10<<26)|(2<<21),
                 (59<<26)|(25<<1)|(1<<11), (59<<26)|(25<<1)|1)
        for word in words:
            with self.subTest(word=word):
                with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)

    def test_synthetic_signedness_and_operand_direction(self):
        for op,name,source in ((42,'lha','rD'),(44,'sth','rS'),(34,'lbz','rD'),
                               (38,'stb','rS'),(48,'lfs','fD'),(52,'stfs','fS')):
            self.assertEqual(a.decode_selected(d_form(op,7,9,-2),0),
                             dict(mnemonic=name,rA=9,displacement=-2,**{source:7}))
        for xo,name in ((922,'extsh'),(954,'extsb')):
            self.assertEqual(a.decode_selected((31<<26)|(7<<21)|(9<<16)|(xo<<1)|1,0),
                             dict(mnemonic=name,rS=7,rA=9,Rc=1))
        self.assertEqual(a.decode_selected((59<<26)|(7<<21)|(9<<16)|(11<<6)|(25<<1),0),
                         dict(mnemonic='fmuls',fD=7,fA=9,fC=11))
        self.assertEqual(a.decode_selected((16<<26)|(12<<21)|(2<<16)|0xfffc,0x1000),
                         dict(mnemonic='bc',BO=12,BI=2,LK=0,target='00000ffc',AA=0))
        for op,name,value in ((10,'cmpli',65535),(11,'cmpi',-1)):
            self.assertEqual(a.decode_selected(d_form(op,8,7,0xffff),0),
                             dict(mnemonic=name,BF=2,L=0,rA=7,immediate=value))

    def test_fixed_reads_reject_before_decode(self):
        pc,size,_ = a.RANGES[0]
        for address,width in ((pc+4,size-4),(pc,size-4),(pc,size+4)):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.range_evidence(None,21,address,width)
        for fields in ((21.0,pc,size),(21,True,size),(21,pc,float(size))):
            with self.assertRaisesRegex(a.c.FormatError,'integer fields'): a.range_evidence(None,*fields)
        with self.assertRaisesRegex(a.c.FormatError,'root/alignment/bounds'):
            a.range_evidence(None,22,pc,size)
        for raw,reason in ((bytes(size),'digest'),(bytes(size-4),'byte width')):
            with patch.object(a,'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError,reason): a.range_evidence(FakeDB(raw),21,pc,size)
                decoder.assert_not_called()
        raw=bytes(4)
        with patch.object(a,'RANGES',((pc,4,hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError,'unselected instruction'):
                a.range_evidence(FakeDB(raw),21,pc,4)
        with patch.object(a,'RANGES',a.RANGES*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'): a.range_evidence(None,21,pc,size)
        for pc,size in ((a.TEXT_START+1,4),(a.TEXT_START,3),(a.TEXT_START-4,4),
                        (a.TEXT_START+a.TEXT_LENGTH,4),(a.TEXT_START,0)):
            with patch.object(a,'RANGES',((pc,size,'unused'),)):
                with self.assertRaisesRegex(a.c.FormatError,'root/alignment/bounds'):
                    a.range_evidence(None,21,pc,size)

    def test_constant_scope_bits_and_mapping_guards(self):
        mapping=a.DATA5_MAPPING
        for fields in ((0x804373c8,8),(0x804373cc,4),(True,4),(0x804373c8,4.0)):
            with self.assertRaises(a.c.FormatError): a.constant_evidence(None,mapping,*fields)
        with patch.object(a,'TARGETS',a.TARGETS*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.constant_evidence(None,mapping,0x804373c8,4)
        with self.assertRaisesRegex(a.c.FormatError,'mapping mismatch'):
            a.constant_evidence(None,mapping[:-1]+(264,),0x804373c8,4)
        for raw,reason in ((bytes(4),'bits mismatch'),(bytes(3),'byte width')):
            with self.assertRaisesRegex(a.c.FormatError,reason):
                a.constant_evidence(FakeDB(raw),mapping,0x804373c8,4)
        for address,width in ((0x804373c9,4),(0x804373c8,3),(mapping[0]-4,4),(mapping[1],4)):
            with patch.object(a,'TARGETS',((address,width,'unused'),)):
                with self.assertRaisesRegex(a.c.FormatError,'alignment/width/bounds'):
                    a.constant_evidence(None,mapping,address,width)

    def test_table_scope_refuses_every_other_signed_index(self):
        for base in (0x802dd57c,0x802dd58c):
            for index in range(-128,128):
                if index not in (1,2):
                    with self.subTest(base=base,index=index):
                        with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                            a.table_cell_evidence(None,a.DATA3_MAPPING,base,index)
        # A different base/index pair may hit a selected address: still refuse.
        with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
            a.table_cell_evidence(None,a.DATA3_MAPPING,0x802dd57c,5)
        for base,index in ((0x802dd580,1),(0x802dd57c,128),(0x802dd57c,True),(0x802dd57c,1.0)):
            with self.assertRaises(a.c.FormatError): a.table_cell_evidence(None,a.DATA3_MAPPING,base,index)
        with patch.object(a,'TABLE_CELLS',a.TABLE_CELLS*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.table_cell_evidence(None,a.DATA3_MAPPING,0x802dd57c,1)

    def test_table_mapping_width_bits_and_address_guards(self):
        with self.assertRaisesRegex(a.c.FormatError,'mapping mismatch'):
            a.table_cell_evidence(None,a.DATA3_MAPPING[:-1]+(200,),0x802dd57c,1)
        for raw,reason in ((bytes(4),'bits mismatch'),(bytes(3),'byte width')):
            with self.assertRaisesRegex(a.c.FormatError,reason):
                a.table_cell_evidence(FakeDB(raw),a.DATA3_MAPPING,0x802dd57c,1)
        for base,index,address in ((0x802dd57c,1,0x802dd584),(0x802dd57d,1,0x802dd581),
                                   (a.DATA3_MAPPING[1]-4,1,a.DATA3_MAPPING[1]),
                                   (0x802dd57c,0,0x802dd57c),
                                   (a.DATA3_MAPPING[0]-8,1,a.DATA3_MAPPING[0]-4)):
            with patch.object(a,'TABLE_CELLS',((base,index,address,'unused'),)):
                with self.assertRaisesRegex(a.c.FormatError,'alignment/index/bounds'):
                    a.table_cell_evidence(None,a.DATA3_MAPPING,base,index)

    def test_authentication_precedes_parsing_and_all_fixed_reads(self):
        for digest in ('0'*64,hashlib.sha256(bytes(32)).hexdigest(),next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c,'GBF') as parser,patch.object(a,'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'): a.inspect(bytes(32),digest)
                parser.assert_not_called(); reader.assert_not_called()
        for reason in ('unsupported schema','language mismatch','File Bytes table is not empty','data5 digest mismatch'):
            with patch.object(a.c,'inspect',side_effect=a.c.FormatError(reason)),patch.object(a.c,'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError,reason): a.inspect(b'synthetic','synthetic')
                parser.assert_not_called()

    def test_no_arbitrary_cli(self):
        for option in (['--address','8005a378'],['--width','520'],['--raw'],['--execute'],['--index','1'],['--pointer','0']):
            with patch.object(a.sys,'argv',['reader','fixture.gbf']+option),contextlib.redirect_stderr(io.StringIO()),patch.object(a,'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code,2); inspect.assert_not_called()

    def test_mapping_guards_precede_all_fixed_reads(self):
        auth={'image_offset':'80000000'}
        blocks={key:[name,None,None,0,encoded,length,0]
                for name,key,encoded,length,root in a.command.MAPPINGS}
        subs={key:[key,2,length,0,root,0]
              for name,key,encoded,length,root in a.command.MAPPINGS}
        for target in ('root','offset','type','duplicate','overlap','image','data3','data5'):
            aa,bb,ss=copy.deepcopy((auth,blocks,subs))
            if target=='root': ss[1][4]+=1
            if target=='offset': ss[1][5]+=1
            if target=='type': ss[1][1]+=1
            if target=='duplicate': bb[99]=copy.deepcopy(bb[1])
            if target=='overlap': bb[99]=['other',None,None,0,0x20000000000055e4,4,0]
            if target=='image': aa['image_offset']='80000004'
            if target=='data3': ss[5][4]+=1
            if target=='data5': ss[7][4]+=1
            with patch.object(a.c,'inspect',return_value=aa),patch.object(a.c,'GBF') as parser, \
                    patch.object(a,'range_evidence') as ranges, \
                    patch.object(a,'constant_evidence') as constants, \
                    patch.object(a,'table_cell_evidence') as cells:
                db=parser.return_value
                db.tables.return_value={'Memory Blocks':'blocks','Sub Memory Blocks':'subs'}
                db.rows.side_effect=lambda name:{'blocks':bb,'subs':ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic','synthetic')
                ranges.assert_not_called(); constants.assert_not_called(); cells.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base=Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR',str(default)))
        paths=[base/f'db.{n}.gbf' for n in (3,4)]
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('both existing local archived snapshots required')
        cls.results=[]
        cls.dbs=[]
        for path in paths:
            a.c.require(32<=path.stat().st_size<=a.c.MAX_FILE,'snapshot size bounds')
            with path.open('rb') as stream: data=stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data)<=a.c.MAX_FILE,'snapshot size bounds')
            cls.results.append(a.inspect(data,hashlib.sha256(data).hexdigest()))
            cls.dbs.append(a.c.GBF(data))
        cls.facts={int(f['address'],16):f for f in cls.results[0]['ranges'][0]['instructions']}

    def test_full_coverage_both_archives(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results},set(a.c.SNAPSHOTS))
        for key in ('ranges','constants','table_cells','table_mapping','function_coverage','table_scope'):
            self.assertEqual(self.results[0][key],self.results[1][key])
        self.assertEqual(len(self.facts),130)
        for result in self.results:
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            coverage=result['function_coverage'][0]
            self.assertEqual(coverage['represented_instructions'],130)
            self.assertEqual(coverage['unrepresented_instructions'],0)
            self.assertEqual(coverage['unrepresented_ranges'],[])
            self.assertEqual(result['table_scope'],dict(authenticated_indices=[1,2],zero_skips_read=True,
                                                       unsupported_signed_indices=[[-128,-1],[3,127]],extent_proven=False))
            for span in result['ranges']:
                for item in [span]+span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw','word','words','hex','bytes')))

    def test_every_operand_in_exact_order(self):
        for result in self.results:
            self.assertEqual(result['ranges'][0]['instructions'],expected_facts())

    def test_boundaries_c_next_entry_and_final_return(self):
        research=Path(__file__).resolve().parents[2]
        mapping=(research/'symbols/GG4E-CSM-20220412.map').read_text()
        source=(research/'decomp/ghidra-export/chunk_0007.c').read_text()
        start=source.index('// ==== 8005a378 ')
        next_entry=source.index('// ==== ',start+8)
        self.assertTrue(source[next_entry:].startswith('// ==== 8005a580 '))
        self.assertEqual(self.facts[0x8005a57c]['mnemonic'],'blr')
        for entry in (0x8005a378,0x8005a580):
            self.assertFalse(any(line.startswith(f'{entry:08x} ') for line in mapping.splitlines()))

    def test_constants_table_values_and_source_addresses(self):
        result=self.results[0]
        self.assertEqual([x['bits'] for x in result['constants']],['3f800000','3fc00000','3cf5c28f'])
        self.assertEqual([x['value'] for x in result['constants']],[1.0,1.5,0.029999999329447746])
        self.assertEqual([x['bits'] for x in result['table_cells']],['3f333333','3ecccccd','3fa00000','3fc00000'])
        self.assertEqual([x['value'] for x in result['table_cells']],[0.699999988079071,0.4000000059604645,1.25,1.5])
        for pc,address in ((0x8005a384,0x804373c8),(0x8005a40c,0x804373c8),
                           (0x8005a420,0x804373d8),(0x8005a528,0x804373dc)):
            self.assertEqual(self.facts[pc]['rA'],2)
            self.assertEqual(self.facts[pc]['displacement']+0x8043ea20,address)
        for pc,base in ((0x8005a438,0x802dd58c),(0x8005a468,0x802dd58c),
                        (0x8005a4bc,0x802dd57c),(0x8005a4ec,0x802dd57c)):
            formed=((self.facts[pc]['immediate']<<16)+self.facts[pc+4]['immediate'])&0xffffffff
            self.assertEqual(formed-4,base)
            self.assertEqual(self.facts[pc+20]['displacement'],-4)

    def test_lazy_order_rounding_timers_and_pointer_boundary(self):
        f=self.facts
        self.assertFalse(any(x['mnemonic'] in ('bl','stwu','mflr','mtlr') for x in f.values()))
        self.assertEqual([f[pc]['displacement'] for pc in (0x8005a388,0x8005a38c,0x8005a390)],
                         [0x1dc8,0x5f4,0x768])
        self.assertEqual(f[0x8005a3a4]['displacement'],0x4a4)
        self.assertEqual([(f[pc]['mnemonic'],f[pc]['rA'],f[pc]['displacement'])
                          for pc in range(0x8005a3a8,0x8005a3c0,4)],
                         [('lfs',4,0x768),('stfs',3,0x768),('lfs',4,0x5f4),
                          ('stfs',3,0x5f4),('lfs',4,0x1dc8),('stfs',3,0x1dc8)])
        for pc in (0x8005a3d4,0x8005a3f8):
            self.assertEqual(f[pc]['mnemonic'],'extsh'); self.assertEqual(f[pc]['Rc'],1)
            self.assertEqual(f[pc+4]['mnemonic'],'sth')
            self.assertEqual((f[pc+8]['BO'],f[pc+8]['BI']),(12,1))
        self.assertEqual([f[pc]['displacement'] for pc in (0x8005a488,0x8005a494,0x8005a4a0)],
                         [0x5e0,0x6fc,0x4a0])
        self.assertEqual((f[0x8005a48c]['MB'],f[0x8005a48c]['ME']),(7,7))
        self.assertEqual(f[0x8005a510]['mnemonic'],'cmpli')
        self.assertEqual(f[0x8005a520]['mnemonic'],'stb')
        self.assertEqual(f[0x8005a524]['target'],'8005a538')
        for start in (0x8005a538,0x8005a55c):
            self.assertEqual([f[start+n]['displacement'] for n in (0,4,8,12,16)],
                             [0x768,0x5f4,0x1dcc,0x768,0x1dd0])
            self.assertEqual(f[start+20],dict(address=f'{start+20:08x}',mnemonic='fmuls',fD=0,fA=1,fC=0))
            self.assertEqual(f[start+24],dict(address=f'{start+24:08x}',mnemonic='fmuls',fD=0,fA=2,fC=0))

    def test_each_instruction_mutation_rejected_before_decode(self):
        for db in self.dbs:
            pc,width,_=a.RANGES[0]
            raw=db.chain(21,pc-a.TEXT_START,width,a.TEXT_LENGTH)[0]
            for offset in range(0,width,4):
                changed=bytearray(raw); changed[offset+3]^=1
                with patch.object(a,'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'):
                        a.range_evidence(FakeDB(changed),21,pc,width)
                    decoder.assert_not_called()

    def test_each_fixed_data_byte_mutation_rejected(self):
        for db in self.dbs:
            for address,width,_ in a.TARGETS:
                raw=db.chain(263,address-a.DATA5_MAPPING[0],width,a.DATA5_MAPPING[-2])[0]
                for offset in range(width):
                    changed=bytearray(raw);changed[offset]^=1
                    with self.assertRaisesRegex(a.c.FormatError,'bits mismatch'):
                        a.constant_evidence(FakeDB(changed),a.DATA5_MAPPING,address,width)
            for base,index,address,_ in a.TABLE_CELLS:
                raw=db.chain(199,address-a.DATA3_MAPPING[0],4,a.DATA3_MAPPING[-2])[0]
                for offset in range(4):
                    changed=bytearray(raw);changed[offset]^=1
                    with self.assertRaisesRegex(a.c.FormatError,'bits mismatch'):
                        a.table_cell_evidence(FakeDB(changed),a.DATA3_MAPPING,base,index)


if __name__=='__main__': unittest.main()
