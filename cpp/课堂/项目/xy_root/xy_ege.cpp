#include <graphics.h>
#include <cmath>
#include "xy_ege.h"


int  WINDOW_WIDTH  = 640;	// 共享参数 窗口宽度
int  WINDOW_HEIGHT = 480;	// 共享参数 窗口高度

// 画图时候的放大倍数
double   MAG = (20.0);		// 放大倍数


/**
 * @brief 开启窗口，绘制x y数轴
 */
void open_xy_window(int width, int height, double mag, bool widthXY)
{
	// 使用用户参数修改默认参数
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	MAG = mag;				// 修改放大倍数

	// 绘制 控制台 窗格，需要指定 宽、高
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (widthXY) {	// 如果需要绘制X Y轴
		//绘制坐标系
		// 先绘制x轴，
		drawLine(-WINDOW_WIDTH / 2 / MAG, 0, WINDOW_WIDTH / 2 / MAG, 0, GREEN);
		if (DELAY) {
			delay_ms(DELAY_MS);
		}
		// 再绘制y轴
		drawLine(0, -WINDOW_HEIGHT / 2 / MAG, 0, WINDOW_HEIGHT / 2 / MAG, GREEN);
		if (DELAY) {
			delay_ms(DELAY_MS);
		}

		// 绘制横坐标 刻度 及 刻度数值
		for (int i = -10; i < 11; i++) {
			// 绘制 刻度， i是x轴刻度值，y从-3绘制到 10
			drawLine(i, -0.05, i, 0.6, WHITE);

			char tmp_str[10] = {0};		// 临时字符串变量
			itoa(i, tmp_str, 10);		// -15~15 刻度 转为字符串 tmp_str
			drawString(i, -0.1, tmp_str, WHITE);	// 绘制刻度值
			if (DELAY) {
				delay_ms(DELAY_MS / 5);
			}
		}
	}
}

/**
 * @brief 关闭窗口
 */
void close_xy_window()
{
	getch();

	closegraph();
}

/**
 * @brief 在屏幕上绘制函数fun的start~stop部分
 *
 * @param fun  要绘制的函数
 * @param start 起始点
 * @param stop 结束点
 * @param step 步长
 */
void drawF(double (*fun)(double), double start, double stop, double step)
{
	// 绘制曲线 绘制 start~stop 区间的曲线，默认x轴放大
	for (double i = start ; i <= stop ; i += step) {
		drawLine(i, fun(i), i + step, fun(i + step), WHITE);
	}
}

/**
 * @brief 如果鼠标左键按下则阻塞，再次按下继续
 */
void pausedByMouseLeft()
{
	bool isPaused = false;

	mouse_msg msg = {0};

	if (mousemsg()) {
		msg = getmouse(); //将鼠标信息存入鼠标结构体
		if (msg.is_down() && msg.is_left()) {
			isPaused = true;
		}
	}

	while (isPaused) {
		if (mousemsg()) {
			msg = getmouse(); //将鼠标信息存入鼠标结构体
			if (msg.is_down() && msg.is_left()) {
				isPaused = false;
			}
		}
		delay_ms(DELAY_MS / 100);	// 避免CPU占用过高
	}
}

/**
 * @brief 按照整数坐标系绘制一个点
 *
 * @param x
 * @param y
 * @param color 颜色
 */
void drawPoint(double x, double y, COLORS color, int delayMs)
{
	// 电脑屏幕的坐标系原点(0,0)是 左上角，x轴向右，y轴向下
	// 在常见的xy坐标系，原点在中间，y轴方向向上 如果原点不在中心 请自定义函数转换
	x *= MAG;
	y *= MAG;
	putpixel(WINDOW_WIDTH  / 2 + x, WINDOW_HEIGHT / 2 - y, color);
	if (DELAY) {
		delay_ms(fmin(delayMs, DELAY_MS / 200));
	}
}

/**
 * @brief 画一个点
 *
 * @param x
 * @param y
 * @param radius 点的半径
 */
void drawCircle(double x, double y, double radius, COLORS color, int delayMs)
{
	// 电脑屏幕的坐标系原点(0,0)是 左上角，x轴向右，y轴向下
	// 在常见的xy坐标系，原点在中间，y轴方向向上  如果原点不在中心 请自定义函数转换
	x *= MAG;
	y *= MAG;
	radius *= MAG;
	if (radius < 2) {
		radius = 2;
	}
	setcolor(color);
	circle(WINDOW_WIDTH  / 2 + x, WINDOW_HEIGHT / 2 - y, radius);
	if (DELAY) {
		delay_ms(fmin(delayMs, DELAY_MS / 200));
	}
}

/**
 * @brief 输出一个字符串
 *
 * @param x
 * @param y
 * @param str 字符串
 * @param color 颜色
 */
void drawString(double x, double y, const char* str, COLORS color, int delayMs)
{
	setcolor(color);
	x *= MAG;
	y *= MAG;
	outtextxy(WINDOW_WIDTH  / 2 + x, WINDOW_HEIGHT / 2 - y, str);
	if (DELAY) {
		if (DELAY) {
			delay_ms(fmin(delayMs, DELAY_MS / 200));
		}
	}
}

/**
 * @brief 绘制一个线段
 *
 * @param x1 起点x
 * @param y1 起点y
 * @param x2 终点x2
 * @param y2 终点y2
 * @param color
 */
void drawLine(double x1, double y1, double x2, double y2, COLORS color, int delayMs)
{
	// 设置画图颜色，GREEN是颜色常数，详细可以查graphics.h对这个宏的定义的值
	setcolor(color);

	x1 *= MAG;
	y1 *= MAG;
	x2 *= MAG;
	y2 *= MAG;


	line(WINDOW_WIDTH  / 2 + x1, WINDOW_HEIGHT / 2 - y1,
	     WINDOW_WIDTH  / 2 + x2, WINDOW_HEIGHT / 2 - y2
	    );
	if (DELAY) {
		delay_ms(fmin(delayMs, DELAY_MS / 200));
	}
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
