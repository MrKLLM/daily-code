package chapter02;

import java.util.Scanner;

public class DayOfTheYear {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int year = scanner.nextInt();
		int month = scanner.nextInt();
		int date = scanner.nextInt();
		boolean isrun = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
//        int daysBeforeMonth = switch (month) {
//        case 1 -> 0;
//        case 2 -> 31;
//        case 3 -> isrun ? 60 : 59; // 1月(31) + 2月(28/29)
//        case 4 -> isrun ? 91 : 90;
//        case 5 -> isrun ? 121 : 120;
//        case 6 -> isrun ? 152 : 151;
//        case 7 -> isrun ? 182 : 181;
//        case 8 -> isrun ? 213 : 212;
//        case 9 -> isrun ? 244 : 243;
//        case 10 -> isrun ? 274 : 273;
//        case 11 -> isrun ? 305 : 304;
//        case 12 -> isrun ? 335 : 334;
//        default -> 0; // 容错处理
//        };
		int daysBeforeMonth = 0;
		switch (month) {
        case 1:
            daysBeforeMonth = 0;
            break;
        case 2:
            daysBeforeMonth = 31;
            break;
        case 3:
            daysBeforeMonth = isrun ? 60 : 59;
            break;
        case 4:
            daysBeforeMonth = isrun ? 91 : 90;
            break;
        case 5:
            daysBeforeMonth = isrun ? 121 : 120;
            break;
        case 6:
            daysBeforeMonth = isrun ? 152 : 151;
            break;
        case 7:
            daysBeforeMonth = isrun ? 182 : 181;
            break;
        case 8:
            daysBeforeMonth = isrun ? 213 : 212;
            break;
        case 9:
            daysBeforeMonth = isrun ? 244 : 243;
            break;
        case 10:
            daysBeforeMonth = isrun ? 274 : 273;
            break;
        case 11:
            daysBeforeMonth = isrun ? 305 : 304;
            break;
        case 12:
            daysBeforeMonth = isrun ? 335 : 334;
            break;
        default:
            daysBeforeMonth = 0; // 容错处理
            break;
    }
        int totalDays = daysBeforeMonth + date;
        System.out.println(totalDays);
	}

}
