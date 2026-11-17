#!/usr/bin/env python3
"""Public synthetic controls + optional private-snapshot validation.

No complete original instruction fixture, bytes, or reconstructable listing is
embedded here. Archive-backed tests require the two existing local snapshots;
they never fetch files. Private full inventories are not test prerequisites.
"""
import contextlib
import copy
import hashlib
import io
import json
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_target_reset_evidence as a
from test_archived_actor_mode1_evidence import encode as mode1_encode
from test_archived_target_preparation_evidence import encode as target_encode
from test_archived_frame_blocker_evidence import encode as prior_encode, invented_operands as prior_invented

RANGES = ((2147667064, 300, '2234d9aa7af59047260c7d72939f52c5ef9b31f10e9e89864abf2ff281132ecc'), (2147667364, 160, '2dcecd916811217d411f21faca6a1ca97774fa3c65c5f3756bf92d230096a693'))
MAPPING = (0x800055e0, 0x802b0160, 1, "MAIN_.text1", 1, 2796416, 21)
READS = [(21, 161432, 300, 2796416), (21, 161732, 160, 2796416)]

ROOT = Path(__file__).resolve().parents[3]
SNAPSHOT_DIR = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


def encode(row, pc):
    n = row['mnemonic']
    if n == 'bclr': return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    if n in ('lfs', 'lfd', 'stfs', 'stfd', 'psq_l', 'psq_st', 'fdivs', 'fsubs', 'fadds', 'fmuls'):
        return mode1_encode(row, pc)
    if n in ('lha', 'fmadds'): return target_encode(row, pc)
    if n in ('sth', 'lhz'):
        return (44 if n == 'sth' else 40) << 26 | row.get('rS', row.get('rD')) << 21 | row['rA'] << 16 | (row['displacement'] & 65535)
    if n == 'subf':
        return 31 << 26 | row['rD'] << 21 | row['rA'] << 16 | row['rB'] << 11 | row.get('OE', 0) << 10 | 40 << 1 | row['Rc']
    if n == 'srawi':
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | 824 << 1 | row['Rc']
    return prior_encode(row, pc)


def invented_operands():
    return prior_invented()


class FakeDB:
    def __init__(self, raw=b''): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_frozen_extents_and_independent_readable_provenance(self):
        self.assertEqual(a.RANGES, RANGES); self.assertEqual(a.TEXT_MAPPING, MAPPING)
        self.assertEqual(sum(width for _, width, _ in RANGES), 460)
        index = (ROOT / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols = (ROOT / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc, width, _ in RANGES:
            chunk = 'chunk_0003.c'
            line = next(i for i, value in enumerate(index) if value.startswith(f'{pc:08x}\t') and value.endswith('\t' + chunk))
            self.assertTrue(index[line + 1].startswith(f'{pc + width:08x}\t'))
            source = (ROOT / 'research/decomp/ghidra-export' / chunk).read_text()
            body, suffix = source.split(f'// ==== {pc:08x} ', 1)[1].split('// ==== ', 1)
            self.assertTrue(body.strip()); self.assertTrue(suffix.startswith(f'{pc + width:08x} '))
            if pc != 0x8005ace8: self.assertRegex(symbols, rf'(?m)^{pc:08x} {width:08x} {pc:08x} 0 ')

    def test_invented_forms_independent_inverse_and_bit_controls(self):
        mutations = 0
        for row in invented_operands():
            word = encode(row, 0x10000000)
            self.assertEqual(a.decode_selected(word, 0x10000000), row)
            for bit in range(32):
                changed = word ^ (1 << bit); mutations += 1
                try: result = a.decode_selected(changed, 0x10000000)
                except a.c.FormatError: continue
                if result is not None:
                    self.assertNotEqual(result, row)
                    self.assertEqual(encode(result, 0x10000000), changed)
        self.assertEqual(mutations, 992)

    def test_invalid_word_pc_reserved_and_unselected_forms(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in ((35 << 26), (35 << 26) | (3 << 21) | (3 << 16),
                     (46 << 26) | (20 << 21) | (21 << 16),
                     (31 << 26) | (151 << 1) | 1, (31 << 26) | (23 << 1) | 1,
                     (16 << 26) | (4 << 21) | 1, 0x4e800420):
            try: result = a.decode_selected(word, 0x10000000)
            except a.c.FormatError: continue
            self.assertIsNone(result)
        self.assertIsNone(a.decode_selected(49 << 26, 0x10000000))  # Updating float load is unselected.

    def test_selection_bounds_types_duplicates_maps_refuse_before_read(self):
        for pc, width, _ in RANGES:
            for bad in (pc - 4, pc + 4, pc + 1, float(pc), True, -1, 1 << 32):
                db = FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, bad, width)
                self.assertFalse(db.calls)
            for bad in (0, width - 4, width + 4, float(width), True, -width):
                db = FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, pc, bad)
                self.assertFalse(db.calls)
            for i, value in enumerate(MAPPING):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    changed = list(MAPPING); changed[i] = replacement; db = FakeDB()
                    with self.assertRaises(a.c.FormatError): a.range_evidence(db, tuple(changed), pc, width)
                    self.assertFalse(db.calls)
            with patch.object(a, 'RANGES', RANGES * 2):
                db = FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, pc, width)
                self.assertFalse(db.calls)
        for pc in (0x800055fc, 0x80010514, 0x803c4e84, 0x803c73b0, 0x803ca270, 0x804360dc):
            db = FakeDB()
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_wrong_width_and_digest_fail_before_decoder(self):
        with patch.object(a, 'decode_selected') as decode:
            for pc, width, _ in RANGES:
                for size in (width - 1, width + 1):
                    with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                        a.range_evidence(FakeDB(bytes(size)), MAPPING, pc, width)
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                    a.range_evidence(FakeDB(bytes(width)), MAPPING, pc, width)
            decode.assert_not_called()

    def test_authentication_precedes_parser_and_selection(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad'); db.assert_not_called(); code.assert_not_called()

    def test_mapping_corruptions_precede_selection(self):
        blocks, subs = {}, {}
        for name, key, start, length, root in a.command.MAPPINGS:
            blocks[key] = [name, None, None, 15, start, length, 0]
            subs[key] = [key, 2, length, 0, root, 0]
        cases = []
        for key in (1, 5, 7):
            for field in (4, 5, 6):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][field] += 1; cases.append((bb, ss))
            for field in range(6):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][field] += 1; cases.append((bb, ss))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]; cases.append((bb, ss))
        for bb, ss in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': '80000000'}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called()
        self.assertEqual(len(cases), 33)

    def test_cli_has_no_general_read_or_dump_options(self):
        for option in ('--address', '--width', '--pointer', '--target', '--dump', '--instructions'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/snapshot.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', json.loads(error.getvalue())['error'])

    def test_reused_context_is_reference_only(self):
        self.assertEqual([(x['address'], x['read_here']) for x in a.REUSED_EVIDENCE],
                         [('80029380', False), ('80053b30', False)])
        for row in a.REUSED_EVIDENCE:
            self.assertTrue((ROOT / 'research/decomp' / row['source']).is_file())
        self.assertEqual(a.INDIRECT_CALLS, {pc: () for pc, _, _ in RANGES})


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing private snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports, cls.traces, cls.auth_traces, cls.rows, cls.words, cls.bodies = [], [], [], [], [], []
        chain, decode = a.c.GBF.chain, a.decode_selected
        for name in ('db.3.gbf', 'db.4.gbf'):
            raw = (SNAPSHOT_DIR / name).read_bytes(); digest = hashlib.sha256(raw).hexdigest()
            trace, rows, words, bodies = [], {}, {}, {}
            def traced(db, *args):
                trace.append(args); result = chain(db, *args)
                if args in READS: bodies[RANGES[READS.index(args)][0]] = result[0]
                return result
            def decoded(word, pc):
                result = decode(word, pc); rows[pc] = result; words[pc] = word
                return result
            with patch.object(a.c.GBF, 'chain', traced): a.c.inspect(raw, digest)
            cls.auth_traces.append(trace[:]); trace.clear()
            with patch.object(a.c.GBF, 'chain', traced), patch.object(a, 'decode_selected', decoded):
                cls.reports.append(a.inspect(raw, digest))
            cls.traces.append(trace[:]); cls.rows.append(rows); cls.words.append(words); cls.bodies.append(bodies)

    def test_exact_two_reads_follow_full_unchanged_authentication(self):
        for trace, auth in zip(self.traces, self.auth_traces):
            self.assertTrue(auth); self.assertTrue(all(row[0] == 263 for row in auth))
            self.assertEqual(trace, auth + READS)

    def test_both_snapshots_complete_and_equal_without_listing_output(self):
        for key in ('mappings', 'ranges', 'selection_basis', 'reused_evidence'):
            self.assertEqual(self.reports[0][key], self.reports[1][key])
        self.assertEqual(self.rows[0], self.rows[1]); self.assertEqual(len(self.rows[0]), 115)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual([r['represented_instructions'] for r in report['ranges']], [75, 40])
            self.assertTrue(all(r['unrepresented_instructions'] == 0 for r in report['ranges']))
            self.assertIn('not original-DOL identity', report['caveat'])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (2, 460, 0))
            for key in ('pointer_following', 'global_payloads_read', 'original_execution', 'operand_listing_output'):
                self.assertIs(basis[key], False)
            text = json.dumps(report)
            for disallowed in ('instructions', 'mnemonic', 'raw_bytes', 'raw_words', 'payload_hex'):
                self.assertNotIn('"' + disallowed + '"', text)

    def test_every_instruction_independent_inverse_and_3680_bit_controls(self):
        count = 0
        for pc, row in self.rows[0].items():
            word = self.words[0][pc]
            self.assertEqual(encode(row, pc), word)
            for bit in range(32):
                count += 1; changed = word ^ (1 << bit)
                try: result = a.decode_selected(changed, pc)
                except a.c.FormatError: continue
                if result is not None:
                    self.assertNotEqual(result, row, (hex(pc), bit))
                    self.assertEqual(encode(result, pc), changed, (hex(pc), bit))
        self.assertEqual(count, 3680)
        for pc, width, digest in RANGES:
            reconstructed = b''.join(struct.pack('>I', encode(self.rows[0][site], site))
                                     for site in range(pc, pc + width, 4))
            self.assertEqual(hashlib.sha256(reconstructed).hexdigest(), digest)

    def test_every_payload_bit_mutation_refuses_before_decode(self):
        count = 0
        with patch.object(a, 'decode_selected') as decoder:
            for pc, width, _ in RANGES:
                body = self.bodies[0][pc]
                for offset in range(width):
                    for bit in range(8):
                        changed = body[:offset] + bytes([body[offset] ^ (1 << bit)]) + body[offset + 1:]
                        with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                            a.range_evidence(FakeDB(changed), MAPPING, pc, width)
                        count += 1
            decoder.assert_not_called()
        self.assertEqual(count, 3680)

    def test_spans_exact_widths_and_map_bounds(self):
        for report in self.reports:
            for row, (pc, width, digest) in zip(report['ranges'], RANGES):
                self.assertEqual(sum(span['length'] for span in row['spans']), width)
                self.assertEqual((row['address'], row['end_exclusive'], row['width'], row['sha256']),
                                 (f'{pc:08x}', f'{pc + width:08x}', width, digest))

    def test_semantic_inventory_mutation_fails_closed(self):
        original = a.decode_selected
        for site in self.rows[0]:
            def mutated(word, pc):
                row = original(word, pc)
                if pc == site: row = dict(row, unexpected_operand=0)
                return row
            entry, width, _ = next(row for row in RANGES if row[0] <= site < row[0] + row[1])
            with patch.object(a, 'decode_selected', mutated):
                with self.assertRaises(a.c.FormatError):
                    a.range_evidence(FakeDB(self.bodies[0][entry]), MAPPING, entry, width)

    def test_vector_stores_and_final_conditional_return(self):
        rows = self.rows[0]
        self.assertEqual(rows[0x8002cda4],dict(mnemonic='lfs',fD=0,rA=2,displacement=-31416))
        for pc,off in ((0x8002cdac,0x1cc),(0x8002cdb0,0x1d0),(0x8002cdb4,0x1d4)):
            self.assertEqual(rows[pc],dict(mnemonic='stfs',fS=0,rA=3,displacement=off))
        self.assertEqual(rows[0x8002ce34],dict(mnemonic='bclr',BO=12,BI=2,BH=0,LK=0))
        self.assertEqual(rows[0x8002ce38],dict(mnemonic='addi',rD=0,rA=4,immediate=-1))
        self.assertEqual(rows[0x8002ce3c],dict(mnemonic='stb',rS=0,rA=3,displacement=0x1e8))
        self.assertEqual(a.CALLS[0x8002cda4],())
        self.assertTrue(all(target=='8002cda4' for _,target in a.CALLS[0x8002cc78]))

    def test_real_hash_schema_and_each_payload_refusal(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes(); digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as selected:
            for changed, claim in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaises(a.c.FormatError): a.inspect(changed, claim)
            selected.assert_not_called()
        original_tables = a.c.GBF.tables
        for table in ('Program', 'Property Table', 'File Bytes', 'ADDRESS MAP', 'Memory Blocks', 'Sub Memory Blocks'):
            for field in ('version', 'keytype', 'types', 'fields', 'missing'):
                def tampered(db):
                    tables = copy.deepcopy(original_tables(db))
                    if field == 'missing': del tables[table]
                    elif field == 'types': tables[table][field] = [99]
                    elif field == 'fields': tables[table][field] = 'Wrong;'
                    else: tables[table][field] += 1
                    return tables
                with patch.object(a.c.GBF, 'tables', tampered), patch.object(a, 'range_evidence') as selected:
                    with self.assertRaises(a.c.FormatError): a.inspect(raw, digest)
                    selected.assert_not_called()
        original = a.c.GBF.chain
        for selected_call in READS:
            def damaged(db, *args):
                body, spans = original(db, *args)
                if args == selected_call: body = bytes([body[0] ^ 1]) + body[1:]
                return body, spans
            with patch.object(a.c.GBF, 'chain', damaged):
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)


if __name__ == '__main__':
    unittest.main()
