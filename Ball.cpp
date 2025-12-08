#include "Ball.h"
#include "Map.h"
void Ball::ballDraw() {
	setfillcolor(WHITE);
	fillcircle(x, y, ballR);
	displayInfo();//显示调试信息
}

void Ball::linkBaffle(Baffle* b) {//让球出现在挡板中间正上方。换句话说，就是关联挡板的过程本身就确定了球的初始位置。
    baffle = b;
	this->x = b->getMid();
	this->y = b->gety()-ballR;
}

void Ball::setBall(int gameLevel, int base_v,int t) {
	this->base_v = base_v;
	this->real_v = 5*base_v + gameLevel; // 实际速度根据基础速度和关卡等级计算
	this->theta = t;
	vx = real_v * 1.0 * cos(theta);//计算速度分量
	vy = -real_v * 1.0 * sin(theta);
}

void Ball::ballMove() {
	//vx =   real_v * 1.0 * cos(theta);//计算速度分量
	//vy = - real_v * 1.0 * sin(theta);
	x += vx;//更新位置
	y += vy;
	vy += g;//施加重力加速度
	real_v = sqrt(vx * vx + vy * vy);//更新实际速度
	theta = atan2(-vy, vx);//更新方向角度
}

void Ball::collideWithBaffle() {
	CollisionInfo* info = collide(x, y, ballR, baffle->getx(), baffle->gety(), baffle->getlength(), baffleWidth);//判断球与版是否碰撞
	if (info->collided && (info->collisionY - baffle->gety())<=20) {//若碰撞到挡板的水平面
		float dx = (info->collisionX - baffle->getMid())*1.0/(baffle->getlength());//计算碰撞点与挡板中点的归一化水平距离
		if (theta>=0) theta = 180 - theta;//垂直反弹
		else theta = -180 - theta;
		theta += dx * 7.0;//根据碰撞点调整反弹角度，最大偏转75度
		vx = real_v * 1.0 * cos(theta);//计算速度分量
		vy = -real_v * 1.0 * sin(theta);
		y = baffle->gety() - ballR;//调整位置，防止卡在挡板内
		//TODO:根据碰撞点调整反弹角度
	}
	delete info;
	return;
}

void Ball::ballRun(Map* map,aGame* game) {
	collideWithBaffle();//与挡板碰撞检测与反弹
	if (x - ballR <= 40) {//与左右墙壁碰撞检测与反弹
		bounce('y');
		x = 40 + ballR;
	}
	if (x + ballR >= 740) {
		bounce('y');
		x = 740 - ballR;
	}
	if (y - ballR <= 40) {//与天花板碰撞检测与反弹
		bounce('x');
		y = 40 + ballR;
	}
	map->check(this,game);//检测与砖块的碰撞并处理
	return;
}

void Ball::bounce(char mode) {
	if (mode == 'y') {//撞到垂直面上反弹
		vx *= -1;

	}
	else if(mode=='x'){//撞到水平面上反弹
		vy *= -1;
	}
	return;
}

void Ball::displayInfo() {
	settextcolor(WHITE);
	std::basic_ostringstream<TCHAR> oss;//建立字符串流
	oss << _T("ball.theta: ") << theta;
	outtextxy(800, 220, (oss.str()).c_str());//输出角度
	oss.str(_T(""));//清空字符串流
	oss << _T("ball.vx: ") << vx;
	outtextxy(800, 280, (oss.str()).c_str());
	oss.str(_T(""));
	oss << _T("ball.vy: ") << vy;
	outtextxy(800, 340, (oss.str()).c_str());
}