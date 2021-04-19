'''
Created Sep. 13th 2019 by Toby Dalton

CS 115 - HW2 Public Test Script
'''

import unittest
import HW2

class Test(unittest.TestCase):
    def setUp(self):
        self.a = "GCATGCAT"
        self.c = "the cat"
        self.s = "GCTAGCTA"

    def testmakeChange(self):
        rslt = HW2.makeChange(313, [7, 24, 42])
        rslt[1].sort()
        self.assertEqual(rslt, [10, [7, 24, 24, 24, 24, 42, 42, 42, 42, 42]])

        rslt = HW2.makeChange(13, [14, 1, 7, 6, 7, 13])
        self.assertEqual(rslt, [1, [13]])

    def testLCS(self):
        self.assertEqual(HW2.LCS(self.a, self.c), "")
        self.assertEqual(HW2.LCS(self.a, self.s), "GCAGCA")

    def testPLCS(self):
        self.assertEqual(HW2.PLCS(self.a, self.c), [[-1], [-1]])
        self.assertEqual(HW2.PLCS(self.a, self.s), [[0, 1, 2, 4, 5, 6], [0, 1, 3, 4, 5, 7]])


if __name__ == "__main__":
    unittest.main()
