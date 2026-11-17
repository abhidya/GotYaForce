#!/usr/bin/env python3
"""Fixed actor-ceiling operands, positive zero and fail-closed guards.

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

import read_archived_actor_ceiling_evidence as a
import read_archived_tick_prefix_evidence as tick
from test_archived_actor_attribute_evidence import FakeDB, d_form


# Reviewed, explicit operand expectations. Not decoded from words at runtime.
EXPECTED = {
    0x80068030: """
stwu rA=1 displacement=-16 rS=1
mflr rD=0
stw rA=1 displacement=20 rS=0
stw rA=1 displacement=12 rS=31
or rS=3 rA=31 rB=3 Rc=0
bl target=8008b290 AA=0
cmpi BF=0 L=0 rA=3 immediate=0
bc BO=4 BI=2 LK=0 target=800680bc AA=0
lbz rD=0 rA=31 displacement=475
extsb rS=0 rA=0 Rc=1
bc BO=4 BI=2 LK=0 target=800680bc AA=0
lfs fD=1 rA=31 displacement=36
lfs fD=0 rA=31 displacement=1640
lwz rD=3 rA=13 displacement=-21316
fadds fD=1 fA=1 fB=0
lfs fD=0 rA=3 displacement=52
fcmpo crD=0 fA=1 fB=0
bc BO=4 BI=1 LK=0 target=800680bc AA=0
lfs fD=1 rA=31 displacement=72
lfs fD=0 rA=2 displacement=-29776
fcmpo crD=0 fA=1 fB=0
bc BO=4 BI=1 LK=0 target=800680bc AA=0
stfs rA=31 displacement=72 fS=0
lwz rD=3 rA=13 displacement=-21316
lfs fD=0 rA=31 displacement=1640
lfs fD=1 rA=3 displacement=52
lfs fD=2 rA=31 displacement=48
fsubs fD=0 fA=1 fB=0
fcmpo crD=0 fA=2 fB=0
bc BO=4 BI=1 LK=0 target=800680b0 AA=0
stfs rA=31 displacement=36 fS=2
b target=800680b4 AA=0
stfs rA=31 displacement=36 fS=0
addi rD=3 rA=0 immediate=1
b target=800680c0 AA=0
addi rD=3 rA=0 immediate=0
lwz rD=0 rA=1 displacement=20
lwz rD=31 rA=1 displacement=12
mtlr rS=0
addi rD=1 rA=1 immediate=16
blr
""",
    0x8008b290: """
lwz rD=3 rA=13 displacement=-31852
lbz rD=3 rA=3 displacement=217
blr
""",
}


def expected_facts(entry):
    facts = []
    for index, line in enumerate(EXPECTED[entry].strip().splitlines()):
        mnemonic, *fields = line.split()
        operands = dict(item.split('=') for item in fields)
        operands = {key: value if key == 'target' else int(value)
                    for key, value in operands.items()}
        facts.append(dict(address=f'{entry + index * 4:08x}', mnemonic=mnemonic, **operands))
    return facts


class SyntheticTests(unittest.TestCase):
    def test_exact_selection_and_unchanged_shared_scope(self):
        self.assertEqual([(pc,n) for pc,n,_ in a.RANGES],[(0x80068030,0xa4),(0x8008b290,0xc)])
        self.assertEqual(a.TARGETS,((0x804375d0,4,'00000000'),))
        self.assertEqual(len(a.c.TARGETS),12)
        self.assertNotIn(0x804375d0,a.c.EXPECTED_TARGETS)
        self.assertEqual([len(expected_facts(pc)) for pc,_,_ in a.RANGES],[41,3])
        # Neither global identity nor a runtime pointee belongs to this selection.
        for address in (0x80433934,0x8043625c,0x804375d4):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.constant_evidence(None,a.DATA5_MAPPING,address,4)

    def test_decoder_bounds_and_unselected_forms(self):
        for word in (-1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)
        for pc in (-1,1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0,pc)
        for word in (0,0x4e800421,d_form(38,3,4,0),d_form(50,0,2,0),
                     d_form(10,0,3,0),(59<<26)|(25<<1),(31<<26)|(922<<1),
                     (19<<26)|(449<<1),(63<<26)|(15<<1)):
            self.assertIsNone(a.decode_selected(word,0))

    def test_reserved_fields_rejected(self):
        words = ((31<<26)|(954<<1)|(1<<11), (11<<26)|(1<<21),
                 (59<<26)|(20<<1)|(1<<6), (59<<26)|(21<<1)|1,
                 (63<<26)|(32<<1)|(1<<21), (63<<26)|(32<<1)|1,
                 (31<<26)|(8<<16)|(339<<1)|1,
                 (31<<26)|(1<<21)|(8<<16)|(339<<1),
                 (31<<26)|(9<<16)|(467<<1))
        for word in words:
            with self.subTest(word=word):
                with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)

    def test_synthetic_operand_direction_and_float_forms(self):
        for op,name,source in ((32,'lwz','rD'),(34,'lbz','rD'),(36,'stw','rS'),
                               (37,'stwu','rS'),(48,'lfs','fD'),(52,'stfs','fS')):
            self.assertEqual(a.decode_selected(d_form(op,7,9,-2),0),
                             dict(mnemonic=name,rA=9,displacement=-2,**{source:7}))
        self.assertEqual(a.decode_selected((31<<26)|(7<<21)|(9<<16)|(954<<1)|1,0),
                         dict(mnemonic='extsb',rS=7,rA=9,Rc=1))
        for xo,name in ((20,'fsubs'),(21,'fadds')):
            self.assertEqual(a.decode_selected((59<<26)|(7<<21)|(9<<16)|(11<<11)|(xo<<1),0),
                             dict(mnemonic=name,fD=7,fA=9,fB=11))
        self.assertEqual(a.decode_selected((63<<26)|(8<<21)|(9<<16)|(11<<11)|(32<<1),0),
                         dict(mnemonic='fcmpo',crD=2,fA=9,fB=11))
        self.assertEqual(a.decode_selected((16<<26)|(4<<21)|(1<<16)|0xfffc,0x1000),
                         dict(mnemonic='bc',BO=4,BI=1,LK=0,target='00000ffc',AA=0))

    def test_fixed_reads_reject_before_decode(self):
        for pc,size,_ in a.RANGES:
            for address,width in ((pc+4,size-4),(pc,size-4),(pc,size+4)):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                    a.range_evidence(None,21,address,width)
            for fields in ((21.0,pc,size),(21,True,size),(21,pc,float(size))):
                with self.assertRaisesRegex(a.c.FormatError,'integer fields'):
                    a.range_evidence(None,*fields)
            with self.assertRaisesRegex(a.c.FormatError,'root/alignment/bounds'):
                a.range_evidence(None,22,pc,size)
            for raw,reason in ((bytes(size),'digest'),(bytes(size-4),'byte width')):
                with patch.object(a,'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError,reason):
                        a.range_evidence(FakeDB(raw),21,pc,size)
                    decoder.assert_not_called()
        pc,size,_=a.RANGES[0]
        with patch.object(a,'RANGES',a.RANGES*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.range_evidence(None,21,pc,size)
        raw=bytes(4)
        with patch.object(a,'RANGES',((pc,4,hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError,'unselected instruction'):
                a.range_evidence(FakeDB(raw),21,pc,4)
        for pc,size in ((a.TEXT_START+1,4),(a.TEXT_START,3),(a.TEXT_START-4,4),
                        (a.TEXT_START+a.TEXT_LENGTH,4),(a.TEXT_START,0)):
            with patch.object(a,'RANGES',((pc,size,'unused'),)):
                with self.assertRaisesRegex(a.c.FormatError,'root/alignment/bounds'):
                    a.range_evidence(None,21,pc,size)

    def test_constant_scope_bits_and_mapping_guards(self):
        mapping=a.DATA5_MAPPING
        for fields in ((0x804375d0,8),(0x804375d4,4),(True,4),(0x804375d0,4.0)):
            with self.assertRaises(a.c.FormatError): a.constant_evidence(None,mapping,*fields)
        with patch.object(a,'TARGETS',a.TARGETS*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.constant_evidence(None,mapping,0x804375d0,4)
        with self.assertRaisesRegex(a.c.FormatError,'mapping mismatch'):
            a.constant_evidence(None,mapping[:-1]+(264,),0x804375d0,4)
        for raw,reason in ((bytes.fromhex('80000000'),'bits mismatch'),(bytes(3),'byte width')):
            with self.assertRaisesRegex(a.c.FormatError,reason):
                a.constant_evidence(FakeDB(raw),mapping,0x804375d0,4)
        for address,width in ((0x804375d1,4),(0x804375d0,3),(mapping[0]-4,4),(mapping[1],4)):
            with patch.object(a,'TARGETS',((address,width,'unused'),)):
                with self.assertRaisesRegex(a.c.FormatError,'alignment/width/bounds'):
                    a.constant_evidence(None,mapping,address,width)

    def test_authentication_precedes_parsing_and_all_fixed_reads(self):
        for digest in ('0'*64,hashlib.sha256(bytes(32)).hexdigest(),next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c,'GBF') as parser,patch.object(a,'range_evidence') as ranges, \
                    patch.object(a,'constant_evidence') as constants:
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'): a.inspect(bytes(32),digest)
                parser.assert_not_called(); ranges.assert_not_called(); constants.assert_not_called()
        for reason in ('unsupported schema','language mismatch','File Bytes table is not empty','data5 digest mismatch'):
            with patch.object(a.c,'inspect',side_effect=a.c.FormatError(reason)),patch.object(a.c,'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError,reason): a.inspect(b'synthetic','synthetic')
                parser.assert_not_called()

    def test_no_arbitrary_cli(self):
        for option in (['--address','80068030'],['--width','164'],['--raw'],['--execute'],
                       ['--pointer','80433934'],['--follow-pointer'],['--index','217']):
            with patch.object(a.sys,'argv',['reader','fixture.gbf']+option), \
                    contextlib.redirect_stderr(io.StringIO()),patch.object(a,'inspect') as inspect:
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
                    patch.object(a,'range_evidence') as ranges,patch.object(a,'constant_evidence') as constants:
                db=parser.return_value
                db.tables.return_value={'Memory Blocks':'blocks','Sub Memory Blocks':'subs'}
                db.rows.side_effect=lambda name:{'blocks':bb,'subs':ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic','synthetic')
                ranges.assert_not_called(); constants.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base=Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR',str(default)))
        paths=[base/f'db.{n}.gbf' for n in (3,4)]
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('both existing local archived snapshots required')
        cls.results=[]
        cls.dbs=[]
        cls.callers=[]
        for path in paths:
            a.c.require(32<=path.stat().st_size<=a.c.MAX_FILE,'snapshot size bounds')
            with path.open('rb') as stream: data=stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data)<=a.c.MAX_FILE,'snapshot size bounds')
            cls.results.append(a.inspect(data,hashlib.sha256(data).hexdigest()))
            db=a.c.GBF(data)
            cls.dbs.append(db)
            # Reuse the unchanged, already allowlisted complete caller. No gap read.
            cls.callers.append(tick.range_evidence(db,21,0x80059068,0xd0))
        cls.facts={int(f['address'],16):f for span in cls.results[0]['ranges'] for f in span['instructions']}

    def test_full_coverage_both_archives(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results},set(a.c.SNAPSHOTS))
        for key in ('ranges','constants','function_coverage','r2_basis','r13_basis'):
            self.assertEqual(self.results[0][key],self.results[1][key])
        self.assertEqual(len(self.facts),44)
        for result in self.results:
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            self.assertEqual([x['represented_instructions'] for x in result['function_coverage']],[41,3])
            for coverage in result['function_coverage']:
                self.assertEqual(coverage['unrepresented_instructions'],0)
                self.assertEqual(coverage['unrepresented_ranges'],[])
            for span in result['ranges']:
                for item in [span]+span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw','word','words','hex','bytes')))

    def test_every_operand_in_exact_order(self):
        for result in self.results:
            for span in result['ranges']:
                self.assertEqual(span['instructions'],expected_facts(int(span['address'],16)))

    def test_extents_agree_with_map_c_next_entry_and_final_return(self):
        research=Path(__file__).resolve().parents[2]
        mapping=(research/'symbols/GG4E-CSM-20220412.map').read_text()
        for entry,width,chunk in ((0x80068030,0xa4,'0008'),(0x8008b290,0xc,'0013')):
            source=(research/f'decomp/ghidra-export/chunk_{chunk}.c').read_text()
            start=source.index(f'// ==== {entry:08x} ')
            next_entry=source.index('// ==== ',start+8)
            self.assertTrue(source[next_entry:].startswith(f'// ==== {entry+width:08x} '))
            line=next(line for line in mapping.splitlines() if line.startswith(f'{entry:08x} '))
            self.assertEqual(int(line.split()[1],16),width)
            self.assertEqual(self.facts[entry+width-4]['mnemonic'],'blr')

    def test_positive_zero_and_global_bases_without_pointer_reads(self):
        value=self.results[0]['constants'][0]
        self.assertEqual((value['address'],value['bits'],value['value']),('804375d0','00000000',0.0))
        self.assertEqual(self.facts[0x8006807c]['displacement']+0x8043ea20,0x804375d0)
        self.assertEqual(self.facts[0x8008b290]['displacement']+0x8043b5a0,0x80433934)
        for pc in (0x80068064,0x8006808c):
            self.assertEqual(self.facts[pc]['rA'],13)
            self.assertEqual(self.facts[pc]['displacement']+0x8043b5a0,0x8043625c)
        self.assertEqual([x['address'] for x in self.results[0]['constants']],['804375d0'])

    def test_unsigned_leaf_and_lazy_actor_signed_byte(self):
        leaf=[self.facts[pc] for pc in range(0x8008b290,0x8008b29c,4)]
        self.assertEqual([x['mnemonic'] for x in leaf],['lwz','lbz','blr'])
        self.assertEqual(leaf[1]['displacement'],0xd9)
        self.assertEqual(self.facts[0x80068048]['rA'],3)
        self.assertEqual(self.facts[0x8006804c]['target'],'800680bc')
        self.assertEqual(self.facts[0x80068050]['displacement'],0x1db)
        self.assertEqual(self.facts[0x80068054]['mnemonic'],'extsb')
        self.assertEqual(self.facts[0x80068054]['Rc'],1)
        self.assertEqual(self.facts[0x80068058]['target'],'800680bc')

    def test_float_loads_arithmetic_comparison_and_write_order(self):
        f=self.facts
        self.assertEqual([f[pc]['mnemonic'] for pc in range(0x8006805c,0x80068078,4)],
                         ['lfs','lfs','lwz','fadds','lfs','fcmpo','bc'])
        self.assertEqual([f[pc]['displacement'] for pc in (0x8006805c,0x80068060,0x8006806c)],
                         [0x24,0x668,0x34])
        self.assertEqual([f[pc]['mnemonic'] for pc in range(0x80068078,0x800680a8,4)],
                         ['lfs','lfs','fcmpo','bc','stfs','lwz','lfs','lfs','lfs','fsubs','fcmpo','bc'])
        self.assertEqual([f[pc]['displacement'] for pc in (0x80068088,0x80068090,0x80068094,0x80068098)],
                         [0x48,0x668,0x34,0x30])
        for pc in (0x80068074,0x80068084,0x800680a4):
            self.assertEqual((f[pc]['BO'],f[pc]['BI']),(4,1))
        self.assertEqual(f[0x8006809c],dict(address='8006809c',mnemonic='fsubs',fD=0,fA=1,fB=0))
        self.assertEqual(f[0x800680a4]['target'],'800680b0')
        self.assertEqual((f[0x800680a8]['fS'],f[0x800680b0]['fS']),(2,0))
        self.assertEqual([f[pc]['immediate'] for pc in (0x800680b4,0x800680bc)],[1,0])

    def test_reused_caller_final_call_is_followed_only_by_void_epilogue(self):
        self.assertEqual(self.callers[0],self.callers[1])
        for caller in self.callers:
            self.assertEqual((caller['address'],caller['end_exclusive'],caller['width']),
                             ('80059068','80059138',0xd0))
            tail=[x for x in caller['instructions'] if int(x['address'],16)>=0x8005911c]
            self.assertEqual(tail,[
                dict(address='8005911c',mnemonic='or',rS=31,rA=3,rB=31,Rc=0),
                dict(address='80059120',mnemonic='bl',target='80068030',AA=0),
                dict(address='80059124',mnemonic='lwz',rD=0,rA=1,displacement=20),
                dict(address='80059128',mnemonic='lwz',rD=31,rA=1,displacement=12),
                dict(address='8005912c',mnemonic='mtlr',rS=0),
                dict(address='80059130',mnemonic='addi',rD=1,rA=1,immediate=16),
                dict(address='80059134',mnemonic='blr')])
        research=Path(__file__).resolve().parents[2]
        source=(research/'decomp/ghidra-export/chunk_0007.c').read_text()
        start=source.index('// ==== 80059068 ')
        end=source.index('// ==== ',start+8)
        self.assertIn('void zz_0059068_',source[start:end])
        self.assertTrue(source[end:].startswith('// ==== 8005913c '))
        self.assertEqual(tick.RANGES[0][:2],(0x80059068,0xd0))
        self.assertFalse(any(pc<=0x80059138<pc+width for pc,width,_ in a.RANGES+tick.RANGES))

    def test_each_instruction_mutation_rejected_before_decode(self):
        for db in self.dbs:
            for pc,width,_ in a.RANGES:
                raw=db.chain(21,pc-a.TEXT_START,width,a.TEXT_LENGTH)[0]
                for offset in range(0,width,4):
                    changed=bytearray(raw); changed[offset+3]^=1
                    with patch.object(a,'decode_selected') as decoder:
                        with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'):
                            a.range_evidence(FakeDB(changed),21,pc,width)
                        decoder.assert_not_called()

    def test_each_fixed_constant_byte_mutation_rejected(self):
        for db in self.dbs:
            for address,width,_ in a.TARGETS:
                raw=db.chain(263,address-a.DATA5_MAPPING[0],width,a.DATA5_MAPPING[-2])[0]
                for offset in range(width):
                    changed=bytearray(raw);changed[offset]^=1
                    with self.assertRaisesRegex(a.c.FormatError,'bits mismatch'):
                        a.constant_evidence(FakeDB(changed),a.DATA5_MAPPING,address,width)


if __name__=='__main__': unittest.main()
