package chapter02;

import java.util.Scanner;

public class DigitSum {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int num  = scanner.nextInt();
		System.out.println(sum(num));

	}

	public static int sum(int num) {
		int res = 0;
		while (num > 0) {
			res += num % 10;
			num/=10;
		}
		return res;
	}
}
