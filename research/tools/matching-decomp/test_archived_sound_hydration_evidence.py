#!/usr/bin/env python3
"""Fixed operand/inverse, byte-field and fail-closed hydration evidence tests."""
import contextlib
import copy
import hashlib
import io
import json
from pathlib import Path
import struct
import unittest
from unittest.mock import patch

import read_archived_sound_hydration_evidence as a
import test_archived_double_action_evidence as previous

FakeDB = previous.FakeDB
# Frozen independently inverse-encoded schedule, not generated during tests.
EXPECTED = previous.ops('''
stwu 1 1 -112
mflr 0
stw 0 1 116
stfd 31 1 96
psq_st 31 1 104 0 0
stmw 24 1 64
or 3 31 3 0
addis 3 0 -32708
lbz 0 31 999
addi 3 3 19836
extsb 0 0 0
rlwinm 0 0 2 0 29 0
lwzx 0 3 0
cmpli 0 0 0 0
stw 0 31 7544
bc 12 2 0 8004bb60 0
lwz 0 13 -21324
stw 0 31 7548
b 8004bb68 0 0
addi 0 0 0
stw 0 31 7548
or 31 3 31 0
addi 25 31 4820
addi 28 31 5588
addi 27 31 5204
addi 24 31 5972
bl 80006f98 0 1
lfs 31 2 -31024
or 31 29 31 0
or 3 30 3 0
addi 26 0 0
b 8004bc18 0 0
lfs 0 30 12
addi 3 1 8
stfs 0 25 0
lfs 0 30 28
stfs 0 25 4
lfs 0 30 44
stfs 0 25 8
lwz 4 25 0
lwz 0 25 4
stw 4 27 0
stw 0 27 4
lwz 0 25 8
addi 25 25 12
stw 0 27 8
addi 27 27 12
stfs 31 28 8
stfs 31 28 4
stfs 31 28 0
addi 28 28 12
stfs 31 24 8
stfs 31 24 4
stfs 31 24 0
addi 24 24 12
bl 8020aefc 0 1
addi 3 29 3796
addi 4 1 8
bl 8020bcb0 0 1
addi 3 29 4308
addi 4 1 8
bl 8020bcb0 0 1
addi 30 30 48
addi 29 29 16
addi 26 26 1
lbz 0 31 7568
extsb 0 0 0
cmp 0 0 26 0
bc 12 0 0 8004bb94 0
addi 0 0 4
addi 4 31 6356
addi 3 0 0
mtctr 0
sth 3 4 4
sth 3 4 2
sth 3 4 0
sth 3 4 10
sth 3 4 8
sth 3 4 6
sth 3 4 16
sth 3 4 14
sth 3 4 12
sth 3 4 22
sth 3 4 20
sth 3 4 18
sth 3 4 28
sth 3 4 26
sth 3 4 24
sth 3 4 34
sth 3 4 32
sth 3 4 30
sth 3 4 40
sth 3 4 38
sth 3 4 36
sth 3 4 46
sth 3 4 44
sth 3 4 42
addi 4 4 48
bc 16 0 0 8004bc38 0
lfs 1 2 -31020
addi 0 0 -1
addi 26 0 0
lfs 0 2 -31024
stfs 1 31 7612
or 31 27 31 0
stfs 1 31 7616
stfs 1 31 7620
stfs 1 31 7508
stfs 1 31 7512
stfs 1 31 7516
stw 0 31 7536
lwz 3 31 1200
lbz 0 3 2
stb 0 31 1401
sth 26 31 7524
sth 26 31 7526
sth 26 31 7528
stfs 0 31 7624
stfs 0 31 7628
stfs 1 31 7580
stb 26 31 7579
stb 26 31 7602
stfs 1 31 7520
stfs 0 31 1752
stfs 1 31 1748
stfs 1 31 1744
lfs 0 31 36
stfs 0 31 1756
or 27 29 27 0
or 31 28 31 0
addi 25 0 0
addi 30 0 -1
addi 24 29 6868
addi 4 0 0
or 24 3 24 0
addi 5 0 64
bl 8000540c 0 1
stb 26 24 51
addi 3 28 7380
addi 4 0 0
addi 5 0 32
stb 25 24 52
stb 30 24 55
bl 8000540c 0 1
addi 25 25 1
addi 28 28 32
cmpi 0 0 25 4
addi 29 29 64
bc 12 0 0 8004bd24 0
addi 26 26 1
addi 27 27 256
cmpi 0 0 26 2
bc 12 0 0 8004bd14 0
lwz 3 31 1200
lbz 0 3 12
stb 0 31 7569
lwz 3 31 1200
lbz 0 3 13
stb 0 31 7570
lwz 3 31 1200
lbz 0 3 14
stb 0 31 7571
lwz 3 31 1200
lfs 1 3 104
lfs 0 3 88
fdivs 0 1 0 0
stfs 0 31 7636
lwz 3 31 1200
lfs 1 3 104
lfs 0 3 92
fdivs 0 1 0 0
stfs 0 31 7640
lwz 3 31 1200
lfs 1 3 104
lfs 0 3 96
fdivs 0 1 0 0
stfs 0 31 7644
lwz 3 31 1200
lfs 1 3 104
lfs 0 3 100
fdivs 0 1 0 0
stfs 0 31 7648
psq_l 31 1 104 0 0
lfd 31 1 96
lmw 24 1 64
lwz 0 1 116
mtlr 0
addi 1 1 112
blr 20 0 0 0
''')
ENTRY = 0x8004bb14
GROUND = bytes([255, 0, 0, 0, 4, 0, 1, 0, 22, 255, 255, 0, 4, 0, 1, 0, 23, 0, 5, 1])
AIR = bytes([255, 0, 0, 0, 4, 1, 1, 0, 25, 255, 255, 0, 4, 1, 1, 0, 255, 3, 5, 0])
DESCRIPTORS = [(0x802bdd60, GROUND), (0x802bdd74, AIR)]
SOUND_ROWS = {
    22: (22, 1, 0, 9, 255, 0),
    23: (35, 1, 1, 103, 0, 0),
    24: (46, 1, 1, 103, 255, 0),
    25: (20, 1, 0, 9, 255, 0),
}
SOUND_HASHES = [
    '6efdec15782a31746c3750cbf0bd50b6c17ea71e5bf299d03f386cdeebaa9c0f',
    '8eb4d90e59ba9ff29fdf22542acbf49bc9e5117375ca8505c6e4bb6eafbbae8b',
    '7b9babbe7055a9f627745df830a58a541037d4fba928f28e89e68eb88e4fee38',
    'd348ac1a16d5d1d4ae6c0dcc79835ebe3e0c7a447945dadb9ba7fca05638878a',
]


def encoded():
    return b''.join(struct.pack('>I', previous.encode(row, ENTRY + i * 4)) for i, row in enumerate(EXPECTED))


def sound_fixture():
    # Explicit synthetic unselected bytes, never a purported retail table dump.
    result = bytearray([0xa5] * a.SOUND_WIDTH)
    for index, values in SOUND_ROWS.items():
        result[index * 8:index * 8 + 8] = struct.pack('>HBBHBB', *values)
    return bytes(result)


def descriptor_inverse(fields):
    p, q = fields['part0'], fields['part1']
    return bytes([fields[k] for k in ('scaleIndex32', 'reserved01', 'reserved02', 'reserved03')] +
        [p[k] for k in ('selector2a', 'selector2b', 'flags', 'rewind26', 'auxiliary37', 'fallbackBE', 'fallbackBF', 'reserved0b')] +
        [q[k] for k in ('selector2a', 'selector2b', 'flags', 'rewind26', 'auxiliary37', 'byte1d98', 'byte1d99', 'byte1d9b')])


class SyntheticTests(unittest.TestCase):
    def test_all_189_instruction_operands_and_inverse_digest(self):
        raw = encoded()
        self.assertEqual(len(EXPECTED), 189)
        self.assertEqual(hashlib.sha256(raw).hexdigest(), a.RANGES[0][2])
        report = a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, ENTRY, 756)
        self.assertEqual(report['instructions'], [dict(address=f'{ENTRY + i * 4:08x}', **row) for i, row in enumerate(EXPECTED)])
        for i, row in enumerate(EXPECTED):
            pc = ENTRY + i * 4
            word = previous.encode(row, pc)
            self.assertEqual(a.decode_selected(word, pc), row)
            for bit in range(32):
                changed = word ^ 1 << bit
                try:
                    decoded = a.decode_selected(changed, pc)
                except a.c.FormatError:
                    continue
                if decoded is not None:
                    self.assertNotEqual(decoded, row)
                    self.assertEqual(previous.encode(decoded, pc), changed)

    def test_fixed_allowlists_types_and_mappings_before_reads(self):
        for address, width in ((ENTRY - 4, 756), (ENTRY, 752), (ENTRY, True), (float(ENTRY), 756)):
            db = FakeDB(encoded())
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, a.TEXT_MAPPING, address, width)
            self.assertEqual(db.calls, [])
        for _, address, width, _ in a.DATA_WINDOWS:
            for pc, size in ((address + 1, width), (address, width + 1), (float(address), width), (address, True)):
                if (pc, size) == (address, width) and type(size) is not bool: continue
                db = FakeDB(bytes(width))
                with self.assertRaises(a.c.FormatError): a.data_window(db, a.DATA3_MAPPING, pc, size)
                self.assertEqual(db.calls, [])
        for fn, mapping, address, width in ((a.range_evidence, a.TEXT_MAPPING, ENTRY, 756),
                                           (a.data_window, a.DATA3_MAPPING, 0x802bdd60, 20)):
            for index in range(len(mapping)):
                bad = list(mapping)
                bad[index] = 'wrong' if isinstance(bad[index], str) else bad[index] + 1
                db = FakeDB(bytes(width))
                with self.assertRaises(a.c.FormatError): fn(db, tuple(bad), address, width)
                self.assertEqual(db.calls, [])

    def test_width_hash_duplicate_and_decoder_refusals(self):
        for raw in (encoded()[:-1], bytes(756)):
            with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(raw), a.TEXT_MAPPING, ENTRY, 756)
        for raw in (GROUND[:-1], bytes(20)):
            with self.assertRaises(a.c.FormatError): a.data_window(FakeDB(raw), a.DATA3_MAPPING, 0x802bdd60, 20)
        with patch.object(a, 'RANGES', a.RANGES * 2):
            db = FakeDB(encoded())
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, a.TEXT_MAPPING, ENTRY, 756)
            self.assertFalse(db.calls)
        with patch.object(a, 'DATA_WINDOWS', a.DATA_WINDOWS * 2):
            db = FakeDB(GROUND)
            with self.assertRaises(a.c.FormatError): a.data_window(db, a.DATA3_MAPPING, 0x802bdd60, 20)
            self.assertFalse(db.calls)
        with patch.object(a, 'decode_selected', return_value=None):
            with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(encoded()), a.TEXT_MAPPING, ENTRY, 756)

    def test_each_descriptor_byte_roundtrips_and_hashes(self):
        for address, raw in DESCRIPTORS:
            self.assertEqual(descriptor_inverse(a.descriptor_fields(raw)), raw)
            db = FakeDB(raw)
            selected, report = a.data_window(db, a.DATA3_MAPPING, address, 20)
            self.assertEqual(selected, raw)
            self.assertEqual(db.calls, [(199, address - 0x802bae60, 20, 1000128)])
            self.assertEqual(report['sha256'], hashlib.sha256(raw).hexdigest())
        for size in (0, 19, 21):
            with self.assertRaises(a.c.FormatError): a.descriptor_fields(bytes(size))

    def test_exact_scalar_windows(self):
        for address, raw in ((0x8033af7a, bytes([3])), (0x8033b036, bytes([0, 1])),
                             (0x802bd788, struct.pack('>h', 0x124)),
                             (0x802bd8a4, struct.pack('>h', 0x4bc)), (0x802bd8a6, struct.pack('>h', 0x4d0))):
            db = FakeDB(raw)
            self.assertEqual(a.data_window(db, a.DATA3_MAPPING, address, len(raw))[0], raw)
            self.assertEqual(len(db.calls), 1)

    def test_only_reached_sound_rows_all_bytes_and_termination(self):
        chains = a.reached_chains(sound_fixture(), 3, DESCRIPTORS)
        self.assertEqual([(r['selector'], len(r['records']), r['closed']) for r in chains],
                         [(22, 1, True), (23, 2, True), (25, 1, True), (255, 0, True)])
        rows = [row for chain in chains for row in chain['records']]
        self.assertEqual([r['index'] for r in rows], [22, 23, 24, 25])
        self.assertEqual([r['sha256'] for r in rows], SOUND_HASHES)
        for row in rows:
            values = tuple(row[k] for k in ('frame', 'windowFlag', 'mode', 'soundId', 'continuation', 'pad'))
            self.assertEqual(values, SOUND_ROWS[row['index']])
            self.assertEqual(hashlib.sha256(struct.pack('>HBBHBB', *values)).hexdigest(), row['sha256'])
        other = bytearray(sound_fixture())
        other[:22 * 8] = bytes(22 * 8)
        other[26 * 8:] = bytes(len(other) - 26 * 8)
        self.assertEqual(a.reached_chains(bytes(other), 3, DESCRIPTORS), chains)

    def test_bad_sound_inputs_and_unclosed_chains_refuse(self):
        for mask in (True, 0, 1, 2, 7, 255):
            with self.assertRaises(a.c.FormatError): a.reached_chains(sound_fixture(), mask, DESCRIPTORS)
        for size in (0, 295, 297):
            with self.assertRaises(a.c.FormatError): a.reached_chains(bytes(size), 3, DESCRIPTORS)
        for index in (128, 254, 37, 127):
            raw = bytearray(GROUND); raw[8] = index
            with self.assertRaises(a.c.FormatError): a.reached_chains(sound_fixture(), 3, [(0x802bdd60, bytes(raw)), DESCRIPTORS[1]])
        raw = bytearray(GROUND); raw[8] = 36
        with self.assertRaisesRegex(a.c.FormatError, 'exceeds'):
            a.reached_chains(bytes(a.SOUND_WIDTH), 3, [(0x802bdd60, bytes(raw)), DESCRIPTORS[1]])
        with self.assertRaises(a.c.FormatError): a.reached_chains(sound_fixture(), 3, list(reversed(DESCRIPTORS)))

    def test_full_authentication_precedes_parser_or_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code, patch.object(a, 'data_window') as data:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad')
            db.assert_not_called(); code.assert_not_called(); data.assert_not_called()

    def test_real_hash_and_schema_refusals_precede_selections(self):
        for digest in ('0' * 64, hashlib.sha256(bytes(32)).hexdigest(), next(iter(a.c.SNAPSHOTS))):
            with patch.object(a.c, 'GBF') as parser, patch.object(a, 'data_window') as selected:
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'):
                    a.inspect(bytes(32), digest)
                parser.assert_not_called(); selected.assert_not_called()
        data = b'synthetic schema fixture'
        digest = hashlib.sha256(data).hexdigest()
        schema = dict(version=0, keytype=4, types=[4], fields='Key;Value;')
        for key, value in (('version', 1), ('keytype', 3), ('types', [2]), ('fields', 'Wrong;')):
            changed = dict(schema); changed[key] = value
            with patch.dict(a.c.SNAPSHOTS, {digest: 'synthetic'}), patch.object(a.c, 'GBF') as parser, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'data_window') as selected:
                parser.return_value.tables.return_value = {'Program': changed}
                with self.assertRaisesRegex(a.c.FormatError, 'unsupported schema: Program'): a.inspect(data, digest)
                parser.return_value.rows.assert_not_called(); code.assert_not_called(); selected.assert_not_called()

    def test_real_mapping_refusals_precede_selections(self):
        blocks = {key: [name, None, None, 0, encoded, length, 0]
                  for name, key, encoded, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0] for name, key, encoded, length, root in a.command.MAPPINGS}
        for target in ('text-root', 'text-offset', 'text-type', 'text-length', 'data3-root', 'data3-offset',
                       'data5-root', 'data5-offset', 'text-duplicate', 'data3-duplicate-sub', 'image', 'overlap'):
            auth, bb, ss = copy.deepcopy(({'image_offset': '80000000'}, blocks, subs))
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
            if target == 'image': auth['image_offset'] = '80000004'
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x200000000004bb14, 4, 0]
            with patch.object(a.c, 'inspect', return_value=auth), patch.object(a.c, 'GBF') as parser, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'data_window') as selected:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called(); selected.assert_not_called()

    def test_initializer_mask_and_all_eight_row_producer_order(self):
        at = {ENTRY + i * 4: row for i, row in enumerate(EXPECTED)}
        self.assertEqual(at[0x8004bcd0], dict(mnemonic='lwz', rD=3, rA=31, displacement=0x4b0))
        self.assertEqual(at[0x8004bcd4], dict(mnemonic='lbz', rD=0, rA=3, displacement=2))
        self.assertEqual(at[0x8004bcd8], dict(mnemonic='stb', rS=0, rA=31, displacement=0x579))
        self.assertEqual(at[0x8004bd20], dict(mnemonic='addi', rD=30, rA=0, immediate=-1))
        self.assertEqual(at[0x8004bd30]['immediate'], 64)
        self.assertEqual(at[0x8004bd34]['target'], '8000540c')
        self.assertEqual(at[0x8004bd38], dict(mnemonic='stb', rS=26, rA=24, displacement=0x33))
        self.assertEqual(at[0x8004bd48], dict(mnemonic='stb', rS=25, rA=24, displacement=0x34))
        self.assertEqual(at[0x8004bd4c], dict(mnemonic='stb', rS=30, rA=24, displacement=0x37))
        self.assertEqual(at[0x8004bd5c]['immediate'], 4)
        self.assertEqual(at[0x8004bd60]['immediate'], 64)
        self.assertEqual(at[0x8004bd6c]['immediate'], 256)
        self.assertEqual(at[0x8004bd70]['immediate'], 2)

    def test_independent_extent_and_no_arbitrary_cli(self):
        root = Path(__file__).resolve().parents[3]
        source = (root / 'research/decomp/ghidra-export/chunk_0006.c').read_text()
        self.assertIn('// ==== 8004bb14  FUN_8004bb14 ====', source)
        self.assertIn('// ==== 8004be08  zz_004be08_ ====', source)
        mapping = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        self.assertNotIn('\n8004bb14 ', mapping)
        for option in ('--address', '--width', '--pointer', '--target'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)


SNAPSHOT_DIR = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports = []
        for name in ('db.3.gbf', 'db.4.gbf'):
            raw = (SNAPSHOT_DIR / name).read_bytes()
            cls.reports.append(a.inspect(raw, hashlib.sha256(raw).hexdigest()))

    def test_both_snapshots_full_facts_and_physical_traces_agree(self):
        for key in ('mappings', 'ranges', 'windows', 'activeMask579', 'descriptor_defaults', 'lookup',
                    'descriptors', 'reached_sound_chains', 'initialized_state', 'function_coverage'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual(self.reports[0]['ranges'][0]['instructions'],
                         [dict(address=f'{ENTRY + i * 4:08x}', **row) for i, row in enumerate(EXPECTED)])
        for fields, (_, raw) in zip(self.reports[0]['descriptors'], DESCRIPTORS):
            self.assertEqual(descriptor_inverse(fields), raw)
        self.assertEqual(self.reports[0]['reached_sound_chains'], a.reached_chains(sound_fixture(), 3, DESCRIPTORS))

    def test_exact_selection_inventory_and_no_raw_sound_window(self):
        report = self.reports[0]
        self.assertEqual([(r['address'], r['width']) for r in report['windows']],
                         [(f'{pc:08x}', width) for _, pc, width, _ in a.DATA_WINDOWS])
        self.assertEqual(report['activeMask579'], 3)
        self.assertEqual(report['descriptor_defaults'], dict(address='8033b036', bytebe=0, bytebf=1))
        for row in report['windows']:
            self.assertEqual(set(row), {'label', 'address', 'end_exclusive', 'width', 'sha256', 'spans'})
        records = [row for chain in report['reached_sound_chains'] for row in chain['records']]
        self.assertEqual([row['address'] for row in records], ['802d3d50', '802d3d58', '802d3d60', '802d3d68'])
        self.assertEqual(report['ranges'][0]['spans'], [dict(root_buffer=21, data_buffer=39,
            chain_offset=288052, data_offset=9626, length=756, obfuscated=True, physical_offset=664992)])


if __name__ == '__main__':
    unittest.main()
