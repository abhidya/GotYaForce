#!/usr/bin/env python3
"""Independent semantic/inverse fixtures:15 instructions,64 bytes,2 fixed reads.

Fixtures are manually authored, not populated by loading reader output or an
archive. Existing optional snapshots are used in place; never fetched.
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

import read_archived_projectile_retirement_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
RANGES = ((0x8007e63c, 60, '955fe1fa85b6c60a40c7e078f9787575519bb7a4455394bc523ae78ec5c932ad'),)
CELLS = (('retirement-state2', 0x802d6fa0, 4, 0x8007e63c,
          '7cc80c32e114c358aba4f4c0ff53230ae0c47acdf8bd9051d0fa1cd6cbc3b830'),)
FIELDS = {'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement',
          'lwz': 'rD rA displacement', 'addi': 'rD rA immediate', 'or': 'rS rA rB Rc',
          'mflr': 'rD', 'mtlr': 'rS', 'bl': 'target AA LK', 'blr': 'BO BI BH LK'}


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


EXPECTED = {0x8007e63c: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
addi 0 0 3
stw 31 1 12
or 3 31 3 0
stb 0 3 0x18
bl 8008aff0 0 1
addi 0 0 0
stb 0 31 0x82
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr 20 0 0 0
''')}


def encode(row, pc):
    """Independent PPC inverse, with no decoder/report/archive dependency."""
    name = row['mnemonic']
    forms = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
             'stb': (38, 'rS', 'displacement'), 'lwz': (32, 'rD', 'displacement'),
             'addi': (14, 'rD', 'immediate')}
    if name in forms:
        opcode, reg, imm = forms[name]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name in ('mflr', 'mtlr'):
        return 31 << 26 | row['rD' if name == 'mflr' else 'rS'] << 21 | 8 << 16 | (339 if name == 'mflr' else 467) << 1
    if name == 'or':
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['rB'] << 11 | 444 << 1 | row['Rc']
    if name == 'bl':
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name == 'blr':
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    raise AssertionError(name)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
PAYLOADS = dict(BODIES)
PAYLOADS[0x802d6fa0] = struct.pack('>I', 0x8007e63c)
SELECTIONS = ((a.cell_evidence, DATA3_MAPPING, 0x802d6fa0, 4),
              (a.range_evidence, TEXT_MAPPING, 0x8007e63c, 60))
EXPECTED_READS = [(199, 115008, 4, 1000128), (21, 495708, 60, 2796416)]


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_exact_inventory_state_arithmetic_and_independent_candidate(self):
        self.assertEqual(a.RANGES, RANGES)
        self.assertEqual(a.CELLS, CELLS)
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(a.DATA3_MAPPING, DATA3_MAPPING)
        self.assertEqual((a.TABLE_ROOT, a.SIGNED_STATE, a.ENTRY_WIDTH), (0x802d6f98, 2, 4))
        self.assertEqual(0x802d6f98 + 2 * 4, CELLS[0][1])
        self.assertEqual(CELLS[0][3], RANGES[0][0])
        self.assertEqual(sum(map(len, PAYLOADS.values())), 64)
        self.assertEqual(len(SELECTIONS), 2)
        self.assertTrue(set(PAYLOADS).isdisjoint({0x802d6f98, 0x802d6f9c, 0x802d6fa4,
                                                 0x8007dcec, 0x8008aff0, 0x8007e678}))

    def test_all15_operands_independent_inverse_hash_and480_decoder_bit_controls(self):
        pc, width, digest = RANGES[0]
        body, rows = BODIES[pc], EXPECTED[pc]
        self.assertEqual(len(body), width)
        self.assertEqual(len(rows), 15)
        self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
        result = a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
        self.assertEqual(result['instructions'], [dict(address=f'{pc + i * 4:08x}', **row)
                                                  for i, row in enumerate(rows)])
        mutations = 0
        for i, row in enumerate(rows):
            address = pc + i * 4
            word = encode(row, address)
            self.assertEqual(a.decode_selected(word, address), row)
            for bit in range(32):
                mutations += 1
                changed = word ^ 1 << bit
                try: decoded = a.decode_selected(changed, address)
                except a.c.FormatError: continue
                if decoded is not None:
                    self.assertNotEqual(decoded, row, (hex(address), bit))
                    self.assertEqual(encode(decoded, address), changed, (hex(address), bit))
        self.assertEqual(mutations, 480)

    def test_source_order_saved_child_helper_return_and_complete_extent(self):
        at = {0x8007e63c + i * 4: row for i, row in enumerate(EXPECTED[0x8007e63c])}
        self.assertEqual(at[0x8007e648], dict(mnemonic='addi', rD=0, rA=0, immediate=3))
        self.assertEqual(at[0x8007e650], dict(mnemonic='or', rS=3, rA=31, rB=3, Rc=0))
        self.assertEqual([(pc, row) for pc, row in at.items() if row['mnemonic'] in ('stb', 'bl')], [
            (0x8007e654, dict(mnemonic='stb', rS=0, rA=3, displacement=0x18)),
            (0x8007e658, dict(mnemonic='bl', target='8008aff0', AA=0, LK=1)),
            (0x8007e660, dict(mnemonic='stb', rS=0, rA=31, displacement=0x82))])
        self.assertEqual(at[0x8007e65c], dict(mnemonic='addi', rD=0, rA=0, immediate=0))
        self.assertFalse(any(row.get('rD') == 3 or (row['mnemonic'] == 'or' and row['rA'] == 3)
                             for row in at.values()))
        self.assertEqual(list(at)[-1], 0x8007e674)
        self.assertEqual(at[0x8007e674], dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
        self.assertEqual(0x8007e678 - 0x8007e63c, 60)
        self.assertEqual([r['address'] for r in a.REUSED_EVIDENCE], ['8007dcec', '8008aff0'])
        self.assertTrue(all(r['read_here'] is False for r in a.REUSED_EVIDENCE))
        # Reuse existing identity/semantics, not an additional archive read.
        import read_archived_projectile_callback_evidence as callback
        self.assertEqual([(int(r['address'], 16), r['width'], r['sha256']) for r in a.REUSED_EVIDENCE],
                         list(callback.RANGES))

    def test_exact_reads_and512_payload_bit_mutations(self):
        mutations = 0
        for (fn, mapping, address, width), call in zip(SELECTIONS, EXPECTED_READS):
            raw = PAYLOADS[address]
            db = FakeDB(raw)
            result = fn(db, mapping, address, width)
            self.assertEqual(db.calls, [call])
            self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
            self.assertEqual(result['width'], width)
            for i in range(len(raw)):
                for bit in range(8):
                    changed = raw[:i] + bytes([raw[i] ^ 1 << bit]) + raw[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        fn(FakeDB(changed), mapping, address, width)
                    mutations += 1
        self.assertEqual(mutations, 512)
        self.assertEqual(a.cell_evidence(FakeDB(PAYLOADS[0x802d6fa0]), DATA3_MAPPING, 0x802d6fa0, 4)['target'],
                         '8007e63c')

    def test_addresses_widths_mapping_types_and_neighbors_refuse_before_read(self):
        for fn, mapping, address, width in SELECTIONS:
            for bad in (address - 1, address + 1, address - 4, address + 4, float(address), True, -1, 1 << 32):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, bad, width)
                self.assertFalse(db.calls)
            for bad in (0, width - 4, width + 4, -width, True, float(width)):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, address, bad)
                self.assertFalse(db.calls)
            for index, value in enumerate(mapping):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    bad = list(mapping); bad[index] = replacement
                    db = FakeDB(PAYLOADS[address])
                    with self.assertRaises(a.c.FormatError): fn(db, tuple(bad), address, width)
                    self.assertFalse(db.calls)
            db = FakeDB(PAYLOADS[address])
            with self.assertRaises(a.c.FormatError): fn(db, list(mapping), address, width)
            self.assertFalse(db.calls)
        for pc in (0x8007dcec, 0x8007e638, 0x8007e678, 0x8007e698, 0x8008aff0):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)
        for pc in (0x802d6f94, 0x802d6f98, 0x802d6f9c, 0x802d6fa4, 0x802d6fa8):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.cell_evidence(db, DATA3_MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_truncation_duplicate_allowlists_wrong_target_and_candidate_refuse(self):
        for fn, mapping, address, width in SELECTIONS:
            for raw in (PAYLOADS[address][:-1], PAYLOADS[address] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'): fn(FakeDB(raw), mapping, address, width)
            name = 'RANGES' if fn == a.range_evidence else 'CELLS'
            with patch.object(a, name, getattr(a, name) * 2):
                db = FakeDB(PAYLOADS[address])
                with self.assertRaises(a.c.FormatError): fn(db, mapping, address, width)
                self.assertFalse(db.calls)
        label, pc, width, target, digest = CELLS[0]
        with patch.object(a, 'CELLS', ((label, pc, width, target + 4, digest),)):
            with self.assertRaisesRegex(a.c.FormatError, 'cell target mismatch'):
                a.cell_evidence(FakeDB(PAYLOADS[pc]), DATA3_MAPPING, pc, width)
        # A changed reported target cannot select another read and fails cross-check.
        with patch.object(a.c, 'inspect', return_value={'image_offset': '80000000'}), \
             patch.object(a.c, 'GBF') as db, patch.object(a.command, 'mappings'), \
             patch.object(a.normal, 'mapping_evidence', side_effect=[(TEXT_MAPPING, {}), (DATA3_MAPPING, {})]), \
             patch.object(a, 'cell_evidence', return_value={'target': '8007e678'}) as cell, \
             patch.object(a, 'range_evidence', return_value={'address': '8007e63c'}) as code:
            db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
            with self.assertRaisesRegex(a.c.FormatError, 'independently selected candidate'): a.inspect(b'x', 'x')
            cell.assert_called_once_with(db.return_value, DATA3_MAPPING, 0x802d6fa0, 4)
            code.assert_called_once_with(db.return_value, TEXT_MAPPING, 0x8007e63c, 60)

    def test_reserved_forms_decoder_bounds_call_and_return_metadata_refuse(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x48000003, 0x94000000, 0x7c0802a7):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x8007e63c)
        for word in (0, 0x48000000, 0x4e800421, 0x4c820020, 0x40800000):
            self.assertIsNone(a.decode_selected(word, 0x8007e63c))
        pc, width, _ = RANGES[0]
        original = a.decode_selected
        with patch.object(a, 'decode_selected', return_value=None):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
        for kind, field, value, error in (
                ('bl', 'target', '80000000', 'direct-call'), ('bl', 'AA', 1, 'direct-call'),
                ('bl', 'LK', 0, 'direct-call'), ('blr', 'BO', 4, 'terminal return'),
                ('blr', 'BI', 1, 'terminal return'), ('blr', 'BH', 1, 'terminal return'),
                ('blr', 'LK', 1, 'terminal return')):
            def changed(word, address):
                row = original(word, address)
                return dict(row, **{field: value}) if row['mnemonic'] == kind else row
            with patch.object(a, 'decode_selected', changed):
                with self.assertRaisesRegex(a.c.FormatError, error):
                    a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
        for kind, error in (('blr', 'terminal return'), ('bl', 'direct-call')):
            def missing(word, address):
                row = original(word, address)
                return dict(mnemonic='addi', rD=0, rA=0, immediate=0) if row['mnemonic'] == kind else row
            with patch.object(a, 'decode_selected', missing):
                with self.assertRaisesRegex(a.c.FormatError, error):
                    a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)

    def test_authentication_precedes_parser_and_both_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad')
            db.assert_not_called(); code.assert_not_called(); cell.assert_not_called()
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(bytes(32), digest)
                db.assert_not_called(); code.assert_not_called(); cell.assert_not_called()
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for key, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[key] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
                db.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'): a.inspect(data, digest)
                db.return_value.rows.assert_not_called(); code.assert_not_called(); cell.assert_not_called()

    def test_mapping_refusals_precede_both_selections(self):
        mappings = a.command.MAPPINGS
        blocks = {key: [name, None, None, 0, start, length, 0] for name, key, start, length, root in mappings}
        subs = {key: [key, 2, length, 0, root, 0] for name, key, start, length, root in mappings}
        cases = []
        for key in (1, 5, 7):
            for field in (4, 5, 6):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][field] += 1
                cases.append((bb, ss, '80000000'))
            for field in range(6):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][field] += 1
                cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); bb[99] = copy.deepcopy(bb[key]); cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); ss[99] = copy.deepcopy(ss[key]); cases.append((bb, ss, '80000000'))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]
                cases.append((bb, ss, '80000000'))
        cases.append((blocks, subs, '80000004'))
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called(); cell.assert_not_called()

    def test_independent_adjacent_sources_no_named_extent_and_no_address_cli(self):
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        source = (root / 'research/decomp/ghidra-export/chunk_0011.c').read_text()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        start = index.index('8007e63c\tFUN_8007e63c\tchunk_0011.c')
        self.assertEqual(index[start + 1], '8007e678\tFUN_8007e678\tchunk_0011.c')
        candidate, suffix = source.split('// ==== 8007e63c ', 1)[1].split('// ==== ', 1)
        self.assertTrue(suffix.startswith('8007e678 '))
        state = candidate.index('*(undefined1 *)(param_1 + 0x18) = 3;')
        helper = candidate.index('zz_008aff0_(param_1);')
        zero = candidate.index('*(undefined1 *)(param_1 + 0x82) = 0;')
        ret = candidate.index('return;')
        self.assertLess(state, helper); self.assertLess(helper, zero); self.assertLess(zero, ret)
        self.assertNotRegex(symbols, r'(?m)^8007e63c ')
        callback = source.split('// ==== 8007dcec ', 1)[1].split('// ==== 8007dd84 ', 1)[0]
        self.assertIn('(&PTR_FUN_802d6f98)[*(char *)(param_1 + 0x18)]', callback)
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/projectile.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', json.loads(error.getvalue())['error'])


SNAPSHOT_DIR = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports, cls.reads, cls.auth_reads = [], [], []
        original = a.c.GBF.chain
        for name in ('db.3.gbf', 'db.4.gbf'):
            raw = (SNAPSHOT_DIR / name).read_bytes()
            digest = hashlib.sha256(raw).hexdigest()
            reads = []
            def traced(db, *args):
                reads.append(args)
                return original(db, *args)
            with patch.object(a.c.GBF, 'chain', traced): a.c.inspect(raw, digest)
            cls.auth_reads.append(reads[:]); reads.clear()
            with patch.object(a.c.GBF, 'chain', traced): cls.reports.append(a.inspect(raw, digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_all_operands_identity_and_static_ceiling_agree(self):
        for key in ('mappings', 'ranges', 'cells', 'function_coverage', 'selection_basis', 'reused_evidence'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            result = report['ranges'][0]
            self.assertEqual(result['instructions'], [dict(address=f'{0x8007e63c + i * 4:08x}', **row)
                                                     for i, row in enumerate(EXPECTED[0x8007e63c])])
            self.assertEqual(report['cells'][0]['target'], result['address'])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_state']), (2, 64, 2))
            self.assertTrue(basis['target_equals_independent_candidate'])
            for key in ('pointer_following', 'helper_read_here', 'other_state_cells_read_here', 'state3_handler_read_here'):
                self.assertFalse(basis[key])
            self.assertIn('not original-DOL identity', report['caveat'])
            self.assertIn('No free/unlink', report['caveat'])

    def test_exact_two_reads_after_unchanged_authentication(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(all(row[0] == 263 for row in auth))
        for report in self.reports:
            coverage, = report['function_coverage']
            self.assertEqual(coverage['represented_instructions'], 15)
            self.assertIsNone(coverage['map_size'])
            self.assertEqual(coverage['unrepresented_instructions'], 0)
            self.assertEqual(coverage['unrepresented_ranges'], [])

    def test_physical_provenance_and_no_raw_payload_output(self):
        expected = {0x802d6fa0: (199, 207, 115008, 362, 4, 3408240),
                    0x8007e63c: (21, 52, 495708, 4368, 60, 872726)}
        for report in self.reports:
            for row in report['cells'] + report['ranges']:
                root, data, chain_offset, data_offset, length, physical = expected[int(row['address'], 16)]
                self.assertEqual(row['spans'], [dict(root_buffer=root, data_buffer=data, chain_offset=chain_offset,
                    data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)])
                self.assertEqual(row['end_exclusive'], f'{int(row["address"], 16) + row["width"]:08x}')
            self.assertEqual(set(report['ranges'][0]), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
            self.assertFalse(any('word' in item for item in report['ranges'][0]['instructions']))
            self.assertEqual(set(report['cells'][0]), {'label', 'address', 'end_exclusive', 'width', 'target', 'sha256', 'spans'})

    def test_real_snapshot_and_selected_payload_tamper_fail_closed(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as code, patch.object(a, 'cell_evidence') as cell:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            code.assert_not_called(); cell.assert_not_called()
        original = a.c.GBF.chain
        for selected_call in EXPECTED_READS:
            def tampered(db, *args):
                payload, spans = original(db, *args)
                if args == selected_call: payload = bytes([payload[0] ^ 1]) + payload[1:]
                return payload, spans
            with patch.object(a.c.GBF, 'chain', tampered):
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)


if __name__ == '__main__':
    unittest.main()
