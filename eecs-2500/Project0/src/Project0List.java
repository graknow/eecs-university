/*
 * Grant Knowlton
 * 
 * This is the main class, which holds
 * the array for the institution list
 * as well as all of the methods to
 * interact with it.  Also implements
 * the user input and output.
 * 
 * This program is intended to create a
 * list of institutions (Which is a collection
 * of a few pieces of data), provide means
 * to interact with the collection, and provide
 * a means to store the created list of institutions
 * to a file.
 */

package proj;

import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;

import java.util.ArrayList;

public class Project0List
{
	private ArrayList<Institution> runningInstitutionList = new ArrayList<Institution>();
	
	public static void main(String[] args) throws IOException
	{
		Scanner scnr = new Scanner(System.in);				// Creates a scanner for input.
		
		Project0List activeList = new Project0List();		// Creates an instance of the main class, which is one copy
															// of the institution list + accompanying methods.
		
		String saveFilePath = "saved.txt";					// Place to store the data when "save" is commanded.
		
		boolean programStatus = true;						// Keeps track of whether the program is still running or needs to stop.
		String userInput = "";								// Location to keep the user's current command input.
		
		// While the program is running:
		while(programStatus)
		{
			// Formatted print of the command prompting.
			System.out.println();
			System.out.println();
			System.out.print("Please enter a command - ");
			
			// Take in the user's next input.
			userInput = scnr.nextLine();
			
			// Determines which command was entered, ignoring character cases
			switch(userInput.toLowerCase())
			{
			case "add":
				// Calls add on active instance, passing scnr to allow for reading new data.
				activeList.add(scnr);
				break;
				
			case "list":
				// Calls list on active instance, passing nothing as this just prints each instance in the array list.
				activeList.list();
				break;
				
			case "delete":
				// Calls delete on active instance, passing scnr to read which institution to delete.
				activeList.delete(scnr);
				break;
				
			case "save":
				// Calls save on active instance, passing the path to the save file.
				activeList.save(saveFilePath);
				break;
				
			case "search":
				// Calls search on active instance, passing scnr to read which institution to search for.
				activeList.search(scnr);
				break;
				
			case "help":
				// Calls help on active instance, passing nothing as this simply prints the valid command list.
				activeList.help();
				break;
				
			case "exit":
				// Calls exit on active instance, setting the program status to false.  Also closes the scnr.
				scnr.close();
				programStatus = activeList.exit();
				break;
				
			default:
				// When an unrecognized command is called, this will inform the user to use help for a list of valid commands.
				System.out.println();
				System.out.println("Unrecognized command!  Type help for command list.");
				break;
			}
		}
	}
	
	/*
	 * 	The add command:
	 * 	Creates a new institution to set data to.  Prompts user
	 * 	for the name (If the name exists the add command prints error
	 * 	and exits).  If name prompting was successful, prompts the user for
	 * 	the rest of the information and sets the next slot in the array list
	 * 	to the institution made here.
	 */
	public void add(Scanner scnr)
	{
		// Temporary institution to plug data into.
		Institution tmpInstitution = new Institution();
		
		System.out.println();
		
		// Sets name.
		System.out.print("What is the institution's name? - ");
		tmpInstitution.setName(scnr.nextLine());
		
		// If name exists already, print error and return to command prompt.
		if(getNameIndex(tmpInstitution.getName()) != -1)
		{
			System.out.println();
			System.out.println("The institution list already contains this university!");
			return;
		}
		
		// Sets nickname
		System.out.print("What is the institution's nickname? - ");
		tmpInstitution.setNickname(scnr.nextLine());
		
		// Sets city
		System.out.print("What city is the institution in? - ");
		tmpInstitution.setCity(scnr.nextLine());
		
		// Sets state
		System.out.print("What state is the institution in? - ");
		tmpInstitution.setState(scnr.nextLine());
		
		// Sets year founded
		System.out.print("What year was the institution founded? - ");
		tmpInstitution.setFoundingYear(scnr.nextInt());
		
		// Sets approx. student body size
		System.out.print("What is the approximate size of the institution's student body? - ");
		tmpInstitution.setStudentBodySize(scnr.nextInt());
		
		// Reads in an empty line as to not mess up the next user input.
		scnr.nextLine();
		
		// Store the temporary institution in the list at the first open index.
		runningInstitutionList.add(tmpInstitution);
	}
	
	/*
	 * 	The list command:
	 * 	Prints each entry in the array list to the console.
	 * 	If the list is empty, it prints a message saying it is empty.
	 */
	public void list()
	{
		// If empty, print it is empty.
		if(runningInstitutionList.size() == 0)
		{
			System.out.println();
			System.out.println("The list is currently empty.");
			return;
		}
		
		// If not empty, print each entry separated by a new line.
		for(int i = 0; i < runningInstitutionList.size(); i++)
		{
			System.out.println();
			System.out.println(runningInstitutionList.get(i));
		}
	}
	
	/*
	 * 	The delete command:
	 * 	Prompts the user for an input, and will determine if an entry's
	 * 	name or nickname matched the input.  If an instance matches either,
	 * 	it will delete the found instance.
	 */
	public void delete(Scanner scnr)
	{
		System.out.println();
		System.out.print("What is the official name of the institution you want to delete? - ");
		
		// Stores the institution to delete, sets a variable for the index to delete.
		String institutionNameToDelete = scnr.nextLine();
		int indexToDelete = 0;
		
		// If name is not found, check for nickname.  If nickname not found, print error saying institution doesn't exist.
		if((indexToDelete = getNameIndex(institutionNameToDelete)) == -1)
		{
			System.out.println();
			System.out.println("That institution's official name isn't in the list, therefore it cannot be deleted!");
			return;
		}
		
		// If index found, delete the instance at the index.
		runningInstitutionList.remove(indexToDelete);
		System.out.println();
		System.out.println("Successfully deleted.");
	}
	
	/*
	 * 	The save command:
	 * 	Creates a file writer, clears the file (To wrtie new data).  Creates
	 * 	a string to put the save data temporarily, then adds this string to the save
	 * 	file.
	 */
	public void save(String saveFilePath)
	{
		try 
		{
			// Creates file writer and clears it.
			FileWriter saveWriter = new FileWriter(saveFilePath);
			saveWriter.flush();
			
			// Tmp data string.
			String saveData = "";
			
			// Add each instance in the array list to the tmp printout.
			for(int i = 0; i < runningInstitutionList.size(); i++)
			{
				Institution currInst = runningInstitutionList.get(i);
				
				saveData += currInst.toString();
				saveData += "\n\n";
			}
			
			// Add the tmp string to the file.
			saveWriter.write(saveData);
			
			System.out.println();
			System.out.println("Successfully saved the data to the file!");
			
			// Close the writer.
			saveWriter.close();
		} 
		// If file write fails, prints error and stack trace.
		catch (IOException e) 
		{
			System.out.println();
			System.out.println("Failed to save file!  Error statement:");
			System.out.println();
			
			e.printStackTrace();
		}
	}
	
	/*
	 * 	The search command:
	 * 	Takes in a string input.  If the string matches the name or nickname of an instance
	 * 	in the list, it will print the full data entry of the instance.  Otherwise it says the 
	 * 	institution wasn't found.
	 */
	public void search(Scanner scnr)
	{
		System.out.println();
		System.out.print("What is the name/nickname of the university you would like to find? - ");
		
		// Store the input for the thing to find.
		String nameOrNicknameToFind = scnr.nextLine();
		int indexOfSearchedInstitution = 0;
		
		System.out.println();
		
		// Searches for the name, if found print the entry.
		if((indexOfSearchedInstitution = getNameIndex(nameOrNicknameToFind)) != -1)
		{
			System.out.println("The institution's name was found in the list.  Here are its details: ");
		}
		// Searches for the nickname, if found print the entry.
		else if((indexOfSearchedInstitution = getNicknameIndex(nameOrNicknameToFind)) != -1)
		{
			System.out.println("The institution's nickname was found in the list.  Here are its details: ");
		}
		// Not found in list, print that it wasn't found.
		else
		{
			System.out.println("The institution was not found in the list.");
			return;
		}
		// Only reaches this point of the institution was found, and will thus print the entry to the console.
		System.out.println(runningInstitutionList.get(indexOfSearchedInstitution));
	}
	
	/*	The help command:
	 *	Prints the list of valid commands.
	 */
	public void help()
	{
		System.out.println();
		System.out.println("The valid commands are:");
		System.out.println("add, list, delete, save, search, help, exit");
	}
	
	/*
	 * 	The exit command:
	 * 	Simply returns false to set the programStatus variable to false;
	 */
	public boolean exit()
	{
		return false;
	}
	
	/*
	 *  A function to get the index of the entry in the list whose name matches the passed string.
	 *  If the name couldn't be found, it returns -1.
	 */
	public int getNameIndex(String nameToFind)
	{
		for(int i = 0; i < runningInstitutionList.size(); i++)
		{
			if(runningInstitutionList.get(i).getName().equalsIgnoreCase(nameToFind))
				return i;
		}
		return -1;
	}
	
	/*
	 *  A function to get the index of the entry in the list whose nickname matches the passed string.
	 *  If the name couldn't be found, it returns -1.
	 */
	public int getNicknameIndex(String nicknameToFind)
	{
		for(int i = 0; i < runningInstitutionList.size(); i++)
		{
			if(runningInstitutionList.get(i).getNickname().equalsIgnoreCase(nicknameToFind))
				return i;
		}
		return -1;
	}
}