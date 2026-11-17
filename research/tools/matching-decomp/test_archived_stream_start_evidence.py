"""Synthetic-only stream-start evidence tests; no archived payload fixtures."""
import hashlib
import unittest
from unittest.mock import patch
import read_archived_constants as c
import read_archived_stream_start_evidence as m
from test_archived_constants import gbf, pack


class StreamStartEvidenceTests(unittest.TestCase):
    def mapping(self):
        return ({1:['MAIN_.text1',None,None,0,0x20000000000055e0,m.TEXT_LENGTH,0]},
                {1:[1,2,m.TEXT_LENGTH,0,21,0]})

    def test_exact_mapping_and_guards(self):
        blocks, subs = self.mapping()
        self.assertEqual(m.text_mapping(blocks,subs,0x80000000),21)
        for index, value in [(0,'other'),(4,0x10000000800055e0),(5,m.TEXT_LENGTH-1),(6,1)]:
            changed = blocks[1].copy()
            changed[index] = value
            with self.subTest(block=index),self.assertRaises(c.FormatError):
                m.text_mapping({1:changed},subs,0x80000000)
        for index, value in [(0,2),(1,1),(2,m.TEXT_LENGTH-1),(3,1),(4,22),(5,1)]:
            changed = subs[1].copy()
            changed[index] = value
            with self.subTest(sub=index),self.assertRaises(c.FormatError):
                m.text_mapping(blocks,{1:changed},0x80000000)
        for b,s in [({},subs),(blocks,{}),({1:blocks[1],2:blocks[1]},subs),
                    (blocks,{1:subs[1],2:subs[1]}),({2:blocks[1]},subs)]:
            with self.assertRaises(c.FormatError):
                m.text_mapping(b,s,0x80000000)
        with self.assertRaises(c.FormatError):
            m.text_mapping(blocks,subs,0)

    def test_range_guards_and_no_raw_output(self):
        # Use fabricated words, not bytes read from an archived range.
        address=m.TEXT_START
        word=(14<<26)|(9<<21)|42
        payload=pack('I',word)
        class DB:
            def chain(self,*args):
                self.args=args
                return payload,[]
        db=DB()
        with self.assertRaises(c.FormatError): m.range_evidence(db,21,address,4)
        with patch.object(m,'RANGES',((address,4,hashlib.sha256(payload).hexdigest()),)), \
             patch.object(m,'WORDS',{address:word}):
            result=m.range_evidence(db,21,address,4)
            self.assertEqual(db.args,(21,0,4,m.TEXT_LENGTH))
            self.assertEqual(set(result),{'address','width','sha256','spans','instructions'})
            self.assertEqual(result['instructions'][0]['immediate'],42)
            with patch.object(m,'WORDS',{address:word+1}):
                with self.assertRaisesRegex(c.FormatError,'word mismatch'):
                    m.range_evidence(db,21,address,4)
            with patch.object(m,'RANGES',((address,4,'0'*64),)):
                with self.assertRaisesRegex(c.FormatError,'digest mismatch'):
                    m.range_evidence(db,21,address,4)
        class ShortDB:
            def chain(self,*args): return b'',[]
        with self.assertRaisesRegex(c.FormatError,'byte width'):
            m.range_evidence(ShortDB(),21,m.RANGES[0][0],m.RANGES[0][1])
        for a,w in ((address+1,4),(address,3),(address-4,4),(address+m.TEXT_LENGTH,4)):
            with patch.object(m,'RANGES',((a,w,'unused'),)):
                with self.assertRaisesRegex(c.FormatError,'alignment/bounds'):
                    m.range_evidence(db,21,a,w)

    def test_authentication_not_bypassed(self):
        data=gbf([b''])
        for digest in (hashlib.sha256(data).hexdigest(),next(iter(c.SNAPSHOTS))):
            with self.assertRaisesRegex(c.FormatError,'not allowlisted'):
                m.inspect(data,digest)

    def test_shared_schema_validation_failure_propagates(self):
        with patch.object(c,'inspect',side_effect=c.FormatError('unsupported schema: Program')), \
             patch.object(c,'GBF') as parser:
            with self.assertRaisesRegex(c.FormatError,'unsupported schema'):
                m.inspect(b'synthetic','synthetic')
            parser.assert_not_called()

    def test_four_mib_chain_guard(self):
        self.assertEqual(c.MAX_CHAIN,4*1024*1024)
        # A synthetic indexed chain declares the largest size. It passes size
        # validation but fails index capacity, before any missing child read.
        db=c.GBF(gbf([pack('BIi',8,c.MAX_CHAIN,-1)]))
        with self.assertRaisesRegex(c.FormatError,'index capacity'):
            db.chain(0,0,4,c.MAX_CHAIN)
        db=c.GBF(gbf([pack('BIi',8,c.MAX_CHAIN+1,-1)]))
        with self.assertRaisesRegex(c.FormatError,'chain size'):
            db.chain(0,0,4,c.MAX_CHAIN+1)


    def test_d_forms_and_signed_displacement(self):
        for op,name,field in ((34,'lbz','rD'),(36,'stw','rS'),(38,'stb','rS'),
                              (48,'lfs','fD'),(52,'stfs','fS')):
            for value in (-32768,-1,0,32767):
                word=(op<<26)|(7<<21)|(3<<16)|(value&0xffff)
                self.assertEqual(m.decode_word(word),dict(mnemonic=name,**{field:7},
                                                         rA=3,displacement=value))

    def test_integer_forms_and_reserved_bits(self):
        for xo,name,fields in ((28,'and',dict(rA=3,rS=7,rB=9)),
                              (343,'lhax',dict(rD=7,rA=3,rB=9)),
                              (266,'add',dict(rD=7,rA=3,rB=9))):
            word=(31<<26)|(7<<21)|(3<<16)|(9<<11)|(xo<<1)
            self.assertEqual(m.decode_word(word),dict(mnemonic=name,**fields))
            with self.assertRaises(c.FormatError): m.decode_word(word|1)
        word=(31<<26)|(7<<21)|(3<<16)|(954<<1)
        self.assertEqual(m.decode_word(word),dict(mnemonic='extsb',rA=3,rS=7))
        with self.assertRaises(c.FormatError): m.decode_word(word|(1<<11))
        self.assertEqual(m.decode_word((14<<26)|(5<<21)|0xffff),
                         dict(mnemonic='li',rD=5,immediate=-1))
        for word in (-1,1<<32,True,0,(14<<26)|(1<<16)):
            with self.assertRaises(c.FormatError): m.decode_word(word)
        # OE is not accepted by the selected add form.
        with self.assertRaises(c.FormatError):
            m.decode_word((31<<26)|(266<<1)|(1<<10))

    def test_rotation_fields(self):
        for shift,mb,me in ((0,0,31),(1,24,30),(1,0,30),(31,31,0)):
            word=(21<<26)|(28<<21)|(5<<16)|(shift<<11)|(mb<<6)|(me<<1)
            self.assertEqual(m.decode_word(word),dict(mnemonic='rlwinm',rA=5,rS=28,
                                                     shift=shift,mask_begin=mb,mask_end=me))
            with self.assertRaises(c.FormatError): m.decode_word(word|1)

    def test_fixed_facts_and_reset_order(self):
        facts={pc:m.decode_word(word) for pc,word in m.WORDS.items()}
        self.assertEqual(facts[0x8004bee4],dict(mnemonic='lbz',rD=0,rA=3,displacement=0x579))
        self.assertEqual(facts[0x8004bf90]['displacement'],0x582)
        self.assertEqual(facts[0x8004bf40],dict(mnemonic='rlwinm',rA=0,rS=28,
                                             shift=1,mask_begin=24,mask_end=30))
        for pc in (0x8004bf9c,0x8004bfa8):
            self.assertEqual((facts[pc]['shift'],facts[pc]['mask_begin'],facts[pc]['mask_end']),
                             (1,0,30))
        for pc in (0x8004bf44,0x8004bfa0,0x8004bfb0):
            self.assertEqual(facts[pc],dict(mnemonic='lhax',rD=0,rA=3,rB=0))
        self.assertEqual(facts[0x8004bfbc],dict(mnemonic='add',rD=22,rA=3,rB=0))
        stores=[f for pc,f in facts.items() if pc>=0x8004c020 and f['mnemonic'] in ('stfs','stw','stb')]
        self.assertEqual([f['displacement'] for f in stores],[12,16,8,29,30,4,0,20,26])
        self.assertTrue(all(f['rA']==3 and f.get('rS',f.get('fS'))==0 for f in stores))
        self.assertEqual(facts[0x8004c024],dict(mnemonic='li',rD=0,immediate=0))
        self.assertEqual(facts[0x8004c020],dict(mnemonic='lfs',fD=0,rA=2,displacement=-31020))

    def test_no_constant_or_control_expansion(self):
        self.assertEqual(len(c.TARGETS),12)
        self.assertIn((0x804370f4,4),c.TARGETS)
        self.assertNotIn(0x804370f4,c.CONTROLS)
        self.assertNotIn(0x804370f4,c.EXPECTED_TARGETS)


if __name__ == '__main__':
    unittest.main()
