"""Synthetic-only bounded setup evidence checks; no archived payload fixtures."""
import hashlib
import unittest
from unittest.mock import patch
import read_archived_constants as c
import read_archived_setup_metadata_evidence as m
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
                         [(0x8004d1f4,80),(0x8004d244,772)])
        self.assertEqual(len(c.TARGETS),12)
        self.assertNotIn((0x8043712c,4),c.TARGETS)
        self.assertNotIn(0x8043712c,c.EXPECTED_TARGETS)
        self.assertNotIn(0x8043712c,c.CONTROLS)
        self.assertTrue(all(any(a<=pc<a+w for a,w,_ in m.RANGES) for pc in m.WORDS))

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

    def test_signed_selector_and_order_fields(self):
        for pc,op,d,a,imm in ((0x8004d218,34,0,3,0x582),
                              (0x8004d304,34,0,5,0x33),
                              (0x8004d308,32,4,3,0x4b0),
                              (0x8004d314,34,7,4,0xbe),
                              (0x8004d31c,38,7,4,0x1d74),
                              (0x8004d2d8,34,0,6,6),
                              (0x8004d3fc,34,0,6,14),
                              (0x8004d49c,34,0,6,22),
                              (0x8004d524,34,0,6,30)):
            w=m.WORDS[pc][0]
            self.assertEqual((w>>26,w>>21&31,w>>16&31,w&65535),(op,d,a,imm))
        for pc in (0x8004d204,0x8004d22c,0x8004d238):
            w=m.WORDS[pc][0]
            self.assertEqual((w>>26,w>>1&1023),(31,343)) # lhax, not lhzx

    def test_branch_targets_and_endpoints(self):
        for pc,target in ((0x8004d250,0x8004d438),(0x8004d25c,0x8004d274),
                          (0x8004d260,0x8004d398)):
            word=m.WORDS[pc][0]
            self.assertEqual(word>>26,16)
            self.assertEqual(pc+(word&0xfffc),target)
        for pc in (0x8004d240,0x8004d264,0x8004d544):
            self.assertEqual(m.WORDS[pc][0],0x4e800020)


if __name__=='__main__': unittest.main()
