#!/usr/bin/env python3
"""Fixed stage-bounds operands, authentication and fail-closed controls."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_stage_bounds_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


class SyntheticTests(unittest.TestCase):
    def test_extent_and_decoder_forms(self):
        self.assertEqual([(pc, n) for pc, n, _ in a.RANGES], [(0x80059e58, 260)])
        for op, name in ((24, 'ori'), (29, 'andis.')):
            self.assertEqual(a.decode_selected(d_form(op, 3, 4, 65535), 0),
                             dict(mnemonic=name, rS=3, rA=4, immediate=65535))
        self.assertEqual(a.decode_selected(d_form(42, 3, 4, -1), 0),
                         dict(mnemonic='lha', rD=3, rA=4, displacement=-1))
        self.assertEqual(a.decode_selected(d_form(44, 3, 4, -1), 0),
                         dict(mnemonic='sth', rS=3, rA=4, displacement=-1))
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)
        for word in (0, d_form(40, 3, 4, 0), 0x4e800421, (59 << 26) | (18 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        for word in (spr_form(467, 12, 9), spr_form(339, 1, 8), spr_form(467, 0, 8, 1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for word in ((63 << 26) | (32 << 1) | 1,
                     (63 << 26) | (1 << 21) | (32 << 1),
                     (31 << 26) | (954 << 1) | (1 << 11)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)

    def test_fixed_reads_reject_before_decode(self):
        pc, size, _ = a.RANGES[0]
        for address, width in ((pc+4,size-4),(pc,size-4),(pc,size+4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
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
        for option in (['--address','80059e58'],['--width','260'],['--raw'],['--execute']):
            with patch.object(a.sys,'argv',['reader','fixture.gbf']+option),contextlib.redirect_stderr(io.StringIO()),patch.object(a,'inspect') as inspect:
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code,2); inspect.assert_not_called()

    def test_mapping_guards_precede_fixed_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image', 'data5'):
            aa, bb, ss = copy.deepcopy((auth, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'data5': ss[7][4] += 1
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base=Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR',str(default)))
        paths=[base/f'db.{n}.gbf' for n in (3,4)]
        if not all(p.is_file() for p in paths): raise unittest.SkipTest('both existing local archived snapshots required')
        cls.results=[]
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE,'snapshot size bounds')
            with path.open('rb') as stream: data=stream.read(a.c.MAX_FILE+1)
            a.c.require(len(data)<=a.c.MAX_FILE,'snapshot size bounds')
            cls.results.append(a.inspect(data,hashlib.sha256(data).hexdigest()))
            cls.raw=a.c.GBF(data).chain(21,0x80059e58-a.TEXT_START,260,a.TEXT_LENGTH)[0]
        cls.facts={int(f['address'],16):f for f in cls.results[0]['ranges'][0]['instructions']}

    def f(self,pc,name,**fields):
        self.assertEqual(self.facts[pc],dict(address=f'{pc:08x}',mnemonic=name,**fields))

    def test_full_coverage_both_archives(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results},set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'],self.results[1]['ranges'])
        self.assertEqual(sorted(self.facts),list(range(0x80059e58,0x80059f5c,4)))
        span=self.results[0]['ranges'][0]
        self.assertEqual(span['spans'],[dict(root_buffer=21,data_buffer=43,chain_offset=346232,data_offset=2294,length=260,obfuscated=True,physical_offset=723196)])
        for result in self.results:
            self.assertEqual(result['constants'],[])
            self.assertEqual(result['function_coverage'],[dict(entry='80059e58',end_exclusive='80059f5c',selected_width=260,represented_instructions=65,unrepresented_instructions=0,unrepresented_ranges=[])])
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
        for item in [span]+span['instructions']:
            self.assertTrue(set(item).isdisjoint(('raw','word','words','hex','bytes')))

    def test_gate_order_and_bounds_operands(self):
        for pc,offset,base in ((0x80059e6c,0x4a1,3),(0x80059e78,0x18,31),(0x80059e84,0x6cb,31)):
            self.f(pc,'lbz',rD=0,rA=base,displacement=offset)
        for pc in (0x80059e70,0x80059e88): self.f(pc,'extsb',rS=0,rA=0,Rc=1)
        self.f(0x80059e7c,'cmpi',BF=0,L=0,rA=0,immediate=1)
        for pc in (0x80059e74,0x80059e80,0x80059e8c): self.f(pc,'bc',BO=4,BI=2,LK=0,target='80059f48',AA=0)
        self.f(0x80059e90,'lwz',rD=3,rA=13,displacement=-21316)
        for pc,offset,reg,base in ((0x80059e94,0x20,1,31),(0x80059e98,0x3c,0,3),(0x80059ea4,0x38,0,3),(0x80059eb0,0x28,1,31),(0x80059eb4,0x44,0,3),(0x80059ec0,0x40,0,3)):
            self.f(pc,'lfs',fD=reg,rA=base,displacement=offset)
        for pc in (0x80059e9c,0x80059ea8,0x80059eb8,0x80059ec4): self.f(pc,'fcmpo',crD=0,fA=1,fB=0)
        for pc,bo,bi,target in ((0x80059ea0,12,0,'80059ecc'),(0x80059eac,12,1,'80059ecc'),(0x80059ebc,12,0,'80059ecc'),(0x80059ec8,4,1,'80059f40')):
            self.f(pc,'bc',BO=bo,BI=bi,LK=0,target=target,AA=0)

    def test_counter_reload_threshold_masks_and_cues(self):
        for pc,reg in ((0x80059ecc,3),(0x80059ed8,0)): self.f(pc,'lha',rD=reg,rA=31,displacement=0x6cc)
        self.f(0x80059ed0,'addi',rD=0,rA=3,immediate=1)
        for pc in (0x80059ed4,0x80059ef4,0x80059f44): self.f(pc,'sth',rS=0,rA=31,displacement=0x6cc)
        self.f(0x80059edc,'cmpi',BF=0,L=0,rA=0,immediate=30)
        self.f(0x80059ee0,'bc',BO=4,BI=0,LK=0,target='80059ef0',AA=0)
        self.f(0x80059ee8,'rlwinm',rS=0,rA=0,SH=0,MB=6,ME=6,Rc=1)
        self.f(0x80059eec,'bc',BO=12,BI=2,LK=0,target='80059f48',AA=0)
        for pc in (0x80059ee4,0x80059ef8): self.f(pc,'lwz',rD=0,rA=31,displacement=0x5e0)
        self.f(0x80059efc,'andis.',rS=0,rA=0,immediate=0x500)
        for pc,imm in ((0x80059ef0,0),(0x80059f04,1),(0x80059f10,2),(0x80059f40,0)): self.f(pc,'addi',rD=0,rA=0,immediate=imm)
        for pc in (0x80059f08,0x80059f14): self.f(pc,'stb',rS=0,rA=31,displacement=0x6cb)
        self.f(0x80059f18,'lha',rD=0,rA=31,displacement=0x272)
        self.f(0x80059f1c,'ori',rS=0,rA=0,immediate=0x43)
        self.f(0x80059f20,'sth',rS=0,rA=31,displacement=0x272)
        for pc in (0x80059f28,0x80059f34): self.f(pc,'addi',rD=4,rA=0,immediate=9)
        self.assertEqual([(f['address'],f['target']) for f in self.facts.values() if f['mnemonic']=='bl'], [('80059f2c','8006a750'),('80059f38','8006a6fc')])

    def test_prologue_epilogue_and_remaining_control_flow(self):
        self.f(0x80059e58,'stwu',rS=1,rA=1,displacement=-16)
        self.f(0x80059e5c,'mflr',rD=0)
        self.f(0x80059e60,'stw',rS=0,rA=1,displacement=20)
        self.f(0x80059e64,'stw',rS=31,rA=1,displacement=12)
        self.f(0x80059e68,'or',rS=3,rA=31,rB=3,Rc=0)
        self.f(0x80059f00,'bc',BO=4,BI=2,LK=0,target='80059f10',AA=0)
        self.f(0x80059f0c,'b',target='80059f24',AA=0)
        for pc in (0x80059f24,0x80059f30): self.f(pc,'or',rS=31,rA=3,rB=31,Rc=0)
        self.f(0x80059f3c,'b',target='80059f48',AA=0)
        self.f(0x80059f48,'lwz',rD=0,rA=1,displacement=20)
        self.f(0x80059f4c,'lwz',rD=31,rA=1,displacement=12)
        self.f(0x80059f50,'mtlr',rS=0)
        self.f(0x80059f54,'addi',rD=1,rA=1,immediate=16)
        self.f(0x80059f58,'blr')
        epilogue=[self.facts[pc] for pc in range(0x80059f48,0x80059f5c,4)]
        self.assertFalse(any(f['mnemonic'] in ('bl','stb','sth','stw') for f in epilogue))
        self.assertEqual([f.get('rA') for f in epilogue if f['mnemonic']=='lwz'],[1,1])
        self.assertEqual([self.facts[pc]['target'] for pc in (0x80059e74,0x80059e80,0x80059e8c)],['80059f48']*3)

    def test_each_instruction_mutation_rejected_before_decode(self):
        for offset in range(0,260,4):
            changed=bytearray(self.raw); changed[offset+3]^=1
            with patch.object(a,'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'): a.range_evidence(FakeDB(changed),21,0x80059e58,260)
                decoder.assert_not_called()


if __name__=='__main__': unittest.main()
