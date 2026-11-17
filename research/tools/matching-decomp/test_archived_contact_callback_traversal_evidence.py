#!/usr/bin/env python3
"""Synthetic admission controls and optional existing-local-snapshot checks."""
import copy
import hashlib
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_contact_callback_traversal_evidence as a
ROOT = Path(__file__).resolve().parents[3]
SNAPSHOTS = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'

class FakeDB:
    def __init__(self, raw=b''): self.raw, self.calls = raw, []
    def chain(self, *args): self.calls.append(args); return self.raw, []

class SyntheticTests(unittest.TestCase):
    def test_extent_has_independent_index_bounds(self):
        lines = (ROOT / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        i = next(i for i, row in enumerate(lines) if row.startswith('80089aec\t'))
        self.assertTrue(lines[i].endswith('\tchunk_0013.c'))
        self.assertTrue(lines[i + 1].startswith('80089c00\t'))
        self.assertEqual(a.RANGE[:2], (0x80089aec, 276))
        self.assertEqual(len(a.CALL_SITES), 3)

    def test_unselected_ranges_and_mappings_refuse_before_read(self):
        for address, width in ((0x80089ae8,276),(0x80089af0,272),(0x80089aec,280),(0x80089aec,0),(True,276),(float(a.RANGE[0]),276),(a.RANGE[0],276.0),(0x80436250,2),(0x8008a28c,48)):
            db = FakeDB()
            with self.assertRaises(a.c.FormatError): a.range_evidence(db,a.TEXT_MAPPING,address,width)
            self.assertEqual(db.calls,[])
        for i,value in enumerate(a.TEXT_MAPPING):
            mapping=list(a.TEXT_MAPPING);mapping[i]=value+1 if type(value)is int else 'wrong'
            db=FakeDB()
            with self.assertRaises(a.c.FormatError): a.range_evidence(db,tuple(mapping),*a.RANGE[:2])
            self.assertEqual(db.calls,[])

    def test_wrong_bytes_never_decode(self):
        with patch.object(a.base,'decode_selected') as decode:
            for n in (0,275,276,277):
                with self.assertRaises(a.c.FormatError): a.range_evidence(FakeDB(bytes(n)),a.TEXT_MAPPING,*a.RANGE[:2])
            decode.assert_not_called()

    def test_authentication_before_selection(self):
        with patch.object(a.c,'inspect',side_effect=a.c.FormatError('stop')) as auth,patch.object(a.c,'GBF') as db,patch.object(a,'range_evidence') as selected:
            with self.assertRaises(a.c.FormatError): a.inspect(b'bad','bad')
            auth.assert_called_once();db.assert_not_called();selected.assert_not_called()

    def test_synthetic_instruction_inverse_bit_controls(self):
        # Invented register/displacement operands, not original-body fixtures.
        words=[(14<<26)|(9<<21)|37,(44<<26)|(7<<21)|(12<<16)|0xff9c,0x4e800020]
        def encode(row):
            n=row['mnemonic']
            if n=='addi':return(14<<26)|(row['rD']<<21)|(row['rA']<<16)|(row['immediate']&65535)
            if n=='sth':return(44<<26)|(row['rS']<<21)|(row['rA']<<16)|(row['displacement']&65535)
            if n=='blr':return(19<<26)|(row['BO']<<21)|(row['BI']<<16)|(row['BH']<<11)|(16<<1)|row['LK']
            return None
        trials=0
        for word in words:
            row=a.base.decode_selected(word,0x10000000);self.assertEqual(encode(row),word)
            for bit in range(32):
                trials+=1;changed=word^(1<<bit)
                try:result=a.base.decode_selected(changed,0x10000000)
                except a.c.FormatError:continue
                if result is not None and result['mnemonic']in('addi','sth','blr'):
                    self.assertNotEqual(result,row);self.assertEqual(encode(result),changed)
        self.assertEqual(trials,96)

@unittest.skipUnless(all((SNAPSHOTS/name).is_file() for name in ('db.3.gbf','db.4.gbf')),'existing local snapshots unavailable')
class ArchiveTests(unittest.TestCase):
    def test_both_snapshots_exact_scope_and_stores(self):
        for name in ('db.3.gbf','db.4.gbf'):
            data=(SNAPSHOTS/name).read_bytes();selected=[];original=a.c.GBF.chain
            def track(db,*args):
                if args==(21,a.RANGE[0]-a.TEXT_MAPPING[0],276,a.TEXT_MAPPING[-2]): selected.append(args)
                return original(db,*args)
            with patch.object(a.c.GBF,'chain',track):result=a.inspect(data,hashlib.sha256(data).hexdigest())
            self.assertEqual(len(selected),1)
            facts=result['ranges'][0];self.assertEqual(facts['represented_instructions'],69)
            self.assertEqual(facts['semantics']['slot_groups'],list(range(49,55)))
            self.assertTrue(facts['semantics']['active_callback_unconditional']);self.assertFalse(facts['semantics']['pause_mask_read'])
            self.assertEqual(result['selection']['data_cells'],0)

    def test_damage_and_operand_drift_refuse(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes();digest=hashlib.sha256(data).hexdigest()
        with patch.object(a,'range_evidence') as selected:
            with self.assertRaises(a.c.FormatError):a.inspect(data,'0'*64)
            selected.assert_not_called()
        original=a.c.GBF.chain
        def damage(db,*args):
            raw,spans=original(db,*args)
            if args==(21,a.RANGE[0]-a.TEXT_MAPPING[0],276,a.TEXT_MAPPING[-2]):raw=bytes([raw[0]^1])+raw[1:]
            return raw,spans
        with patch.object(a.c.GBF,'chain',damage):
            with self.assertRaisesRegex(a.c.FormatError,'digest'):a.inspect(data,digest)
        original_decode=a.base.decode_selected
        def drift(word,pc):
            row=copy.deepcopy(original_decode(word,pc))
            if pc==a.RANGE[0]:row['displacement']=1
            return row
        with patch.object(a.base,'decode_selected',drift):
            with self.assertRaisesRegex(a.c.FormatError,'operand'):a.inspect(data,digest)

if __name__=='__main__':unittest.main()
