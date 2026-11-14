#!/usr/bin/env python3
"""Fixed gauge/scale source anchors and bounded fail-closed controls; no execution."""
import contextlib
import copy
import hashlib
import io
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_gauge_scale_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


class SyntheticTests(unittest.TestCase):
    def test_fixed_extents(self):
        self.assertEqual([(pc, size, pc + size) for pc, size, _ in a.RANGES],
                         [(0x8003d3e8, 92, 0x8003d444), (0x8003d444, 92, 0x8003d4a0),
                          (0x8005bab8, 264, 0x8005bbc0)])

    def test_new_compare_and_negation_forms(self):
        neg = (31 << 26) | (4 << 21) | (3 << 16) | (104 << 1)
        self.assertEqual(a.decode_selected(neg, 0), dict(mnemonic='neg', rD=4, rA=3, Rc=0))
        for bad in (neg | 1, neg | (1 << 11)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        cmpu = (63 << 26) | (3 << 23) | (2 << 16) | (1 << 11)
        self.assertEqual(a.decode_selected(cmpu, 0), dict(mnemonic='fcmpu', crD=3, fA=2, fB=1))
        for bad in (cmpu | 1, cmpu | (1 << 21)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for bad in (spr_form(467, 3, 9), spr_form(339, 1, 8), spr_form(467, 0, 8, 1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)

    def test_single_separate_arithmetic_and_signed_memory(self):
        for op, name, key in ((42, 'lha', 'rD'), (44, 'sth', 'rS'), (38, 'stb', 'rS'),
                              (48, 'lfs', 'fD'), (52, 'stfs', 'fS'), (54, 'stfd', 'fS')):
            self.assertEqual(a.decode_selected(d_form(op, 7, 3, -1), 0),
                             dict(mnemonic=name, **{key: 7}, rA=3, displacement=-1))
        for xo, name in ((20, 'fsubs'), (21, 'fadds')):
            word = (59 << 26) | (2 << 21) | (3 << 16) | (4 << 11) | (xo << 1)
            self.assertEqual(a.decode_selected(word, 0), dict(mnemonic=name, fD=2, fA=3, fB=4))
            for bad in (word | 1, word | (1 << 6)):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
            self.assertIsNone(a.decode_selected((word & ~(63 << 26)) | (63 << 26), 0))
        mul = (59 << 26) | (2 << 21) | (3 << 16) | (4 << 6) | (25 << 1)
        self.assertEqual(a.decode_selected(mul, 0), dict(mnemonic='fmuls', fD=2, fA=3, fC=4))
        with self.assertRaises(a.c.FormatError): a.decode_selected(mul | (1 << 11), 0)
        for fused in (28, 29, 30, 31):
            self.assertIsNone(a.decode_selected((59 << 26) | (fused << 1), 0))
        conversion = (63 << 26) | (2 << 21) | (3 << 11) | (15 << 1)
        self.assertEqual(a.decode_selected(conversion, 0), dict(mnemonic='fctiwz', fD=2, fB=3))
        for bad in (conversion | 1, conversion | (1 << 16)):
            self.assertIsNone(a.decode_selected(bad, 0))

    def test_bounds_and_unselected_forms(self):
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)
        for word in (0, 0x4e800421, d_form(40, 3, 4, 0), (59 << 26) | (18 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))

    def test_fixed_reads_hash_before_decode_and_no_silent_omission(self):
        pc, size, _ = a.RANGES[0]
        for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4), (0, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, address, width)
        for vals in ((21.0, pc, size), (21, True, size), (21, pc, float(size))):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'): a.range_evidence(None, *vals)
        with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
            a.range_evidence(None, 22, pc, size)
        for raw, reason in ((bytes(size), 'digest'), (bytes(size - 4), 'byte width')):
            with patch.object(a, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), 21, pc, size)
                decoder.assert_not_called()
        raw = bytes(4)
        with patch.object(a, 'RANGES', ((pc, 4, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(raw), 21, pc, 4)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, pc, size)

    def test_constant_bits_width_mapping_and_allowlist(self):
        for pc, width, bits in a.TARGETS:
            raw = bytes.fromhex(bits)
            result = a.constant_evidence(FakeDB(raw), a.DATA5_MAPPING, pc, width)
            self.assertEqual(result['bits'], bits)
            for index in range(width):
                changed = bytearray(raw); changed[index] ^= 1
                with self.assertRaisesRegex(a.c.FormatError, 'bits mismatch'):
                    a.constant_evidence(FakeDB(changed), a.DATA5_MAPPING, pc, width)
            with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                a.constant_evidence(FakeDB(raw[:-1]), a.DATA5_MAPPING, pc, width)
        for pc, width in ((0x80436f80, 4), (0x80436f88, 4), (0x80437420, 8)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, pc, width)
        with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
            a.constant_evidence(None, a.DATA5_MAPPING[:-1] + (264,), 0x80437420, 4)

    def test_authentication_precedes_parsing_and_reads(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); reader.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty', 'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_mapping_guards_precede_fixed_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image'):
            aa, bb, ss = copy.deepcopy((auth, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': aa['image_offset'] = '80000004'
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'constant_evidence') as constants:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called(); constants.assert_not_called()

    def test_cli_rejects_addresses_raw_and_execution(self):
        for option in (['--address', '8003d3e8'], ['--width', '92'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + option), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as error: a.main()
                self.assertEqual(error.exception.code, 2); inspect.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        base = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(path.is_file() for path in paths):
            raise unittest.SkipTest('both existing local archived snapshots are required')
        cls.results, cls.raw_ranges = [], []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
            if not cls.raw_ranges:
                db = a.c.GBF(data)  # authenticated above; never written as executable fixtures
                cls.raw_ranges = [db.chain(21, pc - a.TEXT_START, size, a.TEXT_LENGTH)[0]
                                  for pc, size, _ in a.RANGES]
        cls.facts = {int(f['address'], 16): f for r in cls.results[0]['ranges'] for f in r['instructions']}

    def f(self, pc, name, **fields):
        self.assertEqual(self.facts[pc], dict(address=f'{pc:08x}', mnemonic=name, **fields))

    def branch(self, pc, bo, bi, target):
        self.f(pc, 'bc', BO=bo, BI=bi, LK=0, target=f'{target:08x}', AA=0)

    def mem(self, pc, name, offset, reg=0, base=31):
        key = 'fS' if name in ('stfs', 'stfd') else 'fD' if name in ('lfs', 'lfd') else 'rS' if name.startswith('st') else 'rD'
        self.f(pc, name, **{key: reg}, rA=base, displacement=offset)

    def test_both_archives_complete_counts_hashes_and_physical_traces(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['constants'], self.results[1]['constants'])
        self.assertEqual(len(self.facts), 112)
        traces = ((35, 228872, 15958, 605788), (35, 228964, 16050, 605880), (43, 353496, 9558, 730460))
        for span, (pc, width, digest), trace in zip(self.results[0]['ranges'], a.RANGES, traces):
            self.assertEqual([int(f['address'], 16) for f in span['instructions']], list(range(pc, pc + width, 4)))
            self.assertEqual(span['end_exclusive'], f'{pc + width:08x}')
            self.assertEqual(span['sha256'], digest)
            self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=trace[0], chain_offset=trace[1],
                                                data_offset=trace[2], physical_offset=trace[3], length=width, obfuscated=True)])
            for item in [span] + span['instructions']:
                self.assertTrue(set(item).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes')))
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertIn('not proof of unchanged original', result['executable_metadata_caveat'])

    def test_constants_and_recorded_r2_displacements(self):
        values = (4503601774854144.0, 0.5, 1.0, 0.05000000074505806)
        for fact, (pc, width, bits), value in zip(self.results[0]['constants'], a.TARGETS, values):
            offset = pc - 0x80436a20
            self.assertEqual((fact['bits'], fact['value']), (bits, value))
            self.assertEqual(fact['spans'], [dict(root_buffer=263, data_buffer=264, chain_offset=offset,
                                                data_offset=offset, physical_offset=4341766 + offset,
                                                length=width, obfuscated=True)])
            self.assertEqual(self.results[0]['r2_basis']['displacements'][f'{pc:08x}'], pc - 0x8043ea20)

    def test_reset_pair_separate_rounding_conversion_then_short_wrap(self):
        for pc, source, target in ((0x8003d3e8, 0x6c4, 0x6c6), (0x8003d444, 0x7d6, 0x7dc)):
            self.mem(pc + 8, 'lfs', -31400, 0, 2)
            self.mem(pc + 12, 'lha', source, 5, 3)
            self.mem(pc + 16, 'lfs', 0xb4, 1, 3)
            self.f(pc + 20, 'xoris', rS=5, rA=4, immediate=0x8000)
            self.f(pc + 28, 'fsubs', fD=0, fA=1, fB=0)
            self.mem(pc + 32, 'lfs', -31396, 1, 2)
            self.mem(pc + 40, 'lfd', -31384, 3, 2)
            self.f(pc + 48, 'fmuls', fD=0, fA=1, fC=0)
            self.f(pc + 52, 'fsubs', fD=1, fA=2, fB=3)
            self.f(pc + 56, 'fmuls', fD=0, fA=1, fC=0)
            self.f(pc + 60, 'fctiwz', fD=0, fB=0)
            self.mem(pc + 64, 'stfd', 16, 0, 1)
            self.mem(pc + 68, 'lwz', 20, 0, 1)
            self.f(pc + 72, 'extsh', rS=0, rA=0, Rc=0)
            self.f(pc + 76, 'add', rD=0, rA=5, rB=0, Rc=0)
            self.mem(pc + 80, 'sth', target, 0, 3)
            body = [f for addr, f in self.facts.items() if pc <= addr < pc + 92]
            self.assertEqual([f['mnemonic'] for f in body if f['mnemonic'].startswith('f')],
                             ['fsubs', 'fmuls', 'fsubs', 'fmuls', 'fctiwz'])
            self.assertEqual(len([f for f in body if f.get('rA') == 3 and f['mnemonic'] == 'lha']), 1)

    def test_tier_expiry_signed_decrement_store_before_call_then_clears(self):
        self.mem(0x8005bacc, 'lha', 0x750, 4, 3)
        self.f(0x8005bad0, 'cmpi', BF=0, L=0, rA=4, immediate=0)
        self.branch(0x8005bad4, 4, 1, 0x8005bb04)
        self.f(0x8005bad8, 'addi', rD=4, rA=4, immediate=-1)
        self.f(0x8005badc, 'extsh', rS=4, rA=0, Rc=1)
        self.mem(0x8005bae0, 'sth', 0x750, 4)
        self.branch(0x8005bae4, 12, 1, 0x8005bb04)
        self.mem(0x8005bae8, 'lbz', 0x74e)
        self.f(0x8005baec, 'extsb', rS=0, rA=0, Rc=0)
        self.f(0x8005baf0, 'neg', rD=4, rA=0, Rc=0)
        self.f(0x8005baf4, 'bl', target='8006817c', AA=0)
        self.f(0x8005baf8, 'addi', rD=0, rA=0, immediate=0)
        self.mem(0x8005bafc, 'sth', 0x750)
        self.mem(0x8005bb00, 'stb', 0x74e)

    def test_scale_gates_direction_store_reload_and_clamp_call_order(self):
        self.mem(0x8005bb04, 'lfs', 0xb8)
        self.mem(0x8005bb08, 'lfs', 0xb4, 1)
        self.f(0x8005bb0c, 'fcmpu', crD=0, fA=0, fB=1)
        self.branch(0x8005bb10, 12, 2, 0x8005bbac)
        self.mem(0x8005bb14, 'lbz', 0x7c9)
        self.f(0x8005bb18, 'extsb', rS=0, rA=0, Rc=1)
        self.branch(0x8005bb1c, 4, 2, 0x8005bbac)
        self.f(0x8005bb20, 'fcmpo', crD=0, fA=0, fB=1)
        self.branch(0x8005bb24, 4, 1, 0x8005bb58)
        for pc, op, bit in ((0x8005bb28, 'fadds', 0), (0x8005bb58, 'fsubs', 1)):
            self.mem(pc, 'lfs', -30208, 0, 2)
            self.f(pc + 4, op, fD=0, fA=1, fB=0)
            self.mem(pc + 8, 'stfs', 0xb4)
            self.mem(pc + 12, 'lfs', 0xb8, 1)
            self.mem(pc + 16, 'lfs', 0xb4)
            self.f(pc + 20, 'fcmpo', crD=0, fA=1, fB=0)
            self.f(pc + 24, 'cror', crD=2, crA=bit, crB=2)
            self.branch(pc + 28, 4, 2, 0x8005bb84)
            self.mem(pc + 32, 'stfs', 0xb4, 1)
            self.f(pc + 40, 'bl', target='8003d3e8', AA=0)

    def test_five_separate_scale_loads_stores_and_exact_call_set(self):
        for index, offset in enumerate((0x58, 0x5c, 0x60, 0xc0, 0xc4)):
            self.mem(0x8005bb84 + index * 8, 'lfs', 0xb4)
            self.mem(0x8005bb88 + index * 8, 'stfs', offset)
        self.assertEqual({pc: f['target'] for pc, f in self.facts.items() if f['mnemonic'] == 'bl'},
                         {0x8005baf4: '8006817c', 0x8005bb50: '8003d3e8', 0x8005bb80: '8003d3e8'})

    def test_one_bit_at_every_instruction_fails_hash_before_decode(self):
        for raw, (pc, width, _) in zip(self.raw_ranges, a.RANGES):
            for offset in range(0, width, 4):
                changed = bytearray(raw); changed[offset + 3] ^= 1
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(changed), 21, pc, width)
                    decoder.assert_not_called()


if __name__ == '__main__': unittest.main()
