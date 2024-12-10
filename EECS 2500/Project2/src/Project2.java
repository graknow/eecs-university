import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;

public class Project2 {
    private LinkedQueueImplementation<Character> currentPattern;

    private Map<Character, String> rules;

    private double angle;

    private int numExpansions;

    private Character endFlag = Character.valueOf('@');
    
    public static void main(String[] args) throws QueueOverflowException, QueueUnderflowException {
        // Main program instance.
        Project2 mainProgram = new Project2();

        mainProgram.currentPattern = new LinkedQueueImplementation<Character>();
        mainProgram.rules = new HashMap<Character, String>();
        
        mainProgram.readData();
        while(mainProgram.numExpansions > 0) {
            mainProgram.expand();
            mainProgram.numExpansions--;
        }

        System.out.println("The results of the expansion:");
        System.out.println("Angle:         " + mainProgram.angle);
        System.out.print("Final pattern: ");
        while(!mainProgram.currentPattern.isEmpty()) {
            Character c = mainProgram.currentPattern.dequeue();
            if(c.equals(mainProgram.endFlag)) break;
            
            System.out.print(c);
        }
    }

    private void readData() throws QueueOverflowException {
        Scanner scnr = new Scanner(System.in);

        this.angle = scnr.nextDouble();
        scnr.nextLine();

        String initPattern = scnr.nextLine();
        for(int i = 0; i < initPattern.length(); i++) {
            this.currentPattern.enqueue(Character.valueOf(initPattern.charAt(i)));
        }
        this.currentPattern.enqueue(endFlag);

        int numRules = scnr.nextInt();
        for(int i = 0; i < numRules; i++) {
            Character key = Character.valueOf(scnr.next().charAt(0));
            this.rules.put(key, scnr.nextLine());
        }

        this.numExpansions = scnr.nextInt();

        scnr.close();
    }

    private void expand() throws QueueOverflowException, QueueUnderflowException {
        Character currentChar;
        do {
            currentChar = currentPattern.dequeue();

            if(!rules.containsKey(currentChar)) {
                currentPattern.enqueue(currentChar);
                continue;
            }

            for(int i = 1; i < rules.get(currentChar).length(); i++) {
                currentPattern.enqueue(rules.get(currentChar).charAt(i));
            }
        } while(!currentChar.equals(Character.valueOf(endFlag)));
    }
}