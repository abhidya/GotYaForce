#!/usr/bin/env python3
"""Synthetic-only field, allowlist and refusal checks; no original inputs."""
import hashlib
import struct
import unittest
from unittest.mock import patch
import read_archived_actor_traversal_evidence as a


class FakeDB:
    def __init__(self,raw): self.raw,self.calls=raw,[]
    def chain(self,*args):
        self.calls.append(args)
        return self.raw,[]


class EvidenceTests(unittest.TestCase):
    def decode(self,word): return a.decode_selected(word,0x80001000)
    def test_forward_call(self):
        self.assertEqual(self.decode((18<<26)|0x101),dict(mnemonic='bl',target='80001100',AA=0))
    def test_backward_branch(self):
        self.assertEqual(self.decode((18<<26)|0x3fffffc),dict(mnemonic='b',target='80000ffc',AA=0))
    def test_absolute_branch(self):
        self.assertEqual(self.decode((18<<26)|0x102),dict(mnemonic='b',target='00000100',AA=1))
    def test_conditional(self):
        self.assertEqual(self.decode((16<<26)|(12<<21)|(2<<16)|0xfffc),
                         dict(mnemonic='bc',BO=12,BI=2,LK=0,target='80000ffc',AA=0))
    def test_signed_immediate(self):
        self.assertEqual(self.decode((11<<26)|(3<<16)|65535)['immediate'],-1)
        self.assertEqual(self.decode((10<<26)|(3<<16)|65535)['immediate'],65535)
    def test_register_compare(self):
        self.assertEqual(self.decode((31<<26)|(3<<16)|(4<<11)),
                         dict(mnemonic='cmp',BF=0,L=0,rA=3,rB=4))
        self.assertEqual(self.decode((31<<26)|(3<<16)|(4<<11)|(32<<1))['mnemonic'],'cmpl')
    def test_short_load(self):
        self.assertEqual(self.decode((42<<26)|(6<<21)|(29<<16)|0x1d68),
                         dict(mnemonic='lha',rD=6,rA=29,displacement=0x1d68))
    def test_multiply_immediate(self):
        self.assertEqual(self.decode((7<<26)|(4<<21)|(5<<16)|48),
                         dict(mnemonic='mulli',rD=4,rA=5,immediate=48))
    def test_shift_mask(self):
        self.assertEqual(self.decode((21<<26)|(3<<21)|(10<<11)|(21<<1)),
                         dict(mnemonic='rlwinm',rS=3,rA=0,SH=10,MB=0,ME=21,Rc=0))
    def test_sign_extend_record(self):
        self.assertEqual(self.decode((31<<26)|(7<<21)|(922<<1)|1),
                         dict(mnemonic='extsh',rS=7,rA=0,Rc=1))
    def test_ps_add(self):
        self.assertEqual(self.decode((4<<26)|(6<<21)|(2<<16)|(4<<11)|(21<<1)),
                         dict(mnemonic='ps_add',fD=6,fA=2,fB=4))
    def test_ps_neg(self):
        self.assertEqual(self.decode((4<<26)|(2<<21)|(5<<11)|(40<<1)),
                         dict(mnemonic='ps_neg',fD=2,fB=5))
    def test_ps_sum1(self):
        self.assertEqual(self.decode((4<<26)|(5<<21)|(1<<16)|(5<<11)|(5<<6)|(11<<1)),
                         dict(mnemonic='ps_sum1',fD=5,fA=1,fC=5,fB=5))
    def test_quantized_short_load(self):
        self.assertEqual(self.decode((56<<26)|(1<<21)|(1<<16)|(1<<15)|(5<<12)|8),
                         dict(mnemonic='psq_l',fD=1,rA=1,displacement=8,W=1,I=5))
    def test_float_convert(self):
        self.assertEqual(self.decode((63<<26)|(5<<21)|(1<<11)|(12<<1)),dict(mnemonic='frsp',fD=5,fB=1))
        self.assertEqual(self.decode((63<<26)|(1<<11)|(15<<1)),dict(mnemonic='fctiwz',fD=0,fB=1))
    def test_double_load(self):
        self.assertEqual(self.decode((50<<26)|(1<<21)|(2<<16)|0xe610),
                         dict(mnemonic='lfd',fD=1,rA=2,displacement=-6640))
    def test_unselected(self):
        self.assertIsNone(self.decode(0))
    def test_invalid_word(self):
        for word in (-1,1<<32,True,'0'):
            with self.assertRaises(a.c.FormatError): self.decode(word)
    def test_invalid_pc(self):
        for pc in (-1,1,1<<32,True):
            with self.assertRaises(a.c.FormatError): a.decode_selected(0,pc)
    def test_range_allowlist_before_read(self):
        with self.assertRaises(a.c.FormatError): a.range_evidence(None,21,0x800457d8,96)
    def test_range_hash(self):
        with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(bytes(100)),21,0x800457d4,100)
    def test_synthetic_range(self):
        raw=struct.pack('>I',0x4e800020); db=FakeDB(raw)
        with patch.object(a,'RANGES',((0x800457d4,4,hashlib.sha256(raw).hexdigest()),)):
            got=a.range_evidence(db,21,0x800457d4,4)
            self.assertEqual(got['instructions'],[dict(address='800457d4',mnemonic='blr')])
            self.assertEqual(db.calls,[(21,0x800457d4-a.TEXT_START,4,a.TEXT_LENGTH)])
    def test_synthetic_width_mismatch(self):
        raw=bytes(8)
        with patch.object(a,'RANGES',((0x800457d4,4,hashlib.sha256(raw).hexdigest()),)):
            with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(raw),21,0x800457d4,4)
    def test_constant_allowlist_before_read(self):
        with self.assertRaises(a.c.FormatError): a.constant_evidence(None,0x8043707c)
    def test_constants(self):
        self.assertEqual(a.constant_evidence(FakeDB(struct.pack('>f',20)),0x80437098)['value'],20)
        self.assertEqual(a.constant_evidence(FakeDB(struct.pack('>d',1)),0x8043d030)['value'],1)
        with self.assertRaises(a.c.FormatError): a.constant_evidence(FakeDB(bytes(4)),0x80437098)
    def test_authentication_first(self):
        with self.assertRaises(a.c.FormatError): a.inspect(bytes(32),'0'*64)


if __name__=='__main__': unittest.main()
