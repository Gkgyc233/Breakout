#pragma once//单局游戏
#include "Ball.h"
#include "Baffle.h"
#include "Brick.h"
#include "Map.h"


class aGame
{
public:
	aGame() :ifWin(false),ifEnd(false) {};
	aGame(gameSettings set) ;
	aGame(std::wstring lastgamename);//从残局创建
	~aGame() {
		delete ball;
		delete baffle;
		delete map;
		delete msg;
	}
	void gameDraw(std::wstring setname) ;//绘制一局游戏内的物品
	void gameRun() ;//一局游戏运行
	bool ifend() { return ifEnd; }
	bool ifwin() { return ifWin; }
	void displayInfo(std::wstring setname);//绘制游戏信息（血量、关卡等）
	void earnScore() { scores++; }//得分
	int  getScore() { return scores; }//获取分数
	void nextLevel();//进入下一关
	gameSettings settings;//三样默认或自定义设置

	Ball* ball;//小球
	Baffle* baffle;//挡板


	//3.2的残局功能
	Map* map;//砖块地图，可以用于加载残局
	//初始关卡gamelevel的信息覆盖3.1的配置

	int getblood() { return blood; }

	void serialize(std::ofstream& o) {
		o.write(reinterpret_cast<const char*>(&settings), sizeof(settings));
		baffle->serialize(o);
		ball->serialize(o);
		
		o.write(reinterpret_cast<const char*>(&scores), sizeof(scores));
		o.write(reinterpret_cast<const char*>(&blood), sizeof(blood));
		o.write(reinterpret_cast<const char*>(&level), sizeof(level));
		map->serialize(o);
	}
	bool deserialize(std::ifstream& in) {
		// 读取固定大小的数据
		if (!in.read(reinterpret_cast<char*>(&settings), sizeof(settings))) {
			return false;
		}

		// 确保对象已创建
		if (!baffle) baffle = new Baffle();
		if (!ball) ball = new Ball();
		if (!map) map = new Map();

		if (!baffle->deserialize(in)) return false;
		if (!ball->deserialize(in, baffle)) return false;

		if (!in.read(reinterpret_cast<char*>(&scores), sizeof(scores))) return false;
		if (!in.read(reinterpret_cast<char*>(&blood), sizeof(blood))) return false;
		if (!in.read(reinterpret_cast<char*>(&level), sizeof(level))) return false;
		if (!map->deserialize(in)) return false;

		return true;
	}


private:
	ExMessage* msg = new ExMessage;
	int scores;//分数
	int blood;//血量
	bool ifEnd = false;
	bool ifWin = false;//是否在通关状态
	int level;//关卡
	int xBlockNum = 9;//横向格子数（3.2.1）//TODO:根据残局更改横纵格子数
	int yBlockNum = 10;//纵向格子数（注：因为要放挡板和小球，只有上面一半的格子才会被砖占着）
	int displayX = WallWidth * 2 + MapWidth + 20;//信息显示区左上角x坐标
};

