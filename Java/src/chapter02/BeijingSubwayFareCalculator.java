package chapter02;

import java.util.Scanner;

public class BeijingSubwayFareCalculator {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		

		int dist = scanner.nextInt();
		int price = 0;

		
		if (dist <= 0) {
			price = 0;
		} else if(dist <= 6) {
			price = 3;
		} else if(dist <= 12) {
			price = 4;
		} else if(dist <= 22) {
			price = 5;
		} else if(dist <= 32) {
			price = 6;
		} else{
			price = 6 + ((dist + 19 - 32)/20);
		}
		
		System.out.printf("price=%d", price);
		scanner.close();
	}

}
