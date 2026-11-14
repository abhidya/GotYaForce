#!/usr/bin/env python3
"""Frozen full-operand/inverse witnesses and fail-closed fixed-reader tests.

Synthetic cases need no archive. Local cases use only two existing snapshots;
missing inputs skip and are never fetched. No archived instruction execution.
"""
import contextlib
import copy
import hashlib
import importlib
import io
import json
import os
from pathlib import Path
import re
import struct
import unittest
from unittest.mock import patch

import read_archived_frame_suffix_evidence as a
import test_archived_double_action_evidence as previous
import test_archived_actor_mode1_evidence as frame

FakeDB = previous.FakeDB
FIELDS = dict(previous.FIELDS, bclr='BO BI BH LK')


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


# Fixed schedules, never generated during tests; every operand is explicit.
EXPECTED = {
    0x8006f88c: ops('''
lwz 0 3 1504
rlwinm 0 0 0 6 6 1
bc 12 2 0 8006f8a0 0
addi 0 0 0
stb 0 3 1992
lha 0 3 1000
cmpi 0 0 0 10
bclr 4 2 0 0
lbz 0 3 1769
extsb 0 0 1
bclr 4 1 0 0
lbz 4 3 1772
addi 0 4 1
stb 0 3 1772
lbz 0 3 1772
rlwinm 0 0 0 30 31 0
stb 0 3 1772
blr 20 0 0 0
'''),
    0x80055ee4: ops('''
lwz 0 3 1504
rlwinm 0 0 26 31 31 0
stb 0 3 135
lbz 0 3 2252
extsb 0 0 0
cmpi 0 0 0 1
bc 12 2 0 80055f40 0
bc 4 0 0 80055f4c 0
cmpi 0 0 0 0
bc 4 0 0 80055f10 0
b 80055f4c 0 0
lfs 2 3 2044
lfs 1 3 180
lfs 0 2 -30600
fmuls 1 2 1 0
fcmpo 0 1 0
bc 4 0 0 80055f34 0
addi 0 0 1
stb 0 3 491
b 80055f54 0 0
addi 0 0 0
stb 0 3 491
b 80055f54 0 0
addi 0 0 0
stb 0 3 491
b 80055f54 0 0
addi 0 0 1
stb 0 3 491
lwz 0 3 1504
rlwinm 0 0 0 2 2 1
bc 12 2 0 80055f6c 0
addi 0 0 1
stb 0 3 630
b 80055f74 0 0
addi 0 0 0
stb 0 3 630
lbz 0 3 1993
extsb 0 0 1
bclr 12 2 0 0
lha 0 3 626
ori 0 0 65535
sth 0 3 626
blr 20 0 0 0
'''),
    0x8005b880: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stw 31 1 28
stw 30 1 24
stw 29 1 20
stw 28 1 16
or 3 28 3 0
lwz 0 3 1256
cmpli 0 0 0 0
bc 12 2 0 8005b96c 0
addi 29 0 0
addi 30 28 6868
lbz 0 30 55
extsb 0 0 0
cmpi 0 0 0 -1
bc 12 2 0 8005b95c 0
lwz 3 28 1256
rlwinm 0 0 3 0 28 0
add 31 3 0 0 0
lbz 0 31 2
cmpli 0 0 0 0
bc 4 2 0 8005b8f4 0
lfs 1 30 8
or 28 3 28 0
lfs 2 30 16
or 31 4 31 0
bl 8005b98c 0 1
b 8005b948 0 0
lfs 1 30 12
lfs 2 30 20
fcmpo 0 1 2
cror 2 1 2
bc 4 2 0 8005b918 0
or 28 3 28 0
or 31 4 31 0
bl 8005b98c 0 1
b 8005b948 0 0
lha 3 30 36
addis 0 0 17200
stw 0 1 8
or 31 4 31 0
xoris 3 0 32768
lfd 3 2 -30288
stw 0 1 12
or 28 3 28 0
lfd 0 1 8
fsubs 0 0 3 0
fadds 1 1 0 0
bl 8005b98c 0 1
lbz 0 31 6
addi 31 31 8
extsb 0 0 0
cmpi 0 0 0 -1
bc 4 2 0 8005b8d0 0
addi 29 29 1
addi 30 30 64
cmpi 0 0 29 4
bc 12 0 0 8005b8b4 0
lwz 0 1 36
lwz 31 1 28
lwz 30 1 24
lwz 29 1 20
lwz 28 1 16
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
}


def encode(row, pc):
    """Independent inverse encoding, never calls the reader/decoder."""
    if row['mnemonic'] == 'bclr':
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    return previous.encode(row, pc)


PHYSICAL = {'8006f88c': [{'root_buffer': 21,
               'data_buffer': 48,
               'chain_offset': 434860,
               'data_offset': 9032,
               'length': 72,
               'obfuscated': True,
               'physical_offset': 811854}],
 '80055ee4': [{'root_buffer': 21,
               'data_buffer': 42,
               'chain_offset': 329988,
               'data_offset': 2428,
               'length': 172,
               'obfuscated': True,
               'physical_offset': 706946}],
 '8005b880': [{'root_buffer': 21,
               'data_buffer': 43,
               'chain_offset': 352928,
               'data_offset': 8990,
               'length': 268,
               'obfuscated': True,
               'physical_offset': 729892}],
 '802d3b20': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 101568,
               'data_offset': 3300,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3394794}],
 '802d3b48': [{'root_buffer': 199,
               'data_buffer': 206,
               'chain_offset': 101608,
               'data_offset': 3340,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 3394834}],
 '80437298': [{'root_buffer': 263,
               'data_buffer': 264,
               'chain_offset': 2168,
               'data_offset': 2168,
               'length': 4,
               'obfuscated': True,
               'physical_offset': 4343934}]}


def at(entry):
    return {entry + i * 4: row for i, row in enumerate(EXPECTED[entry])}


class SyntheticTests(unittest.TestCase):
    def test_all_operands_inverse_encode_exact_hashes(self):
        self.assertEqual([(p, w) for p, w, _ in a.RANGES],
                         [(0x8006f88c, 72), (0x80055ee4, 172), (0x8005b880, 268)])
        for pc, width, digest in a.RANGES:
            rows = EXPECTED[pc]
            self.assertEqual(len(rows), width // 4)
            raw = struct.pack('>' + 'I' * len(rows), *(encode(row, pc + i * 4) for i, row in enumerate(rows)))
            self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
            db = FakeDB(raw)
            actual = a.range_evidence(db, a.TEXT_MAPPING, pc, width)
            self.assertEqual(actual['instructions'],
                             [dict(address=f'{pc+i*4:08x}', **row) for i, row in enumerate(rows)])
            self.assertEqual(db.calls, [(21, pc - 0x800055e0, width, 2796416)])
            for row in rows:
                self.assertEqual(set(row), {'mnemonic', *FIELDS[row['mnemonic']].split()})

    def test_selection_duplicate_type_guards_before_reads(self):
        for pc, width, _ in a.RANGES:
            for args in ((pc + 4, width - 4), (pc, width + 4), (pc, width - 4), (pc - 4, 4), (pc + width, 4)):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, *args)
            with patch.object(a, 'RANGES', a.RANGES * 2):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    a.range_evidence(None, a.TEXT_MAPPING, pc, width)
        for fn, mapping, allowed, collection in (
                (a.cell_evidence, a.DATA3_MAPPING, 0x802d3b20, 'CELLS'),
                (a.constant_evidence, a.DATA5_MAPPING, 0x80437298, 'CONSTANTS')):
            for pc in (allowed - 4, allowed + 4, 0x802d3ca0, 0x8005b98c):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    fn(None, mapping, pc)
            with patch.object(a, collection, getattr(a, collection) * 2):
                with self.assertRaisesRegex(a.c.FormatError, 'not allowlisted'):
                    fn(None, mapping, allowed)
        for bad in (True, 1.0, '4', None):
            for args in ((bad, 72), (0x8006f88c, bad)):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    a.range_evidence(None, a.TEXT_MAPPING, *args)
            for fn, mapping in ((a.cell_evidence, a.DATA3_MAPPING), (a.constant_evidence, a.DATA5_MAPPING)):
                with self.assertRaisesRegex(a.c.FormatError, 'integer fields'):
                    fn(None, mapping, bad)

    def test_fixed_mapping_guards_before_reads(self):
        for fn, m, args in ((a.range_evidence, a.TEXT_MAPPING, (0x8006f88c, 72)),
                           (a.cell_evidence, a.DATA3_MAPPING, (0x802d3b20,)),
                           (a.constant_evidence, a.DATA5_MAPPING, (0x80437298,))):
            for bad in (list(m), m[:-1] + (22,), (m[0] + 4,) + m[1:], m[:2] + (float(m[2]),) + m[3:]):
                with self.assertRaisesRegex(a.c.FormatError, 'mapping'):
                    fn(None, bad, *args)

    def test_width_hash_and_complete_decode_guards(self):
        for pc, width, _ in a.RANGES:
            for raw, reason in ((bytes(width), 'digest'), (bytes(width - 4), 'byte width'), (bytes(width + 4), 'byte width')):
                with patch.object(a, 'decode_selected') as decoder:
                    with self.assertRaisesRegex(a.c.FormatError, reason):
                        a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, pc, width)
                    decoder.assert_not_called()
        for words, reason in (([0], 'unselected instruction'), ([0x38600000], 'terminal return'),
                              ([0x48001000, 0x4e800020], 'outside fixed span')):
            raw = struct.pack('>' + 'I' * len(words), *words)
            with patch.object(a, 'RANGES', ((0x8006f88c, len(raw), hashlib.sha256(raw).hexdigest()),)):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, 0x8006f88c, len(raw))

    def test_exact_pointer_cells_and_no_following(self):
        self.assertEqual([(pc, target) for _, pc, target, _ in a.CELLS],
                         [(0x802d3b20, 0x8006f88c), (0x802d3b48, 0x802d3ca0)])
        for label, pc, target, digest in a.CELLS:
            raw = struct.pack('>I', target)
            db = FakeDB(raw)
            result = a.cell_evidence(db, a.DATA3_MAPPING, pc)
            self.assertEqual((result['target'], result['label'], result['sha256']),
                             (f'{target:08x}', label, digest))
            self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
            self.assertEqual(db.calls, [(199, pc - 0x802bae60, 4, 1000128)])
            for bad, reason in ((raw[:-1], 'byte width'), (raw + bytes(1), 'byte width'), (bytes(4), 'digest')):
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.cell_evidence(FakeDB(bad), a.DATA3_MAPPING, pc)
            # Independently checks the target as well as its digest.
            with patch.object(a, 'CELLS', ((label, pc, target + 4, digest),)):
                with self.assertRaisesRegex(a.c.FormatError, 'target mismatch'):
                    a.cell_evidence(FakeDB(raw), a.DATA3_MAPPING, pc)

    def test_exact_scalar_bits_width_and_value(self):
        self.assertEqual(a.CONSTANTS, ((0x80437298, '40000000', 'size-product-threshold'),))
        raw = bytes.fromhex('40000000')
        db = FakeDB(raw)
        result = a.constant_evidence(db, a.DATA5_MAPPING, 0x80437298)
        self.assertEqual((result['bits'], result['value']), ('40000000', 2.0))
        self.assertEqual(result['sha256'], hashlib.sha256(raw).hexdigest())
        self.assertEqual(db.calls, [(263, 2168, 4, 27360)])
        for bad, reason in ((raw[:-1], 'byte width'), (raw + bytes(1), 'byte width'), (bytes(4), 'bits mismatch')):
            with self.assertRaisesRegex(a.c.FormatError, reason):
                a.constant_evidence(FakeDB(bad), a.DATA5_MAPPING, 0x80437298)

    def test_authentication_before_parser_and_selections(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'range_evidence') as read:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'):
                    a.inspect(bytes(32), digest)
                parser.assert_not_called()
                read.assert_not_called()
        for reason in ('unsupported schema', 'language mismatch', 'File Bytes table is not empty',
                       'data5 digest mismatch', 'executable metadata SHA/type mismatch'):
            with patch.object(a.c, 'inspect', side_effect=a.c.FormatError(reason)), patch.object(a.c, 'GBF') as parser:
                with self.assertRaisesRegex(a.c.FormatError, reason):
                    a.inspect(b'synthetic', 'synthetic')
                parser.assert_not_called()

    def test_actual_schema_failure_before_reads(self):
        data = b'synthetic schema fixture'
        digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for key, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema)
            changed[key] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as read:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'):
                    a.inspect(data, digest)
                parser.return_value.rows.assert_not_called()
                read.assert_not_called()

    def test_actual_mapping_failure_before_reads(self):
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0] for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('text-root', 'text-offset', 'text-type', 'text-length', 'data3-root', 'data3-offset',
                       'data5-root', 'data5-offset', 'text-duplicate', 'data3-duplicate-sub', 'data5-duplicate-sub',
                       'image', 'overlap'):
            aa, bb, ss = copy.deepcopy(({'image_offset': '80000000'}, blocks, subs))
            if target == 'text-root': ss[1][4] += 1
            if target == 'text-offset': ss[1][5] += 1
            if target == 'text-type': ss[1][1] += 1
            if target == 'text-length': bb[1][5] -= 4
            if target == 'data3-root': ss[5][4] += 1
            if target == 'data3-offset': ss[5][3] += 1
            if target == 'data5-root': ss[7][4] += 1
            if target == 'data5-offset': ss[7][3] += 1
            if target == 'text-duplicate': bb[99] = copy.deepcopy(bb[1])
            if target == 'data3-duplicate-sub': ss[99] = copy.deepcopy(ss[5])
            if target == 'data5-duplicate-sub': ss[99] = copy.deepcopy(ss[7])
            if target == 'image': aa['image_offset'] = '80000004'
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x200000000006f88c, 4, 0]
            with patch.object(a.c, 'inspect', return_value=aa), patch.object(a.c, 'GBF') as parser, \
                    patch.object(a, 'range_evidence') as ranges, patch.object(a, 'cell_evidence') as cells, \
                    patch.object(a, 'constant_evidence') as constants:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                ranges.assert_not_called()
                cells.assert_not_called()
                constants.assert_not_called()

    def test_conditional_return_all_fields_and_reserved_forms(self):
        for bo, bi in ((4, 2), (4, 1), (12, 2)):
            row = dict(mnemonic='bclr', BO=bo, BI=bi, BH=0, LK=0)
            word = encode(row, 0)
            self.assertEqual(a.decode_selected(word, 0), row)
            for mask in (1, 1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15):
                with self.assertRaisesRegex(a.c.FormatError, 'conditional LR-return'):
                    a.decode_selected(word | mask, 0)
        for bo, bi in ((4, 0), (12, 0), (12, 1), (16, 0), (4, 3)):
            with self.assertRaisesRegex(a.c.FormatError, 'conditional LR-return'):
                a.decode_selected(encode(dict(mnemonic='bclr', BO=bo, BI=bi, BH=0, LK=0), 0), 0)
        for bad in (True, -1, 1 << 32, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(bad, 0)
        for bad in (True, -4, 1 << 32, 2, 1.0):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0, bad)

    def test_source_extent_markers_and_map_rows(self):
        root = Path(__file__).resolve().parents[3]
        text = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        maps = {int(pc, 16): int(width, 16) for pc, width in re.findall(r'^([0-9a-f]{8}) ([0-9a-f]{8}) ', text, re.M)}
        for pc, width, chunk in ((0x80055ee4, 172, '0006'), (0x8005b880, 268, '0007')):
            src = (root / f'research/decomp/ghidra-export/chunk_{chunk}.c').read_text()
            markers = [int(v, 16) for v in re.findall(r'^// ==== ([0-9a-f]{8}) ', src, re.M)]
            self.assertEqual(markers[markers.index(pc) + 1], pc + width)
            self.assertEqual(maps[pc], width)
        src = (root / 'research/decomp/ghidra-export/chunk_0009.c').read_text()
        markers = [int(v, 16) for v in re.findall(r'^// ==== ([0-9a-f]{8}) ', src, re.M)]
        self.assertNotIn(0x8006f88c, markers)
        self.assertNotIn(0x8006f88c, maps)
        self.assertEqual(markers[markers.index(0x8006f7c0) + 1], 0x8006f8d4)
        self.assertEqual(a.REUSED_RANGES[0][1] + a.REUSED_RANGES[0][2], 0x8006f88c)
        self.assertEqual(EXPECTED[0x8006f88c][-1], dict(mnemonic='blr', BO=20, BI=0, BH=0, LK=0))

    def test_reused_exact_witnesses_not_new_selections(self):
        for reader, pc, width, sha in a.REUSED_RANGES:
            old = importlib.import_module(f'read_archived_{reader}_evidence')
            self.assertIn((pc, width, sha), old.RANGES)
            self.assertNotIn((pc, width), [r[:2] for r in a.RANGES])
        for reader, pc, width, bits in a.REUSED_CONSTANTS:
            old = importlib.import_module(f'read_archived_{reader}_evidence')
            self.assertIn((pc, width, bits), old.CONSTANTS)
            self.assertNotIn(pc, [r[0] for r in a.CONSTANTS])

    def test_posthook_control_signed_gates_and_two_stores(self):
        q = at(0x8006f88c)
        self.assertEqual(q[0x8006f88c], dict(mnemonic='lwz', rD=0, rA=3, displacement=0x5e0))
        self.assertEqual(q[0x8006f890], dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=6, ME=6, Rc=1))
        self.assertEqual(q[0x8006f894]['target'], '8006f8a0')
        self.assertEqual(q[0x8006f89c]['displacement'], 0x7c8)
        self.assertEqual(q[0x8006f8a0], dict(mnemonic='lha', rD=0, rA=3, displacement=0x3e8))
        self.assertEqual(q[0x8006f8a4]['immediate'], 10)
        self.assertEqual(q[0x8006f8a8], dict(mnemonic='bclr', BO=4, BI=2, BH=0, LK=0))
        self.assertEqual(q[0x8006f8ac]['displacement'], 0x6e9)
        self.assertEqual(q[0x8006f8b0], dict(mnemonic='extsb', rS=0, rA=0, Rc=1))
        self.assertEqual(q[0x8006f8b4], dict(mnemonic='bclr', BO=4, BI=1, BH=0, LK=0))
        self.assertEqual([q[p]['mnemonic'] for p in range(0x8006f8b8, 0x8006f8d0, 4)],
                         ['lbz', 'addi', 'stb', 'lbz', 'rlwinm', 'stb'])
        self.assertEqual([q[p]['displacement'] for p in (0x8006f8b8, 0x8006f8c0, 0x8006f8c4, 0x8006f8cc)], [0x6ec] * 4)
        self.assertEqual(q[0x8006f8c8], dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=30, ME=31, Rc=0))

    def test_flags_signed_policy_fresh_reads_and_ordered_stores(self):
        q = at(0x80055ee4)
        self.assertEqual(q[0x80055ee8], dict(mnemonic='rlwinm', rS=0, rA=0, SH=26, MB=31, ME=31, Rc=0))
        self.assertEqual(q[0x80055eec]['displacement'], 0x87)
        self.assertEqual(q[0x80055ef0]['displacement'], 0x8cc)
        self.assertEqual(q[0x80055ef4], dict(mnemonic='extsb', rS=0, rA=0, Rc=0))
        self.assertEqual([q[p]['displacement'] for p in (0x80055f10, 0x80055f14, 0x80055f18)],
                         [0x7fc, 0xb4, 0x80437298 - 0x8043ea20])
        self.assertEqual(q[0x80055f1c], dict(mnemonic='fmuls', fD=1, fA=2, fC=1, Rc=0))
        self.assertEqual(q[0x80055f20], dict(mnemonic='fcmpo', BF=0, fA=1, fB=0))
        self.assertEqual((q[0x80055f24]['BO'], q[0x80055f24]['BI']), (4, 0))
        self.assertEqual([q[p]['displacement'] for p in (0x80055f2c, 0x80055f38, 0x80055f44, 0x80055f50)], [0x1eb] * 4)
        self.assertEqual(q[0x80055f54], dict(mnemonic='lwz', rD=0, rA=3, displacement=0x5e0))
        self.assertEqual(q[0x80055f58], dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=2, ME=2, Rc=1))
        self.assertEqual([q[p]['displacement'] for p in (0x80055f64, 0x80055f70)], [0x276] * 2)
        self.assertEqual(q[0x80055f74]['displacement'], 0x7c9)
        self.assertEqual(q[0x80055f7c], dict(mnemonic='bclr', BO=12, BI=2, BH=0, LK=0))
        self.assertEqual(q[0x80055f80], dict(mnemonic='lha', rD=0, rA=3, displacement=0x272))
        self.assertEqual(q[0x80055f84], dict(mnemonic='ori', rS=0, rA=0, immediate=65535))
        self.assertEqual(q[0x80055f88], dict(mnemonic='sth', rS=0, rA=3, displacement=0x272))

    def test_sound_null_signed_indices_fresh_pointer_and_four_row_order(self):
        q = at(0x8005b880)
        self.assertEqual(q[0x8005b8a0], dict(mnemonic='lwz', rD=0, rA=3, displacement=0x4e8))
        self.assertEqual(q[0x8005b8a8]['target'], '8005b96c')
        self.assertEqual(q[0x8005b8b0]['immediate'], 0x1ad4)
        self.assertEqual(q[0x8005b8b4]['displacement'], 0x37)
        self.assertEqual(q[0x8005b8b8], dict(mnemonic='extsb', rS=0, rA=0, Rc=0))
        self.assertEqual(q[0x8005b8bc]['immediate'], -1)
        self.assertEqual(q[0x8005b8c0]['target'], '8005b95c')
        self.assertEqual(q[0x8005b8c4], dict(mnemonic='lwz', rD=3, rA=28, displacement=0x4e8))
        self.assertEqual(q[0x8005b8c8], dict(mnemonic='rlwinm', rS=0, rA=0, SH=3, MB=0, ME=28, Rc=0))
        self.assertEqual(q[0x8005b8cc], dict(mnemonic='add', rD=31, rA=3, rB=0, OE=0, Rc=0))
        self.assertEqual([q[p]['immediate'] for p in (0x8005b95c, 0x8005b960, 0x8005b964)], [1, 0x40, 4])
        self.assertEqual(q[0x8005b968], dict(mnemonic='bc', BO=12, BI=0, LK=0, target='8005b8b4', AA=0))

    def test_sound_elapsed_frame_duration_and_record_sentinel_order(self):
        q = at(0x8005b880)
        self.assertEqual(q[0x8005b8d0]['displacement'], 2)
        self.assertEqual([q[p]['displacement'] for p in (0x8005b8dc, 0x8005b8e4)], [8, 0x10])
        self.assertEqual([q[p]['displacement'] for p in (0x8005b8f4, 0x8005b8f8)], [0xc, 0x14])
        self.assertEqual(q[0x8005b900], dict(mnemonic='cror', BT=2, BA=1, BB=2))
        self.assertEqual(q[0x8005b904], dict(mnemonic='bc', BO=4, BI=2, LK=0, target='8005b918', AA=0))
        self.assertEqual(q[0x8005b918], dict(mnemonic='lha', rD=3, rA=30, displacement=0x24))
        self.assertEqual(q[0x8005b928], dict(mnemonic='xoris', rS=3, rA=0, immediate=0x8000))
        self.assertEqual(q[0x8005b92c], dict(mnemonic='lfd', fD=3, rA=2, displacement=0x804373d0 - 0x8043ea20))
        self.assertEqual(q[0x8005b93c], dict(mnemonic='fsubs', fD=0, fA=0, fB=3, Rc=0))
        self.assertEqual(q[0x8005b940], dict(mnemonic='fadds', fD=1, fA=1, fB=0, Rc=0))
        self.assertEqual([q[p]['target'] for p in (0x8005b8ec, 0x8005b910, 0x8005b944)], ['8005b98c'] * 3)
        self.assertEqual(q[0x8005b948], dict(mnemonic='lbz', rD=0, rA=31, displacement=6))
        self.assertEqual(q[0x8005b94c], dict(mnemonic='addi', rD=31, rA=31, immediate=8))
        self.assertEqual(q[0x8005b950], dict(mnemonic='extsb', rS=0, rA=0, Rc=0))
        self.assertEqual(q[0x8005b954]['immediate'], -1)
        self.assertEqual(q[0x8005b958]['target'], '8005b8d0')

    def test_existing_frame_capture_markers_and_suffix_order_without_new_selection(self):
        q = {0x80055568 + i * 4: row for i, row in enumerate(frame.EXPECTED[0x80055568])}
        self.assertEqual([q[p]['immediate'] for p in (0x80055574, 0x800555d0, 0x800555f4, 0x8005561c)], [2, 1, 0, 2])
        self.assertEqual([q[p]['displacement'] for p in (0x8005559c, 0x800555a4, 0x800555a8)], [0x20, 0x24, 0x28])
        self.assertEqual(q[0x800555c0]['mnemonic'], 'bctrl')
        self.assertEqual([q[p]['displacement'] for p in (0x800555c4, 0x800555cc)], [0x5db, 0x5da])
        self.assertEqual(q[0x80055628]['displacement'], 0x4c0)
        self.assertEqual(q[0x80055638]['target'], '80055ee4')
        self.assertEqual(q[0x8005563c]['displacement'], 0x5e0)
        self.assertEqual(q[0x80055640], dict(mnemonic='rlwinm', rS=0, rA=0, SH=0, MB=25, ME=25, Rc=1))
        self.assertEqual(q[0x80055648]['displacement'], 0x598)
        self.assertEqual(q[0x8005564c], dict(mnemonic='extsb', rS=0, rA=0, Rc=1))
        self.assertEqual([q[p]['displacement'] for p in (0x8005565c, 0x80055664, 0x80055668)], [0x20, 0x24, 0x28])
        self.assertEqual(q[0x80055670]['target'], '8005b880')
        self.assertEqual(q[0x80055688]['mnemonic'], 'blr')

    def test_no_arbitrary_cli_or_shared_allowlist_widening(self):
        for pc, width, _ in a.RANGES:
            self.assertNotIn((pc, width), a.c.TARGETS)
            self.assertNotIn((pc, width), [x[:2] for x in a.double.RANGES])
        for _, pc, _, _ in a.CELLS:
            self.assertNotIn(pc, [x[1] for x in a.double.CELLS])
        for args in (['--address', '802d3ca0'], ['--width', '72'], ['--target', '8005b98c'],
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
        cls.constructors = []
        cls.biases = []
        rotation = importlib.import_module('read_archived_actor_rotation_evidence')
        for p in paths:
            a.c.require(32 <= p.stat().st_size <= a.c.MAX_FILE, 'snapshot size bounds')
            with p.open('rb') as stream: data = stream.read(a.c.MAX_FILE + 1)
            a.c.require(len(data) <= a.c.MAX_FILE, 'snapshot size bounds')
            cls.results.append(a.inspect(data, hashlib.sha256(data).hexdigest()))
            db = a.c.GBF(data)
            # Prior fixed selections through their unchanged independent readers.
            cls.constructors.append(a.normal.range_evidence(db, a.TEXT_MAPPING, 0x8006f60c, 252))
            cls.biases.append(rotation.constant_evidence(db, rotation.DATA5_MAPPING, 0x804373d0, 8))

    def test_all_operands_and_extent_both_snapshots(self):
        for result in self.results:
            for span, (pc, width, digest) in zip(result['ranges'], a.RANGES):
                self.assertEqual(span['instructions'],
                                 [dict(address=f'{pc+i*4:08x}', **row) for i, row in enumerate(EXPECTED[pc])])
                self.assertEqual((span['width'], span['sha256'], span['end_exclusive']),
                                 (width, digest, f'{pc+width:08x}'))
            self.assertEqual(sum(c['represented_instructions'] for c in result['function_coverage']), 128)
            for cov in result['function_coverage']:
                self.assertEqual((cov['unrepresented_instructions'], cov['unrepresented_ranges']), (0, []))
                self.assertEqual(cov['map_size'], a.MAP_SIZES.get(int(cov['entry'], 16)))

    def test_identical_results_and_exact_physical_spans(self):
        self.assertEqual([r['snapshot'] for r in self.results], ['db.3.gbf', 'db.4.gbf'])
        for key in ('ranges', 'cells', 'constants', 'mappings', 'function_coverage', 'recorded_bases',
                    'float_preconditions', 'reused_evidence'):
            self.assertEqual(self.results[0][key], self.results[1][key])
        for result in self.results:
            for key in ('ranges', 'cells', 'constants'):
                for item in result[key]: self.assertEqual(item['spans'], PHYSICAL[item['address']])
            self.assertEqual(result['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual(result['data5_sha256'], a.c.DATA5_SHA)
            self.assertEqual(result['executable_sha256_property_type'], 2)

    def test_constructor_source_offsets_establish_actor_fields(self):
        self.assertEqual(self.constructors[0], self.constructors[1])
        for result in self.constructors:
            q = {int(row['address'], 16): {k: v for k, v in row.items() if k != 'address'}
                 for row in result['instructions']}
            self.assertEqual(q[0x8006f610], dict(mnemonic='addis', rD=4, rA=0, immediate=-32723))
            self.assertEqual(q[0x8006f618], dict(mnemonic='addi', rD=4, rA=4, immediate=0x3b14))
            for source, destination in ((0xc, 0x4c0), (0x34, 0x4e8)):
                pc = 0x8006f620 + source * 2
                self.assertEqual(q[pc], dict(mnemonic='lwz', rD=0, rA=4, displacement=source))
                self.assertEqual(q[pc + 4], dict(mnemonic='stw', rS=0, rA=3, displacement=destination))
                self.assertIn(0x802d3b14 + source, [row[1] for row in a.CELLS])

    def test_reused_bias_and_literal_selections_only(self):
        self.assertEqual(self.biases[0], self.biases[1])
        self.assertEqual((self.biases[0]['address'], self.biases[0]['bits']),
                         ('804373d0', '4330000080000000'))
        for result in self.results:
            self.assertEqual([r['address'] for r in result['ranges']], [f'{pc:08x}' for pc, _, _ in a.RANGES])
            self.assertEqual([r['address'] for r in result['cells']], [f'{pc:08x}' for _, pc, _, _ in a.CELLS])
            self.assertEqual([r['address'] for r in result['constants']], ['80437298'])
            self.assertNotIn('raw', json.dumps(result))
            self.assertEqual(sum(r['width'] for k in ('ranges', 'cells', 'constants') for r in result[k]), 524)
            self.assertNotIn('802d3ca0', [r['address'] for r in result['ranges'] + result['cells'] + result['constants']])


if __name__ == '__main__':
    unittest.main()
