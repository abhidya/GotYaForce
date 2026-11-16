#!/usr/bin/env python3
"""All 192 independent operands, inverse encoding and bounded-read controls.

Synthetic/source tests need only this checkout. Local-archive tests use the
existing ignored snapshots, or GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR, and skip if
both are unavailable. They never fetch archives or read scratch reports.
"""
import contextlib
import copy
import hashlib
import io
import os
from pathlib import Path
import re
import struct
import unittest
from unittest.mock import patch

import read_archived_control40_helper_evidence as a
from control40_helper_expected_operands import EXPECTED, encode

ROOT = Path(__file__).resolve().parents[3]
# Exact independently selected entry/next-entry rows, not discovered from bytes.
# Provenance is also recorded in control40-helper-evidence-2026-11-14.md.
SOURCE_SELECTION = (
    (0x80069210, 172, 1342, 'zz_0069210_', 1343, 'FUN_800692bc', 'chunk_0008.c'),
    (0x800693fc, 196, 1345, 'FUN_800693fc', 1346, 'zz_00694c0_', 'chunk_0008.c'),
    (0x8006965c, 152, 1352, 'FUN_8006965c', 1353, 'FUN_800696f4', 'chunk_0009.c'),
    (0x800695c4, 96, 1350, 'FUN_800695c4', 1351, 'FUN_80069624', 'chunk_0008.c'),
    (0x8006952c, 96, 1348, 'FUN_8006952c', 1349, 'FUN_8006958c', 'chunk_0008.c'),
    (0x800691d8, 56, 1341, 'FUN_800691d8', 1342, 'zz_0069210_', 'chunk_0008.c'),
)


def packed(address):
    return b''.join(struct.pack('>I', encode(item, address + 4 * n))
                    for n, item in enumerate(EXPECTED[address]))


def operands(address):
    return [dict(address=f'{address + 4 * n:08x}', **item)
            for n, item in enumerate(EXPECTED[address])]


class FakeDB:
    def __init__(self, data):
        self.data, self.reads = data, []

    def chain(self, *args):
        self.reads.append(args)
        return self.data, []


class FixedTests(unittest.TestCase):
    def test_all_192_explicit_operands_and_inverse_hashes(self):
        self.assertEqual(len(EXPECTED), 6)
        self.assertEqual(sum(map(len, EXPECTED.values())), 192)
        for address, width, digest in a.RANGES:
            with self.subTest(address=hex(address)):
                raw = packed(address)
                self.assertEqual(len(raw), width)
                self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
                for n, expected in enumerate(EXPECTED[address]):
                    self.assertEqual(a.decode_selected(struct.unpack_from('>I', raw, n * 4)[0],
                                                       address + n * 4), expected)
                db = FakeDB(raw)
                row = a.range_evidence(db, 21, address, width)
                self.assertEqual(db.reads, [(21, address - a.TEXT_START, width, a.TEXT_LENGTH)])
                self.assertEqual(row['instructions'], operands(address))
                self.assertEqual(row['control_flow']['cfg_reachable_instructions'], len(EXPECTED[address]))

    def test_every_single_bit_window_mutation_fails(self):
        count = 0
        for address, width, _ in a.RANGES:
            good = packed(address)
            for n in range(width):
                for bit in range(8):
                    raw = bytearray(good)
                    raw[n] ^= 1 << bit
                    with self.assertRaisesRegex(a.c.FormatError, 'digest'):
                        a.range_evidence(FakeDB(raw), 21, address, width)
                    count += 1
        self.assertEqual(count, 6144)

    def test_wrong_root_extent_type_and_unselected_addresses_fail_before_read(self):
        db = FakeDB(b'')
        for address, width, _ in a.RANGES:
            for args in ((22, address, width), (21, address + 4, width),
                         (21, address, width + 4), (21, address, width - 4),
                         (True, address, width), (21, float(address), width),
                         (21, address, float(width))):
                with self.subTest(args=args), self.assertRaises(a.c.FormatError):
                    a.range_evidence(db, *args)
        for address, width in ((0x800694c0, 40), (0x800696f4, 148), (0x80069814, 76),
                               (0x800699d8, 100), (0x80437250, 4), (0x800692bc, 4),
                               (0x8006958c, 56), (0x4ac, 4), (0x9f, 1)):
            with self.assertRaisesRegex(a.c.FormatError, 'allowlisted'):
                a.range_evidence(db, 21, address, width)
        self.assertEqual(db.reads, [])
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'allowlisted'):
                a.range_evidence(db, 21, 0x80069210, 172)
        self.assertEqual(db.reads, [])

    def test_truncated_extra_and_empty_reads_fail_before_decode(self):
        for address, width, _ in a.RANGES:
            raw = packed(address)
            for bad in (raw[:-1], raw + b'\0', b''):
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, 'width'):
                        a.range_evidence(FakeDB(bad), 21, address, width)
                    decoder.assert_not_called()

    def test_cfg_terminal_bounds_call_and_fields_fail(self):
        address, width = 0x80069210, 172
        base = operands(address)
        changes = [(-1, 'mnemonic', 'addi'), (-1, 'BO', 4), (-1, 'BI', 1),
                   (-1, 'BH', 1), (-1, 'LK', 1), (5, 'target', '800692bc'),
                   (5, 'target', '80069211'), (5, 'target', '80069210'),
                   (5, 'AA', 1), (5, 'LK', 1), (5, 'BO', 16), (5, 'BI', 7),
                   (38, 'target', '800677b0'), (38, 'LK', 0), (38, 'AA', 1),
                   (1, 'address', '80069210')]
        for n, key, value in changes:
            bad = copy.deepcopy(base)
            bad[n][key] = value
            with self.subTest(n=n, key=key), self.assertRaises(a.c.FormatError):
                a.control_flow(bad, address, width)
        with self.assertRaisesRegex(a.c.FormatError, 'coverage'):
            a.control_flow(base[:-1], address, width)
        bad = copy.deepcopy(base)
        bad[1] = dict(address=bad[1]['address'], mnemonic='blr', BO=20, BI=0, BH=0, LK=0)
        with self.assertRaisesRegex(a.c.FormatError, 'interior return'):
            a.control_flow(bad, address, width)
        bad = copy.deepcopy(base)
        bad[5] = dict(address=bad[5]['address'], mnemonic='b', target='80069230', AA=0, LK=0)
        with self.assertRaisesRegex(a.c.FormatError, 'unreachable instruction'):
            a.control_flow(bad, address, width)

    def test_decoder_bounds_reserved_and_unselected_forms(self):
        for word, pc in ((-1, 0), (2**32, 0), (True, 0), (0, True), (0, -4),
                         (0, 1), (0, 2**32), (1.0, 0), (0, 4.0)):
            with self.assertRaises(a.c.FormatError):
                a.decode_selected(word, pc)
        for word in (0, 0x60000000, 0x4e800420, 0x4d820020, 48 << 26,
                     10 << 26, 31 << 26 | 104 << 1):
            self.assertIsNone(a.decode_selected(word, 0x80069210))
        for word in (31 << 26 | 8 << 16 | 339 << 1 | 1,
                     31 << 26 | 1 << 21 | 8 << 16 | 339 << 1,
                     31 << 26 | 9 << 16 | 467 << 1,
                     31 << 26 | 1 << 11 | 954 << 1, 31 << 26 | 1,
                     11 << 26 | 1 << 21, 31 << 26 | 1 << 22):
            with self.assertRaises(a.c.FormatError):
                a.decode_selected(word, 0x80069210)

    def test_lhz_signed_displacement_and_branch_inverse_boundaries(self):
        for reg in (0, 1, 31):
            for disp in (-32768, -1, 0, 32767):
                row = dict(mnemonic='lhz', rD=reg, rA=31 - reg, displacement=disp)
                self.assertEqual(a.decode_selected(encode(row, 0x80000000), 0x80000000), row)
        for name in ('b', 'bl', 'bc'):
            for aa in (0, 1):
                deltas = (-32768, -4, 0, 32764) if name == 'bc' else (-33554432, -4, 0, 33554428)
                for delta in deltas:
                    pc = 0x80000000
                    target = (delta if aa else pc + delta) & 0xffffffff
                    row = dict(mnemonic=name, target=f'{target:08x}', AA=aa, LK=int(name == 'bl'))
                    if name == 'bc':
                        row.update(BO=4, BI=2)
                    self.assertEqual(a.decode_selected(encode(row, pc), pc), row)

    def test_cli_has_only_snapshot_argument(self):
        for option in ('--address', '--width', '--pointer', '--target', '--dump', '--raw', '--execute'):
            with patch('sys.argv', ['reader', 'none', option, '0']), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as error:
                    a.main()
                self.assertEqual(error.exception.code, 2)
                inspect.assert_not_called()
        with patch('sys.argv', ['reader', '/nonexistent/control40.gbf']), \
                contextlib.redirect_stderr(io.StringIO()) as output:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', output.getvalue())

    def test_authentication_precedes_parser_and_ranges(self):
        with patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as selected:
            with self.assertRaisesRegex(a.c.FormatError, 'SHA256'):
                a.inspect(bytes(64), '0' * 64)
            db.assert_not_called()
            selected.assert_not_called()

    def test_source_selection_extents_markers_and_only_one_map_row(self):
        self.assertEqual([(pc, size) for pc, size, *_ in SOURCE_SELECTION],
                         [(pc, size) for pc, size, _ in a.RANGES])
        index = (ROOT / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        for pc, size, first, name, next_line, next_name, filename in SOURCE_SELECTION:
            self.assertEqual(next_line, first + 1)
            self.assertEqual(index[first - 1], f'{pc:08x}\t{name}\t{filename}')
            self.assertEqual(index[next_line - 1], f'{pc + size:08x}\t{next_name}\t{filename}')
            source = (ROOT / 'research/decomp/ghidra-export' / filename).read_text()
            markers = re.findall(r'^// ==== ([0-9a-f]{8})  (\S+) ====$', source, re.M)
            position = markers.index((f'{pc:08x}', name))
            self.assertEqual(markers[position + 1], (f'{pc + size:08x}', next_name))
        symbol = (ROOT / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        matches = [line for line in symbol.splitlines() if re.search(r'\b80069210\b', line)]
        self.assertEqual(matches, ['80069210 000000ac 80069210 0 zz_0069210_'])
        for address, _, _ in a.RANGES:
            if address != 0x80069210:
                self.assertNotRegex(symbol, rf'\b{address:08x}\b')

    def test_shared_allowlists_unchanged(self):
        for address, width, _ in a.RANGES:
            self.assertNotIn((address, width), a.c.TARGETS)
            with self.assertRaisesRegex(a.c.FormatError, 'allowlisted'):
                a.command.read_range(None, address, width, 0x80000000)
            with self.assertRaisesRegex(a.c.FormatError, 'allowlisted'):
                a.status.range_evidence(None, 21, address, width)

    def test_exact_mapping_rejections_precede_selection(self):
        auth = {'image_offset': '80000000'}
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0]
                for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('root', 'offset', 'type', 'duplicate', 'overlap', 'image',
                       'data5root', 'data5offset', 'data5length',
                       'data3root', 'data3offset', 'data3length'):
            aa, bb, ss = copy.deepcopy((auth, blocks, subs))
            if target == 'root': ss[1][4] += 1
            if target == 'offset': ss[1][5] += 1
            if target == 'type': ss[1][1] += 1
            if target == 'duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x20000000000055e4, 4, 0]
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'data5root': ss[7][4] += 1
            if target == 'data5offset': ss[7][5] += 4
            if target == 'data5length': bb[7][5] -= 4
            if target == 'data3root': ss[5][4] += 1
            if target == 'data3offset': ss[5][5] += 4
            if target == 'data3length': bb[5][5] -= 4
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as selected:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'blocks', 'Sub Memory Blocks': 'subs'}
                db.rows.side_effect = lambda name: {'blocks': bb, 'subs': ss}[name]
                with self.subTest(target=target), self.assertRaises(a.c.FormatError):
                    a.inspect(b'synthetic', 'synthetic')
                selected.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(path.is_file() for path in paths):
            raise unittest.SkipTest('both local archives required; never fetch')
        cls.inputs, cls.reports, cls.reads = [], [], []
        original = a.c.GBF.chain
        for path in paths:
            a.c.require(32 <= path.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with path.open('rb') as stream:
                data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            digest, reads = hashlib.sha256(data).hexdigest(), []

            def traced(db, *args):
                reads.append(args)
                return original(db, *args)

            with patch.object(a.c.GBF, 'chain', traced):
                report = a.inspect(data, digest)
            cls.inputs.append((data, digest))
            cls.reports.append(report)
            cls.reads.append(reads)

    def test_snapshot_agreement_and_complete_derived_reports(self):
        normalized = [{key: value for key, value in report.items()
                       if key not in ('snapshot', 'snapshot_sha256')} for report in self.reports]
        self.assertEqual(*normalized)
        for report in self.reports:
            self.assertEqual(report['total_new_selected_bytes'], 768)
            self.assertEqual(report['total_instructions'], 192)
            self.assertEqual(len(report['ranges']), 6)
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(sum(len(row['control_flow']['internal_branches'])
                                 for row in report['ranges']), 46)
            self.assertEqual(sum(len(row['control_flow']['direct_calls'])
                                 for row in report['ranges']), 7)

            def no_raw(value):
                if isinstance(value, dict):
                    self.assertTrue(set(value).isdisjoint(('raw', 'word', 'words', 'hex', 'bytes', 'bits')))
                    for child in value.values(): no_raw(child)
                elif isinstance(value, list):
                    for child in value: no_raw(child)

            no_raw(report)

    def test_exact_only_six_text_reads_after_existing_authentication(self):
        auth = [(263, 0, 27360, 27360)] + [
            (263, address - 0x80436a20, width, 27360) for address, width in a.c.TARGETS]
        expected = auth + [(21, address - a.TEXT_START, width, a.TEXT_LENGTH)
                           for address, width, _ in a.RANGES]
        self.assertEqual(len(expected), 19)
        for reads in self.reads:
            self.assertEqual(reads, expected)

    def test_real_selected_operands_equal_independent_transcription(self):
        for report in self.reports:
            self.assertEqual([row['address'] for row in report['ranges']],
                             [f'{address:08x}' for address, _, _ in a.RANGES])
            for row, (address, width, digest) in zip(report['ranges'], a.RANGES):
                self.assertEqual(row['instructions'], operands(address))
                self.assertEqual(row['sha256'], digest)
                self.assertEqual(row['end_exclusive'], f'{address + width:08x}')
                self.assertEqual(row['map_size'], 172 if address == 0x80069210 else None)
                flow = row['control_flow']
                self.assertEqual(flow['terminal_return'], f'{address + width - 4:08x}')
                self.assertEqual(flow['represented_instructions'], width // 4)
                self.assertEqual(flow['cfg_reachable_instructions'], width // 4)
                self.assertEqual(flow['unrepresented_instructions'], 0)
                self.assertEqual(flow['unrepresented_ranges'], [])
                self.assertEqual(flow['interior_returns'], [])
                self.assertTrue(flow['all_internal_edges_forward'])

    def test_physical_spans_including_split_instruction(self):
        expected = [
            [(46, 408624, 15552, 785606, 172)],
            [(46, 409116, 16044, 786098, 196)],
            [(47, 409724, 274, 786712, 152)],
            [(47, 409572, 122, 786560, 96)],
            [(46, 409420, 16348, 786402, 30), (47, 409450, 0, 786438, 66)],
            [(46, 408568, 15496, 785550, 56)],
        ]
        for report in self.reports:
            for row, spans in zip(report['ranges'], expected):
                self.assertEqual(row['spans'], [dict(root_buffer=21, data_buffer=buffer,
                    chain_offset=chain, data_offset=offset, length=length,
                    obfuscated=True, physical_offset=physical)
                    for buffer, chain, offset, physical, length in spans])

    def test_changed_snapshot_or_spoofed_digest_fails_before_parse(self):
        for data, digest in self.inputs:
            bad = bytearray(data)
            bad[100] ^= 1
            for raw, sha in ((bad, digest), (bad, hashlib.sha256(bad).hexdigest()), (data, '0' * 64)):
                with patch.object(a.c, 'GBF') as db:
                    with self.assertRaisesRegex(a.c.FormatError, 'SHA256'):
                        a.inspect(raw, sha)
                    db.assert_not_called()

    def test_auth_schema_file_bytes_rejections_precede_selection(self):
        original = a.c.GBF.tables
        data, digest = self.inputs[0]
        changes = [('Program', 'version', 9), ('Property Table', 'types', [4, 2]),
                   ('File Bytes', 'root', 7), ('File Bytes', 'count', 1),
                   ('ADDRESS MAP', 'version', 2), ('Memory Blocks', 'types', []),
                   ('Sub Memory Blocks', 'keytype', 4)]
        for table, key, value in changes:
            def altered(db):
                result = copy.deepcopy(original(db))
                result[table][key] = value
                return result

            with patch.object(a.c.GBF, 'tables', altered), patch.object(a, 'range_evidence') as selected:
                with self.subTest(table=table, key=key), self.assertRaises(a.c.FormatError):
                    a.inspect(data, digest)
                selected.assert_not_called()

    def test_auth_metadata_map_rejections_precede_selection(self):
        original = a.c.GBF.rows
        data, digest = self.inputs[0]
        changes = [(2, 'Program Name', ['other']), (2, 'Language ID', ['other']),
                   (2, 'Image Offset', ['bad!']),
                   (9, 'Program Information.Executable SHA256', ['0' * 64, 2]),
                   (9, 'Program Information.Created With Ghidra Version', ['12.1.2', 0]),
                   (10, 0, ['rom', 0, False]), (12, 1, [1, 2, a.TEXT_LENGTH, 0, 22, 0])]
        for root, key, value in changes:
            def altered(db, table):
                result = copy.deepcopy(original(db, table))
                if table['root'] == root: result[key] = value
                return result

            with patch.object(a.c.GBF, 'rows', altered), patch.object(a, 'range_evidence') as selected:
                with self.subTest(root=root, key=key), self.assertRaises(a.c.FormatError):
                    a.inspect(data, digest)
                selected.assert_not_called()

    def test_auth_data5_hash_and_control_rejections_precede_selection(self):
        original = a.c.GBF.chain
        data, digest = self.inputs[0]
        for changed in ((263, 0, 27360, 27360), (263, 0x8043d1f8 - 0x80436a20, 4, 27360),
                        (263, 0x80437148 - 0x80436a20, 4, 27360)):
            def altered(db, *args):
                raw, spans = original(db, *args)
                if args == changed: raw = bytes([raw[0] ^ 1]) + raw[1:]
                return raw, spans

            with patch.object(a.c.GBF, 'chain', altered), patch.object(a, 'range_evidence') as selected:
                with self.subTest(args=changed), self.assertRaises(a.c.FormatError):
                    a.inspect(data, digest)
                selected.assert_not_called()


if __name__ == '__main__':
    unittest.main(verbosity=2)
