#pragma once//单局游戏
#include "Ball.h"
#include "Baffle.h"
#include "Brick.h"
#include "Map.h"
class aGame
{
public:
	aGame(gameSettings set) ;
	void gameDraw() ;//绘制一局游戏内的物品
	void readLastGame(std::string lastgame);//读取并加载残局
	void gameRun() ;//一局游戏运行
	void gameInit();//通过配置创建一局游戏
	bool ifend() { return ifEnd; }
	bool ifwin() { return ifWin; }
	void displayInfo();//绘制游戏信息（血量、关卡等）
	void earnScore() { scores++; }//得分
	int  getScore() { return scores; }//获取分数
	void nextLevel();//进入下一关
	gameSettings settings;//三样默认或自定义设置
private:
	ExMessage* msg = new ExMessage;
	int scores;//分数
	int blood;//血量
	bool ifEnd = false;
	bool ifWin = false;//是否在通关状态
	int level;//关卡
	Ball* ball;//小球
	Baffle* baffle;//挡板
	//3.1的配置功能
	//std::wstring setName;//配置文件的名字
	//NOTE:从文件读取设置的功能已经在BasicSettings和GameManager中实现，不需要在这里重复实现


	//3.2的残局功能
	Map* map;//砖块地图，可以用于加载残局
	//初始关卡gamelevel的信息覆盖3.1的配置
};

