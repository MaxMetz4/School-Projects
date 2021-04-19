package exercises;

public class PalindromeChecker {
	// data fields
	private Stack<Character> s;
	private String str;
	
	// Constructor
	PalindromeChecker(String s) {
		fillStack(s);
		this.str=s;
	}
	
	private void fillStack(String s) {
		// consider using s.CharAt(i) to grab i-th char in s
	}
	
	private String reverseString() {
		return "no";
	}
	
	public Boolean isPalindrome() {
		return str.equals(reverseString());
	}
	
	public static void main(String[] args) {
		// code to test your solution 
		// include examples and non-examples
	}
}
