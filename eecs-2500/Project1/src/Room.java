/**
 * Grant Knowlton
 * 
 * A class to represent a single room.
 * 
 * Two constructors are supplied, one being a default constructor that creates a person with number -1 in both room slots.
 * The other takes in two people and creates a room with them as the occupants.
 * 
 * The only field present is the Occupants array, which is meant to hold the two occupants of the room.
 * 
 * Provides a toString method to allow for easier printing to the console.  All it requires is a supplied room number.
 */

public class Room {
	public Person[] Occupants;

	// Default constructor, makes a room of two people with numbers both being -1.
	public Room() {
		this(new Person(-1), new Person(-1));
	}
	
	// Constructor to create a room give the two occupant people.
	public Room(Person person1, Person person2) {
		Occupants = new Person[2];
		Occupants[0] = person1;
		Occupants[1] = person2;
	}
	
	// To string method, prints the occupants, the passed room number, and some minor flavor text + formatting.
	public String toString(int roomNumber) {
		return "Room " + roomNumber + ":     " + Occupants[0].toString() + " and " + Occupants[1].toString();
	}
}
