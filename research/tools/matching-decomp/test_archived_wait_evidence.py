"""Synthetic-only tests; no archived payload fixtures or external dependencies."""
import hashlib
import unittest
from unittest.mock import patch
import read_archived_constants as c
import read_archived_wait_evidence as m
from test_archived_constants import gbf, pack


class WaitEvidenceTests(unittest.TestCase):
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

    def test_synthetic_psq_fields_and_signed_displacement(self):
        for d in (0,1,2,31):
            for a in (0,27,31):
                for displacement in (-2048,-1,0,36,2047):
                    for w,i in ((0,0),(1,5),(0,7)):
                        word = (56<<26)|(d<<21)|(a<<16)|(w<<15)|(i<<12)|(displacement&0xfff)
                        self.assertEqual(m.decode_word(word),dict(mnemonic='psq_l',fD=d,rA=a,
                                             displacement=displacement,W=w,I=i))

    def test_synthetic_float_fields_and_reserved_bits(self):
        for xo,name in ((18,'fdivs'),(21,'fadds')):
            word=(59<<26)|(7<<21)|(3<<16)|(4<<11)|(xo<<1)
            self.assertEqual(m.decode_word(word),dict(mnemonic=name,fD=7,fA=3,fB=4))
            for bad in (word|1,word|(1<<6)):
                with self.assertRaises(c.FormatError): m.decode_word(bad)
        word=(59<<26)|(7<<21)|(3<<16)|(4<<6)|(25<<1)
        self.assertEqual(m.decode_word(word),dict(mnemonic='fmuls',fD=7,fA=3,fC=4))
        with self.assertRaises(c.FormatError): m.decode_word(word|(1<<11))

    def test_synthetic_startup_forms(self):
        self.assertEqual(m.decode_word((14<<26)|(5<<21)|0xffff),
                         dict(mnemonic='li',rD=5,immediate=-1))
        self.assertEqual(m.decode_word((25<<26)|(6<<21)|(5<<16)|13),
                         dict(mnemonic='oris',rA=5,rS=6,immediate=13))
        for spr in (0,31,32,917,1023):
            word=(31<<26)|(9<<21)|((spr&31)<<16)|((spr>>5)<<11)|(467<<1)
            self.assertEqual(m.decode_word(word),dict(mnemonic='mtspr',spr=spr,rS=9))
        for word in (-1,1<<32,0,(14<<26)|(1<<16)):
            with self.assertRaises(c.FormatError): m.decode_word(word)

    def test_fixed_word_facts(self):
        facts={pc:m.decode_word(word) for pc,word in m.WORDS.items()}
        self.assertEqual(facts[0x8004ce34],dict(mnemonic='psq_l',fD=1,rA=27,displacement=36,W=1,I=5))
        self.assertEqual(facts[0x8004ce68]['fD'],2)
        self.assertEqual([facts[pc]['mnemonic'] for pc in (0x8004ce38,0x8004ce74,0x8004ce7c)],
                         ['fadds','fdivs','fmuls'])
        self.assertEqual(facts[0x8002a414],dict(mnemonic='li',rD=3,immediate=7))
        self.assertEqual(facts[0x8002a418],dict(mnemonic='oris',rA=3,rS=3,immediate=7))
        self.assertEqual(facts[0x8002a41c],dict(mnemonic='mtspr',spr=917,rS=3))

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

    def test_added_constant_keeps_existing_targets(self):
        self.assertEqual(len(c.TARGETS),12)
        self.assertIn((0x80437148,4),c.TARGETS)
        self.assertEqual(c.EXPECTED_TARGETS[0x80437148],'42c80000')
        self.assertNotIn(0x80437148,c.CONTROLS)
        self.assertEqual(c.CONTROLS,{0x8043d1f8:'00000000',0x804374e4:'40000000',
                                     0x804374b0:'40a00000',0x80437464:'bf800000'})


if __name__ == '__main__':
    unittest.main()
