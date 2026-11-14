"""An accuracy interval does not determine the SDK Normalize result at s=1.

These are hypothetical seeds, not asserted Gekko/emulator outputs. This is a
bounded independent rational proof, not a reciprocal-estimate implementation.
No archive, external implementation, lookup table or runtime code is imported.
"""
from fractions import Fraction as F
import struct
import unittest


def power2(n):
    return F(2**n) if n >= 0 else F(1, 2**(-n))


def rn32(value):
    """Exact ties-even rounding for the finite normal proof operands only."""
    if value == 0:
        return F(0)
    sign, magnitude = (-1 if value < 0 else 1), abs(value)
    exponent = magnitude.numerator.bit_length() - magnitude.denominator.bit_length()
    if magnitude < power2(exponent):
        exponent -= 1
    assert -126 <= exponent <= 126
    quantum = power2(exponent - 23)
    scaled = magnitude / quantum
    whole, remainder = divmod(scaled.numerator, scaled.denominator)
    twice = 2 * remainder
    if twice > scaled.denominator or (twice == scaled.denominator and whole % 2):
        whole += 1
    return sign * whole * quantum


def bits(value):
    return struct.pack('>f', float(value)).hex()


def normalize_refinement(seed):
    assert abs(seed - 1) <= F(1, 4096)
    square = rn32(seed * seed)
    half = rn32(seed / 2)
    correction = -rn32(square - 3)
    refined = rn32(correction * half)
    return seed, square, half, correction, refined


class NormalizeBoundTests(unittest.TestCase):
    def test_both_hypothetical_seeds_satisfy_even_the_stronger_bound(self):
        for seed in (F(1), 1 - F(1, 4096)):
            self.assertLessEqual(abs(seed - 1), F(1, 4096))
            self.assertEqual(rn32(seed), seed)

    def test_exact_unit_seed_schedule(self):
        self.assertEqual(normalize_refinement(F(1)), (F(1), F(1), F(1, 2), F(2), F(1)))

    def test_lower_bound_seed_schedule(self):
        trace = normalize_refinement(1 - F(1, 4096))
        self.assertEqual(trace, (1-F(1, 4096), 1-F(1, 2048)+F(1, 2**24),
                                F(1, 2)-F(1, 8192), 2+F(1, 2048), 1-F(1, 2**24)))

    def test_final_stored_result_is_not_unique(self):
        a, b = normalize_refinement(F(1)), normalize_refinement(1-F(1, 4096))
        self.assertEqual(bits(a[-1]), '3f800000')
        self.assertEqual(bits(b[-1]), '3f7fffff')
        self.assertNotEqual(a[-1], b[-1])


if __name__ == '__main__':
    unittest.main()
