#include"GameManager.h"
GameManager::GameManager() {
	std::ifstream o(mr + settings + hz, std::ios::in | std::ios::binary);
	if (o.is_open()) { o.read((char*)&s, sizeof(s)); o.close(); }
	else { std::ofstream o(mr + settings + hz, std::ios::out | std::ios::binary);
	o.write((char*)&s, sizeof(s)); o.close();
	}
}

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
	
};

void GameManager::MenuCheck() {
	if (check) {//是否初始化
		while (!buttons.empty()) {
			delete buttons.back();
			buttons.pop_back();
		}
		check = false;
		//初始化按钮
		Button* begin = new Button(WindowWidth / 2, WindowHeight / 4, WindowWidth / 3, WindowHeight / 12);
		begin->setString(_T("开始游戏"));
		begin->setid(3);
		buttons.push_back(begin);

		Button* setting = new Button(WindowWidth / 5, WindowHeight / 2, WindowWidth / 5, WindowHeight / 12);
		setting->setString(L"当前配置：" + settings);
		setting->setid(1);
		buttons.push_back(setting);

		Button* lastgame = new Button(WindowWidth / 5*4, WindowHeight / 2, WindowWidth / 5, WindowHeight / 12);
		lastgame->setString(_T("无残局"));
		lastgame->setid(2);
		buttons.push_back(lastgame);

		Button* exit = new Button(WindowWidth / 2, WindowHeight / 4*3, WindowWidth / 3, WindowHeight / 12);
		exit->setString(_T("退出游戏"));
		exit->setid(-1);
		buttons.push_back(exit);
	}
	if (peekmessage(m,EX_MOUSE)) {
		if (m->message == WM_LBUTTONDOWN) {
			int x = m->x; int y = m->y;
			for (Button* i : buttons) {//检查按钮触发
				if (i->ifIn(x, y)) {
					switch (i->uid()) {
					case 3: { check = true; state = 3; Start(); break; }
					case 1: { check = true; state = 1; Settings(); break; }
					case -1: { ifrunning = false;return; break; }
					case 2: { check = true; state = 2; Lastgame(); break; }
					}
					break;
				}
			}
		}
	}
	
}
void GameManager::Menudraw() {
	for (auto i : buttons) {
		i->draw();
	}
}
void GameManager::SetDraw() {
	for (auto i : buttons) {
		i->draw();
	}
}
void GameManager::Settings() {//配置界面
	if (check) {//是否初始化
		while (!buttons.empty()) {
			delete buttons.back();
			buttons.pop_back();
		}
		check = false;
		//初始化按钮
		Button* menu = new Button(WindowWidth / 10, WindowHeight / 10, WindowWidth / 30, WindowHeight / 30);
		menu->setString(_T("返回"));
		menu->setid(0);
		buttons.push_back(menu);

		Button* create = new Button(WindowWidth / 10 * 9, WindowHeight / 10 * 9, WindowWidth / 25, WindowHeight / 30);
		create->setString(_T("创建新配置"));
		create->setid(10);
		buttons.push_back(create);


		for (const auto& entry : std::filesystem::directory_iterator(mr)) {
			if (entry.is_regular_file()) {
				std::cout << entry.path().filename() << std::endl;
			}
		}
		
	}
	if (peekmessage(m, EX_MOUSE)) {
		if (m->message == WM_LBUTTONDOWN) {
			int x = m->x; int y = m->y;
			for (Button* i : buttons) {//检查按钮触发
				if (i->ifIn(x, y)) {//在按钮范围内
					switch (i->uid()) {
					case 0: { check = true; state = 0; break; }
					case 10: { create(); break; }
					}

				}
				break;
			}
		}
	}
}


void GameManager::create(){}