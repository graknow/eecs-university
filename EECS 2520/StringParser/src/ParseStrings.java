import java.util.Scanner;

public class ParseStrings {
   public static void main(String[] args) {
      Scanner scnr = new Scanner(System.in);
      String[] strings = new String[1];
      
      do {
         strings = scnr.nextLine().split(",");
         
         if(strings[0].equals("q")) {
            continue;
         }

         if(strings.length == 1) {
            System.out.println("Error: No comma in string.");
            continue;
         }

         System.out.println("First word: " + strings[0].trim());
         System.out.println("Second word: " + strings[1].trim());
      } while(!strings[0].equals("q"));      

      scnr.close();
   }
}
