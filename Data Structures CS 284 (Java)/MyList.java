package exercises;

public class MyList<E> {
	// data fields
	private E[] data;
	private int free;
	
	
	// Constructors
	MyList(int size) {
		data = (E[]) new Object[size];
		free = 0;
	}
	
	// Methods
	/**
	 * Add element elem at the end of the list.
	 * Returns null if the list is full
	 * @param elem Element to insert
	 * @return The element just inserted
	 */
	public E addLast(E elem) {
		if (free==data.length) { // array is full
			throw new IllegalStateException();
		}
		data[free]=elem;
		free++;
		return elem;
	}
	
	public E addFirst(E elem) {
		return add(0,elem);
	}
	
	public E add(int index, E elem) {
		if (index<0 || index>free) { // index out of range
			throw new IllegalArgumentException();
		}
		if (free==data.length) { // array is full
			throw new IllegalStateException();
		}		
		for (int i=free; i>index; i--) {
			data[i]=data[i-1];
		}
		data[index]=elem;
		free++;
		return elem;
	}
	
	public E removeLast() {
		if (free==0) {
			throw new IllegalStateException("Cannot remove from empty list");
		}
		free--;
		return data[free+1];
	}
	
	public E removeFirst() {
		if (free==0) {
			throw new IllegalStateException("Cannot remove from empty list");
		}
		E temp = data[0];
		for (int i=0; i<free; i++) {
			data[i]=data[i+1];
		}
		free--;
		return temp;
		
	}
	
	public int size() {
		return free;
	}
	
	public E remove(int index) {
		return null;
	}
			
	public Boolean member(E elem) {
		int i=0;
		while (i<free && !data[i].equals(elem)) { 
				i++;
		}
		return i<free;
	}
	
	
	public int find(E elem) {
	   int i=0;
	   while (i<free && !data[i].equals(elem)) {
		   i++;
	   }
	   
//	   if (i<free) {
//		   return i;
//	   } else {
//		   return -1;
//	   }
	   return i<free ? i : -1;
		
	}
	
	public Boolean included_in(MyList<E> l) {
		int i=0;
		while (i<free && l.member(data[i])) { 
				i++;
		}
		return !(i<free);
	}
		
	public MyList<Pair<E,E>>zip(MyList<E> l) {
		int len = Math.min(this.size(),l.size());
		MyList<Pair<E,E>> result = new MyList<Pair<E,E>>(len);
		for (int i=0; i<len; i++) {
			result.addLast(new Pair<E,E>(data[i],l.data[i]));
		}
		return result;
	}
	
	public <F> MyList<Pair<E,F>>zip2(MyList<F> l) {
		int len = Math.min(this.size(),l.size());
		MyList<Pair<E,F>> result = new MyList<Pair<E,F>>(len);
		for (int i=0; i<len; i++) {
			result.addLast(new Pair<E,F>(data[i],l.data[i]));
		}
		return result;
	}
	
	public Boolean sublist(MyList<E> l) {
		return null;
	}

	public String toString() {
		StringBuilder s = new StringBuilder();
		for (int i=0; i<free; i++) {
			s.append(data[i].toString()+",");
		}
		return "["+s.toString()+"]";
	}
	
	
	public static void main(String[] args) {
		MyList<Integer> l = new MyList<>(20);
		MyList<Integer> l2 = new MyList<>(20);
		MyList<String> l3 = new MyList<>(20);
		
		
		for (int i=0; i<10; i++) {
			l.addFirst(i);
		}
		for (int i=0; i<20; i++) {
			l2.addFirst(i+200);
		}

		for (int i=0; i<20; i++) {
			l3.addFirst(((Integer) i).toString()+ "<<<");
		}

		System.out.println(l);
		System.out.println(l2);
		System.out.println(l3);
		
//		l.add(4, 12);
//		System.out.println(l);
		
//		MyList<String> l2 = new MyList<String>(20);
//		l.removeFirst();
//		l.removeFirst();
//		l.removeLast();
//		System.out.println(l);
//		
//		
//		System.out.println(l.member(7));
//		System.out.println(l.member(12));
//		System.out.println(l.member(77));
//		System.out.println(l.find(7));
//		System.out.println(l.find(77));
		
		System.out.println(l.zip(l2));
		System.out.println(l.<String>zip2(l3));
		
	}
	
}
