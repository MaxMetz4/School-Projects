package exercises;

public class SingleLL<E> {

	private static class Node<F> {
		// data fields
		private F data;
		private Node<F> next;
		// Constructor
		
		public Node(F data, Node<F> next) {
			super();
			this.data = data;
			this.next = next;
		}
		public Node(F data) {
			super();
			this.data = data;
		}
		
	}
	// data fields
	private Node<E> head;
	private int size;
	
    // Constructor
	SingleLL() {
		head=null;
		size=0;
	}
	
	// Methods
	
	public E addFirst(E item) {
		head = new Node<E>(item,head);
		size++;
		return item;
	}

	
	public E addLast(E item) {
		if (head==null) {
			return this.addFirst(item);
		}
		Node<E> current = head;
		while (current.next!=null) {
			current=current.next;
		}
		
		current.next = new Node<>(item);
		size++;
		return item;
	}
	
	public E add(int index, E item) {
		if (index<0 || index>size) {
			throw new IllegalArgumentException();
		}
		if (index==0) {
			return this.addFirst(item);
		}
		
		Node<E> current = head;
		for (int i=0; i<index-1; i++) {
			current=current.next;
		}
		
		current.next = new Node<>(item,current.next);
		size++;
		return item;
 	}
	
	public E removeFirst(E item) {
		if (head==null) {
			throw new IllegalStateException("List is empty");
		}
		E temp = head.data;
		head = head.next;
		size--;
		return temp;
		
	}
	
	public E removeLast(E item) {
		return null;
	}
	
	public E remove(int index, E item) {
		return null;
	}
	
	public String toString() {
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
	
	public SingleLL<E> clone() {
		
		Node<E> current = head;
		Node<E> last = new Node<>(null);
		Node<E> newHead = last;
		
		while (current!=null) {
			last.next = new Node<E>(current.data);
			current = current.next;
			last = last.next;
		}
		
		SingleLL<E> result = new SingleLL<E>();
		result.head = newHead.next;
		result.size = size;
		return result;
	}
	
	public void take(int n) {
		
		if (n==0) {
			head=null;
			size=0;
			return;
		}
	    
		Node<E> current = head;
		int i=0;
		
		while (current!=null & i<n-1) {
			current = current.next;
			i++;
		}
		
		if (current!=null) {
			current.next=null;
			size = i+1;
		}
	
	}
	
	public void drop(int n) {
		
		if (n>=size) {
			head = null;
			size = 0;
			return;
		}
		Node<E> current = head;
		int i=0;
		
		while (current!=null & i<n) {
			current = current.next;
			i++;
		}
		
		if (current!=null) {
			head = current;
			size = size-i;
		}
	
	}
	
	public Pair<SingleLL<E>,SingleLL<E>> splitAt(int n) {
		
		SingleLL<E> lc1 = this.clone();
		SingleLL<E> lc2 = this.clone();
		
		lc1.take(n);
		lc2.drop(n);
		return new Pair<SingleLL<E>,SingleLL<E>>(lc1,lc2);
	}
	public static void main(String[] args) {
		//testing through console here
	}
}
