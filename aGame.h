#pragma once//单局游戏
#include "Ball.h"
#include "Baffle.h"
#include "Brick.h"
class aGame
{
public:
	aGame(std::string settings, int gamelevel,
		std::vector<Brick>& bricks,
		std::string lastGame
		) :
		settings(settings),gamelevel(gamelevel) {
		readLastGame(lastGame);
	};//创建一局游戏：配置文件名，关卡等级；残局文件名
	aGame(std::string settings, int gamelevel) :
		scores(0), blood(3), width(9),
		hight(18),settings(settings), gamelevel(gamelevel){};//创建一局游戏：配置文件名，关卡等级
	void gameGraw() {};//绘制一局游戏内的物品
	void readLastGame(std::string lastgame){}//读取并加载残局//
	void newGame() {}//根据配置文件创建新一局游戏
private:
	int scores;//分数
	int blood;//血量
	int gamelevel;//游戏关卡等级

	Ball ball;//小球
	Baffle baffle;//挡板

	//3.1的配置功能
	std::string settings;//三样默认或自定义设置 的文件名

	//3.2的残局功能
	int width, hight;//一局游戏的地图宽高
	std::vector<Brick> bricks;//砖块与占位符的平铺状态
	//初始关卡的信息随3.1的配置一起导入
};

