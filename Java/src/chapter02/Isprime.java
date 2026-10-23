package chapter02;

import java.util.Scanner;

public class Isprime {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int num  = scanner.nextInt();

		if (isprime(num)) {
			System.out.println(1);
		} else {
			System.out.println(0);
		}
	}

	public static boolean isprime(int num) {
		boolean is_prime = true;
		if (num == 2) {
			return true;
		}
		if (num <= 1 || num % 2 == 0) {
			return false;
		}
		
		for (int i = 3; i < num/2; i+=2) {
			if (num%i==0) {
				return false;
			}
		}
		
		return is_prime;
	}
}
