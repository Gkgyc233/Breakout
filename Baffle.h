#pragma once//游戏里的挡板
#include "BasicSettings.h"
class Baffle
{
public:
	Baffle() {};
	void baffleDraw();//绘制挡板
	void baffleMove();//移动挡板
	void adjust(int level) { //根据关卡调整挡板长度，最短60px
		length = (WindowWidth * 7 / 27) * pow(0.95, level);
		if (length < 60) length = 60;
		x = (780 - length) / 2;
		speed = 8 + 0.3 * level;
		if (speed > 15.0) speed = 15.0;
		return;
	}
	int getMid() { return x+length/2; };
	int getx() { return x; };
	int gety() { return y; };
	int getlength() { return length; };
	bool hitLeftWall() { return x <= 40; };//检测是否碰到左边墙壁
	bool hitRightWall() { return x + length >= 740; };//检测是否碰到右边墙壁
private:
	int length = WindowWidth*7/27;//挡板长度240px
	int x =(780-length)/2, y=520;//初始坐标
	float speed = 8;
};

