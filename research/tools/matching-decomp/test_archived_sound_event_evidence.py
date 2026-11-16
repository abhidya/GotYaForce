#!/usr/bin/env python3
"""Frozen full-operand/inverse witnesses and fail-closed sound-helper tests.

Synthetic tests do not need private inputs. Archive tests use the two existing
snapshots only and skip if absent. No original instruction execution.
"""
import contextlib
import copy
import hashlib
import io
import json
import os
from pathlib import Path
import re
import struct
import unittest
from unittest.mock import patch

import read_archived_sound_event_evidence as a
import test_archived_double_action_evidence as previous

FakeDB = previous.FakeDB
FIELDS = dict(previous.FIELDS, fcmpu='BF fA fB')


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


# Fixed independently reviewed instruction schedule, never generated during tests.
EXPECTED = ops('''
stwu 1 1 -16
mflr 0
lfd 3 2 -30216
stw 0 1 20
addis 0 0 17200
lfs 4 2 -30268
lhz 5 4 0
stw 0 1 8
stw 5 1 12
lfd 0 1 8
fsubs 0 0 3 0
fcmpu 0 4 0
bc 4 2 0 8005b9c8 0
fcmpo 0 1 4
bc 12 1 0 8005baa8 0
addis 0 0 17200
stw 5 1 12
lfd 4 2 -30216
stw 0 1 8
lfs 0 2 -30268
lfd 3 1 8
fsubs 3 3 4 0
fcmpo 0 3 0
bc 4 1 0 8005ba24 0
stw 5 1 12
stw 0 1 8
lfd 0 1 8
fsubs 0 0 4 0
fcmpo 0 1 0
bc 12 0 0 8005baa8 0
stw 5 1 12
stw 0 1 8
lfd 0 1 8
fsubs 0 0 4 0
fcmpo 0 2 0
cror 2 1 2
bc 4 2 0 8005ba24 0
b 8005baa8 0 0
lbz 0 4 3
cmpi 0 0 0 1
bc 12 2 0 8005ba5c 0
bc 4 0 0 8005ba40 0
cmpi 0 0 0 0
bc 4 0 0 8005ba50 0
b 8005baa8 0 0
cmpi 0 0 0 4
bc 12 2 0 8005baa8 0
bc 4 0 0 8005baa8 0
b 8005ba9c 0 0
lhz 4 4 4
bl 800f036c 0 1
b 8005baa8 0 0
lfs 1 3 180
lfs 0 2 -30228
fcmpo 0 1 0
bc 4 0 0 8005ba78 0
lhz 4 4 4
addi 4 4 -1
b 8005ba94 0 0
lfs 0 2 -30224
fcmpo 0 1 0
bc 4 1 0 8005ba90 0
lhz 4 4 4
addi 4 4 1
b 8005ba94 0 0
lhz 4 4 4
bl 800f036c 0 1
b 8005baa8 0 0
lhz 4 4 4
lfs 1 2 -30236
bl 800f061c 0 1
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
''')


def encode(row, pc):
    """Independent inverse encoding; never calls any reader or decoder."""
    if row['mnemonic'] == 'fcmpu':
        return 63 << 26 | row['BF'] << 23 | row['fA'] << 16 | row['fB'] << 11
    return previous.encode(row, pc)


def at():
    return {0x8005b98c + 4 * i: row for i, row in enumerate(EXPECTED)}


SCALARS = (
    (0x804373e4, '00000000', 0.0, 'df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119'),
    (0x80437418, '4330000000000000', 4503599627370496.0, '2b2979f362d94c89fe17a6e01637f14332de063fe7a544bdc5facfc046f4169f'),
    (0x8043740c, '3f333333', 0.699999988079071, 'fe3ddc91b044dfc5ee07935a7f3e8f4cbe8e4c6af60c9ce5db25c5c81da15178'),
    (0x80437410, '40000000', 2.0, 'c31425b44a7ed682a3356bf6820141e1584a15c43b6d6793f552e5d4621586f7'),
    (0x80437404, '3e4ccccd', 0.20000000298023224, 'cea23fc0ff6ff5c3256ac12d2f117ac6077bc1e314894509962f9ec10ea0a269'),
)
PHYSICAL = {
    '8005b98c': (21, 43, 353196, 9258, 300, 730160),
    '804373e4': (263, 264, 2500, 2500, 4, 4344266),
    '80437418': (263, 264, 2552, 2552, 8, 4344318),
    '8043740c': (263, 264, 2540, 2540, 4, 4344306),
    '80437410': (263, 264, 2544, 2544, 4, 4344310),
    '80437404': (263, 264, 2532, 2532, 4, 4344298),
}


class SyntheticTests(unittest.TestCase):
    def test_document_witness_matches_all_operands(self):
        root = Path(__file__).resolve().parents[3]
        document = (root / 'research/decomp/sound-event-helper-evidence-2026-11-14.md').read_text()
        rows = re.findall(r'^(8005[0-9a-f]{4}) (\w+\s+[^\n]+)$', document, re.M)
        self.assertEqual([int(pc, 16) for pc, _ in rows], list(range(0x8005b98c, 0x8005bab8, 4)))
        self.assertEqual(ops('\n'.join(row for _, row in rows)), EXPECTED)

    def test_all_75_instructions_inverse_encode_exact_hash(self):
        self.assertEqual(a.RANGES, ((0x8005b98c, 300,
            'e2da8d687aa2b5cadc9c8159e24ec46a1bd81ad0b331d575715a359780f0ddb7'),))
        pc, width, digest = a.RANGES[0]
        self.assertEqual(len(EXPECTED), 75)
        raw = struct.pack('>75I', *(encode(row, pc + 4 * i) for i, row in enumerate(EXPECTED)))
        self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
        db = FakeDB(raw)
        result = a.range_evidence(db, a.TEXT_MAPPING, pc, width)
        self.assertEqual(result['instructions'], [dict(address=f'{pc+4*i:08x}', **row)
                                                  for i, row in enumerate(EXPECTED)])
        self.assertEqual(db.calls, [(21, 353196, 300, 2796416)])
        for row in EXPECTED:
            self.assertEqual(set(row), {'mnemonic', *FIELDS[row['mnemonic']].split()})

    def test_fixed_selection_guards_before_reads(self):
        for pc, width in ((0x8005b990, 296), (0x8005b98c, 296), (0x8005b98c, 304),
                          (0x8005bab8, 4), (0x8005b880, 268), (0x802d3ca0, 8), (0x800ff418, 4)):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, pc, width)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.range_evidence(None, a.TEXT_MAPPING, 0x8005b98c, 300)
        for pc in (0x804373e0, 0x804373e8, 0x80437414, 0x8043741c, 0x802d3ca0):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, pc)
        with patch.object(a, 'CONSTANTS', a.CONSTANTS * 2):
            with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                a.constant_evidence(None, a.DATA5_MAPPING, 0x804373e4)
        for bad in (True, 1.0, '4', None):
            for args in ((bad, 300), (0x8005b98c, bad)):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    a.range_evidence(None, a.TEXT_MAPPING, *args)
            with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                a.constant_evidence(None, a.DATA5_MAPPING, bad)

    def test_fixed_mapping_guards_before_reads(self):
        for fn, m, args in ((a.range_evidence, a.TEXT_MAPPING, (0x8005b98c, 300)),
                           (a.constant_evidence, a.DATA5_MAPPING, (0x804373e4,))):
            for bad in (list(m), m[:-1] + (22,), (m[0] + 4,) + m[1:], m[:2] + (float(m[2]),) + m[3:]):
                with self.assertRaisesRegex(a.c.FormatError, 'mapping'):
                    fn(None, bad, *args)

    def test_width_hash_and_complete_decode_guards(self):
        for raw, reason in ((bytes(300), 'digest'), (bytes(296), 'byte width'), (bytes(304), 'byte width')):
            with patch.object(a, 'decode_selected') as decoder:
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x8005b98c, 300)
                decoder.assert_not_called()
        for words, reason in (([0], 'unselected instruction'), ([0x38600000], 'terminal return'),
                              ([0x48001000, 0x4e800020], 'outside fixed span')):
            raw = struct.pack('>' + 'I' * len(words), *words)
            with patch.object(a, 'RANGES', ((0x8005b98c, len(raw), hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x8005b98c, len(raw))

    def test_unordered_compare_reserved_fields_and_bounds(self):
        row = dict(mnemonic='fcmpu', BF=0, fA=4, fB=0)
        self.assertEqual(encode(row, 0), 0xfc040000)
        self.assertEqual(a.decode_selected(0xfc040000, 0), row)
        for mask in (1, 1 << 21, 1 << 22, 1 << 23, 1 << 24, 1 << 25):
            with self.assertRaisesRegex(a.c.FormatError, 'unordered floating-comparison'):
                a.decode_selected(0xfc040000 | mask, 0)
        for bad in (True, -1, 1 << 32, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for bad in (True, -4, 1 << 32, 2, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, bad)

    def test_exact_constants_and_width_guards(self):
        self.assertEqual([(pc, bits) for pc, bits, _ in a.CONSTANTS], [(pc, bits) for pc, bits, _, _ in SCALARS])
        for pc, bits, value, digest in SCALARS:
            raw = bytes.fromhex(bits)
            db = FakeDB(raw)
            result = a.constant_evidence(db, a.DATA5_MAPPING, pc)
            self.assertEqual((result['bits'], result['value'], result['sha256']), (bits, value, digest))
            self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
            self.assertEqual(db.calls, [(263, pc - 0x80436a20, len(raw), 27360)])
            for bad, reason in ((raw[:-1], 'byte width'), (raw + b'\0', 'byte width'),
                                (bytes([raw[0] ^ 1]) + raw[1:], 'bits mismatch')):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.constant_evidence(FakeDB(bad), a.DATA5_MAPPING, pc)

    def test_whole_file_authentication_before_parser_or_reads(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as read:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'):
                    a.inspect(bytes(32), digest)
                parser.assert_not_called()
                read.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty',
                       'data5 digest mismatch', 'executable metadata SHA/type mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), \
                    patch.object(a, 'source_extent_evidence') as extent, patch.object(a, 'range_evidence') as read:
                with self.assertRaisesRegex(a.c.FormatError, reason): a.inspect(b'synthetic', 'synthetic')
                extent.assert_not_called()
                read.assert_not_called()

    def test_actual_schema_language_metadata_and_filebytes_rejections(self):
        data = b'synthetic schema fixture'; digest = hashlib.sha256(data).hexdigest()
        tables = {
            'Program': dict(version=0, keytype=4, types=[4], fields='Key;Value;'),
            'Property Table': dict(version=0, keytype=4, types=[4, 0], fields='Property Name;Value;Type;'),
            'File Bytes': dict(version=0, keytype=3, types=[4, 3, 3, 5, 5],
                fields='Key;Filename;Offset;Size;Chain Buffer IDs;Layered Chain Buffer IDs;',
                root=-1, count=0, maxkey=-(1 << 63)),
        }
        program = {'Program Name': ['boot.dol'], 'Language ID': ['PowerPC:BE:32:Gekko_Broadway'],
                   'Image Offset': ['80000000']}
        props = {'Program Information.Executable SHA256': [a.c.EXECUTABLE_SHA, 2],
                 'Program Information.Created With Ghidra Version': ['12.1.2', 2]}
        for case in ('schema', 'language', 'sha', 'sha-type', 'version', 'file-root', 'file-count', 'file-key'):
            tt, pp, pr = copy.deepcopy((tables, program, props))
            if case == 'schema': tt['Program']['types'] = [2]
            if case == 'language': pp['Language ID'] = ['PowerPC:LE:32:default']
            if case == 'sha': pr['Program Information.Executable SHA256'][0] = '0' * 64
            if case == 'sha-type': pr['Program Information.Executable SHA256'][1] = 0
            if case == 'version': pr['Program Information.Created With Ghidra Version'][0] = '12.1.1'
            if case == 'file-root': tt['File Bytes']['root'] = 0
            if case == 'file-count': tt['File Bytes']['count'] = 1
            if case == 'file-key': tt['File Bytes']['maxkey'] = 0
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as read:
                parser.return_value.tables.return_value = tt
                parser.return_value.rows.side_effect = lambda t: pp if t == tt['Program'] else pr
                with self.assertRaises(a.c.FormatError): a.inspect(data, digest)
                read.assert_not_called()

    def test_actual_mapping_failure_before_reads(self):
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0] for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('text-root', 'text-offset', 'text-type', 'text-length', 'data3-root',
                       'data5-root', 'data5-offset', 'text-duplicate', 'data5-duplicate', 'image', 'overlap'):
            aa, bb, ss = copy.deepcopy(({'image_offset': '80000000'}, blocks, subs))
            if target == 'text-root': ss[1][4] += 1
            if target == 'text-offset': ss[1][5] += 1
            if target == 'text-type': ss[1][1] += 1
            if target == 'text-length': bb[1][5] -= 4
            if target == 'data3-root': ss[5][4] += 1
            if target == 'data5-root': ss[7][4] += 1
            if target == 'data5-offset': ss[7][3] += 1
            if target == 'text-duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'data5-duplicate': ss[99] = copy.deepcopy(ss[7])
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x200000000005b98c, 4, 0]
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'constant_evidence') as constants:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called()
                constants.assert_not_called()

    def test_source_extent_and_digest_guard(self):
        result = a.source_extent_evidence()
        self.assertEqual((result['map_row'], result['map_size'], result['entry_marker_line'],
                          result['next_marker_line'], result['entry'], result['end_exclusive']),
                         (718, 300, 3628, 3672, '8005b98c', '8005bab8'))
        with patch.object(a.Path, 'read_bytes', return_value=b'untrusted'):
            with self.assertRaisesRegex(a.c.FormatError, 'source extent file digest'):
                a.source_extent_evidence()
        with patch.object(a.c, 'inspect', return_value={}), \
                patch.object(a, 'source_extent_evidence', side_effect=a.c.FormatError('source mismatch')), \
                patch.object(a, 'range_evidence') as ranges, patch.object(a, 'constant_evidence') as constants:
            with self.assertRaisesRegex(a.c.FormatError, 'source mismatch'): a.inspect(b'x', 'x')
            ranges.assert_not_called(); constants.assert_not_called()

    def test_gate_eager_load_order_unsigned_frame_and_repeated_conversions(self):
        q = at()
        self.assertEqual([q[p]['displacement'] for p in (0x8005b994, 0x8005b9a0, 0x8005b9a4)],
                         [-30216, -30268, 0])
        self.assertEqual(q[0x8005b9a4], dict(mnemonic='lhz', rD=5, rA=4, displacement=0))
        self.assertNotIn('xoris', [r['mnemonic'] for r in EXPECTED])
        self.assertEqual(q[0x8005b9b8], dict(mnemonic='fcmpu', BF=0, fA=4, fB=0))
        self.assertEqual(q[0x8005b9c0], dict(mnemonic='fcmpo', BF=0, fA=1, fB=4))
        self.assertEqual((q[0x8005b9c4]['BO'], q[0x8005b9c4]['BI'], q[0x8005b9c4]['target']),
                         (12, 1, '8005baa8'))
        self.assertEqual([q[p]['displacement'] for p in (0x8005b9d0, 0x8005b9d8)], [-30216, -30268])
        self.assertEqual([q[p] for p in (0x8005b9b4, 0x8005b9e0, 0x8005b9f8, 0x8005ba10)],
                         [dict(mnemonic='fsubs', fD=d, fA=d, fB=b, Rc=0)
                          for d, b in ((0, 3), (3, 4), (0, 4), (0, 4))])
        self.assertEqual(q[0x8005ba18], dict(mnemonic='cror', BT=2, BA=1, BB=2))
        self.assertEqual((q[0x8005ba1c]['BO'], q[0x8005ba1c]['BI'], q[0x8005ba1c]['target']),
                         (4, 2, '8005ba24'))

    def test_kind_signed_comparisons_on_unsigned_byte_and_complete_dead_branch(self):
        q = at()
        self.assertEqual(q[0x8005ba24], dict(mnemonic='lbz', rD=0, rA=4, displacement=3))
        self.assertEqual([q[p] for p in (0x8005ba28, 0x8005ba34, 0x8005ba40)],
                         [dict(mnemonic='cmpi', BF=0, L=0, rA=0, immediate=i) for i in (1, 0, 4)])
        self.assertEqual(q[0x8005ba3c], dict(mnemonic='b', target='8005baa8', AA=0, LK=0))
        self.assertNotIn('extsb', [r['mnemonic'] for r in EXPECTED])
        self.assertEqual([(pc, row['target']) for pc, row in q.items() if row['mnemonic'] == 'bl'],
                         [(0x8005ba54, '800f036c'), (0x8005ba94, '800f036c'), (0x8005baa4, '800f061c')])

    def test_scale_once_lower_then_lazy_upper_and_full_u32_id_arithmetic(self):
        q = at()
        self.assertEqual([(pc, row) for pc, row in q.items() if row.get('rA') == 3],
                         [(0x8005ba5c, dict(mnemonic='lfs', fD=1, rA=3, displacement=0xb4))])
        self.assertEqual([q[p]['displacement'] for p in (0x8005ba60, 0x8005ba78)], [-30228, -30224])
        self.assertEqual((q[0x8005ba68]['BO'], q[0x8005ba68]['BI'], q[0x8005ba68]['target']),
                         (4, 0, '8005ba78'))
        self.assertEqual((q[0x8005ba80]['BO'], q[0x8005ba80]['BI'], q[0x8005ba80]['target']),
                         (4, 1, '8005ba90'))
        for pc in (0x8005ba50, 0x8005ba6c, 0x8005ba84, 0x8005ba90, 0x8005ba9c):
            self.assertEqual(q[pc], dict(mnemonic='lhz', rD=4, rA=4, displacement=4))
        self.assertEqual(q[0x8005ba70], dict(mnemonic='addi', rD=4, rA=4, immediate=-1))
        self.assertEqual(q[0x8005ba88], dict(mnemonic='addi', rD=4, rA=4, immediate=1))
        self.assertNotIn('rlwinm', [r['mnemonic'] for r in EXPECTED])
        self.assertEqual(q[0x8005baa0], dict(mnemonic='lfs', fD=1, rA=2, displacement=-30236))
        self.assertEqual([q[p]['mnemonic'] for p in range(0x8005ba9c, 0x8005baa8, 4)], ['lhz', 'lfs', 'bl'])

    def test_literal_only_cli_no_table_or_phase_one_or_shared_allowlist_edits(self):
        for pc, width, _ in a.RANGES:
            self.assertNotIn((pc, width), a.c.TARGETS)
            self.assertNotIn((pc, width), [r[:2] for r in a.double.RANGES])
        for pc, _, _ in a.CONSTANTS:
            self.assertNotIn(pc, [r[0] for r in a.double.CONSTANTS])
        for args in (['--address', '802d3ca0'], ['--width', '300'], ['--target', '800ff418'],
                     ['--raw'], ['--execute'], ['--follow']):
            with patch.object(a.sys, 'argv', ['reader', 'fixture.gbf'] + args), \
                    contextlib.redirect_stderr(io.StringIO()), patch.object(a, 'inspect') as inspect:
                with self.assertRaises(SystemExit) as ex: a.main()
                self.assertEqual(ex.exception.code, 2)
                inspect.assert_not_called()


class LocalArchiveTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        default = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'
        base = Path(os.environ.get('GOTYAFORCE_ARCHIVED_PROGRAMDB_DIR', str(default)))
        paths = [base / f'db.{n}.gbf' for n in (3, 4)]
        if not all(p.is_file() for p in paths):
            raise unittest.SkipTest('local archives unavailable; never fetched')
        cls.results = []
        for p in paths:
            a.c.require(32 <= p.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with p.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))

    def test_all_operands_full_extent_and_constants_both_snapshots(self):
        for result in self.results:
            span = result['ranges'][0]
            self.assertEqual(span['instructions'], [dict(address=f'{0x8005b98c+i*4:08x}', **row)
                                                    for i, row in enumerate(EXPECTED)])
            self.assertEqual((span['width'], span['sha256'], span['end_exclusive']),
                             (300, a.RANGES[0][2], '8005bab8'))
            coverage = result['function_coverage'][0]
            self.assertEqual((coverage['represented_instructions'], coverage['unrepresented_instructions'],
                              coverage['unrepresented_ranges'], coverage['map_size']), (75, 0, [], 300))
            self.assertEqual([(int(r['address'], 16), r['bits'], r['value'], r['sha256'])
                              for r in result['constants']], list(SCALARS))

    def test_identical_results_and_exact_physical_spans(self):
        self.assertEqual([r['snapshot'] for r in self.results], ['db.3.gbf', 'db.4.gbf'])
        for key in ('ranges', 'constants', 'mappings', 'function_coverage', 'recorded_bases',
                    'float_preconditions', 'source_extent', 'conditional_calls'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        for result in self.results:
            for item in result['ranges'] + result['constants']:
                root, buf, chain, offset, width, physical = PHYSICAL[item['address']]
                self.assertEqual(item['spans'], [dict(root_buffer=root, data_buffer=buf,
                    chain_offset=chain, data_offset=offset, length=width, obfuscated=True,
                    physical_offset=physical)])
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(result['data5_sha256'], a.c.DATA5_SHA)
            self.assertEqual(result['executable_sha256_property_type'], 2)

    def test_only_324_selected_bytes_no_payload_or_phase_one(self):
        for result in self.results:
            selected = result['ranges'] + result['constants']
            self.assertEqual(sum(r['width'] for r in selected), 324)
            self.assertEqual([r['address'] for r in selected],
                             ['8005b98c', '804373e4', '80437418', '8043740c', '80437410', '80437404'])
            self.assertNotIn('raw', json.dumps(result))
            self.assertEqual(len(result['conditional_calls']), 3)


if __name__ == '__main__':
    unittest.main()
