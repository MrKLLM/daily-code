#include "xy_ege.h"
#include<iostream>
#include<sstream>
#include <cmath>
using namespace std;

const double EPSILON = 1E-4;		// 误差

/**
 * @brief 绘图函数 大家可以定义自己的函数
 * 测试表达式 y = 0.4*x^2 - 2*x - 5;
 * @param x
 *
 * @return 返回值y
 */
double f1(double x)
{
	return 0.4 * x * x - 2 * x - 5;
}
double f2(double x)
{
	return 0.2 * x * x + 1.2 * x - 4;
}

double f2derv(double x)
{
	return 2 * 0.2 * x + 1.2;
}

bool LinearSearch(double (*fun)(double), double start, double stop, double step, double* root);
bool  binarySearch(double (*fun)(double), double start, double stop, double* root);
bool  regulaFalsiSearch(double (*fun)(double), double start, double stop, double* root);
bool newtonRaphsonSearch(double (*fun)(double), double (*fun_derv)(double), double start, double stop, double* root);


// 主程序入口
int main()
{
	open_xy_window(1024, 768, 20, true);		// 以默认参数开启一个窗口，绘制x y数轴

	// 绘制曲线 绘制 -10~10 区间的曲线，默认x轴放大
	drawF(f2, -10, 10, 0.1);

	// 遍历查找函数的根 0~10之间
	// 设置步长0.0001查找  步长太长容易越过，导致找不到，步长太细，很慢
	// 读者可以尝试 0.01
	double start = 0.0;		// 查找区间 开始点
	double stop = 8.0;		// 查找区间 结束点

	double step = 0.0001;	// 步长
	bool findRoot = false;	// 是否找到了根的数值解
	double root = start;	// 找到的根

//	findRoot = LinearSearch(f2, start, stop, step, &root);

//	findRoot = binarySearch(f2, start, stop, &root);

//	findRoot = regulaFalsiSearch(f2, start, stop, &root);

	findRoot = newtonRaphsonSearch(f2, f2derv, start, stop, &root);

	close_xy_window();

	return 0;
}



/**
 * @brief 线性枚举的方法查找函数的第一个根
 *
 * @param fun 函数地址
 * @param start
 * @param stop
 * @param step
 * @param root
 *
 * @return 是否搜索成功
 */
bool LinearSearch(double (*fun)(double), double start, double stop, double step, double* root)
{
	long count = 0;		// 统计尝试步数
	for (double i = start; i <= stop; i += step) {
		drawCircle(i, 0, 0.1, RED, 0);	// 绘制正在尝试的数值x
		double y = fun(i);	// 计算y
		count++;

		drawLine(i, 0, i, y, WHITE);
		// 图形界面输出
		ostringstream tmp_str;
		tmp_str << count << ":\tx:" << i << " y:" << y;
		drawString(5, 6, tmp_str.str().c_str(), WHITE);

		// 输出枚举信息
		cout << count << ":\tx = " << i  << " " << "y = " << y << endl;
		if (abs(y) < EPSILON) {			// 判断是不是根
			cout << "找到了" << i << "用了" << count << "步" << endl;
			(*root) = i;
			return true;
		}

		pausedByMouseLeft();	// 鼠标左键 暂停 恢复
	}

	return false;		//找不到
}

/**
 * @brief 二分法查找函数fun的根
 *
 * @param fun 函数地址
 * @param start 开始点
 * @param stop 结束点
 * @param root 找到的根
 *
 * @return 是否找到
 */
bool  binarySearch(double (*fun)(double), double start, double stop, double* root)
{
	double txt_y = -1;						// 提示文本的y轴
	double txt_x = -14;						// 提示文本的x轴

	// 函数有效性检查
	// 垂直线判断
	if (abs(start - stop) <= EPSILON) {
		*root = start;		// 垂直线，则 start就是根
		return true;
	}

	// 平行线x轴判断
	if (abs(fun(start) - fun(stop)) <= EPSILON) { // 是平行线
		if (fun(start) <= EPSILON) {				// 如果平行，且y=0，则都是根
			*root = start;							// 找最接近的数值解
			return true;
		} else if (fun(stop) <= EPSILON) {
			*root = stop;
			return true;
		} else {
			return false;							// 平行 不是x轴 则没有根
		}
	}

	// 如果不是垂直线 也不是平行x轴的线 则 折半查找
	bool isFind = false;					// 标记是否找到
	long count = 1;							// 最大查找次数

	if (fun(start) * fun(stop) < 0) {			// 如果符号不同，则有 根，使用C++ 异或 计算
		double mid = (start + stop) / 2.0;		// 条件初始化
		while (!isFind) {
			// 先查中间值mid是否符合要求
			double y = fun(mid);	// 计算y，  除以MAG求实际值

			drawLine(mid, 0, mid, y, YELLOW);
			if (abs(y) < EPSILON) {			// 判断是符合条件的 根
				cout << "找到了" << mid << "用了" << count << "步" << endl;
				*root = mid;
				isFind = true;
				return isFind;
			}

			// 控制台输出
			cout << "x = " << mid << " y = " << y << endl;

			// 图形界面输出
			ostringstream tmp_str;
			tmp_str << count << ":\tx:" << mid << " y:" << y;
			drawString(txt_x, txt_y, tmp_str.str().c_str(), YELLOW);
			txt_y -= 0.9;

			// 如果不是根，更新 起始点 和 结束点，再找中间点
			if (fun(mid) * fun(stop) < 0) {
				start = mid;
				mid = (start + stop) / 2.0;
			} else {
				stop = mid;
				mid = (start + stop) / 2.0;
			}
			delay_ms(500);
			//pausedByMouseLeft();
			count++;							// 计数+1，避免死循环
		}
	} else {
		// 该区域没有数值解
		cout << "该区域没有数值解，根。 " <<  endl;
		return false;
	}
	return false;
}

/**
 * @brief 弦截法/假位置法 查找函数fun的根
 *
 * @param fun 函数地址
 * @param start 开始点
 * @param stop 结束点
 * @param root 找到的根
 *
 * @return 是否找到
 */
bool  regulaFalsiSearch(double (*fun)(double), double start, double stop, double* root)
{
	// 函数有效性检查
	// 垂直线判断
	if (abs(start - stop) <= EPSILON) {
		*root = start;		// 垂直线，则 start就是根
		return true;
	}

	// 平行线x轴判断
	if (abs(fun(start) - fun(stop)) <= EPSILON) { // 是平行线
		if (fun(start) <= EPSILON) {				// 如果平行，且y=0，则都是根
			*root = start;							// 找最接近的数值解
			return true;
		} else if (fun(stop) <= EPSILON) {
			*root = stop;
			return true;
		} else {
			return false;							// 平行 不是x轴 则没有根
		}
	}

	double txt_y = 7;						// 提示文本的y轴
	double txt_x = 6.5;						// 提示文本的x轴

	// 弦截法 是否找到
	bool isFind = false;					// 标记是否找到
	long count = 1;							// 最大查找次数

	if (fun(start) * fun(stop) < 0) {				// 如果符号不同，则有 根，使用C++ 异或 计算
		while (!isFind) {
			// 用割线求交点 mid
			double mid = (start * fun(stop) - stop * fun(start)) / (fun(stop) - fun(start));
			// 先查中间值mid是否符合要求
			double y = fun(mid);	// 计算y，  除以MAG求实际值

			drawLine(start, fun(start), stop, fun(stop), RED);
			if (abs(y) < EPSILON) {			// 判断是符合条件的 根
				cout << "找到了" << mid << "用了" << count << "步" << endl;
				*root = mid;
				isFind = true;
				return isFind;
			}

			// 控制台输出
			cout << "x = " << mid << " y = " << y << endl;

			// 图形界面输出
			ostringstream tmp_str;
			tmp_str << count << ":\tx:" << mid << " y:" << y;
			drawString(txt_x, txt_y, tmp_str.str().c_str(), RED);
			txt_y -= 0.9;

			// 如果不是根，更新 起始点 和 结束点，再找中间点
			if (y * fun(start) < 0) {
				stop = mid;
			} else {
				start = mid;
			}
			delay_ms(500);
			//pausedByMouseLeft();
			count++;							// 计数+1，避免死循环
		}
	} else {
		// 该区域没有数值解
		cout << "该区域没有数值解，根。 " <<  endl;
		return false;
	}
	return false;
}

bool newtonRaphsonSearch(double (*fun)(double), double (*fun_derv)(double), double start, double stop, double* root)
{
	double txt_y = 6;						// 提示文本的y轴
	double txt_x = -8;						// 提示文本的x轴
	long count = 0;		// 统计尝试步数
	bool isFind = false;
	*root = (start + stop) / 2.0;
	while (!isFind && count < 500) {
		drawCircle((*root), 0, 0.1, RED, 0);	// 绘制正在尝试的数值x
		double y = fun(*root);	// 计算y
		count++;

		drawLine(*root, 0, *root, y, RED);
		// 图形界面输出
		ostringstream tmp_str;
		tmp_str << count << ":\tx:" << *root << " y:" << y;
		drawString(txt_x, txt_y, tmp_str.str().c_str(), WHITE);
		txt_y -= 0.9;

		// 输出枚举信息
		cout << count << ":\tx = " << *root  << " " << "y = " << y << endl;
		if (abs(y) < EPSILON) {			// 判断是不是根
			cout << "找到了" << *root << "用了" << count << "步" << endl;
			return true;
		} else {
			*root = *root - fun(*root) / fun_derv(*root);
		}

		pausedByMouseLeft();	// 鼠标左键 暂停 恢复
	}

	return false;		//找不到
}

