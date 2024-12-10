public class Palindrome {

	public static void main(String[] args) {
		StackInterface<Character> stack = new StackImplementation<Character>(10);

		java.util.Scanner input = new java.util.Scanner(System.in);
		String originalString;
		Character originalCharacters[];

		System.out.println("Input a string to test : ");
		originalString = input.nextLine();
		/*
		 * Step through the original string pushing the lower case equivalent of any
		 * letter onto the stack. 
		 */
		for (int position = 0; position < originalString.length(); position++) {
			Character ch;
			ch = originalString.charAt(position);
			if (Character.isLetter(ch)) {
				stack.push(Character.toLowerCase(ch));
			}
		}
		
		/*
		 * Step through the original string and, when we find a letter, convert it
		 * to lower case and see if it is equal to the letter on the top of the stack. 
		 * If this works for all letters we have a palindrome.  If it fails for even 1
		 * letter it is not a palindrome. 
		 */
		for (int position = 0; position < originalString.length(); position++) {
			Character ch;
			ch = originalString.charAt(position);
			if (Character.isLetter(ch)) {
				Character lower = Character.toLowerCase(ch);
				if (!lower.equals(stack.pop())) {
					System.out.println("It is not a palindrome");
					System.exit(0);
				}
			}
		}
		System.out.println("It is a palindrome!");


		System.exit(0);
	}
}
