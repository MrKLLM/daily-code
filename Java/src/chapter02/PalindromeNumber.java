package chapter02;

import java.util.Iterator;
import java.util.Scanner;

public class PalindromeNumber {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int a  = scanner.nextInt();
		int b  = scanner.nextInt();
		for (int i = a; i <= b; i++) {
			if (isPalindrome(i)) {
				System.out.println(i);
			}
		}
	}
	
	public static boolean isPalindrome(int num) {
	    // 如果是负数，直接返回 false
	    if (num < 0) {
	        return false;
	    }
	    
	    int origin = num;
	    int reverse = 0;
	    while (num>0) {
			int digit = num%10;
			reverse = reverse * 10 + digit;
			num/=10;
		}
	    return origin == reverse;
	}
	
//	public static boolean isPalindromeStr(int num) {
//	    // 如果是负数，直接返回 false
//	    if (num < 0) {
//	        return false;
//	    }
//	    
//	    // 1. int 转 String
//	    String originalStr = String.valueOf(num); 
//	    
//	    // 2. 使用 StringBuilder 反转字符串
//	    String reversedStr = new StringBuilder(originalStr).reverse().toString();
//	    
//	    // 3. 比较原字符串和反转后的字符串是否相等
//	    return originalStr.equals(reversedStr);
//	}

}
