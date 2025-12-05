#pragma once//通用基础信息
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include<vector>
#include <string>
#include<fstream>
#include <filesystem>

class BasicSettings
{
};


extern const int ballR ;//球半径
extern const int baffleWidth;//挡板厚度


extern const int WindowWidth ;
extern const int WindowHeight ;

extern const std::wstring hz;//配置文件后缀
extern const std::wstring mr;//配置文件目录


class gameSettings {
public:
	int basicV = 1;//基础球速
	int seed = -1;//种子
	int k = 1;//初始关卡
};









