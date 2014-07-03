import unittest
from bulletphysics import *

class QuaternionTest(unittest.TestCase):

    def setUp(self):
        self.quaternion = Quaternion(1.0, 2.0, 3.0, 4.0)

    def test_add(self):
        self.assertRaises(TypeError, self.quaternion.__add__, False)
        q = self.quaternion + Quaternion(0.0, 0.1, 0.2, 0.3)
        self.assertEqual(1.0, round(q.getX(), 2))
        self.assertEqual(2.1, round(q.getY(), 2))
        self.assertEqual(3.2, round(q.getZ(), 2))
        self.assertEqual(4.3, round(q.getW(), 2))

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
