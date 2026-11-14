#!/usr/bin/env python3
"""Fixed-source field/order checks and synthetic fail-closed controls; no execution."""
import contextlib
import copy
import hashlib
import io
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_actor_status_evidence as a
from test_archived_actor_attribute_evidence import FakeDB, d_form, spr_form


def x_form(xo, d=3, ra=4, rb=5, rc=0):
    return (31 << 26) | (d << 21) | (ra << 16) | (rb << 11) | (xo << 1) | rc


class SyntheticTests(unittest.TestCase):
    def test_scalar_width_sign_and_store_direction(self):
        for op, name, reg in ((34, 'lbz', 'rD'), (42, 'lha', 'rD'), (38, 'stb', 'rS'),
                              (44, 'sth', 'rS'), (36, 'stw', 'rS'), (52, 'stfs', 'fS'),
                              (54, 'stfd', 'fS')):
            for offset in (-32768, -1, 0, 32767):
                self.assertEqual(a.decode_selected(d_form(op, 7, 3, offset), 0),
                                 dict(mnemonic=name, **{reg: 7}, rA=3, displacement=offset))
        self.assertEqual(a.decode_selected(x_form(922, 3, 4, 0), 0),
                         dict(mnemonic='extsh', rS=3, rA=4, Rc=0))
        self.assertIsNone(a.decode_selected(d_form(40, 3, 4, 5), 0))  # no unsigned-short fallback

    def test_indexed_widths_and_reserved_bit(self):
        for xo, name, reg in ((87, 'lbzx', 'rD'), (151, 'stwx', 'rS'), (215, 'stbx', 'rS')):
            self.assertEqual(a.decode_selected(x_form(xo), 0),
                             dict(mnemonic=name, **{reg: 3}, rA=4, rB=5))
            with self.assertRaises(a.c.FormatError): a.decode_selected(x_form(xo, rc=1), 0)

    def test_new_integer_forms_keep_operand_direction_and_record(self):
        for xo, name in ((40, 'subf'), (75, 'mulhw')):
            for rc in (0, 1):
                self.assertEqual(a.decode_selected(x_form(xo, rc=rc), 0),
                                 dict(mnemonic=name, rD=3, rA=4, rB=5, Rc=rc))
        self.assertEqual(a.decode_selected(x_form(60, rc=1), 0),
                         dict(mnemonic='andc', rS=3, rA=4, rB=5, Rc=1))
        self.assertEqual(a.decode_selected(x_form(824), 0),
                         dict(mnemonic='srawi', rS=3, rA=4, SH=5, Rc=0))
        self.assertEqual(a.decode_selected(d_form(27, 4, 0, 0x8000), 0),
                         dict(mnemonic='xoris', rS=4, rA=0, immediate=32768))
        self.assertEqual(a.decode_selected(d_form(8, 4, 8, 7), 0),
                         dict(mnemonic='subfic', rD=4, rA=8, immediate=7))

    def test_condition_register_and_single_arithmetic(self):
        cmpword = (63 << 26) | (3 << 23) | (2 << 16) | (1 << 11) | (32 << 1)
        self.assertEqual(a.decode_selected(cmpword, 0), dict(mnemonic='fcmpo', crD=3, fA=2, fB=1))
        crword = (19 << 26) | (2 << 21) | (1 << 16) | (2 << 11) | (449 << 1)
        self.assertEqual(a.decode_selected(crword, 0), dict(mnemonic='cror', crD=2, crA=1, crB=2))
        for bad in (cmpword | 1, cmpword | (1 << 21), crword | 1):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for xo, name in ((18, 'fdivs'), (20, 'fsubs'), (21, 'fadds')):
            word = (59 << 26) | (7 << 21) | (3 << 16) | (5 << 11) | (xo << 1)
            self.assertEqual(a.decode_selected(word, 0), dict(mnemonic=name, fD=7, fA=3, fB=5))
            for bad in (word | 1, word | (1 << 6)):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
            self.assertIsNone(a.decode_selected((word & ~(63 << 26)) | (63 << 26), 0))
        mul = (59 << 26) | (7 << 21) | (3 << 16) | (5 << 6) | (25 << 1)
        self.assertEqual(a.decode_selected(mul, 0), dict(mnemonic='fmuls', fD=7, fA=3, fC=5))
        with self.assertRaises(a.c.FormatError): a.decode_selected(mul | (1 << 11), 0)

    def test_spr_scope_and_branch_conditions(self):
        self.assertEqual(a.decode_selected(spr_form(339), 0), dict(mnemonic='mflr', rD=0))
        self.assertEqual(a.decode_selected(spr_form(467), 0), dict(mnemonic='mtlr', rS=0))
        self.assertEqual(a.decode_selected(spr_form(467, 3, 9), 0), dict(mnemonic='mtctr', rS=3))
        for word in (spr_form(339, 0, 9), spr_form(467, 0, 256), spr_form(467, 1, 8), spr_form(467, 0, 9, 1)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        self.assertEqual(a.decode_selected((16 << 26) | (16 << 21) | 0xfffc, 0x8006de04),
                         dict(mnemonic='bc', BO=16, BI=0, LK=0, target='8006de00', AA=0))
        for word in (0, 0x4e800421, 0x4e800021, (4 << 26) | (21 << 1)):
            self.assertIsNone(a.decode_selected(word, 0))
        for word in (-1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, pc)

    def test_fixed_ranges_only_and_hash_before_decode(self):
        for address, width in ((0x80055690, 1852), (0x8005568c, 1852), (0x8006dcc0, 340), (0, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, address, width)
        for vals in ((21.0, 0x8005568c, 1856), (21, True, 1856), (21, 0x8005568c, 1856.0)):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'): a.range_evidence(None, *vals)
        with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
            a.range_evidence(None, 22, 0x8005568c, 1856)
        for raw, error in ((bytes(1856), 'digest'), (bytes(1852), 'byte width')):
            with patch.object(a, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, error):
                    a.range_evidence(FakeDB(raw), 21, 0x8005568c, 1856)
                decoder.assert_not_called()
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, 0x8005568c, 1856)

    def test_complete_decode_does_not_silently_omit(self):
        for word in (0, 0x4e800421):
            raw = struct.pack('>I', word)
            with patch.object(a, 'RANGES', ((0x8005568c, 4, hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                    a.range_evidence(FakeDB(raw), 21, 0x8005568c, 4)
        raw = struct.pack('>2I', d_form(44, 7, 5, 2), 0x4e800020)
        with patch.object(a, 'RANGES', ((0x8005568c, 8, hashlib.sha256(raw).hexdigest()),)):
            result = a.range_evidence(FakeDB(raw), 21, 0x8005568c, 8)
        self.assertEqual([f['address'] for f in result['instructions']], ['8005568c', '80055690'])
        self.assertEqual([f['mnemonic'] for f in result['instructions']], ['sth', 'blr'])

    def test_constants_are_four_fixed_bit_patterns(self):
        for address, width, bits in a.TARGETS:
            raw = bytes.fromhex(bits)
            result = a.constant_evidence(FakeDB(raw), a.DATA5_MAPPING, address, width)
            self.assertEqual(result['bits'], bits)
            for index in range(width):
                changed = bytearray(raw); changed[index] ^= 1
                with self.assertRaisesRegex(a.c.FormatError, 'bits mismatch'):
                    a.constant_evidence(FakeDB(changed), a.DATA5_MAPPING, address, width)
            with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                a.constant_evidence(FakeDB(raw[:-1]), a.DATA5_MAPPING, address, width)
        for address, width in ((0x80437254, 4), (0x80437250, 8), (0x804376a0, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, address, width)
        with self.assertRaisesRegex(a.c.FormatError, 'mapping mismatch'):
            a.constant_evidence(None, a.DATA5_MAPPING[:-1] + (264,), 0x80437250, 4)

    def test_authentication_precedes_new_reads(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as evidence:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(bytes(32), digest)
                parser.assert_not_called(); evidence.assert_not_called()
        for error in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty', 'data5 digest mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(error)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, error): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_mapping_mutations_precede_ranges_and_constants(self):
        auth = dict.fromkeys(('snapshot', 'snapshot_sha256', 'program_name', 'created_with_ghidra_version',
                             'executable_sha256_metadata', 'executable_sha256_property_type',
                             'executable_metadata_caveat', 'file_bytes_table', 'block_size',
                             'master_root', 'table_roots', 'data5_sha256'), 'synthetic')
        auth['image_offset'] = '80000000'
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

    def test_cli_cannot_request_addresses_raw_or_execution(self):
        for option in (['--address', '8005568c'], ['--width', '1856'], ['--raw'], ['--execute']):
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
                db = a.c.GBF(data)  # already authenticated above; retain no raw fixture on disk
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

    def test_both_snapshots_full_548_instructions_same_traces(self):
        self.assertEqual({r['snapshot_sha256'] for r in self.results}, set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(self.results[0]['constants'], self.results[1]['constants'])
        self.assertEqual(len(self.facts), 548)
        for span, (pc, width, digest), trace in zip(self.results[0]['ranges'], a.RANGES,
                                                  ((42, 327852, 292, 704810), (48, 427744, 1916, 804738))):
            self.assertEqual([int(f['address'], 16) for f in span['instructions']], list(range(pc, pc + width, 4)))
            self.assertEqual(span['sha256'], digest)
            self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=trace[0], chain_offset=trace[1],
                                                data_offset=trace[2], physical_offset=trace[3], length=width, obfuscated=True)])
        for result in self.results:
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertIn('not proof of unchanged original', result['executable_metadata_caveat'])
            for span in result['ranges']:
                for item in [span] + span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes')))

    def test_every_instruction_mutation_fails_before_decode(self):
        for raw, (pc, width, _) in zip(self.raw_ranges, a.RANGES):
            for offset in range(0, width, 4):
                mutated = bytearray(raw); mutated[offset + 3] ^= 1
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(mutated), 21, pc, width)
                    decoder.assert_not_called()

    def test_constants_have_exact_identity_bits_values_and_trace(self):
        self.assertEqual([(v['address'], v['bits'], v['value']) for v in self.results[0]['constants']],
                         [('80437250', '00000000', 0.0), ('80437658', '00000000', 0.0),
                          ('804376c8', '41200000', 10.0), ('804376a0', '4330000080000000', 2**52 + 2**31)])
        for v, offset in zip(self.results[0]['constants'], (2096, 3128, 3240, 3200)):
            self.assertEqual(v['spans'], [dict(root_buffer=263, data_buffer=264, chain_offset=offset,
                                              data_offset=offset, physical_offset=4341766 + offset,
                                              length=v['width'], obfuscated=True)])

    def test_state_timer_retains_entry_operand_then_reloads_store(self):
        self.mem(0x800556a4, 'lwz', 0x5e0, base=3)
        self.f(0x800556a8, 'rlwinm', rS=0, rA=0, SH=0, MB=30, ME=31, Rc=1)
        self.branch(0x800556ac, 4, 2, 0x800556f4)
        self.mem(0x800556b0, 'lfs', 0x694, 2)
        self.mem(0x800556b4, 'lfs', -30672, 1, 2)
        self.f(0x800556b8, 'fcmpo', crD=0, fA=2, fB=1)
        self.branch(0x800556bc, 4, 1, 0x800556f4)
        self.mem(0x800556c0, 'lfs', 0x1dc8)
        self.f(0x800556c4, 'fsubs', fD=0, fA=2, fB=0)
        self.mem(0x800556c8, 'stfs', 0x694)
        self.mem(0x800556cc, 'lfs', 0x694)
        self.f(0x800556d0, 'fcmpo', crD=0, fA=0, fB=1)
        self.f(0x800556d4, 'cror', crD=2, crA=0, crB=2)
        self.branch(0x800556d8, 4, 2, 0x800556f4)
        self.mem(0x800556dc, 'stfs', 0x694, 1)
        self.mem(0x800556e4, 'lwz', 0x5e0, 3)
        self.f(0x800556e8, 'rlwinm', rS=3, rA=3, SH=0, MB=0, ME=29, Rc=0)
        self.mem(0x800556ec, 'stw', 0x5e0, 3)
        self.mem(0x800556f0, 'stb', 0x73f)

    def test_five_rate_timers_order_fresh_rate_strict_negative_clamp(self):
        for pc, offset in zip(range(0x800556f4, 0x800557d0, 44), (0x690, 0x698, 0x69c, 0x6a0, 0x6a4)):
            self.mem(pc, 'lfs', offset, 2); self.mem(pc + 4, 'lfs', -30672, 1, 2)
            self.f(pc + 8, 'fcmpo', crD=0, fA=2, fB=1); self.branch(pc + 12, 4, 1, pc + 44)
            self.mem(pc + 16, 'lfs', 0x768)
            self.f(pc + 20, 'fsubs', fD=0, fA=2, fB=0)
            self.mem(pc + 24, 'stfs', offset); self.mem(pc + 28, 'lfs', offset)
            self.f(pc + 32, 'fcmpo', crD=0, fA=0, fB=1)
            self.branch(pc + 36, 4, 0, pc + 44); self.mem(pc + 40, 'stfs', offset, 1)

    def test_byte_short_wrapping_and_poison_signed_reload(self):
        self.mem(0x800557d0, 'lbz', 0x6fc)
        self.mem(0x800557e0, 'stb', 0x7de)
        self.mem(0x800557fc, 'lha', 0x6b8, 3)
        self.mem(0x80055808, 'lbz', 0x4a1)
        self.mem(0x80055820, 'lbz', 0x71c)
        self.f(0x80055824, 'cmpli', BF=0, L=0, rA=0, immediate=0)
        self.f(0x8005582c, 'addi', rD=0, rA=3, immediate=-1)
        self.mem(0x80055830, 'sth', 0x6b8)
        for pc, offset in ((0x80055834, 0x656), (0x80055848, 0x593), (0x8005585c, 0x594), (0x80055870, 0x596)):
            self.mem(pc, 'lbz', offset, 3)
            self.f(pc + 4, 'extsb', rS=3, rA=0, Rc=1)
            self.branch(pc + 8, 12, 2, pc + 20)
            self.f(pc + 12, 'addi', rD=0, rA=3, immediate=-1); self.mem(pc + 16, 'stb', offset)
        self.f(0x800558b0, 'extsh', rS=0, rA=4, Rc=0)
        self.mem(0x800558b4, 'sth', 0x6ba)
        self.f(0x800558bc, 'mulhw', rD=0, rA=0, rB=4, Rc=0)
        self.f(0x800558c4, 'srawi', rS=0, rA=0, SH=4, Rc=0)
        self.f(0x800558d0, 'mulli', rD=0, rA=0, immediate=30)
        self.f(0x800558d4, 'subf', rD=0, rA=0, rB=4, Rc=1)
        self.mem(0x800558f0, 'lha', 0x6ba)
        self.branch(0x800558f8, 12, 1, 0x80055908)
        self.f(0x80055900, 'rlwinm', rS=0, rA=0, SH=0, MB=30, ME=28, Rc=0)

    def test_six_counters_are_three_unrolled_entries_times_two(self):
        self.f(0x80055908, 'addi', rD=0, rA=0, immediate=2)
        self.f(0x80055918, 'mtctr', rS=0)
        for pc in (0x8005591c, 0x80055964, 0x800559ac):
            self.f(pc + 4, 'slw', rS=5, rA=3, rB=7, Rc=0)
            self.mem(pc + 20, 'lbz', 0x709)
            self.f(pc + 40, 'stbx', rS=4, rA=31, rB=0)
            self.f(pc + 48, 'lbzx', rD=3, rA=31, rB=6)
            self.f(pc + 64, 'stbx', rS=0, rA=31, rB=6)
        self.branch(0x800559f4, 16, 0, 0x8005591c)
        for pc, offset, reg in ((0x800559f8, 0x709, 4), (0x800559fc, 0x708, 3), (0x80055a00, 0x707, 0)):
            self.mem(pc, 'lbz', offset, reg)
        self.f(0x80055a14, 'andc', rS=3, rA=0, rB=0, Rc=1)
        self.branch(0x80055a18, 12, 2, 0x80055a2c)

    def test_refill_cap_happens_after_signed_short_store_and_reload(self):
        for pc, target in ((0x80055a70, 0x80055a9c), (0x80055acc, 0x80055af8)):
            self.mem(pc, 'lwz', 0x4ac, 3); self.mem(pc + 4, 'lha', 0x736, 4)
            self.mem(pc + 8, 'lha', 8, 0, 3)
            self.f(pc + 12, 'add', rD=0, rA=4, rB=0, Rc=0)
            self.mem(pc + 16, 'sth', 0x736); self.mem(pc + 20, 'lwz', 0x4ac, 3)
            self.mem(pc + 24, 'lha', 0x736); self.mem(pc + 28, 'lha', 4, 3, 3)
            self.f(pc + 32, 'cmp', BF=0, L=0, rA=0, rB=3)
            self.branch(pc + 36, 4, 1, target); self.mem(pc + 40, 'sth', 0x736, 3)
        for pc in (0x80055a58, 0x80055ab4):
            self.mem(pc, 'lha', 0x73a, 3)
            self.f(pc + 4, 'cmpi', BF=0, L=0, rA=3, immediate=0)
            self.branch(pc + 8, 12, 2, pc + 24)
            self.mem(pc + 16, 'sth', 0x73a)
        self.mem(0x80055aa0, 'stb', 0x747)
        self.f(0x80055aac, 'rlwinm', rS=0, rA=0, SH=0, MB=24, ME=24, Rc=1)

    def test_timers_expire_in_order_and_720_outside_control_gate(self):
        self.f(0x80055afc, 'rlwinm', rS=0, rA=0, SH=0, MB=7, ME=7, Rc=1)
        self.branch(0x80055b00, 4, 2, 0x80055be8)
        for pc, offset in ((0x80055b04, 0x684), (0x80055b3c, 0x688), (0x80055b74, 0x7d8),
                           (0x80055bac, 0x68c), (0x80055be8, 0x720)):
            self.mem(pc, 'lfs', offset, 2); self.mem(pc + 16, 'lfs', 0x1dcc)
            self.f(pc + 20, 'fsubs', fD=0, fA=2, fB=0)
            self.mem(pc + 24, 'stfs', offset); self.mem(pc + 28, 'lfs', offset)
            self.f(pc + 36, 'cror', crD=2, crA=0, crB=2)
            self.mem(pc + 44, 'stfs', offset, 1)
        self.mem(0x80055b34, 'lha', 0x6be); self.mem(0x80055b38, 'sth', 0x6c2)
        self.mem(0x80055be0, 'sth', 0x6c8); self.mem(0x80055be4, 'stb', 0x6ca)
        self.mem(0x80055c1c, 'sth', 0x272)

    def test_child_lifecycle_signed_and_loop_advances_after_removal(self):
        self.mem(0x80055c2c, 'lwz', 0x440, 3, 7)
        self.mem(0x80055c38, 'lbz', 0x18, 0, 3)
        self.f(0x80055c3c, 'extsb', rS=0, rA=0, Rc=0)
        self.f(0x80055c40, 'cmpi', BF=0, L=0, rA=0, immediate=2)
        self.branch(0x80055c44, 12, 0, 0x80055cf0)
        self.f(0x80055ce0, 'stwx', rS=4, rA=31, rB=0)
        self.mem(0x80055cec, 'stb', 0x485)
        self.f(0x80055cf0, 'addi', rD=8, rA=8, immediate=1)
        self.f(0x80055cf8, 'cmpi', BF=0, L=0, rA=8, immediate=8)
        self.branch(0x80055d00, 12, 0, 0x80055c2c)

    def test_ammo_call_is_only_unconditional_callee_on_all_returning_paths(self):
        calls = {pc: f['target'] for pc, f in self.facts.items() if f['mnemonic'] == 'bl'}
        self.assertEqual(calls, {0x80055a28: '800f0104', 0x80055b70: '8003d3e8', 0x80055ba8: '8003d444',
                                 0x80055d08: '8006dcc0', 0x80055d58: '8005c290'})
        # Static overapproximation of branch edges; no source instruction execution.
        def reaches_return(removed):
            todo, seen = [0x8005568c], set()
            while todo:
                pc = todo.pop()
                if pc == removed or pc in seen: continue
                seen.add(pc); f = self.facts[pc]
                if f['mnemonic'] == 'blr': return True
                if f['mnemonic'] in ('b', 'bc'):
                    target = int(f['target'], 16)
                    self.assertTrue(0x8005568c <= target < 0x80055dcc)
                    todo.append(target)
                if f['mnemonic'] != 'b': todo.append(pc + 4)
            return False
        self.assertFalse(reaches_return(0x80055d08))
        for call in set(calls) - {0x80055d08}: self.assertTrue(reaches_return(call))
        self.assertFalse(any(f['mnemonic'] == 'bl' for pc, f in self.facts.items() if pc >= 0x8006dcc0))

    def test_ammo_retained_rate_then_pause_then_debt_then_mode(self):
        self.mem(0x8006dcc4, 'lbz', 0x6fc, 0, 3); self.mem(0x8006dcc8, 'lfs', 0x768, 3, 3)
        self.f(0x8006dccc, 'extsb', rS=0, rA=0, Rc=1); self.branch(0x8006dcd0, 12, 2, 0x8006dcdc)
        self.mem(0x8006dcd4, 'lfs', -29528, 0, 2); self.f(0x8006dcd8, 'fmuls', fD=3, fA=3, fC=0)
        self.f(0x8006dcdc, 'addi', rD=0, rA=0, immediate=3)
        self.f(0x8006dce0, 'addi', rD=6, rA=3, immediate=0x774)
        self.f(0x8006dce4, 'addi', rD=7, rA=3, immediate=0x78c)
        self.f(0x8006dcec, 'mtctr', rS=0)
        self.mem(0x8006dcf0, 'lbz', 0x597, 4, 3); self.branch(0x8006dd04, 4, 2, 0x8006ddf8)
        self.mem(0x8006dd08, 'lfs', 4, 1, 6); self.branch(0x8006dd14, 4, 1, 0x8006ddf8)
        self.mem(0x8006dd18, 'lha', 4, 0, 7)
        self.branch(0x8006dd20, 12, 2, 0x8006dd74); self.branch(0x8006dd24, 4, 0, 0x8006ddf8)
        self.branch(0x8006dd2c, 4, 0, 0x8006dd38)
        self.f(0x8006ddfc, 'addi', rD=6, rA=6, immediate=8)
        self.f(0x8006de00, 'addi', rD=7, rA=7, immediate=8)
        self.branch(0x8006de04, 16, 0, 0x8006dcf0)

    def test_mode0_debt_store_reload_two_max_reads_then_zero(self):
        self.f(0x8006dd40, 'fsubs', fD=0, fA=1, fB=3)
        self.mem(0x8006dd44, 'stfs', 4, 0, 6); self.mem(0x8006dd48, 'lfs', 4, 1, 6)
        self.f(0x8006dd54, 'cror', crD=2, crA=0, crB=2); self.branch(0x8006dd58, 4, 2, 0x8006ddf8)
        for pc in (0x8006dd5c, 0x8006dde8):
            self.mem(pc, 'lha', 2, 0, 7); self.mem(pc + 4, 'sth', 0, 0, 6)
            self.mem(pc + 8, 'lha', 2, 0, 7); self.mem(pc + 12, 'sth', 2, 0, 6)
        self.mem(0x8006dd6c, 'stfs', 4, 0, 6)
        self.assertFalse(any(f['mnemonic'] == 'stfs' for pc, f in self.facts.items() if 0x8006dde8 <= pc < 0x8006ddf8))

    def test_mode1_signed_bias_division_and_conditional_mirror(self):
        self.mem(0x8006dd80, 'stfs', 4, 0, 6); self.mem(0x8006dd84, 'lfs', 4, 2, 6)
        self.branch(0x8006dd90, 4, 1, 0x8006dde8)
        self.mem(0x8006dd94, 'lha', 6, 4, 7)
        self.f(0x8006dd98, 'addis', rD=0, rA=0, immediate=0x4330)
        self.mem(0x8006dd9c, 'stw', 8, 0, 1)
        self.f(0x8006dda0, 'xoris', rS=4, rA=0, immediate=0x8000)
        self.mem(0x8006dda4, 'lfd', -29568, 1, 2); self.mem(0x8006dda8, 'stw', 12, 0, 1)
        self.mem(0x8006ddac, 'lha', 2, 4, 7); self.mem(0x8006ddb0, 'lfd', 8, 0, 1)
        self.mem(0x8006ddb4, 'lha', 0, 0, 6)
        self.f(0x8006ddb8, 'fsubs', fD=0, fA=0, fB=1)
        self.f(0x8006ddbc, 'fdivs', fD=0, fA=2, fB=0)
        self.f(0x8006ddc0, 'fctiwz', fD=0, fB=0)
        self.f(0x8006ddcc, 'addi', rD=5, rA=5, immediate=1)
        self.f(0x8006ddd0, 'subf', rD=4, rA=5, rB=4, Rc=0)
        self.f(0x8006ddd4, 'cmp', BF=0, L=0, rA=0, rB=4)
        self.branch(0x8006ddd8, 12, 2, 0x8006ddf8)
        self.mem(0x8006dddc, 'sth', 0, 4, 6); self.mem(0x8006dde0, 'sth', 2, 4, 6)

    def test_final_refill_reaction_and_fb_accumulator_predicates(self):
        self.f(0x80055d10, 'rlwinm', rS=3, rA=0, SH=0, MB=0, ME=0, Rc=1)
        self.branch(0x80055d14, 4, 2, 0x80055d7c)
        self.mem(0x80055d18, 'lbz', 0x7d4); self.branch(0x80055d20, 12, 2, 0x80055d7c)
        self.f(0x80055d24, 'rlwinm', rS=3, rA=0, SH=0, MB=6, ME=6, Rc=1)
        self.branch(0x80055d28, 12, 2, 0x80055d64)
        self.mem(0x80055d5c, 'sth', 0x6b6, 30)
        self.mem(0x80055d64, 'lwz', 0x4ac, 3); self.mem(0x80055d6c, 'lha', 4, 3, 3)
        self.mem(0x80055d70, 'sth', 0x738, 3); self.mem(0x80055d74, 'sth', 0x736, 3)
        self.mem(0x80055d78, 'stb', 0x747)
        self.mem(0x80055d7c, 'lbz', 0x5da); self.f(0x80055d80, 'cmpi', BF=0, L=0, rA=0, immediate=1)
        self.branch(0x80055d84, 4, 2, 0x80055dac)
        self.mem(0x80055d88, 'lfs', 0x8c8, 1)
        self.f(0x80055d94, 'cror', crD=2, crA=1, crB=2); self.branch(0x80055d98, 4, 2, 0x80055db4)
        self.mem(0x80055d9c, 'lfs', 0x1dcc); self.f(0x80055da0, 'fadds', fD=0, fA=1, fB=0)
        self.mem(0x80055da4, 'stfs', 0x8c8); self.mem(0x80055dac, 'lfs', -30672, 0, 2)
        self.mem(0x80055db0, 'stfs', 0x8c8)


if __name__ == '__main__': unittest.main()
