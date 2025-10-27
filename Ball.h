#pragma once//球
#include"BasicSettings.h"
#include"Baffle.h"
class Ball
{
public:
	Ball(int gameLevel,int base_v) {}//输入关卡等级与基础速度
	void ballDraw();//球绘制
private:
	int x, y;//坐标
	int base_v;//基础球速
	int real_v;//实际计算得到球速
	int theta;//速度方向角度
	Baffle* baffle;//该局游戏的挡板对象
};

