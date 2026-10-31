package chapter03;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;



public class IntersectionOfIntegers {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int n1 = sc.nextInt();
		int[] arr1 = new int[n1];
		for (int i = 0; i < n1; i++) {
			arr1[i] = sc.nextInt();
		}
		
		int n2 = sc.nextInt();
		int[] arr2 = new int[n2];
		for (int i = 0; i < n2; i++) {
			arr2[i] = sc.nextInt();
		}
		
		int[] intersection = getIntersection(arr1, arr2);
		if (intersection.length == 0) {
			return;
		}
		
		Arrays.sort(intersection);
		
		for (int i = intersection.length-1; i >= 0; i--) {
			System.out.print(intersection[i]);
			if (i>0) {
				System.out.print(" ");
			}
		}
	}
	public static int[] getIntersection(int[] arr1,int[] arr2) {
		int maxLen = Math.min(arr1.length, arr2.length);
		int[] tmp = new int[maxLen];
		int count = 0;
		
		for (int i = 0; i < arr1.length; i++) {
			for (int j = 0; j < arr2.length; j++) {
				if (arr1[i] == arr2[j] ) {
					tmp[count++] = arr1[i];
					break;
				}
			}
		}
		
		return Arrays.copyOf(tmp, count);
	}

}

