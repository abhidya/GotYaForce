#!/usr/bin/env python3
"""Independent operands/inverse: 13 instructions, 52 code bytes, one read.

Literal fixtures manually authored; tests never derive fixtures from archive or
reader reports. Synthetic finite-state checks are not original-code execution.
Existing private snapshots are optional, never fetched.
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

import read_archived_rng_evidence as a

ENTRY, WIDTH = 0x800055fc, 52
DIGEST = '74fb9a01b91b2d60cd400a8a96d2781782ea688ddd992f4e5eb472d4b9426438'
TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
EXPECTED_READS = [(21, 28, 52, 2796416)]
# Every operand is independently specified, including otherwise inert fields.
EXPECTED = [
    dict(mnemonic='lbz', rD=0, rA=13, displacement=-21721),
    dict(mnemonic='lbz', rD=4, rA=13, displacement=-21722),
    dict(mnemonic='rlwinm', rS=0, rA=0, SH=8, MB=0, ME=23, Rc=0),
    dict(mnemonic='add', rD=0, rA=0, rB=4, Rc=0),
    dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=16, ME=31, Rc=0),
    dict(mnemonic='mulli', rD=0, rA=0, immediate=3),
    dict(mnemonic='srawi', rS=0, rA=3, SH=8, Rc=0),
    dict(mnemonic='rlwinm', rS=3, rA=0, SH=0, MB=24, ME=31, Rc=0),
    dict(mnemonic='stb', rS=3, rA=13, displacement=-21721),
    dict(mnemonic='add', rD=0, rA=4, rB=0, Rc=0),
    dict(mnemonic='stb', rS=0, rA=13, displacement=-21722),
    dict(mnemonic='rlwinm', rS=0, rA=3, SH=0, MB=24, ME=31, Rc=0),
    dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0),
]


def encode(row):
    """Independent inverse PPC bit placement, with no reader/report inputs."""
    name = row['mnemonic']
    if name in ('lbz', 'stb', 'mulli'):
        op, register, imm = {'lbz': (34, 'rD', 'displacement'),
                             'stb': (38, 'rS', 'displacement'),
                             'mulli': (7, 'rD', 'immediate')}[name]
        return op << 26 | row[register] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name == 'rlwinm':
        return (21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 |
                row['MB'] << 6 | row['ME'] << 1 | row['Rc'])
    if name == 'add':
        return 31 << 26 | row['rD'] << 21 | row['rA'] << 16 | row['rB'] << 11 | 266 << 1 | row['Rc']
    if name == 'srawi':
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | 824 << 1 | row['Rc']
    if name == 'blr':
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    raise AssertionError(name)


BODY = b''.join(struct.pack('>I', encode(row)) for row in EXPECTED)


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


def synthetic_step(high, low):
    """Evaluate only the literal fixture; no runtime imports or original bytes."""
    r, memory, events, carry = [0] * 32, {-21721: high, -21722: low}, [], None
    for row in EXPECTED:
        name = row['mnemonic']
        if name in ('lbz', 'stb'):
            address = r[row['rA']] + row['displacement']
            if name == 'lbz':
                r[row['rD']] = memory[address]
                events.append(('load', address, 1, memory[address]))
            else:
                memory[address] = r[row['rS']] & 255
                events.append(('store', address, 1, memory[address]))
        elif name == 'rlwinm':
            value, shift = r[row['rS']], row['SH']
            rotated = ((value << shift) | (value >> ((32 - shift) % 32))) & 0xffffffff
            mask = sum(1 << (31 - bit) for bit in range(row['MB'], row['ME'] + 1))
            r[row['rA']] = rotated & mask
        elif name == 'add':
            r[row['rD']] = (r[row['rA']] + r[row['rB']]) & 0xffffffff
        elif name == 'mulli':
            value = r[row['rA']]
            signed = value - (1 << 32) if value >> 31 else value
            r[row['rD']] = signed * row['immediate'] & 0xffffffff
        elif name == 'srawi':
            value, shift = r[row['rS']], row['SH']
            signed = value - (1 << 32) if value >> 31 else value
            carry = int(signed < 0 and bool(value & ((1 << shift) - 1)))
            r[row['rA']] = signed >> shift & 0xffffffff
        elif name != 'blr':
            raise AssertionError(name)
    return memory[-21721], memory[-21722], r[3], carry, events


class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_independent_source_index_map_extent(self):
        self.assertEqual(a.RANGES, ((ENTRY, WIDTH, DIGEST),))
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        self.assertEqual(index[16], '800055fc\tzz_00055fc_\tchunk_0000.c')
        self.assertEqual(index[17], '80005630\tzz_0005630_\tchunk_0000.c')
        source = (root / 'research/decomp/ghidra-export/chunk_0000.c').read_text().splitlines()[372:386]
        self.assertEqual(source[0], '// ==== 800055fc  zz_00055fc_ ====')
        self.assertEqual(source[-1], '}')
        self.assertIn('DAT_804360c7', '\n'.join(source))
        self.assertIn('DAT_804360c6', '\n'.join(source))
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text().splitlines()
        self.assertEqual(symbols[16], '800055fc 00000034 800055fc 0 zz_00055fc_')

    def test_all13_operands_independent_inverse_and416_bit_controls(self):
        self.assertEqual(len(BODY), WIDTH)
        self.assertEqual(hashlib.sha256(BODY).hexdigest(), DIGEST)
        report = a.range_evidence(FakeDB(BODY), TEXT_MAPPING, ENTRY, WIDTH)
        self.assertEqual(report['instructions'], [dict(address=f'{ENTRY + i * 4:08x}', **row)
                                                  for i, row in enumerate(EXPECTED)])
        mutations = 0
        for i, row in enumerate(EXPECTED):
            word, pc = encode(row), ENTRY + i * 4
            self.assertEqual(a.decode_selected(word, pc), row)
            for bit in range(32):
                mutations += 1
                changed = word ^ 1 << bit
                try: decoded = a.decode_selected(changed, pc)
                except a.c.FormatError: continue
                if decoded is not None:
                    self.assertNotEqual(decoded, row, (hex(pc), bit))
                    self.assertEqual(encode(decoded), changed, (hex(pc), bit))
        self.assertEqual(mutations, 416)

    def test_exact_single_read_and416_payload_bit_refusals_before_decode(self):
        db = FakeDB(BODY)
        a.range_evidence(db, TEXT_MAPPING, ENTRY, WIDTH)
        self.assertEqual(db.calls, EXPECTED_READS)
        mutations = 0
        with patch.object(a, 'decode_selected') as decoder:
            for i in range(WIDTH):
                for bit in range(8):
                    changed = BODY[:i] + bytes([BODY[i] ^ 1 << bit]) + BODY[i + 1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                        a.range_evidence(FakeDB(changed), TEXT_MAPPING, ENTRY, WIDTH)
                    mutations += 1
            decoder.assert_not_called()
        self.assertEqual(mutations, 416)

    def test_all65536_byte_states_source_formula_order_width_and_carry(self):
        for high in range(256):
            for low in range(256):
                actual = synthetic_step(high, low)
                next_high = ((high * 256 + low) * 3 // 256) % 256
                next_low = (low + next_high) % 256
                self.assertEqual(actual, (next_high, next_low, next_low, 0,
                    [('load', -21721, 1, high), ('load', -21722, 1, low),
                     ('store', -21721, 1, next_high), ('store', -21722, 1, next_low)]))

    def test_boundary_vectors_no_new_low_feedback_and_no_call(self):
        for high, low, next_high, next_low in ((0, 0, 0, 0), (0, 255, 2, 1),
                (1, 0, 3, 3), (85, 85, 255, 84), (85, 86, 0, 86), (255, 255, 255, 254)):
            self.assertEqual(synthetic_step(high, low)[:3], (next_high, next_low, next_low))
        self.assertEqual(a.expected_flow(), [dict(address='8000562c', **EXPECTED[-1])])
        self.assertEqual([row['mnemonic'] for row in EXPECTED],
                         ['lbz', 'lbz', 'rlwinm', 'add', 'rlwinm', 'mulli', 'srawi',
                          'rlwinm', 'stb', 'add', 'stb', 'rlwinm', 'blr'])
        self.assertTrue(all(row.get('Rc', 0) == 0 for row in EXPECTED))

    def test_addresses_widths_duplicate_ranges_and_exact_typed_maps_refuse(self):
        for pc, width in [(bad, WIDTH) for bad in (ENTRY - 4, ENTRY + 4, ENTRY + 1,
                float(ENTRY), True, -1, 1 << 32, 0x804360c6, 0x804360c7)] + [
                (ENTRY, bad) for bad in (0, WIDTH - 4, WIDTH + 4, -WIDTH, True, float(WIDTH))]:
            db = FakeDB(BODY)
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, width)
            self.assertFalse(db.calls)
        for index, value in enumerate(TEXT_MAPPING):
            for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                changed = list(TEXT_MAPPING); changed[index] = replacement; db = FakeDB(BODY)
                with self.assertRaises(a.c.FormatError):
                    a.range_evidence(db, tuple(changed), ENTRY, WIDTH)
                self.assertFalse(db.calls)
        with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(BODY), list(TEXT_MAPPING), ENTRY, WIDTH)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            db = FakeDB(BODY)
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, ENTRY, WIDTH)
            self.assertFalse(db.calls)
        for raw in (BODY[:-1], BODY + b'\0'):
            with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                a.range_evidence(FakeDB(raw), TEXT_MAPPING, ENTRY, WIDTH)

    def test_decoder_bounds_reserved_bits_and_control_metadata_refuse(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for bit in range(32):
            changed = encode(EXPECTED[-1]) ^ 1 << bit
            if changed >> 26 == 19:
                with self.assertRaises(a.c.FormatError): a.decode_selected(changed, ENTRY)
        self.assertIsNone(a.decode_selected(encode(EXPECTED[3]) | 1 << 10, ENTRY))  # add OE1
        original = a.decode_selected
        with patch.object(a, 'decode_selected', return_value=None):
            with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                a.range_evidence(FakeDB(BODY), TEXT_MAPPING, ENTRY, WIDTH)
        for field, value in EXPECTED[-1].items():
            replacement = 'add' if field == 'mnemonic' else value ^ 1
            def changed(word, pc):
                row = original(word, pc)
                return dict(row, **{field: replacement}) if pc == 0x8000562c else row
            with patch.object(a, 'decode_selected', changed):
                with self.assertRaisesRegex(a.c.FormatError, 'complete control-flow mismatch'):
                    a.range_evidence(FakeDB(BODY), TEXT_MAPPING, ENTRY, WIDTH)

    def test_authentication_precedes_parser_and_selection(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad'); db.assert_not_called(); code.assert_not_called()

    def test_mapping_refusal_precedes_selection(self):
        blocks, subs = {}, {}
        for name, key, start, length, root in a.command.MAPPINGS:
            blocks[key] = [name, None, None, 15, start, length, 0]
            subs[key] = [key, 2, length, 0, root, 0]
        cases = []
        for key in (1, 5, 7):
            for field, value in ((0, 'wrong'), (4, blocks[key][4] + 4), (5, blocks[key][5] + 4), (6, 1)):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][field] = value; cases.append((bb, ss, '80000000'))
            for field in range(6):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][field] += 1; cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); bb[99] = copy.deepcopy(bb[key]); cases.append((bb, ss, '80000000'))
            bb, ss = copy.deepcopy((blocks, subs)); ss[99] = copy.deepcopy(ss[key]); cases.append((bb, ss, '80000000'))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]
                cases.append((bb, ss, '80000000'))
        cases.append((blocks, subs, '80000004'))
        self.assertEqual(len(cases), 43)
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called()

    def test_no_arbitrary_cli_and_missing_snapshot(self):
        for option in ('--address', '--width', '--pointer', '--target', '--dump', '--state'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/rng.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
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
            raw = (SNAPSHOT_DIR / name).read_bytes(); digest = hashlib.sha256(raw).hexdigest(); reads = []
            def traced(db, *args):
                reads.append(args)
                return original(db, *args)
            with patch.object(a.c.GBF, 'chain', traced): a.c.inspect(raw, digest)
            cls.auth_reads.append(reads[:]); reads.clear()
            with patch.object(a.c.GBF, 'chain', traced): cls.reports.append(a.inspect(raw, digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_exact_operands_coverage_and_ceiling(self):
        for key in ('mappings', 'ranges', 'function_coverage', 'selection_basis'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([row['snapshot'] for row in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([row['snapshot_sha256'] for row in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(report['ranges'][0]['instructions'],
                             [dict(address=f'{ENTRY + i * 4:08x}', **row) for i, row in enumerate(EXPECTED)])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (1, 52, 0))
            for key in ('pointer_following', 'global_payloads_read', 'callee_bodies_read',
                        'globals_runtime_values_established', 'original_execution', 'initial_rng_bytes_read'):
                self.assertFalse(basis[key])
            self.assertIn('not original-DOL identity', report['caveat'])
            row = report['function_coverage'][0]
            self.assertEqual(row['represented_instructions'], 13)
            self.assertEqual(row['unrepresented_instructions'], 0)
            self.assertEqual(row['unrepresented_ranges'], [])
            self.assertEqual(row['selected_width'], row['map_size'])

    def test_exact_single_selected_read_after_unchanged_authentication(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(auth)
            self.assertTrue(all(row[0] == 263 for row in auth))

    def test_physical_span_and_no_raw_output(self):
        for report in self.reports:
            row = report['ranges'][0]
            self.assertEqual(row['spans'], [dict(root_buffer=21, data_buffer=22, chain_offset=28,
                data_offset=28, length=52, obfuscated=True, physical_offset=376866)])
            self.assertEqual(row['end_exclusive'], '80005630')
            self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
            self.assertFalse(any('word' in item or 'bytes' in item for item in row['instructions']))

    def test_real_snapshot_hash_schema_and_selected_payload_refuse(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes(); digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as code:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            code.assert_not_called()
        original_tables = a.c.GBF.tables
        for name in ('Program', 'Property Table', 'File Bytes', 'ADDRESS MAP', 'Memory Blocks', 'Sub Memory Blocks'):
            for field in ('version', 'keytype', 'types', 'fields', 'missing'):
                def tampered_tables(db):
                    tables = copy.deepcopy(original_tables(db))
                    if field == 'missing': del tables[name]
                    elif field == 'types': tables[name][field] = [99]
                    elif field == 'fields': tables[name][field] = 'Wrong;'
                    else: tables[name][field] += 1
                    return tables
                with patch.object(a.c.GBF, 'tables', tampered_tables), patch.object(a, 'range_evidence') as code:
                    with self.assertRaises(a.c.FormatError): a.inspect(raw, digest)
                    code.assert_not_called()
        original = a.c.GBF.chain
        def tampered(db, *args):
            payload, spans = original(db, *args)
            if args == EXPECTED_READS[0]: payload = bytes([payload[0] ^ 1]) + payload[1:]
            return payload, spans
        with patch.object(a.c.GBF, 'chain', tampered), patch.object(a, 'decode_selected') as decode:
            with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)
            decode.assert_not_called()


if __name__ == '__main__': unittest.main()
