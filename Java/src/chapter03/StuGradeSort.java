package chapter03;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;



public class StuGradeSort {
	public static class Stu{
		String name;
		int grade;
	}
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		Stu[] stugrade = new Stu[50];
		
		for (int i = 0; i < n; i++) {
			stugrade[i] = new Stu();
			stugrade[i].name = scanner.next();
			stugrade[i].grade = scanner.nextInt();
		}
//		for (int i = 0; i < n; i++) {
//			System.out.println(stugrade[i].name);
//		}
		Arrays.sort(stugrade,0,n,new Comparator<Stu>(){

			@Override
			public int compare(Stu o1, Stu o2) {
				return Integer.compare(o2.grade,o1.grade);
			}
			 
		});
		for (int i = 0; i < n; i++) {
		System.out.println("            "+stugrade[i].name+"   "+stugrade[i].grade);
		}
	}

}

