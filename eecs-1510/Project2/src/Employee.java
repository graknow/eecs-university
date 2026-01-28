/*
 * 		Employee Class
 * 
 * 		An extension of the person class that provides a variable to 
 * 		store an employee's ID number and the name of their department.
 * 		Provides a constructor, a reset function, basic getter and setter functions
 * 		for the employee variables, a console output function, and an
 * 		equals method for comparing two instances of Employee. 
 */

public class Employee extends Person
{
	// An integer that stores the employee's ID number.
    private int employeeID;
    
    // A string that stores the name of the employee's department.
    private String department;
    
    // Constructor with no arguments, calls super class (Person) constructor
    // with no argument, then sets employee ID to 0 and department to "".
 	public Employee()
 	{
 		super();
 		employeeID = 0;
 		department = "";
 	}
    
    // The overloaded constructor with a string, int, and string as the input.
    // The ID and department are stored in their respective variables,
    // while the name input is sent to the super class's (Person) constructor.
    public Employee(String newName, String newDepartment, int newEmployeeID)
    {
    	super(newName);
    	employeeID = newEmployeeID;
    	department = newDepartment;
    }
    
    // A reset function which will has the same parameters as the constructor, but
    // will just allow a user to reset all the associated variables to new values, as
    // well as reset the variables through the super class.
    public void reset(String newName, String newDepartment, int newEmployeeID)
    {
    	super.setName(newName);
    	employeeID = newEmployeeID;
    	department = newDepartment;
    }
    
    // Returns the value of the employee's ID.
    public int getEmployeeID()
    {
    	return employeeID;
    }
    
    // Sets the employee ID to the passed value.
    public void setEmployeeID(int newEmployeeID)
    {
    	employeeID = newEmployeeID;
    }
    
    // Returns the name of the employee's department.
    public String getDepartment()
    {
    	return department;
    }
    
    // Sets the name of the department to the passed value.
    public void setDepartment(String newDepartment)
    {
    	department = newDepartment;
    }
    
    // Writes an output to the console.  Consists of calling the writeOutput()
    // method from the parent class (Person) followed by printing the department name
    // and employeeID number with accompanying labels.
    public void writeOutput()
    {
    	super.writeOutput();
    	System.out.println("Dept: " + department);
    	System.out.println("Employee ID: " + employeeID);
    }
    
    // Compares two Employee instances, by checking if their employee IDs and department names are the same,
    // as well as if their names are the same (Which is checked through the super class hasSameName() method).
    // This returns true if all checked values are the same, and false otherwise.
    public boolean equals(Employee otherEmployee)
    {
    	if((this.getEmployeeID() == otherEmployee.getEmployeeID()) && (this.getDepartment() == otherEmployee.getDepartment()) && super.hasSameName(otherEmployee)) return true;
    	return false;
    }
}
