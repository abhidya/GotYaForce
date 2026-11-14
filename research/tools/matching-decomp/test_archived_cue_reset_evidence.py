#!/usr/bin/env python3
"""Fixed cue-reset operands, authentication and fail-closed controls."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_cue_reset_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


class SyntheticTests(unittest.TestCase):
    def test_extent_and_decoder_forms(self):
        self.assertEqual([(pc,n) for pc,n,_ in a.RANGES],[(0x8006a6fc,84),(0x8006a750,100)])
        for word in (-1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)
        for pc in (-1,1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0,pc)
        for word in (0,d_form(40,3,4,0),0x4e800421,d_form(48,3,4,0)):
            self.assertIsNone(a.decode_selected(word,0))
        for word in ((31<<26)|(87<<1)|1,(31<<26)|(954<<1)|(1<<11)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)

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
        for option in (['--address','8006a6fc'],['--width','84'],['--raw'],['--execute']):
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
        cls.facts={int(f['address'],16):f for span in cls.results[0]['ranges'] for f in span['instructions']}

    def test_full_coverage_both_archives(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results},set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'],self.results[1]['ranges'])
        self.assertEqual(sorted(self.facts),list(range(0x8006a6fc,0x8006a7b4,4)))
        for result in self.results:
            self.assertEqual(result['constants'],[])
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            for coverage, (_,width,_) in zip(result['function_coverage'],a.RANGES):
                self.assertEqual(coverage['represented_instructions'],width//4)
                self.assertEqual(coverage['unrepresented_instructions'],0)
            for span in result['ranges']:
                for item in [span]+span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw','word','words','hex','bytes')))

    def test_every_operand_in_exact_order(self):
        for entry,width,_ in a.RANGES:
            second=entry==0x8006a750
            def f(name,**kw): return dict(mnemonic=name,**kw)
            expected=[f('lwz',rD=5,rA=3,displacement=0x4f0),
                      f('rlwinm',rS=4,rA=0,SH=1,MB=0,ME=30,Rc=0)]
            if second:
                expected += [f('add',rD=5,rA=5,rB=0,Rc=0),f('lbz',rD=6,rA=5,displacement=1)]
            else:
                expected += [f('lbzx',rD=6,rA=5,rB=0)]
            expected += [f('extsb',rS=6,rA=0,Rc=0),f('cmpi',BF=0,L=0,rA=0,immediate=-1),
                         f('bc',BO=4,BI=2,LK=0,target='8006a774' if second else '8006a71c',AA=0),
                         f('addi',rD=3,rA=0,immediate=0),f('blr'),
                         f('lbz',rD=5,rA=3,displacement=0x5e4 if second else 0x5e5),
                         f('addi',rD=0,rA=0,immediate=0),
                         f('stb',rS=5,rA=3,displacement=0x7ce if second else 0x7cf),
                         f('stb',rS=4,rA=3,displacement=0x5e4 if second else 0x5e5),
                         f('lbz',rD=4,rA=3,displacement=0x5db if second else 0x5da),
                         f('stb',rS=4,rA=3,displacement=0x5dd if second else 0x5dc),
                         f('stb',rS=6,rA=3,displacement=0x5db if second else 0x5da)]
            expected += [f('stb',rS=0,rA=3,displacement=n) for n in
                         ((0x547,0x546,0x545,0x544,0x588) if second else (0x543,0x542,0x541,0x540))]
            if second:
                expected += [f('stw',rS=0,rA=3,displacement=0x754),f('stb',rS=0,rA=3,displacement=0x1db3)]
            expected += [f('addi',rD=3,rA=0,immediate=1),f('blr')]
            self.assertEqual(len(expected),width//4)
            self.assertEqual([self.facts[entry+i*4] for i in range(len(expected))],
                             [dict(address=f'{entry+i*4:08x}',**op) for i,op in enumerate(expected)])

    def test_each_instruction_mutation_rejected_before_decode(self):
        default=Path(__file__).resolve().parents[2]/'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base=Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR',str(default)))
        db=a.c.GBF((base/'db.3.gbf').read_bytes())
        for pc,width,_ in a.RANGES:
            raw=db.chain(21,pc-a.TEXT_START,width,a.TEXT_LENGTH)[0]
            for offset in range(0,width,4):
                changed=bytearray(raw); changed[offset+3]^=1
                with patch.object(a,'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'):
                        a.range_evidence(FakeDB(changed),21,pc,width)
                    decoder.assert_not_called()


if __name__=='__main__': unittest.main()
