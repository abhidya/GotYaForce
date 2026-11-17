"""Synthetic-only bounded setup evidence checks; no archived payload fixtures."""
import hashlib
import unittest
from unittest.mock import patch
import read_archived_constants as c
import read_archived_ready_setup_evidence as m
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
                         [(0x80006f98,28),(0x8004871c,208),(0x8004a754,220),
                          (0x8004d548,244),(0x8004adc8,192),(0x8004af94,76)])
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

    def test_source_order_and_reloads(self):
        fields = ((0x80006f98,34,4,3,0x97),
                  (0x8004876c,38,29,31,0x28),(0x80048778,38,30,31,0x29),
                  (0x8004d5bc,36,0,30,4),(0x8004d5c0,32,0,30,4),
                  (0x8004d5cc,32,3,30,0),(0x8004d5e0,32,3,30,4),
                  (0x8004d5f4,36,0,30,4),(0x8004d5fc,32,4,30,4),
                  (0x8004ae08,32,4,29,4),(0x8004ae10,32,4,4,12),
                  (0x8004ae18,32,0,4,12),(0x8004ae1c,48,2,3,12),
                  (0x8004ae20,48,1,3,28),(0x8004ae28,48,0,3,44),
                  (0x8004afa0,32,5,29,4),(0x8004afa8,32,3,5,12),
                  (0x8004afc8,32,3,30,0x7c))
        for pc,op,d,a,imm in fields:
            w=m.WORDS[pc][0]
            self.assertEqual((w>>26,w>>21&31,w>>16&31,w&65535),(op,d,a,imm))
        self.assertEqual(m.WORDS[0x80006fa4][0],0x7c830774) # extsb
        self.assertEqual(m.WORDS[0x8004ae24][0],0x7c00f840) # cmplw
        # All four global reads lie after the in-count branch and before its target.
        for pc in (0x8004ae4c,0x8004ae50,0x8004ae54,0x8004ae58):
            self.assertTrue(0x8004ae38 < pc < 0x8004af94)
            self.assertIn('OUT-OF-COUNT',m.WORDS[pc][1])

    def test_branch_targets_and_endpoints(self):
        for pc,target in ((0x8004ae38,0x8004af94),(0x8004ae00,0x8004b710),
                          (0x8004d5e8,0x8004d618),(0x8004afd0,0x8004b2f0)):
            word=m.WORDS[pc][0]
            self.assertEqual(word>>26,16)
            self.assertEqual(pc+(word&0xfffc),target)
        for pc in (0x80006fb0,0x800487e8,0x8004a82c,0x8004d638):
            self.assertEqual(m.WORDS[pc][0],0x4e800020)
        for pc,target in ((0x8004ae04,0x80006f98),(0x80048750,0x8004d1f4),
                          (0x8004877c,0x8004d244),(0x800487cc,0x8004a754),
                          (0x8004a7b8,0x8004d548),(0x8004af9c,0x8025b178),
                          (0x8004afac,0x8025b1b0),(0x8004afc4,0x8024dc04)):
            w=m.WORDS[pc][0]; displacement=w&0x03fffffc
            if displacement&0x02000000: displacement-=0x04000000
            self.assertEqual(w>>26,18)
            self.assertEqual(pc+displacement,target)

    def test_slot_fixed_width_digest_target_and_no_payload(self):
        payload=pack('I',0x8004871c)
        class DB:
            def chain(self,*args):
                self.args=args
                return payload,[]
        db=DB()
        # Use the known image relocation from the mapping arithmetic, not a snapshot.
        with patch.object(c,'address_start',return_value=m.SLOT_ADDRESS):
            fact=m.slot_evidence(db,0)
            self.assertEqual(db.args,(199,0,4,0xf42c0))
            self.assertEqual(fact['target'],'8004871c')
            self.assertNotIn('raw',fact)
            payload=pack('I',0x80048720)
            with self.assertRaisesRegex(c.FormatError,'slot digest mismatch'):
                m.slot_evidence(db,0)
            with patch.object(m,'SLOT_SHA256',hashlib.sha256(payload).hexdigest()):
                with self.assertRaisesRegex(c.FormatError,'slot target mismatch'):
                    m.slot_evidence(db,0)
            payload=b''
            with self.assertRaisesRegex(c.FormatError,'slot byte width'):
                m.slot_evidence(db,0)
        with patch.object(c,'address_start',return_value=m.SLOT_ADDRESS+4):
            with self.assertRaisesRegex(c.FormatError,'slot mapping bounds'):
                m.slot_evidence(db,0)


if __name__=='__main__': unittest.main()
