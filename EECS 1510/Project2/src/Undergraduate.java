/*
 * 		Undergraduate Class
 * 
 * 		An extension of the Student class that provides a variable 
 * 		for the student's academic level.  Provides a constructor, a
 * 		reset function, basic getter and setter functions for the level value, 
 * 		a console output function, and an equals method to compare two instances
 * 		of the Undergraduate class.
 */

public class Undergraduate extends Student
{
	// A variable for storing the undergraduate's level.
	private int level;
	
	// Constructor with no arguments, calls super class (Student) constructor
    // with no argument, then sets level to 0.
 	public Undergraduate()
 	{
 		super();
 		level = 0;
 	}
	
	// The overloaded constructor that takes in the name, student ID number,
	// and level as the input.  The level is stored in the respective variable, 
	// while all other parameters are passed to the super class's (Student) constructor.
	public Undergraduate(String newName, int newStudentNumber, int newLevel)
	{
		super(newName, newStudentNumber);
		level = newLevel;
	}
	
	// A reset function which will has the same parameters as the constructor, but
    // will just allow a user to reset all the associated variables to new values, as
	// well as reset the variables through the super class's reset function.
	public void reset(String newName, int newStudentNumber, int newLevel)
	{
		super.reset(newName, newStudentNumber);
		level = newLevel;
	}
	
	// Returns the undergraduate's level.
	public int getLevel()
	{
		return level;
	}
	
	// Sets the undergraduate's level to the passed value.
	public void setLevel(int newLevel)
	{
		level = newLevel;
	}
	
	// Writes an output to the console, first consisting of
	// the output from the super class's (Student) output function, then
	// it outputs the undergraduate's level with an accompanying label.
	public void writeOutput()
	{
		super.writeOutput();
		System.out.println("Student Level: " + level);
	}
	
	// Compares two Undergraduate instances, by checking if the super class (Student) values are the same
    // through the employee equals method, as well as if their levels are the same.  Returns
	// true if the checked values are the same and false otherwise.
	public boolean equals(Undergraduate otherUndergraduate)
	{
		if((this.getLevel() == otherUndergraduate.getLevel()) && super.equals(otherUndergraduate)) return true;
		return false;
	}
}
