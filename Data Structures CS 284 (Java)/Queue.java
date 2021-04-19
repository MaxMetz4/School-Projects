package exercises;

public class Queue<E> {
	
	private static class Node<F> {
		// data fields
		private F data;
		private Node<F> next;
		
		// Constructors
		
		public Node(F data, Node<F> next) {
			super();
			this.data = data;
			this.next = next;
		}
		public Node(F data) {
			super();
			this.data = data;
			this.next = null;
		}
		
		
		
	}
	// date fields
	private Node<E> front;
	private Node<E> rear;
	private int size;
	
	// Constructor
	Queue() {
		front=null;
		rear=null;
		size=0;
	}
	
	// Methods
	
	/**
	 * Adds a new element to the rear of the queue
	 * @param item to be added
	 * @return item that was added
	 */
	public E offer(E item) {
		return null;
	}
	
	/**
	 * Inspects the item at the front
	 * @return the element at the front
	 * @throws IllegalStateException if the queue is empty
	 */
	public E peek() {
		return null;
	}
	
	/** 
	 * Inspects and removes the item at the front
	 * @return the item at the front
	 * @throws IllegalStateException if the queue is empty 
	 */
	public E poll() {
		return null;
	}
	
	/**
	 * Size of the queue
	 * @return
	 */
	public int size() {
		return size;
	}
	
	
}
