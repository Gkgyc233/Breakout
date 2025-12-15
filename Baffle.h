#pragma once//游戏里的挡板
#include "BasicSettings.h"
class Baffle
{
public:
	Baffle() {};
	void baffleDraw();//绘制挡板
	void baffleMove();//移动挡板
	void adjust(int level) { //根据关卡调整挡板长度，最短60px
		if (length < minLength) length = minLength;
		x = (MapWidth + 2 * WallWidth - length) / 2;
		x = (780 - length) / 2;
		speed = 8 + 0.3 * level;
		if (speed > 15.0) speed = 15.0;
		return;
	}
	int getMid() { return x+length/2; };
	int getx() { return x; };
	int gety() { return y; };
	int getlength() { return length; };
	bool hitLeftWall() { return x <= WallWidth; };//检测是否碰到左边墙壁
	bool hitRightWall() { return x + length >= WallWidth + MapWidth; };//检测是否碰到右边墙壁

	void serialize(std::ofstream& out) const {//序列化函数
		out.write(reinterpret_cast<const char*>(&x), sizeof(x));
		out.write(reinterpret_cast<const char*>(&y), sizeof(y));
		out.write(reinterpret_cast<const char*>(&length), sizeof(length));
		out.write(reinterpret_cast<const char*>(&speed), sizeof(speed));
	}
	bool deserialize(std::ifstream& in) {//反序列化函数
		if(!in.read(reinterpret_cast<char*>(&x), sizeof(x)))return false;
		if(!in.read(reinterpret_cast<char*>(&y), sizeof(y)))return false;
		if(!in.read(reinterpret_cast<char*>(&length), sizeof(length)))return false;
		if(!in.read(reinterpret_cast<char*>(&speed), sizeof(speed)))return false;
		return true;
	}

private:
	int length = WindowWidth * 7 / 27;//挡板长度
	int minLength = WindowWidth / 18;//挡板最小长度
	int x = (MapWidth + 2 * WallWidth - length) / 2, y = WindowHeight * 13 / 16;//初始坐标
	float speed = 8;
};

