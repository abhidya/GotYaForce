"""Synthetic-only bounded setup evidence checks; no archived payload fixtures."""
import hashlib
import unittest
from unittest.mock import patch
import read_archived_constants as c
import read_archived_setup_command_evidence as m
from test_archived_constants import gbf, pack


class SetupEvidenceTests(unittest.TestCase):
    def test_authentication_cannot_be_spoofed(self):
        data=gbf([b''])
        for digest in (hashlib.sha256(data).hexdigest(), next(iter(c.SNAPSHOTS))):
            with self.assertRaisesRegex(c.FormatError,'not allowlisted'):
                m.inspect(data,digest)

    def test_schema_failure_propagates_before_other_reads(self):
        with patch.object(c,'inspect',side_effect=c.FormatError('unsupported schema')), \
             patch.object(c,'GBF') as parser:
            with self.assertRaisesRegex(c.FormatError,'unsupported schema'):
                m.inspect(b'synthetic','synthetic')
            parser.assert_not_called()

    def test_ranges_are_narrow_and_constants_unchanged(self):
        self.assertEqual([(a,w) for a,w,_ in m.RANGES],
                         [(0x8004c050,584),(0x8004c298,396),(0x80048648,212)])
        self.assertEqual(len(c.TARGETS),12)
        self.assertNotIn((0x8043712c,4),c.TARGETS)
        self.assertNotIn(0x8043712c,c.EXPECTED_TARGETS)
        self.assertNotIn(0x8043712c,c.CONTROLS)
        self.assertTrue(all(any(a<=pc<a+w for a,w,_ in m.RANGES) for pc in m.WORDS))

    def test_entry1_and_width(self):
        table=bytearray(72)
        table[4:8]=pack('I',0x8004c298)
        m.verify_entry1(table)
        for value in (table[:-1],table+b'\0',bytes(72)):
            with self.assertRaises(c.FormatError):m.verify_entry1(value)

    def test_synthetic_range_no_payload_output(self):
        address=m.TEXT_START
        word=0x60000000  # Synthetic fixture, no archived payload.
        payload=pack('I',word)
        class DB:
            def chain(self,*args):
                self.args=args
                return payload,[]
        db=DB()
        with self.assertRaisesRegex(c.FormatError,'not allowlisted'):
            m.range_evidence(db,21,address,4)
        with patch.object(m,'RANGES',((address,4,hashlib.sha256(payload).hexdigest()),)), \
             patch.object(m,'WORDS',{address:(word,'synthetic fact')}):
            fact=m.range_evidence(db,21,address,4)
            self.assertEqual(db.args,(21,0,4,m.TEXT_LENGTH))
            self.assertEqual(set(fact),{'address','width','sha256','spans','instructions'})
            self.assertEqual(fact['instructions'][0]['annotation'],'synthetic fact')
            with patch.object(m,'WORDS',{address:(word+1,'wrong')}):
                with self.assertRaisesRegex(c.FormatError,'word mismatch'):
                    m.range_evidence(db,21,address,4)
            with patch.object(m,'RANGES',((address,4,'0'*64),)):
                with self.assertRaisesRegex(c.FormatError,'digest mismatch'):
                    m.range_evidence(db,21,address,4)

    def test_width_alignment_bounds(self):
        class DB:
            def chain(self,*args):return b'',[]
        with self.assertRaisesRegex(c.FormatError,'byte width'):
            m.range_evidence(DB(),21,*m.RANGES[0][:2])
        for a,w in ((m.TEXT_START+1,4),(m.TEXT_START,3),(m.TEXT_START-4,4),
                    (m.TEXT_START+m.TEXT_LENGTH,4)):
            with patch.object(m,'RANGES',((a,w,'unused'),)):
                with self.assertRaisesRegex(c.FormatError,'alignment/bounds'):
                    m.range_evidence(DB(),21,a,w)

    def test_fmr_lifetimes_and_signed_defaults(self):
        # Independently decode fields for the selected exact fmr words.
        for pc,d,b in ((0x8004c070,31,1),(0x8004c098,1,31),
                       (0x8004c2b0,31,1),(0x8004c388,1,31)):
            word=m.WORDS[pc][0]
            self.assertEqual((word>>26,word>>21&31,word>>16&31,word>>11&31,
                              word>>1&1023,word&1),(63,d,0,b,72,0))
        for pc,op,d,a,imm in ((0x8004c2c0,14,0,31,8),(0x8004c2cc,36,0,5,0),
                               (0x8004c2dc,42,3,31,6),(0x8004c304,34,30,31,3),
                               (0x8004c310,34,29,31,4)):
            word=m.WORDS[pc][0]
            self.assertEqual((word>>26,word>>21&31,word>>16&31,word&65535),
                             (op,d,a,imm))

    def test_branch_targets(self):
        for pc,target in ((0x8004c0e0,0x8004c170),(0x8004c0d8,0x8004c094),
                          (0x8004c3d0,0x8004c320),(0x8004866c,0x80048704),
                          (0x8004869c,0x80048704),(0x800486b4,0x800486cc)):
            word=m.WORDS[pc][0]
            self.assertEqual(word>>26,16)
            offset=word&0xfffc
            if offset&0x8000:offset-=0x10000
            self.assertEqual(pc+offset,target)
        for pc,target in ((0x8004c3a4,0x80048648),(0x800486c4,0x8004a41c),
                          (0x80048700,0x8004d08c)):
            word=m.WORDS[pc][0]
            self.assertEqual((word>>26,word&3),(18,1))
            offset=word&0x3fffffc
            if offset&0x2000000:offset-=0x4000000
            self.assertEqual(pc+offset,target)
        self.assertEqual(m.WORDS[0x8004c420][0],0x4e800020)


if __name__=='__main__': unittest.main()
