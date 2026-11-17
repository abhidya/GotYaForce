"""Synthetic-only fixed movement evidence checks; no archived payload fixtures."""
import hashlib
import unittest
from unittest.mock import patch
import read_archived_constants as c
import read_archived_movement_followup_evidence as m
from test_archived_constants import gbf, pack


class MovementEvidenceTests(unittest.TestCase):
    def test_authentication_cannot_be_spoofed(self):
        data = gbf([b''])
        for digest in (hashlib.sha256(data).hexdigest(), next(iter(c.SNAPSHOTS))):
            with self.assertRaisesRegex(c.FormatError, 'not allowlisted'):
                m.inspect(data, digest)

    def test_schema_failure_precedes_other_reads(self):
        with patch.object(c, 'inspect', side_effect=c.FormatError('unsupported schema')), \
             patch.object(c, 'GBF') as parser:
            with self.assertRaisesRegex(c.FormatError, 'unsupported schema'):
                m.inspect(b'synthetic', 'synthetic')
            parser.assert_not_called()

    def test_fixed_scope_and_existing_reader_unchanged(self):
        self.assertEqual([(a, w) for a, w, _ in m.RANGES],
                         [(0x80048648, 212), (0x8004d08c, 360)])
        self.assertEqual(m.MOVEMENT_TARGETS,
                         ((0x80437104, 4, '3f000000'), (0x80437134, 4, '3f333333'),
                          (0x8043714c, 4, '40a00000')))
        self.assertEqual(len(c.TARGETS), 12)
        for address, width, _ in m.MOVEMENT_TARGETS:
            self.assertNotIn((address, width), c.TARGETS)
            self.assertNotIn(address, c.CONTROLS)
            self.assertNotIn(address, c.EXPECTED_TARGETS)
        self.assertTrue(all(any(a <= pc < a+w for a, w, _ in m.RANGES) for pc in m.WORDS))

    def test_synthetic_range_guards_and_no_payload_output(self):
        address, word = m.TEXT_START, 0x60000000
        payload = pack('I', word)
        class DB:
            def chain(self, *args):
                self.args = args
                return payload, []
        db = DB()
        with self.assertRaisesRegex(c.FormatError, 'not allowlisted'):
            m.range_evidence(db, 21, address, 4)
        with patch.object(m, 'RANGES', ((address, 4, hashlib.sha256(payload).hexdigest()),)), \
             patch.object(m, 'WORDS', {address:(word, 'synthetic fact')}):
            fact = m.range_evidence(db, 21, address, 4)
            self.assertEqual(db.args, (21, 0, 4, m.TEXT_LENGTH))
            self.assertEqual(set(fact), {'address', 'width', 'sha256', 'spans', 'instructions'})
            self.assertEqual(fact['instructions'][0]['annotation'], 'synthetic fact')
            with patch.object(m, 'WORDS', {address:(word+1, 'wrong')}):
                with self.assertRaisesRegex(c.FormatError, 'word mismatch'):
                    m.range_evidence(db, 21, address, 4)
            with patch.object(m, 'RANGES', ((address, 4, '0'*64),)):
                with self.assertRaisesRegex(c.FormatError, 'digest mismatch'):
                    m.range_evidence(db, 21, address, 4)

    def test_range_width_alignment_bounds(self):
        class DB:
            def chain(self, *args): return b'', []
        with self.assertRaisesRegex(c.FormatError, 'byte width'):
            m.range_evidence(DB(), 21, *m.RANGES[0][:2])
        for address, width in ((m.TEXT_START+1, 4), (m.TEXT_START, 3),
                               (m.TEXT_START-4, 4), (m.TEXT_START+m.TEXT_LENGTH, 4)):
            with patch.object(m, 'RANGES', ((address, width, 'unused'),)):
                with self.assertRaisesRegex(c.FormatError, 'alignment/bounds'):
                    m.range_evidence(DB(), 21, address, width)

    def test_constant_guards_and_synthetic_scalar(self):
        address = 0x80437104
        mapping = (address, address+4, 7, 'MAIN_.data5', 7, 4, 263)
        payload = pack('f', 1.5)
        class DB:
            def chain(self, *args):
                self.args = args
                return payload, []
        db = DB()
        with self.assertRaisesRegex(c.FormatError, 'not allowlisted'):
            m.constant_evidence(db, mapping, address+4, 4)
        with self.assertRaisesRegex(c.FormatError, 'bits mismatch'):
            m.constant_evidence(db, mapping, address, 4)
        with patch.object(m, 'MOVEMENT_TARGETS', ((address, 4, payload.hex()),)):
            fact = m.constant_evidence(db, mapping, address, 4)
            self.assertEqual(db.args, (263, 0, 4, 4))
            self.assertEqual(fact['number'], 1.5)
            self.assertEqual(fact['sha256'], hashlib.sha256(payload).hexdigest())
            self.assertFalse(fact['control'])
            self.assertNotIn('raw', fact)
            with self.assertRaisesRegex(c.FormatError, 'width/bounds'):
                m.constant_evidence(db, (address+1, address+5, 7, '', 7, 4, 263), address, 4)
            payload = b''
            with self.assertRaisesRegex(c.FormatError, 'byte width'):
                m.constant_evidence(db, mapping, address, 4)
        payload = pack('I', 0x7fc00000)
        with patch.object(m, 'MOVEMENT_TARGETS', ((address, 4, payload.hex()),)):
            with self.assertRaisesRegex(c.FormatError, 'nonfinite'):
                m.constant_evidence(db, mapping, address, 4)

    def test_float_decoder_operands_and_reserved_bits(self):
        for d, a, b, fc in ((1, 2, 3, 4), (31, 30, 29, 28), (0, 0, 0, 0)):
            sub = (59 << 26) | (d << 21) | (a << 16) | (b << 11) | (20 << 1)
            self.assertEqual(m.float_instruction(sub),
                             dict(mnemonic='fsubs', fD=d, fA=a, fB=b, rounding='single'))
            mul = (59 << 26) | (d << 21) | (a << 16) | (fc << 6) | (25 << 1)
            self.assertEqual(m.float_instruction(mul),
                             dict(mnemonic='fmuls', fD=d, fA=a, fC=fc, rounding='single'))
            for xo, name in ((29, 'fmadds'), (30, 'fnmsubs')):
                fused = (59 << 26) | (d << 21) | (a << 16) | (b << 11) | (fc << 6) | (xo << 1)
                self.assertEqual(m.float_instruction(fused),
                                 dict(mnemonic=name, fD=d, fA=a, fC=fc, fB=b, rounding='single fused'))
                with self.assertRaises(c.FormatError): m.float_instruction(fused | 1)
            for bad in (sub | 1, sub | (1 << 6), mul | 1, mul | (1 << 11)):
                with self.assertRaises(c.FormatError): m.float_instruction(bad)
        for cr in range(8):
            compare = (63 << 26) | (cr << 23) | (7 << 16) | (11 << 11) | (32 << 1)
            self.assertEqual(m.float_instruction(compare), dict(mnemonic='fcmpo', crD=cr, fA=7, fB=11))
            for bad in (compare | 1, compare | (1 << 21)):
                with self.assertRaises(c.FormatError): m.float_instruction(bad)
        for bad in (-1, 1 << 32, 0, 0xfc010000):
            with self.assertRaises(c.FormatError): m.float_instruction(bad)

    def test_verified_float_operand_order(self):
        expected = {
            0x8004d0e8: ('fsubs', 1, 1, 2, None),
            0x8004d0ec: ('fmuls', 1, 3, None, 1),
            0x8004d0f0: ('fmuls', 0, 1, None, 0),
            0x8004d11c: ('fnmsubs', 0, 1, 0, 2),
            0x8004d144: ('fsubs', 1, 1, 3, None),
            0x8004d148: ('fmadds', 1, 1, 3, 2),
            0x8004d174: ('fsubs', 1, 1, 4, None),
            0x8004d1b0: ('fsubs', 1, 1, 0, None),
            0x8004d1c4: ('fmuls', 1, 2, None, 1),
            0x8004d1c8: ('fmuls', 1, 3, None, 1),
        }
        for pc, want in expected.items():
            fact = m.float_instruction(m.WORDS[pc][0])
            self.assertEqual(tuple(fact.get(k) for k in ('mnemonic', 'fD', 'fA', 'fB', 'fC')), want)
        for pc in (0x8004d14c, 0x8004d178, 0x8004d1d4):
            self.assertEqual(m.float_instruction(m.WORDS[pc][0]),
                             dict(mnemonic='fcmpo', crD=0, fA=1, fB=0))

    def test_source_memory_order_and_single_670_snapshot(self):
        fields = ((0x8004d090, 34, 0, 3, 0x3e8), (0x8004d09c, 34, 0, 3, 0x661),
                  (0x8004d0a8, 32, 0, 3, 0x5e0), (0x8004d0b4, 34, 4, 3, 0x71d),
                  (0x8004d0fc, 32, 4, 3, 0x4b0), (0x8004d100, 48, 4, 3, 0x670),
                  (0x8004d104, 48, 0, 3, 0x920), (0x8004d110, 52, 0, 3, 0x6d0),
                  (0x8004d114, 48, 1, 3, 0x66c), (0x8004d118, 48, 0, 3, 0x6d0),
                  (0x8004d120, 52, 0, 3, 0x6d0), (0x8004d124, 32, 4, 3, 0x4b0),
                  (0x8004d128, 48, 3, 3, 0x24), (0x8004d12c, 34, 0, 4, 0xf),
                  (0x8004d130, 48, 0, 3, 0x6d0), (0x8004d140, 48, 1, 4, 0x8f0),
                  (0x8004d164, 48, 0, 3, 0x6d0), (0x8004d194, 34, 4, 6, 0),
                  (0x8004d1a4, 48, 1, 3, 0x6d0), (0x8004d1a8, 48, 0, 3, 0x24),
                  (0x8004d1b8, 52, 1, 3, 0x6d0), (0x8004d1bc, 48, 1, 3, 0x6d8),
                  (0x8004d1c0, 48, 3, 3, 0x6d0), (0x8004d1cc, 52, 1, 3, 0x6d0),
                  (0x8004d1d0, 48, 1, 3, 0x6d0), (0x8004d1dc, 52, 0, 3, 0x6d0),
                  (0x8004d1e8, 52, 0, 3, 0x6d0))
        for pc, op, d, a, imm in fields:
            word = m.WORDS[pc][0]
            self.assertEqual((word >> 26, word >> 21 & 31, word >> 16 & 31, word & 65535),
                             (op, d, a, imm))
        reads670 = [pc for pc, (word, _) in m.WORDS.items()
                    if word >> 26 == 48 and word >> 16 & 31 == 3 and word & 65535 == 0x670]
        self.assertEqual(reads670, [0x8004d100])
        self.assertEqual(m.WORDS[0x8004d108][0], 0x38c40022)
        self.assertEqual(m.WORDS[0x8004d188][0], 0x38c60008)

    def test_signed_bytes_and_strict_comparison_branches(self):
        for pc in (0x8004d0a0, 0x8004d0b8, 0x8004d0c0,
                   0x8004d134, 0x8004d160, 0x8004d198):
            word = m.WORDS[pc][0]
            self.assertEqual((word >> 26, (word >> 1) & 1023), (31, 954))
        self.assertEqual(m.WORDS[0x8004d19c][0], 0x2c00ffff)
        for pc in (0x8004d150, 0x8004d17c, 0x8004d1d8):
            word = m.WORDS[pc][0]
            self.assertEqual((word >> 26, word >> 21 & 31, word >> 16 & 31), (16, 4, 0))

    def test_branch_targets_and_caller_postamble(self):
        branches = ((0x8004866c, 0x80048704), (0x80048684, 0x800486a0),
                    (0x80048690, 0x800486a0), (0x8004869c, 0x80048704),
                    (0x800486b4, 0x800486cc), (0x800486f0, 0x80048704),
                    (0x8004d098, 0x8004d1e4), (0x8004d0a4, 0x8004d1e4),
                    (0x8004d0b0, 0x8004d1e4), (0x8004d0bc, 0x8004d0fc),
                    (0x8004d150, 0x8004d158), (0x8004d17c, 0x8004d184),
                    (0x8004d190, 0x8004d1a4), (0x8004d1a0, 0x8004d160),
                    (0x8004d1d8, 0x8004d1ec))
        for pc, target in branches:
            word = m.WORDS[pc][0]
            displacement = word & 0xfffc
            if displacement & 0x8000: displacement -= 0x10000
            self.assertEqual(word >> 26, 16)
            self.assertEqual(pc+displacement, target)
        for pc, target in ((0x800486c4, 0x8004a41c), (0x80048700, 0x8004d08c)):
            word = m.WORDS[pc][0]
            displacement = word & 0x03fffffc
            if displacement & 0x02000000: displacement -= 0x04000000
            self.assertEqual(word >> 26, 18)
            self.assertEqual(pc+displacement, target)
        self.assertEqual(m.WORDS[0x800486fc][0], 0xd01e06d8)
        for pc in (0x80048718, 0x8004d1f0):
            self.assertEqual(m.WORDS[pc][0], 0x4e800020)

    def test_constant_instruction_address_derivation(self):
        # r2=8043ea20 is the same source convention used by the existing reader.
        for pc, address in ((0x800486f4, 0x804370f0), (0x8004d0d4, 0x804370f8),
                            (0x8004d0dc, 0x8043714c), (0x8004d10c, 0x80437104),
                            (0x8004d1ac, 0x80437134), (0x8004d1e4, 0x804370f4)):
            word = m.WORDS[pc][0]
            self.assertEqual(word >> 16 & 31, 2)
            displacement = (word & 65535)-65536
            self.assertEqual(0x8043ea20+displacement, address)


if __name__ == '__main__':
    unittest.main()
