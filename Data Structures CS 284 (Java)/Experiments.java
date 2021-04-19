package exercises;

public class Experiments {
	
	public static int fact(int x) {
		if (x == 0) {
			return 1;
		} else {
			return x * fact(x - 1);
		}
	}
	
	public static int fib(int n) {
		if (n<=1) {
			return 1;
		} else {
			return fib(n-1) + fib(n-2);
		}
	}
	
	public static double newFib(double n, double old, double current) {
		if (n<=1) {
			return current;
		} else {
			return newFib(n-1,current, old+current);
		}
	}
	
	public static void main(String[] args) {
		System.out.println(newFib(57,1,1));
	}
}
