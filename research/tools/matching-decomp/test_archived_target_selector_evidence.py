#!/usr/bin/env python3
"""Independent literal operand fixture/inverse for 273 instructions / 1092 bytes.

No fixture generation at test runtime, no original execution, no estimator or
runtime imports. Existing local snapshots are optional and never fetched.
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

import read_archived_target_selector_evidence as a

INVENTORY = (
    (0x8006b450, 932, 'cfc8c375b1bce3d53cbfe9f1d3283341bc7c8ca09ff463b1afaed3a838eca0a7'),
    (0x80010514, 160, '0064cd5dc8e78221bbe059631e699e5d62ce30994743b870fbf0f4ade60803da'),
)
TEXT_MAPPING = (0x800055e0, 0x802b0160, 1, 'MAIN_.text1', 1, 2796416, 21)
EXPECTED_READS = [(21, 417392, 932, 2796416), (21, 44852, 160, 2796416)]
# Literal operands transcribed from the bounded first inspection. These are
# independent of reader execution and output at test time. Inverse below places
# every represented field independently, including PSQ W/I/signed12 and bctr.
ASSEMBLY = '''
8006b450 stwu 1 1 -64
8006b454 mflr 0
8006b458 stw 0 1 68
8006b45c stfd 31 1 48
8006b460 psq_st 31 1 56 0 0
8006b464 stmw 27 1 28
8006b468 or 3 29 3 0
8006b46c lbz 3 3 996
8006b470 extsb 3 3 0
8006b474 bl 80010514
8006b478 cmpi 3 0
8006b47c bc 4 2 8006b7d8
8006b480 lbz 0 29 1855
8006b484 extsb 0 0 1
8006b488 bc 4 2 8006b7d8
8006b48c lbz 0 29 1852
8006b490 extsb 0 0 0
8006b494 cmpi 0 1
8006b498 bc 4 1 8006b7d8
8006b49c cmpi 0 4
8006b4a0 bc 12 2 8006b4f4
8006b4a4 bc 4 0 8006b4b8
8006b4a8 cmpi 0 2
8006b4ac bc 12 2 8006b4dc
8006b4b0 bc 4 0 8006b4e8
8006b4b4 b 8006b544
8006b4b8 cmpi 0 6
8006b4bc bc 4 0 8006b544
8006b4c0 lwz 0 29 1288
8006b4c4 addi 30 29 1854
8006b4c8 addi 31 0 0
8006b4cc stw 0 29 1760
8006b4d0 lwz 0 29 1284
8006b4d4 stw 0 29 1764
8006b4d8 b 8006b544
8006b4dc addi 30 29 1853
8006b4e0 addi 31 0 1
8006b4e4 b 8006b544
8006b4e8 addi 30 29 1853
8006b4ec addi 31 0 2
8006b4f0 b 8006b544
8006b4f4 lwz 3 29 1760
8006b4f8 addi 30 29 1853
8006b4fc addi 31 0 1
8006b500 cmpli 3 0
8006b504 bc 12 2 8006b544
8006b508 lbz 0 3 0
8006b50c extsb 0 0 1
8006b510 bc 12 2 8006b544
8006b514 lbz 0 3 24
8006b518 cmpi 0 1
8006b51c bc 4 2 8006b544
8006b520 lbz 0 3 131
8006b524 extsb 0 0 1
8006b528 bc 4 2 8006b544
8006b52c stw 3 29 1288
8006b530 addi 3 0 2
8006b534 addi 0 0 0
8006b538 stb 3 29 1282
8006b53c stb 0 29 1852
8006b540 b 8006b7d8
8006b544 lbz 5 30 0
8006b548 addi 0 0 0
8006b54c addis 3 0 -32708
8006b550 stb 0 29 1852
8006b554 addi 3 3 7548
8006b558 extsb 5 5 0
8006b55c lhz 4 13 -21342
8006b560 stw 0 13 -21504
8006b564 mtctr 4
8006b568 cmpi 4 0
8006b56c bc 4 1 8006b650
8006b570 lwz 4 3 0
8006b574 cmpli 4 0
8006b578 bc 12 2 8006b648
8006b57c lwz 6 4 40
8006b580 lhz 0 6 2
8006b584 rlwinm 0 0 0 22 22 1
8006b588 bc 12 2 8006b648
8006b58c lwz 7 4 32
8006b590 cmpli 7 0
8006b594 bc 12 2 8006b648
8006b598 lbz 0 7 0
8006b59c extsb 0 0 1
8006b5a0 bc 12 2 8006b648
8006b5a4 cmpl 29 7
8006b5a8 bc 12 2 8006b648
8006b5ac cmpi 31 0
8006b5b0 bc 12 2 8006b5d0
8006b5b4 lbz 6 29 136
8006b5b8 lbz 0 7 136
8006b5bc extsb 6 6 0
8006b5c0 extsb 0 0 0
8006b5c4 cmp 6 0
8006b5c8 bc 12 2 8006b648
8006b5cc b 8006b600
8006b5d0 lbz 6 29 136
8006b5d4 lbz 0 7 136
8006b5d8 extsb 6 6 0
8006b5dc extsb 0 0 0
8006b5e0 cmp 6 0
8006b5e4 bc 4 2 8006b648
8006b5e8 lbz 0 29 1184
8006b5ec extsb 0 0 1
8006b5f0 bc 12 2 8006b600
8006b5f4 lwz 0 29 1188
8006b5f8 cmpl 0 7
8006b5fc bc 12 2 8006b648
8006b600 lbz 0 7 136
8006b604 cmpi 0 4
8006b608 bc 12 2 8006b648
8006b60c lbz 0 7 24
8006b610 extsb 0 0 0
8006b614 cmpi 0 2
8006b618 bc 4 0 8006b648
8006b61c lwz 0 29 1284
8006b620 cmpl 0 4
8006b624 bc 4 2 8006b62c
8006b628 lwz 5 13 -21504
8006b62c lwz 8 13 -21504
8006b630 addis 6 0 -32709
8006b634 addi 6 6 8712
8006b638 addi 7 8 1
8006b63c rlwinm 8 0 2 0 29 0
8006b640 stw 7 13 -21504
8006b644 stwx 4 6 0
8006b648 addi 3 3 4
8006b64c bc 16 0 8006b570
8006b650 lwz 0 13 -21504
8006b654 cmpi 0 0
8006b658 bc 12 2 8006b7d8
8006b65c lwz 0 29 1284
8006b660 cmpli 0 0
8006b664 bc 12 2 8006b6dc
8006b668 cmpi 31 2
8006b66c bc 12 2 8006b68c
8006b670 bc 4 0 8006b690
8006b674 cmpi 31 0
8006b678 bc 4 0 8006b684
8006b67c b 8006b690
8006b680 b 8006b690
8006b684 addi 5 5 1
8006b688 b 8006b690
8006b68c addi 5 5 -1
8006b690 cmpi 5 0
8006b694 bc 4 0 8006b6a4
8006b698 lwz 3 13 -21504
8006b69c addi 5 3 -1
8006b6a0 b 8006b6b8
8006b6a4 lwz 3 13 -21504
8006b6a8 addi 0 3 -1
8006b6ac cmp 5 0
8006b6b0 bc 4 1 8006b6b8
8006b6b4 addi 5 0 0
8006b6b8 addis 3 0 -32709
8006b6bc rlwinm 5 0 2 0 29 0
8006b6c0 addi 3 3 8712
8006b6c4 lwzx 31 3 0
8006b6c8 stb 5 30 0
8006b6cc lwz 0 29 1284
8006b6d0 cmpl 0 31
8006b6d4 bc 4 2 8006b770
8006b6d8 b 8006b7d8
8006b6dc lwz 5 29 1200
8006b6e0 addis 3 0 -32709
8006b6e4 addi 4 3 8712
8006b6e8 addi 3 1 8
8006b6ec lbz 0 5 16
8006b6f0 lwz 4 4 0
8006b6f4 extsb 0 0 0
8006b6f8 mulli 0 0 48
8006b6fc or 4 31 4 0
8006b700 addi 4 4 100
8006b704 add 5 29 0 0
8006b708 lfs 0 5 2272
8006b70c stfs 0 1 8
8006b710 lfs 0 5 2288
8006b714 stfs 0 1 12
8006b718 lfs 0 5 2304
8006b71c stfs 0 1 16
8006b720 bl 8020bc88
8006b724 addis 3 0 -32709
8006b728 fmr 31 1
8006b72c addi 3 3 8712
8006b730 addi 28 0 1
8006b734 addi 30 3 4
8006b738 b 8006b764
8006b73c lwz 27 30 0
8006b740 addi 3 1 8
8006b744 addi 4 27 100
8006b748 bl 8020bc88
8006b74c fcmpo 1 31
8006b750 bc 12 1 8006b75c
8006b754 or 27 31 27 0
8006b758 fmr 31 1
8006b75c addi 30 30 4
8006b760 addi 28 28 1
8006b764 lwz 0 13 -21504
8006b768 cmp 28 0
8006b76c bc 12 0 8006b73c
8006b770 addi 7 0 1
8006b774 addis 3 0 -32708
8006b778 stb 7 29 1282
8006b77c addi 4 3 29616
8006b780 addi 3 0 3
8006b784 addi 0 0 0
8006b788 stw 31 29 1284
8006b78c lwz 5 31 32
8006b790 stw 5 29 1288
8006b794 lwz 6 31 100
8006b798 lwz 5 31 104
8006b79c stw 6 29 1292
8006b7a0 stw 5 29 1296
8006b7a4 lwz 5 31 108
8006b7a8 stw 5 29 1300
8006b7ac stb 7 29 1283
8006b7b0 stb 7 29 1852
8006b7b4 lbz 5 29 996
8006b7b8 extsb 5 5 0
8006b7bc stb 7 29 1009
8006b7c0 mulli 5 5 996
8006b7c4 add 4 4 5 0
8006b7c8 stb 3 4 742
8006b7cc stb 0 4 27
8006b7d0 stb 0 4 26
8006b7d4 stb 0 4 25
8006b7d8 psq_l 31 1 56 0 0
8006b7dc lfd 31 1 48
8006b7e0 lmw 27 1 28
8006b7e4 lwz 0 1 68
8006b7e8 mtlr 0
8006b7ec addi 1 1 64
8006b7f0 blr 20 0 0 0
80010514 mulli 0 3 996
80010518 addis 4 0 -32708
8001051c addi 5 0 0
80010520 addi 4 4 29616
80010524 add 4 4 0 0
80010528 lbz 0 4 24
8001052c cmpi 0 2
80010530 bc 4 2 80010538
80010534 oris 5 5 32768
80010538 addis 4 0 -32708
8001053c rlwinm 3 0 2 0 29 0
80010540 addi 3 4 20100
80010544 lwzx 3 3 0
80010548 lbz 0 3 1085
8001054c rlwinm 0 0 0 25 31 0
80010550 cmpli 0 9
80010554 bc 12 1 800105ac
80010558 addis 3 0 -32724
8001055c rlwinm 0 0 2 0 29 0
80010560 addi 3 3 14648
80010564 lwzx 0 3 0
80010568 mtctr 0
8001056c bctr 20 0 0 0
80010570 ori 5 5 1
80010574 b 800105ac
80010578 ori 5 5 2
8001057c b 800105ac
80010580 ori 5 5 4
80010584 b 800105ac
80010588 ori 5 5 8
8001058c b 800105ac
80010590 ori 5 5 16
80010594 b 800105ac
80010598 ori 5 5 32
8001059c b 800105ac
800105a0 ori 5 5 64
800105a4 b 800105ac
800105a8 ori 5 5 128
800105ac or 5 3 5 0
800105b0 blr 20 0 0 0
'''

D_FORMS = {'lwz': (32, 'rD'), 'lbz': (34, 'rD'), 'stw': (36, 'rS'), 'stwu': (37, 'rS'),
           'stb': (38, 'rS'), 'lhz': (40, 'rD'), 'lmw': (46, 'rD'), 'stmw': (47, 'rS'),
           'lfs': (48, 'fD'), 'lfd': (50, 'fD'), 'stfs': (52, 'fS'), 'stfd': (54, 'fS')}


def parse_fixture():
    result = []
    for line in ASSEMBLY.strip().splitlines():
        pc, name, *args = line.split()
        values = [int(arg) for arg in args] if name not in ('bc', 'b', 'bl') else []
        fields = {
            'mflr': 'rD', 'mtlr': 'rS', 'mtctr': 'rS',
            'addi': 'rD rA immediate', 'addis': 'rD rA immediate', 'mulli': 'rD rA immediate',
            'ori': 'rS rA immediate', 'oris': 'rS rA immediate', 'extsb': 'rS rA Rc',
            'or': 'rS rA rB Rc', 'add': 'rD rA rB Rc', 'rlwinm': 'rS rA SH MB ME Rc',
            'cmp': 'rA rB', 'cmpl': 'rA rB', 'cmpi': 'rA immediate', 'cmpli': 'rA immediate',
            'fcmpo': 'fA fB', 'fmr': 'fD fB', 'lwzx': 'rD rA rB', 'stwx': 'rS rA rB',
            'psq_st': 'fS rA displacement W I', 'psq_l': 'fD rA displacement W I',
            'blr': 'BO BI BH LK', 'bctr': 'BO BI BH LK',
        }
        if name in D_FORMS: fields[name] = D_FORMS[name][1] + ' rA displacement'
        row = dict(mnemonic=name)
        if name == 'bc': row.update(BO=int(args[0]), BI=int(args[1]), target=args[2], AA=0, LK=0)
        elif name in ('b', 'bl'): row.update(target=args[0], AA=0, LK=int(name == 'bl'))
        else:
            keys = fields[name].split(); assert len(keys) == len(values), line
            row.update(zip(keys, values))
        if name in ('cmp', 'cmpl', 'cmpi', 'cmpli'): row.update(BF=0, L=0)
        if name == 'fcmpo': row.update(BF=0)
        result.append(dict(address=pc, **row))
    return result


def encode(row, pc):
    """Independent PPC bit placement, never calling the reader's decoder."""
    name = row['mnemonic']
    if name in D_FORMS:
        op, reg = D_FORMS[name]
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['displacement'] & 65535
    if name in ('psq_st', 'psq_l'):
        op, reg = (60, 'fS') if name == 'psq_st' else (56, 'fD')
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['W'] << 15 | row['I'] << 12 | row['displacement'] & 4095
    if name in ('addi', 'addis', 'mulli', 'ori', 'oris'):
        op, reg = {'addi': (14, 'rD'), 'addis': (15, 'rD'), 'mulli': (7, 'rD'), 'ori': (24, 'rS'), 'oris': (25, 'rS')}[name]
        return op << 26 | row[reg] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name in ('cmpi', 'cmpli'):
        return (11 if name == 'cmpi' else 10) << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['immediate'] & 65535
    if name in ('cmp', 'cmpl'):
        return 31 << 26 | row['BF'] << 23 | row['L'] << 21 | row['rA'] << 16 | row['rB'] << 11 | (32 if name == 'cmpl' else 0) << 1
    if name == 'rlwinm':
        return 21 << 26 | row['rS'] << 21 | row['rA'] << 16 | row['SH'] << 11 | row['MB'] << 6 | row['ME'] << 1 | row['Rc']
    if name == 'extsb': return 31 << 26 | row['rS'] << 21 | row['rA'] << 16 | 954 << 1 | row['Rc']
    if name in ('or', 'add'):
        return 31 << 26 | row['rD' if name == 'add' else 'rS'] << 21 | row['rA'] << 16 | row['rB'] << 11 | (444 if name == 'or' else 266) << 1 | row['Rc']
    if name in ('lwzx', 'stwx'):
        return 31 << 26 | row['rD' if name == 'lwzx' else 'rS'] << 21 | row['rA'] << 16 | row['rB'] << 11 | (23 if name == 'lwzx' else 151) << 1
    if name in ('mflr', 'mtlr', 'mtctr'):
        reg, spr, xo = ('rD', 8, 339) if name == 'mflr' else ('rS', 8 if name == 'mtlr' else 9, 467)
        return 31 << 26 | row[reg] << 21 | (spr & 31) << 16 | (spr >> 5) << 11 | xo << 1
    if name == 'bc': return 16 << 26 | row['BO'] << 21 | row['BI'] << 16 | (int(row['target'], 16) - pc) & 65532 | row['AA'] << 1 | row['LK']
    if name in ('b', 'bl'): return 18 << 26 | (int(row['target'], 16) - pc) & 0x3fffffc | row['AA'] << 1 | row['LK']
    if name in ('blr', 'bctr'): return 19 << 26 | row['BO'] << 21 | row['BI'] << 16 | row['BH'] << 11 | (16 if name == 'blr' else 528) << 1 | row['LK']
    if name == 'fcmpo': return 63 << 26 | row['BF'] << 23 | row['fA'] << 16 | row['fB'] << 11 | 32 << 1
    if name == 'fmr': return 63 << 26 | row['fD'] << 21 | row['fB'] << 11 | 72 << 1
    raise AssertionError(name)


ALL_EXPECTED = parse_fixture()
EXPECTED = {pc: [r for r in ALL_EXPECTED if pc <= int(r['address'],16) < pc+width] for pc,width,_ in INVENTORY}
BODIES = {pc: b''.join(struct.pack('>I', encode(row, int(row['address'], 16))) for row in EXPECTED[pc]) for pc,_,_ in INVENTORY}


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args): self.calls.append(args); return self.raw, []

TABLE_ADDRESS, TABLE_WIDTH = 0x802c3938, 40
TABLE_DIGEST = '7464e12255e4f6c2c50b0cd2d2545500fe0a00ac82237ee4343c83dcb572ba11'
TABLE_TARGETS = (0x800105ac, 0x800105ac, 0x80010570, 0x80010578, 0x80010580,
                 0x80010588, 0x80010590, 0x80010598, 0x800105a0, 0x800105a8)
TABLE_BYTES = b''.join(struct.pack('>I', value) for value in TABLE_TARGETS)
DATA3_MAPPING = (0x802bae60, 0x803af120, 5, 'MAIN_.data3', 5, 1000128, 199)
TABLE_READ = (199, 35544, 40, 1000128)
ALL_READS = EXPECTED_READS + [TABLE_READ]


class SyntheticTests(unittest.TestCase):
    def test_literal_inventory_independent_source_index_map_extent(self):
        self.assertEqual(a.RANGES, INVENTORY)
        self.assertEqual(a.TEXT_MAPPING, TEXT_MAPPING)
        self.assertEqual(a.DATA3_MAPPING, DATA3_MAPPING)
        self.assertEqual(len(ALL_EXPECTED), 273)
        root = Path(__file__).resolve().parents[3]
        index = (root / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        symbols = (root / 'research/symbols/GG4E-CSM-20220412.map').read_text().splitlines()
        for pc, width, _ in INVENTORY:
            self.assertEqual([row['address'] for row in EXPECTED[pc]],
                             [f'{addr:08x}' for addr in range(pc, pc+width, 4)])
        self.assertEqual(index[1391:1393], ['8006b450\tzz_006b450_\tchunk_0009.c', '8006b7f4\tzz_006b7f4_\tchunk_0009.c'])
        self.assertEqual(index[200:202], ['80010514\tzz_0010514_\tchunk_0001.c', '800105b4\tzz_00105b4_\tchunk_0001.c'])
        for file, start, end, entry, size, map_line in (
                ('chunk_0009.c', 1441, 1582, '8006b450', '000003a4', 835),
                ('chunk_0001.c', 3095, 3132, '80010514', '000000a0', 150)):
            lines = (root / 'research/decomp/ghidra-export' / file).read_text().splitlines()[start-1:end]
            self.assertEqual(lines[0], f'// ==== {entry}  zz_00{entry[3:]}_ ====')
            self.assertEqual(lines[-1], '}')
            self.assertEqual(symbols[map_line-1], f'{entry} {size} {entry} 0 zz_00{entry[3:]}_')
        # The default label is NOT a second extent or a switch-table size.
        self.assertEqual(symbols[150], '800105ac 000000a0 800105ac 0 def_8001056C')

    def test_all273_operands_inverse_and8736_instruction_bit_controls(self):
        count = 0
        for pc, width, digest in INVENTORY:
            body = BODIES[pc]
            self.assertEqual((len(body), hashlib.sha256(body).hexdigest()), (width, digest))
            report = a.range_evidence(FakeDB(body), TEXT_MAPPING, pc, width)
            self.assertEqual(report['instructions'], EXPECTED[pc])
            for original in EXPECTED[pc]:
                address = int(original['address'], 16)
                row = {k:v for k,v in original.items() if k != 'address'}
                word = encode(row, address)
                self.assertEqual(a.decode_selected(word, address), row)
                for bit in range(32):
                    count += 1; changed = word ^ 1 << bit
                    try: decoded = a.decode_selected(changed, address)
                    except a.c.FormatError: continue
                    if decoded is not None:
                        self.assertNotEqual(decoded, row, (hex(address), bit))
                        self.assertEqual(encode(decoded, address), changed, (hex(address), bit))
        self.assertEqual(count, 8736)

    def test_exact_code_reads_and8736_payload_bit_refusals_before_decode(self):
        count = 0
        for (pc,width,_), expected_read in zip(INVENTORY, EXPECTED_READS):
            body = BODIES[pc]; db = FakeDB(body)
            a.range_evidence(db, TEXT_MAPPING, pc, width)
            self.assertEqual(db.calls, [expected_read])
            with patch.object(a, 'decode_selected') as decode:
                for index in range(width):
                    for bit in range(8):
                        changed = body[:index] + bytes([body[index] ^ 1 << bit]) + body[index+1:]
                        with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                            a.range_evidence(FakeDB(changed), TEXT_MAPPING, pc, width)
                        count += 1
                decode.assert_not_called()
        self.assertEqual(count, 8736)

    def test_table_independent_inverse_ten_targets_and320_bit_refusals(self):
        self.assertEqual(a.TABLE, (TABLE_ADDRESS, TABLE_WIDTH, TABLE_DIGEST))
        self.assertEqual(a.TABLE_TARGETS, TABLE_TARGETS)
        self.assertEqual(hashlib.sha256(TABLE_BYTES).hexdigest(), TABLE_DIGEST)
        db = FakeDB(TABLE_BYTES)
        report = a.table_evidence(db, DATA3_MAPPING, TABLE_ADDRESS, TABLE_WIDTH)
        self.assertEqual(db.calls, [TABLE_READ])
        self.assertEqual(report['entries'], [dict(index=i, address=f'{TABLE_ADDRESS+4*i:08x}', target=f'{target:08x}')
                                            for i,target in enumerate(TABLE_TARGETS)])
        self.assertEqual(report['extent_basis'], 'authenticated instruction reachability, not map extent')
        count = 0
        with patch.object(a.c, 'integer') as integer:
            for index in range(40):
                for bit in range(8):
                    changed = TABLE_BYTES[:index] + bytes([TABLE_BYTES[index] ^ 1 << bit]) + TABLE_BYTES[index+1:]
                    with self.assertRaisesRegex(a.c.FormatError, 'table digest mismatch'):
                        a.table_evidence(FakeDB(changed), DATA3_MAPPING, TABLE_ADDRESS, TABLE_WIDTH)
                    count += 1
            integer.assert_not_called()
        self.assertEqual(count, 320)
        for index in range(10):
            changed = list(TABLE_TARGETS); changed[index] ^= 4
            with patch.object(a, 'TABLE_TARGETS', tuple(changed)):
                with self.assertRaisesRegex(a.c.FormatError, 'table targets mismatch'):
                    a.table_evidence(FakeDB(TABLE_BYTES), DATA3_MAPPING, TABLE_ADDRESS, TABLE_WIDTH)

    def test_complete_flow_and_every_flow_operand_tamper_refused(self):
        count = 0; calls = []
        original = a.decode_selected
        for pc, width, _ in INVENTORY:
            flow = [r for r in EXPECTED[pc] if r['mnemonic'] in ('bc','b','bl','blr','bctr')]
            self.assertEqual(a.expected_flow(pc), flow)
            self.assertEqual(len(flow), 53 if pc == 0x8006b450 else 11)
            self.assertTrue(all(pc <= int(r['target'],16) < pc+width for r in flow if r['mnemonic'] in ('bc','b')))
            calls.extend((r['address'],r['target']) for r in flow if r['mnemonic'] == 'bl')
            for row in flow:
                address = int(row['address'],16)
                for field, value in row.items():
                    if field == 'address': continue
                    replacement = ('addi' if field == 'mnemonic' else f'{int(value,16)^4:08x}'
                                   if field == 'target' else value ^ 1)
                    def changed(word, where):
                        decoded = original(word, where)
                        return dict(decoded, **{field: replacement}) if where == address else decoded
                    with patch.object(a, 'decode_selected', changed):
                        with self.assertRaisesRegex(a.c.FormatError, 'complete control-flow mismatch'):
                            a.range_evidence(FakeDB(BODIES[pc]), TEXT_MAPPING, pc, width)
                    count += 1
        self.assertEqual(calls, [('8006b474','80010514'),('8006b720','8020bc88'),('8006b748','8020bc88')])
        self.assertEqual(count, 337)

    def test_switch_guard_stride_table_extent_return_masks_and_signed_index(self):
        rows = {int(r['address'],16):r for r in EXPECTED[0x80010514]}
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x80010548,0x80010570,4)],
                         ['lbz','rlwinm','cmpli','bc','addis','rlwinm','addi','lwzx','mtctr','bctr'])
        self.assertEqual((rows[0x8001054c]['SH'],rows[0x8001054c]['MB'],rows[0x8001054c]['ME']), (0,25,31))
        self.assertEqual((rows[0x80010550]['immediate'],rows[0x80010554]['BO'],rows[0x80010554]['BI'],rows[0x80010554]['target']),
                         (9,12,1,'800105ac'))
        self.assertEqual((rows[0x8001055c]['SH'],rows[0x8001055c]['MB'],rows[0x8001055c]['ME']), (2,0,29))
        self.assertEqual(((rows[0x80010558]['immediate'] << 16)+rows[0x80010560]['immediate']) & 0xffffffff, TABLE_ADDRESS)
        for byte in range(256):
            index = byte & 127
            if index > 9: continue
            self.assertTrue(TABLE_ADDRESS <= TABLE_ADDRESS+4*index < TABLE_ADDRESS+TABLE_WIDTH)
            target = TABLE_TARGETS[index]
            if index < 2: self.assertEqual(target,0x800105ac)
            else:
                self.assertEqual(rows[target]['mnemonic'], 'ori')
                self.assertEqual(rows[target]['immediate'], 1 << (index-2))
        self.assertEqual(rows[0x80010514]['immediate'], 0x3e4)
        self.assertEqual(rows[0x80010528]['displacement'], 0x18)
        self.assertEqual(rows[0x80010534]['immediate'], 0x8000)
        self.assertEqual(rows[0x80010540]['immediate'], 0x4e84)
        self.assertEqual(rows[0x80010548]['displacement'], 0x43d)
        # No stack or payload writes occur in the helper; only register results.
        self.assertFalse(any(r['mnemonic'] in ('stw','stb','stwx','stfs','stwu') for r in rows.values()))

    def test_psq_warnings_not_unreachable_and_all_complete_body_bytes_retained(self):
        rows = {int(r['address'],16):r for r in EXPECTED[0x8006b450]}
        for pc, name, reg in ((0x8006b460,'psq_st','fS'),(0x8006b7d8,'psq_l','fD')):
            self.assertEqual(rows[pc],dict(address=f'{pc:08x}',mnemonic=name,**{reg:31},rA=1,displacement=56,W=0,I=0))
        self.assertEqual(rows[0x8006b45c]['mnemonic'],'stfd')
        self.assertEqual(rows[0x8006b7dc]['mnemonic'],'lfd')
        self.assertEqual(rows[0x8006b47c]['target'],'8006b7d8')
        # Simple direct CFG reachability, not instruction execution or condition evaluation.
        pending, reached = [0x8006b450], set()
        while pending:
            pc = pending.pop()
            if pc in reached: continue
            reached.add(pc); row = rows[pc]; name = row['mnemonic']
            if name == 'blr': continue
            if name in ('bc','b'): pending.append(int(row['target'],16))
            if name != 'b': pending.append(pc+4)
        self.assertIn(0x8006b460,reached); self.assertIn(0x8006b7d8,reached)
        self.assertEqual(set(rows)-reached,{0x8006b680})
        self.assertEqual(rows[0x8006b680]['target'],'8006b690')

    def test_selector_entry_guard_cues_and_fast_return_order(self):
        rows = {int(r['address'],16):r for r in EXPECTED[0x8006b450]}
        self.assertEqual((rows[0x8006b46c]['displacement'],rows[0x8006b470]['mnemonic']), (0x3e4,'extsb'))
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006b474,0x8006b49c,4)],
                         ['bl','cmpi','bc','lbz','extsb','bc','lbz','extsb','cmpi','bc'])
        self.assertEqual((rows[0x8006b480]['displacement'],rows[0x8006b48c]['displacement']), (0x73f,0x73c))
        self.assertEqual((rows[0x8006b498]['BO'],rows[0x8006b498]['BI']), (4,1))
        for pc, offset, mode in ((0x8006b4dc,0x73d,1),(0x8006b4e8,0x73d,2),(0x8006b4f8,0x73d,1)):
            self.assertEqual((rows[pc]['rD'],rows[pc]['rA'],rows[pc]['immediate']), (30,29,offset))
            self.assertEqual((rows[pc+4]['rD'],rows[pc+4]['immediate']), (31,mode))
        self.assertEqual(rows[0x8006b4bc]['target'],'8006b544')  # cue >= 6 does not initialize r30/r31
        self.assertEqual(rows[0x8006b544]['rA'],30)
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006b4c0,0x8006b4d8,4)],
                         ['lwz','addi','addi','stw','lwz','stw'])
        self.assertEqual([(rows[pc]['rA'],rows[pc]['displacement']) for pc in (0x8006b4c0,0x8006b4cc,0x8006b4d0,0x8006b4d4)],
                         [(29,0x508),(29,0x6e0),(29,0x504),(29,0x6e4)])
        self.assertEqual([(rows[pc]['mnemonic'],rows[pc].get('displacement')) for pc in (0x8006b52c,0x8006b538,0x8006b53c)],
                         [('stw',0x508),('stb',0x502),('stb',0x73c)])
        self.assertEqual(rows[0x8006b540]['target'],'8006b7d8')

    def test_candidate_filter_order_signed_status_count_store_before_list_store(self):
        rows = {int(r['address'],16):r for r in EXPECTED[0x8006b450]}
        self.assertEqual(rows[0x8006b55c]['mnemonic'],'lhz')
        self.assertEqual(rows[0x8006b55c]['displacement'],-21342)
        self.assertEqual(rows[0x8006b560]['displacement'],-21504)
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006b57c,0x8006b59c,4)],
                         ['lwz','lhz','rlwinm','bc','lwz','cmpli','bc','lbz'])
        self.assertEqual((rows[0x8006b584]['MB'],rows[0x8006b584]['ME']), (22,22))
        self.assertEqual((rows[0x8006b5a4]['rA'],rows[0x8006b5a4]['rB']), (29,7))
        self.assertEqual((rows[0x8006b60c]['displacement'],rows[0x8006b610]['mnemonic'],rows[0x8006b614]['immediate']), (0x18,'extsb',2))
        self.assertEqual((rows[0x8006b618]['BO'],rows[0x8006b618]['BI']), (4,0))
        for value in range(256):
            signed = value - 256 if value >= 128 else value
            self.assertEqual(signed < 2, value in (0,1) or value >= 128)
        self.assertEqual(rows[0x8006b628]['rD'],5)
        self.assertEqual(rows[0x8006b62c]['rD'],8)
        self.assertEqual((rows[0x8006b640]['mnemonic'],rows[0x8006b644]['mnemonic']), ('stw','stwx'))
        self.assertEqual((rows[0x8006b644]['rS'],rows[0x8006b644]['rA'],rows[0x8006b644]['rB']), (4,6,0))
        self.assertEqual((rows[0x8006b64c]['BO'],rows[0x8006b64c]['BI']), (16,0))

    def test_cycle_write_before_compare_nearest_unordered_and_commit_load_order(self):
        rows = {int(r['address'],16):r for r in EXPECTED[0x8006b450]}
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006b6c4,0x8006b6dc,4)],
                         ['lwzx','stb','lwz','cmpl','bc','b'])
        self.assertEqual(rows[0x8006b6c8]['rA'],30)
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006b708,0x8006b724,4)],
                         ['lfs','stfs','lfs','stfs','lfs','stfs','bl'])
        self.assertEqual([(rows[pc]['rA'],rows[pc]['displacement']) for pc in (0x8006b708,0x8006b710,0x8006b718)],
                         [(5,0x8e0),(5,0x8f0),(5,0x900)])
        self.assertEqual((rows[0x8006b750]['BO'],rows[0x8006b750]['BI']), (12,1))
        # BO12/BI1 skips GT only. Equality and unordered replace the winner.
        for lt,gt,eq,un in ((1,0,0,0),(0,1,0,0),(0,0,1,0),(0,0,0,1)):
            self.assertEqual(not bool(gt), bool(lt or eq or un))
        self.assertEqual([rows[pc]['mnemonic'] for pc in range(0x8006b788,0x8006b7b4,4)],
                         ['stw','lwz','stw','lwz','lwz','stw','stw','lwz','stw','stb','stb'])
        self.assertEqual([(rows[pc]['rA'],rows[pc]['displacement']) for pc in (0x8006b794,0x8006b798,0x8006b7a4)],
                         [(31,0x64),(31,0x68),(31,0x6c)])
        self.assertEqual(rows[0x8006b7b4]['displacement'],0x3e4)  # reload before +3f1 write
        self.assertEqual(rows[0x8006b7bc]['displacement'],0x3f1)
        self.assertEqual([rows[pc]['displacement'] for pc in range(0x8006b7c8,0x8006b7d8,4)], [0x2e6,0x1b,0x1a,0x19])

    def test_invalid_code_table_ranges_maps_widths_and_decoder_bounds(self):
        for pc,width,_ in INVENTORY:
            body = BODIES[pc]
            for address, size in [(bad,width) for bad in (pc-4,pc+4,pc+1,float(pc),True,-1,1<<32,TABLE_ADDRESS)] + [
                    (pc,bad) for bad in (0,width-4,width+4,-width,True,float(width))]:
                db = FakeDB(body)
                with self.assertRaises(a.c.FormatError): a.range_evidence(db,TEXT_MAPPING,address,size)
                self.assertFalse(db.calls)
            for raw in (body[:-1],body+b'\0'):
                with self.assertRaisesRegex(a.c.FormatError,'byte width'): a.range_evidence(FakeDB(raw),TEXT_MAPPING,pc,width)
            with patch.object(a,'RANGES',a.RANGES*2):
                db=FakeDB(body)
                with self.assertRaises(a.c.FormatError): a.range_evidence(db,TEXT_MAPPING,pc,width)
                self.assertFalse(db.calls)
            with patch.object(a,'decode_selected',return_value=None):
                with self.assertRaisesRegex(a.c.FormatError,'unselected instruction'): a.range_evidence(FakeDB(body),TEXT_MAPPING,pc,width)
        for address,width in [(bad,40) for bad in (TABLE_ADDRESS-4,TABLE_ADDRESS+4,TABLE_ADDRESS+40,float(TABLE_ADDRESS),True)] + [
                (TABLE_ADDRESS,bad) for bad in (0,4,36,44,True,40.0)]:
            db=FakeDB(TABLE_BYTES)
            with self.assertRaises(a.c.FormatError): a.table_evidence(db,DATA3_MAPPING,address,width)
            self.assertFalse(db.calls)
        for raw in (TABLE_BYTES[:-1],TABLE_BYTES+b'\0'):
            with self.assertRaisesRegex(a.c.FormatError,'table byte width'):
                a.table_evidence(FakeDB(raw),DATA3_MAPPING,TABLE_ADDRESS,40)
        for mapping,call,body,address,width in ((TEXT_MAPPING,a.range_evidence,BODIES[0x8006b450],0x8006b450,932),
                                                (DATA3_MAPPING,a.table_evidence,TABLE_BYTES,TABLE_ADDRESS,40)):
            variants=[list(mapping)]
            for index,value in enumerate(mapping):
                for replacement in (value+1,float(value)) if type(value) is int else ('wrong',):
                    changed=list(mapping);changed[index]=replacement;variants.append(tuple(changed))
            for changed in variants:
                db=FakeDB(body)
                with self.assertRaises(a.c.FormatError): call(db,changed,address,width)
                self.assertFalse(db.calls)
        for word,pc in ((True,0),(-1,0),(1<<32,0),(0,True),(0,1),(0,-4),(0,1<<32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word,pc)

    def test_authentication_precedes_parser_and_all_selection(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c,'GBF') as db, patch.object(a,'range_evidence') as code, patch.object(a,'table_evidence') as table:
            with self.assertRaisesRegex(a.c.FormatError,'auth stop'): a.inspect(b'bad','bad')
            auth.assert_called_once_with(b'bad','bad');db.assert_not_called();code.assert_not_called();table.assert_not_called()

    def test_mapping_refusal_precedes_all_selection(self):
        blocks,subs={},{}
        for name,key,start,length,root in a.command.MAPPINGS:
            blocks[key]=[name,None,None,15,start,length,0];subs[key]=[key,2,length,0,root,0]
        cases=[]
        for key in (1,5,7):
            for field,value in ((0,'wrong'),(4,blocks[key][4]+4),(5,blocks[key][5]+4),(6,1)):
                bb,ss=copy.deepcopy((blocks,subs));bb[key][field]=value;cases.append((bb,ss,'80000000'))
            for field in range(6):
                bb,ss=copy.deepcopy((blocks,subs));ss[key][field]+=1;cases.append((bb,ss,'80000000'))
            bb,ss=copy.deepcopy((blocks,subs));bb[99]=copy.deepcopy(bb[key]);cases.append((bb,ss,'80000000'))
            bb,ss=copy.deepcopy((blocks,subs));ss[99]=copy.deepcopy(ss[key]);cases.append((bb,ss,'80000000'))
            for kind in ('block','sub'):
                bb,ss=copy.deepcopy((blocks,subs));del (bb if kind=='block' else ss)[key];cases.append((bb,ss,'80000000'))
        cases.append((blocks,subs,'80000004'));self.assertEqual(len(cases),43)
        for bb,ss,image in cases:
            with patch.object(a.c,'inspect',return_value={'image_offset':image}),patch.object(a.c,'GBF') as db, \
                 patch.object(a,'range_evidence') as code,patch.object(a,'table_evidence') as table:
                db.return_value.tables.return_value={'Memory Blocks':'b','Sub Memory Blocks':'s'}
                db.return_value.rows.side_effect=lambda key:{'b':bb,'s':ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic','synthetic')
                code.assert_not_called();table.assert_not_called()

    def test_no_arbitrary_cli_and_missing_snapshot(self):
        for option in ('--address','--width','--pointer','--target','--table','--dump','--state'):
            with patch('sys.argv',['reader','none',option,'0']),contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code,2)
        with patch('sys.argv',['reader','/nonexistent/target.gbf']),contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(),1);self.assertIn('not a regular file',json.loads(error.getvalue())['error'])


SNAPSHOT_DIR = Path(__file__).resolve().parents[2] / 'decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


@unittest.skipUnless(all((SNAPSHOT_DIR/name).is_file() for name in ('db.3.gbf','db.4.gbf')),
                     'existing local snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports,cls.reads,cls.auth_reads=[],[],[]
        original=a.c.GBF.chain
        for name in ('db.3.gbf','db.4.gbf'):
            raw=(SNAPSHOT_DIR/name).read_bytes();digest=hashlib.sha256(raw).hexdigest();reads=[]
            def traced(db,*args): reads.append(args);return original(db,*args)
            with patch.object(a.c.GBF,'chain',traced): a.c.inspect(raw,digest)
            cls.auth_reads.append(reads[:]);reads.clear()
            with patch.object(a.c.GBF,'chain',traced): cls.reports.append(a.inspect(raw,digest))
            cls.reads.append(reads[:])

    def test_both_snapshots_exact_operands_table_coverage_and_ceiling(self):
        for key in ('mappings','ranges','switch_table','function_coverage','selection_basis'):
            self.assertEqual(self.reports[0][key],self.reports[1][key],key)
        self.assertEqual([r['snapshot'] for r in self.reports],['db.3.gbf','db.4.gbf'])
        self.assertEqual([r['snapshot_sha256'] for r in self.reports],
                         ['7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0',
                          '1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'],dict(version=0,root=-1,count=0))
            for row,(pc,width,_) in zip(report['ranges'],INVENTORY): self.assertEqual(row['instructions'],EXPECTED[pc])
            self.assertEqual([int(row['target'],16) for row in report['switch_table']['entries']],list(TABLE_TARGETS))
            basis=report['selection_basis']
            self.assertEqual((basis['reads'],basis['bytes'],basis['selected_data_cells']),(3,1132,10))
            self.assertEqual(basis['selected_code_bytes'],1092)
            for key in ('pointer_following','global_payloads_read','unlisted_callee_bodies_read',
                        'globals_runtime_values_established','original_execution','constants_selected','estimator_imported'):
                self.assertFalse(basis[key])
            self.assertTrue(basis['switch_table_selected']);self.assertTrue(basis['switch_targets_established'])
            self.assertIn('not original-DOL identity',report['caveat'])
            self.assertEqual([r['represented_instructions'] for r in report['function_coverage']],[233,40])
            for row in report['function_coverage']:
                self.assertEqual(row['unrepresented_instructions'],0);self.assertEqual(row['unrepresented_ranges'],[])
                self.assertEqual(row['selected_width'],row['map_size'])

    def test_exact_three_selected_reads_after_unchanged_authentication(self):
        for reads,auth in zip(self.reads,self.auth_reads):
            self.assertEqual(reads,auth+ALL_READS);self.assertTrue(auth)
            self.assertTrue(all(row[0]==263 for row in auth))

    def test_physical_spans_and_no_raw_output(self):
        for report in self.reports:
            expected_spans=[dict(root_buffer=21,data_buffer=47,chain_offset=417392,data_offset=7942,length=932,obfuscated=True,physical_offset=794380),
                            dict(root_buffer=21,data_buffer=24,chain_offset=44852,data_offset=12096,length=160,obfuscated=True,physical_offset=421702)]
            for row,span in zip(report['ranges'],expected_spans):
                self.assertEqual(row['spans'],[span])
                self.assertEqual(set(row),{'address','end_exclusive','width','sha256','spans','instructions'})
                self.assertFalse(any('word' in item or 'bytes' in item for item in row['instructions']))
            self.assertEqual(report['switch_table']['spans'],[dict(root_buffer=199,data_buffer=202,chain_offset=35544,
                data_offset=2788,length=40,obfuscated=True,physical_offset=3328746)])
            self.assertEqual(report['switch_table']['end_exclusive'],'802c3960')
            self.assertEqual(set(report['switch_table']),{'address','end_exclusive','width','sha256','spans','entries','extent_basis'})

    def test_snapshot_hash_schema_and_each_selected_payload_refuse(self):
        raw=(SNAPSHOT_DIR/'db.3.gbf').read_bytes();digest=hashlib.sha256(raw).hexdigest()
        with patch.object(a,'range_evidence') as code,patch.object(a,'table_evidence') as table:
            for changed,claimed in ((raw,'0'*64),(raw[:-1]+bytes([raw[-1]^1]),digest)):
                with self.assertRaisesRegex(a.c.FormatError,'SHA256 not allowlisted'): a.inspect(changed,claimed)
            code.assert_not_called();table.assert_not_called()
        original_tables=a.c.GBF.tables
        for name in ('Program','Property Table','File Bytes','ADDRESS MAP','Memory Blocks','Sub Memory Blocks'):
            for field in ('version','keytype','types','fields','missing'):
                def changed_tables(db):
                    tables=copy.deepcopy(original_tables(db))
                    if field=='missing': del tables[name]
                    elif field=='types': tables[name][field]=[99]
                    elif field=='fields': tables[name][field]='Wrong;'
                    else: tables[name][field]+=1
                    return tables
                with patch.object(a.c.GBF,'tables',changed_tables),patch.object(a,'range_evidence') as code, \
                     patch.object(a,'table_evidence') as table:
                    with self.assertRaises(a.c.FormatError): a.inspect(raw,digest)
                    code.assert_not_called();table.assert_not_called()
        original=a.c.GBF.chain
        for target in ALL_READS:
            def tampered(db,*args):
                payload,spans=original(db,*args)
                if args==target: payload=bytes([payload[0]^1])+payload[1:]
                return payload,spans
            with patch.object(a.c.GBF,'chain',tampered):
                with self.assertRaisesRegex(a.c.FormatError,'digest mismatch'): a.inspect(raw,digest)


if __name__ == '__main__': unittest.main()
