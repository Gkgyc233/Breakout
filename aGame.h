#pragma once
#include "Ball.h"
#include "Baffle.h"
#include "Brick.h"
class aGame
{
public:
	aGame(std::string settings, int gamelevel,
		std::vector<Brick>& bricks,
		int width = 9, int hight = 18, int scores = 0, int blood = 3,
		Ball, Baffle;
		) :
		scores(scores), blood(3),width(width),
		hight(hight),bricks(bricks),
		settings(settings),gamelevel(gamelevel) { };//创建一局游戏：配置文件名，关卡等级；残局信息(砖块，地图，分数，血量，球状态，挡板状态)
	aGame(std::string settings, int gamelevel) :
		scores(0), blood(3), width(9),
		hight(18),settings(settings), gamelevel(gamelevel){};//创建一局游戏：配置文件名，关卡等级
	void gameGraw() {};//绘制一局游戏内的物品
private:
	int scores;//分数
	int blood;//血量
	int gamelevel;//游戏关卡等级

	

	//3.1的配置功能
	std::string settings;//三样默认或自定义设置 的文件名

	//3.2的残局功能
	int width, hight;//一局游戏的地图宽高
	std::vector<Brick> bricks;//砖块与占位符的平铺状态
	//初始关卡的信息随3.1的配置一起导入
};

