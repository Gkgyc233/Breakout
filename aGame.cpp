#include "aGame.h"

void aGame::readLastGame(std::string lastgame) {};

void aGame::gameRun() {
	ball.ballMove();//处理球的移动
	baffle.baffleMove();//处理挡板的移动
	if (peekmessage(msg)) {//接收消息
		/*if (msg->message == WM_KEYDOWN) {//若消息为按键按下
			switch (msg->vkcode) {
			case VK_LEFT: { baffle.setSpeed(-3); break; }//左移挡板
			case VK_RIGHT: { baffle.setSpeed(3); break; }//右移挡板
			}
		}
		else if (msg->message == WM_KEYUP) {
			switch (msg->vkcode) {
			case VK_LEFT: { baffle.setSpeed(0); break; }
			case VK_RIGHT: { baffle.setSpeed(0); break; }
			}
		}*/
	}
}

void aGame::gameDraw() {
	baffle.baffleDraw();
	ball.ballDraw();
	map.mapDraw();

}

void aGame::gameInit() {
	
}


aGame::aGame(gameSettings set) {
	this->settings = set;
	this->baffle = Baffle();
	this->ball = Ball();
	this->map = Map();
	this->scores = 0;
	this->blood = 3;
	this->level = set.k;
	ball.setBall(level, set.basicV, 45);
	ball.linkBaffle(&baffle);
}