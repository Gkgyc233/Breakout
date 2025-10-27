#pragma once//游戏管理器
#include "BasicSettings.h"
class GameManager
{private:
	int state = 0;//状态参数，0为主菜单，1为自定义配置界面，2为残局设定加载界面，3为游戏内界面，4为暂停保存残局界面
	bool ifrunning = true;//游戏运行中

	std::string settings = "default";
	std::string lastgame;

	void Menudraw() {};//主菜单绘制
	void Settings() {};//进入自定义配置界面//调用配置的类的函数
	void Lastgame() {};//进入残局设定加载界面//调研残局的类的函数
	void Stop() {};//进入暂停界面
	bool Start() {};//开始一局游戏
public:
	void draw() {};//整体的绘制函数//根据不同状态调用不同的绘制函数
	void run() {};//游戏运行，检查输入信号，切换界面
	bool ifRunning() { return ifrunning; };//游戏是否运行中
};

