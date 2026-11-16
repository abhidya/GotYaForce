#!/usr/bin/env python3
"""Fixed initializer operands, authentication and fail-closed controls."""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_input_gqr_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


EXPECTED = [
    dict(address='8002a408', mnemonic='li', rD=3, immediate=6),
    dict(address='8002a40c', mnemonic='oris', rA=3, rS=3, immediate=6),
    dict(address='8002a410', mnemonic='mtspr', spr=916, rS=3),
    dict(address='8002a414', mnemonic='li', rD=3, immediate=7),
    dict(address='8002a418', mnemonic='oris', rA=3, rS=3, immediate=7),
    dict(address='8002a41c', mnemonic='mtspr', spr=917, rS=3),
]


class SyntheticTests(unittest.TestCase):
    def test_exact_extent_and_existing_control(self):
        self.assertEqual(a.RANGES, ((0x8002a408, 24,
                         '9b36820166852b72b71cd34c91a379644b1b9dc97aca1e7e6c078cc74933efce'),))
        self.assertEqual(sorted(a.WORDS), list(range(0x8002a408, 0x8002a420, 4)))
        for pc in range(0x8002a414, 0x8002a420, 4):
            self.assertEqual(a.WORDS[pc], a.wait.WORDS[pc])

    def test_selected_decoder_and_strict_inputs(self):
        self.assertEqual(a.decode_selected(d_form(14, 9, 0, -1)),
                         dict(mnemonic='li', rD=9, immediate=-1))
        self.assertEqual(a.decode_selected(d_form(25, 8, 7, 0x8000)),
                         dict(mnemonic='oris', rA=7, rS=8, immediate=0x8000))
        for spr in (0, 31, 32, 916, 917, 1023):
            self.assertEqual(a.decode_selected(spr_form(467, 5, spr)),
                             dict(mnemonic='mtspr', spr=spr, rS=5))
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'):
                a.decode_selected(word)
        for word in (0, 0x4e800020, d_form(14, 3, 1, 0), d_form(56, 1, 2, 0),
                     spr_form(339, 3, 916), spr_form(467, 3, 916, 1)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected'):
                a.decode_selected(word)

    def test_range_guards_before_reads_and_decode(self):
        pc, width, _ = a.RANGES[0]
        for args in ((21, pc + 4, width - 4), (21, pc, width - 4), (21, pc, width + 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, *args)
        for args in ((21.0, pc, width), (21, True, width), (21, pc, float(width))):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.range_evidence(None, *args)
        with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
            a.range_evidence(None, 22, pc, width)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, pc, width)
        for raw, reason in ((bytes(width - 4), 'byte width'), (bytes(width), 'digest')):
            with patch.object(a, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), 21, pc, width)
                decoder.assert_not_called()

    def test_fixed_word_guard_independent_of_digest(self):
        pc, _, _ = a.RANGES[0]
        payload = struct.pack('>I', d_form(14, 3, 0, 5))
        with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(payload).hexdigest()),)), \
                patch.object(a, 'decode_selected') as decoder:
            with self.assertRaisesRegex(a.c.FormatError, 'word mismatch'):
                a.range_evidence(FakeDB(payload), 21, pc, 4)
            decoder.assert_not_called()

    def test_initializer_is_only_two_exact_triplets(self):
        settings = a.initializer_settings(copy.deepcopy(EXPECTED))
        self.assertEqual(settings, [
            dict(register='GQR4', spr=916, write_address='8002a410', value='00060006',
                 load_type=6, load_scale=0, store_type=6, store_scale=0),
            dict(register='GQR5', spr=917, write_address='8002a41c', value='00070007',
                 load_type=7, load_scale=0, store_type=7, store_scale=0),
        ])
        for length in (0, 5, 7):
            with self.assertRaisesRegex(a.c.FormatError, 'instruction count'):
                a.initializer_settings((EXPECTED + EXPECTED)[:length])
        for index, item in enumerate(EXPECTED):
            for key, value in item.items():
                changed = copy.deepcopy(EXPECTED)
                changed[index][key] = value + 1 if isinstance(value, int) else 'wrong'
                with self.subTest(index=index, key=key), self.assertRaisesRegex(a.c.FormatError, 'operand mismatch'):
                    a.initializer_settings(changed)

    def test_authentication_precedes_new_reads(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.inspect(bytes(32), digest)
                parser.assert_not_called()
                reader.assert_not_called()
        for reason in ('schema', 'language', 'File Bytes table is not empty', 'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), \
                    patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_mapping_failures_precede_fixed_reads(self):
        blocks = {1: ['MAIN_.text1', None, None, 0, 0x20000000000055e0, a.wait.TEXT_LENGTH, 0]}
        subs = {1: [1, 2, a.wait.TEXT_LENGTH, 0, 21, 0]}
        for target in ('root', 'source_offset', 'type', 'duplicate', 'overlap', 'image'):
            auth, bb, ss = copy.deepcopy(({'image_offset': '80000000'}, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'source_offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = bb[1].copy()
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': auth['image_offset'] = '80000004'
            with patch.object(a.c, 'inspect', return_value=auth), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as reader:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.subTest(target=target), self.assertRaises(a.c.FormatError):
                    a.inspect(b'synthetic', 'synthetic')
                reader.assert_not_called()

    def test_no_arbitrary_cli(self):
        for option in (['--address', '8002a408'], ['--width', '24'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as reader:
                with self.assertRaises(SystemExit) as exc:
                    a.main()
                self.assertEqual(exc.exception.code, 2)
                reader.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(path.is_file() for path in paths):
            raise unittest.SkipTest('both existing local archived snapshots required')
        cls.results = []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream:
                data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))

    def test_full_selected_coverage_and_cross_snapshot_identity(self):
        self.assertEqual({result['snapshot_sha256'] for result in self.results}, set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        for result in self.results:
            self.assertEqual(result['ranges'][0]['instructions'], EXPECTED)
            self.assertEqual(result['initializer_settings'], a.initializer_settings(EXPECTED))
            self.assertEqual(result['selected_coverage'], dict(start='8002a408', end_exclusive='8002a420',
                             represented_instructions=6, unrepresented_instructions=0))
            self.assertFalse(result['owner_function']['whole_function_covered'])
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            for item in result['ranges'] + result['ranges'][0]['instructions']:
                self.assertTrue(set(item).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes')))

    def test_each_instruction_mutation_rejected_before_decode(self):
        # Re-encode the explicit expected operands, not an archived payload fixture.
        payload = struct.pack('>6I', d_form(14, 3, 0, 6), d_form(25, 3, 3, 6), spr_form(467, 3, 916),
                              d_form(14, 3, 0, 7), d_form(25, 3, 3, 7), spr_form(467, 3, 917))
        pc, width, _ = a.RANGES[0]
        for offset in range(width):
            for bit in range(8):
                changed = bytearray(payload)
                changed[offset] ^= 1 << bit
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(changed), 21, pc, width)
                    decoder.assert_not_called()


if __name__ == '__main__':
    unittest.main()
