/*
 * 				Grant Conrad Knowlton
 * 
 * 				Date: April 23rd, 2023
 * 				Class: EECS 1510
 * 				       Object Oriented Programming
 * 				
 * 				Project 2
 * 
 * 		This project is an introduction to class inheritance and
 * 		polymorphism.  The main method doesn't do much, merely
 * 		intended to stress the integrity of the class structure.
 * 		There are 6 class files that are a part of the project,
 * 		the person, employee, faculty, staff, student, and undergraduate.
 * 		Person is the central class, with employee and student deriving from it.
 * 		Faculty and staff are derived from employee, and undergraduate
 * 		is derived from student.  The main method will create various
 * 		instances of these classes, then call the writeOutput() method,
 * 		which will be specifically defined in each subclass to create
 * 		a different output.  It will call each method by iterating through
 * 		a person array, so each subclass method will take precedent over
 * 		the parent function definition.  Each class will further be described
 * 		in their own comments in their own file.
 */

public class PolymorphismDemo
{
	public static void main(String[] args)
	{
		// WHAT IS THIS FOR
		Person[] people = new Person[21];

		people[0] = new Person("Smith, Ron");
		people[1] = new Undergraduate();
		people[2] = new Undergraduate("Kick, Anita", 9931, 2);
		people[3] = new Employee();
		people[4] = new Staff("Harvey, Patrick", "EECS", 4555, 20);
		people[5] = new Student();
		people[6] = new Staff();
		people[7] = new Person();
		people[8] = new Undergraduate("Bugg, June", 9901, 4);
		people[9] = new Student("DeBanque, Robin", 8812);
		people[10] = new Faculty("Thomas, Lawrence", "EECS", 6221, "Associate Professor");
		people[11] = new Faculty();
		people[12] = new Student("Rumbry, Jon", 9693);
		people[13] = new Employee("Deer, Bob", "CHEM", 4201);
		people[14] = new Faculty("Hobbs, Joe", "EECS", 4531, "Associate Chair");
		people[15] = new Employee("Shmo, Joe", "MAIN", 7824);
		people[16] = new Staff("Yawf, Len", "MECH", 8942, 28);
		people[17] = new Staff("Bruh, John", "ARTE", 2369, -2);
		people[18] = new Employee("Brando, Dio", "JOJO", 8945);
		people[19] = new Faculty("Hennen, Christie", "EECS", 9821, "Advisor");
		people[20] = new Undergraduate("Tired, Iam", 4532, 6);
		
		
//WHAT IS THIS DOING
		for (Person p : people)
		{
			p.writeOutput();
			System.out.println();
		}
	}
}