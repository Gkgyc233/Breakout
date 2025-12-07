#pragma once//游戏内的砖头
#include"BasicSettings.h"
class Brick
{
public:
		Brick(int x,int y,int h,int w,int brickType = 0): x(x),y(y),h(h),w(w),brickType(brickType){};
		int Type() { return brickType; };
		void brickDraw();
private:
	int brickType;//砖块类型:0-普通砖 1-耐久砖 2-坚不可摧砖 3-无砖
	int x, y;//坐标
	int h, w;//高宽
};

