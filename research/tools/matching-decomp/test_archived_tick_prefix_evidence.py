#!/usr/bin/env python3
"""Fixed tick/source-order anchors and fail-closed controls; no execution."""
import contextlib
import copy
import hashlib
import io
from pathlib import Path
import unittest
from unittest.mock import patch

import read_archived_tick_prefix_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


class SyntheticTests(unittest.TestCase):
    def test_fixed_extents_and_explicit_support_gap(self):
        self.assertEqual([(pc, size, pc + size) for pc, size, _ in a.RANGES],
                         [(0x80059068, 208, 0x80059138), (0x80067a70, 80, 0x80067ac0),
                          (0x80067d58, 24, 0x80067d70)])
        self.assertEqual(sum(size // 4 for _, size, _ in a.RANGES), 78)
        self.assertEqual((0x80067d58 - 0x80067ac0) // 4, 166)

    def test_single_division_preserves_direction_and_rejects_reserved_forms(self):
        word = (59 << 26) | (2 << 21) | (3 << 16) | (4 << 11) | (18 << 1)
        self.assertEqual(a.decode_selected(word, 0), dict(mnemonic='fdivs', fD=2, fA=3, fB=4))
        for bad in (word | 1, word | (1 << 6)):
            with self.assertRaisesRegex(a.c.FormatError, 'single arithmetic'):
                a.decode_selected(bad, 0)
        for op, xo in ((63, 18), (59, 20), (59, 21), (59, 25), (59, 29)):
            self.assertIsNone(a.decode_selected((op << 26) | (xo << 1), 0))

    def test_indexed_load_and_exact_indirect_call(self):
        word = (31 << 26) | (12 << 21) | (4 << 16) | (7 << 11) | (23 << 1)
        self.assertEqual(a.decode_selected(word, 0), dict(mnemonic='lwzx', rD=12, rA=4, rB=7))
        with self.assertRaisesRegex(a.c.FormatError, 'indexed-load'):
            a.decode_selected(word | 1, 0)
        self.assertEqual(a.decode_selected(0x4e800421, 0),
                         dict(mnemonic='bctrl', BO=20, BI=0, BH=0, LK=1))
        for bit in (0, 11, 16, 21):
            self.assertIsNone(a.decode_selected(0x4e800421 ^ (1 << bit), 0))
        self.assertEqual(a.decode_selected(spr_form(467, 12, 9), 0), dict(mnemonic='mtctr', rS=12))
        self.assertEqual(a.decode_selected(spr_form(339, 0, 8), 0), dict(mnemonic='mflr', rD=0))
        self.assertEqual(a.decode_selected(spr_form(467, 0, 8), 0), dict(mnemonic='mtlr', rS=0))
        for bad in (spr_form(339, 0, 9), spr_form(467, 3, 9), spr_form(339, 1, 8),
                    spr_form(467, 0, 8, 1)):
            with self.assertRaisesRegex(a.c.FormatError, 'SPR'): a.decode_selected(bad, 0)

    def test_memory_signedness_mask_fields_and_record_bit(self):
        for op, name, key in ((32, 'lwz', 'rD'), (34, 'lbz', 'rD'), (36, 'stw', 'rS'),
                              (37, 'stwu', 'rS'), (38, 'stb', 'rS'), (48, 'lfs', 'fD'),
                              (52, 'stfs', 'fS')):
            self.assertEqual(a.decode_selected(d_form(op, 7, 3, -1), 0),
                             dict(mnemonic=name, **{key: 7}, rA=3, displacement=-1))
        mask = (21 << 26) | (3 << 21) | (3 << 16) | (12 << 6) | (10 << 1)
        self.assertEqual(a.decode_selected(mask, 0),
                         dict(mnemonic='rlwinm', rS=3, rA=3, SH=0, MB=12, ME=10, Rc=0))
        ext = (31 << 26) | (954 << 1) | 1
        self.assertEqual(a.decode_selected(ext, 0), dict(mnemonic='extsb', rS=0, rA=0, Rc=1))
        with self.assertRaisesRegex(a.c.FormatError, 'sign-extension'):
            a.decode_selected(ext | (1 << 11), 0)
        for op in (10, 11):
            self.assertEqual(a.decode_selected(d_form(op, 0, 31, 0), 0),
                             dict(mnemonic='cmpli' if op == 10 else 'cmpi', BF=0, L=0, rA=31, immediate=0))
            with self.assertRaisesRegex(a.c.FormatError, 'comparison'):
                a.decode_selected(d_form(op, 1, 31, 0), 0)

    def test_bounds_and_unselected_forms(self):
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)
        for word in (0, d_form(40, 3, 4, 0), d_form(44, 3, 4, 0), (31 << 26) | (266 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))

    def test_fixed_reads_hash_before_decode_and_no_silent_omission(self):
        pc, size, _ = a.RANGES[0]
        for address, width in ((pc + 4, size - 4), (pc, size - 4), (pc, size + 4),
                               (0x80067ac0, 664), (0x80067a70, 768)):
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

    def test_authentication_precedes_parsing_and_reads(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as reader:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); reader.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty',
                       'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_mapping_guards_precede_fixed_reads(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image', 'data5'):
            aa, bb, ss = copy.deepcopy((auth, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'data5': ss[7][4] += 1
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called()

    def test_cli_rejects_addresses_raw_and_execution(self):
        for option in (['--address', '80059068'], ['--width', '208'], ['--raw'], ['--execute']):
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

    def mem(self, pc, name, offset, reg=0, base=31):
        key = 'fS' if name == 'stfs' else 'fD' if name == 'lfs' else 'rS' if name.startswith('st') else 'rD'
        self.f(pc, name, **{key: reg}, rA=base, displacement=offset)

    def test_both_archives_counts_hashes_traces_and_explicit_coverage(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['function_coverage'], self.results[1]['function_coverage'])
        self.assertEqual(len(self.facts), 78)
        traces = ((42, 342664, 15104, 719622), (46, 402576, 9504, 779558), (46, 403320, 10248, 780302))
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
            self.assertEqual(result['constants'], [])
            tick, support = result['function_coverage']
            self.assertEqual(tick['represented_instructions'], 52)
            self.assertEqual(tick['unrepresented_instructions'], 0)
            self.assertEqual(tick['unrepresented_ranges'], [])
            self.assertEqual(support['represented_instructions'], 26)
            self.assertEqual(support['unrepresented_instructions'], 166)
            self.assertEqual(support['unrepresented_ranges'],
                             [dict(address='80067ac0', end_exclusive='80067d58', width=664)])
        self.assertFalse(any(pc in self.facts for pc in range(0x80067ac0, 0x80067d58, 4)))

    def test_actual_scalar_divisions_have_separate_denominator_loads_and_stores(self):
        self.f(0x80059078, 'or', rS=3, rA=31, rB=3, Rc=0)
        for pc, offset in ((0x8005907c, 0x760), (0x8005908c, 0x764)):
            self.mem(pc, 'lfs', offset, 1, 3)
            self.mem(pc + 4, 'lfs', 0xb4, 0, 3)
            self.f(pc + 8, 'fdivs', fD=0, fA=1, fB=0)
            self.mem(pc + 12, 'stfs', offset, 0, 3)
        prefix = [self.facts[pc] for pc in range(0x8005907c, 0x8005909c, 4)]
        self.assertEqual([f['mnemonic'] for f in prefix], ['lfs', 'lfs', 'fdivs', 'stfs'] * 2)
        self.assertEqual(len([f for f in prefix if f.get('displacement') == 0xb4]), 2)

    def test_first_three_calls_same_actor_and_complete_tick_call_order(self):
        for pc, target in ((0x8005909c, '8005bab8'), (0x800590a4, '80067a70'), (0x800590ac, '80059e58')):
            self.f(pc, 'bl', target=target, AA=0)
        for pc in (0x800590a0, 0x800590a8):
            self.f(pc, 'or', rS=31, rA=3, rB=31, Rc=0)
        self.assertEqual([(f'{pc:08x}', f['target']) for pc, f in self.facts.items() if f['mnemonic'] == 'bl'],
                         [('8005909c', '8005bab8'), ('800590a4', '80067a70'), ('800590ac', '80059e58'),
                          ('800590b4', '800685c0'), ('800590bc', '8005a190'), ('80059100', '80059f5c'),
                          ('80059108', '8005a144'), ('80059110', '8005a298'), ('80059118', '8005a378'),
                          ('80059120', '80068030')])

    def test_downstream_dispatch_is_evidence_not_implemented_prefix(self):
        self.f(0x800590c0, 'cmpi', BF=0, L=0, rA=3, immediate=0)
        self.f(0x800590c4, 'bc', BO=4, BI=2, LK=0, target='8005910c', AA=0)
        self.mem(0x800590c8, 'lbz', 0x5e4)
        self.f(0x800590cc, 'addis', rD=3, rA=0, immediate=-32723)
        self.f(0x800590d0, 'addi', rD=4, rA=3, immediate=0x3300)
        self.f(0x800590d8, 'extsb', rS=0, rA=0, Rc=0)
        self.f(0x800590dc, 'rlwinm', rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0)
        self.f(0x800590e0, 'lwzx', rD=12, rA=4, rB=0)
        self.mem(0x800590ec, 'lwz', 0x4c8, 12)
        for pc in (0x800590e4, 0x800590f4): self.f(pc, 'mtctr', rS=12)
        for pc in (0x800590e8, 0x800590f8): self.f(pc, 'bctrl', BO=20, BI=0, BH=0, LK=1)

    def test_support_writes_precede_all_short_circuit_reads(self):
        self.f(0x80067a7c, 'addi', rD=0, rA=0, immediate=0)
        self.f(0x80067a88, 'or', rS=3, rA=30, rB=3, Rc=0)
        self.mem(0x80067a8c, 'lwz', 0x5e0, 3, 3)
        self.f(0x80067a90, 'rlwinm', rS=3, rA=3, SH=0, MB=12, ME=10, Rc=0)
        mask = sum(1 << (31 - bit) for bit in range(32) if bit >= 12 or bit <= 10)
        self.assertEqual(mask, 0xffefffff)
        self.mem(0x80067a94, 'stw', 0x5e0, 3, 30)
        self.mem(0x80067a98, 'stb', 0x598, 0, 30)
        self.mem(0x80067a9c, 'lbz', 0x1db, 0, 30)
        self.f(0x80067aa0, 'extsb', rS=0, rA=0, Rc=1)
        self.mem(0x80067aa8, 'lwz', 0x1e4, 31, 30)
        self.f(0x80067aac, 'cmpli', BF=0, L=0, rA=31, immediate=0)
        self.mem(0x80067ab4, 'lbz', 0, 0, 31)
        self.f(0x80067ab8, 'extsb', rS=0, rA=0, Rc=1)
        for pc in (0x80067aa4, 0x80067ab0, 0x80067abc):
            self.f(pc, 'bc', BO=12, BI=2, LK=0, target='80067d58', AA=0)
        body = [f for pc, f in self.facts.items() if 0x80067a70 <= pc < 0x80067d70]
        self.assertFalse(any(f['mnemonic'] in ('bl', 'bctrl') for f in body))
        self.assertEqual([(f['mnemonic'], f['displacement']) for f in body
                          if f['mnemonic'] in ('stw', 'stb') and f['rA'] != 1],
                         [('stw', 0x5e0), ('stb', 0x598)])

    def test_no_support_epilogue_returns_without_additional_actor_reads_or_writes(self):
        self.mem(0x80067d58, 'lwz', 148, 0, 1)
        self.mem(0x80067d5c, 'lwz', 140, 31, 1)
        self.mem(0x80067d60, 'lwz', 136, 30, 1)
        self.f(0x80067d64, 'mtlr', rS=0)
        self.f(0x80067d68, 'addi', rD=1, rA=1, immediate=144)
        self.f(0x80067d6c, 'blr')

    def test_one_bit_at_every_instruction_fails_hash_before_decode(self):
        for raw, (pc, width, _) in zip(self.raw_ranges, a.RANGES):
            for offset in range(0, width, 4):
                changed = bytearray(raw); changed[offset + 3] ^= 1
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(changed), 21, pc, width)
                    decoder.assert_not_called()


if __name__ == '__main__': unittest.main()
