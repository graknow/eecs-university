/**
 * Grant Knowlton
 * 
 * An interface for a stack.  Provides necessary methods for any stack class.
 * 
 * Outlines these methods:
 * 		push,
 * 		peek,
 * 		pop,
 * 		isFull,
 * 		isEmpty
 * 
 * Created with a template type "T" to allow for the creation of stacks with different data types.
 */
public interface StackInterface<T> {


	/**
	 * Push an item of type T onto this stack.  The stack size increases by 1 and the item becomes the new top of stack. 
	 * 
	 * @param item  the object to be placed on the top of this stack.
	 */
	public void push (T item);


	/**
	 * Returns the top item of the stack.
	 * @return  the item on top of this stack
	 */
	public T peek();


	/**
	 * Returns the top item of the stack, then removes it.
	 * @return  the item that was on top of this stack. 
	 */
	public T pop();


	/**
	 * Determine if the stack is full.  If the stack counter equals the size, the stack is full.
	 * @return true if this stack is full.  False otherwise.
	 */
	public boolean isFull();


	/**
	 * Determine if the stack is empty.  If the stack counter is 0, the stack is empty.
	 * @return true if this stack is empty.  False otherwise.
	 */
	public boolean isEmpty();

}
