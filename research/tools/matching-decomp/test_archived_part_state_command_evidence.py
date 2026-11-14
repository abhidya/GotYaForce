#!/usr/bin/env python3
"""All46 operands, independent encodings, all60 prefix bytes and refusal guards.

Synthetic checks need no archives. Optional local archive tests authenticate
both existing snapshots and never download inputs or execute original code.
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

import read_archived_part_state_command_evidence as a


class FakeDB:
    def __init__(self, raw):
        self.raw, self.calls = raw, []

    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


FIELDS = {'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement', 'lhz': 'rD rA displacement',
          'stw': 'rS rA displacement', 'stb': 'rS rA displacement', 'addi': 'rD rA immediate',
          'rlwinm': 'rS rA SH MB ME Rc', 'xori': 'rS rA immediate', 'extsb': 'rS rA Rc',
          'or': 'rS rA rB Rc', 'cmpi': 'BF L rA immediate', 'cmpli': 'BF L rA immediate',
          'bc': 'BO BI LK target AA', 'blr': 'BO BI BH LK', 'bclr': 'BO BI BH LK'}


def ops(text):
    result = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        result.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                            for key, value in zip(keys, values)}))
    return result


# Frozen semantic schedule, not produced by the reader during testing.
EXPECTED = {
    0x8004c424: ops('''
lwz 6 5 0
rlwinm 4 0 0 31 31 1
addi 0 6 8
stw 0 5 0
bclr 12 2 0 0
lbz 0 6 2
stb 0 3 7407
lbz 0 6 3
stb 0 3 7408
lbz 0 6 4
stb 0 3 1768
lbz 0 6 5
stb 0 3 1769
lbz 4 6 1
extsb 4 0 0
cmpi 0 0 0 -2
bc 4 2 0 8004c478 0
lbz 0 3 1410
xori 0 0 1
stb 0 3 1410
blr 20 0 0 0
cmpi 0 0 0 -1
bclr 12 2 0 0
stb 4 3 1410
blr 20 0 0 0
'''),
    0x8004c488: ops('''
lwz 6 5 0
rlwinm 4 0 0 30 30 1
addi 0 6 8
stw 0 5 0
bclr 12 2 0 0
lbz 0 6 1
stb 0 3 7439
lbz 0 6 2
stb 0 3 7440
lhz 0 6 6
cmpli 0 0 0 65535
bclr 12 2 0 0
lwz 0 3 1504
rlwinm 0 0 0 28 19 0
stw 0 3 1504
lhz 0 6 6
lwz 4 3 1504
rlwinm 0 0 0 20 27 0
or 4 0 0 0
stw 0 3 1504
blr 20 0 0 0
'''),
}
RANGES = (
    (0x8004c424, 100, 'be8ac95c75902d94a0afcbb214ac797ca8f501e0676336d015a424da509cc839'),
    (0x8004c488, 84, 'f0408efcd1b500c334e09862a1a4f0209c4aab0205b2184750565a043cbe6eb3'),
)
DATA_WINDOWS = (
    ('ground-initial20', 0x802be5ee, 20, '14f850a2bf4697c92ac063e5b35fe68f5b54892c8653dd313e53fe3903ebdff6'),
    ('ground-continuation8', 0x802be602, 8, '8666d68f6b5964c5f8b774f3c4d2046a920342700c737366062abbd4c7841918'),
    ('air-initial20', 0x802be656, 20, '6186d688a629f42df51983a88011287bc65c8e74133aa53f5f7f67d32adeadfa'),
    ('air-continuation12', 0x802be66a, 12, '5053f080e446d14bbd04be06873b151c6dea341ac08b390863cf98ea957bdfad'),
)
TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)

# Independently authored numeric records; every payload and padding byte matters.
GROUND_RECORDS = (bytes([1, 4, 0, 1, 6, 0, 0, 0]), bytes([2, 255, 0, 0, 0, 0, 0, 0]),
                  bytes([3, 0, 1, 0, 0, 0, 0, 64]), bytes([0, 2, 0, 2]))
AIR_RECORDS = (bytes([1, 4, 1, 1, 6, 0, 0, 0]), GROUND_RECORDS[1], GROUND_RECORDS[2],
               bytes([8, 0, 0, 1]), bytes([0, 2, 0, 1]))
GROUND, AIR = b''.join(GROUND_RECORDS), b''.join(AIR_RECORDS)
PAYLOADS = {0x802be5ee: GROUND[:20], 0x802be602: GROUND[20:],
            0x802be656: AIR[:20], 0x802be66a: AIR[20:]}


def encode(row, pc):
    """Independent PPC inverse, not a call back into the decoder."""
    n = row['mnemonic']
    if n in ('lwz', 'lbz', 'lhz', 'stw', 'stb', 'addi', 'xori'):
        opcode, reg, imm = {'lwz': (32, 'rD', 'displacement'), 'lbz': (34, 'rD', 'displacement'),
            'lhz': (40, 'rD', 'displacement'), 'stw': (36, 'rS', 'displacement'),
            'stb': (38, 'rS', 'displacement'), 'addi': (14, 'rD', 'immediate'),
            'xori': (26, 'rS', 'immediate')}[n]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if n in ('blr', 'bclr'):
        return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | 16 << 1 | row['LK']
    if n == 'bc':
        target = int(row['target'], 16)
        displacement = target if row['AA'] else target - pc
        return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc | row['AA'] << 1 | row['LK']
    if n in ('cmpi', 'cmpli'):
        return (11 if n == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if n == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    if n in ('extsb', 'or'):
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | row.get('rB', 0) << 11 | (954 if n == 'extsb' else 444) << 1 | row['Rc']
    raise AssertionError(n)


def encoded(address):
    return b''.join(struct.pack('>I', encode(row, address + i * 4)) for i, row in enumerate(EXPECTED[address]))


def record_inverse(row):
    opcode = row['opcode']
    if opcode == 1:
        return bytes([opcode] + [row[k] for k in ('group', 'slot', 'mode', 'transition', 'reserved05')]) + struct.pack('>h', row['start_signed'])
    if opcode == 2:
        assert row['selector582_signed'] == struct.unpack('b', bytes([row['selector582']]))[0]
        return bytes([opcode] + [row[k] for k in ('selector582', 'part0_state1b', 'part0_auxiliary1c', 'byte6e8', 'byte6e9', 'reserved06', 'reserved07')])
    if opcode == 3:
        return bytes([opcode] + [row[k] for k in ('part1_state1b', 'part1_auxiliary1c', 'reserved03', 'reserved04', 'reserved05')]) + struct.pack('>H', row['control_unsigned'])
    if opcode == 8:
        return bytes([opcode, row['reserved01'], row['reserved02']]) + struct.pack('b', row['operand_signed'])
    assert opcode == 0
    return bytes([opcode, row['mode']]) + struct.pack('>h', row['wait_signed'])


class SyntheticTests(unittest.TestCase):
    def test_exact_inventory_mappings_and_exclusions(self):
        self.assertEqual(a.RANGES, RANGES)
        self.assertEqual(a.DATA_WINDOWS, DATA_WINDOWS)
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(a.DATA3_MAPPING, DATA3_MAPPING)
        addresses = {pc for pc, _, _ in a.RANGES} | {pc for _, pc, _, _ in a.DATA_WINDOWS}
        self.assertTrue(addresses.isdisjoint({0x802d0da0, 0x8004c5fc, 0x8031f004, 0x800ff418,
                                             0x8043386c, 0x804392c8, 0x802bd788}))

    def test_all_46_instruction_operands_inverse_encodings_and_hashes(self):
        self.assertEqual(sum(map(len, EXPECTED.values())), 46)
        for address, width, digest in RANGES:
            raw = encoded(address)
            self.assertEqual(len(raw), width)
            self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
            db = FakeDB(raw)
            result = a.range_evidence(db, TEXT_MAPPING, address, width)
            self.assertEqual(result['instructions'], [dict(address=f'{address + i * 4:08x}', **row)
                                                      for i, row in enumerate(EXPECTED[address])])
            self.assertEqual(db.calls, [(21, address - 0x800055e0, width, 2796416)])
            for i, row in enumerate(EXPECTED[address]):
                pc = address + i * 4
                word = encode(row, pc)
                self.assertEqual(a.decode_selected(word, pc), row)
                for bit in range(32):
                    changed = word ^ 1 << bit
                    try:
                        decoded = a.decode_selected(changed, pc)
                    except a.c.FormatError:
                        continue
                    if decoded is not None:
                        self.assertNotEqual(decoded, row)
                        self.assertEqual(encode(decoded, pc), changed)

    def test_all_returns_and_reserved_fields(self):
        returns = {pc + i * 4: row for pc, rows in EXPECTED.items() for i, row in enumerate(rows)
                   if row['mnemonic'] in ('blr', 'bclr')}
        self.assertEqual(tuple(returns), (0x8004c434, 0x8004c474, 0x8004c47c, 0x8004c484,
                                         0x8004c498, 0x8004c4b4, 0x8004c4d8))
        for pc, row in returns.items():
            self.assertEqual((row['BO'], row['BI'], row['BH'], row['LK']),
                             (12, 2, 0, 0) if row['mnemonic'] == 'bclr' else (20, 0, 0, 0))
            for bad in (encode(row, pc) | 1, encode(row, pc) | 0x800):
                with self.assertRaises(a.c.FormatError): a.decode_selected(bad, pc)
        with self.assertRaises(a.c.FormatError): a.decode_selected(0x4d820020, 0x8004c424)
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)

    def test_cursor_masks_stores_sentinels_and_fresh_control_loads(self):
        at = {pc + i * 4: row for pc, rows in EXPECTED.items() for i, row in enumerate(rows)}
        for pc, mask_bit in ((0x8004c424, 31), (0x8004c488, 30)):
            self.assertEqual(at[pc + 4], dict(mnemonic='rlwinm', rS=4, rA=0, SH=0, MB=mask_bit, ME=mask_bit, Rc=1))
            self.assertEqual(at[pc + 8], dict(mnemonic='addi', rD=0, rA=6, immediate=8))
            self.assertEqual(at[pc + 12], dict(mnemonic='stw', rS=0, rA=5, displacement=0))
            self.assertEqual(at[pc + 16]['mnemonic'], 'bclr')
        self.assertEqual([(pc, row['displacement']) for pc, row in at.items()
                          if row['mnemonic'] == 'stb'],
                         [(0x8004c43c, 0x1cef), (0x8004c444, 0x1cf0), (0x8004c44c, 0x6e8),
                          (0x8004c454, 0x6e9), (0x8004c470, 0x582), (0x8004c480, 0x582),
                          (0x8004c4a0, 0x1d0f), (0x8004c4a8, 0x1d10)])
        self.assertEqual([at[pc]['immediate'] for pc in (0x8004c460, 0x8004c478, 0x8004c4b0)], [-2, -1, 65535])
        self.assertEqual([(pc, row['rA'], row['displacement']) for pc, row in at.items()
                          if row['mnemonic'] == 'stw'],
                         [(0x8004c430, 5, 0), (0x8004c494, 5, 0), (0x8004c4c0, 3, 0x5e0), (0x8004c4d4, 3, 0x5e0)])
        self.assertEqual(at[0x8004c4c4], dict(mnemonic='lhz', rD=0, rA=6, displacement=6))
        self.assertEqual(at[0x8004c4c8], dict(mnemonic='lwz', rD=4, rA=3, displacement=0x5e0))
        self.assertEqual([(at[pc]['MB'], at[pc]['ME']) for pc in (0x8004c4bc, 0x8004c4cc)], [(28, 19), (20, 27)])
        self.assertFalse(any(row.get('displacement') == 0x584 for row in at.values()))

    def test_all_60_payload_bytes_roundtrip_with_exact_window_hashes(self):
        for _, address, width, digest in DATA_WINDOWS:
            raw = PAYLOADS[address]
            self.assertEqual(hashlib.sha256(raw).hexdigest(), digest)
            db = FakeDB(raw)
            selected, report = a.data_window(db, DATA3_MAPPING, address, width)
            self.assertEqual(selected, raw)
            self.assertEqual(report['sha256'], digest)
            self.assertEqual(db.calls, [(199, address - 0x802bae60, width, 1000128)])
        for address, raw, records in ((0x802be5ee, GROUND, GROUND_RECORDS), (0x802be656, AIR, AIR_RECORDS)):
            result = a.prefix_fields(address, raw[:20], raw[20:])
            self.assertEqual(result['width'], len(raw))
            self.assertEqual(result['end_exclusive'], f'{address + len(raw):08x}')
            self.assertEqual([record_inverse(row) for row in result['records']], list(records))
            cursor = address
            for row, record in zip(result['records'], records):
                self.assertEqual(row['address'], f'{cursor:08x}')
                self.assertEqual(row['width'], len(record))
                self.assertEqual(row['sha256'], hashlib.sha256(record).hexdigest())
                cursor += len(record)
            self.assertFalse(result['handler08_selected'])
            self.assertFalse(result['bank_headers_selected'])
        self.assertEqual([row['opcode'] for row in a.prefix_fields(0x802be656, AIR[:20], AIR[20:])['records']], [1, 2, 3, 8, 0])

    def test_each_selected_byte_mutation_refuses(self):
        for address, width, _ in RANGES:
            raw = encoded(address)
            for i in range(width):
                changed = raw[:i] + bytes([raw[i] ^ 1]) + raw[i + 1:]
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                    a.range_evidence(FakeDB(changed), TEXT_MAPPING, address, width)
        for _, address, width, _ in DATA_WINDOWS:
            raw = PAYLOADS[address]
            for i in range(width):
                changed = raw[:i] + bytes([raw[i] ^ 1]) + raw[i + 1:]
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                    a.data_window(FakeDB(changed), DATA3_MAPPING, address, width)
        for address, raw in ((0x802be5ee, GROUND), (0x802be656, AIR)):
            for i in range(len(raw)):
                changed = raw[:i] + bytes([raw[i] ^ 1]) + raw[i + 1:]
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                    a.prefix_fields(address, changed[:20], changed[20:])

    def test_fixed_allowlist_types_and_mappings_precede_reads(self):
        for fn, mapping, selections in ((a.range_evidence, TEXT_MAPPING, [(pc, width) for pc, width, _ in RANGES]),
                                         (a.data_window, DATA3_MAPPING, [(pc, width) for _, pc, width, _ in DATA_WINDOWS])):
            for address, width in selections:
                for pc, size in ((address - 1, width), (address + 1, width), (address, width + 1),
                                 (address, width - 1), (float(address), width), (address, True)):
                    db = FakeDB(bytes(width))
                    with self.assertRaises(a.c.FormatError): fn(db, mapping, pc, size)
                    self.assertFalse(db.calls)
                for index, value in enumerate(mapping):
                    bad = list(mapping); bad[index] = 'wrong' if isinstance(value, str) else value + 1
                    db = FakeDB(bytes(width))
                    with self.assertRaises(a.c.FormatError): fn(db, tuple(bad), address, width)
                    self.assertFalse(db.calls)
                db = FakeDB(bytes(width))
                with self.assertRaises(a.c.FormatError): fn(db, list(mapping), address, width)
                self.assertFalse(db.calls)

    def test_truncation_duplicates_and_decoder_fail_closed(self):
        for address, width, _ in RANGES:
            for raw in (encoded(address)[:-1], encoded(address) + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                    a.range_evidence(FakeDB(raw), TEXT_MAPPING, address, width)
        for _, address, width, _ in DATA_WINDOWS:
            for raw in (PAYLOADS[address][:-1], PAYLOADS[address] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                    a.data_window(FakeDB(raw), DATA3_MAPPING, address, width)
        for name, fn, mapping, address, width in (('RANGES', a.range_evidence, TEXT_MAPPING, 0x8004c424, 100),
                                                 ('DATA_WINDOWS', a.data_window, DATA3_MAPPING, 0x802be5ee, 20)):
            with patch.object(a, name, getattr(a, name) * 2):
                db = FakeDB(bytes(width))
                with self.assertRaises(a.c.FormatError): fn(db, mapping, address, width)
                self.assertFalse(db.calls)
        for row in (None, dict(mnemonic='lbz', rD=0, rA=0, displacement=0)):
            with patch.object(a, 'decode_selected', return_value=row):
                with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(encoded(0x8004c424)), TEXT_MAPPING, 0x8004c424, 100)

    def test_prefix_wrong_identity_shape_or_pair_refuses(self):
        for address, initial, tail in ((0x802be5ef, GROUND[:20], GROUND[20:]),
                                      (float(0x802be5ee), GROUND[:20], GROUND[20:]),
                                      (0x802be5ee, GROUND[:19], GROUND[20:]),
                                      (0x802be5ee, bytearray(GROUND[:20]), GROUND[20:]),
                                      (0x802be5ee, AIR[:20], GROUND[20:]),
                                      (0x802be5ee, GROUND[:20], AIR[20:]),
                                      (0x802be656, AIR[:20], AIR[20:-1]),
                                      (0x802be656, AIR[:20], AIR[20:] + b'\0')):
            with self.assertRaises(a.c.FormatError): a.prefix_fields(address, initial, tail)

    def test_authentication_precedes_parser_and_selections(self):
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
        blocks = {key: [name, None, None, 0, encoded_start, length, 0]
                  for name, key, encoded_start, length, root in a.command.MAPPINGS}
        subs = {key: [key, 2, length, 0, root, 0] for name, key, encoded_start, length, root in a.command.MAPPINGS}
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
            if target == 'overlap': bb[99] = ['other', None, None, 0, 0x200000000004c424, 4, 0]
            with patch.object(a.c, 'inspect', return_value=auth), patch.object(a.c, 'GBF') as parser, \
                 patch.object(a, 'range_evidence') as code, patch.object(a, 'data_window') as selected:
                db = parser.return_value
                db.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called(); selected.assert_not_called()

    def test_independent_extent_sources_and_no_address_cli(self):
        root = Path(__file__).resolve().parents[3]
        handlers = (root / 'research/decomp/anim-sound-op-decode-2026-07-04.md').read_text()
        for text in ('| 0x02 | 8004c424 |', '| 0x03 | 8004c488 |', '| 0x04 | 8004c4dc |'):
            self.assertIn(text, handlers)
        control = (root / 'research/decomp/stream-control-reachability-2026-11-12.md').read_text()
        self.assertIn('84-byte (0x54) function through 8004c4d8', control)
        ninja = (root / 'research/decomp/double-ninja-source-x-2026-11-12.md').read_text()
        self.assertIn('802be5ee/802be656', ninja)
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/part-state-evidence.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', json.loads(error.getvalue())['error'])


SNAPSHOT_DIR = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports, cls.reads = [], []
        original = a.c.GBF.chain
        for name in ('db.3.gbf', 'db.4.gbf'):
            reads = []
            def traced(db, *args):
                reads.append(args)
                return original(db, *args)
            raw = (SNAPSHOT_DIR / name).read_bytes()
            with patch.object(a.c.GBF, 'chain', traced):
                cls.reports.append(a.inspect(raw, hashlib.sha256(raw).hexdigest()))
            cls.reads.append(reads)

    def test_both_snapshots_all_facts_and_physical_spans_agree(self):
        for key in ('mappings', 'ranges', 'windows', 'prefixes', 'function_coverage', 'reused_table_witness'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            for span in report['ranges']:
                pc = int(span['address'], 16)
                self.assertEqual(span['instructions'], [dict(address=f'{pc + i * 4:08x}', **row)
                                                        for i, row in enumerate(EXPECTED[pc])])
            self.assertEqual([[record_inverse(row) for row in prefix['records']] for prefix in report['prefixes']],
                             [list(GROUND_RECORDS), list(AIR_RECORDS)])

    def test_exact_six_literal_reads_and_no_command_table(self):
        expected = [(21, pc - 0x800055e0, width, 2796416) for pc, width, _ in RANGES]
        expected += [(199, pc - 0x802bae60, width, 1000128) for _, pc, width, _ in DATA_WINDOWS]
        for reads in self.reads:
            self.assertEqual([row for row in reads if row[0] in (21, 199)], expected)
            # The only other payload reads belong to the unchanged data5 authenticator.
            self.assertTrue(all(row[0] in (21, 199, 263) for row in reads))
        witness = self.reports[0]['reused_table_witness']
        self.assertFalse(witness['read_here'])
        self.assertEqual(witness['slots'], {'02': '8004c424', '03': '8004c488'})

    def test_exact_physical_provenance_and_output_shape(self):
        report = self.reports[0]
        expected = {0x8004c424: (21, 39, 290372, 11946, 100, 667312),
                    0x8004c488: (21, 39, 290472, 12046, 84, 667412),
                    0x802be5ee: (199, 200, 14222, 14222, 20, 3307412),
                    0x802be602: (199, 200, 14242, 14242, 8, 3307432),
                    0x802be656: (199, 200, 14326, 14326, 20, 3307516),
                    0x802be66a: (199, 200, 14346, 14346, 12, 3307536)}
        for row in report['ranges'] + report['windows']:
            root, data, chain_offset, data_offset, length, physical = expected[int(row['address'], 16)]
            self.assertEqual(row['spans'], [dict(root_buffer=root, data_buffer=data, chain_offset=chain_offset,
                                                data_offset=data_offset, length=length, obfuscated=True, physical_offset=physical)])
        for row in report['windows']:
            self.assertEqual(set(row), {'label', 'address', 'end_exclusive', 'width', 'sha256', 'spans'})
        self.assertEqual([r['represented_instructions'] for r in report['function_coverage']], [25, 21])

    def test_real_archive_tamper_and_selected_payload_tamper_refuse(self):
        raw = (SNAPSHOT_DIR / 'db.3.gbf').read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        with patch.object(a, 'range_evidence') as selected:
            for changed, claimed in ((raw, '0' * 64), (raw[:-1] + bytes([raw[-1] ^ 1]), digest)):
                with self.assertRaisesRegex(a.c.FormatError, 'SHA256 not allowlisted'): a.inspect(changed, claimed)
            selected.assert_not_called()
        original = a.c.GBF.chain
        for root, offset, width, length in self.reads[0]:
            if root not in (21, 199):
                continue
            target = (root, offset, width, length)
            def altered(db, *args):
                data, spans = original(db, *args)
                return (bytes([data[0] ^ 1]) + data[1:] if args == target else data), spans
            with patch.object(a.c.GBF, 'chain', altered):
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)


if __name__ == '__main__':
    unittest.main()
