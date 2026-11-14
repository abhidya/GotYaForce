#!/usr/bin/env python3
"""Independent semantic operands/inverse:270 instructions,1080 bytes,5 reads.

Literal fixtures below are manually authored, never loaded from reader/report/
archive output by tests. Existing private snapshots optional; never fetched.
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

import read_archived_outer_frame_evidence as a

TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
RANGES = (
    (0x80029434, 320, '6b951fb1955f3acb931beff0831af002d9b6ff9b108a15796a3114b5020b1b6c'),
    (0x8008b048, 68, 'f301aa22755c8f9c590db04552e1461969fbdb7f0df11c62b225eed6b77c264d'),
    (0x8008b010, 40, '979ef724f8f7c5c40352c666b8676668553d3f5333961b61443f2eafbb5b7b8e'),
    (0x80029d48, 336, 'cafbf7ba2143ecf749bfec6a51d4d7525da518e34836b42c07e591009d47feb0'),
    (0x80029e98, 316, 'b6a32d4c3b5911b5974991cf21f060fc128e48d8116cabb0c96f146cdaeae450'),
)
FIELDS = {
    'stwu': 'rS rA displacement', 'stw': 'rS rA displacement', 'stb': 'rS rA displacement',
    'sth': 'rS rA displacement', 'lwz': 'rD rA displacement', 'lbz': 'rD rA displacement',
    'lhz': 'rD rA displacement', 'lha': 'rD rA displacement',
    'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'xoris': 'rS rA immediate',
    'or': 'rS rA rB Rc', 'and': 'rS rA rB Rc', 'slw': 'rS rA rB Rc',
    'add': 'rD rA rB Rc', 'extsb': 'rS rA Rc', 'extsh': 'rS rA Rc',
    'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS', 'lbzx': 'rD rA rB', 'stbx': 'rS rA rB',
    'bl': 'target AA LK', 'b': 'target AA LK', 'bc': 'BO BI target AA LK',
    'blr': 'BO BI BH LK', 'bclr': 'BO BI BH LK',
    'rlwinm': 'rS rA SH MB ME Rc', 'cmpi': 'BF L rA immediate', 'cmpli': 'BF L rA immediate',
    'cmp': 'BF L rA rB', 'cmpl': 'BF L rA rB',
    'lfd': 'fD rA displacement', 'stfd': 'fS rA displacement',
    'fsubs': 'fD fA fB', 'fdivs': 'fD fA fB', 'fmuls': 'fD fA fC', 'fctiwz': 'fD fB',
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
    0x80029434: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
bl 8008b048 0 1
bl 80029d48 0 1
lwz 3 13 -31852
lbz 0 3 0x66
extsb 0 0 1
bc 4 2 80029464 0 0
bl 80053b30 0 1
bl 8006ae60 0 1
bl 80027764 0 1
bl 8000bef4 0 1
lwz 3 13 -31852
lbz 0 3 0x66
extsb 0 0 1
bc 4 2 800294b8 0 0
addi 3 0 0x28
bl 80089a94 0 1
addi 3 0 0x20
bl 80089a94 0 1
bl 80053a2c 0 1
bl 80087cf0 0 1
addi 3 0 0
bl 80089a94 0 1
addi 3 0 0x10
bl 80089a94 0 1
addi 3 0 8
bl 80089a94 0 1
addi 3 0 0x18
bl 80089a94 0 1
addi 3 0 0x38
bl 80089898 0 1
addi 3 0 0x3a
bl 80089898 0 1
addi 3 0 0x39
bl 80089898 0 1
bl 80089554 0 1
lwz 4 13 -31852
lwz 3 4 0xb0
addi 0 3 1
stw 0 4 0xb0
lwz 3 13 -31852
lbz 0 3 0x66
extsb 0 0 1
bc 4 2 800294f8 0 0
bl 8008a28c 0 1
bl 80089aec 0 1
bl 8002bb14 0 1
bl 80036e24 0 1
bl 8008972c 0 1
bl 80089658 0 1
lwz 3 13 -31852
lbz 0 3 0x66
extsb 0 0 1
bc 4 2 80029520 0 0
bl 80053a94 0 1
addi 3 0 0x3b
bl 80089898 0 1
lwz 3 13 -31852
lbz 0 3 0x66
cmpi 0 0 0 1
bc 12 2 80029534 0 0
bl 8000bda4 0 1
lwz 3 13 -31852
lbz 0 3 0x66
cmpi 0 0 0 1
bc 12 2 80029548 0 0
bl 80040b94 0 1
bl 800eff30 0 1
lwz 3 13 -31852
lbz 0 3 0xd1
stb 0 3 0xd3
lwz 3 13 -31852
lbz 0 3 0xd2
stb 0 3 0xd4
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x8008b048: ops('''
stwu 1 1 -16
mflr 0
stw 0 1 20
lwz 3 13 -31852
lbz 3 3 0x15d4
extsb 3 0 1
bc 12 2 8008b070 0 0
extsb 3 3 0
addi 3 3 -1
bl 8008b010 0 1
lwz 3 13 -31852
addi 0 0 0
stb 0 3 0x15d4
lwz 0 1 20
mtlr 0
addi 1 1 16
blr 20 0 0 0
'''),
    0x8008b010: ops('''
lwz 4 13 -31852
cmpi 0 0 3 2
stb 3 4 0x66
bclr 4 0 0 0
cmpi 0 0 3 0
bclr 12 0 0 0
lwz 3 13 -31852
addi 0 0 0
sth 0 3 0xd6
blr 20 0 0 0
'''),
    0x80029d48: ops('''
stwu 1 1 -48
mflr 0
stw 0 1 52
stw 31 1 44
stw 30 1 40
addi 30 0 0
lwz 3 13 -31852
addi 31 3 0xf4
or 31 3 31 0
bl 80029e98 0 1
lbz 0 31 1
extsb 0 0 1
bc 4 1 80029e70 0 0
lbz 0 31 0x10
extsb 0 0 1
bc 12 2 80029e4c 0 0
addi 0 0 0
stb 0 31 0xf
bl 8008b290 0 1
cmpi 0 0 3 0
bc 4 2 80029e70 0 0
bl 8008b480 0 1
cmpi 0 0 3 0
bc 12 2 80029db8 0 0
lbz 0 31 3
extsb 0 0 0
and 3 0 0 1
bc 12 2 80029e70 0 0
lha 3 31 0x18
addi 3 3 -1
extsh 3 0 1
sth 3 31 0x18
bc 12 1 80029de0 0 0
addi 0 0 0
sth 0 31 0x32
stb 0 31 0x10
sth 0 31 0x32
b 80029e70 0 0
lha 3 31 0x18
addis 4 0 0x4330
lha 0 31 0x1a
xoris 3 3 0x8000
lhz 5 31 0x30
xoris 0 0 0x8000
stw 3 1 20
lfd 2 2 -31512
stw 4 1 16
lfd 3 2 -31520
lfd 0 1 16
stw 0 1 28
fsubs 1 0 2
stw 4 1 24
lfd 0 1 24
stw 5 1 12
fsubs 0 0 2
stw 4 1 8
fdivs 0 1 0
lfd 1 1 8
fsubs 1 1 3
fmuls 0 1 0
fctiwz 0 0
stfd 0 1 32
lwz 0 1 36
sth 0 31 0x32
b 80029e70 0 0
lhz 3 31 0x32
lhz 0 31 0x30
cmpl 0 0 3 0
bc 12 0 80029e68 0 0
addi 0 0 1
stb 0 31 0xf
b 80029e70 0 0
addi 0 0 0
stb 0 31 0xf
addi 30 30 1
addi 31 31 0x3c
cmpi 0 0 30 4
bc 12 0 80029d68 0 0
lwz 0 1 52
lwz 31 1 44
lwz 30 1 40
mtlr 0
addi 1 1 48
blr 20 0 0 0
'''),
    0x80029e98: ops('''
addi 5 0 0
addi 4 0 -1
stb 5 3 1
addi 0 0 3
addi 7 0 0
addi 6 0 0
stb 5 3 2
stb 5 3 3
stb 4 3 4
stb 4 3 5
stb 4 3 6
stb 4 3 7
stb 4 3 8
stb 4 3 9
mtctr 0
lwz 5 13 -31852
addi 4 0 1
slw 4 8 6 0
lbz 0 5 0x15d9
and 0 0 8 1
bc 12 2 80029f4c 0 0
addi 4 6 0xcb
lbz 0 3 0
lbzx 4 5 4
extsb 0 0 0
extsb 4 4 0
cmp 0 0 4 0
bc 4 2 80029f4c 0 0
lbz 4 3 1
addi 0 4 1
stb 0 3 1
lwz 4 13 -31856
lbz 0 4 2
extsb 0 0 0
and 0 0 8 1
bc 12 2 80029f34 0 0
lbz 4 3 2
addi 0 4 1
stb 0 3 2
lbz 4 3 3
addi 0 7 4
addi 7 7 1
or 4 4 8 0
stb 4 3 3
stbx 6 3 0
lwz 5 13 -31852
addi 4 0 1
addi 6 6 1
lbz 0 5 0x15d9
slw 4 8 6 0
and 0 0 8 1
bc 12 2 80029fc8 0 0
addi 4 6 0xcb
lbz 0 3 0
lbzx 4 5 4
extsb 0 0 0
extsb 4 4 0
cmp 0 0 4 0
bc 4 2 80029fc8 0 0
lbz 4 3 1
addi 0 4 1
stb 0 3 1
lwz 4 13 -31856
lbz 0 4 2
extsb 0 0 0
and 0 0 8 1
bc 12 2 80029fb0 0 0
lbz 4 3 2
addi 0 4 1
stb 0 3 2
lbz 4 3 3
addi 0 7 4
addi 7 7 1
or 4 4 8 0
stb 4 3 3
stbx 6 3 0
addi 6 6 1
bc 16 0 80029ed4 0 0
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
             'lhz': (40, 'rD', 'displacement'), 'lha': (42, 'rD', 'displacement'),
             'lfd': (50, 'fD', 'displacement'), 'stfd': (54, 'fS', 'displacement'),
             'xoris': (27, 'rS', 'immediate'), 'addi': (14, 'rD', 'immediate'),
             'addis': (15, 'rD', 'immediate')}
    if name in forms:
        opcode, reg, imm = forms[name]
        return opcode << 26 | row[reg] << 21 | row['rA'] << 16 | row[imm] & 65535
    if name in ('mflr', 'mtlr', 'mtctr'):
        return (31 << 26 | row['rD' if name == 'mflr' else 'rS'] << 21 |
                (9 if name == 'mtctr' else 8) << 16 | (339 if name == 'mflr' else 467) << 1)
    if name in ('or', 'and', 'slw', 'add', 'lwzx', 'lbzx', 'stbx'):
        xo, reg = {'or': (444, 'rS'), 'and': (28, 'rS'), 'slw': (24, 'rS'),
                   'add': (266, 'rD'), 'lwzx': (23, 'rD'), 'lbzx': (87, 'rD'), 'stbx': (215, 'rS')}[name]
        return (31 << 26 | row[reg] << 21 | row['rA'] << 16 | row['rB'] << 11 |
                xo << 1 | row.get('Rc', 0))
    if name in ('extsb', 'extsh'):
        return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | (954 if name == 'extsb' else 922) << 1 | row['Rc']
    if name in ('bl', 'b', 'bc'):
        displacement = int(row['target'], 16) - (0 if row['AA'] else pc)
        if name == 'bc':
            return (16 << 26 | row['BO'] << 21 | row['BI'] << 16 | displacement & 0xfffc |
                    row['AA'] << 1 | row['LK'])
        return 18 << 26 | displacement & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name in ('blr', 'bclr'):
        return (19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 |
                16 << 1 | row['LK'])
    if name == 'rlwinm':
        return (21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 |
                row['MB'] << 6 | row['ME'] << 1 | row['Rc'])
    if name in ('cmpi', 'cmpli'):
        return ((11 if name == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 |
                row['rA'] << 16 | row['immediate'] & 65535)
    if name in ('cmp', 'cmpl'):
        return (31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 |
                row['rB'] << 11 | (32 if name == 'cmpl' else 0) << 1)
    if name in ('fsubs', 'fdivs', 'fmuls'):
        return (59 << 26 | row['fD'] << 21 | row['fA'] << 16 |
                (row['fC'] << 6 if name == 'fmuls' else row['fB'] << 11) |
                {'fsubs': 20, 'fdivs': 18, 'fmuls': 25}[name] << 1)
    if name == 'fctiwz':
        return 63 << 26 | row['fD'] << 21 | row['fB'] << 11 | 15 << 1
    raise AssertionError(name)


BODIES = {pc: b''.join(struct.pack('>I', encode(row, pc + i * 4)) for i, row in enumerate(rows))
          for pc, rows in EXPECTED.items()}
EXPECTED_READS = [(21, 147028, 320, 2796416), (21, 547432, 68, 2796416),
                  (21, 547376, 40, 2796416), (21, 149352, 336, 2796416),
                  (21, 149688, 316, 2796416)]


def at(entry):
    return {entry + i * 4: row for i, row in enumerate(EXPECTED[entry])}


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_independent_extents_and_reused_scheduler(self):
        self.assertEqual(a.RANGES, RANGES); self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(sum(map(len, BODIES.values())), 1080)
        self.assertEqual([len(rows) for rows in EXPECTED.values()], [80, 17, 10, 84, 79])
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text()
        for pc, width, _ in RANGES:
            chunk = 'chunk_0013.c' if pc in (0x8008b048, 0x8008b010) else 'chunk_0003.c'
            source = (root / 'research/decomp/ghidra-export' / chunk).read_text()
            start = index.index(f'{pc:08x}\tzz_{pc - 0x80000000:07x}_\t{chunk}')
            self.assertTrue(index[start + 1].startswith(f'{pc + width:08x}\t'))
            body, suffix = source.split(f'// ==== {pc:08x} ', 1)[1].split('// ==== ', 1)
            self.assertTrue(suffix.startswith(f'{pc + width:08x} '))
            self.assertRegex(symbols, rf'(?m)^{pc:08x} {width:08x} {pc:08x} 0 ')
            self.assertTrue(body.strip())
        import read_archived_object_scheduler_evidence as scheduler
        available = {pc: (width, digest) for pc, width, digest in scheduler.RANGES}
        self.assertEqual([row['address'] for row in a.REUSED_EVIDENCE], ['80089898', '80089a94'])
        for row in a.REUSED_EVIDENCE:
            self.assertEqual((row['width'], row['sha256']), available[int(row['address'], 16)])
            self.assertIs(row['read_here'], False)

    def test_all270_operands_independent_inverse_hash_and8640_bit_controls(self):
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
        self.assertEqual(mutations, 8640)

    def test_exact_reads_and8640_payload_bit_refusals_before_decode(self):
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
        self.assertEqual(mutations, 8640)

    def test_all65_control_flow_rows_and_no_indirect_calls(self):
        counts = []
        for pc, width, _ in RANGES:
            rows = [dict(address=f'{site:08x}', **row) for site, row in at(pc).items()
                    if row['mnemonic'] in ('b', 'bc', 'bl', 'blr', 'bclr')]
            self.assertEqual(a.expected_flow(pc), rows)
            self.assertEqual(rows[-1], dict(address=f'{pc + width - 4:08x}',
                                           mnemonic='blr', BO=20, BI=0, BH=0, LK=0))
            self.assertTrue(all(pc <= int(row['target'], 16) < pc + width
                                for row in rows if row['mnemonic'] in ('b', 'bc')))
            counts.append(len(rows))
        self.assertEqual(counts, [36, 3, 3, 15, 8])
        self.assertFalse(any(row['mnemonic'] == 'bctrl' for rows in EXPECTED.values() for row in rows))

    def test_request_signed_argument_store_before_bounds_and_reloads(self):
        request, setter = at(0x8008b048), at(0x8008b010)
        self.assertEqual([request[pc] for pc in range(0x8008b054, 0x8008b07c, 4)], ops("""
lwz 3 13 -31852
lbz 3 3 0x15d4
extsb 3 0 1
bc 12 2 8008b070 0 0
extsb 3 3 0
addi 3 3 -1
bl 8008b010 0 1
lwz 3 13 -31852
addi 0 0 0
stb 0 3 0x15d4
"""))
        self.assertEqual(list(setter.values()), ops("""
lwz 4 13 -31852
cmpi 0 0 3 2
stb 3 4 0x66
bclr 4 0 0 0
cmpi 0 0 3 0
bclr 12 0 0 0
lwz 3 13 -31852
addi 0 0 0
sth 0 3 0xd6
blr 20 0 0 0
"""))

    def test_refresh_captured_team_pointer_signed_gate_first_refusal_and_unsigned_charge(self):
        rows = at(0x80029d48)
        self.assertEqual([rows[pc] for pc in range(0x80029d60, 0x80029d94, 4)], ops("""
lwz 3 13 -31852
addi 31 3 0xf4
or 31 3 31 0
bl 80029e98 0 1
lbz 0 31 1
extsb 0 0 1
bc 4 1 80029e70 0 0
lbz 0 31 0x10
extsb 0 0 1
bc 12 2 80029e4c 0 0
addi 0 0 0
stb 0 31 0xf
bl 8008b290 0 1
"""))
        self.assertEqual([rows[pc] for pc in range(0x80029e4c, 0x80029e80, 4)], ops("""
lhz 3 31 0x32
lhz 0 31 0x30
cmpl 0 0 3 0
bc 12 0 80029e68 0 0
addi 0 0 1
stb 0 31 0xf
b 80029e70 0 0
addi 0 0 0
stb 0 31 0xf
addi 30 30 1
addi 31 31 0x3c
cmpi 0 0 30 4
bc 12 0 80029d68 0 0
"""))
        self.assertEqual([site for site, row in rows.items() if row['mnemonic'] == 'lwz'
                          and row['rA'] == 13], [0x80029d60])
        # Even inaccessible burst suffix is decoded exactly; neither constants nor
        # helpers are admitted just because their instruction operands appear here.
        self.assertEqual([rows[pc] for pc in range(0x80029dcc, 0x80029ddc, 4)],
                         ops('addi 0 0 0\nsth 0 31 0x32\nstb 0 31 0x10\nsth 0 31 0x32'))
        self.assertEqual([(row['fD'], row['rA'], row['displacement']) for row in rows.values()
                          if row['mnemonic'] == 'lfd' and row['rA'] == 2],
                         [(2, 2, -31512), (3, 2, -31520)])

    def test_team_refresh_live_mask_loads_signed_ids_and_exact_store_order(self):
        rows = at(0x80029e98)
        stores = [row['displacement'] for pc, row in rows.items() if pc < 0x80029ed0
                  and row['mnemonic'] == 'stb']
        self.assertEqual(stores, list(range(1, 10)))
        self.assertEqual(rows[0x80029ea4], ops('addi 0 0 3')[0])
        self.assertEqual(rows[0x80029ed0], ops('mtctr 0')[0])
        self.assertEqual(rows[0x80029fcc], ops('bc 16 0 80029ed4 0 0')[0])
        for base, skip, inactive in ((0x80029eec, '80029f4c', '80029f34'),
                                     (0x80029f68, '80029fc8', '80029fb0')):
            self.assertEqual([rows[pc] for pc in range(base, base + 96, 4)], ops(f"""
addi 4 6 0xcb
lbz 0 3 0
lbzx 4 5 4
extsb 0 0 0
extsb 4 4 0
cmp 0 0 4 0
bc 4 2 {skip} 0 0
lbz 4 3 1
addi 0 4 1
stb 0 3 1
lwz 4 13 -31856
lbz 0 4 2
extsb 0 0 0
and 0 0 8 1
bc 12 2 {inactive} 0 0
lbz 4 3 2
addi 0 4 1
stb 0 3 2
lbz 4 3 3
addi 0 7 4
addi 7 7 1
or 4 4 8 0
stb 4 3 3
stbx 6 3 0
"""))
        self.assertEqual([rows[pc] for pc in range(0x80029ed4, 0x80029eec, 4)], ops("""
lwz 5 13 -31852
addi 4 0 1
slw 4 8 6 0
lbz 0 5 0x15d9
and 0 0 8 1
bc 12 2 80029f4c 0 0
"""))
        self.assertEqual([rows[pc] for pc in range(0x80029f4c, 0x80029f68, 4)], ops("""
lwz 5 13 -31852
addi 4 0 1
addi 6 6 1
lbz 0 5 0x15d9
slw 4 8 6 0
and 0 0 8 1
bc 12 2 80029fc8 0 0
"""))

    def test_outer_first_boundaries_schedule_order_and_final_masks(self):
        rows = at(0x80029434)
        self.assertEqual([rows[pc] for pc in range(0x80029440, 0x80029468, 4)], ops("""
bl 8008b048 0 1
bl 80029d48 0 1
lwz 3 13 -31852
lbz 0 3 0x66
extsb 0 0 1
bc 4 2 80029464 0 0
bl 80053b30 0 1
bl 8006ae60 0 1
bl 80027764 0 1
bl 8000bef4 0 1
"""))
        scheduled = [(pc, rows[pc - 4]['immediate'], row['target']) for pc, row in rows.items()
                     if row['mnemonic'] == 'bl' and row['target'] in ('80089a94', '80089898')]
        self.assertEqual([(group, target) for _, group, target in scheduled],
                         [(40, '80089a94'), (32, '80089a94'), (0, '80089a94'),
                          (16, '80089a94'), (8, '80089a94'), (24, '80089a94'),
                          (56, '80089898'), (58, '80089898'), (57, '80089898'),
                          (59, '80089898')])
        self.assertEqual([rows[pc] for pc in range(0x8002954c, 0x80029564, 4)],
                         ops('lwz 3 13 -31852\nlbz 0 3 0xd1\nstb 0 3 0xd3\n'
                             'lwz 3 13 -31852\nlbz 0 3 0xd2\nstb 0 3 0xd4'))

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
        for pc in (0x80029574, 0x80029fd4, 0x8008b290, 0x8008b480, 0x80433934, 0x80433930, 0x80436f00):
            db = FakeDB(b'')
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, TEXT_MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_decoder_bounds_reserved_bits_and_all_control_metadata_mutations(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in (0x4e800021, 0x4e800420, 0x4e800820, 0x48000003, 0x94000000, 0x7c0802a7,
                     0x41820003, 0x4c000020, 0x4e808020):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, 0x80089898)
        original = a.decode_selected; mutations = 0
        for pc, width, _ in RANGES:
            with patch.object(a, 'decode_selected', return_value=None):
                with self.assertRaisesRegex(a.c.FormatError, 'unselected instruction'):
                    a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
            for site, expected in at(pc).items():
                if expected['mnemonic'] not in ('bc', 'b', 'bl', 'blr', 'bclr'): continue
                for field, value in expected.items():
                    replacement = 'addi' if field == 'mnemonic' else '80000000' if field == 'target' else value ^ 1
                    def changed(word, address):
                        row = original(word, address)
                        return dict(row, **{field: replacement}) if address == site else row
                    with patch.object(a, 'decode_selected', changed):
                        with self.assertRaisesRegex(a.c.FormatError, 'complete control-flow mismatch'):
                            a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
                    mutations += 1
        self.assertEqual(mutations, 311)

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
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (5, 1080, 0))
            for key in ('pointer_following', 'reused_helpers_read', 'global_payloads_read',
                        'callback_bodies_read', 'owner_runtime_value_established'):
                self.assertFalse(basis[key])
            self.assertIn('not original-DOL identity', report['caveat'])
            self.assertEqual(sum(row['represented_instructions'] for row in report['function_coverage']), 270)
            for row in report['function_coverage']:
                self.assertEqual(row['unrepresented_instructions'], 0); self.assertEqual(row['unrepresented_ranges'], [])
                self.assertEqual(row['selected_width'], row['map_size'])

    def test_exact_five_reads_after_full_unchanged_authentication(self):
        for reads, auth in zip(self.reads, self.auth_reads):
            self.assertEqual(reads, auth + EXPECTED_READS)
            self.assertTrue(auth); self.assertTrue(all(row[0] == 263 for row in auth))

    def test_physical_spans_and_no_raw_output(self):
        expected = {0x80029434: (30, 147028, 16004, 320, 523914),
                    0x8008b048: (55, 547432, 6958, 68, 924468),
                    0x8008b010: (55, 547376, 6902, 40, 924412),
                    0x80029d48: (31, 149352, 1950, 336, 526244),
                    0x80029e98: (31, 149688, 2286, 316, 526580)}
        for report in self.reports:
            for row in report['ranges']:
                buffer, offset, data_offset, width, physical = expected[int(row['address'], 16)]
                self.assertEqual(row['spans'], [dict(root_buffer=21, data_buffer=buffer, chain_offset=offset,
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
