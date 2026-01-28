/*
 * Grant Knowlton
 * 
 * This is the main class of this project.  It contains the main method and a few methods to organize
 * the process of solving for stable room combinations.
 * 
 * There are 4 class instance fields that are used for things that will need to be passed around the program
 * a lot.  These fields are: 
 * 		scnr 		- A scanner object for reading inputs.
 * 		personArray - An array that will hold all of the people supplied by the user.
 * 		roomArray	- An array that will hold all of the rooms that the people from peopleArray can be organized into.
 * 		
 * 		workingStableArrangements - This stack will hold a known stable organization of the roomArray.  Used for backtracking
 * 		and knowing when the arrangement is complete/failed.
 * 
 * 	Other than the main method, there are a few methods that assist in code organization.  These are:
 * 		readData()				- Reads in the inputs from the user, and creates a person for each set of preferences.
 * 		findStableArrangement() - The method that is intended to handle most of the solving logic.  Will return true
 * 								  when a stable arrangement is found, false if one could not be found.
 * 		isArrangementStable()	- Determines if a supplied array of rooms is stable.
 * 		findNextRoom()			- Finds the next two people to put in a room for testing.
 */


import java.util.Scanner;

public class Project1 {
	// Variables to be used throughout the class.
	private Scanner scnr = new Scanner(System.in);
	
	private Person personArray[];
	private Room roomArray[];
	private StackImplementation<Room[]> workingStableArrangements;

	public static void main(String[] args) {
		// An instance of this class to use.
		Project1 mainProgram = new Project1();
		
		System.out.println("Input the number of people, followed by each person's"
					   + "\npreferences in the order of each person.  I.e. input"
					   + "\nperson 0 first, then person 1, etc...\n");
		
		// Read in the user data, then determine a stable arrangement if possible.
		mainProgram.readData();
		boolean success = mainProgram.findStableArrangement();

		System.out.println();

		// If stable arrangement found, print out the arrangement.  If not able to be found, print out a message stating so.
		if(success)
			for(int i = 0; i < mainProgram.roomArray.length; i++) {
				System.out.println(mainProgram.workingStableArrangements.peek()[i].toString(i));
			}
		else
			System.out.println("There is no possible stable arrangement of these people!");

		mainProgram.scnr.close();
	}

	// Holds all of the code related to reading the user's input.  Initializes the room array to default rooms.
	// Stores each created person into the personArray and assigns the preferences for each person.
	private void readData() {

		int personCount = scnr.nextInt();
		int roomCount = personCount / 2;
		
		personArray = new Person[personCount];
		roomArray = new Room[roomCount];

		// Initialize rooms to default rooms.
		for(int i = 0; i < roomCount; i++) {
			roomArray[i] = new Room();
		}

		// Initialize stack.
		workingStableArrangements = new StackImplementation<Room[]>(roomCount);
		
		// Initialize people to their numbers and preference lists.
		for(int i = 0; i < personCount; i++) {
			personArray[i] = new Person(i, personCount);
			for(int j = 0; j < personCount - 1; j++) {
				personArray[i].setPreferenceToPerson(scnr.nextInt(), j);
			}
		}
	}
	
	// This method holds all of the logic relating to finding the stable arrangement of rooms.  It returns true
	// if a stable arrangement is found, and returns false if it is not possible to form a stable arrangement.
	private boolean findStableArrangement() {
		// Tracks the number of rooms that are filled in the roomArray.	
		int currentRoomCount = 0;
		
		// The main solving loop.  Will run until the workingStableArrangements stack is full, as this would imply that
		// a stable roomArray was pushed a number of times equal to the number of rooms.  This indicates that the loop
		// found a stable arrangement for each room, thus indicating a found solution.
		while(!workingStableArrangements.isFull()) {
			roomArray[currentRoomCount] = findNextRoom(currentRoomCount);

			// This if statement runs if the current arrangement of rooms in roomArray completely stable.
			if(isArrangementStable(currentRoomCount)) {
				roomArray[currentRoomCount].Occupants[0].setAvailability(false);
				roomArray[currentRoomCount].Occupants[1].setAvailability(false);

				// Pushes a clone of the roomArray onto the stack, as this is curently a known stable state.
				workingStableArrangements.push(roomArray.clone());
				currentRoomCount++;
				continue;
			}

			// All of the code below runs if the made arrangement of rooms is not found to be stable.  It first backtracks
			// to the last known stable state by popping off of the stack and decrementing the currentRoomCount.

			roomArray = workingStableArrangements.pop();
			currentRoomCount--;

			// This secondary loop modifies and deconstructs the last known stable state until a new stable state is found.
			do {
				// If the next person would be outside of the range of personNumbers, then there is no new stable arrangement
				// found in this state.  Therefore, it is necessary to pop off of the stack again.
				if(roomArray[currentRoomCount].Occupants[1].getPersonNumber() + 1 == personArray.length) {
					// If there are no more stable arrangements to pop, then there is no possible stable arrangement.  The method will return false.
					roomArray[currentRoomCount].Occupants[1].setAvailability(true);
					if(workingStableArrangements.isEmpty()) {
						return false;
					}
					
					roomArray = workingStableArrangements.pop();
					currentRoomCount--;
				}
				// Change the second occupant of the most recent stable room to the person with the next personNumber.
				// Changes availabilities accordingly.
				roomArray[currentRoomCount].Occupants[1].setAvailability(true);
				roomArray[currentRoomCount].Occupants[1] = 
						personArray[roomArray[currentRoomCount].Occupants[1].getPersonNumber() + 1];
				roomArray[currentRoomCount].Occupants[1].setAvailability(false);
			} while(!isArrangementStable(currentRoomCount));  // Will continue doing this until new stable arrangement is found.

			workingStableArrangements.push(roomArray.clone());
			currentRoomCount++;
		}

		// If the loop ends, then a stable solution was found.  Returns true.
		return true;
	}

	// This method determines if an arragement of rooms is stable.  It does this by comparing each of the older rooms
	// with the newest added room to the array.  Returns false if arrangement is not stable, true otherwise.
	private boolean isArrangementStable(int numberOfMadeRooms) {
		// Creates 4 tmp people for easier readability.
		Person tmpPerson0 = roomArray[numberOfMadeRooms].Occupants[0];
		Person tmpPerson1 = roomArray[numberOfMadeRooms].Occupants[1];

		for(int i = 0; i < numberOfMadeRooms; i++) {
			Person tmpPerson2 = roomArray[i].Occupants[0];
			Person tmpPerson3 = roomArray[i].Occupants[1];

			// The logic assigns person0 and 1 to 1 room, and person2 and 3 to another room.

			// If person0 prefers person2 more than person1, and person2 prefers person0 more than person3, return false.
			if(tmpPerson0.getPreferenceForPerson(tmpPerson2.getPersonNumber()) < tmpPerson0.getPreferenceForPerson(tmpPerson1.getPersonNumber())
				&& tmpPerson2.getPreferenceForPerson(tmpPerson0.getPersonNumber()) < tmpPerson2.getPreferenceForPerson(tmpPerson3.getPersonNumber()))
			{
				return false;
			}
			// If person1 prefers person2 more than person0, and person2 prefers person1 more than person3, return false.
			if(tmpPerson1.getPreferenceForPerson(tmpPerson2.getPersonNumber()) < tmpPerson1.getPreferenceForPerson(tmpPerson0.getPersonNumber())
				&& tmpPerson2.getPreferenceForPerson(tmpPerson1.getPersonNumber()) < tmpPerson2.getPreferenceForPerson(tmpPerson3.getPersonNumber()))
			{
				return false;
			}
			// If person0 prefers person3 more than person1, and person3 prefers person0 more than person2, return false.
			if(tmpPerson0.getPreferenceForPerson(tmpPerson3.getPersonNumber()) < tmpPerson0.getPreferenceForPerson(tmpPerson1.getPersonNumber())
				&& tmpPerson3.getPreferenceForPerson(tmpPerson0.getPersonNumber()) < tmpPerson3.getPreferenceForPerson(tmpPerson2.getPersonNumber()))
			{
				return false;
			}
			// If person1 prefers person3 more than person0, and person3 prefers person1 more than person2, return false.
			if(tmpPerson1.getPreferenceForPerson(tmpPerson3.getPersonNumber()) < tmpPerson1.getPreferenceForPerson(tmpPerson0.getPersonNumber())
				&& tmpPerson3.getPreferenceForPerson(tmpPerson1.getPersonNumber()) < tmpPerson3.getPreferenceForPerson(tmpPerson2.getPersonNumber()))
			{
				return false;
			}
		}
		// Arrangement is stable.
		return true;
	}

	// Determines the next room to find based on the availability of the people.  If people aren't found, they will
	// stay as default people (where personNumber = -1).
	private Room findNextRoom(int currentRoomIndex) {
		Room tmpRoom = new Room();
		int numFound = 0;

		// When two available people are found, stop searching and return the found room.
		for(int i = 0; i < personArray.length && numFound < 2; i++) {
			if(personArray[i].isAvailable()) {
				tmpRoom.Occupants[numFound++] = personArray[i];
			}
		}

		return tmpRoom;
	}
}
