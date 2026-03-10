#include<iostream>
#include <graphics.h>
#include <cmath>
#include <sstream>
using namespace std;
#include "xy_ege.h"

// 调整延时的毫秒数
#define TREE_DELAY_MS (50)

// 第一颗树的长度
const int STEP = 160;

// 树枝的最小长度 2比较好看
const int MIN_STEP = 10;

// 树枝每次缩小的长度
const double TREE_MAG = 0.6;


/**
 * @brief 递归绘制分形树
 *
 * @param p0  出发点
 * @param length 初始长度
 * @param angle  初始方向
 * @param lr_angle 分形度数 angle of left and right
 */
void fractal_sub_tree(ege_point p0, int length, double angle, double lr_angle)
{
	static int count = 0;
	// 递归绘制p0点开始的分形树，先画树干，画左树枝，再画右树枝

	// 树干的目标点在 当前点 angle 方向的 length * TREE_MAG 远处
	ege_point p1 = getNextPoint(p0, angle, length * TREE_MAG);
	if (length < MIN_STEP) {	// 如果步长太短就不画了
		return;
	}
	// 画树干
	drawLine(p0.x, p0.y, p1.x, p1.y, WHITE);
	count++;
	ostringstream oss;
	oss << "M" << count;
	if (length > 35) {		// 标识树干
		drawString((p0.x + p1.x) / 2, (p0.y + p1.y) / 2, oss.str().c_str(), WHITE);
	}
	delay_ms(TREE_DELAY_MS);		// 延时 演示
	pausedByMouseLeft();	// 鼠标左键 暂停 恢复

	// 左树枝 方向
	double left_agle = (angle + lr_angle);
	// 左树枝是 p1~p2连线，树枝长度减半
	ege_point p2 = getNextPoint(p1, left_agle, length * TREE_MAG);
	drawLine(p1.x, p1.y, p2.x, p2.y, GREEN);	// 画出左树枝
	count++;
	oss.str("");
	oss.clear();
	oss << "L" << count;
	if (length > 35) {
		drawString((p1.x + p2.x) / 2, (p1.y + p2.y) / 2, oss.str().c_str(), GREEN);
	}
	delay_ms(TREE_DELAY_MS);							// 延时 演示
	pausedByMouseLeft();	// 鼠标左键 暂停 恢复
	// 递归绘制 p2 开始的 分形树
	fractal_sub_tree(p2,  length * TREE_MAG,  left_agle, lr_angle);

	// 右树枝方向
	double right_agle = (angle - lr_angle);
	// 右树枝是 p1~p3连线，树枝长度减半
	ege_point p3 = getNextPoint(p1, right_agle, length * TREE_MAG);
	drawLine(p1.x, p1.y, p3.x, p3.y, RED);	// 画出右树枝
	count++;
	oss.str("");
	oss.clear();
	oss << "R" << count;
	if (length > 35) {
		drawString((p1.x + p3.x) / 2, (p1.y + p3.y) / 2, oss.str().c_str(), RED);
	}
	delay_ms(TREE_DELAY_MS);					// 延时 演示
	pausedByMouseLeft();	// 鼠标左键 暂停 恢复
	// 递归绘制 p3 开始的 分形树
	fractal_sub_tree(p3,  length * TREE_MAG, right_agle, lr_angle);
}


// 主程序入口
int main()
{
	open_xy_window(640, 480, 1.0, false);

	// 定义初始点，中间最下方
	ege_point p0 {0, -WINDOW_HEIGHT / 2};

	// 递归调用，第一棵树 90°方向,分形度数44°
	// 第一棵树 方向最好在 75°~105°，树会左右歪
	// 分形度数在30~55为好，分形度数越小，树越直立，越大树冠越大
	fractal_sub_tree(p0, STEP, 90, 45);

	close_xy_window();
	// 你还会做哪些分形树？
	return 0;
}
