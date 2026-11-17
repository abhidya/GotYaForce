"""Integrity of already-recorded matched8b480 text, NOT a new retail oracle.

Reads only checked-in C/header and registry text. No archive selection, DOL,
compiler, verify.py, source-global pointer dereference or extraction is used.
"""
import copy
import hashlib
import json
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[3]
DIGEST = 'fefc8366d0fc68371afbec1e38cd03a0e947bb8c008c1c70d8223e52fef8473c'
EXPECTED_ROWS = [
    ('8008b480', '806d8394', 'lwz r3, -0x7c6c(r13)'),
    ('8008b484', '886300eb', 'lbz r3, 0xeb(r3)'),
    ('8008b488', '4e800020', 'blr'),
]
RELOCATION = dict(offset='0x000', type='R_PPC_EMB_SDA21',
                  symbol='PTR_DAT_80433934', retail_addr='0x80433934',
                  retail_how='sda', symbol_source='registry+name')


def require(ok, message):
    if not ok:
        raise ValueError(message)


def validate_record(source, entry):
    """Reject changed words, operands, body, identity or recorded relocation."""
    header, body = source.split(' */\n', 1)
    rows = re.findall(r'^ \*   ([0-9a-f]{8})  ([0-9a-f]{8})  (.+)$', header, re.M)
    require(rows == EXPECTED_ROWS, 'recorded instruction words/operands changed')
    # Independently decode the two recorded D-form words, not their prose.
    def d_form(word):
        immediate = word & 0xffff
        return (word >> 26, (word >> 21) & 31, (word >> 16) & 31,
                immediate if immediate < 0x8000 else immediate - 0x10000)
    require(d_form(int(rows[0][1], 16)) == (32, 3, 13, -31852), 'lwz operands')
    require(d_form(int(rows[1][1], 16)) == (34, 3, 3, 235), 'lbz operands')
    require(int(rows[2][1], 16) == 0x4e800020, 'blr encoding')
    require(0x8043b5a0 - 31852 == 0x80433934, 'SDA arithmetic')
    require('_SDA_BASE_ (r13) = 0x8043b5a0' in header, 'recorded SDA base')
    require('+0x000 R_PPC_EMB_SDA21  PTR_DAT_80433934         retail 0x80433934  (sda, via registry+name)' in header,
            'recorded header relocation')
    require(hashlib.sha256(body.encode()).hexdigest() == DIGEST, 'C-body hash')
    require(f'source sha256    : {DIGEST}' in header, 'header hash')
    require(entry['source_sha256'] == DIGEST, 'registry hash')
    require(entry['name'] == 'zz_008b480_' and entry['addr'] == '0x8008b480'
            and entry['insns'] == 3 and entry['src'] == 'game/zz_008b480_.c'
            and entry['sym'] == 'f' and entry['shape'] == 'lwz lbz blr', 'registry identity')
    # False denotes a verified relocation-masked match in this corpus. It is
    # not treated as fresh matching or as unverified/compile-only evidence.
    require(entry['exact_bytes'] is False and 'exact_bytes      : false' in header,
            'recorded relocation-masked match')
    require(entry['data_relocs_verified'] == [RELOCATION], 'registry relocation')
    require(entry['globals'] == ['PTR_DAT_80433934 @ 0x80433934'], 'registry global')
    require('char pad_0[0xeb];' in body and 'unsigned char  field_eb;' in body
            and 'return PTR_DAT_80433934->field_eb;' in body, 'C leaf layout')


class RecordedBurstLeafEvidence(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        registry = json.loads((ROOT / 'src-match/matched.json').read_text())
        cls.entry = next(e for e in registry['functions'] if e['name'] == 'zz_008b480_')
        cls.source = (ROOT / 'src-match/game/zz_008b480_.c').read_text()

    def test_existing_record_integrity(self):
        validate_record(self.source, self.entry)

    def test_changed_instruction_offset_or_operands_refused(self):
        for before, after in [('886300eb', '886300ec'), ('0xeb(r3)', '0xec(r3)'),
                              ('806d8394', '806d8398'), ('8008b488', '8008b48c'),
                              ('4e800020', '60000000')]:
            with self.subTest(before=before), self.assertRaisesRegex(ValueError, 'words/operands'):
                validate_record(self.source.replace(before, after), self.entry)

    def test_changed_body_or_recorded_hash_refused(self):
        for source in [self.source.replace('pad_0[0xeb]', 'pad_0[0xec]'),
                       self.source.replace('return PTR_DAT_80433934', 'return PTR_DAT_80433938')]:
            with self.assertRaisesRegex(ValueError, 'C-body hash'):
                validate_record(source, self.entry)
        with self.assertRaisesRegex(ValueError, 'header hash'):
            validate_record(self.source.replace(DIGEST, '0' * 64), self.entry)
        entry = copy.deepcopy(self.entry)
        entry['source_sha256'] = '0' * 64
        with self.assertRaisesRegex(ValueError, 'registry hash'):
            validate_record(self.source, entry)

    def test_changed_recorded_global_and_sda_refused(self):
        for before, after, failure in [('0x8043b5a0', '0x8043b5a4', 'SDA base'),
                                      ('retail 0x80433934', 'retail 0x80433938', 'header relocation')]:
            with self.subTest(before=before), self.assertRaisesRegex(ValueError, failure):
                validate_record(self.source.replace(before, after), self.entry)
        for field, value in [('symbol', 'PTR_DAT_80433938'), ('retail_addr', '0x80433938'),
                             ('offset', '0x004'), ('type', 'R_PPC_ADDR32')]:
            entry = copy.deepcopy(self.entry)
            entry['data_relocs_verified'][0][field] = value
            with self.subTest(field=field), self.assertRaisesRegex(ValueError, 'registry relocation'):
                validate_record(self.source, entry)
        entry = copy.deepcopy(self.entry)
        entry['globals'] = ['PTR_DAT_80433938 @ 0x80433938']
        with self.assertRaisesRegex(ValueError, 'registry global'):
            validate_record(self.source, entry)


if __name__ == '__main__':
    unittest.main()
