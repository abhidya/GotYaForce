#!/usr/bin/env python3
"""Synthetic adversarial controls plus optional authenticated local archive tests.

No original executable fixtures, instruction execution or live-state claims.
"""
import contextlib
import copy
import hashlib
import io
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_actor_attribute_evidence as a


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, [dict(synthetic=True)]


def d_form(op, reg, base, offset):
    return (op << 26) | (reg << 21) | (base << 16) | (offset & 65535)


def spr_form(xo, reg=0, spr=8, record=0):
    return (31 << 26) | (reg << 21) | ((spr & 31) << 16) | ((spr >> 5) << 11) | (xo << 1) | record


class EvidenceTests(unittest.TestCase):
    def decode(self, word, pc=0x80055dcc):
        return a.decode_selected(word, pc)

    def test_fixed_span_identity(self):
        self.assertEqual(a.RANGES, ((0x80055dcc, 280,
                         '7f60ab140ba8c7261c2ad34d87e1f41962e0c870e435a5c0efc12f216e6fb4a2'),))
        self.assertEqual(a.RANGES[0][0] + a.RANGES[0][1], 0x80055ee4)

    def test_narrow_link_register_save_and_restore(self):
        self.assertEqual(self.decode(spr_form(339)), dict(mnemonic='mflr', rD=0))
        self.assertEqual(self.decode(spr_form(467)), dict(mnemonic='mtlr', rS=0))
        for xo in (339, 467):
            for reg, spr, record in ((1, 8, 0), (31, 8, 0), (0, 0, 0), (0, 9, 0),
                                     (0, 256, 0), (0, 264, 0), (0, 1023, 0), (0, 8, 1)):
                with self.subTest(xo=xo, reg=reg, spr=spr, record=record):
                    with self.assertRaisesRegex(a.c.FormatError, 'link-register'):
                        self.decode(spr_form(xo, reg, spr, record))
        for xo in (338, 340, 466, 468):
            self.assertIsNone(self.decode(spr_form(xo)))

    def test_spr_split_halves_not_interchanged(self):
        # SPR 256 has the same encoded halfword bit population as LR, but is not LR.
        self.assertEqual((spr_form(339, spr=8) >> 16) & 31, 8)
        self.assertEqual((spr_form(339, spr=256) >> 11) & 31, 8)
        with self.assertRaises(a.c.FormatError): self.decode(spr_form(339, spr=256))

    def test_word_and_byte_store_operand_names(self):
        for op, name in ((36, 'stw'), (37, 'stwu'), (38, 'stb')):
            for offset in (-32768, -16, -1, 0, 0x87, 32767):
                self.assertEqual(self.decode(d_form(op, 7, 3, offset)),
                                 dict(mnemonic=name, rS=7, rA=3, displacement=offset))
        self.assertEqual(self.decode(d_form(32, 4, 3, 0x4b0)),
                         dict(mnemonic='lwz', rD=4, rA=3, displacement=0x4b0))

    def test_float_load_store_fields_and_signed_offsets(self):
        for reg, base, offset in ((0, 3, 0x668), (1, 3, 0xb4), (0, 4, 0x74),
                                  (7, 5, -32768), (31, 31, -1), (3, 0, 32767)):
            self.assertEqual(self.decode(d_form(48, reg, base, offset)),
                             dict(mnemonic='lfs', fD=reg, rA=base, displacement=offset))
            self.assertEqual(self.decode(d_form(52, reg, base, offset)),
                             dict(mnemonic='stfs', fS=reg, rA=base, displacement=offset))

    def test_single_multiply_not_double_or_fused(self):
        word = (59 << 26) | (7 << 21) | (3 << 16) | (5 << 6) | (25 << 1)
        self.assertEqual(self.decode(word), dict(mnemonic='fmuls', fD=7, fA=3, fC=5))
        for bad in (word | 1, word | (1 << 11)):
            with self.assertRaises(a.c.FormatError): self.decode(bad)
        for op, xo in ((63, 25), (59, 18), (59, 24), (59, 29), (4, 25)):
            self.assertIsNone(self.decode((op << 26) | (xo << 1)))

    def test_bit6_extract_fields_preserve_no_record(self):
        word = (21 << 26) | (26 << 11) | (31 << 6) | (31 << 1)
        self.assertEqual(self.decode(word),
                         dict(mnemonic='rlwinm', rS=0, rA=0, SH=26, MB=31, ME=31, Rc=0))
        self.assertEqual(self.decode(word | 1)['Rc'], 1)

    def test_immediate_signed_compare_and_zero_register_base(self):
        self.assertEqual(self.decode(d_form(14, 4, 0, 0)),
                         dict(mnemonic='addi', rD=4, rA=0, immediate=0))
        self.assertEqual(self.decode(d_form(14, 1, 1, -16))['immediate'], -16)
        self.assertEqual(self.decode((11 << 26) | (4 << 16) | 9),
                         dict(mnemonic='cmpi', BF=0, L=0, rA=4, immediate=9))
        self.assertEqual(self.decode((11 << 26) | (3 << 23) | (4 << 16) | 65535),
                         dict(mnemonic='cmpi', BF=3, L=0, rA=4, immediate=-1))
        self.assertIsNone(self.decode((10 << 26) | (4 << 16) | 9))

    def test_conditional_branch_preserves_condition_and_target(self):
        self.assertEqual(self.decode((16 << 26) | (4 << 21) | 0x4c, 0x80055e84),
                         dict(mnemonic='bc', BO=4, BI=0, LK=0, target='80055ed0', AA=0))
        self.assertEqual(self.decode((16 << 26) | (12 << 21) | (2 << 16) | 0xfffc),
                         dict(mnemonic='bc', BO=12, BI=2, LK=0, target='80055dc8', AA=0))
        self.assertEqual(self.decode((16 << 26) | (4 << 21) | 0x103),
                         dict(mnemonic='bc', BO=4, BI=0, LK=1, target='00000100', AA=1))

    def test_backward_call_and_final_return(self):
        word = (18 << 26) | ((0x8004d08c - 0x80055ed0) & 0x3fffffc) | 1
        self.assertEqual(self.decode(word, 0x80055ed0),
                         dict(mnemonic='bl', target='8004d08c', AA=0))
        self.assertEqual(self.decode((18 << 26) | 0x102),
                         dict(mnemonic='b', target='00000100', AA=1))
        self.assertEqual(self.decode(0x4e800020), dict(mnemonic='blr'))
        for word in (0x4e800021, 0x4e800421, 0x4e801020):
            self.assertIsNone(self.decode(word))

    def test_unselected_forms(self):
        for word in (0, 34 << 26, 40 << 26, 44 << 26, 50 << 26, 56 << 26,
                     (31 << 26) | (28 << 1), (31 << 26) | (266 << 1)):
            self.assertIsNone(self.decode(word))

    def test_word_and_pc_type_bounds(self):
        for word in (-1, 1 << 32, True, False, 1.0, '0', None):
            with self.assertRaisesRegex(a.c.FormatError, 'word bounds'): self.decode(word)
        for pc in (-1, 1, 1 << 32, True, False, 1.0, '0', None):
            with self.assertRaisesRegex(a.c.FormatError, 'PC bounds'): self.decode(0, pc)

    def test_allowlist_refusal_before_read(self):
        for address, width in ((0x80055dd0, 276), (0x80055dcc, 276), (0x80055dcc, 284),
                               (0x80055dcb, 280), (0x80055ee4, 280), (0x80055dcc, 0)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, address, width)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, 21, 0x80055dcc, 280)

    def test_range_integer_fields_before_read(self):
        for values in ((21.0, 0x80055dcc, 280), (True, 0x80055dcc, 280),
                       (21, float(0x80055dcc), 280), (21, 0x80055dcc, 280.0)):
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.range_evidence(None, *values)

    def test_root_alignment_and_bounds_before_read(self):
        with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
            a.range_evidence(None, 22, 0x80055dcc, 280)
        for address, width in ((0x80055dcd, 280), (0x80055dcc, 279), (a.TEXT_START - 4, 4),
                               (a.TEXT_START + a.TEXT_LENGTH - 4, 8), (0x80055dcc, 0),
                               (0x80055dcc, -4), (1 << 32, 4)):
            with patch.object(a, 'RANGES', ((address, width, 'unused'),)):
                with self.assertRaisesRegex(a.c.FormatError, 'root/alignment/bounds'):
                    a.range_evidence(None, 21, address, width)

    def test_width_and_hash_precede_decoding(self):
        for raw, message in ((bytes(280), 'digest mismatch'), (bytes(276), 'byte width'),
                             (bytes(284), 'byte width')):
            with patch.object(a, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, message):
                    a.range_evidence(FakeDB(raw), 21, 0x80055dcc, 280)
                decoder.assert_not_called()
        raw = bytes(284)
        with patch.object(a, 'RANGES', ((0x80055dcc, 280, hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                a.range_evidence(FakeDB(raw), 21, 0x80055dcc, 280)

    def test_synthetic_complete_order_trace_and_no_raw_output(self):
        # Synthetic register-7 sequence, not copied executable bytes.
        words = (d_form(48, 7, 5, 12), (59 << 26) | (7 << 21) | (7 << 16) | (2 << 6) | (25 << 1),
                 d_form(52, 7, 5, 20), d_form(38, 4, 5, 3), 0x4e800020)
        raw = struct.pack('>5I', *words)
        db = FakeDB(raw)
        with patch.object(a, 'RANGES', ((0x80055dcc, 20, hashlib.sha256(raw).hexdigest()),)):
            result = a.range_evidence(db, 21, 0x80055dcc, 20)
        self.assertEqual(db.calls, [(21, 329708, 20, a.TEXT_LENGTH)])
        self.assertEqual(result['spans'], [dict(synthetic=True)])
        self.assertEqual(result['end_exclusive'], '80055de0')
        self.assertEqual([i['mnemonic'] for i in result['instructions']], ['lfs', 'fmuls', 'stfs', 'stb', 'blr'])
        self.assertEqual([i['address'] for i in result['instructions']],
                         ['80055dcc', '80055dd0', '80055dd4', '80055dd8', '80055ddc'])
        for item in [result] + result['instructions']:
            self.assertTrue(set(item).isdisjoint(('raw', 'bytes', 'word', 'words', 'hex')))

    def test_no_silently_omitted_instruction(self):
        for word in (0, spr_form(339, spr=9)):
            raw = struct.pack('>I', word)
            with patch.object(a, 'RANGES', ((0x80055dcc, 4, hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaises(a.c.FormatError):
                    a.range_evidence(FakeDB(raw), 21, 0x80055dcc, 4)

    def test_authentication_before_parser_or_span_read(self):
        data = bytes(32)
        for digest in ('0' * 64, hashlib.sha256(data).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as evidence:
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'): a.inspect(data, digest)
                parser.assert_not_called(); evidence.assert_not_called()
        for message in ('unsupported schema: Program', 'language mismatch', 'executable metadata SHA/type mismatch',
                        'File Bytes table is not empty', 'unsupported address map',
                        'data5 digest mismatch', 'known control mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(message)), \
                    patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as evidence:
                with self.assertRaisesRegex(a.c.FormatError, message): a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called(); evidence.assert_not_called()

    def inspect_fixture(self):
        auth = dict(snapshot='synthetic', snapshot_sha256='synthetic', program_name='boot.dol',
                    created_with_ghidra_version='12.1.2', executable_sha256_metadata='synthetic',
                    executable_sha256_property_type=2, executable_metadata_caveat='synthetic',
                    file_bytes_table=dict(version=0, root=-1, count=0), block_size=16384,
                    master_root=1, table_roots={}, image_offset='80000000', data5_sha256='synthetic')
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        return auth, blocks, subs

    def run_inspect_fixture(self, auth, blocks, subs, expect_error=None):
        with patch.object(a.c, 'inspect', return_value=auth) as authentication, \
                patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence', return_value='derived') as evidence:
            db = parser.return_value
            db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
            db.rows.side_effect = lambda table: {'blocks': blocks, 'subs': subs}[table]
            if expect_error:
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                evidence.assert_not_called()
                result = None
            else:
                result = a.inspect(b'synthetic', 'synthetic')
                evidence.assert_called_once_with(db, 21, 0x80055dcc, 280)
            authentication.assert_called_once_with(b'synthetic', 'synthetic')
            db.chain.assert_not_called()
            return result

    def test_inspect_one_fixed_span_no_new_constants(self):
        result = self.run_inspect_fixture(*self.inspect_fixture())
        self.assertEqual(result['ranges'], ['derived'])
        self.assertEqual(result['constants'], [])
        self.assertEqual((result['block_name'], result['chain_root']), ('MAIN_.text1', 21))
        self.assertIn('not unchanged original-DOL or live parity', result['caveat'])

    def test_mapping_mutations_fail_before_span_reads(self):
        for key in (1, 5, 7):
            for index in (0, 1, 2, 3, 4, 5):
                auth, blocks, subs = self.inspect_fixture()
                subs[key][index] += 1
                with self.subTest(key=key, subfield=index):
                    self.run_inspect_fixture(auth, blocks, subs, expect_error=True)
            for index in (4, 5, 6):
                auth, blocks, subs = self.inspect_fixture()
                blocks[key][index] += 1
                with self.subTest(key=key, blockfield=index):
                    self.run_inspect_fixture(auth, blocks, subs, expect_error=True)
            for target in ('duplicate_block', 'duplicate_subblock', 'missing_block', 'missing_subblock', 'wrong_key'):
                auth, blocks, subs = self.inspect_fixture()
                if target == 'duplicate_block': blocks[99] = copy.deepcopy(blocks[key])
                if target == 'duplicate_subblock': subs[99] = copy.deepcopy(subs[key])
                if target == 'missing_block': del blocks[key]
                if target == 'missing_subblock': del subs[key]
                if target == 'wrong_key': blocks[99] = blocks.pop(key)
                with self.subTest(key=key, target=target):
                    self.run_inspect_fixture(auth, blocks, subs, expect_error=True)
        auth, blocks, subs = self.inspect_fixture()
        blocks[99] = ['overlapping unrelated block', None, None, 0, 0x20000000000055e4, 4, 0]
        self.run_inspect_fixture(auth, blocks, subs, expect_error=True)
        auth, blocks, subs = self.inspect_fixture(); auth['image_offset'] = '80000004'
        self.run_inspect_fixture(auth, blocks, subs, expect_error=True)

    def test_cli_has_only_snapshot_input(self):
        for extra in (['--address', '80055dcc'], ['--width', '280'], ['--raw'], ['--execute']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + extra), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as error: a.main()
                self.assertEqual(error.exception.code, 2)
                inspect.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    """Both existing snapshots only; optional when private local inputs are absent."""
    @classmethod
    def setUpClass(cls):
        base = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        paths = [base / f'db.{number}.gbf' for number in (3, 4)]
        if not all(path.is_file() for path in paths):
            raise unittest.SkipTest('both local archived snapshots are not present')
        cls.results = []
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot exceeds size bound')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
        cls.instructions = cls.results[0]['ranges'][0]['instructions']
        cls.facts = {int(fact['address'], 16): fact for fact in cls.instructions}

    def fact(self, pc, **fields):
        self.assertEqual(self.facts[pc], dict(address=f'{pc:08x}', **fields))

    def test_both_snapshots_same_complete_evidence_and_trace(self):
        self.assertEqual({result['snapshot_sha256'] for result in self.results}, set(a.c.SNAPSHOTS))
        self.assertEqual(self.results[0]['ranges'], self.results[1]['ranges'])
        self.assertEqual(len(self.instructions), 70)
        self.assertEqual(list(self.facts), list(range(0x80055dcc, 0x80055ee4, 4)))
        span = self.results[0]['ranges'][0]
        self.assertEqual((span['address'], span['end_exclusive'], span['width'], span['sha256']),
                         ('80055dcc', '80055ee4', 280, a.RANGES[0][2]))
        self.assertEqual(span['spans'], [dict(root_buffer=21, data_buffer=42, chain_offset=329708,
                                            data_offset=2148, physical_offset=706666,
                                            length=280, obfuscated=True)])

    def test_metadata_is_import_evidence_not_original_bytes(self):
        for result in self.results:
            self.assertEqual(result['executable_sha256_metadata'],
                             '21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836')
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual((result['block_size'], result['master_root'], result['image_offset']),
                             (16384, 1, '80000000'))
            self.assertEqual(result['constants'], [])
            self.assertIn('not proof of unchanged original executable bytes', result['executable_metadata_caveat'])

    def test_prologue_and_bit6_store(self):
        self.fact(0x80055dcc, mnemonic='stwu', rS=1, rA=1, displacement=-16)
        self.fact(0x80055dd0, mnemonic='mflr', rD=0)
        self.fact(0x80055dd4, mnemonic='addi', rD=4, rA=0, immediate=0)
        self.fact(0x80055dd8, mnemonic='stw', rS=0, rA=1, displacement=20)
        self.fact(0x80055ddc, mnemonic='cmpi', BF=0, L=0, rA=4, immediate=9)
        self.fact(0x80055de0, mnemonic='lwz', rD=0, rA=3, displacement=0x5e0)
        self.fact(0x80055de4, mnemonic='rlwinm', rS=0, rA=0, SH=26, MB=31, ME=31, Rc=0)
        self.fact(0x80055de8, mnemonic='stb', rS=0, rA=3, displacement=0x87)

    def test_retained_descriptor_and_scale_five_ordered_products(self):
        self.fact(0x80055dec, mnemonic='lwz', rD=4, rA=3, displacement=0x4b0)
        self.fact(0x80055df0, mnemonic='lfs', fD=1, rA=3, displacement=0xb4)
        for pc, source, dest in ((0x80055df4, 0x4c, 0x668), (0x80055e00, 0x44, 0x66c),
                                 (0x80055e0c, 0x48, 0x670), (0x80055e18, 0x54, 0x674),
                                 (0x80055e24, 0x50, 0x770)):
            self.fact(pc, mnemonic='lfs', fD=0, rA=4, displacement=source)
            self.fact(pc + 4, mnemonic='fmuls', fD=0, fA=0, fC=1)
            self.fact(pc + 8, mnemonic='stfs', fS=0, rA=3, displacement=dest)
        self.assertEqual(sum(f.get('displacement') == 0x4b0 for f in self.instructions), 1)
        self.assertEqual(sum(f.get('displacement') == 0xb4 for f in self.instructions), 1)

    def test_parameter_pointer_is_reloaded_before_each_float_copy(self):
        for pc, source, dest in ((0x80055e30, 0x74, 0x678), (0x80055e3c, 0x78, 0x67c),
                                 (0x80055e48, 0x7c, 0x680)):
            self.fact(pc, mnemonic='lwz', rD=4, rA=3, displacement=0x4ac)
            self.fact(pc + 4, mnemonic='lfs', fD=0, rA=4, displacement=source)
            self.fact(pc + 8, mnemonic='stfs', fS=0, rA=3, displacement=dest)
        self.assertEqual(sum(f.get('displacement') == 0x4ac for f in self.instructions), 3)

    def test_all_fifteen_rows_load_then_store_in_order(self):
        pcs = list(range(0x80055e54, 0x80055e84, 8)) + list(range(0x80055e88, 0x80055ed0, 8))
        self.assertEqual(len(pcs), 15)
        for index, pc in enumerate(pcs):
            self.fact(pc, mnemonic='lfs', fD=0, rA=3, displacement=0x850 + index * 4)
            self.fact(pc + 4, mnemonic='stfs', fS=0, rA=3, displacement=0x814 + index * 4)

    def test_branch_uses_unchanged_entry_compare_not_actor_data(self):
        self.fact(0x80055e84, mnemonic='bc', BO=4, BI=0, LK=0, target='80055ed0', AA=0)
        between = [fact for fact in self.instructions if '80055de0' <= fact['address'] < '80055e84']
        self.assertEqual({fact['mnemonic'] for fact in between}, {'lwz', 'rlwinm', 'stb', 'lfs', 'fmuls', 'stfs'})
        self.assertTrue(all(fact.get('Rc', 0) == 0 for fact in between))
        # Full operand checks above establish the entry compare as signed 0 < 9;
        # the false-CR0.LT branch is therefore not taken on normal entry.
        self.assertEqual(self.facts[0x80055dd4]['immediate'], 0)
        self.assertEqual(self.facts[0x80055ddc]['immediate'], 9)

    def test_one_final_real_callee_then_epilogue(self):
        self.fact(0x80055ed0, mnemonic='bl', target='8004d08c', AA=0)
        self.fact(0x80055ed4, mnemonic='lwz', rD=0, rA=1, displacement=20)
        self.fact(0x80055ed8, mnemonic='mtlr', rS=0)
        self.fact(0x80055edc, mnemonic='addi', rD=1, rA=1, immediate=16)
        self.fact(0x80055ee0, mnemonic='blr')
        self.assertEqual([f['address'] for f in self.instructions if f['mnemonic'] == 'bl'], ['80055ed0'])
        self.assertEqual([f['address'] for f in self.instructions if f['mnemonic'] == 'blr'], ['80055ee0'])
        self.assertFalse(any(f.get('rA') in (2, 13) for f in self.instructions))

    def test_no_raw_executable_output(self):
        for result in self.results:
            for span in result['ranges']:
                for item in [span] + span['instructions']:
                    self.assertTrue(set(item).isdisjoint(('raw', 'bytes', 'word', 'words', 'hex')))


if __name__ == '__main__':
    unittest.main()
