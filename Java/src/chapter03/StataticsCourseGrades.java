package chapter03;

import java.util.Iterator;
import java.util.Scanner;

public class StataticsCourseGrades {

	public static void main(String[] args) 	{
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		double[] course = new double[100];
		double sum = 0;
		
		for(int i = 0;i < n;i++) {
			course[i] = sc.nextDouble();
			sum+=course[i];
		}
		
		 double ave = sum/n;
		 System.out.printf("%.1f",ave);
		 System.out.println();
		 for (int i = 0; i < n; i++) {
			 if (course[i]<ave) {
				System.out.println((i+1)+":"+(course[i]));
			}
			
		}
	}

}

