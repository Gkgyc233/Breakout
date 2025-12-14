#include"GameManager.h"
GameManager::GameManager() {
	std::ifstream o(mr + settings + hz, std::ios::in | std::ios::binary);
	if (o.is_open()) {
		o.read((char*)&set, sizeof(set));
		o.close();
	}
	else {
		std::ofstream o(mr + settings + hz, std::ios::out | std::ios::binary);
		o.write((char*)&set, sizeof(set)); 
		o.close();
	}
}

void GameManager::draw() {
	cleardevice();
	switch (state) {
	case 0:Menudraw(); break;
	case 1:SetDraw(); break;
	case 2:LastgameDraw(); break;
	case 3:thisgame->gameDraw(settings); break;
	case 4:StopDraw(); break;
	case 5:WinDraw(); break;
	case 6:LoseDraw(); break;
	}
};
void GameManager::run() {
	switch (state) {
	case 0:MenuCheck(); break;
	case 1:Settings(); break;
	case 2:Lastgame(); break;
	case 3:Start(); break;
	case 4:Stop(); break;
	case 5:Win(); break;
	case 6:Lose(); break;
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
		if(ifLastgame) { lastgame->setString(lastgamename); }
		else { lastgame->setString(_T("无残局")); }
		
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
void GameManager::LastgameDraw() {
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

		allSettingsName.clear();
		int i = 0;
		for (const auto& entry : std::filesystem::directory_iterator(mr)) {//可选择的配置文件的按钮
			if (entry.is_regular_file()) {
				Button* set = new Button(WindowWidth / 2, WindowHeight / 10 *(2+ i), WindowWidth / 5, WindowHeight / 25);
				set->setString(entry.path().filename());
				set->setid(-1-i);
				buttons.push_back(set);

				allSettingsName.push_back(entry.path().filename());
				//pass//低矮处消隐//似乎也没必要
				i++;
			}
		}
		
	}
	if (peekmessage(m, EX_MOUSE)) {
		if (m->message == WM_LBUTTONDOWN) {
			int x = m->x; int y = m->y;
			for (Button* i : buttons) {//检查按钮触发
				if (i->ifIn(x, y)) {//在按钮范围内
					if (i->uid() < 0) {
						std::wstring nextconfig = i->Word();
						settings = nextconfig.substr(0,nextconfig.length()-7);//修改当前配置文件

						std::ifstream ss(mr + nextconfig, std::ios::in | std::ios::binary);
						ss.read((char*)&set, sizeof(set));
						ss.close();

						check = true; state = 0;//返回主菜单
					}//检查配置文件按钮
					else {
						switch (i->uid()) {
						case 0: { check = true; state = 0; break; }
						case 10: { create(); break; }
						}
					}
				break;
				}
				
			}
		}
		else if (WM_MOUSEWHEEL) {
			for (auto& i : buttons) {
				if (i->uid() < 0) { i->moveY(m->wheel/10); }
			}
		}//滚动滑轮
	}
}


void GameManager::create(){
	wchar_t s[20]; // 稍微增大缓冲区

	// 配置名称
	int result = InputBox(s, 20,
		L"创建新配置\n"
		L"要求：\n"
		L"只能包含字母、数字或下划线\n");

	if (result == 0) {
		return; // 用户点击取消
	}
	if (wcslen(s) == 0) {
		MessageBox(GetHWnd(), L"配置名称不能为空", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}
	for (size_t i = 0; i < wcslen(s); i++) {
		wchar_t c = s[i];
		if (!((c >= L'a' && c <= L'z') ||
			(c >= L'A' && c <= L'Z') ||
			(c >= L'0' && c <= L'9') ||
			c == L'_')) {
			MessageBox(GetHWnd(),
				L"配置名称只能包含字母、数字或下划线\n"
				L"请不要使用空格、中文或其他特殊字符",
				L"输入错误", MB_OK | MB_ICONERROR);
			return;
		}
	}
	std::wstring configName = s;
	std::wstring fullPath = mr + configName + hz;

	if (std::filesystem::exists(fullPath)) {
		int choice = MessageBox(GetHWnd(),
			L"该配置名称已存在，是否覆盖？",
			L"确认覆盖", MB_YESNO | MB_ICONWARNING);

		if (choice != IDYES) {
			return;
		}
	}


	wchar_t n[256],sd[256],level[256];
	int basicV = InputBox(n, 256, L"请输入一个1到10的正整数，表示球运动的基础速度");
	if (basicV == 0) return; // 用户取消
	if (wcslen(n) == 0) {
		MessageBox(GetHWnd(), L"基础速度不能为空", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}
	basicV = 0;
	try {
		basicV = std::stoi(n);
	}
	catch (const std::exception&) {
		MessageBox(GetHWnd(), L"基础速度必须是1-10之间的整数", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}
	if (basicV < 1 || basicV > 10) {
		MessageBox(GetHWnd(), L"基础速度必须在1-10之间", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}
	int seed = InputBox(sd, 256, L"请输入一个整数，作为随机数种子");
	if (seed == 0) return; // 用户取消

	if (wcslen(sd) == 0) {
		MessageBox(GetHWnd(), L"随机数种子不能为空", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}
	seed = 0;
	try {
		seed = std::stoi(sd);
	}
	catch (const std::exception&) {
		MessageBox(GetHWnd(), L"随机数种子必须是有效的整数", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}

	int gamelevel = InputBox(level, 256, L"请输入一个正整数，作为初始关卡");
	if (gamelevel == 0) return; // 用户取消
	if (wcslen(level) == 0) {
		MessageBox(GetHWnd(), L"初始关卡不能为空", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}
	gamelevel = 0;
	try {
		gamelevel = std::stoi(level);
	}
	catch (const std::exception&) {
		MessageBox(GetHWnd(), L"初始关卡必须是正整数", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}
	if (gamelevel < 1) {
		MessageBox(GetHWnd(), L"初始关卡必须是正整数（>=1）", L"输入错误", MB_OK | MB_ICONERROR);
		return;
	}


	std::wstring confirmMsg = L"请确认以下配置信息：\n\n";
	confirmMsg += L"配置名称: " + configName + L"\n";
	confirmMsg += L"基础速度: " + std::to_wstring(basicV) + L"\n";
	confirmMsg += L"随机数种子: " + std::to_wstring(seed) + L"\n";
	confirmMsg += L"初始关卡: " + std::to_wstring(gamelevel) + L"\n\n";
	confirmMsg += L"确认创建此配置吗？";

	int confirm = MessageBox(GetHWnd(), confirmMsg.c_str(), L"确认配置", MB_YESNO | MB_ICONQUESTION);

	if (confirm != IDYES) {
		return;
	}

	gameSettings a;
	a.basicV = basicV;
	a.seed = seed;
	a.k = gamelevel;

	std::ofstream o(fullPath, std::ios::out | std::ios::binary);
	o.write((char*)&a, sizeof(a));
	o.close();

	settings = configName;
	set = a;
	check = true;
}

void GameManager::Start() {
	if (check) {
		check = false;
		if (nextlevel) {
			nextlevel = false;
			thisgame->nextLevel();
		}
		if (newgame) {
			newgame = false;
			if (ifLastgame) { thisgame = startAGame(lastgamename); }
			else { thisgame = startAGame(); }
			

		}//创建一局游戏(根据配置文件或残局)
	}
	//进行游戏
	if (thisgame->ifend()) {//游戏结束，移动到失败界面
		state = 6;
		check = true;
		newgame = true;
	}
	else if (thisgame->ifwin()) {//若胜利
		state = 5;
		check = true;
		nextlevel = true;
	}
	else {
		thisgame->gameRun();
		if (GetAsyncKeyState('P') & 0x8000) {
			state = 4;
			check = true;
		}
	}
}

aGame* GameManager::startAGame() {
	aGame* game = new aGame(set);

	return game;
}
aGame* GameManager::startAGame(std::wstring) {
	aGame* game = new aGame(lastgamename);

	return game;
}

void GameManager::Stop() {
	if (check) {
		while (!buttons.empty()) {
			delete buttons.back();
			buttons.pop_back();
		}
		check = false;
		Button* resume = new Button(WindowWidth / 5, WindowHeight / 2, WindowWidth / 5, WindowHeight / 12);//绘制按钮
		resume->setString(L"恢复");
		resume->setid(0);
		buttons.push_back(resume);

		Button* lastgame = new Button(WindowWidth / 5 * 4, WindowHeight / 2, WindowWidth / 5, WindowHeight / 12);
		lastgame->setString(L"保存残局");
		lastgame->setid(1);
		buttons.push_back(lastgame);
	}
	if (peekmessage(m, EX_MOUSE)) {
		if (m->message == WM_LBUTTONDOWN) {
			int x = m->x; int y = m->y;
			for (Button* i : buttons) {//检查按钮触发
				if (i->ifIn(x, y)) {
					switch (i->uid()) {
					case 0: { check = true; state = 3; Start(); break; }
					case 1: {  if (createLastgame(true)) { check = true; state = 3; Start(); }; break; }//保存残局信息后继续游戏
					}
					break;
				}
			}
		}
	}
}

void GameManager::StopDraw() {
	settextcolor(WHITE);//绘制“暂停”
	settextstyle(WindowHeight / 12, 0, _T("Consolas"));
	outtextxy((WindowWidth-textwidth(L"已暂停")) / 2, WindowHeight / 6, L"已暂停");
	for (auto i : buttons) {
		i->draw();
	}
}

void GameManager::Win() {
	if (check) {
		while (!buttons.empty()) {
			delete buttons.back();
			buttons.pop_back();
		}
		check = false;
		Button* next = new Button(WindowWidth / 2, WindowHeight / 2, WindowWidth / 3, WindowHeight / 12);
		next->setString(L"下一关");
		next->setid(0);
		buttons.push_back(next);
	}
	if (peekmessage(m, EX_MOUSE)) {
		if (m->message == WM_LBUTTONDOWN) {
			int x = m->x; int y = m->y;
			for (Button* i : buttons) {//检查按钮触发
				if (i->ifIn(x, y)) {
					switch (i->uid()) {
					case 0: { check = true; state = 3; break; }
					}
					break;
				}
			}
		}
	}
}

void GameManager::WinDraw() {
	settextcolor(WHITE);//绘制“胜利”
	settextstyle(WindowHeight / 12, 0, _T("Consolas"));
	outtextxy((WindowWidth - textwidth(L"你过关")) / 2, WindowHeight / 6, L"你过关！");
	std::basic_ostringstream<TCHAR> oss;//建立字符串流
	oss << _T("当前分数: ") << thisgame->getScore();//输出分数
	std::basic_string<TCHAR> str = oss.str();
	LPCTSTR word = (str).c_str();
	outtextxy((WindowWidth - textwidth(word)) / 2, WindowHeight / 3, word);
	for (auto i : buttons) {
		i->draw();
	}
}

void GameManager::Lose() {
	if (check) {
		while (!buttons.empty()) {
			delete buttons.back();
			buttons.pop_back();
		}
		check = false;
		Button* menu = new Button(WindowWidth / 2, WindowHeight / 2, WindowWidth / 3, WindowHeight / 12);
		menu->setString(L"返回主菜单");
		menu->setid(0);
		buttons.push_back(menu);
	}
	if (peekmessage(m, EX_MOUSE)) {
		if (m->message == WM_LBUTTONDOWN) {
			int x = m->x; int y = m->y;
			for (Button* i : buttons) {//检查按钮触发
				if (i->ifIn(x, y)) {
					switch (i->uid()) {
					case 0: { check = true; state = 0; break; }
					}
					break;
				}
			}
		}
	}
}

void GameManager::LoseDraw() {
	settextcolor(WHITE);//绘制“GameOver”
	settextstyle(WindowHeight / 12, 0, _T("Consolas"));
	outtextxy((WindowWidth - textwidth(L"该罚")) / 2, WindowHeight / 6, L"该罚！");
	std::basic_ostringstream<TCHAR> oss;//建立字符串流
	oss << _T("分数: ") << thisgame->getScore();//输出分数
	std::basic_string<TCHAR> str = oss.str();
	LPCTSTR word = (str).c_str();
	outtextxy((WindowWidth - textwidth(word)) / 2, WindowHeight / 3, word);
	for (auto i : buttons) {
		i->draw();
	}
}



void GameManager::Lastgame() {
	if (check) {
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
		create->setString(_T("创建新残局"));
		create->setid(10);
		buttons.push_back(create);

		Button* nocreate = new Button(WindowWidth / 10 * 9, WindowHeight / 10 * 7, WindowWidth / 25, WindowHeight / 30);
		nocreate->setString(_T("不加载残局"));
		nocreate->setid(1);
		buttons.push_back(nocreate);


		allSettingsName.clear();
		int i = 0;
		for (const auto& entry : std::filesystem::directory_iterator(lastgame_prefix)) {//与“可选择的配置文件的按钮”是相同配置方法
			if (entry.is_regular_file()) {
				Button* set = new Button(WindowWidth / 2, WindowHeight / 10 * (2 + i), WindowWidth / 5, WindowHeight / 25);
				set->setString(entry.path().filename());
				set->setid(-1 - i);
				buttons.push_back(set);

				allSettingsName.push_back(entry.path().filename());
				i++;
			}
		}
	}
	//残局查看与选择
	
	if (peekmessage(m, EX_MOUSE)) {
		if (m->message == WM_LBUTTONDOWN) {
			int x = m->x; int y = m->y;
			for (Button* i : buttons) {//检查按钮触发
				if (i->ifIn(x, y)) {//在按钮范围内
					if (i->uid() < 0) {
						lastgamename = i->Word();
						//在创建游戏时，依据残局文件创建游戏
						ifLastgame = true;
						check = true; state = 0;//返回主菜单
					}//检查配置文件按钮
					else {
						switch (i->uid()) {
						case 0: { check = true; state = 0; break; }
						case 1: { check = true; state = 0; ifLastgame = false;lastgamename=L""; break; }
						case 10: { this->createLastgame(); break; }
						}
					}
					break;
				}

			}
		}
		else if (WM_MOUSEWHEEL) {
			for (auto& i : buttons) {
				if (i->uid() < 0) { i->moveY(m->wheel / 10); }
			}
		}//滚动滑轮
	}
	//确认残局信息
}
	

//TODO如何创建残局？读取残局？
bool GameManager::createLastgame(bool ready) {
	if (!ready) {//创建新残局

	}
	else {//保存暂停的残局

		std::wstring name;
		wchar_t s[30];
		int result = InputBox(s, 30,
			L"保存当前游戏为残局，请填写残局名称\n"
			L"要求：\n"
			L"只能包含字母、数字或下划线\n");
		if (result == 0) {
			return false; // 用户点击取消
		}
		if (wcslen(s) == 0) {
			MessageBox(GetHWnd(), L"残局名称不能为空", L"输入错误", MB_OK | MB_ICONERROR);
			return false;
		}
		// 验证名称格式
		for (size_t i = 0; i < wcslen(s); i++) {
			wchar_t c = s[i];
			if (!((c >= L'a' && c <= L'z') ||
				(c >= L'A' && c <= L'Z') ||
				(c >= L'0' && c <= L'9') ||
				c == L'_')) {
				MessageBox(GetHWnd(),
					L"残局名称只能包含字母、数字或下划线\n"
					L"请不要使用空格、中文或其他特殊字符",
					L"输入错误", MB_OK | MB_ICONERROR);
				return false;
			}
		}
		name = s;
		std::wstring fullPath = lastgame_prefix + name + lastgame_postfix;
		if (std::filesystem::exists(fullPath)) {
			int choice = MessageBox(GetHWnd(),
				L"该残局名称已存在，是否覆盖？",
				L"确认覆盖", MB_YESNO | MB_ICONWARNING);
			if (choice != IDYES) {
				return false;
			}
		}
		std::ofstream o(fullPath, std::ios::binary);
		if (!o.is_open()) {
			MessageBox(GetHWnd(), L"无法创建残局文件", L"错误", MB_OK | MB_ICONERROR);
			return false;
		}
		o.write((char*)&(thisgame->settings), sizeof(thisgame->settings));
		thisgame->baffle->serialize(o);
		thisgame->ball->serialize(o);
		thisgame->map->serialize(o);
		int score = thisgame->getScore();
		o.write((char*)&score, sizeof(score));
		int blood = thisgame->getblood();
		o.write((char*)&blood, sizeof(blood));

		o.close();

		lastgamename = name;
	}
	ifLastgame = true;
	return true;
}
