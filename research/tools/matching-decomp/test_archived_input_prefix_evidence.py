#!/usr/bin/env python3
"""Fixed input-prefix operands, authentication and fail-closed controls."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_input_prefix_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def ops(text):
    """Independent expected operand notation, not an instruction decoder."""
    fields = {
        'stwu': 'rS rA displacement', 'stw': 'rS rA displacement',
        'stb': 'rS rA displacement', 'sth': 'rS rA displacement',
        'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement',
        'lhz': 'rD rA displacement', 'lbzx': 'rD rA rB',
        'addi': 'rD rA immediate', 'addis': 'rD rA immediate',
        'ori': 'rS rA immediate', 'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS',
        'rlwinm': 'rS rA SH MB ME Rc', 'extsb': 'rS rA Rc',
        'srawi': 'rS rA SH', 'or': 'rS rA rB', 'and': 'rS rA rB',
        'mullw': 'rD rA rB', 'add': 'rD rA rB',
        'cmpl': 'BF L rA rB', 'cmpli': 'BF L rA immediate',
        'psq_l': 'fD rA displacement W I', 'blr': '',
        'bc': 'BO BI target', 'bl': 'target', 'b': 'target',
    }
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = fields[name].split()
        assert len(keys) == len(values), line
        item = dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                    for key, value in zip(keys, values)})
        if name in ('srawi', 'or', 'and', 'mullw', 'add'):
            item['Rc'] = 0
        if name in ('bc', 'bl', 'b'):
            item['AA'] = 0
        if name == 'bc':
            item['LK'] = 0
        result.append(item)
    return result


class SyntheticTests(unittest.TestCase):
    def test_extent_and_decoder_forms(self):
        self.assertEqual([(pc,n) for pc,n,_ in a.RANGES],[(0x800685c0,304),(0x80068980,524),(0x8006de44,164),(0x8008b73c,116)])
        for word in (-1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,0)
        for pc in (-1,1,1<<32,True,1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0,pc)
        for word in (0,d_form(42,3,4,0),0x4e800421,d_form(48,3,4,0),(31<<26)|(747<<1)):
            self.assertIsNone(a.decode_selected(word,0))
        for word in ((31<<26)|(87<<1)|1,(31<<26)|(954<<1)|(1<<11),(31<<26)|(32<<1)|1,(31<<26)|(32<<1)|(1<<21)):
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
        for option in (['--address','800685c0'],['--width','304'],['--raw'],['--execute']):
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
        self.assertEqual(sorted(self.facts),[pc for start,width,_ in a.RANGES for pc in range(start,start+width,4)])
        for result in self.results:
            self.assertEqual(result['constants'],[])
            self.assertEqual(result['file_bytes_table'],dict(version=0,root=-1,count=0))
            for coverage, (_,width,_) in zip(result['function_coverage'],a.RANGES):
                self.assertEqual(coverage['represented_instructions'],width//4)
                self.assertEqual(coverage['unrepresented_instructions'],0)
            for span in result['ranges']:
                for item in [span]+span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw','word','words','hex','bytes')))

    def assert_sequence(self, entry, expected):
        width = next(width for pc, width, _ in a.RANGES if pc == entry)
        self.assertEqual(len(expected), width // 4)
        self.assertEqual([self.facts[entry + i * 4] for i in range(len(expected))],
                         [dict(address=f'{entry + i * 4:08x}', **op) for i, op in enumerate(expected)])

    def test_every_caller_operand_in_exact_order(self):
        expected = ops("""
            stwu 1 1 -16
            mflr 0
            stw 0 1 20
            stw 31 1 12
            or 3 31 3
            addi 4 31 0x5fc
            bl 80068980
            addi 0 0 0
            addis 3 0 -32723
            stw 0 31 0x5d4
            addi 4 3 0x38f8
            or 31 3 31
            addi 5 31 0x614
            addi 6 0 0x20
            bl 80068b8c
        """)
        for table, field, mask in ((0x3904,0x618,0x40),(0x3910,0x61c,0x80),
                                   (0x391c,0x624,0x200),(0x3928,0x600,1),
                                   (0x3934,0x604,2),(0x3940,0x608,4),
                                   (0x394c,0x60c,8),(0x3958,0x610,0x10),
                                   (0x3964,0x628,0x2000)):
            expected += ops(f"""
                addis 4 0 -32723
                or 31 3 31
                addi 4 4 {table}
                addi 5 31 {field}
                addi 6 0 {mask}
                bl 80068b8c
            """)
        expected += ops("""
            or 31 3 31
            bl 800686f0
            lwz 0 1 20
            lwz 31 1 12
            mtlr 0
            addi 1 1 16
            blr
        """)
        self.assert_sequence(0x800685c0, expected)

    def test_every_input_operand_in_exact_order(self):
        self.assert_sequence(0x80068980, ops("""
            stwu 1 1 -16
            mflr 0
            stw 0 1 20
            stw 31 1 12
            or 4 31 4
            stw 30 1 8
            or 3 30 3
            lbz 0 4 0
            rlwinm 0 0 0 31 31 1
            bc 4 2 80068a04
            lbz 3 30 0x5ca
            addi 5 0 20
            lbz 4 30 0x5cb
            bl 8008b73c
            rlwinm 3 3 0 24 31 1
            bc 12 2 80068a04
            lbz 0 31 0
            ori 0 0 1
            stb 0 31 0
            lhz 0 30 0x5d8
            rlwinm 0 0 0 16 27 0
            sth 0 30 0x5d8
            lhz 0 30 0x5d8
            or 0 0 3
            sth 0 30 0x5d8
            lhz 0 30 0x5d8
            rlwinm 0 0 0 28 29 1
            bc 12 2 800689fc
            addi 0 0 3
            stb 0 31 1
            b 80068a04
            addi 0 0 2
            stb 0 31 1
            lbz 0 31 0
            rlwinm 0 0 0 30 30 1
            bc 4 2 80068a5c
            lbz 3 30 0x5ca
            addi 5 0 52
            lbz 4 30 0x5cb
            bl 8008b73c
            rlwinm 3 5 0 24 31 1
            bc 12 2 80068a5c
            lbz 3 31 0
            addi 0 0 20
            ori 3 3 2
            stb 3 31 0
            lhz 3 30 0x5d8
            rlwinm 3 3 0 28 23 0
            sth 3 30 0x5d8
            lhz 4 30 0x5d8
            and 4 3 5
            rlwinm 3 3 4 0 27 0
            or 4 3 3
            sth 3 30 0x5d8
            stb 0 31 1
            lbz 3 31 0
            rlwinm 3 0 0 28 28 1
            bc 4 2 80068aac
            lwz 0 30 0x5b4
            rlwinm 0 4 0 12 15 1
            bc 12 2 80068ae8
            ori 3 0 8
            rlwinm 4 3 24 8 31 0
            stb 0 31 0
            addi 0 0 20
            lhz 4 30 0x5d8
            rlwinm 4 4 0 24 19 0
            sth 4 30 0x5d8
            lhz 5 30 0x5d8
            srawi 5 4 4
            and 4 3 3
            or 5 3 3
            sth 3 30 0x5d8
            stb 0 31 3
            b 80068ae8
            lwz 0 30 0x5b4
            rlwinm 0 0 0 12 15 1
            bc 4 2 80068ae8
            addi 3 0 0
            addi 0 0 16
            stb 3 31 0
            lhz 3 30 0x5d8
            rlwinm 3 3 0 20 31 0
            sth 3 30 0x5d8
            lhz 3 30 0x5b8
            lhz 4 30 0x5d8
            rlwinm 3 3 12 16 19 0
            or 4 3 3
            sth 3 30 0x5d8
            stb 0 31 2
            lbz 3 31 1
            extsb 3 0 1
            bc 12 2 80068b10
            addi 3 3 -1
            extsb 3 0 1
            stb 3 31 1
            bc 12 1 80068b10
            lhz 0 30 0x5d8
            rlwinm 0 0 0 16 23 0
            sth 0 30 0x5d8
            lbz 3 31 3
            extsb 3 0 1
            bc 12 2 80068b38
            addi 3 3 -1
            extsb 3 0 1
            stb 3 31 3
            bc 12 1 80068b38
            lhz 0 30 0x5d8
            rlwinm 0 0 0 24 19 0
            sth 0 30 0x5d8
            lbz 3 31 2
            cmpli 0 0 3 0
            bc 12 2 80068b60
            addi 3 3 -1
            rlwinm 3 0 0 24 31 1
            stb 3 31 2
            bc 4 2 80068b60
            lhz 0 30 0x5d8
            rlwinm 0 0 0 20 31 0
            sth 0 30 0x5d8
            addis 4 0 15
            or 30 3 30
            addi 4 4 0x0f00
            bl 8006de44
            stb 3 30 0x749
            lwz 0 1 20
            lwz 31 1 12
            lwz 30 1 8
            mtlr 0
            addi 1 1 16
            blr
        """))

    def test_every_popcount_operand_in_exact_order(self):
        expected = ops("""
            lwz 5 3 0x5bc
            addi 0 0 4
            addi 3 0 0
            addi 6 0 0
            and 5 4 4
            mtctr 0
        """)
        for i in range(8):
            expected += ops(f"""
                rlwinm 4 0 0 31 31 1
                bc 12 2 {0x8006de68 + 16*i:08x}
                addi 3 3 1
                srawi 4 4 1
            """)
        expected += ops("""
            addi 6 6 7
            bc 16 0 8006de5c
            blr
        """)
        self.assert_sequence(0x8006de44, expected)

    def test_every_direction_operand_in_exact_order(self):
        self.assert_sequence(0x8008b73c, ops("""
            stwu 1 1 -16
            mflr 0
            rlwinm 3 6 0 24 31 0
            stw 0 1 20
            rlwinm 4 0 0 24 31 0
            extsb 6 6 0
            extsb 0 0 0
            stb 3 1 8
            mullw 3 0 0
            stb 4 1 9
            mullw 6 6 6
            mullw 0 5 5
            add 3 6 3
            cmpl 0 0 3 0
            bc 12 0 8008b79c
            psq_l 2 1 8 1 4
            psq_l 1 1 9 1 4
            bl 800452a0
            rlwinm 3 4 0 16 31 0
            addi 3 13 -31864
            addi 0 4 4096
            rlwinm 0 0 19 29 31 0
            lbzx 3 3 0
            b 8008b7a0
            addi 3 0 0
            lwz 0 1 20
            mtlr 0
            addi 1 1 16
            blr
        """))

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
