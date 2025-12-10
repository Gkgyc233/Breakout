#include "Map.h"
#include "Brick.h"
#include "Ball.h"
#include <vector>
Map::Map(int seed,int xBlockNum , int yBlockNum ,int level) {//默认的地图：9*5，砖的类型随gamelevel变化。
	this->xBlockNum = xBlockNum;
	this->yBlockNum = yBlockNum;
	this->BlockWidth = 700 / xBlockNum;
	this->BlockHeight = 200 / yBlockNum;
	this->BrickHeight = BlockHeight * 9 / 10;
	this->BrickWidth = BlockWidth * 9 / 10;
	int cur_x = 45, cur_y = 45;
	vector<vector<int>>* type = getRandType(level, seed, xBlockNum, yBlockNum);
	for (int x = 0; x < xBlockNum; x++) {
		this->bricks.push_back(std::vector<Brick>());
		for (int y = 0; y < yBlockNum; y++) {
			//int type = getRandType(level,seed);//根据level调整砖块类型
			this->bricks[x].push_back(Brick(cur_x, cur_y, BrickHeight, BrickWidth, (*type)[x][y]));//生成砖块
			cur_y += BlockHeight;
		}
		cur_x += BlockWidth;
		cur_y = 45;
	}
	delete type;
}

bool Map::is_empty() {//检测是否所有可以被打掉的砖都被打掉了
	for (int x = 0; x < xBlockNum; x++) {
		for (int y = 0; y < yBlockNum; y++) {
			if(bricks[x][y].Type()<=1){//若为普通砖或耐久砖
				return false;
			}
		}
	}
	return true;
}

void Map::mapDraw() {
	setfillcolor(WHITE);
	fillrectangle(0, 0, 40, WindowHeight);//绘制墙面、天花板、地板
	fillrectangle(740, 0, 780, WindowHeight);
	fillrectangle(0, 0, 780, 40);
	fillrectangle(0, 600, 780, WindowHeight);
	for (int x = 0; x < xBlockNum; x++) {
		for (int y = 0; y < yBlockNum; y++) {
			bricks[x][y].brickDraw();
		}
	}
	return;
}

void Map::check(Ball* ball,aGame* game) {//判断球与砖的碰撞并处理
	for (int i = 0; i < xBlockNum; i++){
		for (int j = 0; j < yBlockNum; j++  ) {
			bricks[i][j].check(ball,game);
		}
	}
}

void Map::clear() {//清图，调试用。
	for (int x = 0; x < xBlockNum; x++) {
		for (int y = 0; y < yBlockNum; y++) {
			if(bricks[x][y].Type()<=1) bricks[x][y].destroy();
		}
	}
}