package exercises;

public interface StackInt<E> {

	E push(E obj);
	
	E peek();
	
	E pop();
	
	boolean empty(); 
	
}
