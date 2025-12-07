#include "Ball.h"

void Ball::ballDraw() {
	setfillcolor(WHITE);
	fillcircle(x, y, ballR);
}

void Ball::linkBaffle(Baffle* b) {//让球出现在挡板中间正上方。换句话说，就是关联挡板的过程本身就确定了球的初始位置。
    baffle = b;
	this->x = b->getMid();
	this->y = b->gety()-ballR;
}

void Ball::setBall(int gameLevel, int base_v,int t) {
	this->base_v = base_v;
	this->real_v = 10*base_v + gameLevel; // 实际速度根据基础速度和关卡等级计算
	this->theta = t;
}

void Ball::ballMove() {
	float vx =   real_v * 1.0 * cos(theta);//计算速度分量
	float vy = - real_v * 1.0 * sin(theta);
	x += vx;//更新位置
	y += vy;
	vy += g;//施加重力加速度
	real_v = sqrt(vx * vx + vy * vy);//更新实际速度
	theta = atan2(-vy, vx);//更新方向角度
}