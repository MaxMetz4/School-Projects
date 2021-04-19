import unittest
import polynomials as Po

L = Po.LinkedPolynomial()
L.createListFromNumbers([(2,2),(1,1)])

p = Po.LinkedPolynomial()
p.createListFromNumbers([(3,2), (-5, 1)])

Q = Po.LinkedPolynomial()
Q.createListFromNumbers([(-1, 3), (1, 0)])

class Test(unittest.TestCase):

    def testL(self):
        self.assertEqual(L.__str__(), "2x^2 + 1x^1")

    def testp(self):
        self.assertEqual(p.__str__(), "3x^2 - 5x^1")

    def testEq(self):
        self.assertFalse(L == p)

    def testCall(self):
        self.assertEqual(L(2), 10)

    def testNeg(self):
        self.assertEqual((-p).__str__(), "-3x^2 + 5x^1")

    def testSub(self):
        self.assertEqual((L-p).__str__(), "-1x^2 + 6x^1")

    def testQ(self):
        self.assertEqual(Q.__str__(), "-1x^3 + 1x^0")

    def testAdd(self):
        self.assertEqual((Q+p).__str__(), "-1x^3 + 3x^2 - 5x^1 + 1x^0")

if __name__ == "__main__":
    unittest.main()
