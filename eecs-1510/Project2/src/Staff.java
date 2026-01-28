/*
 * 		Staff Class
 * 
 * 		An extension of the Employee class that provides a variable 
 * 		for the staff's pay grade.  Provides a constructor, a reset function,
 * 		basic getter and setter functions for the pay grade, a console
 * 		output function, and an equals method to compare two instances
 * 		of the Staff class.
 */

public class Staff extends Employee
{
	// An integer that stores the staff member's pay grade.
	private int payGrade;
	
	// Constructor with no arguments, calls super class (Employee) constructor
    // with no argument, then sets pay grade to 0.
 	public Staff()
 	{
 		super();
 		payGrade = 0;
 	}
	
	// The overloaded constructor that takes in the name, employee number, department name, and pay grade
	// as the input.  The pay grade is stored in the respective variable, while all other
	// parameters are passed to the super class's (Employee) constructor.
	public Staff(String newName, String newDepartment, int newEmployeeNumber, int newPayGrade)
	{
		super(newName, newDepartment, newEmployeeNumber);
		
		// Checks if the new pay grade value is within range, otherwise it sets it to 0
		if(newPayGrade < 1 || newPayGrade > 20) newPayGrade = 0;
		payGrade = newPayGrade;
	}
	
	// A reset function which will has the same parameters as the constructor, but
    // will just allow a user to reset all the associated variables to new values, as
	// well as reset the variables through the super class's reset function.
	public void reset(String newName, String newDepartment, int newEmployeeNumber, int newPayGrade)
	{
		super.reset(newName, newDepartment, newEmployeeNumber);
		
		// Checks if the new pay grade value is within range, otherwise it sets it to 0
		if(newPayGrade < 1 || newPayGrade > 20) newPayGrade = 0;
		payGrade = newPayGrade;
	}
	
	// Returns the staff's pay grade.
	public int getPayGrade()
	{
		return payGrade;
	}
	
	// Sets the staff's pay grade to the passed value.
	public void setPayGrade(int newPayGrade)
	{
		if(newPayGrade < 1 || newPayGrade > 20) newPayGrade = 0;
		payGrade = newPayGrade;
	}
	
	// Writes an output to the console, first consisting of
	// the output from the super classes (Employee) output function, then
	// it outputs the staff's pay grade with an accompanying label.
	public void writeOutput()
	{
		super.writeOutput();
		System.out.println("Pay Grade: " + payGrade);
	}
	
	// Compares two Staff instances, by checking if the super class (Employee) values are the same
    // through the employee equals method, as well as if their pay grade values are the same.  Returns
	// true if the checked values are the same and false otherwise.
	public boolean equals(Staff otherStaff)
	{
		if((this.getPayGrade() == otherStaff.getPayGrade()) && super.equals(otherStaff)) return true;
		return false;
	}
}
