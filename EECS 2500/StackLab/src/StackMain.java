
public class StackMain {

	
	public static void main (String args[]) {
		
		StackInterface<String> stringStack = new StackImplementation<String> (5);

		System.out.println("isEmpty() = "+stringStack.isEmpty() + "   isFull() = " + stringStack.isFull());

		stringStack.push("Red");
		stringStack.push("Green");
		stringStack.push("Blue");
		stringStack.push("Cyan");
		stringStack.push("Magenta");
		stringStack.push("Yellow");
		System.out.println("isEmpty() = "+stringStack.isEmpty() + "   isFull() = " + stringStack.isFull());
		while (!stringStack.isEmpty()) {
			System.out.println("Popped " + stringStack.pop());
		}
		System.out.println("isEmpty() = "+stringStack.isEmpty() + "   isFull() = " + stringStack.isFull());

	}
}
