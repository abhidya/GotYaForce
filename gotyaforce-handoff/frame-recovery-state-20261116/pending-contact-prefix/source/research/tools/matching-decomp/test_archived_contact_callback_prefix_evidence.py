#!/usr/bin/env python3
"""Synthetic admission controls and optional existing-local-snapshot checks."""
import copy
import hashlib
from pathlib import Path
import unittest
from unittest.mock import patch
import read_archived_contact_callback_prefix_evidence as a
ROOT = Path(__file__).resolve().parents[3]
SNAPSHOTS = ROOT / 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db'

class FakeDB:
    def __init__(self, raw=b''): self.raw, self.calls = raw, []
    def chain(self, *args): self.calls.append(args); return self.raw, []

class SyntheticTests(unittest.TestCase):
    def test_extent_has_independent_index_bounds(self):
        lines = (ROOT / 'research/decomp/ghidra-export/_index.tsv').read_text().splitlines()
        i = next(i for i, row in enumerate(lines) if row.startswith('8008a65c\t'))
        self.assertTrue(lines[i].endswith('\tchunk_0013.c'))
        self.assertTrue(lines[i + 1].startswith('8008aa40\t'))
        self.assertEqual(a.RANGE[:2], (0x8008a65c, 996))
        self.assertEqual(len(a.INDIRECT_CALLS), 2)

    def test_unselected_ranges_and_mappings_refuse_before_read(self):
        for address, width in ((0x8008a658,996),(0x8008a660,992),(0x8008a65c,1000),(0x8008a65c,0),(True,996),(float(a.RANGE[0]),996),(a.RANGE[0],996.0),(0x80436250,2),(0x8008aa40,996),(0x8020b7a8,996)):
            db = FakeDB()
            with self.assertRaises(a.c.FormatError): a.range_evidence(db,a.TEXT_MAPPING,address,width)
            self.assertEqual(db.calls,[])
        for i,value in enumerate(a.TEXT_MAPPING):
            mapping=list(a.TEXT_MAPPING);mapping[i]=value+1 if type(value)is int else 'wrong'
            db=FakeDB()
            with self.assertRaises(a.c.FormatError): a.range_evidence(db,tuple(mapping),*a.RANGE[:2])
            self.assertEqual(db.calls,[])

    def test_wrong_bytes_never_decode(self):
        with patch.object(a,'decode_selected') as decode:
            for n in (0,995,996,997):
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
            row=a.decode_selected(word,0x10000000);self.assertEqual(encode(row),word)
            for bit in range(32):
                trials+=1;changed=word^(1<<bit)
                try:result=a.decode_selected(changed,0x10000000)
                except a.c.FormatError:continue
                if result is not None and result['mnemonic']in('addi','sth','blr'):
                    self.assertNotEqual(result,row);self.assertEqual(encode(result),changed)
        self.assertEqual(trials,96)

    def test_reused_fctiwz_fields_and_bctrl(self):
        for fd in range(32):
            for fb in range(32):
                word=(63<<26)|(fd<<21)|(fb<<11)|(15<<1)
                row=a.decode_selected(word,0x10000000)
                self.assertEqual(row,dict(mnemonic='fctiwz',fD=fd,fB=fb,Rc=0))
                for change in (1,1<<16):
                    with self.assertRaises(a.c.FormatError):a.decode_selected(word|change,0x10000000)
        row=a.decode_selected(0x4e800421,0x10000000)
        self.assertEqual(row,dict(mnemonic='bctrl',BO=20,BI=0,BH=0,LK=1))
        for word,pc in ((True,0),(-1,0),(1<<32,0),(0,True),(0,-4),(0,1),(0,1<<32)):
            with self.assertRaises(a.c.FormatError):a.decode_selected(word,pc)

@unittest.skipUnless(all((SNAPSHOTS/name).is_file() for name in ('db.3.gbf','db.4.gbf')),'existing local snapshots unavailable')
class ArchiveTests(unittest.TestCase):
    def test_both_snapshots_exact_scope_and_stores(self):
        for name in ('db.3.gbf','db.4.gbf'):
            data=(SNAPSHOTS/name).read_bytes();selected=[];original=a.c.GBF.chain
            def track(db,*args):
                if args==(21,a.RANGE[0]-a.TEXT_MAPPING[0],996,a.TEXT_MAPPING[-2]): selected.append(args)
                return original(db,*args)
            with patch.object(a.c.GBF,'chain',track):result=a.inspect(data,hashlib.sha256(data).hexdigest())
            self.assertEqual(len(selected),1)
            facts=result['ranges'][0];self.assertEqual(facts['represented_instructions'],249)
            self.assertTrue(facts['semantics']['state_ge3_returns'])
            self.assertEqual(facts['semantics']['state1_copy_order'],['load30','load34','store3c','store40','load38','store44','load60']);self.assertFalse(facts['semantics']['callee_bodies_selected'])
            self.assertEqual(result['selection']['data_cells'],0)

    def test_damage_and_operand_drift_refuse(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes();digest=hashlib.sha256(data).hexdigest()
        with patch.object(a,'range_evidence') as selected:
            with self.assertRaises(a.c.FormatError):a.inspect(data,'0'*64)
            selected.assert_not_called()
        original=a.c.GBF.chain
        def damage(db,*args):
            raw,spans=original(db,*args)
            if args==(21,a.RANGE[0]-a.TEXT_MAPPING[0],996,a.TEXT_MAPPING[-2]):raw=bytes([raw[0]^1])+raw[1:]
            return raw,spans
        with patch.object(a.c.GBF,'chain',damage):
            with self.assertRaisesRegex(a.c.FormatError,'digest'):a.inspect(data,digest)
        original_decode=a.decode_selected
        def drift(word,pc):
            row=copy.deepcopy(original_decode(word,pc))
            if pc==a.RANGE[0]:row['displacement']=1
            return row
        with patch.object(a,'decode_selected',drift):
            with self.assertRaisesRegex(a.c.FormatError,'operand'):a.inspect(data,digest)

    def test_semantic_prefix_mutations_refuse(self):
        data=(SNAPSHOTS/'db.3.gbf').read_bytes();captured=[];original=a.summarize
        def capture(rows):captured.extend(copy.deepcopy(rows));return original(rows)
        with patch.object(a,'summarize',capture):a.inspect(data,hashlib.sha256(data).hexdigest())
        for pc,key,value in [('8008a67c','displacement',36),('8008a6f0','mnemonic','lha'),
                             ('8008a6f4','displacement',44),('8008a874','displacement',64),
                             ('8008a714','target','8008a71c'),('8008aa04','displacement',19),
                             ('8008a6c4','mnemonic','or'),('8008a6d0','SH',11),
                             ('8008a9fc','BI',0)]:
            rows=copy.deepcopy(captured);row=next(r for r in rows if r['address']==pc);row[key]=value
            with self.assertRaises(a.c.FormatError):a.summarize(rows)

if __name__=='__main__':unittest.main()
