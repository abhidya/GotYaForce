#!/usr/bin/env python3
"""Synthetic-only structural and instruction-field checks; no original inputs."""
import unittest
import read_archived_world_matrix_evidence as w

class FakeDB:
    def __init__(self,raw): self.raw=raw
    def chain(self,*args): return self.raw,[]

class EvidenceTests(unittest.TestCase):
    def test_scalar_load(self):
        self.assertEqual(w.decode_float(0xc03f0000),dict(mnemonic='lfs',fD=1,rA=31,displacement=0))
    def test_scalar_store(self):
        self.assertEqual(w.decode_float(0xd0430014),dict(mnemonic='stfs',fD=2,rA=3,displacement=20))
    def test_muls0(self):
        self.assertEqual(w.decode_float(0x11860018),dict(mnemonic='ps_muls0',fD=12,fA=6,fC=0,fB=0))
    def test_madds1(self):
        self.assertEqual(w.decode_float(0x11bf685e),dict(mnemonic='ps_madds1',fD=13,fA=31,fC=1,fB=13))
    def test_negative_fused(self):
        self.assertEqual(w.decode_float(0x114a48bc),dict(mnemonic='ps_nmsub',fD=10,fA=10,fC=2,fB=9))
    def test_merges(self):
        self.assertEqual(w.decode_float(0x116a4c60),dict(mnemonic='ps_merge01',fD=11,fA=10,fB=9))
        self.assertEqual(w.decode_float(0x10ea04a0)['mnemonic'],'ps_merge10')
    def test_fres(self):
        self.assertEqual(w.decode_float(0xed601830),dict(mnemonic='fres',fD=11,fB=3))
    def test_store_single(self):
        self.assertEqual(w.decode_float(0xf003800c),dict(mnemonic='psq_st',fD=0,rA=3,displacement=12,W=1,I=0))
    def test_negative_offset(self):
        self.assertEqual(w.decode_float(0xe0030ffc)['displacement'],-4)
    def test_bad_words(self):
        for word in (-1,1<<32,True,0,0x11860019):
            with self.assertRaises(w.c.FormatError): w.decode_float(word)
    def test_range_allowlist(self):
        with self.assertRaises(w.c.FormatError): w.range_evidence(None,21,0x8020af60,4)
    def test_range_hash(self):
        with self.assertRaises(w.c.FormatError): w.range_evidence(FakeDB(bytes(204)),21,0x8020af5c,204)
    def test_constant_allowlist(self):
        with self.assertRaises(w.c.FormatError): w.constant_evidence(None,0x80435ca8)
    def test_constant_bits(self):
        with self.assertRaises(w.c.FormatError): w.constant_evidence(FakeDB(bytes(4)),0x8043ca68)
        self.assertEqual(w.constant_evidence(FakeDB(bytes.fromhex('3f800000')),0x8043ca68)['value'],1)
    def test_auth_first(self):
        with self.assertRaises(w.c.FormatError): w.inspect(bytes(32),'0'*64)

if __name__=='__main__': unittest.main()
