package homeworks;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

class TreapTest {

	@Test
	void testTreap() {
		Treap<Integer> testTree = new Treap < Integer >();
		assertEquals(false, testTree.equals(null), "Has a treap object been created");
	}

	@Test
	void testTreapLong() {
		Treap<String> testTree = new Treap < String>();
		assertEquals(false, testTree.equals(null), "Has a treap with a seed object been created");
	}

	@Test
	void testAddE() {
		Treap<Integer> testTree = new Treap < Integer >();
		testTree . add (4 ,19);
		testTree . add (2 ,31);
		testTree . add (6 ,70);
		testTree . add (1 ,84);
		testTree . add (3 ,12);
		testTree . add (5 ,83);
		testTree . add (7 ,26);
		assertEquals(1, testTree.getRoot().data, "1");
		assertEquals(null, testTree.getRoot().left, "2");
		assertEquals(5, testTree.getRoot().right.data, "3");
		assertEquals(2, testTree.getRoot().right.left.data, "4");
		assertEquals(6, testTree.getRoot().right.right.data, "5");
		
		assertEquals(70, testTree.getRoot().right.right.priority, "6");
		assertEquals(26, testTree.getRoot().right.right.right.priority, "7");

/* This is what it looks like
(key = 1, priority = 84)
   null
   (key = 5, priority = 83)
      (key = 2, priority = 31)
         null
         (key = 4, priority = 19)
            (key = 3, priority = 12)
               null
               null
            null
      (key = 6, priority = 70)
         null
         (key = 7, priority = 26)
            null
            null
*/
	}

	@Test
	void testAddEInt() {
		Treap<Integer> testTree = new Treap < Integer >();
		testTree . add (4);
		testTree . add (2);
		testTree . add (6);
		testTree . add (1);
		testTree . add (3);
		testTree.toString();
		//I'm not sure how to test this one... I printed the result to the console and you can see how
		//priorites are randomized after each time it is run
	}

	@Test
	void testDelete() {
		Treap<Integer> testTree = new Treap < Integer >();
		testTree . add (4 ,19);
		testTree . add (2 ,31);
		testTree . add (6 ,70);
		testTree . add (1 ,84);
		testTree . add (3 ,12);
		testTree . add (5 ,83);
		testTree . add (7 ,26);
		
		assertEquals(true, testTree.find(7), "7 before removal"); 
		testTree.delete(7);
		assertEquals(false, testTree.find(7), "7 after removal"); 
		
		assertEquals(true, testTree.find(5), "5 before removal"); 
		testTree.delete(5);
		assertEquals(false, testTree.find(5), "5 after removal"); 
	}

	@Test
	void testFind() {
		Treap<Integer> testTree = new Treap < Integer >();
		testTree . add (4);
		testTree . add (2);
		testTree . add (6);
		testTree . add (1);
		testTree . add (3);
		
		assertEquals(true, testTree.find(4), "find 4 in treap");
		assertEquals(true, testTree.find(2), "find 7 in treap");
		assertEquals(false, testTree.find(40), "find 6 in treap");
		assertEquals(false, testTree.find(-4), "find 7 in treap");
	}

}
