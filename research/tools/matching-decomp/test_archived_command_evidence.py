"""Synthetic-only command evidence tests; no archived payload fixtures."""
import hashlib
import unittest
from unittest.mock import patch
import read_archived_constants as c
import read_archived_command_evidence as m
from test_archived_constants import gbf


class CommandEvidenceTests(unittest.TestCase):
    def mapping(self):
        return ({key: [name, None, None, 0, encoded, length, 0]
                 for name,key,encoded,length,root in m.MAPPINGS},
                {key: [key, 2, length, 0, root, 0]
                 for name,key,encoded,length,root in m.MAPPINGS})

    def test_mapping_guards(self):
        blocks, subs = self.mapping()
        m.mappings(blocks, subs, 0x80000000)
        for key in (1,5,7):
            for index,value in ((0,'other'),(4,0),(5,1),(6,1)):
                changed={k:r.copy() for k,r in blocks.items()}
                changed[key][index]=value
                with self.subTest(key=key,index=index),self.assertRaises(c.FormatError):
                    m.mappings(changed,subs,0x80000000)
            for index in range(6):
                changed={k:r.copy() for k,r in subs.items()}
                changed[key][index]+=1
                with self.subTest(key=key,subindex=index),self.assertRaises(c.FormatError):
                    m.mappings(blocks,changed,0x80000000)
            for b,s in (({k:r for k,r in blocks.items() if k!=key},subs),
                        (blocks,{k:r for k,r in subs.items() if k!=key}),
                        ({**blocks,99:blocks[key]},subs),
                        (blocks,{**subs,99:subs[key]})):
                with self.assertRaises(c.FormatError): m.mappings(b,s,0x80000000)
        with self.assertRaises(c.FormatError): m.mappings(blocks,subs,0)

    def test_allowlisted_range_guards(self):
        payload=b'\x12\x34\x56\x78'
        class DB:
            def chain(self,*args):
                self.args=args
                return payload,[]
        db=DB()
        address=m.TABLE_ADDRESS
        with self.assertRaisesRegex(c.FormatError,'not allowlisted'):
            m.read_range(db,address,4,0x80000000)
        with patch.object(m,'RANGES',((address,4,hashlib.sha256(payload).hexdigest(),1),)):
            raw,fact=m.read_range(db,address,4,0x80000000)
            self.assertEqual(raw,payload)
            self.assertEqual(db.args,(199,address-0x802bae60,4,0xf42c0))
            self.assertNotIn('bytes',fact)
            self.assertNotIn('raw',fact)
        with patch.object(m,'RANGES',((address,4,'0'*64,1),)):
            with self.assertRaisesRegex(c.FormatError,'digest mismatch'):
                m.read_range(db,address,4,0x80000000)
        for a,width in ((address+1,4),(address,3),(0x802bae5c,4),(0x803af120,4)):
            with patch.object(m,'RANGES',((a,width,'unused',1),)):
                with self.assertRaisesRegex(c.FormatError,'alignment/bounds'):
                    m.read_range(db,a,width,0x80000000)
        class ShortDB:
            def chain(self,*args): return b'',[]
        with self.assertRaisesRegex(c.FormatError,'byte width'):
            m.read_range(ShortDB(),address,72,0x80000000)

    def test_synthetic_selected_instruction_validation(self):
        # Fabricated instruction and a zero-filled synthetic range, not archive bytes.
        raw=bytearray(552)
        raw[4:8]=bytes.fromhex('3860002a')
        with patch.object(m,'WORDS',{m.HANDLER_ADDRESS+4:(0x3860002a,'li 3, 42')}):
            self.assertEqual(m.instruction_facts(raw),[
                dict(address='8004caa8',word='3860002a',annotation='li 3, 42')])
            raw[7]^=1
            with self.assertRaisesRegex(c.FormatError,'word mismatch'):
                m.instruction_facts(raw)
        with self.assertRaisesRegex(c.FormatError,'byte width'): m.instruction_facts(b'')

    def test_selected_facts_are_bounded_not_full_dump(self):
        self.assertLess(len(m.WORDS)*4,552)
        self.assertTrue(all(m.HANDLER_ADDRESS<=pc<m.HANDLER_ADDRESS+552 and pc%4==0
                            for pc in m.WORDS))
        self.assertEqual(m.WORDS[0x8004cb0c][0],0xc8228720)
        self.assertEqual(m.WORDS[0x8004cc0c][0],0x68000001)
        self.assertEqual(m.WORDS[0x8004cc68][0],0x68000001)

    def test_authentication_and_shared_validation(self):
        data=gbf([b''])
        for digest in (hashlib.sha256(data).hexdigest(),next(iter(c.SNAPSHOTS))):
            with self.assertRaisesRegex(c.FormatError,'not allowlisted'): m.inspect(data,digest)
        for message in ('unsupported schema: Program','data5 digest mismatch','known control mismatch'):
            with patch.object(c,'inspect',side_effect=c.FormatError(message)),patch.object(c,'GBF') as parser:
                with self.assertRaisesRegex(c.FormatError,message): m.inspect(b'fixture','fixture')
                parser.assert_not_called()


if __name__ == '__main__':
    unittest.main()
