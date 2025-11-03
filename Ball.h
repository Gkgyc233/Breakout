#pragma once//球
#include"BasicSettings.h"
#include"Baffle.h"
class Ball
{
public:
	void setBall(int gameLevel, int base_v,int x,int y,int t);//输入关卡等级,基础速度,位置，方向
	void linkBaffle(Baffle* b);//关联挡板
	void ballDraw();//球绘制
private:
	int x, y;//坐标
	int base_v;//基础球速
	int real_v;//实际计算得到球速
	int theta;//速度方向角度
	Baffle* baffle;//该局游戏的挡板对象
};

