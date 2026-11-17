#!/usr/bin/env python3
"""Public synthetic controls + optional private-snapshot validation.

No complete original instruction fixture, bytes, or reconstructable listing is
embedded here. Archive-backed tests require the two existing local snapshots;
they never fetch files. Private full inventories are not test prerequisites.
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

import read_archived_matrix_active_evidence as a
from test_archived_double_action_evidence import encode as double_encode
from test_archived_later_outer_evidence import encode as contact_encode
from test_archived_actor_mode1_evidence import encode as mode1_encode
from test_archived_target_preparation_evidence import encode as target_encode
from test_archived_frame_blocker_evidence import encode as prior_encode, invented_operands as prior_invented

RANGES = ((2147776772, 296, '79704ea5e729833d36b5d4bb4164d21d3711b0db9e51b63a6bbef9da0ffda41e'), (2147902848, 76, '586315cc74ccba7aad75f08eea721f7c8a6dec5bd837b630231a83b4251131a1'), (2147927848, 152, 'fe69cec08aad2b5a23ae8fce80d8b0aeb1113b2745e6331d3f9304ebdad30c57'), (2147929212, 20, '3596abe8738d7683464fcc48aa718710633cadcd9a737faa93768214043a5d85'))
MAPPING = (2147505632, 2150302048, 1, 'MAIN_.text1', 1, 2796416, 21)
READS = [(21, 271140, 296, 2796416), (21, 397216, 76, 2796416), (21, 422216, 152, 2796416), (21, 423580, 20, 2796416)]
CONSTANT_READS = [(263, 1724, 4, 27360), (263, 1688, 8, 27360), (263, 3188, 4, 27360), (263, 3200, 8, 27360)]

ROOT = Path(__file__).resolve().parents[3]
SNAPSHOT_DIR = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'


def encode(row, pc):
    if row['mnemonic'] == 'fctiwz': return double_encode(row,pc)
    if row['mnemonic'] in ('xoris','fneg'): return mode1_encode(row,pc)
    return contact_encode(row,pc)


def invented_operands():
    return prior_invented()


class FakeDB:
    def __init__(self, raw=b''): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class SyntheticTests(unittest.TestCase):
    def test_frozen_extents_and_independent_readable_provenance(self):
        self.assertEqual(a.RANGES, RANGES); self.assertEqual(a.TEXT_MAPPING, MAPPING)
        self.assertEqual(sum(width for _, width, _ in RANGES), 544)
        index=(ROOT/'research/decomp/ghidra-export/_index.tsv').read_text()
        for start,end,chunk in ((0x80047904,0x80047a2c,'chunk_0005.c'),(0x80066580,0x800665cc,'chunk_0008.c'),(0x8006c728,0x8006cc90,'chunk_0009.c')):
            self.assertIn(f'{start:08x}\t',index);self.assertIn(f'{end:08x}\t',index)
            source=(ROOT/'research/decomp/ghidra-export'/chunk).read_text()
            body,suffix=source.split(f'// ==== {start:08x} ',1)[1].split('// ==== ',1)
            self.assertTrue(body.strip());self.assertTrue(suffix.startswith(f'{end:08x} '))
        self.assertEqual(a.UNSELECTED_BRANCHES,(('8006c74c','8006c7c0'),))

    def test_invented_forms_independent_inverse_and_bit_controls(self):
        mutations = 0
        for row in invented_operands():
            word = encode(row, 0x10000000)
            self.assertEqual(a.decode_selected(word, 0x10000000), row)
            for bit in range(32):
                changed = word ^ (1 << bit); mutations += 1
                try: result = a.decode_selected(changed, 0x10000000)
                except a.c.FormatError: continue
                if result is not None:
                    self.assertNotEqual(result, row)
                    self.assertEqual(encode(result, 0x10000000), changed)
        self.assertEqual(mutations, 992)

    def test_invalid_word_pc_reserved_and_unselected_forms(self):
        for word, pc in ((True, 0), (-1, 0), (1 << 32, 0), (0, True), (0, 1), (0, -4), (0, 1 << 32)):
            with self.assertRaises(a.c.FormatError): a.decode_selected(word, pc)
        for word in ((35 << 26), (35 << 26) | (3 << 21) | (3 << 16),
                     (46 << 26) | (20 << 21) | (21 << 16),
                     (31 << 26) | (151 << 1) | 1, (31 << 26) | (23 << 1) | 1,
                     (16 << 26) | (4 << 21) | 1, 0x4e800420):
            try: result = a.decode_selected(word, 0x10000000)
            except a.c.FormatError: continue
            self.assertIsNone(result)
        self.assertIsNone(a.decode_selected(49 << 26, 0x10000000))  # Updating float load is unselected.

    def test_selection_bounds_types_duplicates_maps_refuse_before_read(self):
        for pc, width, _ in RANGES:
            for bad in (pc - 4, pc + 4, pc + 1, float(pc), True, -1, 1 << 32):
                db = FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, bad, width)
                self.assertFalse(db.calls)
            for bad in (0, width - 4, width + 4, float(width), True, -width):
                db = FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, pc, bad)
                self.assertFalse(db.calls)
            for i, value in enumerate(MAPPING):
                for replacement in (value + 1, float(value)) if type(value) is int else ('wrong',):
                    changed = list(MAPPING); changed[i] = replacement; db = FakeDB()
                    with self.assertRaises(a.c.FormatError): a.range_evidence(db, tuple(changed), pc, width)
                    self.assertFalse(db.calls)
            with patch.object(a, 'RANGES', RANGES * 2):
                db = FakeDB()
                with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, pc, width)
                self.assertFalse(db.calls)
        for pc in (0x800055fc, 0x80010514, 0x803c4e84, 0x803c73b0, 0x803ca270, 0x804360dc):
            db = FakeDB()
            with self.assertRaises(a.c.FormatError): a.range_evidence(db, MAPPING, pc, 4)
            self.assertFalse(db.calls)

    def test_wrong_width_and_digest_fail_before_decoder(self):
        with patch.object(a, 'decode_selected') as decode:
            for pc, width, _ in RANGES:
                for size in (width - 1, width + 1):
                    with self.assertRaisesRegex(a.c.FormatError, 'byte width'):
                        a.range_evidence(FakeDB(bytes(size)), MAPPING, pc, width)
                with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                    a.range_evidence(FakeDB(bytes(width)), MAPPING, pc, width)
            decode.assert_not_called()

    def test_reused_xoris_and_fneg_forms(self):
        for d in range(32):
            for b in range(32):
                row=dict(mnemonic='fneg',fD=d,fB=b,Rc=0)
                self.assertEqual(a.decode_selected(encode(row,0),0),row)
            for imm in (0,1,32768,65535):
                row=dict(mnemonic='xoris',rS=d,rA=31-d,immediate=imm)
                self.assertEqual(a.decode_selected(encode(row,0),0),row)

    def test_constant_scope_mapping_and_bits(self):
        for pc,width,bits in a.CONSTANTS:
            raw=bytes.fromhex(bits);self.assertEqual(a.constant_evidence(FakeDB(raw),a.DATA_MAPPING,pc,width)['bits'],bits)
            for badpc,badwidth in ((pc+1,width),(pc,width+1),(True,width),(pc,True)):
                db=FakeDB(raw)
                with self.assertRaises(a.c.FormatError):a.constant_evidence(db,a.DATA_MAPPING,badpc,badwidth)
                self.assertFalse(db.calls)
            with self.assertRaises(a.c.FormatError):a.constant_evidence(FakeDB(raw),MAPPING,pc,width)
            for i in range(width*8):
                changed=bytearray(raw);changed[i//8]^=1<<(i%8)
                with self.assertRaises(a.c.FormatError):a.constant_evidence(FakeDB(bytes(changed)),a.DATA_MAPPING,pc,width)

    def test_authentication_precedes_parser_and_selection(self):
        with patch.object(a.c, 'inspect', side_effect=a.c.FormatError('auth stop')) as auth, \
             patch.object(a.c, 'GBF') as db, patch.object(a, 'range_evidence') as code:
            with self.assertRaisesRegex(a.c.FormatError, 'auth stop'): a.inspect(b'bad', 'bad')
            auth.assert_called_once_with(b'bad', 'bad'); db.assert_not_called(); code.assert_not_called()

    def test_mapping_corruptions_precede_selection(self):
        blocks, subs = {}, {}
        for name, key, start, length, root in a.command.MAPPINGS:
            blocks[key] = [name, None, None, 15, start, length, 0]
            subs[key] = [key, 2, length, 0, root, 0]
        cases = []
        for key in (1, 5, 7):
            for field in (4, 5, 6):
                bb, ss = copy.deepcopy((blocks, subs)); bb[key][field] += 1; cases.append((bb, ss))
            for field in range(6):
                bb, ss = copy.deepcopy((blocks, subs)); ss[key][field] += 1; cases.append((bb, ss))
            for table in ('block', 'sub'):
                bb, ss = copy.deepcopy((blocks, subs)); del (bb if table == 'block' else ss)[key]; cases.append((bb, ss))
        for bb, ss in cases:
            with patch.object(a.c, 'inspect', return_value={'image_offset': '80000000'}), patch.object(a.c, 'GBF') as db, \
                 patch.object(a, 'range_evidence') as code:
                db.return_value.tables.return_value = {'Memory Blocks': 'b', 'Sub Memory Blocks': 's'}
                db.return_value.rows.side_effect = lambda key: {'b': bb, 's': ss}[key]
                with self.assertRaises(a.c.FormatError): a.inspect(b'synthetic', 'synthetic')
                code.assert_not_called()
        self.assertEqual(len(cases), 33)

    def test_cli_has_no_general_read_or_dump_options(self):
        for option in ('--address', '--width', '--pointer', '--target', '--dump', '--instructions'):
            with patch('sys.argv', ['reader', 'none', option, '0']), contextlib.redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as exc: a.main()
                self.assertEqual(exc.exception.code, 2)
        with patch('sys.argv', ['reader', '/nonexistent/snapshot.gbf']), contextlib.redirect_stderr(io.StringIO()) as error:
            self.assertEqual(a.main(), 1)
            self.assertIn('not a regular file', json.loads(error.getvalue())['error'])

    def test_reused_scope_is_explicit(self):
        self.assertEqual([(x['address'], x['read_here']) for x in a.REUSED_EVIDENCE],
                         [('80047904', True)])
        for row in a.REUSED_EVIDENCE:
            self.assertTrue((ROOT / 'research/decomp' / row['source']).is_file())
        self.assertTrue(all(not v for v in a.INDIRECT_CALLS.values()))


@unittest.skipUnless(all((SNAPSHOT_DIR / name).is_file() for name in ('db.3.gbf', 'db.4.gbf')),
                     'existing private snapshots optional; never fetched')
class ArchivedTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reports, cls.traces, cls.auth_traces, cls.rows, cls.words, cls.bodies = [], [], [], [], [], []
        chain, decode = a.c.GBF.chain, a.decode_selected
        for name in ('db.3.gbf', 'db.4.gbf'):
            raw = (SNAPSHOT_DIR / name).read_bytes(); digest = hashlib.sha256(raw).hexdigest()
            trace, rows, words, bodies = [], {}, {}, {}
            def traced(db, *args):
                trace.append(args); result = chain(db, *args)
                if args in READS: bodies[RANGES[READS.index(args)][0]] = result[0]
                return result
            def decoded(word, pc):
                result = decode(word, pc); rows[pc] = result; words[pc] = word
                return result
            with patch.object(a.c.GBF, 'chain', traced): a.c.inspect(raw, digest)
            cls.auth_traces.append(trace[:]); trace.clear()
            with patch.object(a.c.GBF, 'chain', traced), patch.object(a, 'decode_selected', decoded):
                cls.reports.append(a.inspect(raw, digest))
            cls.traces.append(trace[:]); cls.rows.append(rows); cls.words.append(words); cls.bodies.append(bodies)

    def test_exact_eight_reads_follow_full_unchanged_authentication(self):
        for trace, auth in zip(self.traces, self.auth_traces):
            self.assertTrue(auth); self.assertTrue(all(row[0] == 263 for row in auth))
            self.assertEqual(trace, auth + READS + CONSTANT_READS)

    def test_both_snapshots_complete_and_equal_without_listing_output(self):
        for key in ('mappings', 'ranges', 'constants', 'selection_basis', 'reused_evidence'):
            self.assertEqual(self.reports[0][key], self.reports[1][key])
        self.assertEqual(self.rows[0], self.rows[1]); self.assertEqual(len(self.rows[0]), 136)
        self.assertEqual([r['snapshot'] for r in self.reports], ['db.3.gbf', 'db.4.gbf'])
        for report in self.reports:
            self.assertEqual(report['file_bytes_table'], dict(version=0, root=-1, count=0))
            self.assertEqual([r['represented_instructions'] for r in report['ranges']], [74,19,38,5])
            self.assertTrue(all(r['unrepresented_instructions'] == 0 for r in report['ranges']))
            self.assertIn('not original-DOL identity', report['caveat'])
            basis = report['selection_basis']
            self.assertEqual((basis['reads'], basis['bytes'], basis['selected_data_cells']), (8, 568, 4))
            for key in ('pointer_following', 'global_payloads_read', 'original_execution', 'operand_listing_output'):
                self.assertIs(basis[key], False)
            text = json.dumps(report)
            for disallowed in ('instructions', 'mnemonic', 'raw_bytes', 'raw_words', 'payload_hex'):
                self.assertNotIn('"' + disallowed + '"', text)

    def test_every_instruction_independent_inverse_and_4352_bit_controls(self):
        count = 0
        for pc, row in self.rows[0].items():
            word = self.words[0][pc]
            self.assertEqual(encode(row, pc), word)
            for bit in range(32):
                count += 1; changed = word ^ (1 << bit)
                try: result = a.decode_selected(changed, pc)
                except a.c.FormatError: continue
                if result is not None:
                    self.assertNotEqual(result, row, (hex(pc), bit))
                    self.assertEqual(encode(result, pc), changed, (hex(pc), bit))
        self.assertEqual(count, 4352)
        for pc, width, digest in RANGES:
            reconstructed = b''.join(struct.pack('>I', encode(self.rows[0][site], site))
                                     for site in range(pc, pc + width, 4))
            self.assertEqual(hashlib.sha256(reconstructed).hexdigest(), digest)

    def test_every_payload_bit_mutation_refuses_before_decode(self):
        count = 0
        with patch.object(a, 'decode_selected') as decoder:
            for pc, width, _ in RANGES:
                body = self.bodies[0][pc]
                for offset in range(width):
                    for bit in range(8):
                        changed = body[:offset] + bytes([body[offset] ^ (1 << bit)]) + body[offset + 1:]
                        with self.assertRaisesRegex(a.c.FormatError, 'digest mismatch'):
                            a.range_evidence(FakeDB(changed), MAPPING, pc, width)
                        count += 1
            decoder.assert_not_called()
        self.assertEqual(count, 4352)

    def test_spans_exact_widths_and_map_bounds(self):
        for report in self.reports:
            for row, (pc, width, digest) in zip(report['ranges'], RANGES):
                self.assertEqual(sum(span['length'] for span in row['spans']), width)
                self.assertEqual((row['address'], row['end_exclusive'], row['width'], row['sha256']),
                                 (f'{pc:08x}', f'{pc + width:08x}', width, digest))

    def test_semantic_inventory_mutation_fails_closed(self):
        original = a.decode_selected
        for site in self.rows[0]:
            def mutated(word, pc):
                row = original(word, pc)
                if pc == site: row = dict(row, unexpected_operand=0)
                return row
            entry, width, _ = next(row for row in RANGES if row[0] <= site < row[0] + row[1])
            with patch.object(a, 'decode_selected', mutated):
                with self.assertRaises(a.c.FormatError):
                    a.range_evidence(FakeDB(self.bodies[0][entry]), MAPPING, entry, width)

    def test_source_effect_order_and_constants(self):
        r=self.rows[0]
        for pc,field,value in ((0x80047940,'displacement',0x18),(0x8004795c,'displacement',0x191e),(0x80047960,'displacement',0x191c),(0x80047968,'target','80066580'),(0x8004796c,'displacement',0x72),(0x80047978,'immediate',0x5000),(0x80047980,'immediate',-0x5000),(0x800479a8,'immediate',1),(0x800479ac,'target','8006c728'),(0x8006658c,'displacement',0x508),(0x800665b8,'displacement',0x72),(0x8006c744,'displacement',0x508),(0x8006c768,'displacement',0x18d4),(0x8006c790,'displacement',0x18d4),(0x8006c794,'displacement',0x18d6),(0x8006c7b8,'displacement',0x18d6),(0x8006c7bc,'target','8006cc7c')):
            self.assertEqual(r[pc][field],value)
        self.assertEqual([x['value'] for x in self.reports[0]['constants']],[0.9599999785423279,4503601774854144,0.9599999785423279,4503601774854144])
        self.assertNotIn(0x8006c7c0,r)


if __name__ == '__main__':
    unittest.main()
