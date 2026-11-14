#!/usr/bin/env python3
"""Independent operands/inverse:149 instructions,596 bytes,3 fixed reads.

Semantic fixtures are manually authored, not populated from archive/reader/
decoder output at test time. Existing snapshots are optional and never fetched.
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

import read_archived_object_scheduler_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
RANGES = (
    (0x80089898, 228, '126a25b8262b9ec16da7e6121fd72318cce3c39faab481f718d2a559307c1299'),
    (0x8008997c, 280, '3d628d2b7b32b3cd2c7e0816370547898bb863673bd68351246c797720e57eab'),
    (0x80089a94, 88, 'dcb8bf7edce7313e0e258ee526af82153e5e35eac0987938a42cccc6a270dde4'),
)
FIELDS = {
    'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement',
    'sth': 'rS rA displacement', 'stmw': 'rS rA displacement', 'lmw': 'rD rA displacement',
    'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement', 'lhz': 'rD rA displacement',
    'addi': 'rD rA immediate', 'addis': 'rD rA immediate',
    'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc', 'slw': 'rS rA rB Rc',
    'add': 'rD rA rB Rc', 'extsb': 'rS rA Rc',
    'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS', 'lwzx': 'rD rA rB',
    'bl': 'target AA LK', 'b': 'target AA LK', 'bc': 'BO BI target AA LK',
    'blr': 'BO BI BH LK', 'bctrl': 'BO BI BH LK',
    'rlwinm': 'rS rA SH MB ME Rc', 'cmpi': 'BF L rA immediate', 'cmpli': 'BF L rA immediate',
}


def ops(text):
    rows = []
    for line in text.strip().splitlines():
        name, *values = line.split()
        keys = FIELDS[name].split()
        assert len(keys) == len(values), line
        rows.append(dict(mnemonic=name, **{key: value if key == 'target' else int(value, 0)
                                           for key, value in zip(keys, values)}))
    return rows


EXPECTED = {
    0x80089898: ops('''
stwu 1 1 -16
mflr 0
cmpi 0 0 3 56
stw 0 1 20
stw 31 1 12
stw 30 1 8
bc 4 0 800898ec 0 0
rlwinm 3 0 0 29 31 0
cmpi 0 0 0 7
bc 12 2 800898ec 0 0
cmpi 0 0 3 8
bc 4 0 800898dc 0 0
lwz 4 13 -31852
lbz 0 4 0xd2
rlwinm 0 0 0 24 24 1
bc 12 2 800898ec 0 0
b 80089964 0 0
lwz 4 13 -31852
lbz 0 4 0xd1
rlwinm 0 0 0 24 24 1
bc 4 2 80089964 0 0
addis 4 0 -32708
rlwinm 3 0 2 0 29 0
addi 3 4 0x706c
addi 31 0 0
lwzx 30 3 0
b 8008995c 0 0
lbz 0 30 0
extsb 0 0 1
bc 12 2 80089958 0 0
lwz 4 30 0x20
or 30 3 30 0
lwz 0 30 0x24
stw 4 30 0x2c
stw 0 30 0x30
lwz 0 30 0x28
stw 0 30 0x34
lwz 0 30 0x70
stw 0 30 0x76
lhz 0 30 0x74
sth 0 30 0x7a
lwz 12 30 0xc
mtctr 12
bctrl 20 0 0 1
lbz 0 30 0x86
extsb 0 0 1
bc 12 2 80089958 0 0
stb 31 30 0x1ca
lwz 30 30 8
cmpli 0 0 30 0
bc 4 2 80089904 0 0
lwz 0 1 20
lwz 31 1 12
lwz 30 1 8
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x8008997c: ops('''
stwu 1 1 -32
mflr 0
stw 0 1 36
stmw 27 1 12
or 3 29 3 0
cmpi 0 0 29 56
bc 4 0 80089a80 0 0
addis 3 0 -32708
addi 30 0 0
addi 31 3 0x4e84
lwz 3 31 0
lbz 0 3 0
extsb 0 0 1
bc 12 2 80089a70 0 0
cmpi 0 0 29 8
bc 4 0 800899d8 0 0
lwz 3 13 -31852
addi 0 0 1
slw 0 0 30 0
lbz 3 3 0xd2
and 3 0 0 1
bc 4 2 80089a70 0 0
b 800899f0 0 0
lwz 3 13 -31852
addi 0 0 1
slw 0 0 30 0
lbz 3 3 0xd1
and 3 0 0 1
bc 4 2 80089a70 0 0
add 0 29 30 0
addis 3 0 -32708
rlwinm 0 4 2 0 29 0
addi 28 0 0
addi 0 3 0x706c
add 3 0 4 0
lwz 27 3 4
b 80089a68 0 0
lbz 0 27 0
extsb 0 0 1
bc 12 2 80089a64 0 0
lwz 4 27 0x20
or 27 3 27 0
lwz 0 27 0x24
stw 4 27 0x2c
stw 0 27 0x30
lwz 0 27 0x28
stw 0 27 0x34
lwz 0 27 0x70
stw 0 27 0x76
lhz 0 27 0x74
sth 0 27 0x7a
lwz 12 27 0xc
mtctr 12
bctrl 20 0 0 1
lbz 0 27 0x86
extsb 0 0 1
bc 12 2 80089a64 0 0
stb 28 27 0x1ca
lwz 27 27 8
cmpli 0 0 27 0
bc 4 2 80089a10 0 0
addi 30 30 1
addi 31 31 4
cmpi 0 0 30 6
bc 12 0 800899a4 0 0
lmw 27 1 12
lwz 0 1 36
mtlr 0
addi 1 1 32
blr 20 0 0 0
'''),
    0x80089a94: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
stw 31 1 12
or 3 31 3 0
cmpi 0 0 31 56
bc 4 0 80089ab8 0 0
rlwinm 31 0 0 29 31 1
bc 12 2 80089ac4 0 0
or 31 3 31 0
bl 80089898 0 1
b 80089ad8 0 0
bl 8008997c 0 1
or 31 3 31 0
bl 80089898 0 1
addi 3 31 7
bl 80089898 0 1
lwz 0 1 20
lwz 31 1 12
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
}


def encode(row, pc):
    """Independent PPC inverse, with no decoder/report/archive inputs."""
    name = row['mnemonic']
    forms = {'stwu': (37, 'rS', 'displacement'), 'stw': (36, 'rS', 'displacement'),
             'stb': (38, 'rS', 'displacement'), 'sth': (44, 'rS', 'displacement'),
             'stmw': (47, 'rS', 'displacement'), 'lmw': (46, 'rD', 'displacement'),
             'lwz': (32, 'rD', 'displacement'), 'lbz': (34, 'rD', 'displacement'),
             'lhz': (40, 'rD', 'displacement'), 'addi': (14, 'rD', 'immediate'),
             'addis': (15, 'rD', 'immediate')}
    if name in forms:
        opcode, reg, imm = forms[name]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name in ('mflr', 'mtlr', 'mtctr'):
        return (31 << 26 | row['rD' if name == 'mflr' else 'rS'] << 21 |
                (9 if name == 'mtctr' else 8) << 16 | (339 if name == 'mflr' else 467) << 1)
    if name in ('or', 'and', 'slw', 'add', 'lwzx'):
        xo, reg = {'or': (444, 'rS'), 'and': (28, 'rS'), 'slw': (24, 'rS'),
                   'add': (266, 'rD'), 'lwzx': (23, 'rD')}[name]
        return (31 << 26 | row[reg] << 21 | row['rA'] << 16 | row['rB'] << 11 |
                xo << 1 | row.get('Rc', 0))
    if name == 'extsb':
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | 954 << 1 | row['Rc']
    if name in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if name == 'bc':
            return (16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc |
                    row['AA'] << 1 | row['LK'])
        return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name in ('blr', 'bctrl'):
        return (19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 |
                (528 if name == 'bctrl' else 16) << 1 | row['LK'])
    if name == 'rlwinm':
        return (21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 |
                row['MB'] << 6 | row['ME'] << 1 | row['Rc'])
    if name in ('cmpi', 'cmpli'):
        return ((11 if name == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 |
                row['rA'] << 16 | row['immediate'] & 65535)
    raise AssertionError(name)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
EXPECTED_READS = [(21, 541368, 228, 2796416), (21, 541596, 280, 2796416),
                  (21, 541876, 88, 2796416)]


def at(entry):
    return {entry + i * 4: row for i, row in enumerate(EXPECTED[entry])}


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_independent_extents_and_reused_cleanup(self):
        self.assertEqual(a.RANGES, RANGES); self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(sum(map(len, BODIES.values())), 596)
        self.assertEqual([len(rows) for rows in EXPECTED.values()], [57, 70, 22])
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        source = (root / 'research/decomp/ghidra-export/chunk_0013.c').read_text()
        for pc, width, _ in RANGES:
            start = index.index(f'{pc:08x}\tzz_{pc - 0x80000000:07x}_\tchunk_0013.c')
            self.assertTrue(index[start + 1].startswith(f'{pc + width:08x}\t'))
            body, suffix = source.split(f'// ==== {pc:08x} ', 1)[1].split('// ==== ', 1)
            self.assertTrue(suffix.startswith(f'{pc + width:08x} '))
            self.assertRegex(symbols, rf'(?m)^{pc:08x} {width:08x} {pc:08x} 0 ')
            self.assertTrue(body.strip())
        import read_archived_projectile_cleanup_evidence as cleanup
        available = {pc: (width, digest) for pc, width, digest in cleanup.RANGES}
        self.assertEqual([row['address'] for row in a.REUSED_EVIDENCE], ['80088e50', '80089814'])
        for row in a.REUSED_EVIDENCE:
            self.assertEqual((row['width'], row['sha256']), available[int(row['address'], 16)])
            self.assertIs(row['read_here'], False)

    def test_all149_operands_independent_inverse_hash_and4768_bit_controls(self):
        mutations = 0
        for pc, width, digest in RANGES:
            body, rows = BODIES[pc], EXPECTED[pc]
            self.assertEqual(len(body), width); self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
            report = a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
            self.assertEqual(report['instructions'], [dict(address=f'{pc + i * 4:08x}', **row)
                                                      for i, row in enumerate(rows)])
            for i, row in enumerate(rows):
                address = pc + i * 4; word = encode(row, address)
                self.assertEqual(a.decode_selected(word, address), row)
                for bit in range(32):
                    mutations += 1; changed = word ^ 1 << bit
                    try: decoded = a.decode_selected(changed, address)
                    except a.c.FormatError: continue
                    if decoded is not None:
                        self.assertNotEqual(decoded, row, (hex(address), bit))
                        self.assertEqual(encode(decoded, address), changed, (hex(address), bit))
        self.assertEqual(mutations, 4768)

    def test_exact_reads_and4768_payload_bit_refusals_before_decode(self):
        mutations = 0
        for (pc, width, _), call in zip(RANGES, EXPECTED_READS):
            body = BODIES[pc]; db = FakeDB(body)
            report = a.range_evidence(db, TEXT_MAPPING, pc, width)
            self.assertEqual(db.calls, [call]); self.assertEqual(report['width'], width)
            with patch.object(a, 'decode_selected') as decoder:
                for i in range(width):
                    for bit in range(8):
                        changed = body[:i] + bytes([body[i] ^ 1 << bit]) + body[i + 1:]
                        with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                            a.range_evidence(FakeDB(changed), TEXT_MAPPING, pc, width)
                        mutations += 1
                decoder.assert_not_called()
        self.assertEqual(mutations, 4768)

    def test_all33_control_flow_rows_and_indirect_calls(self):
        counts = []
        for pc, width, _ in RANGES:
            rows = [dict(address=f'{site:08x}', **row) for site, row in at(pc).items()
                    if row['mnemonic'] in ('b', 'bc', 'bl', 'blr', 'bctrl')]
            self.assertEqual(a.expected_flow(pc), rows)
            self.assertEqual(rows[-1], dict(address=f'{pc + width - 4:08x}',
                                           mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
            self.assertTrue(all(pc <= int(row['target'], 16) < pc + width
                                for row in rows if row['mnemonic'] in ('b', 'bc')))
            counts.append(len(rows))
        self.assertEqual(counts, [12, 13, 8])
        self.assertEqual([pc for entry in EXPECTED for pc, row in at(entry).items()
                          if row['mnemonic'] == 'bctrl'], [0x80089944, 0x80089a50])

    def test_both_exact_snapshot_callback_postfield_and_live_next_order(self):
        for entry, site, obj, zero, nextpc in ((0x80089898, 0x80089910, 30, 31, '80089958'),
                                             (0x8008997c, 0x80089a1c, 27, 28, '80089a64')):
            rows = at(entry)
            self.assertEqual([rows[pc] for pc in range(site, site + 19 * 4, 4)], ops(f'''
lwz 4 {obj} 0x20
or {obj} 3 {obj} 0
lwz 0 {obj} 0x24
stw 4 {obj} 0x2c
stw 0 {obj} 0x30
lwz 0 {obj} 0x28
stw 0 {obj} 0x34
lwz 0 {obj} 0x70
stw 0 {obj} 0x76
lhz 0 {obj} 0x74
sth 0 {obj} 0x7a
lwz 12 {obj} 0xc
mtctr 12
bctrl 20 0 0 1
lbz 0 {obj} 0x86
extsb 0 0 1
bc 12 2 {nextpc} 0 0
stb {zero} {obj} 0x1ca
lwz {obj} {obj} 8
'''))
            self.assertEqual([rows[pc] for pc in range(site - 12, site, 4)],
                             ops(f'lbz 0 {obj} 0\nextsb 0 0 1\nbc 12 2 {nextpc} 0 0'))
            self.assertEqual([row for row in rows.values() if row['mnemonic'] == 'lwz'
                              and row['rA'] == obj and row['displacement'] == 8],
                             ops(f'lwz {obj} {obj} 8'))
            self.assertIn(ops(f'addi {zero} 0 0')[0], list(rows.values()))

    def test_signed_pause_gates_owner_pointer_and_independent_eligibility_owner(self):
        single, batch = at(0x80089898), at(0x8008997c)
        self.assertEqual(single[0x800898a0], ops('cmpi 0 0 3 56')[0])
        self.assertEqual(single[0x800898b4], ops('rlwinm 3 0 0 29 31 0')[0])
        self.assertEqual(single[0x800898b8], ops('cmpi 0 0 0 7')[0])
        self.assertEqual(single[0x800898c0], ops('cmpi 0 0 3 8')[0])
        for site, offset in ((0x800898c8, 0xd2), (0x800898dc, 0xd1)):
            self.assertEqual([single[pc] for pc in range(site, site + 12, 4)],
                ops(f'lwz 4 13 -31852\nlbz 0 4 {offset}\nrlwinm 0 0 0 24 24 1'))
        self.assertEqual(batch[0x80089990], ops('cmpi 0 0 29 56')[0])
        self.assertEqual([batch[pc] for pc in range(0x80089998, 0x800899b4, 4)], ops('''
addis 3 0 -32708
addi 30 0 0
addi 31 3 0x4e84
lwz 3 31 0
lbz 0 3 0
extsb 0 0 1
bc 12 2 80089a70 0 0
'''))
        for site, offset in ((0x800899bc, 0xd2), (0x800899d8, 0xd1)):
            self.assertEqual([batch[pc] for pc in range(site, site + 24, 4)],
                ops(f'lwz 3 13 -31852\naddi 0 0 1\nslw 0 0 30 0\nlbz 3 3 {offset}\nand 3 0 0 1\nbc 4 2 80089a70 0 0'))
        self.assertEqual([batch[pc] for pc in range(0x800899f0, 0x80089a0c, 4)], ops('''
add 0 29 30 0
addis 3 0 -32708
rlwinm 0 4 2 0 29 0
addi 28 0 0
addi 0 3 0x706c
add 3 0 4 0
lwz 27 3 4
'''))
        self.assertEqual([batch[pc] for pc in range(0x80089a70, 0x80089a80, 4)],
                         ops('addi 30 30 1\naddi 31 31 4\ncmpi 0 0 30 6\nbc 12 0 800899a4 0 0'))

    def test_wrapper_group_selection_order_and_preserved_base(self):
        rows = at(0x80089a94)
        self.assertEqual([rows[pc] for pc in range(0x80089aa4, 0x80089ad8, 4)], ops('''
or 3 31 3 0
cmpi 0 0 31 56
bc 4 0 80089ab8 0 0
rlwinm 31 0 0 29 31 1
bc 12 2 80089ac4 0 0
or 31 3 31 0
bl 80089898 0 1
b 80089ad8 0 0
bl 8008997c 0 1
or 31 3 31 0
bl 80089898 0 1
addi 3 31 7
bl 80089898 0 1
'''))

    def test_addresses_widths_duplicate_ranges_and_exact_typed_maps_refuse(self):
        for pc, width, _ in RANGES:
            for bad in (pc - 1, pc + 1, pc - 4, pc + 4, float(pc), True, -1, 1 << 32):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, bad, width)
                self.assertFalse(db.calls)
            for bad in (0, width - 4, width + 4, -width, True, float(width)):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, bad)
                self.assertFalse(db.calls)
            for index, value in enumerate(TEXT_MAPPING):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    changed = list(TEXT_MAPPING); changed[index] = replacement; db = FakeDB(BODIES[pc])
                    with self.assertRaises(a.c.FormatError): a.range_evidence(db, tuple(changed), pc, width)
                    self.assertFalse(db.calls)
            with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(BODIES[pc]), list(TEXT_MAPPING), pc, width)
            with patch.object(a, 'RANGES', RANGES * 2):
                db = FakeDB(BODIES[pc])
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, width)
                self.assertFalse(db.calls)
            for raw in (BODIES[pc][:-1], BODIES[pc] + b'\0'):
                with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                    a.range_evidence(FakeDB(raw), TEXT_MAPPING, pc, width)
        for pc in (0x80089814, 0x80089aec, 0x803c706c, 0x803c4e84, 0x80433934):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_decoder_bounds_reserved_bits_and_all_control_metadata_mutations(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x48000003, 0x94000000, 0x7c0802a7,
                     0x41820003, 46 << 26 | 27 << 21 | 28 << 16):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x80089898)
        original = a.decode_selected; mutations = 0
        for pc, width, _ in RANGES:
            with patch.object(a, 'decode_selected', return_value=None):
                with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                    a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
            for site, expected in at(pc).items():
                if expected['mnemonic'] not in ('bc', 'b', 'bl', 'blr', 'bctrl'): continue
                for field, value in expected.items():
                    replacement = 'addi' if field == 'mnemonic' else '80000000' if field == 'target' else value ^ 1
                    def changed(word, address):
                        row = original(word, address)
                        return dict(row, **{field: replacement}) if address == site else row
                    with patch.object(a, 'decode_selected', changed):
                        with self.assertRaisesRegex(a.c.FormatError, 'complete control-flow mismatch'):
                            a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
                    mutations += 1
        self.assertEqual(mutations, 175)

    def test_authentication_precedes_parser_and_selections(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad'); db.assert_not_called(); code.assert_not_called()

    def test_mapping_refusal_precedes_all_selections(self):
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
        for bb, ss, image in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': image}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called()

    def test_no_arbitrary_cli_and_missing_snapshot(self):
        for option in ('--address', '--width', '--pointer', '--target', '--dump'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/scheduler.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
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

    def test_both_snapshots_operands_complete_coverage_and_ceiling(self):
        for key in ('mappings', 'ranges', 'function_coverage', 'selection_basis', 'reused_evidence'):
            self.assertEqual(self.reports[0][key], self.reports[1][key], key)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            for row in report['ranges']:
                pc = int(row['address'], 16)
                self.assertEqual(row['instructions'], [dict(address=f'{pc + i * 4:08x}', **op)
                                                       for i, op in enumerate(EXPECTED[pc])])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (3, 596, 0))
            for key in ('pointer_following', 'reused_helpers_read', 'global_payloads_read',
                        'callback_bodies_read', 'pause_owner_runtime_value_established'):
                self.assertFalse(basis[key])
            self.assertIn('not original-DOL identity', report['caveat'])
            self.assertEqual(sum(row['represented_instructions'] for row in report['function_coverage']), 149)
            for row in report['function_coverage']:
                self.assertEqual(row['unrepresented_instructions'], 0); self.assertEqual(row['unrepresented_ranges'], [])
                self.assertEqual(row['selected_width'], row['map_size'])

    def test_exact_three_reads_after_full_unchanged_authentication(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(auth); self.assertTrue(all(row[0] == 263 for row in auth))

    def test_physical_spans_and_no_raw_output(self):
        expected = {0x80089898: (541368, 894, 228, 918404),
                    0x8008997c: (541596, 1122, 280, 918632),
                    0x80089a94: (541876, 1402, 88, 918912)}
        for report in self.reports:
            for row in report['ranges']:
                offset, data_offset, width, physical = expected[int(row['address'], 16)]
                self.assertEqual(row['spans'], [dict(root_buffer=21, data_buffer=55, chain_offset=offset,
                    data_offset=data_offset, length=width, obfuscated=True, physical_offset=physical)])
                self.assertEqual(row['end_exclusive'], f'{int(row["address"], 16) + width:08x}')
                self.assertEqual(set(row), {'address', 'end_exclusive', 'width', 'sha256', 'spans', 'instructions'})
                self.assertFalse(any('word' in item for item in row['instructions']))

    def test_real_snapshot_hash_schema_and_each_payload_refuse_before_selection_or_decode(self):
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
        for selected_call in EXPECTED_READS:
            def tampered(db, *args):
                payload, spans = original(db, *args)
                if args == selected_call: payload = bytes([payload[0] ^ 1]) + payload[1:]
                return payload, spans
            with patch.object(a.c.GBF, 'chain', tampered):
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'): a.inspect(raw, digest)


if __name__ == '__main__':
    unittest.main()
