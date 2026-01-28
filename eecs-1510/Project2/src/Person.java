/*
 * 		Person Class
 * 
 * 		This is the most abstract class that is implemented in this
 * 		project.  Provides a constructor and a structure for the other classes to be
 * 		extended off of.  Has a String for the person's name, provides
 * 		basic getter setter functions, a console output function, and a
 * 		hasSameName method for comparing two Person instances.
 */

public class Person
{
	// A string that sores the name of the person.
	private String name;
	
	// Constructor with no arguments, sets name to "".
	public Person()
	{
		name = "";
	}
	
	// The overloaded constructor with a string input, 
	// which will be saved in the private "name" variable.
	public Person(String newName)
	{
		name = newName;
	}
	
	// Allows the user to reset the value in the name variable to
	// whatever is passed to the method.
	public void reset(String newName)
	{
		name = newName;
	}
	
	// Sets the name variable to whatever value is passed.
	public void setName(String newName)
	{
		name = newName;
	}
	
	// Returns the value of name.
	public String getName()
	{
		return name;
	}
	
	// Prints an output to the console, which will be the person's name,
	// as well as a label denoting it is the name of the person.
	public void writeOutput()
	{
		System.out.println("Name: " + name);
	}
	
	// Compares two Person instances, returning true if they have the same name value
	// of false if they do not have the same name.
	public boolean hasSameName(Person otherPerson)
	{
		if(this.getName() == otherPerson.getName()) return true;
		return false;
	}
}
