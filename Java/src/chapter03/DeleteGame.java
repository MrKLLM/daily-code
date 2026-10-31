package chapter03;

import java.util.Arrays;
import java.util.Iterator;
import java.util.Scanner;

public class DeleteGame {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int n = sc.nextInt();
		int m = sc.nextInt();
		int[][] arr1 = new int[n][m];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				arr1[i][j] = sc.nextInt();
			}
			
		}
		
		
		int[][] toDelete = new int[n][m]; //删除标记数组，默认为1，待删除为0
		for (int[] is : toDelete) {
			Arrays.fill(is, 1);
		}
		


		
		//按行检查
		for (int i = 0; i < n; i++) {
			int begin = 0;
			for (int j = 1; j <= m; j++) {
				if (j == m || arr1[i][begin] != arr1[i][j]) {
					if (j-begin >= 3) {
						for (int j2 = begin; j2 < j; j2++) {
							toDelete[i][j2] = 0; 
						}
					}
					begin = j;
				}
					
			}
				
		}
		
		// 按列检查连续段
		for (int j = 0; j < m; j++) {
		    int begin = 0;
		    for (int i = 1; i <= n; i++) {
		        if (i == n || arr1[i][j] != arr1[begin][j]) {
		            if (i - begin >= 3) {
		                for (int k = begin; k < i; k++) {
		                    toDelete[k][j] = 0;
		                }
		            }
		            begin = i;
		        }
		    }
		}
		for (int i = 0; i < n; i++) {
			if (i != 0) {
			System.out.println();
			}
		    for (int j = 0; j < m; j++) {
		    	if (toDelete[i][j]==1) {
					System.out.print(arr1[i][j] + " ");
				}else {
					System.out.print(0 + " ");
				}
		    	
		    }
		}
//		for (int i = 0; i < n; i++) {
//			if (i != 0) {
//				System.out.println();
//			}
//			for (int j = 0; j < m; j++) {
////				System.out.print(arr1[i][j]+" ");
//				System.out.print(toDelete[i][j]+" ");
//			}
//		}
	}

}
