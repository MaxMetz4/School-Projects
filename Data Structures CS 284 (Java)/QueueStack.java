package exercises;


public class QueueStack<E> 
{
	
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
	
	
	private Stack<E> queueStack;
	private Stack<E> holdStack;
	private int size;
	
	
	QueueStack()
	{
	queueStack = new Stack<E>();
	holdStack = new Stack<E>();
	
	size = 0;
	}

	public E offer(E item)
	{
	//step 1
	while(!queueStack.empty())
		{
		holdStack.push(queueStack.pop());
		}
	//step 2
	queueStack.push(item);
	//step 3
	while(!holdStack.empty())
		{
		queueStack.push(holdStack.pop());
		}	
	size++;
	return item;
	}
	
	public E peek()
	{
	if(!queueStack.empty())
		{return queueStack.peek();}
	throw new IllegalStateException();
	}
	
	public E poll()
	{
	if(!queueStack.empty())
		{size--;
		return queueStack.pop();}
	throw new IllegalStateException();
	}
	
	public int size()
	{return this.size;}
	
	public String toString()
	{return queueStack.toString();}
	
	public static void main(String args[])
		{
		QueueStack<Integer> qs = new QueueStack<Integer>();
		
		qs.offer(4);
		qs.offer(5);
		qs.offer(7);
		qs.offer(2);
		System.out.println(qs.toString());
		
		qs.offer(3);
		System.out.println(qs.toString());
		System.out.println(qs.peek());
		System.out.println(qs.poll());
		System.out.println(qs.poll());
		System.out.println(qs);


		
		
		}
	
}














