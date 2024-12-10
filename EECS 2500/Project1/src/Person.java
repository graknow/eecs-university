/**
 * Grant Knowlton
 * 
 * A class to represent a single person.
 * 
 * Two constructors are applied.  One for if there is just a person number supplied.  This doesn't initialize the preference list.
 * The other constructor is for if the person number and the number of people are supplied, which will assign the person number and create an array with
 * the size equal to the number of people.  It assigns this array to the personPreference field, and initializes the index of the person's self to -1.
 * 
 * There are three fields, one for the person number, one for the availability of the person, and one for the list of preferences for each other person.
 * 
 * There is a get/set method for interacting with the personPreference array.  There is also a pair of get/set methods for accessing the availability.  The PersonNumber field only has a
 * get method, as it ideally shouldn't ever change.  Finally there is a toString method, which provides a formatted printing in the form of "Person [personNumber]".
 */

public class Person {
	private int personNumber;

	private boolean availability;
	
	private int personPreference[];

	// Constructor for the case of just having a person number.  personPreference is left as null.
	public Person(int personNum) {
		personNumber = personNum;
		availability = true;
	}
	
	// Constructor for the case of having both the person number and the total number of people.
	public Person(int personNum, int count) {
		personPreference = new int[count];
		personNumber = personNum;

		// The person's preference for themself is set to -1.
		personPreference[personNum] = -1;

		availability = true;
	}
	
	public void setPreferenceToPerson(int otherPersonNumber, int rank) {
		// The other person's number is used as the index to facilitate the production of functions.
		// It is easier to compare preferences for a specific person when you can just check the value at the same index for two people.
		// This mainly makes checking stable arrangements eaiser.
		personPreference[otherPersonNumber] = rank;
	}
	
	public int getPreferenceForPerson(int otherPersonNumber) {
		// The other person's number is used as the index to facilitate the production of functions.
		// It is easier to compare preferences for a specific person when you can just check the value at the same index for two people.
		// This mainly makes checking stable arrangements eaiser.
		return personPreference[otherPersonNumber];
	}

	public void setAvailability(boolean status) {
		availability = status;
	}

	public boolean isAvailable() {
		return availability;
	}

	public int getPersonNumber() {
		return personNumber;
	}
	
	// Simply prints "Person " followed by the person number.
	public String toString() {
		return "Person " + personNumber;
	}
}
