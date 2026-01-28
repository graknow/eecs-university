/**
 * Grant Knowlton
 * 
 * An implementation of the StackInterface interface.
 * 
 * Provides a constructor that takes the initial size of the stack.  Implementation for
 * the interface methods are made, and the expandArray method is added.
 * 
 * The stack has two private fields:
 * stackData - Holds the data that has been pushed onto the stack.
 * stackCount - Holds the index of the stackData that is next to be pushed onto.
 * 
 * Further explanation of the method implementations can be found in each individual method.
 */

public class StackImplementation<T> implements StackInterface<T> {
	
	private T[] stackData;
	private int stackCount;
	
	// Constructor for when a size is supplied.
	@SuppressWarnings("unchecked")
	public StackImplementation(int initSize) {
		// Allocate new stack, and initialize stack count to 0;
		stackData = (T []) new Object[initSize];
		stackCount = 0;
	}
	
	// Adds the passed value to the top of the stack.
	@Override
	public void push(T item) {
		// If full, expand array by 10 items.
		if(this.isFull()) {
			expandArray();
		}
		stackData[stackCount++] = item;
	}

	// Returns the top item of the stack.
	@Override
	public T peek() {
		// Returns the top item without decrementing the stackCount.
		return stackData[stackCount - 1];
	}

	// Returns the top item of the stack, then removes it from the stack.
	@Override
	public T pop() {
		// If empty, print error and return from function.  Otherwise return the top most value
		// and decrement the stackCount.
		if(this.isEmpty()) {
			System.out.println("The stack is empty!  Nothing to pop off of it!");
			return null;
		}
		T tmpData = stackData[--stackCount];
		stackData[stackCount] = null;
		return tmpData;
	}

	// Returns true if the stack is full, otherwise returns false.
	@Override
	public boolean isFull() {
		// If stackCount equals the length of the stackData, it is full (Return true).  Otherwise false.
		return stackCount == stackData.length;
	}

	// Returns true if the stack is empty, otherwise returns false.
	@Override
	public boolean isEmpty() {
		// If stackCount equals 0, it is empty (Return true). Otherwise false.
		return stackCount == 0;
	}
	
	// Expands the array of the stack if something is pushed onto a full stack.
	@SuppressWarnings("unchecked")
	private void expandArray() {
		// Allocates a bigger T array (10 larger) then copies all the data from the
		// original stackData to the bigger stack.  Then it sets the current stackData
		// to the bigger array.
		T[] biggerStack;
		biggerStack = (T []) new Object[stackData.length + 10];
		for(int index = 0; index < stackData.length; index++) {
			biggerStack[index] = stackData[index];
		}
		stackData = biggerStack;
	}
}
