/*
 * 		Faculty Class
 * 
 * 		An extension of the Employee class, which provides a constructor, 
 * 		a variable for the Faculty's title for their position,
 * 		a reset function, basic getter and setter functions
 * 		for title, a console output function, and an equals method for
 * 		comparing two Faculty instances.
 */

public class Faculty extends Employee
{
	// A string that stores the title of the Faculty member's position.
	private String title;
	
	// Constructor with no arguments, calls super class (Employee) constructor
    // with no argument, then sets title to "".
 	public Faculty()
 	{
 		super();
 		title = "";
 	}
	
	// The overloaded constructor that takes in the name, employee number, department name, and title
	// as the input.  The title is stored in the respective variable, while all other
	// parameters are passed to the super class's (Employee) constructor.
	public Faculty(String newName, String newDepartment, int newEmployeeNumber, String newTitle)
	{
		super(newName, newDepartment, newEmployeeNumber);
		title = newTitle;
	}
	
	// A reset function which will has the same parameters as the constructor, but
    // will just allow a user to reset all the associated variables to new values, as
	// well as reset the variables through the super class's reset function.
	public void reset(String newName, String newDepartment, int newEmployeeNumber, String newTitle)
	{
		super.reset(newName, newDepartment, newEmployeeNumber);
		title = newTitle;
	}
	
	// Returns the faculty's title.
	public String getTitle()
	{
		return title;
	}
	
	// Sets the faculty's title to the passed value.
	public void setTitle(String newTitle)
	{
		title = newTitle;
	}
	
	// Writes an output to the console, first consisting of
	// the output from the super class's (Employee) output function, then
	// it outputs the faculty's title with an accompanying label.
	public void writeOutput()
	{
		super.writeOutput();
		System.out.println("Title: " + title);
	}
	
	// Compares two Faculty instances, by checking if the super class (Employee) values are the same
    // through the employee equals method, as well as if their titles are the same.  Returns
	// true if the checked values are the same and false otherwise.
	public boolean equals(Faculty otherFaculty)
	{
		if((this.getTitle() == otherFaculty.getTitle()) && super.equals(otherFaculty)) return true;
		return false;
	}
}
