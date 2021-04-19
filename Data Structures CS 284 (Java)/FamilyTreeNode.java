package special_assignment;

//Name: Maxwell Metzner
//Pledge: I pledge my honor that I have abided by the Stevens Honor System.

import java.util.ArrayList;
import java.util.List;

public class FamilyTreeNode {
	// Data fields
	private String lastName;
	private List<Person> members;
	private FamilyTreeNode left;
	private FamilyTreeNode right;

	/**
     	* Constructor: initializes a new FamilyTreeNode
     	* given a lastName
     	*/
	public FamilyTreeNode(String lastName) {
        	this.lastName = lastName;
        	this.members = new ArrayList<Person>();
        	this.setLeft(null);
        	this.setRight(null);
	}

	/**
     	* Returns the last name of the FamilyTreeNode
     	*/
	public String getLastName() {
		return this.lastName;
	}

	/**
     	* Returns the arraylist of members in the FamilyTreeNode
     	*/
	public List<Person> getMembers() {
		return this.members;
		
	}

	public FamilyTreeNode getRight() {
		if (right == null) {
			return null;
			}
		return right;
	}

	public FamilyTreeNode getLeft() {
		if (left == null) {
			return null;
			}
		return left;
	}

	public void setLeft(FamilyTreeNode left) {
		this.left = left;
	}

	public void setRight(FamilyTreeNode right) {
		this.right = right;
	}

	/*
	 * Returns true if there is an instance of Person in the FamilyTreeNode that has
	 * the same first and last name provided Return false otherwise
	 */
	public boolean doesFamilyMemberExist(String lastName, String firstName) {
		for (Person temp : this.members) {
			if (temp.getFirstName() == firstName && temp.getLastName() == lastName) {//Iterate through members, looking for desired person
				return true;
			}
		}
		return false;
	}

	/**
	 * Returns true if there is an instance of Person in the FamilyTreeNode whose
	 * phone number matches the one provided Returns false otherwise
	 */
	public boolean doesNumberExist(String phoneNumber) {
		for (Person temp : this.members) {
			if (temp.getPhoneNumber() == phoneNumber) {//Iterate through members, looking for phone number
				return true;
			}
		}
		return false;
	}

	/*
	 * Adds a Person to this FamilyTreeNode
	 * Throw an exception if the last name provided does not match the last name of the FamilyTreeNode
	 */
	public void addFamilyMember(String lastName, String firstName, String phoneNumber) {
		if (this.lastName != lastName) {
			throw new IllegalArgumentException("Last name does not match");
		}
		if (doesFamilyMemberExist(lastName, firstName) == true) {
			throw new IllegalArgumentException("Person already exists");
		}
		if (doesNumberExist(phoneNumber) == true) {
			throw new IllegalArgumentException("Number already exists");
		}
		Person newPerson = new Person(lastName, firstName, phoneNumber);//Make sure person dosen't already exist, otherwise add it
		this.members.add(newPerson);
	}

	/**
	 * Adds a Person to this FamilyTreeNode
	 * Throw an exception if the last name provided does not match the last name of the FamilyTreeNode
	 */
	public void addFamilyMember(Person person) {
		if (person.getLastName() != lastName) {
			throw new IllegalArgumentException("Last Name does not match");
		}
		if (doesFamilyMemberExist(person.getLastName(), person.getFirstName()) == true) {
			throw new IllegalArgumentException("Person already exists");
		}
		if (doesNumberExist(person.getPhoneNumber()) == true) {
			throw new IllegalArgumentException("Number already exists");//Same as other addFamilyMember, if person dosen't already exist, add it
		}
		members.add(person);
	}

	/*
	 * Returns the phone number of the person in the family with the given phone
	 * number Returns "Does not exist." if not found
	 */
	public String getPhoneNumberOfFamilyMember(String lastName, String firstName) {
		if (this.doesFamilyMemberExist(lastName, firstName)  == true) {
			for (Person temp : this.members) {
				if (temp.getFirstName() == firstName && temp.getLastName() == lastName) {//Searches members for family member, then retrieves their number
					return temp.getPhoneNumber();
				}
			}
		}
		return "Does not exist.";
	}

	/*
	 * toString method Ex: [] [John Smith (5551234567), May Smith (5551234568),
	 * April Smith (5551234569), August Smith (5551234570)]
	 */
	public String toString() {
		return members.toString();//ArrayList already comes with toString functionality
	}
	/*
	public static void main(String args[]) {
		FamilyTreeNode node = new FamilyTreeNode("Wumbo");
		node.addFamilyMember("Wumbo", "Spongebob", "1234567890");
		node.addFamilyMember("Wumbo", "Patrick", "2345678901");
		if (node.doesFamilyMemberExist("Wumbo", "Spongebob") == true) {
			System.out.println("Test 1 Good");
		} else {
			System.out.println("Test 1 Failed");
		}
		
		if (node.doesFamilyMemberExist("Wumbo", "Bonelli") == false) {
			System.out.println("Test 2 Good");
		} else {
			System.out.println("Test 2 Failed");
		}
		
		if (node.doesNumberExist("1234567890") == true) {
			System.out.println("Test 3 Good");
		} else {
			System.out.println("Test 3 Failed");
		}
		
		if (node.doesNumberExist("0000000000") == false) {
			System.out.println("Test 4 Good");
		} else {
			System.out.println("Test 4 Failed");
		}
		System.out.println(node.getLastName());
		System.out.println(node);
	}
	*/
}