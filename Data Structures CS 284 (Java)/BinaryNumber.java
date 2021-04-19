package homeworks;
import java.util.Arrays;

// Name: Maxwell Metzner (Section A)
// Pledge: I pledge my honor that I have abided by the Stevens Honor System.

public class BinaryNumber{
	
	public static void main(String[] args) { //these are my test cases that I used to make sure all the methods were working correctly
		BinaryNumber a = new BinaryNumber(4);
		BinaryNumber b = new BinaryNumber("0101");
		BinaryNumber c = new BinaryNumber("1100");
		BinaryNumber d = new BinaryNumber("111000");
		BinaryNumber e = new BinaryNumber("010101");
		System.out.println("1.)" +(a.data).toString());
		System.out.println("2.)" +(b.data).toString());
		System.out.println("3.)" +a.getLength());
		System.out.println("4.)" +b.getLength());
		System.out.println("5.)" +(a.getInnerArray()).toString());
		System.out.println("6.)" +(b.getInnerArray()).toString());
		System.out.println("7.)" +a.getDigit(2));
		System.out.println("8.)" +b.getDigit(2));
		System.out.println("9.)" +a.toDecimal()); 
		System.out.println("10.)" +b.toDecimal());
		a.bitShift(1,2);
		System.out.println("11.)" +(a.data).toString()); 
		b.bitShift(-1,2);
		System.out.println("12.)" +(b.data).toString());
		System.out.println("13.)" +(bwor(d,e)).toString());
		System.out.println("13.)" +(bwand(d,e)).toString());
		d.add(e);
		System.out.println("14.)" +(d.data).toString());
	}
	
		//data fields
		private int data[];
		private int length;
		
		//constructors
		BinaryNumber(int length) {//creates int[] of the specified length, and it is filled with 0's
			this.data = new int[length];
			this.length = length;
		}
		BinaryNumber(String str) {
			this.length = str.length();
			this.data = new int[length];
			String[] result = str.split("");//separates the numbers on str into a string array that can be reformed into an int array
		    for(int i=0; i<this.length; i++) {
		    	this.data[i] = Integer.parseInt(result[i]);
		    }	
		}
			
		//Methods
		
		public int getLength() {//I gave the objects a length field so this returns that
			return length;
		}
		public int[] getInnerArray() {//I gave the objects a data field so this returns that
			return data;
		}
		public int getDigit(int index) {
			return data[index];
		}
		public int toDecimal() {//the exponent value decreases after each term of the binary array, and adds each value to sum
			double exponent = length-1;
			double sum = 0;
			for(int i=0; i<length; i++) {
				double d = data[i];
				sum = sum + (d * Math.pow(2, exponent));
				exponent--;
			}
			return (int) sum;
		}
		public void bitShift(int direction, int amount) {//creates 0's on the leading or ending of the original int array
			int[] newArray = new int[length+amount];
			if(direction == 1) {
				for(int i=0; i<amount; i++) {
					newArray[i] = 0;
				}
				for(int i=amount; i<(amount+length); i++) {
					newArray[i] = data[i-amount];
				}
				data = newArray;
			}
			if(direction == -1) {
				for(int i=0; i<(length); i++) {
					newArray[i] = data[i];
				}
				for(int i=(length); i<(length+amount); i++) {
					newArray[i] = 0;
				}
				data=newArray;
			}
		}
		public static int[] bwor(BinaryNumber bn1, BinaryNumber bn2) {//checks first value of bn1 against bn2 and puts a 1 if either has a 1
			int[] newArray = new int[bn1.length];
			if(bn1.length == bn2.length) {
				for(int i=0; i<bn1.length; i++) {
					if((bn1.data[i]==1) || (bn2.data[i]) == 1) {
						newArray[i] = 1;
					} else {
						newArray[i] = 0;
					}
				}
			} else {
				throw new IllegalArgumentException();
			}
			return newArray;
		}
		public static int[] bwand(BinaryNumber bn1, BinaryNumber bn2) {//similar to bwor except using "&&" instead of "||"
			int[] newArray = new int[bn1.length];
			if(bn1.length == bn2.length) {
				for(int i=0; i<bn1.length; i++) {
					if((bn1.data[i]==1) && (bn2.data[i]) == 1) {
						newArray[i] = 1;
					} else {
						newArray[i] = 0;
					}
				}
			} else {
				throw new IllegalArgumentException();
			}
			return newArray;
		}
		public void add(BinaryNumber aBinaryNumber) {//calculates a remainder based on the addition
		int[] newArray = new int[aBinaryNumber.length];
		int remainder = 0;
			if(this.length == aBinaryNumber.length) {
				for(int i=aBinaryNumber.length-1; i>(-1); i--) {
					remainder = remainder + (this.data[i] + aBinaryNumber.data[i]);
					if(remainder == 0) {
						newArray[i] = 0;
						remainder = 0;
					}
					if(remainder == 1) {
						newArray[i] = 1;
						remainder = 0;
					}
					if(remainder == 2) {
						newArray[i] = 0;
						remainder = 1;
					}
					if(remainder == 3) {
						newArray[i] = 1;
						remainder = 1;
					}
				}
				this.data = newArray;//if the array cannot fit the addition because there is a remainder at the end, this creates a new free spot
				if(remainder == 1) {
					this.bitShift(1,1);
					this.data[0] = 1;
				}
			} else {
			throw new IllegalArgumentException();
			}

		}
		public String toString() {//translates the int array into a string
			String strArray[] = new String[this.data.length];

			for (int i = 0; i < this.data.length; i++)
				
				strArray[i] = String.valueOf(this.data[i]);
			 String str = String.format("%d",this.data);  
			 return Arrays.toString(strArray);
		}
		
		//I meant to do something like this but it kept returning object locations :(
		
		/*
		public String toString() {
			int[] arr = this.data;
			String str = "";
			for(int i=0; i<arr.length; i++) {
				str = str + ("[" + Integer.toString(arr[i]) + "], ");
			}
			return str;
		}
		*/
}
