package homeworks;

// Name: Maxwell Metzner
// Pledge: I pledge my honor that I have abided by the Stevens Honor System

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class Anagrams {
	final Integer[] primes =  
			{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
			31, 37, 41, 43, 47, 53, 59, 61, 67, 
			71, 73, 79, 83, 89, 97, 101};
	Map<Character,Integer> letterTable;
	Map<Long,ArrayList<String>> anagramTable;

	Anagrams() {
		buildLetterTable();
		anagramTable = new HashMap<Long,ArrayList<String>>();
	}
	
	/**
	 * 	Initializes the letter table for the anagram.
	 */
	
	public void buildLetterTable() {
		HashMap<Character, Integer> newLetterTable = new HashMap<Character,Integer>();
		char letter = 'a';
		for (int i = 0; i != 26; i++) {
			newLetterTable.put((char) (letter + i), primes[i]);//Sets both the letter and prime by incrementing the character and prime number
		}
		this.letterTable = newLetterTable;
	}

	/**
	 * 	Adds word to the list 
	 * 
	 * @param s, the string that is being added to the list
	 */
	
	public void addWord(String s) {
		if (s.length() < 1) {// Throw an error if the string is empty
			throw new IllegalArgumentException();
		}
		if (anagramTable.containsKey(myHashCode(s))) {// If s is already in the table, replace it
			ArrayList<String> temp = anagramTable.get(myHashCode(s));
			temp.add(s);
			anagramTable.replace(myHashCode(s), temp);
		} else {
			ArrayList<String> temp = new ArrayList<String>();//Otherwise put it into the table
			temp.add(s);
			anagramTable.put(myHashCode(s), temp);
		}
	}
	
	/**
	 * 	Rotates the Nodes to the right, making sure to return the pivot
	 * so that it can be attached to a predecessor node.
	 * 
	 * @param s, the string that is being hashed
	 * @return long, gets the unique hash code for the letters used
	 */
	
	public long myHashCode(String s) {// hashes the given string
		Long hash = 1L;
		while (s.length() != 0) {// hashes head and loops around to tail
			hash *= letterTable.get(java.lang.Character.toLowerCase(s.charAt(0)));
			s = s.substring(1);
		}
	    return hash;
	}
	
	/**
	 * 	receives the name of a text file containing words, one per line, and builds the hash table anagramTable.
	 * 
	 * @param s, name of a text file containing words
	 */
	
	public void processFile(String s) throws IOException {
		FileInputStream fstream = new FileInputStream(s);
		BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
		String strLine;
		while ((strLine = br.readLine()) != null)   {
			this.addWord(strLine); 
		}
		br.close();
	}
	
	/**
	 * 	Identifies anagrams by hash and groups them together, checking for largest group of anagrams
	 * 
	 * @returns ArrayList<Map.Entry<Long,ArrayList<String>>>, the largest list of anagrams,
	 */
	
	public ArrayList<Map.Entry<Long,ArrayList<String>>> getMaxEntries() {
		ArrayList<Map.Entry<Long,ArrayList<String>>> newList = new ArrayList<Map.Entry<Long,ArrayList<String>>>();
		int numAnagrams = 0;
		for (Map.Entry<Long,ArrayList<String>> entry: anagramTable.entrySet()) { 
			if (entry.getValue().size() > numAnagrams) {//If it has more anagrams, "switch" to that anagram list
				newList.clear();
				newList.add(entry);
				numAnagrams = entry.getValue().size();
			} else {
				if (entry.getValue().size() == numAnagrams) {//If it is an anagram, add it to list
					newList.add(entry);
				}
			}
		}
		return newList;
	}
	
	/**
	 * 	Runs the program, initializing object and calling the dictionary being used
	 */
	
	public static void main(String[] args) {
		Anagrams a = new Anagrams();
		
		final long startTime = System.nanoTime();    
		try {
			a.processFile("words_alpha.txt");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		ArrayList<Map.Entry<Long,ArrayList<String>>> maxEntries = a.getMaxEntries();
		final long estimatedTime = System.nanoTime() - startTime;
		final double seconds = ((double) estimatedTime/1000000000);
		System.out.println("Time: "+ seconds);
		System.out.println("List of max anagrams: "+ maxEntries);
		
		System.out.println("Length of list of max anagrams : " + maxEntries.get(0).getValue().size());
		//Above line wasn't originally in the stub but the assignment sheet needs it for the "expected outcome" to be true
	}
}
