package chapter02;

import java.util.Scanner;

public class RMB_Currency_Exchange {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int money = sc.nextInt();
		
		int n1 = money/10;
		int n2 = (money%10)/5;
		int n3 = (money%10%5)/2;
		int n4 = (money%10%5%2)/1;
		
		System.out.printf("%d %d %d %d", n1,n2,n3,n4);

	}

}
