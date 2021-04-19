package homeworks;

// Name: Maxwell Metzner (Section A)
// Pledge: I pledge my honor that I have abided by the Stevens Honor System.

public class Complexity{
	
	public static void main(String[] args) {
		//TEST CASES
		
		//method1(10);
		//method2(10);
		//method3(1000);
		//method4(100);
		//method5(10000);
	}
	
	/* EXAMPLE METHOD GIVEN

	void public method0 (int n) {
		int counter =0;
		for (i =0; i<n; i ++) {
			System.out.println(" Operation "+ counter );
			counter ++;
		}
	}*/
	
	public static void method1(int n) {//: a method that has time complexity O(n^2).
		int counter = 1;
		for (int i = 0; i < n; i++) {
			for (int j=0; j < n; j++) {
				System.out.println(counter);
			    counter++;
			}//nestled 2 loops of n complexity
		}	
	}
	public static void method2(int n) {//: a method that has time complexity O(n^3).
		int counter = 1;
		for (int i = 0; i < n; i++) {
			for (int j=0; j < n; j++) {
				for (int k=0; k < n; k++ ) {
					System.out.println(counter);
				    counter++;
				}//nestled 3 loops of n complexity
			}
		}	
	}
	public static void method3(int n) {//: a method that has time complexity O(log n).
		int counter = 1;
		for (int i = 1; i < n; i = i * 2){
			System.out.println(counter);
		    counter++;
		}//a single loop of log n complexity (loops log base 2 times truncated)
	}
	public static void method4(int n) {//: a method that has time complexity O(n log n).
		int counter = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < n; j = j * 2){
			    System.out.println(counter);
			    counter++;
			}//outer loop has complexity n and inner loop has complexity log n 
		}
	}
	public static void method5(int n) {//: a method that has time complexity O(log log n).
		int counter = 1;
		for (int i = 2; i < n; i = i * i^i ){
			for (int j = i * i; j < n; j = j * j^j){
				System.out.println("i" + i);
				System.out.println("j" + j);
				System.out.println(counter);
			    counter++;
				//outer loop has log n complexity and so does the inner loop
			}
		}
	}
	public static int method6(int n) {//: a method that has time complexity O(2^n).
		return 0;
	}
}