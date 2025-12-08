#include "BasicSettings.h"


const int ballR = 10;//球半径
const int baffleWidth = 50;//挡板厚度
const int baffleSpeed = 8;//挡板速度

const int WindowWidth = 1080;
const int WindowHeight = 640;

enum brickType { Durable, Normal, Indestructible, No };//#,@,* 三种砖与没有砖的占位

const std::wstring hz = L".config";
const std::wstring mr = L".\\config\\";

const std::wstring lastgame_prefix = L".\\endgames\\";
const std::wstring lastgame_postfix = L".end";

const float g = 0.3;//重力加速度

CollisionInfo* collide(int ball_x, int ball_y, int r, int rect_x, int rect_y, int rect_width, int rect_height) {//判断球与矩形的碰撞
	CollisionInfo* info = new CollisionInfo;
	if (ball_x <= rect_x - r || ball_x >= rect_x+rect_width + r || ball_y <= rect_y - r || ball_y >= rect_y+rect_height + r) return info;//初步检测
	int clostestX = std::clamp(ball_x, rect_x, rect_x + rect_width);//找到球心到矩形最近的点
	int clostestY = std::clamp(ball_y, rect_y, rect_y + rect_height);
	int dist_squared = (ball_x - clostestX) * (ball_x - clostestX) + (ball_y - clostestY) * (ball_y - clostestY);//计算距离的平方
	info->collided = dist_squared <= r * r;//判断是否碰撞
	if (info->collided) {
		info->collisionX = clostestX;//记录碰撞点x坐标
		info->collisionY = clostestY;//记录碰撞点y坐标
	}
	return info;
}
/*
我们规定：
gameLevel只影响ball的速度和baffle的宽度；
ball的实际速度由base_v和gameLevel综合而来
残局信息覆盖配置信息

*/