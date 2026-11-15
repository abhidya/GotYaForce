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

import read_archived_frame_blocker_evidence as a

RANGES = (
    (0x80027764, 736, '6ecb2b36a87268ae52b5b4f53649991e70f755c5a4128eaf1575bb90c9668d4f'),
    (0x8000bef4, 1056, 'dc9bdaf0c10968c6eadd7325b99361b7c91d5cddf2a1758edca587cd5b8b82e4'),
)
MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
READS = [(21, 139652, 736, 2796416), (21, 26900, 1056, 2796416)]
ROOT = Path(__file__).resolve().parents[3]
SNAPSHOT_DIR = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


def encode(row, pc):
    """Independent inverse: numerical PPC forms, no production decoder imports."""
    name = row['mnemonic']
    forms = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
             'stb': (38, 'rS', 'displacement'), 'stmw': (47, 'rS', 'displacement'),
             'lwz': (32, 'rD', 'displacement'), 'lbz': (34, 'rD', 'displacement'),
             'lbzu': (35, 'rD', 'displacement'), 'lmw': (46, 'rD', 'displacement'),
             'mulli': (7, 'rD', 'immediate'), 'addi': (14, 'rD', 'immediate'),
             'addis': (15, 'rD', 'immediate')}
    if name in forms:
        op, reg, imm = forms[name]
        return (op << 26) | (row[reg] << 21) | (row['rA'] << 16) | (row[imm] & 65535)
    if name in ('mflr', 'mtlr', 'mtctr'):
        reg = row['rD'] if name == 'mflr' else row['rS']
        return (31 << 26) | (reg << 21) | ((9 if name == 'mtctr' else 8) << 16) | ((339 if name == 'mflr' else 467) << 1)
    if name in ('or', 'and', 'slw', 'add', 'lwzx', 'lbzx', 'stwx', 'stbx'):
        xo, reg = {'or': (444, 'rS'), 'and': (28, 'rS'), 'slw': (24, 'rS'),
                   'add': (266, 'rD'), 'lwzx': (23, 'rD'), 'lbzx': (87, 'rD'),
                   'stwx': (151, 'rS'), 'stbx': (215, 'rS')}[name]
        return (31 << 26) | (row[reg] << 21) | (row['rA'] << 16) | (row['rB'] << 11) | (xo << 1) | row.get('Rc', 0)
    if name == 'extsb':
        return (31 << 26) | (row['rS'] << 21) | (row['rA'] << 16) | (954 << 1) | row['Rc']
    if name in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if name == 'bc':
            return (16 << 26) | (row['BO'] << 21) | (row['BI'] << 16) | (displacement & 0xfffc) | (row['AA'] << 1) | row['LK']
        return (18 << 26) | (displacement & 0x3fffffc) | (row['AA'] << 1) | row['LK']
    if name == 'blr':
        return (19 << 26) | (row['BO'] << 21) | (row['BI'] << 16) | (row['BH'] << 11) | (16 << 1) | row['LK']
    if name == 'rlwinm':
        return (21 << 26) | (row['rS'] << 21) | (row['rA'] << 16) | (row['SH'] << 11) | (row['MB'] << 6) | (row['ME'] << 1) | row['Rc']
    if name in ('cmpi', 'cmpli'):
        return ((11 if name == 'cmpi' else 10) << 26) | (row['BF'] << 23) | (row['L'] << 21) | (row['rA'] << 16) | (row['immediate'] & 65535)
    if name == 'cmp':
        return (31 << 26) | (row['BF'] << 23) | (row['L'] << 21) | (row['rA'] << 16) | (row['rB'] << 11)
    raise AssertionError(name)


def invented_operands():
    # Arbitrary register/immediate combinations, not a sequence from either body.
    rows = []
    for name in ('stwu', 'stw', 'stb', 'stmw', 'lwz', 'lbz', 'lbzu', 'lmw'):
        rows.append(dict(mnemonic=name, **{'rS' if name.startswith('st') else 'rD': 17}, rA=3, displacement=-212))
    for name in ('mulli', 'addi', 'addis'):
        rows.append(dict(mnemonic=name, rD=19, rA=7, immediate=-31))
    for name in ('mflr', 'mtlr', 'mtctr'):
        rows.append(dict(mnemonic=name, **{'rD' if name == 'mflr' else 'rS': 0 if name != 'mtctr' else 19}))
    for name in ('or', 'and', 'slw', 'add', 'lwzx', 'lbzx', 'stwx', 'stbx'):
        row = dict(mnemonic=name, **{'rD' if name in ('add', 'lwzx', 'lbzx') else 'rS': 22}, rA=11, rB=17)
        if name in ('or', 'and', 'slw', 'add'): row['Rc'] = 1
        rows.append(row)
    rows.extend([dict(mnemonic='extsb', rS=27, rA=13, Rc=1),
                 dict(mnemonic='b', target='100001a4', AA=0, LK=0),
                 dict(mnemonic='bl', target='0ffffea4', AA=0, LK=1),
                 dict(mnemonic='bc', BO=4, BI=0, target='0fffff80', AA=0, LK=0),
                 dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0),
                 dict(mnemonic='rlwinm', rS=21, rA=12, SH=27, MB=3, ME=25, Rc=1),
                 dict(mnemonic='cmpi', BF=0, L=0, rA=7, immediate=-1023),
                 dict(mnemonic='cmpli', BF=0, L=0, rA=25, immediate=64444),
                 dict(mnemonic='cmp', BF=0, L=0, rA=19, rB=4)])
    return rows


class FakeDB:
    def __init__(self, raw=b''): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_frozen_extents_and_independent_readable_provenance(self):
        self.assertEqual(a.RANGES, RANGES); self.assertEqual(a.TEXT_MAPPING, MAPPING)
        self.assertEqual(sum(width for _, width, _ in RANGES), 1792)
        index = (ROOT / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols = (ROOT / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc, width, _ in RANGES:
            chunk = 'chunk_0003.c' if pc == 0x80027764 else 'chunk_0001.c'
            line = index.index(f'{pc:08x}\tzz_{pc - 0x80000000:07x}_\t{chunk}')
            self.assertTrue(index[line + 1].startswith(f'{pc + width:08x}\t'))
            source = (ROOT / 'research/decomp/ghidra-export' / chunk).read_text()
            body, suffix = source.split(f'// ==== {pc:08x} ', 1)[1].split('// ==== ', 1)
            self.assertTrue(body.strip()); self.assertTrue(suffix.startswith(f'{pc + width:08x} '))
            self.assertRegex(symbols, rf'(?m)^{pc:08x} {width:08x} {pc:08x} 0 ')

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
                     (16 << 26) | (4 << 21) | 1, 0x4e800421):
            try: result = a.decode_selected(word, 0x10000000)
            except a.c.FormatError: continue
            self.assertIsNone(result)
        self.assertIsNone(a.decode_selected(48 << 26, 0x10000000))  # Floating load is outside this reader.

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

    def test_reused_helpers_are_references_only(self):
        self.assertEqual([(x['address'], x['read_here']) for x in a.REUSED_EVIDENCE],
                         [('800055fc', False), ('80010514', False)])
        for row in a.REUSED_EVIDENCE:
            self.assertTrue((ROOT / 'research/decomp' / row['source']).is_file())
        self.assertEqual(a.CALLS, {0x80027764: (('80027770', '800055fc'),),
            0x8000bef4: (('8000c11c', '80010514'), ('8000c1e4', '80010514'), ('8000c270', '80010514'))})


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
        self.assertEqual(self.rows[0], self.rows[1]); self.assertEqual(len(self.rows[0]), 448)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual([r['represented_instructions'] for r in report['ranges']], [184, 264])
            self.assertTrue(all(r['unrepresented_instructions'] == 0 for r in report['ranges']))
            self.assertIn('not original-DOL identity', report['caveat'])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (2, 1792, 0))
            for key in ('pointer_following', 'helpers_read', 'global_payloads_read', 'original_execution', 'operand_listing_output'):
                self.assertIs(basis[key], False)
            text = json.dumps(report)
            for disallowed in ('instructions', 'mnemonic', 'raw_bytes', 'raw_words', 'payload_hex'):
                self.assertNotIn('"' + disallowed + '"', text)

    def test_every_instruction_independent_inverse_and_14336_bit_controls(self):
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
        self.assertEqual(count, 14336)
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
        self.assertEqual(count, 14336)

    def test_spans_exact_widths_and_map_bounds(self):
        expected = [(30, 139652, 8628, 736, 516538), (23, 26900, 10522, 1056, 403744)]
        for report in self.reports:
            for row, values, (pc, width, digest) in zip(report['ranges'], expected, RANGES):
                buffer, offset, data_offset, length, physical = values
                self.assertEqual(row['spans'], [dict(root_buffer=21, data_buffer=buffer, chain_offset=offset,
                    data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)])
                self.assertEqual((row['address'], row['end_exclusive'], row['width'], row['sha256']),
                                 (f'{pc:08x}', f'{pc + width:08x}', width, digest))

    def test_semantic_inventory_mutation_fails_closed(self):
        original = a.decode_selected
        for site in self.rows[0]:
            def mutated(word, pc):
                row = original(word, pc)
                if pc == site: row = dict(row, unexpected_operand=0)
                return row
            entry = 0x80027764 if 0x80027764 <= site < 0x80027a44 else 0x8000bef4
            width = 736 if entry == 0x80027764 else 1056
            with patch.object(a, 'decode_selected', mutated):
                with self.assertRaises(a.c.FormatError):
                    a.range_evidence(FakeDB(self.bodies[0][entry]), MAPPING, entry, width)

    def test_leader_order_widths_live_reload_and_signed_last_tie(self):
        rows = self.rows[0]
        first_game_store = min(pc for pc in range(0x80027764, 0x80027a44, 4)
            if rows[pc]['mnemonic'].startswith('st') and rows[pc].get('rA') != 1)
        self.assertGreater(first_game_store, 0x80027770)
        # Four owner-row+38 stores precede scans, with three later owner reloads.
        owner_stores = [rows[pc]['displacement'] for pc in range(0x80027774, 0x800277c0, 4)
                        if rows[pc]['mnemonic'] == 'stw']
        self.assertEqual(owner_stores, [0x12c, 0x168, 0x1a4, 0x1e0])
        self.assertEqual(sum(rows[pc]['mnemonic'] == 'lwz' and rows[pc].get('rA') == 13
                             for pc in range(0x80027774, 0x800277c0, 4)), 4)
        for flag, pointer in ((0x800277d8, 0x800277dc), (0x80027844, 0x80027848)):
            self.assertEqual((rows[flag]['mnemonic'], rows[flag]['displacement']), ('stb', 0x335))
            self.assertEqual((rows[pointer]['mnemonic'], rows[pointer]['displacement']), ('stw', 0x330))
        for pc in (0x800277fc, 0x80027828, 0x80027868, 0x80027894):
            self.assertEqual((rows[pc]['BO'], rows[pc]['BI']), (12, 0))  # Skip only signed LT, retain ties.
        updates = [(pc, row['displacement']) for pc, row in rows.items()
                   if 0x80027764 <= pc < 0x80027a44 and row['mnemonic'] == 'lbzu']
        self.assertEqual(updates, [(0x80027834, 0x1e00), (0x80027938, 0x7800), (0x800279fc, 0x7800)])
        self.assertEqual((rows[0x800278a8]['BO'], rows[0x800278a8]['BI']), (16, 0))
        for pc in (0x800278bc, 0x80027980): self.assertEqual(rows[pc]['displacement'], 0x335)

    def test_binding_scan_live_masks_mode_widths_and_helper_mask(self):
        rows = self.rows[0]
        masks = [pc for pc in range(0x8000bf90, 0x8000c0a0, 4)
                 if rows[pc]['mnemonic'] == 'lbz' and rows[pc].get('displacement') == 2]
        self.assertEqual(len(masks), 6)
        self.assertTrue(all(rows[pc]['rA'] == 6 for pc in masks))  # Captured participant.
        self.assertFalse(any(rows[pc]['mnemonic'] == 'lwz' and rows[pc].get('rA') == 13
                             for pc in range(0x8000bf90, 0x8000c0d0, 4)))
        for call, mask in ((0x8000c11c, 0x8000c120), (0x8000c1e4, 0x8000c1e8), (0x8000c270, 0x8000c274)):
            self.assertEqual(rows[call]['target'], '80010514')
            self.assertEqual(tuple(rows[mask][key] for key in ('SH', 'MB', 'ME', 'Rc')), (0, 1, 31, 1))
        self.assertEqual(rows[0x8000c18c]['immediate'], 2)
        self.assertEqual(rows[0x8000c234]['immediate'], 4)
        self.assertEqual([rows[pc]['immediate'] for pc in (0x8000c130, 0x8000c1f8, 0x8000c284)], [0x3e4] * 3)
        self.assertEqual([rows[pc]['immediate'] for pc in (0x8000c148, 0x8000c210, 0x8000c29c)], [0x394] * 3)
        self.assertEqual([rows[pc]['displacement'] for pc in (0x8000c160, 0x8000c21c, 0x8000c2b0)], [0x10] * 3)

    def test_binding_duplicate_accesses_and_final_actor_store(self):
        rows = self.rows[0]
        for start, stop, source_offset in ((0x8000bf2c, 0x8000bf84, 0x2ec0),
                                           (0x8000c2a4, 0x8000c2f8, 0x10)):
            stores = [row for pc, row in rows.items() if start <= pc < stop and row['mnemonic'] in ('stw', 'stb')]
            self.assertEqual([(row['mnemonic'], row['displacement']) for row in stores],
                             [('stw', 0x14), ('stb', 0xc), ('stw', 0x18), ('stb', 0xd),
                              ('stw', 0x1c), ('stb', 0xe), ('stw', 0x20), ('stb', 0xf)])
            reads = [row for pc, row in rows.items() if start <= pc < stop and row['mnemonic'] == 'lbz']
            self.assertEqual([row['displacement'] for row in reads], [source_offset] * 4)
            self.assertEqual(sum(row['mnemonic'] == 'lwz' and row.get('rA') == 13
                                 for pc, row in rows.items() if start <= pc < stop), 7)
        self.assertEqual(rows[0x8000bf18]['displacement'], -21700)
        for pc in (0x8000bf88, 0x8000c184, 0x8000c22c, 0x8000c2fc):
            self.assertEqual((rows[pc]['mnemonic'], rows[pc]['displacement']), ('stb', 0x487))

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
