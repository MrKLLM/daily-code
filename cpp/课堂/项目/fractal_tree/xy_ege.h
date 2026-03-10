#include <graphics.h>

// 宏的注释 不能放到行尾，为什么？
#ifndef PI
	#define PI (3.14159265)
#endif

// 向调用者公开参数 MAG
extern double   MAG ;
extern int  WINDOW_WIDTH ;	// 共享参数 窗口宽度
extern int  WINDOW_HEIGHT;

// 调整动态绘制延时的毫秒数
#ifndef DELAY_MS
	#define DELAY_MS (500)
#endif

// 控制是否动态绘制坐标轴
#ifndef DELAY
	#define DELAY 	(1)
#endif

/**
 * @brief 开启窗口，用户可以修改默认参数，绘制x y数轴
 */
void open_xy_window(int width = 640, int height = 480, double mag = 20, bool widthXY = true);

/**
 * @brief 关闭窗口
 */
void close_xy_window();

/**
 * @brief 在屏幕上绘制函数fun的start~stop部分
 *
 * @param fun  要绘制的函数
 * @param start 起始点
 * @param stop 结束点
 * @param step 步长
 */
void drawF(double (*fun)(double), double start, double stop, double step);

/**
 * @brief 如果鼠标左键按下则阻塞，再次按下继续
 */
void pausedByMouseLeft() ;

/**
 * @brief 按照整数坐标系绘制一个点
 *
 * @param x
 * @param y
 * @param color 颜色
 */
void drawPoint(double x, double y, COLORS color, int delayMs = 10) ;

/**
 * @brief 画一个点
 *
 * @param x
 * @param y
 * @param radius 点的半径
 */
void drawCircle(double x, double y, double radius, COLORS color, int delayMs = 10);

/**
 * @brief 输出一个字符串
 *
 * @param x
 * @param y
 * @param str 字符串
 * @param color 颜色
 */
void drawString(double x, double y, const char* str, COLORS color, int delayMs = 10);

/**
 * @brief 绘制一个线段
 *
 * @param x1 起点x
 * @param y1 起点y
 * @param x2 终点x
 * @param y2 终点y
 * @param color
 */
void drawLine(double x1, double y1, double x2, double y2, COLORS color, int delayMs = 10);


/**
 * @brief p0点 angle方向 length距离的点的坐标
 *
 * @param p0 初始点
 * @param angle  方向
 * @param length  长度
 *
 * @return 新的点
 */
ege_point getNextPoint(ege_point p0, double angle, int length);
