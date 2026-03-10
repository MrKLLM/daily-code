#include<iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

// 调整延时的毫秒数
#define DELAY_MS (20)

// 第一颗树的长度
const int STEP = 160;

// 树枝的最小长度
const int MIN_STEP = 2;

// 树枝每次缩小的长度
const double MAG = 0.6;

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
 * @brief p0点 angle方向 length距离的点的坐标
 *
 * @param p0 初始点
 * @param angle  方向
 * @param length  长度
 *
 * @return 新的点
 */
ege_point getNextPoint(ege_point p0, double angle, int length)
{
	ege_point p1;
	p1.x = p0.x + length * cos(angle * PI / 180);	// x0+l*cos(angle)
	p1.y = p0.y + length * sin(angle * PI / 180);	// y0+l*sin(angle)
	return p1;
}

/**
 * @brief 递归绘制分形树
 *
 * @param p0  出发点
 * @param length 初始长度
 * @param angle  初始方向
 * @param lr_angle 分形度数
 */
void fractal_sub_tree(ege_point p0, int length, double angle, double lr_angle)
{
	// 递归绘制p0点开始的分形树，先画树干，画左树枝，再画右树枝

	// 树干的目标点在 当前点 angle 方向的 length * MAG 远处
	ege_point p1 = getNextPoint(p0, angle, length * MAG);
	if (length < MIN_STEP)	// 如果步长太短就不画了
	{
		return;
	}
	// 画树干
	drawLine(p0.x, p0.y, p1.x, p1.y, WHITE);
	delay_ms(DELAY_MS);		// 延时 演示

	// 左树枝 方向
	double left_agle = (angle + lr_angle);
	// 左树枝是 p1~p2连线，树枝长度减半
	ege_point p2 = getNextPoint(p1, left_agle, length * MAG);
	drawLine(p1.x, p1.y, p2.x, p2.y, WHITE);	// 画出左树枝
	delay_ms(DELAY_MS);							// 延时 演示
	// 递归绘制 p2 开始的 分形树
	fractal_sub_tree(p2,  length * MAG,  left_agle, lr_angle);

	// 右树枝方向
	double right_agle = (angle - lr_angle );
	// 右树枝是 p1~p3连线，树枝长度减半
	ege_point p3 = getNextPoint(p1, right_agle, length * MAG);
	drawLine(p1.x, p1.y, p3.x, p3.y, WHITE);	// 画出右树枝
	delay_ms(DELAY_MS);							// 延时 演示
	// 递归绘制 p3 开始的 分形树
	fractal_sub_tree( p3,  length * MAG, right_agle, lr_angle);
}



// 主程序入口
int main()
{
	// 绘制窗格
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	// 定义初始点，中间最下方
	ege_point p0 {0, -WINDOW_HEIGHT / 2};

	// 递归调用，第一棵树 90°方向,分形度数44°
	// 第一棵树 方向最好在 75°~105°，树会左右歪
	// 分形度数在30~55为好，分形度数越小，树越直立，越大树冠越大
	fractal_sub_tree(p0, STEP, 90, 45);

	getch();

	closegraph();
	// 你还会做哪些分形树？
	return 0;
}
