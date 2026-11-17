#!/usr/bin/env python3
"""Synthetic decoder/authentication tests; no archived instruction execution."""
import hashlib
import struct
import unittest
from unittest.mock import patch
import read_archived_terrain_matrix_evidence as t


class FakeDB:
    def __init__(self, raw): self.raw, self.calls = raw, []
    def chain(self, *args):
        self.calls.append(args)
        return self.raw, []


class EvidenceTests(unittest.TestCase):
    def test_xoris(self):
        self.assertEqual(t.decode_selected((27 << 26) | (7 << 21) | (4 << 16) | 0x8000, 0),
                         dict(mnemonic='xoris', rS=7, rA=4, immediate=0x8000))

    def test_lfsx(self):
        self.assertEqual(t.decode_selected((31 << 26) | (6 << 21) | (27 << 16) | (9 << 11) | (535 << 1), 0),
                         dict(mnemonic='lfsx', fD=6, rA=27, rB=9))

    def test_fcmpo(self):
        self.assertEqual(t.decode_selected((63 << 26) | (3 << 23) | (4 << 16) | (30 << 11) | (32 << 1), 0),
                         dict(mnemonic='fcmpo', BF=3, fA=4, fB=30))

    def test_fmadds_operand_order(self):
        self.assertEqual(t.decode_selected((59 << 26) | (30 << 21) | (3 << 16) | (7 << 11) | (1 << 6) | (29 << 1), 0),
                         dict(mnemonic='fmadds', fD=30, fA=3, fC=1, fB=7))

    def test_signed_mask_and_sentinel_decoding(self):
        self.assertEqual(t.decode_selected(0x7c840774, 0)['mnemonic'], 'extsb')
        self.assertEqual(t.decode_selected((11 << 26) | 0xffff, 0)['immediate'], -1)
        signed = t.traversal.signed(0xc0, 8)
        self.assertEqual([bool(signed & (1 << (i+6))) for i in range(4)], [True]*4)
        self.assertNotEqual(t.traversal.signed(0xfe, 8), -1)

    def test_query_branch(self):
        pc, target = 0x8004723c, 0x8003d6e4
        word = (18 << 26) | ((target-pc) & 0x3fffffc) | 1
        self.assertEqual(t.decode_selected(word, pc), dict(mnemonic='bl', target='8003d6e4', AA=0))

    def test_invalid_inputs(self):
        for word in (-1, 1 << 32, True, '0'):
            with self.assertRaises(t.c.FormatError): t.decode_selected(word, 0)
        for pc in (-1, 1, 1 << 32, True):
            with self.assertRaises(t.c.FormatError): t.decode_selected(0, pc)

    def test_fixed_range_contract(self):
        self.assertEqual([(a,n) for a,n,_ in t.RANGES], [(0x80047164,480),(0x80047344,36)])
        with self.assertRaises(t.c.FormatError): t.range_evidence(None,21,0x80047168,476)
        with self.assertRaises(t.c.FormatError): t.range_evidence(None,22,0x80047164,480)
        with self.assertRaises(t.c.FormatError): t.range_evidence(FakeDB(bytes(480)),21,0x80047164,480)

    def test_synthetic_tail_load_store_order(self):
        words=[0xc0231d60,0xc002867c,0xec010032,0xd0031d60,
               0xc0231d58,0xc0031d60,0xec01002a,0xd0031d58,0x4e800020]
        raw=struct.pack('>9I',*words);db=FakeDB(raw)
        with patch.object(t,'RANGES',((0x80047344,36,hashlib.sha256(raw).hexdigest()),)):
            facts=t.range_evidence(db,21,0x80047344,36)['instructions']
        self.assertEqual([f['mnemonic'] for f in facts],['lfs','lfs','fmuls','stfs','lfs','lfs','fadds','stfs','blr'])
        self.assertEqual([facts[i]['displacement'] for i in (0,3,4,5,7)],[0x1d60,0x1d60,0x1d58,0x1d60,0x1d58])
        self.assertEqual(db.calls,[(21,0x80047344-t.TEXT_START,36,t.TEXT_LENGTH)])

    def test_width_rejected_independently_of_hash(self):
        raw=bytes(8)
        with patch.object(t,'RANGES',((0x80047344,4,hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaises(t.c.FormatError):t.range_evidence(FakeDB(raw),21,0x80047344,4)

    def test_constants(self):
        for address,value in ((0x8043709c,0.800000011920929),(0x804370a4,2.0),(0x804370b8,4503601774854144.0)):
            raw=bytes.fromhex(t.TARGETS[address]);db=FakeDB(raw)
            result=t.constant_evidence(db,address)
            self.assertEqual(result['value'],value)
            self.assertEqual(db.calls,[(263,address-0x80436a20,len(raw),27360)])
            for bad in (raw[:-1],raw+b'\0',bytes(len(raw))):
                with self.assertRaises(t.c.FormatError):t.constant_evidence(FakeDB(bad),address)
        with self.assertRaises(t.c.FormatError):t.constant_evidence(None,0x804370a8)

    def test_authentication_first(self):
        with self.assertRaises(t.c.FormatError):t.inspect(bytes(32),'0'*64)


if __name__=='__main__':unittest.main()
