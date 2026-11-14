#!/usr/bin/env python3
"""Synthetic fixed-span, decoder and refusal tests; no archived byte fixtures."""
import contextlib
import hashlib
import io
import struct
import unittest
from unittest.mock import patch

import read_archived_transform_history_evidence as h


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, [dict(synthetic=True)]


class EvidenceTests(unittest.TestCase):
    def decode(self, word, pc=0x8005685c):
        return h.decode_selected(word, pc)

    def test_fixed_span_identity(self):
        self.assertEqual(h.RANGES, ((0x8005685c, 0xa4,
                         '9ad43b6e8ed1d405fa3c2e0fc0803871f93353c6ebf6f7ae7585d07211bf41a6'),))
        self.assertEqual(h.RANGES[0][0] + h.RANGES[0][1], 0x80056900)

    def test_word_load_and_store_fields(self):
        for offset in (0x2c, 0x30, 0x34, 0x20, 0x24, 0x28, 0x70, 0x1d64, 0xcc, 0x518, 0x51c, 0x520):
            word = (32 << 26) | (7 << 21) | (3 << 16) | offset
            self.assertEqual(self.decode(word), dict(mnemonic='lwz', rD=7, rA=3, displacement=offset))
        for offset in (0x5e8, 0x5ec, 0x5f0, 0x2c, 0x30, 0x34, 0x76, 0x1d6a, 0x524, 0x528, 0x52c):
            word = (36 << 26) | (7 << 21) | (3 << 16) | offset
            self.assertEqual(self.decode(word), dict(mnemonic='stw', rS=7, rA=3, displacement=offset))

    def test_short_pair_tails_are_unsigned_loads(self):
        for source, target in ((0x74, 0x7a), (0x1d68, 0x1d6e)):
            self.assertEqual(self.decode((40 << 26) | (3 << 16) | source),
                             dict(mnemonic='lhz', rD=0, rA=3, displacement=source))
            self.assertEqual(self.decode((44 << 26) | (3 << 16) | target),
                             dict(mnemonic='sth', rS=0, rA=3, displacement=target))
        self.assertIsNone(self.decode((42 << 26) | (3 << 16) | 0x74))

    def test_scalar_copy_is_float_load_store(self):
        self.assertEqual(self.decode((48 << 26) | (3 << 16) | 0x6d0),
                         dict(mnemonic='lfs', fD=0, rA=3, displacement=0x6d0))
        self.assertEqual(self.decode((52 << 26) | (3 << 16) | 0x6d4),
                         dict(mnemonic='stfs', fS=0, rA=3, displacement=0x6d4))

    def test_signed_memory_displacement(self):
        self.assertEqual(self.decode((36 << 26) | (4 << 21) | (3 << 16) | 0xffff),
                         dict(mnemonic='stw', rS=4, rA=3, displacement=-1))
        self.assertEqual(self.decode((48 << 26) | (7 << 21) | (5 << 16) | 0x8000),
                         dict(mnemonic='lfs', fD=7, rA=5, displacement=-32768))

    def test_target_and_source_byte_loads(self):
        for destination, base, offset in ((0, 4, 0x83), (4, 4, 0x5e6), (0, 3, 0x3e5)):
            self.assertEqual(self.decode((34 << 26) | (destination << 21) | (base << 16) | offset),
                             dict(mnemonic='lbz', rD=destination, rA=base, displacement=offset))

    def test_unsigned_compare_fields(self):
        self.assertEqual(self.decode((10 << 26) | (4 << 16)),
                         dict(mnemonic='cmpli', BF=0, L=0, rA=4, immediate=0))
        self.assertEqual(self.decode((10 << 26) | (3 << 23) | (1 << 21) | (5 << 16) | 0xffff),
                         dict(mnemonic='cmpli', BF=3, L=1, rA=5, immediate=65535))

    def test_sign_extension_and_record_mask(self):
        for register, record in ((0, 1), (4, 0), (0, 0)):
            word = (31 << 26) | (register << 21) | (register << 16) | (954 << 1) | record
            self.assertEqual(self.decode(word), dict(mnemonic='extsb', rS=register, rA=register, Rc=record))
        self.assertEqual(self.decode((31 << 26) | (4 << 21) | (28 << 1) | 1),
                         dict(mnemonic='and', rS=4, rA=0, rB=0, Rc=1))

    def test_conditional_return_and_final_return(self):
        conditional = (19 << 26) | (12 << 21) | (2 << 16) | (16 << 1)
        self.assertEqual(self.decode(conditional), dict(mnemonic='bclr', BO=12, BI=2, BH=0, LK=0))
        self.assertEqual(self.decode((19 << 26) | (20 << 21) | (16 << 1)), dict(mnemonic='blr'))
        for changed in (conditional | 1, conditional | (1 << 11), conditional | (1 << 13),
                        conditional ^ (1 << 16), conditional ^ (1 << 21), conditional ^ 2):
            self.assertIsNone(self.decode(changed))

    def test_branch_fields_and_target(self):
        self.assertEqual(self.decode((16 << 26) | (4 << 21) | (2 << 16) | 0x1c, 0x800568c8),
                         dict(mnemonic='bc', BO=4, BI=2, LK=0, target='800568e4', AA=0))
        self.assertEqual(self.decode((16 << 26) | (12 << 21) | (2 << 16) | 0xfffc),
                         dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80056858', AA=0))
        self.assertEqual(self.decode((16 << 26) | (12 << 21) | (2 << 16) | 0x103),
                         dict(mnemonic='bc', BO=12, BI=2, LK=1, target='00000100', AA=1))

    def test_unselected_forms(self):
        for word in (0, 18 << 26, 0x4e800421, (31 << 26) | (266 << 1), 14 << 26):
            self.assertIsNone(self.decode(word))

    def test_invalid_words_and_pcs(self):
        for word in (-1, 1 << 32, True, False, 1.0, '0', None):
            with self.subTest(word=word), self.assertRaises(h.c.FormatError):
                self.decode(word)
        for pc in (-1, 1, 1 << 32, True, False, 2147838044.0, '0', None):
            with self.subTest(pc=pc), self.assertRaises(h.c.FormatError):
                self.decode(0, pc)

    def test_range_allowlist_before_read(self):
        for address, width in ((0x80056860, 160), (0x8005685c, 160), (0x8005685c, 168),
                               (0x8005685b, 164), (0x80056900, 164), (0x8005685c, 0)):
            with self.subTest(address=address, width=width), self.assertRaisesRegex(h.c.FormatError, 'not allowlisted'):
                h.range_evidence(None, 21, address, width)

    def test_range_integer_fields_before_read(self):
        for root, address, width in ((21.0, 0x8005685c, 164), (True, 0x8005685c, 164),
                                     (21, float(0x8005685c), 164), (21, 0x8005685c, 164.0)):
            with self.assertRaisesRegex(h.c.FormatError, 'integer fields'):
                h.range_evidence(None, root, address, width)

    def test_range_root_alignment_bounds_before_read(self):
        with self.assertRaisesRegex(h.c.FormatError, 'root/alignment/bounds'):
            h.range_evidence(None, 22, 0x8005685c, 164)
        for address, width in ((0x8005685d, 164), (0x8005685c, 163),
                               (h.TEXT_START - 4, 4), (h.TEXT_START + h.TEXT_LENGTH - 4, 8),
                               (0x8005685c, 0), (0x8005685c, -4)):
            with patch.object(h, 'RANGES', ((address, width, 'unused'),)):
                with self.assertRaisesRegex(h.c.FormatError, 'root/alignment/bounds'):
                    h.range_evidence(None, 21, address, width)

    def test_duplicate_allowlist_is_rejected(self):
        with patch.object(h, 'RANGES', h.RANGES * 2):
            with self.assertRaisesRegex(h.c.FormatError, 'not allowlisted'):
                h.range_evidence(None, 21, 0x8005685c, 164)

    def test_range_hash_and_width_before_decode(self):
        for raw, message in ((bytes(164), 'digest mismatch'), (bytes(160), 'byte width'),
                             (bytes(168), 'byte width')):
            with patch.object(h, 'decode_selected') as decoder:
                with self.assertRaisesRegex(h.c.FormatError, message):
                    h.range_evidence(FakeDB(raw), 21, 0x8005685c, 164)
                decoder.assert_not_called()

    def test_width_independent_of_hash(self):
        raw = bytes(168)
        with patch.object(h, 'RANGES', ((0x8005685c, 164, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(h.c.FormatError, 'byte width'):
                h.range_evidence(FakeDB(raw), 21, 0x8005685c, 164)

    def test_synthetic_fields_order_and_no_raw_output(self):
        # Fabricated register-7 word/halfword pair; not a copy of archive bytes.
        words = ((32 << 26) | (7 << 21) | (3 << 16) | 0x70,
                 (36 << 26) | (7 << 21) | (3 << 16) | 0x76,
                 (40 << 26) | (7 << 21) | (3 << 16) | 0x74,
                 (44 << 26) | (7 << 21) | (3 << 16) | 0x7a)
        raw = struct.pack('>4I', *words)
        db = FakeDB(raw)
        with patch.object(h, 'RANGES', ((0x8005685c, 16, hashlib.sha256(raw).hexdigest()),)):
            result = h.range_evidence(db, 21, 0x8005685c, 16)
        self.assertEqual(db.calls, [(21, 0x8005685c - h.TEXT_START, 16, h.TEXT_LENGTH)])
        self.assertEqual(result['spans'], [dict(synthetic=True)])
        self.assertEqual(result['end_exclusive'], '8005686c')
        self.assertEqual([item['mnemonic'] for item in result['instructions']], ['lwz', 'stw', 'lhz', 'sth'])
        self.assertEqual([item['displacement'] for item in result['instructions']], [0x70, 0x76, 0x74, 0x7a])
        self.assertEqual([item['address'] for item in result['instructions']],
                         ['8005685c', '80056860', '80056864', '80056868'])
        for item in [result] + result['instructions']:
            self.assertTrue(set(item).isdisjoint(('raw', 'bytes', 'word', 'words', 'hex')))

    def test_unselected_span_refuses_incomplete_evidence(self):
        raw = bytes(4)
        with patch.object(h, 'RANGES', ((0x8005685c, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(h.c.FormatError, 'unselected instruction'):
                h.range_evidence(FakeDB(raw), 21, 0x8005685c, 4)

    def test_authentication_and_shared_validation_first(self):
        data = bytes(32)
        for digest in ('0' * 64, hashlib.sha256(data).hexdigest(), next(iter(h.c.SNAPSHOTS))):
            with patch.object(h.c, 'GBF') as parser:
                with self.assertRaisesRegex(h.c.FormatError, 'not allowlisted'):
                    h.inspect(data, digest)
                parser.assert_not_called()
        for message in ('unsupported schema: Program', 'data5 digest mismatch', 'known control mismatch'):
            with patch.object(h.c, 'inspect', side_effect=h.c.FormatError(message)), patch.object(h.c, 'GBF') as parser:
                with self.assertRaisesRegex(h.c.FormatError, message):
                    h.inspect(b'fixture', 'fixture')
                parser.assert_not_called()

    def inspect_fixture(self):
        auth = dict(snapshot='synthetic', snapshot_sha256='synthetic', program_name='boot.dol',
                    created_with_ghidra_version='12.1.2', executable_sha256_metadata='synthetic',
                    executable_sha256_property_type=2, executable_metadata_caveat='synthetic',
                    file_bytes_table=dict(version=0, root=-1, count=0), block_size=16384,
                    master_root=1, table_roots={}, image_offset='80000000', data5_sha256='synthetic')
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in h.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in h.command.MAPPINGS}
        return auth, blocks, subs

    def test_inspect_uses_fixed_range_and_no_new_constants(self):
        auth, blocks, subs = self.inspect_fixture()
        with patch.object(h.c, 'inspect', return_value=auth) as authentication, \
                patch.object(h.c, 'GBF') as parser, patch.object(h, 'range_evidence', return_value='derived') as evidence:
            db = parser.return_value
            db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
            db.rows.side_effect = lambda table: {'blocks': blocks, 'subs': subs}[table]
            result = h.inspect(b'synthetic', 'synthetic')
            authentication.assert_called_once_with(b'synthetic', 'synthetic')
            evidence.assert_called_once_with(db, 21, 0x8005685c, 164)
            db.chain.assert_not_called()
        self.assertEqual(result['ranges'], ['derived'])
        self.assertEqual(result['constants'], [])
        self.assertEqual(result['chain_root'], 21)
        self.assertEqual(result['block_name'], 'MAIN_.text1')

    def test_inspect_mapping_failures_precede_span_read(self):
        for key in (1, 5, 7):
            auth, blocks, subs = self.inspect_fixture()
            subs[key][4] += 1
            with patch.object(h.c, 'inspect', return_value=auth), patch.object(h.c, 'GBF') as parser, \
                    patch.object(h, 'range_evidence') as evidence:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda table: {'blocks': blocks, 'subs': subs}[table]
                with self.subTest(key=key), self.assertRaisesRegex(h.c.FormatError, 'mapping mismatch'):
                    h.inspect(b'synthetic', 'synthetic')
                evidence.assert_not_called()
                db.chain.assert_not_called()

    def test_cli_has_no_address_or_width_interface(self):
        with patch.object(h.sys, 'argv', ['reader', 'fixture.gbf', '--address', '8005685c']), \
                contextlib.redirect_stderr(io.StringIO()), patch.object(h, 'inspect') as inspect:
            with self.assertRaises(SystemExit) as error:
                h.main()
            self.assertEqual(error.exception.code, 2)
            inspect.assert_not_called()


if __name__ == '__main__':
    unittest.main()
