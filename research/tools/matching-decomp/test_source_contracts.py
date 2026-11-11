"""Guard explicit pointer flow in refined matched callers (not a retail oracle)."""
import hashlib
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[3]


class RefinedSourceContracts(unittest.TestCase):
    def test_pointer_arguments_and_provenance(self):
        required = {
            'zz_01ca918_': ('void f(void *p0)', 'FUN_8000540c(void *, int, int)', 'FUN_8000540c(p0,'),
            'zz_0269590_': ('void f(void * p0)', 'FUN_8000540c(void *, int, int)', 'FUN_8000540c(p0,'),
            'gnt4-HSD_FObjRemove': ('void f(void *p0)', 'FUN_8024a48c(void *)', 'FUN_8024a48c(p0);'),
            'gnt4-HSD_JObjAnimAll': ('void f(void * p0)', 'FUN_8024ebc8(void *)', 'FUN_8024ebc8(p0);'),
            'gnt4-HSD_TlutFree-bl': ('void f(void *p0)', 'FUN_8025ce98(void *, int)', 'FUN_8025ce98(p0,'),
        }
        entries = {e['name']: e for e in json.loads((ROOT / 'src-match/matched.json').read_text())['functions']}
        for name, contracts in required.items():
            with self.subTest(name=name):
                entry = entries[name]
                header, body = (ROOT / 'src-match' / entry['src']).read_text().split(' */\n', 1)
                for contract in contracts:
                    self.assertIn(contract, body)
                digest = hashlib.sha256(body.encode()).hexdigest()
                self.assertEqual(entry['source_sha256'], digest)
                self.assertIn(digest, header)
                self.assertIn('Source refined after generation', header)
                self.assertTrue(entry['source_refinement']['retail_evidence'])
                self.assertGreater(entry['permuter_steps'], 0)


if __name__ == '__main__':
    unittest.main()
