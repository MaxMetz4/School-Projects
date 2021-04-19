import unittest
from Rational import Rational

class Test(unittest.TestCase):

    def testSimplify(self):
        R = Rational(15, 20)
        R.simplify()
        self.assertEqual(R, Rational(3, 4))
        
        K = Rational(120, 15)
        K.simplify()
        self.assertEqual(K, Rational(8, 1))

    def testInvert(self):
        J = Rational(3, 4)
        J.invert()
        self.assertEqual(J, Rational(4, 3))

    def testMul(self):
        V = Rational(10, 3)
        T = Rational(3, 10)
        self.assertEqual(V * T, Rational(1, 1))

    def testDiv(self):
        C = Rational(4, 52)
        c = Rational(3, 7)
        self.assertEqual(C / c, Rational(7, 39))

    def testInt(self):
        A = Rational(24, 7)
        self.assertEqual(int(A), 3)

if __name__ == "__main__":
    unittest.main()
