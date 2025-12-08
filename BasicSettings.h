#pragma once//通用基础信息
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include<vector>
#include <string>
#include<fstream>
#include <filesystem>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <tchar.h>
#include <random>

#define pi 3.1415926

class BasicSettings
{
};


extern const int ballR ;//球半径
extern const int baffleWidth;//挡板厚度
extern const int baffleSpeed;//挡板速度

extern const int WindowWidth ;
extern const int WindowHeight ;

extern const std::wstring hz;//配置文件后缀
extern const std::wstring mr;//配置文件目录

extern const std::wstring lastgame_prefix;//残局文件前缀
extern const std::wstring lastgame_postfix;//残局文件后缀

extern const float g;//重力加速度

class gameSettings {
public:
	int basicV = 1;//基础球速
	int seed = -1;//种子
	int k = 1;//初始关卡
};

struct CollisionInfo {//碰撞信息
	bool collided = false;//是否碰撞
	float collisionX = -1;//碰撞点x坐标
	float collisionY = -1;//碰撞点y坐标
};

CollisionInfo* collide(int ball_x, int ball_y, int r, int rect_x, int rect_y, int rect_width, int rect_height);//判断球与矩形的碰撞

int getRandType(int level);//根据关卡等级返回随机砖块类型








