/*
 * 		Student Class
 * 
 * 		An extension of the Person class that provides a
 * 		variable to store a student's ID number.  It provides
 * 		a constructor, a reset function, basic getter and setter
 * 		functions, a console output function, and an equals method
 * 		for comparing two Student instances.
 */

public class Student extends Person
{
	// An integer that stores the student's ID number.
    private int studentNumber;
    
    // Constructor with no arguments, calls super class (Person) constructor
    // with no argument, then sets student ID number to 0.
 	public Student()
 	{
 		super();
 		studentNumber = 0;
 	}
    
    // The overloaded constructor that takes in the name and student ID number
 	// as the input.  The student ID number is stored in the respective variable, 
    // while all other parameters are passed to the super class's (Person) constructor.
    public Student(String newName, int newStudentNumber)
    {
    	super(newName);
    	studentNumber = newStudentNumber;
    }
    
    // A reset function which will has the same parameters as the constructor, but
    // will just allow a user to reset all the associated variables to new values, as
	// well as reset the variables through the super class's reset function.
    public void reset(String newName, int newStudentNumber)
    {
    	super.setName(newName);
    	studentNumber = newStudentNumber;
    }
    
    // Returns the student's ID number.
    public int getStudentNumber()
    {
    	return studentNumber;
    }
    
    // Sets the student's ID number to the passed value.
    public void setStudentNumber(int newStudentNumber)
    {
    	studentNumber = newStudentNumber;
    }
    
    // Writes an output to the console, first consisting of
 	// the output from the super class's (Person) output function, then
 	// it outputs the student's ID number with an accompanying label.
    public void writeOutput()
    {
    	super.writeOutput();
    	System.out.println("Student Number: " + studentNumber);
    }
    
    // Compares two Student instances, by checking if their student ID number is the same,
    // as well as if their names are the same (Which is checked through the super class hasSameName() method).
    // This returns true if all checked values are the same, and false otherwise.
    public boolean equals(Student otherStudent)
    {
    	if((this.getStudentNumber() == otherStudent.getStudentNumber()) && super.hasSameName(otherStudent)) return true;
    	return false;
    }
}
