#pragma once
#include "BasicSettings.h"
#include "Brick.h"
#include <vector> // 修正：确保包含 vector 头文件
using std::vector; // 修正：使用 std 命名空间下的 vector

class Ball;//前向声明
class Brick;//前向声明
class Map
{
public:
	Map(int seed,int xBlockNum ,int yBlockNum , int level);
	void mapDraw();
	bool is_empty();//判断地图上是否还有可摧毁砖块
	void check(Ball* ball,aGame* game);//检测球与砖块的碰撞并处理
	void clear();//清图，调试用。
private:
	int xBlockNum;//横向砖块数量
	int yBlockNum;//纵向砖块数量
	std::vector<std::vector<Brick>> bricks;//砖块二维数组
	int BlockWidth;
	int BlockHeight;
	int BrickHeight;
	int BrickWidth;
};

