#include "aGame.h"

void aGame::readLastGame(std::string lastgame) {};

void aGame::gameRun() {
	ball->ballMove();//处理球的移动
	baffle->baffleMove();//处理挡板的移动
	ball->ballRun(map,this);//处理球的逻辑（与挡板、墙壁、砖块的交互）
	if (ball->fall()) {//若球掉落
		blood--;//扣血
		if (blood <= 0) {
			ifEnd = true;
		}
		else {
			ball->setBall(level, this->settings.basicV);//重置球状态
			ball->linkBaffle(baffle);//重新将球放回挡板上
		}
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
	baffle->adjustLength(level);
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