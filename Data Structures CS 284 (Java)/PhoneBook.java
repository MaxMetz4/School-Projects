package special_assignment;

// Name: Maxwell Metzner
// Pledge: I pledge my honor that I have abided by the Stevens Honor System.

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class PhoneBook {
	// Data fields
	/**
	* Each BSFamilyTree contains family members that share a first letter of their last name.
	*/
	public Map<Character, BSFamilyTree> directory;

	/**
     	* Creates a new phone book with an empty directory.
     	*/
	public PhoneBook() {
		HashMap<Character, BSFamilyTree> newDirectory = new HashMap<Character,BSFamilyTree>();
		char letter = 'A';
		for (int i = 0; i != 26; i++) {
			newDirectory.put((char) (letter + i), new BSFamilyTree());//Sets both the letter and prime by incrementing the character and prime number
		}
		this.directory = newDirectory;
	}

	/*
	 * Returns the instance of BSFamilyTree at the indicated letter
	 * Must accept lowercase letters as well as uppercase letters
	 */
	public BSFamilyTree getFamilyTree(char letter) {
		if (Character.isLowerCase(letter) == true) {
			letter = (char) (letter - 32);//converts lowercase to uppercase
		}
		if (directory.get(letter) == null) {
			return null;
		}
		return directory.get(letter);
	}

	/*
	 * Adds a FamilyTreeNode to the PhoneBook
	 */
	public void addFamily(String lastName) {
		BSFamilyTree desiredTree = getFamilyTree(lastName.charAt(0));//Takes beginning character of last name
		desiredTree.addFamilyTreeNode(lastName);
	}

	/*
	 * Adds a Person to the PhoneBook
	 * If a FamilyTreeNode with the given last name doesn't currently exist, create the FamilyTreeNode
	 */
	public void addPerson(String lastName, String firstName, String phoneNumber) {
		BSFamilyTree desiredTree = getFamilyTree(lastName.charAt(0));//Find Starting Letter
		if (desiredTree.doesFamilyExist(lastName) == false) {
			desiredTree.addFamilyTreeNode(lastName);
		}
		FamilyTreeNode desiredNode = desiredTree.getFamilyTreeNode(lastName);//Find Family
		if (desiredNode.doesNumberExist(phoneNumber) == true || desiredNode.doesFamilyMemberExist(lastName, firstName) == true) {
			throw new IllegalArgumentException("Phone or person already exists");
		}
		desiredNode.addFamilyMember(lastName, firstName, phoneNumber);//Add person to Family
	}

	/*
	 * Finds the phone number of a person
	 * Returns 'Does not exist.' if not found.
	 */
	public String getPhoneNumber(String lastName, String firstName) {
		BSFamilyTree desiredTree = getFamilyTree(lastName.charAt(0));//Find Starting Letter
		if (desiredTree.doesFamilyExist(lastName) == false) {
			return "Does not exist.";
		}
		FamilyTreeNode desiredNode = desiredTree.getFamilyTreeNode(lastName);//Find Family
		if (desiredNode.doesFamilyMemberExist(lastName, firstName) == true) {
			return desiredNode.getPhoneNumberOfFamilyMember(lastName, firstName);//Take person from Family
		}
		return "Does not exist.";
	}

    	/**
     	* String representation of PhoneBook
     	*/
	public String toString() {
		for(Map.Entry<Character, BSFamilyTree> entry : directory.entrySet()) {
			System.out.println(entry.getKey());
		    System.out.println(entry.getValue().toString());
		}
		return null;
	}
	
	/*
	public static void main(String args[]) {
		PhoneBook myPhoneBook = new PhoneBook();
		myPhoneBook.toString();
		myPhoneBook.addFamily("Wumbo");
		myPhoneBook.addPerson("Wumbo", "Spongebob", "1234567890");
		myPhoneBook.addPerson("Wumbo", "Patrick", "2345678901");
		myPhoneBook.addFamily("Smith");
		myPhoneBook.addPerson("Smith", "Morty", "3456789012");
		myPhoneBook.addPerson("Smith", "Beth", "4567890123");
		myPhoneBook.toString();
	}
	*/
}
