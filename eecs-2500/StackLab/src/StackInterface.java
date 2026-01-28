/**
 * 
 */

/**
 * Stack Interface to be implemented in Lab for Week 4. 
 * This is a simple Stack interface -- It will allow us to 
 * implement our own stack during the lab.
 */
public interface StackInterface<T> {
	/**
	 * Push an item of type T onto this stack.  The stack size increases by 1 and the item becomes the new top of staack. 
	 * 
	 * @param item  the object to be placed on the top of this stack.
	 */
	public void push (T item);
	/**
	 * 
	 * @return  the item on top of this stack
	 */
	public T peek();
	/**
	 * removes and returns the item on the top of this stack.
	 * @return  the item that was on top of this stack. 
	 */
	public T pop();
	/**
	 * 
	 * @return true if this stack is full.  false otherwise.
	 */
	public boolean isFull();
	/**
	 * 
	 * @return true if this stack is empty.  False otherwise.
	 */
	public boolean isEmpty();

}
