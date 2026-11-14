#!/usr/bin/env python3
"""Fixed ready-lifecycle operands and fail-closed guards, no payload fixtures."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_ready_lifecycle_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


# Explicit derived operands, independent of the reader's decoding implementation.
# No archived instruction words or executable payload is stored here.
EXPECTED = {
    0x8006a980: '''
stwu rS=1 rA=1 displacement=-64
mflr rD=0
addi rD=4 rA=0 immediate=2
stw rS=0 rA=1 displacement=68
addi rD=0 rA=0 immediate=4
stw rS=31 rA=1 displacement=60
or rS=3 rA=31 rB=3 Rc=0
stb rS=4 rA=3 displacement=24
addi rD=3 rA=0 immediate=0
stb rS=4 rA=31 displacement=25
stb rS=3 rA=31 displacement=26
stb rS=3 rA=31 displacement=27
lha rD=3 rA=31 displacement=626
ori rS=3 rA=3 immediate=1091
sth rS=3 rA=31 displacement=626
stb rS=0 rA=31 displacement=1168
lha rD=0 rA=31 displacement=1002
sth rS=0 rA=31 displacement=1164
lbz rD=0 rA=31 displacement=1005
stb rS=0 rA=31 displacement=1166
lbz rD=0 rA=31 displacement=1007
stb rS=0 rA=31 displacement=1167
lbz rD=0 rA=31 displacement=1184
extsb rS=0 rA=0 Rc=1
bc BO=12 BI=2 LK=0 target=8006aa84 AA=0
lhz rD=0 rA=31 displacement=1164
addi rD=3 rA=1 immediate=8
sth rS=0 rA=1 displacement=8
lbz rD=4 rA=31 displacement=1166
lbz rD=5 rA=31 displacement=1167
extsb rS=4 rA=4 Rc=0
extsb rS=5 rA=5 Rc=0
bl target=80066198 AA=0
lha rD=4 rA=31 displacement=454
addis rD=5 rA=0 immediate=17200
lha rD=0 rA=31 displacement=452
extsh rS=3 rA=6 Rc=0
xoris rS=4 rA=3 immediate=32768
stw rS=5 rA=1 displacement=24
xoris rS=0 rA=0 immediate=32768
xoris rS=6 rA=4 immediate=32768
stw rS=3 rA=1 displacement=28
lfd fD=2 rA=2 displacement=-29648
lfd fD=0 rA=1 displacement=24
stw rS=0 rA=1 displacement=36
fsubs fD=1 fA=0 fB=2
stw rS=5 rA=1 displacement=32
lfd fD=0 rA=1 displacement=32
stw rS=4 rA=1 displacement=20
fsubs fD=0 fA=0 fB=2
stw rS=5 rA=1 displacement=16
fdivs fD=0 fA=1 fB=0
lfd fD=1 rA=1 displacement=16
fsubs fD=1 fA=1 fB=2
fmuls fD=0 fA=1 fC=0
fctiwz fD=0 fB=0
stfd fS=0 rA=1 displacement=40
lwz rD=0 rA=1 displacement=44
sth rS=0 rA=31 displacement=1172
lha rD=0 rA=31 displacement=1172
cmpi BF=0 L=0 rA=0 immediate=0
bc BO=12 BI=1 LK=0 target=8006aa8c AA=0
addi rD=0 rA=0 immediate=1
sth rS=0 rA=31 displacement=1172
b target=8006aa8c AA=0
lha rD=0 rA=31 displacement=454
sth rS=0 rA=31 displacement=1172
lha rD=3 rA=31 displacement=452
addi rD=0 rA=0 immediate=0
sth rS=3 rA=31 displacement=1174
stb rS=0 rA=31 displacement=1185
lwz rD=31 rA=1 displacement=60
lwz rD=0 rA=1 displacement=68
mtlr rS=0
addi rD=1 rA=1 immediate=64
blr
''',
    0x8006aab0: '''
addi rD=5 rA=0 immediate=2
addi rD=4 rA=0 immediate=0
stb rS=5 rA=3 displacement=24
addi rD=0 rA=0 immediate=4
stb rS=5 rA=3 displacement=25
stb rS=4 rA=3 displacement=26
stb rS=4 rA=3 displacement=27
lha rD=4 rA=3 displacement=626
ori rS=4 rA=4 immediate=1091
sth rS=4 rA=3 displacement=626
stb rS=0 rA=3 displacement=1162
stb rS=0 rA=3 displacement=1168
lha rD=0 rA=3 displacement=1182
sth rS=0 rA=3 displacement=1164
lbz rD=0 rA=3 displacement=1005
stb rS=0 rA=3 displacement=1166
lha rD=0 rA=3 displacement=454
sth rS=0 rA=3 displacement=1172
lha rD=0 rA=3 displacement=452
sth rS=0 rA=3 displacement=1174
blr
''',
    0x8005a298: '''
stwu rS=1 rA=1 displacement=-16
mflr rD=0
stw rS=0 rA=1 displacement=20
stw rS=31 rA=1 displacement=12
or rS=3 rA=31 rB=3 Rc=0
lbz rD=0 rA=3 displacement=2002
rlwinm rS=0 rA=0 SH=0 MB=30 ME=31 Rc=0
cmpi BF=0 L=0 rA=0 immediate=1
bc BO=4 BI=2 LK=0 target=8005a2d4 AA=0
lwz rD=0 rA=31 displacement=1460
rlwinm rS=0 rA=0 SH=0 MB=27 ME=27 Rc=1
bc BO=4 BI=2 LK=0 target=8005a364 AA=0
addi rD=0 rA=0 immediate=4
stb rS=0 rA=31 displacement=1852
b target=8005a364 AA=0
lbz rD=0 rA=31 displacement=1855
extsb rS=0 rA=0 Rc=1
bc BO=4 BI=2 LK=0 target=8005a364 AA=0
lbz rD=0 rA=31 displacement=1852
extsb rS=0 rA=0 Rc=1
bc BO=4 BI=2 LK=0 target=8005a364 AA=0
lbz rD=0 rA=31 displacement=1185
extsb rS=0 rA=0 Rc=1
bc BO=4 BI=2 LK=0 target=8005a34c AA=0
lbz rD=3 rA=31 displacement=996
extsb rS=3 rA=3 Rc=0
bl target=80010514 AA=0
cmpi BF=0 L=0 rA=3 immediate=0
bc BO=4 BI=2 LK=0 target=8005a364 AA=0
lwz rD=3 rA=31 displacement=1492
rlwinm rS=3 rA=0 SH=0 MB=29 ME=29 Rc=1
bc BO=12 BI=2 LK=0 target=8005a324 AA=0
addi rD=0 rA=0 immediate=2
stb rS=0 rA=31 displacement=1852
b target=8005a364 AA=0
rlwinm rS=3 rA=0 SH=0 MB=28 ME=28 Rc=1
bc BO=12 BI=2 LK=0 target=8005a338 AA=0
addi rD=0 rA=0 immediate=3
stb rS=0 rA=31 displacement=1852
b target=8005a364 AA=0
rlwinm rS=3 rA=0 SH=0 MB=27 ME=27 Rc=1
bc BO=12 BI=2 LK=0 target=8005a364 AA=0
addi rD=0 rA=0 immediate=5
stb rS=0 rA=31 displacement=1852
b target=8005a364 AA=0
lwz rD=3 rA=31 displacement=1288
lwz rD=0 rA=31 displacement=1188
cmpl BF=0 L=0 rA=3 rB=0
bc BO=4 BI=2 LK=0 target=8005a364 AA=0
addi rD=0 rA=0 immediate=2
stb rS=0 rA=31 displacement=1852
lwz rD=0 rA=1 displacement=20
lwz rD=31 rA=1 displacement=12
mtlr rS=0
addi rD=1 rA=1 immediate=16
blr
''',
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
    def test_extents_and_no_new_data(self):
        self.assertEqual([(pc,n) for pc,n,_ in a.RANGES],
                         [(0x8006a980,304),(0x8006aab0,84),(0x8005a298,224)])
        self.assertEqual(len(a.c.TARGETS),12)
        self.assertNotIn(0x80437650,a.c.EXPECTED_TARGETS)
        self.assertFalse(hasattr(a,'TARGETS'))
        self.assertFalse(hasattr(a,'DATA_RANGES'))
        for entry,width,_ in a.RANGES:
            self.assertEqual(len(expected_facts(entry)),width//4)

    def test_decoder_bounds_and_unselected_forms(self):
        for word in (-1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)
        for pc in (-1,1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0,pc)
        for word in (0,d_form(48,3,4,0),0x4e800421,d_form(10,0,4,0),
                     (59<<26)|(21<<1),(31<<26)|(87<<1)):
            self.assertIsNone(a.decode_selected(word,0))

    def test_reserved_fields_rejected(self):
        words = ((31<<26)|(32<<1)|1, (31<<26)|(1<<21)|(32<<1),
                 (31<<26)|(954<<1)|(1<<11), (31<<26)|(922<<1)|(1<<11),
                 (11<<26)|(1<<21), (59<<26)|(18<<1)|(1<<6),
                 (59<<26)|(20<<1)|1, (59<<26)|(25<<1)|(1<<11),
                 (63<<26)|(15<<1)|(1<<16), (63<<26)|(15<<1)|1,
                 spr_form(339,1,8), spr_form(467,0,9), spr_form(339,0,8)|1)
        for word in words:
            with self.subTest(word=word):
                with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)

    def test_synthetic_signedness_and_operand_direction(self):
        for op,name,source in ((40,'lhz','rD'),(42,'lha','rD'),(44,'sth','rS'),
                               (38,'stb','rS'),(50,'lfd','fD'),(54,'stfd','fS')):
            self.assertEqual(a.decode_selected(d_form(op,7,9,-2),0),
                             dict(mnemonic=name,rA=9,displacement=-2,**{source:7}))
        for op,name in ((24,'ori'),(27,'xoris')):
            self.assertEqual(a.decode_selected(d_form(op,7,9,0xffff),0),
                             dict(mnemonic=name,rS=7,rA=9,immediate=65535))
        self.assertEqual(a.decode_selected((31<<26)|(8<<21)|(7<<16)|(9<<11)|(32<<1),0),
                         dict(mnemonic='cmpl',BF=2,L=0,rA=7,rB=9))
        for xo,name in ((18,'fdivs'),(20,'fsubs')):
            self.assertEqual(a.decode_selected((59<<26)|(7<<21)|(9<<16)|(11<<11)|(xo<<1),0),
                             dict(mnemonic=name,fD=7,fA=9,fB=11))
        self.assertEqual(a.decode_selected((59<<26)|(7<<21)|(9<<16)|(11<<6)|(25<<1),0),
                         dict(mnemonic='fmuls',fD=7,fA=9,fC=11))
        self.assertEqual(a.decode_selected((63<<26)|(7<<21)|(11<<11)|(15<<1),0),
                         dict(mnemonic='fctiwz',fD=7,fB=11))
        self.assertEqual(a.decode_selected((18<<26)|0x03fffffd,0x1000),
                         dict(mnemonic='bl',target='00000ffc',AA=0))
        self.assertEqual(a.decode_selected((16<<26)|(12<<21)|(2<<16)|0xfffc,0x1000),
                         dict(mnemonic='bc',BO=12,BI=2,LK=0,target='00000ffc',AA=0))

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

    def test_authentication_precedes_parsing(self):
        for digest in ('0'*64,hashlib.sha256(bytes(32)).hexdigest(),next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c,'GBF') as parser,patch.object(a,'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'): a.inspect(bytes(32),digest)
                parser.assert_not_called(); reader.assert_not_called()
        for reason in ('unsupported schema','language mismatch','File Bytes table is not empty','data5 digest mismatch'):
            with patch.object(a.c,'inspect',side_effect=a.c.FormatError(reason)),patch.object(a.c,'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError,reason): a.inspect(b'synthetic','synthetic')
                parser.assert_not_called()

    def test_no_arbitrary_cli(self):
        for option in (['--address','8006a980'],['--width','304'],['--raw'],['--execute'],['--index','0']):
            with patch.object(a.sys,'argv',['reader','fixture.gbf']+option),contextlib.redirect_stderr(io.StringIO()),patch.object(a,'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code,2); inspect.assert_not_called()

    def test_mapping_guards_precede_fixed_reads(self):
        auth={'image_offset':'80000000'}
        blocks={key:[name,None,None,0,encoded,length,0]
                for name,key,encoded,length,root in a.command.MAPPINGS}
        subs={key:[key,2,length,0,root,0]
              for name,key,encoded,length,root in a.command.MAPPINGS}
        for target in ('root','offset','type','duplicate','overlap','image','data5'):
            aa,bb,ss=copy.deepcopy((auth,blocks,subs))
            if target=='root': ss[1][4]+=1
            if target=='offset': ss[1][5]+=1
            if target=='type': ss[1][1]+=1
            if target=='duplicate': bb[99]=copy.deepcopy(bb[1])
            if target=='overlap': bb[99]=['other',None,None,0,0x20000000000055e4,4,0]
            if target=='image': aa['image_offset']='80000004'
            if target=='data5': ss[7][4]+=1
            with patch.object(a.c,'inspect',return_value=aa),patch.object(a.c,'GBF') as parser, \
                    patch.object(a,'range_evidence') as ranges:
                db=parser.return_value
                db.tables.return_value={'Memory Blocks':'blocks','Sub Memory Blocks':'subs'}
                db.rows.side_effect=lambda name:{'blocks':bb,'subs':ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic','synthetic')
                ranges.assert_not_called()


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
            # Reuse only already authenticated snapshots for mutation checks.
            cls.dbs.append(a.c.GBF(data))
        cls.facts={int(f['address'],16):f for span in cls.results[0]['ranges'] for f in span['instructions']}

    def test_full_coverage_both_archives(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results},set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'],self.results[1]['ranges'])
        self.assertEqual(len(self.facts),153)
        for result in self.results:
            self.assertEqual(result['constants'],[])
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            for coverage,(_,width,_) in zip(result['function_coverage'],a.RANGES):
                self.assertEqual(coverage['represented_instructions'],width//4)
                self.assertEqual(coverage['unrepresented_instructions'],0)
                self.assertEqual(coverage['unrepresented_ranges'],[])
            for span in result['ranges']:
                for item in [span]+span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw','word','words','hex','bytes')))

    def test_every_operand_in_exact_order(self):
        for result in self.results:
            for span in result['ranges']:
                self.assertEqual(span['instructions'],expected_facts(int(span['address'],16)))

    def test_boundaries_c_next_entries_and_final_returns(self):
        research=Path(__file__).resolve().parents[2]
        mapping=(research/'symbols/GG4E-CSM-20220412.map').read_text()
        for entry,width,_ in a.RANGES:
            name='chunk_0007.c' if entry==0x8005a298 else 'chunk_0009.c'
            source=(research/'decomp/ghidra-export'/name).read_text()
            start=source.index(f'// ==== {entry:08x} ')
            next_entry=source.index('// ==== ',start+8)
            self.assertTrue(source[next_entry:].startswith(f'// ==== {entry+width:08x} '))
            self.assertEqual(self.facts[entry+width-4]['mnemonic'],'blr')
            self.assertFalse(any(line.startswith(f'{entry:08x} ') for line in mapping.splitlines()))
        self.assertIn('8006ab04 00000098 8006ab04',mapping)

    def test_lazy_gates_writes_and_external_boundaries(self):
        facts=self.facts
        self.assertEqual(facts[0x8006a9d8]['displacement'],0x4a0)
        self.assertEqual(facts[0x8006a9e0]['target'],'8006aa84')
        self.assertEqual(facts[0x8006aa84]['displacement'],0x1c6)
        self.assertEqual(facts[0x8006aa88]['displacement'],0x494)
        self.assertEqual(facts[0x8006aa8c]['displacement'],0x1c4)
        self.assertEqual(facts[0x8006aa94]['displacement'],0x496)
        self.assertEqual(facts[0x8006aa98]['displacement'],0x4a1)
        leaf=[facts[pc] for pc in range(0x8006aab0,0x8006ab04,4)]
        self.assertFalse(any(f['mnemonic'] in ('b','bl','bc') for f in leaf))
        self.assertEqual([f['displacement'] for f in leaf if f['mnemonic'] in ('stb','sth')],
                         [0x18,0x19,0x1a,0x1b,0x272,0x48a,0x490,0x48c,0x48e,0x494,0x496])
        calls=[(f['address'],f['target']) for f in facts.values() if f['mnemonic']=='bl']
        self.assertEqual(calls,[('8006aa00','80066198'),('8005a300','80010514')])
        self.assertEqual([(pc,facts[pc]['displacement']) for pc in (0x8005a2d4,0x8005a2e0,0x8005a2ec)],
                         [(0x8005a2d4,0x73f),(0x8005a2e0,0x73c),(0x8005a2ec,0x4a1)])
        self.assertEqual(facts[0x8005a30c]['displacement'],0x5d4)
        self.assertEqual(facts[0x8006aa28],dict(address='8006aa28',mnemonic='lfd',fD=2,rA=2,displacement=-29648))
        self.assertEqual({facts[pc]['mnemonic'] for pc in range(0x8006aa04,0x8006aa84,4)} &
                         {'fsubs','fdivs','fmuls','fctiwz','lfd','stfd'},
                         {'fsubs','fdivs','fmuls','fctiwz','lfd','stfd'})

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



if __name__=='__main__': unittest.main()
