package homeworks;

import static org.junit.Assert.*;//JUnit 5

import org.junit.jupiter.api.Test;

public class IDLListTest
	{
	IDLList<Integer> list1 = new IDLList<>();
	
	@Test
	public void testAddIndexElem()
		{//index starts with 1 and ends with size
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		list1.add(2,0);
		assertEquals(list1.toString(), "[1,0,2,3,4,]");
		
		list1.add(1,0);
		assertEquals(list1.toString(), "[0,1,0,2,3,4,]");
		}
	@Test
	public void testAddElem()
	{
		list1.add(1);
		assertEquals(list1.toString(), "[1,]");
		
		list1.add(2);
		assertEquals(list1.toString(), "[2,1,]");
		}
	@Test
	public void testAppendElem()
		{
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		list1.append(0);
		assertEquals(list1.toString(), "[1,2,3,4,0,]");
		
		list1.append(9);
		assertEquals(list1.toString(), "[1,2,3,4,0,9,]");
		}
	@Test
	public void testGetIndex()
		{
		list1.add(2);
		list1.add(3);
		list1.add(4);
		list1.add(5);
		list1.add(6);
		list1.add(7);
		list1.add(8);
		list1.add(9);
		
		assertEquals(list1.get(3), (Integer) 7);
		
		assertEquals(list1.get(1), (Integer) 9);
		
		assertEquals(list1.get(8), (Integer) 2);
		
		}
	@Test
	public void testGetHead()
		{
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		assertEquals(list1.getHead(), (Integer) 1);
		
		list1.remove();
		assertEquals(list1.getHead(), (Integer) 2);
		}
	@Test
	public void testGetLast()
		{
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		assertEquals(list1.getLast(), (Integer) 4);
		
		list1.removeAt(4);
		assertEquals(list1.getLast(), (Integer) 3);
		}
	@Test
	public void testSize()
		{
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		assertEquals((Integer)list1.size(), (Integer) 4);
		}
	@Test
	public void testRemove()
		{
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		assertEquals(list1.remove(), (Integer) 1);
		assertEquals(list1.toString(), "[2,3,4,]");
		
		assertEquals(list1.remove(), (Integer) 2);
		assertEquals(list1.toString(), "[3,4,]");
		}
	@Test
	public void testRemoveLast()
		{
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		list1.removeLast();
		assertEquals(list1.toString(), "[1,2,3,]");
		
		list1.removeLast();
		assertEquals(list1.toString(), "[1,2,]");
		}
	@Test
	public void testRemoveAtIndex()
		{
		list1.add(4);
		list1.add(3);
		list1.add(2);
		list1.add(1);
		
		list1.removeAt(2);
		assertEquals(list1.toString(), "[1,3,4,]");
		
		list1.removeAt(2);
		assertEquals(list1.toString(), "[1,4,]");
		}
	@Test
	public void testRemoveElem()
		{
		list1.add(8);
		list1.add(6);
		list1.add(6);
		list1.add(4);
		list1.add(1);
		
		list1.remove(6);
		assertEquals(list1.toString(), "[1,4,6,8,]");
		
		list1.remove(4);
		assertEquals(list1.toString(), "[1,6,8,]");
		}
	@Test
	public void testToString()
		{
		list1.add(1);
		assertEquals(list1.toString(), "[1,]");
		
		list1.add(1);
		assertEquals(list1.toString(), "[1,1,]");
		}
	}
