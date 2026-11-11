"""Portable expression controls for mechanically seeded bit masks."""
import unittest
from seed_cfg import Arg, Lifter, SeedFail, Bin, Cmp, Const, render


def evaluate(e, value):
    if e.k == "arg":
        return value
    if e.k == "const":
        return e.a[0]
    op, a, b = e.a
    a, b = evaluate(a, value), evaluate(b, value)
    return {"&": lambda: a & b, "<<": lambda: a << b,
            ">>": lambda: a >> b}[op]() & 0xffffffff


class NonRotatingMaskTests(unittest.TestCase):
    def test_all_1024_masks_against_bit_index_definition(self):
        for mb in range(32):
            for me in range(32):
                with self.subTest(mb=mb, me=me):
                    e = Lifter.rlwinm(None, Arg(0), {"sh": 0, "mb": mb, "me": me})
                    # PowerPC bit zero is the MSB; wrap means the union of ends.
                    indices = range(mb, me + 1) if mb <= me else list(range(mb, 32)) + list(range(me + 1))
                    mask = sum(1 << (31 - bit) for bit in indices)
                    for value in (0, 0xffffffff, 0x80000000, 0x55555555, 0xaaaaaaaa, 0x12345678):
                        self.assertEqual(evaluate(e, value), value & mask)

    def test_single_bit_25_is_numeric_bit_6(self):
        e = Lifter.rlwinm(None, Arg(0), {"sh": 0, "mb": 25, "me": 25})
        self.assertEqual(evaluate(e, 0xffffffff), 0x40)

    def test_unsupported_rotated_mask_stays_refused(self):
        with self.assertRaises(SeedFail):
            Lifter.rlwinm(None, Arg(0), {"sh": 3, "mb": 5, "me": 12})


class SignedMaskRenderingTests(unittest.TestCase):
    def test_signed_order_casts_high_bit_mask(self):
        mask = Bin("&", Arg(0), Const(0x80000000))
        for op in ("<", "<=", ">", ">="):
            self.assertEqual(render(Cmp(op, mask, Const(0), True), {}),
                             "(int)(p0 & 0x80000000) %s 0" % op)
            self.assertEqual(render(Cmp(op, Const(0), mask, True), {}),
                             "0 %s (int)(p0 & 0x80000000)" % op)

    def test_unsigned_order_preserves_unsigned_mask(self):
        mask = Bin("&", Arg(0), Const(0x80000000))
        self.assertEqual(render(Cmp("<", mask, Const(0), False), {}),
                         "(p0 & 0x80000000) < 0")

    def test_low_bit_mask_and_equality_do_not_need_cast(self):
        self.assertEqual(render(Cmp("<", Bin("&", Arg(0), Const(0x40)), Const(0), True), {}),
                         "(p0 & 0x40) < 0")
        self.assertEqual(render(Cmp("==", Bin("&", Arg(0), Const(0x80000000)), Const(0), True), {}),
                         "(p0 & 0x80000000) == 0")

    def test_float_comparison_is_not_cast_to_integer(self):
        self.assertEqual(render(Cmp("<", Const(1.5), Const(2.0), True), {}), "1.5f < 2.0f")
