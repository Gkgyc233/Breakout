#pragma once//游戏里的挡板
#include "BasicSettings.h"
class Baffle
{
public:
	Baffle() {};
	void baffleDraw();//绘制挡板
	void baffleMove();//移动挡板
	int getMid() { return x+length/2; };
	int gety() { return y; };
	void setSpeed(int spd) { speed = spd; };//设置挡板速度
private:
	int length = WindowWidth*5/27;//挡板长度200px
	int x =(780-length)/2, y=480;//初始坐标
	int speed = 0;
};

