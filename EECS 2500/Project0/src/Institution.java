/*
 * Grant Knowlton
 * 
 * Institution class, which holds all
 * the information about a specific
 * institution.
 * 
 * Also provides the toString() override which prints
 * an institution in a certain format to the console.
 * 
 */

package proj;

public class Institution 
{
	// Fields for the names.
	private String name;
	private String nickname;
	
	// Fields for the location.
	private String city;
	private String state;
	
	// Fields for the founding date and
	// student body size.
	private int foundingYear;
	private int studentBodySize;
	
	// Default constructor, sets variables to new strings or 0 (for ints).
	public Institution()
	{
		name = new String();
		nickname = new String();
		city = new String();
		state = new String();
		foundingYear = 0;
		studentBodySize = 0;
	}
	
	public String getNickname() 
	{
		return nickname;
	}
	
	public void setNickname(String nickname) 
	{
		this.nickname = nickname;
	}
	
	public String getCity() 
	{
		return city;
	}
	
	public void setCity(String city) 
	{
		this.city = city;
	}
	
	public String getState() 
	{
		return state;
	}
	
	public void setState(String state) 
	{
		this.state = state;
	}
	
	public int getFoundingYear() 
	{
		return foundingYear;
	}
	
	public void setFoundingYear(int foundingYear) 
	{
		this.foundingYear = foundingYear;
	}
	
	public int getStudentBodySize() 
	{
		return studentBodySize;
	}
	
	public void setStudentBodySize(int studentBodySize) 
	{
		this.studentBodySize = studentBodySize;
	}
	
	public String getName() 
	{
		return name;
	}
	
	public void setName(String name) 
	{
		this.name = name;
	}
	
	/*
	 * 	Prints an institution in the format of:
	 * 	
	 * 	name (nickname): city, state
	 * 	Founded in foundingYear.
	 * 	Approx. student body size: studentBodySize
	 */
	public String toString()
	{
		String output = "";
		
		output += name;
		output += " (" + nickname + "): ";
		output += city + ", ";
		output += state + ". \n";
		output += "Founded in " + foundingYear + ".\n";
		output += "Approx. student body size: " + studentBodySize;
		
		return output;
	}
}
