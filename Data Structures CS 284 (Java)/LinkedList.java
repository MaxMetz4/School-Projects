package exercises;
import java.util.Scanner;

//class node
class Node {
	protected int data;
	protected Node next, prev;
	
	//constructor
	public Node() {
		next = null;
		prev = null; 
		data = 0;
	}
	//constructor
	public Node(int d, Node n, Node p) {
		data = d;
		next = n;
		prev = p;
	}
//function to set  to next node
public void setNext(Node n) {
	next = n;
}
//function to set  to previous node
public void setPrev(Node p) {
	prev = p;
}
//function to get  to previous node
public Node getNext() {
	return next;
}
//function to get  to previous node
public Node getPrev() {
	return prev;
}
//function to set data to node
public void setData(int d) {
	data = d;
}
//function to get data from node
public int getData() {
	return data;
}
}
public class LinkedList {
	protected Node head;
	protected Node tail;
	public int size;
	//constructor
	public LinkedList() {
		head = null;
		tail = null;
		size = 0;
	}
	//function to check if list is empty
	public boolean isEmpty() {
		return head == null;
	}
	//function to get size of list
public int getSize() {
	return size;
}
//function to insert element at the beginning
public void insertAthead(int elem) {
	Node current = new Node(elem,null,null);
	if (head == null) {
		head = current;
		tail = head;
	} else {
		head.setPrev(current);
		current.setNext(head);
		head = current;
	}
	size++;
}
//function to insert element at the tail
public void insertAttail(int elem) {
	Node current = new Node(elem,null,null);
	if (head == null) {
		head = current;
		tail = head;
	} else {
		current.setPrev(tail);
		tail.setNext(current);
		tail = current;
	}
	size++;
}
//function to insert element at indexition
public void insertAtindex(int elem, int index) {
	Node current = new Node(elem,null,null);
	if (index == 1) {
		insertAthead(elem);
		return;
	}
	Node ptr = head;
	for (int i = 2; i <= size; i++) {
		if (i == index) {
			Node tmp = ptr.getNext();
			ptr.setNext(current);
			current.setPrev(ptr);
			current.setNext(tmp);
			tmp.setPrev(current);
		}
		ptr = ptr.getNext();
	}
	size++;
}
//function to delete Node at indexition
public void deleteAtindex(int index) {
	if (index == 1) {
		if (size == 1) {
			head = null;
			tail = null;
			size = 0;
			return;
		}
		head = head.getNext();
		head.setPrev(null);
		size--;
		return;
	}
	if (index == size) {
		tail = tail.getPrev();
		tail.setNext(null);
		size--;
		}
	Node ptr = head.getNext();
	for (int i = 2; i <= size; i++) {
		if (i == index) {
			Node p = ptr.getPrev();
			Node n = ptr.getNext();
			p.setNext(n);
			n.setPrev(p);
			size--;
			return;
		}
		ptr = ptr.getNext();
	}
}
//function to display statistics of list
public void display() {
	System.out.println("\nDoubly ed List = ");
	if (size == 0) {
		System.out.println("empty\n");
		return;
	}
	if (head.getNext() == null) {
		System.out.println(head.getData());
		return;
	}
	Node ptr = head;
	System.out.println(head.getData() + "<->");
	ptr = head.getNext();
	while (ptr.getNext() != null) {
		System.out.println(ptr.getData() + "<->");
		ptr = ptr.getNext();
	}
	System.out.print(ptr.getData() + "\n");
}
}
