package chapter02;

import java.util.Scanner;

public class OperatorCalc {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		String opStr = sc.next();
		char op = opStr.charAt(0);
		
		double num1 = sc.nextDouble();
		double num2 = sc.nextDouble();
		
		switch (op) {
        case '+':
            System.out.println(num1 + "+" + num2 + "=" + (num1 + num2));
            break;
        case '-':
            System.out.println(num1 + "-" + num2 + "=" + (num1 - num2));
            break;
        case '*':
            System.out.println(num1 + "*" + num2 + "=" + (num1 * num2));
            break;
        case '/':
            System.out.println(num1 + "/" + num2 + "=" + (num1 / num2));
            break;
        default:
            System.out.println("error");
            break;
    }
		
//		String result = switch (opStr) {
//		case "+" -> num1 + "+" + num2 + "=" + (num1+num2);
//		case "-" -> num1 + "-" + num2 + "=" + (num1-num2);
//		case "*" -> num1 + "*" + num2 + "=" + (num1*num2);
//		case "/" -> num1 + "/" + num2 + "=" + (num1/num2);
//		
//		
//		
//		default -> "error";
//		};
//		
//		System.out.print(result);
		sc.close();
	}

}
