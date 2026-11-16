#!/usr/bin/env python3
"""All control/effect operands, fixed data, authentication and rejection tests."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_control_effect_evidence as a
import read_archived_tick_prefix_evidence as tick
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def ops(text):
    """Explicit independently maintained expected operands, not an executor."""
    fields = {'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement', 'sth': 'rS rA displacement', 'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement', 'lha': 'rD rA displacement', 'lhz': 'rD rA displacement', 'lwzx': 'rD rA rB', 'lfs': 'fD rA displacement', 'stfs': 'fS rA displacement', 'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'add': 'rD rA rB Rc', 'mflr': 'rD', 'mtlr': 'rS', 'rlwinm': 'rS rA SH MB ME Rc', 'extsb': 'rS rA Rc', 'extsh': 'rS rA Rc', 'cntlzw': 'rS rA Rc', 'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc', 'cmp': 'BF L rA rB', 'cmpi': 'BF L rA immediate', 'cmpli': 'BF L rA immediate', 'blr': '', 'bc': 'BO BI target', 'bl': 'target', 'b': 'target'}
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = fields[name].split()
        assert len(keys) == len(values), line
        item = dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                    for key, value in zip(keys, values)})
        if name in ('bc', 'bl', 'b'): item['AA'] = 0
        if name == 'bc': item['LK'] = 0
        result.append(item)
    return result


EXPECTED = {
    0x8005a190: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
lbz 0 3 1185
extsb 0 0 1
bc 4 2 8005a1c8
lbz 0 31 1184
extsb 0 0 1
bc 4 2 8005a1c8
lbz 0 31 1788
extsb 0 0 1
bc 12 2 8005a1d0
addi 3 0 0
b 8005a284
lbz 0 31 1162
cmpi 0 0 0 2
bc 4 2 8005a224
lha 4 31 1180
cmpi 0 0 4 0
bc 4 1 8005a1f4
addi 0 4 -1
sth 0 31 1180
b 8005a280
bl 8006ab9c
cmpi 0 0 3 0
bc 12 2 8005a280
or 31 3 31 0
bl 8006aab0
lbz 4 31 136
or 31 3 31 0
addi 5 0 0
extsb 4 4 0
bl 80176ec0
addi 3 0 1
b 8005a284
lbz 0 31 1168
cmpi 0 0 0 2
bc 4 2 8005a280
lha 4 31 1178
cmpi 0 0 4 0
bc 4 1 8005a280
addi 4 4 -1
extsh 4 0 1
sth 4 31 1178
bc 12 1 8005a280
bl 8006abb8
cmpi 0 0 3 0
bc 12 2 8005a278
or 31 3 31 0
bl 8006a980
addi 3 0 4
addi 0 0 3
stb 3 31 1161
addi 3 0 1
stb 0 31 25
b 8005a284
addi 0 0 1
sth 0 31 1178
addi 3 0 0
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr
'''),
    0x8006ab9c: ops('''
addis 4 0 -28416
lwz 3 3 1504
addi 0 4 4099
and 3 0 0 0
cntlzw 0 0 0
rlwinm 0 3 27 5 31 0
blr
'''),
    0x8006abb8: ops('''
addis 4 0 -28416
lwz 3 3 1504
addi 0 4 4096
and 3 0 0 0
cntlzw 0 0 0
rlwinm 0 3 27 5 31 0
blr
'''),
    0x800061cc: ops('''
stwu 1 1 -16
mflr 0
addi 5 0 0
stw 0 1 20
bl 800061f0
lwz 0 1 20
mtlr 0
addi 1 1 16
blr
'''),
    0x800061f0: ops('''
add 7 3 5 0
addi 8 0 0
addis 6 0 -32724
stb 8 7 2015
rlwinm 4 0 2 0 29 0
rlwinm 5 5 2 0 29 0
addi 4 6 14192
lfs 0 2 -32768
lwzx 4 4 0
add 3 3 5 0
addi 0 0 255
stw 4 3 2028
stfs 0 3 2020
stb 0 3 2039
stb 8 3 2036
stb 8 3 2037
stb 8 3 2038
blr
'''),
    0x800f0104: ops('''
stwu 1 1 -32
mflr 0
addis 6 0 -32707
addi 8 0 0
stw 0 1 36
addi 6 6 15080
rlwinm 5 0 4 20 27 0
stw 31 1 28
or 4 31 4 0
stw 30 1 24
or 3 30 3 0
stw 29 1 20
lbz 7 3 150
extsb 7 7 0
rlwinm 7 7 7 0 24 0
add 6 6 7 0
add 6 6 0 0
lwz 7 6 88
addi 29 6 80
cmpli 0 0 7 0
bc 4 2 800f0160
addi 8 0 1
b 800f0188
addis 6 0 -32718
rlwinm 31 0 2 22 29 0
addi 6 6 -18796
lha 7 7 0
lwzx 6 6 0
lha 0 6 0
cmp 0 0 7 0
bc 12 2 800f0188
bl 800f02d0
addi 8 0 1
cmpi 0 0 8 1
bc 4 2 800f01ec
addis 3 0 -32718
rlwinm 31 0 2 22 29 0
addi 3 3 -18796
lwzx 0 3 0
stw 0 29 8
bl 80207058
stw 3 29 0
lwz 3 29 8
lhz 0 3 4
cmpi 0 0 0 1
bc 12 2 800f01dc
bc 4 0 800f01ec
cmpi 0 0 0 0
bc 4 0 800f01cc
b 800f01ec
lha 4 3 0
or 30 3 30 0
bl 800f036c
b 800f01ec
lha 4 3 0
or 30 3 30 0
lfs 1 2 -22992
bl 800f061c
stw 30 29 12
addi 0 0 2
stw 0 29 4
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
lwz 0 1 36
mtlr 0
addi 1 1 32
blr
'''),
}


class DataDB(FakeDB):
    """Synthetic fixed cue1 anchor; no arbitrary archive input."""
    def __init__(self, raw, anchor=0x8031b454):
        super().__init__(raw)
        self.anchor = anchor
        self.calls = []

    def chain(self, root, offset, width, length):
        self.calls.append((root, offset, width, length))
        if offset == 0x8031b698 - 0x802bae60:
            return struct.pack('>I', self.anchor), []
        return self.raw, [dict(synthetic=True)]


class SyntheticTests(unittest.TestCase):
    def test_extents_and_types(self):
        self.assertEqual([r[:2] for r in a.RANGES],
                         [(0x8005a190,264),(0x8006ab9c,28),(0x8006abb8,28),
                          (0x800061cc,36),(0x800061f0,72),(0x800f0104,272)])
        self.assertEqual([r[:2] for r in a.DATA_RANGES],
                         [(0x80436a20,4),(0x802c37bc,8),(0x8031b698,4),(0x8031b454,2)])
        for word in (-1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)
        for pc in (-1,1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0,pc)

    def test_new_forms_and_reserved_fields(self):
        cntlzw=(31<<26)|(7<<21)|(3<<16)|(26<<1)
        for rc in (0,1):
            self.assertEqual(a.decode_selected(cntlzw|rc,0),dict(mnemonic='cntlzw',rS=7,rA=3,Rc=rc))
        with self.assertRaisesRegex(a.c.FormatError,'reserved cntlzw'):
            a.decode_selected(cntlzw|(1<<11),0)
        self.assertEqual(a.decode_selected(d_form(40,4,7,-2),0),
                         dict(mnemonic='lhz',rD=4,rA=7,displacement=-2))
        self.assertEqual(a.decode_selected(d_form(42,4,7,-2),0),
                         dict(mnemonic='lha',rD=4,rA=7,displacement=-2))
        lwzx=(31<<26)|(4<<21)|(7<<16)|(5<<11)|(23<<1)
        self.assertEqual(a.decode_selected(lwzx,0),dict(mnemonic='lwzx',rD=4,rA=7,rB=5))
        with self.assertRaisesRegex(a.c.FormatError,'reserved indexed-load'): a.decode_selected(lwzx|1,0)
        for word in (d_form(11,1,4,1),d_form(10,1,4,1),spr_form(339,1),spr_form(467,0,9),
                     spr_form(339,0)|1,(31<<26)|(954<<1)|(1<<11),
                     (31<<26)|(922<<1)|(1<<11),(31<<26)|(1<<21)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)

    def test_unsupported_forms(self):
        for word in (0,0x4e800421,d_form(7,1,4,1),d_form(24,1,4,1),
                     d_form(46,24,1,16),d_form(47,24,1,16),d_form(50,31,1,16),
                     d_form(54,31,1,16),d_form(56,31,1,16),d_form(60,31,1,16),
                     (31<<26)|(24<<1),(31<<26)|(87<<1),(31<<26)|(343<<1),
                     (31<<26)|(60<<1),(19<<26)|(449<<1),(59<<26)|(21<<1)):
            self.assertIsNone(a.decode_selected(word,0))

    def test_fixed_instruction_reads_reject_before_decode(self):
        for pc,size,_ in a.RANGES:
            for address,width in ((pc+4,size-4),(pc,size-4),(pc,size+4),(pc-4,size+4)):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                    a.range_evidence(None,21,address,width)
            for fields in ((21.0,pc,size),(21,True,size),(21,pc,float(size))):
                with self.assertRaisesRegex(a.c.FormatError,'integer fields'): a.range_evidence(None,*fields)
            with self.assertRaisesRegex(a.c.FormatError,'root/alignment/bounds'):
                a.range_evidence(None,22,pc,size)
            for raw,reason in ((bytes(size),'digest'),(bytes(size-4),'byte width'),(bytes(size+4),'byte width')):
                with patch.object(a,'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError,reason):
                        a.range_evidence(FakeDB(raw),21,pc,size)
                    decoder.assert_not_called()
        pc=a.RANGES[0][0]
        with patch.object(a,'RANGES',((pc,4,hashlib.sha256(bytes(4)).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError,'unselected instruction'):
                a.range_evidence(FakeDB(bytes(4)),21,pc,4)
        with patch.object(a,'RANGES',a.RANGES*2):
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'): a.range_evidence(None,21,pc,264)

    def test_fixed_data_mapping_and_extent_refusals(self):
        for pc,size,_ in a.DATA_RANGES:
            mapping=a.DATA5_MAPPING if pc==0x80436a20 else a.DATA3_MAPPING
            for address,width in ((pc+size,size),(pc,size+2),(pc,size-2),(pc-2,size+2),
                                   (0x802c3770,4),(0x802c37b8,4),(0x802c37c4,4),
                                   (0x8031b694,4),(0x8031b454,6),(0x8031b456,2)):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                    a.data_evidence(None,mapping,address,width)
            for address,width in ((float(pc),size),(pc,True),(pc,float(size))):
                with self.assertRaisesRegex(a.c.FormatError,'integer fields'):
                    a.data_evidence(None,mapping,address,width)
            for index in (0,1,2,4,5,6):
                for value in (mapping[index]+4,float(mapping[index])):
                    changed=list(mapping);changed[index]=value
                    with self.assertRaisesRegex(a.c.FormatError,'mapping mismatch'):
                        a.data_evidence(None,tuple(changed),pc,size)
            for changed in (list(mapping),a.DATA3_MAPPING if mapping==a.DATA5_MAPPING else a.DATA5_MAPPING):
                with self.assertRaisesRegex(a.c.FormatError,'mapping mismatch'):
                    a.data_evidence(None,changed,pc,size)
            with patch.object(a,'DATA_RANGES',a.DATA_RANGES*2):
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                    a.data_evidence(None,mapping,pc,size)

    def test_data_width_digest_precede_value_checks(self):
        for pc,size,_ in a.DATA_RANGES:
            mapping=a.DATA5_MAPPING if pc==0x80436a20 else a.DATA3_MAPPING
            for raw,reason in ((bytes(size),'digest'),(bytes(size-1),'byte width'),(bytes(size+1),'byte width')):
                if pc==0x80436a20 and len(raw)==size: raw=b'\x80\0\0\0'
                db=DataDB(raw) if pc==0x8031b454 else FakeDB(raw)
                with self.assertRaisesRegex(a.c.FormatError,reason): a.data_evidence(db,mapping,pc,size)

    def test_values_checked_even_if_digest_were_changed(self):
        rows=((0x80436a20,struct.pack('>I',0x80000000),'positive zero'),
              (0x802c37bc,struct.pack('>II',0x802c36b4,0x802c36e0),'color pointer'),
              (0x802c37bc,struct.pack('>II',0x802c36b0,0x802c36e4),'color pointer'),
              (0x8031b698,struct.pack('>I',0x8031b456),'cue1 pointer'),
              (0x8031b454,struct.pack('>h',-126),'signed16 head'))
        for pc,raw,reason in rows:
            ranges=tuple((p,n,hashlib.sha256(raw).hexdigest() if p==pc else h)
                         for p,n,h in a.DATA_RANGES)
            mapping=a.DATA5_MAPPING if pc==0x80436a20 else a.DATA3_MAPPING
            with patch.object(a,'DATA_RANGES',ranges):
                with self.assertRaisesRegex(a.c.FormatError,reason):
                    a.data_evidence(DataDB(raw) if pc==0x8031b454 else FakeDB(raw),mapping,pc,len(raw))

    def test_head_has_fixed_pointer_anchor_before_any_head_read(self):
        db=DataDB(struct.pack('>h',126))
        result=a.data_evidence(db,a.DATA3_MAPPING,0x8031b454,2)
        self.assertEqual(result['fields'][0]['value'],126)
        self.assertEqual(db.calls,[(199,0x8031b698-0x802bae60,4,0xf42c0),
                                   (199,0x8031b454-0x802bae60,2,0xf42c0)])
        db=DataDB(struct.pack('>h',126),anchor=0x8031b458)
        with self.assertRaisesRegex(a.c.FormatError,'digest'):
            a.data_evidence(db,a.DATA3_MAPPING,0x8031b454,2)
        self.assertEqual(len(db.calls),1)
        self.assertNotIn((0x8031b458,2),[r[:2] for r in a.DATA_RANGES])

    def test_authentication_precedes_parsing(self):
        for digest in ('0'*64,hashlib.sha256(bytes(32)).hexdigest(),next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c,'GBF') as parser,patch.object(a,'range_evidence') as reader,\
                    patch.object(a,'data_evidence') as data_reader:
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'): a.inspect(bytes(32),digest)
                parser.assert_not_called();reader.assert_not_called();data_reader.assert_not_called()
        for reason in ('unsupported schema','language mismatch','File Bytes table is not empty','data5 digest mismatch'):
            with patch.object(a.c,'inspect',side_effect=a.c.FormatError(reason)),patch.object(a.c,'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError,reason): a.inspect(b'synthetic','synthetic')
                parser.assert_not_called()

    def test_schema_rejected_before_new_reads(self):
        data=b'synthetic schema fixture';digest=hashlib.sha256(data).hexdigest()
        schema=dict(version=0,keytype=4,types=[4],fields='Key;Value;')
        for field,value in (('version',1),('keytype',3),('types',[2]),('fields','Wrong;')):
            changed=dict(schema);changed[field]=value
            with patch.dict(a.c.SNAPSHOTS,{digest:'synthetic'}),patch.object(a.c,'GBF') as parser,\
                    patch.object(a,'range_evidence') as ranges,patch.object(a,'data_evidence') as data_reader:
                parser.return_value.tables.return_value={'Program':changed}
                with self.assertRaisesRegex(a.c.FormatError,'unsupported schema: Program'): a.inspect(data,digest)
                parser.return_value.rows.assert_not_called();ranges.assert_not_called();data_reader.assert_not_called()

    def test_mapping_guards_precede_fixed_reads(self):
        auth={'image_offset':'80000000'}
        blocks={key:[name,None,None,0,encoded,length,0]
                for name,key,encoded,length,root in a.command.MAPPINGS}
        subs={key:[key,2,length,0,root,0] for name,key,encoded,length,root in a.command.MAPPINGS}
        for target in ('root','offset','type','duplicate','overlap','image','data5root',
                       'data5offset','data5length','data3root','data3offset','data3length'):
            aa,bb,ss=copy.deepcopy((auth,blocks,subs))
            if target=='root': ss[1][4]+=1
            if target=='offset': ss[1][5]+=1
            if target=='type': ss[1][1]+=1
            if target=='duplicate': bb[99]=copy.deepcopy(bb[1])
            if target=='overlap': bb[99]=['other',None,None,0,0x20000000000055e4,4,0]
            if target=='image': aa['image_offset']='80000004'
            if target=='data5root': ss[7][4]+=1
            if target=='data5offset': ss[7][5]+=4
            if target=='data5length': bb[7][5]-=4
            if target=='data3root': ss[5][4]+=1
            if target=='data3offset': ss[5][5]+=4
            if target=='data3length': bb[5][5]-=4
            with patch.object(a.c,'inspect',return_value=aa),patch.object(a.c,'GBF') as parser,\
                    patch.object(a,'range_evidence') as ranges,patch.object(a,'data_evidence') as data_reader:
                db=parser.return_value;db.tables.return_value={'Memory Blocks':'blocks','Sub Memory Blocks':'subs'}
                db.rows.side_effect=lambda name:{'blocks':bb,'subs':ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic','synthetic')
                ranges.assert_not_called();data_reader.assert_not_called()

    def test_shared_allowlists_unchanged(self):
        for pc,size,_ in a.RANGES+a.DATA_RANGES:
            self.assertNotIn((pc,size),a.c.TARGETS)
            self.assertNotIn((pc,size),[r[:2] for r in a.command.RANGES])
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.command.read_range(None,pc,size,0x80000000)
        for reader in (a.charge,tick):
            for pc,size,_ in a.RANGES:
                self.assertNotIn((pc,size),[r[:2] for r in reader.RANGES])
                with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                    reader.range_evidence(None,21,pc,size)
        for pc,size,_ in a.DATA_RANGES:
            self.assertNotIn((pc,size),[r[:2] for r in a.charge.DATA_RANGES])
            with self.assertRaisesRegex(a.c.FormatError,'not allowlisted'):
                a.charge.data_evidence(None,a.DATA3_MAPPING,pc,size)

    def test_no_arbitrary_cli_or_execution(self):
        for option in (['--address','8005a190'],['--width','264'],['--raw'],['--execute'],['--index','1']):
            with patch.object(a.sys,'argv',['reader','fixture.gbf']+option),\
                    contextlib.redirect_stderr(io.StringIO()),patch.object(a,'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code,2);inspect.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base=Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR',str(default)))
        paths=[base/f'db.{n}.gbf' for n in (3,4)]
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('local archives unavailable')
        cls.results=[];cls.databases=[];cls.ticks=[]
        for path in paths:
            a.c.require(32<=path.stat().st_size<=a.c.MAX_FILE,'snapshot size bounds')
            with path.open('rb') as stream: data=stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data)<=a.c.MAX_FILE,'snapshot size bounds')
            digest=hashlib.sha256(data).hexdigest()
            cls.results.append(a.inspect(data,digest))
            cls.ticks.append(tick.inspect(data,digest))
            cls.databases.append(a.c.GBF(data))

    def test_every_instruction_and_operand_both_archives(self):
        self.assertEqual(sum(len(v) for v in EXPECTED.values()),175)
        for result in self.results:
            for selected,coverage in zip(result['ranges'],result['function_coverage']):
                pc=int(selected['address'],16);items=EXPECTED[pc]
                expected=[dict(address=f'{pc+i*4:08x}',**item) for i,item in enumerate(items)]
                self.assertEqual(selected['instructions'],expected)
                self.assertEqual(coverage,dict(entry=f'{pc:08x}',end_exclusive=f'{pc+len(items)*4:08x}',
                                 selected_width=len(items)*4,represented_instructions=len(items),
                                 unrepresented_instructions=0,unrepresented_ranges=[]))
                self.assertEqual(selected['instructions'][-1]['mnemonic'],'blr')
        self.assertEqual(self.results[0]['ranges'],self.results[1]['ranges'])
        self.assertEqual(self.results[0]['data_ranges'],self.results[1]['data_ranges'])

    def test_each_instruction_mutation_fails_before_decode_both_archives(self):
        for db in self.databases:
            for pc,size,_ in a.RANGES:
                raw,_=db.chain(21,pc-a.TEXT_START,size,a.TEXT_LENGTH)
                for offset in range(0,size,4):
                    changed=bytearray(raw);changed[offset+3]^=1
                    with patch.object(a,'decode_selected') as decoder:
                        with self.assertRaisesRegex(a.c.FormatError,'digest'):
                            a.range_evidence(FakeDB(bytes(changed)),21,pc,size)
                        decoder.assert_not_called()

    def test_each_data_byte_mutation_rejected_both_archives(self):
        for db in self.databases:
            for pc,size,_ in a.DATA_RANGES:
                mapping=a.DATA5_MAPPING if pc==0x80436a20 else a.DATA3_MAPPING
                raw,_=db.chain(mapping[6],pc-mapping[0],size,mapping[5])
                for offset in range(size):
                    changed=bytearray(raw);changed[offset]^=1
                    fixture=DataDB(bytes(changed)) if pc==0x8031b454 else FakeDB(bytes(changed))
                    with self.assertRaisesRegex(a.c.FormatError,'digest'):
                        a.data_evidence(fixture,mapping,pc,size)

    def test_fixed_data_values_and_physical_spans(self):
        result=self.results[0]
        self.assertEqual([[f['value'] for f in r['fields']] for r in result['data_ranges']],
                         [[0.0],['802c36b0','802c36e0'],['8031b454'],[126]])
        self.assertEqual([[f['type'] for f in r['fields']] for r in result['data_ranges']],
                         [['f32'],['pointer32','pointer32'],['pointer32'],['s16']])
        self.assertEqual([f['table_index'] for f in result['data_ranges'][1]['fields']],[19,20])
        self.assertEqual(result['data_ranges'][2]['fields'][0]['table_index'],1)
        self.assertEqual(result['r2_basis']['displacements'],{'80436a20':-32768})
        spans=[(21,43,347056,3118,724020,264),(21,47,415164,5714,792152,28),
               (21,47,415192,5742,792180,28),(21,22,3052,3052,379890,36),
               (21,22,3088,3088,379926,72),(21,80,961316,11392,1338502,272),
               (263,264,0,0,4341766,4),(199,202,35164,2408,3328366,8),
               (199,224,395320,2248,3688654,4),(199,224,394740,1668,3688074,2)]
        for r,values in zip(result['ranges']+result['data_ranges'],spans):
            root,buffer,chain,offset,physical,length=values
            self.assertEqual(r['spans'],[dict(root_buffer=root,data_buffer=buffer,chain_offset=chain,
                             data_offset=offset,physical_offset=physical,length=length,obfuscated=True)])

    def test_source_order_and_calls_are_not_c_summaries(self):
        bypc={i['address']:i for r in self.results[0]['ranges'] for i in r['instructions']}
        self.assertEqual([(pc,bypc[pc]['displacement']) for pc in ('8005a1a4','8005a1b0','8005a1bc')],
                         [('8005a1a4',0x4a1),('8005a1b0',0x4a0),('8005a1bc',0x6fc)])
        self.assertEqual(bypc['8005a240']['mnemonic'],'extsh')
        self.assertEqual(bypc['8005a244']['mnemonic'],'sth')
        self.assertEqual([(i['address'],i['target']) for i in self.results[0]['ranges'][0]['instructions']
                          if i['mnemonic']=='bl'],
                         [('8005a1f4','8006ab9c'),('8005a204','8006aab0'),('8005a218','80176ec0'),
                          ('8005a24c','8006abb8'),('8005a25c','8006a980')])
        self.assertEqual([(pc,bypc[pc]['displacement']) for pc in
                          ('800061fc','8000621c','80006220','80006224','80006228','8000622c','80006230')],
                         [('800061fc',0x7df),('8000621c',0x7ec),('80006220',0x7e4),('80006224',0x7f7),
                          ('80006228',0x7f4),('8000622c',0x7f5),('80006230',0x7f6)])
        self.assertEqual(bypc['800f01b0']['mnemonic'],'lhz')
        self.assertEqual(bypc['800f01c8'],dict(address='800f01c8',mnemonic='b',target='800f01ec',AA=0))
        self.assertEqual(bypc['800f016c']['mnemonic'],'lha')
        self.assertEqual(bypc['800f0170']['mnemonic'],'lwzx')
        self.assertEqual(bypc['800f0174']['mnemonic'],'lha')
        self.assertEqual(bypc['800f018c']['target'],'800f01ec')
        self.assertEqual(bypc['800f01ec'],dict(address='800f01ec',mnemonic='stw',rS=30,rA=29,displacement=12))
        self.assertEqual(bypc['800f01f4'],dict(address='800f01f4',mnemonic='stw',rS=0,rA=29,displacement=4))
        self.assertEqual([(i['address'],i['target']) for i in self.results[0]['ranges'][5]['instructions']
                          if i['mnemonic']=='bl'],
                         [('800f0180','800f02d0'),('800f01a4','80207058'),
                          ('800f01d4','800f036c'),('800f01e8','800f061c')])

    def test_existing_tick_continuation_is_conditional(self):
        for result in self.ticks:
            bypc={i['address']:i for i in result['ranges'][0]['instructions']}
            self.assertEqual(bypc['800590bc']['target'],'8005a190')
            self.assertEqual(bypc['800590c4'],dict(address='800590c4',mnemonic='bc',BO=4,BI=2,LK=0,
                             target='8005910c',AA=0))
            self.assertEqual(bypc['800590c8']['displacement'],0x5e4)
            self.assertEqual(bypc['800590d8']['mnemonic'],'extsb')
            self.assertEqual(bypc['800590e0'],dict(address='800590e0',mnemonic='lwzx',rD=12,rA=4,rB=0))
            self.assertEqual(bypc['800590e8'],dict(address='800590e8',mnemonic='bctrl',BO=20,BI=0,BH=0,LK=1))
            self.assertEqual(bypc['80059110']['target'],'8005a298')

    def test_no_raw_output_and_metadata(self):
        for result in self.results:
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            self.assertEqual(len(result['ranges']),6);self.assertEqual(len(result['data_ranges']),4)
            def no_raw(value):
                if isinstance(value,dict):
                    self.assertTrue(set(value).isdisjoint(('raw','word','words','hex','bytes','bits')))
                    for child in value.values(): no_raw(child)
                elif isinstance(value,list):
                    for child in value:no_raw(child)
            no_raw(result)


if __name__=='__main__': unittest.main()
