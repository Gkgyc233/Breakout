#include"GameManager.h"


void GameManager::draw() {
	cleardevice();
	switch (state) {
	case 0:Menudraw(); break;
	case 1:SetDraw(); break;
	case 2:LastgameDraw(); break;
	case 3:thisgame->gameGraw(); break;
	case 4:StopDraw(); break;
	}
};
void GameManager::run() {
	switch (state) {
	case 0:MenuCheck(); break;
	case 1:Settings(); break;
	case 2:Lastgame(); break;
	case 3:thisgame->gameRun(); break;
	case 4:Stop(); break;
	}
	flushmessage();
};

void GameManager::MenuCheck() {
	if (check) {//是否初始化
		while (!buttons.empty()) {
			delete buttons.back();
			buttons.pop_back();
		}
		//处理按钮
		Button* begin = new Button(WindowWidth / 2, WindowHeight / 4, WindowWidth / 3, WindowHeight / 12);
		begin->setString(_T("开始游戏"));
		buttons.push_back(begin);

		Button* setting = new Button(WindowWidth / 5, WindowHeight / 2, WindowWidth / 5, WindowHeight / 12);
		setting->setString(L"当前配置：" + settings);
		buttons.push_back(setting);

		Button* lastgame = new Button(WindowWidth / 5*4, WindowHeight / 2, WindowWidth / 5, WindowHeight / 12);
		lastgame->setString(_T("无残局"));
		buttons.push_back(lastgame);

		Button* exit = new Button(WindowWidth / 2, WindowHeight / 4*3, WindowWidth / 3, WindowHeight / 12);
		exit->setString(_T("退出游戏"));
		buttons.push_back(exit);
	}
	for (auto i : buttons) {//检查按钮触发
	}
	
}
void GameManager::Menudraw() {
	for (auto i : buttons) {
		i->draw();
	}
}