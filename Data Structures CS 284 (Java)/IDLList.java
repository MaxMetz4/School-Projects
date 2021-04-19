package homeworks;

import java.util.ArrayList;

public class IDLList<E> {

	private static class Node<E> {
		//Data Fields
		private E data;
		private Node<E> next;
		private Node<E> prev;
		
		//Constructor
		public Node(E elem) {
			super();
			this.next = null;
			this.prev = null;
			this.data = elem;
		}
		public Node(E elem, Node<E> prev, Node<E> next) {
			super();
			this.data = elem;
			this.next = next;
			this.prev = prev;
		}
	}
	//Data Fields
	private Node<E> head;
	private Node<E> tail;
	private int size;
	private ArrayList<Node<E>> indices;
	
	//Constructor
	public IDLList() { //Requires index maintenance
		head = null;
		tail = null;
		size = 0;
		indices = new ArrayList<Node<E>>();
	}
	
	//Methods
	public boolean add (int index, E elem) {//Requires index maintenance
		Node<E> current = new Node<E>(elem,null,null);
		if (index < 1 || index> size) {
			throw new IllegalArgumentException("Index is out of range");
		}
		if (index==1) {
			add(elem);
			return true;
		}
		Node<E> current2 = indices.get(index-2);//using index for fast access
		Node<E> temp = current2.next;
		current2.next = current;
		current.prev = current2;
		current.next = temp;
		temp.prev = current;
		size++;
		indices.add(index-1,current);//adding entry to index
		return true;
	}
	public boolean add (E elem) {//Requires index maintenance
		Node<E> current = new Node<E>(elem,null,null);
		if (head == null) {
			head = current;
			tail = head;
		} else {
			head.prev = current;
			current.next = head;
			head = current;
		}
		indices.add(0,current);
		size++;
		return true;
	}
	public boolean append (E elem) {//Requires index maintenance
		Node<E> current = new Node<E>(elem,null,null);
		if (head == null) {
			head = current;
			tail = head;
			indices.add(0,current);
		} else {
			current.prev = tail;
			tail.next = current;
			tail = current;
			indices.add(size-1,current);
		}
		size++;
		return true;
	}
	public E get (int index) { 
		if (index == 1) {
			return head.data;
		}
		if (index == size) {
			return tail.data;
		}
		Node<E>temp = indices.get(index-1);//fast Accessing
			return  temp.data;
	}
	public E getHead () { 
		return head.data;
	}
	public E getLast () { 
		return tail.data;
	}
	public int size() {
		return size;
	}
	public E remove() {//Requires index maintenance
		Node<E> temp = head;
		if (size == 1) {
			temp = null;
			size--;
			return null;
		}
		if (size < 1) {
			throw new IllegalStateException("List already empty");
		}
		head = head.next;
		indices.remove(0);
		size--;
		return temp.data;
	}
	public E removeLast () {//Requires index maintenance
		Node<E> temp = tail;
		if (size == 1) {
			temp = null;
			size--;
			return null;
		}
		if (size < 1) {
			throw new IllegalStateException("List already empty");
		}
		tail = tail.prev;
		tail.next = null;
		size--;
		indices.remove(size-1);
		return temp.data;
	}
	public E removeAt (int index) {//Requires index maintenance
		if (index < 1 || index > size) {
			throw new IllegalStateException("Invalid index");
		}
		if (index == 1) {
			indices.remove(0);
			size--;
			return remove();
		}
		if (index == size) {
			indices.remove(size-1);
			size--;
			return removeLast();
			}
		Node<E> temp = indices.get(index-1);
		Node<E> before = temp.prev;
		Node<E> after = temp.next;
		before.next = after;
		after.prev = before;
		size--;
		indices.remove(index-1);
		return temp.data;
	}
	public boolean remove (E elem) {//Requires index maintenance
		Node<E> current = head;
		for (int i = 1; i <= size; i++) {//cannot use fast access since it needs to check each element sequentially
			if (current.data == elem) {
				removeAt(i);//this also takes care of size--;
				indices.remove(i-1);
				return true;
			}
			current = current.next;
		}
		return false;
	}
	public String toString() { //borrowed from SLList classroom example
		StringBuilder s = new StringBuilder();
		
		Node<E> current = head;
		s.append("[");
		while (current!=null) {
			s.append(current.data.toString()+",");
			current = current.next;
		}
		s.append("]");
		return s.toString();
	}
}
