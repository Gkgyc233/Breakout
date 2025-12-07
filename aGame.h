#pragma once//单局游戏
#include "Ball.h"
#include "Baffle.h"
#include "Brick.h"
#include "Map.h"
class aGame
{
public:
	aGame() {};
	void gameGraw() ;//绘制一局游戏内的物品
	void readLastGame(std::string lastgame);//读取并加载残局
	void gameRun() ;//一局游戏运行
	bool ifend() { return ifEnd; }
private:
	int scores;//分数
	int blood;//血量
	bool ifEnd = false;

	Ball ball;//小球
	Baffle baffle;//挡板

	//3.1的配置功能
	gameSettings settings;//三样默认或自定义设置
	std::wstring setName;//配置文件的名字

	//3.2的残局功能
	Map map;//砖块地图，可以用于加载残局
	//初始关卡gamelevel的信息覆盖3.1的配置
};

