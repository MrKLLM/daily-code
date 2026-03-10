#include<iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

// 画图时候的放大倍数
const double MAG = 20.0;

// 宏的注释 不能放到行尾，为什么？
#define PI (3.14159265)

const double EPSILON = 1E-2;		// 误差


/**
 * @brief 按照整数坐标系绘制一个点
 *
 * @param x
 * @param y
 * @param color 颜色
 */
void drawPoint(int x, int y, COLORS color)
{
	putpixel(WINDOW_WIDTH  / 2 + x, WINDOW_HEIGHT / 2 - y, color);
}

/**
 * @brief 画一个点
 *
 * @param x
 * @param y
 * @param radius 点的半径
 */
void drawCircle(int x, int y, int radius)
{
	circle(WINDOW_WIDTH  / 2 + x, WINDOW_HEIGHT / 2 - y, radius);
}

/**
 * @brief 输出一个字符串
 *
 * @param x
 * @param y
 * @param str 字符串
 * @param color 颜色
 */
void drawString(int x, int y, char* str, COLORS color)
{
	setcolor(color);
	outtextxy(WINDOW_WIDTH  / 2 + x, WINDOW_HEIGHT / 2 - y, str);
}

/**
 * @brief 绘制一个线段
 *
 * @param x1 起点x
 * @param y1 起点y
 * @param x2 终点x
 * @param y2 终点y
 * @param color
 */
void drawLine(int x1, int y1, int x2, int y2, COLORS color)
{
	// 设置画图颜色，GREEN是颜色常数，详细可以查graphics.h对这个宏的定义的值
	setcolor(color);

	line(WINDOW_WIDTH  / 2 + x1, WINDOW_HEIGHT / 2 - y1,
	     WINDOW_WIDTH  / 2 + x2, WINDOW_HEIGHT / 2 - y2
	    );
}

/**
 * @brief 绘图函数
 * 测试表达式 y = 2*x^2+4*x - 50;
 * @param x
 *
 * @return 返回值y
 */
double fun1(double x)
{
	double x_mag = x / MAG;
	return 2 * x_mag * x_mag + 4 * x_mag - 50;
}

// 主程序入口
int main()
{
	// 绘制窗格
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	//绘制坐标系
	drawLine(-WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, 0, GREEN);
	drawLine(0, -WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT / 2, RED);

	// 绘制横坐标数据点
	for (int i = -15; i < 15; i++)
	{
		char tmp_str[10] = {0};
		drawLine(i * MAG, 0, i * MAG, 10, WHITE);
		itoa(i, tmp_str, 10);
		drawString(i * MAG, -5, tmp_str, WHITE);
	}

	// 绘制曲线
	for (int i = -10 * MAG; i < 10 * MAG; i++)
	{
		drawLine(i, fun1(i), i + 1, fun1(i + 1), RED);
	}

	// 遍历查找函数的根 0~10之间
	// 设置步长查找  步长不合适找不到，步长太细，很慢
	double step = 0.001;	// 步长
	for (int i = 0; i < round(10 / step); i++)
	{
		drawCircle(i * step * MAG, 0, 2);	// 正在尝试的数值x
		double y = fun1(i * step * MAG);	// 计算y，  除以MAG求实际值
		cout << "y = " << y << endl;					// 输出y
		if (abs(y) < EPSILON)				// 判断是不是根
		{
			cout << "找到了" << i*step << "用了" << i << "步" << endl;
			break;	// 找了 跳出循环
		}
		delay_ms(1000 * step);				// 模拟动画延时
	}

	// 折半查找
	bool isFind = false;					// 标记是否找到
	long count = 0;							// 最大查找次数
	double start = 0.0;
	double stop = 10.0;
	double mid = (start + stop) / 2.0;		// 条件初始化
	while (!isFind  &&  count < 100)
	{
		// 和for循环体非常像
		drawCircle(mid * MAG, 0, 2);	// 正在尝试的数值x
		double y = fun1(mid * MAG);	// 计算y，  除以MAG求实际值
		drawLine(mid * MAG, 0, mid * MAG, y, YELLOW);
		cout << "y = " << y << endl;					// 输出y
		if (abs(y) < EPSILON)				// 判断是不是根
		{
			cout << "找到了" << mid << "用了" << count << "步" << endl;
			break;	// 找了 跳出循环
		}

		// 更新 起始点 和 结束点，再找中间点
		if (y < 0)
		{
			start = mid;
			mid = (start + stop) / 2.0;
		}
		else
		{
			stop = mid;
			mid = (start + stop) / 2.0;
		}

		delay_ms(1000);				// 模拟动画延时
		count++;							// 计数+1，避免死循环
	}

	getch();

	closegraph();
	return 0;
}
