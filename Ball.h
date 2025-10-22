#pragma once
#include"BasicSettings.h"
#include"Baffle.h"
class Ball
{
public:
	void ballDraw();//球绘制
private:
	int x, y;//坐标
	Baffle* baffle;//该局游戏的挡板对象
};

