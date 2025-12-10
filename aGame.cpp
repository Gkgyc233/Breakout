#include "aGame.h"

void aGame::readLastGame(std::string lastgame) {};

void aGame::gameRun() {
	ball->ballMove();//处理球的移动
	baffle->baffleMove();//处理挡板的移动
	ball->ballRun(map,this);//处理球的逻辑（与挡板、墙壁、砖块的交互）
	if (ball->fall()||((GetAsyncKeyState('R') & 0x8000)&&(!ball->isFrozen()))) {//若球掉落或者球卡住之后玩家按下R键脱困
		blood--;//扣血
		if (blood <= 0) {
			ifEnd = true;
		}
		else {
			ball->setBall(level, this->settings.basicV);//重置球状态
			ball->linkBaffle(baffle);//重新将球放回挡板上
		}
	}
	if (map->is_empty()) {//若砖块被清空，赢。
		ifWin = true;
	}
	if (GetAsyncKeyState('C') & 0x8000) {//调试用，清图
		map->clear();
	}
}

void aGame::gameDraw() {
	baffle->baffleDraw();
	ball->ballDraw();
	map->mapDraw();
	this->displayInfo();
}

void aGame::gameInit() {
	
}


aGame::aGame(gameSettings set) {
	this->settings = set;
	this->baffle = new Baffle();
	this->ball = new Ball();
	this->map = new Map();
	this->scores = 0;
	this->blood = 3;
	this->level = set.k;
	ball->setBall(level, set.basicV);
	ball->linkBaffle(baffle);
	baffle->adjust(level);
}

void aGame::displayInfo() {//显示血量、分数,etc.
	settextcolor(WHITE);
	std::basic_ostringstream<TCHAR> oss;//建立字符串流
	oss << _T("score: ") << scores;
	outtextxy(800, 40, (oss.str()).c_str());//输出分数
	oss.str(_T(""));//清空字符串流
	oss << _T("blood: ") << blood;
	outtextxy(800, 100, (oss.str()).c_str());
	oss.str(_T(""));
	oss << _T("level: ") << level;
	outtextxy(800, 160, (oss.str()).c_str());
	oss.str(_T(""));
	return;
}

void aGame::nextLevel() {//进入下一关
	level++;
	blood = 3;//重置游戏状态
	ifWin = false;
	delete baffle;
	baffle = new Baffle();//重置挡板
	ball->setBall(level, this->settings.basicV);//重置球状态
	ball->linkBaffle(baffle);//重新将球放回挡板上
	baffle->adjust(level);//调整挡板长度和速度
	delete map;
	map = new Map(9, 5, level);//创建新地图
}