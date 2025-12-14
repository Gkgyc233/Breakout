#pragma once//球
#include"BasicSettings.h"
#include"Baffle.h"
class Map;//前向声明
class aGame;//前向声明
class Ball
{
public:
	Ball() {};
	void setBall(int gameLevel, int base_v,int t=90);//输入关卡等级,基础速度，方向
	void linkBaffle(Baffle* b);//关联挡板
	void ballDraw();//球绘制
	void ballMove();//球移动
	void collideWithBaffle();//与挡板碰撞检测与反弹
	bool fall() { return y - ballR > WindowHeight; };//检测球是否掉落出屏幕
	void ballRun(Map* map,aGame* game);//球的逻辑运行
	float getx() { return x; };
	float gety() { return y; };
	float getvx() { return vx; };
	float getvy() { return vy; };
	void sety(float yy) { y = yy; };
	void setx(float xx) { x = xx; };
	void bounce(char mode);//根据碰撞方式计算反弹，mode==x表示从撞到水平面上反弹，mode==y表示撞到垂直面上反弹
	void displayInfo();//显示球的信息，调试用
	bool isFrozen() { return frozen; };
	void defroze() { frozen = false; };

    void serialize(std::ofstream& out) const {
        // 保存基本数据成员
		out.write(reinterpret_cast<const char*>(&x), sizeof(x));
		out.write(reinterpret_cast<const char*>(&y), sizeof(y));
		out.write(reinterpret_cast<const char*>(&vx), sizeof(vx));
		out.write(reinterpret_cast<const char*>(&vy), sizeof(vy));
		out.write(reinterpret_cast<const char*>(&base_v), sizeof(base_v));
		out.write(reinterpret_cast<const char*>(&real_v), sizeof(real_v));
		out.write(reinterpret_cast<const char*>(&limit_v), sizeof(limit_v));
		out.write(reinterpret_cast<const char*>(&theta), sizeof(theta));
		out.write(reinterpret_cast<const char*>(&frozen), sizeof(frozen));

    }

    bool deserialize(std::ifstream& in,Baffle* b) {
		if (!in.read(reinterpret_cast<char*>(&x), sizeof(x))) return false;
		if (!in.read(reinterpret_cast<char*>(&y), sizeof(y))) return false;
		if (!in.read(reinterpret_cast<char*>(&vx), sizeof(vx))) return false;
		if (!in.read(reinterpret_cast<char*>(&vy), sizeof(vy))) return false;
		if (!in.read(reinterpret_cast<char*>(&base_v), sizeof(base_v))) return false;
		if (!in.read(reinterpret_cast<char*>(&real_v), sizeof(real_v))) return false;
		if (!in.read(reinterpret_cast<char*>(&limit_v), sizeof(limit_v))) return false;
		if (!in.read(reinterpret_cast<char*>(&theta), sizeof(theta))) return false;
		if (!in.read(reinterpret_cast<char*>(&frozen), sizeof(frozen))) return false;
        linkBaffle(b);
        // 注意：baffle指针在反序列化后需要重新设置
        // 这个调用linkBaffle完成
    }


private:
	float x, y;//坐标
	float vx, vy;
	int base_v;//基础球速
	float real_v;//实际计算得到球速
	float limit_v;//速度上限
	float theta;//速度方向角度（角度制）
	bool frozen;//球是否可动（我们希望球在一开始静止，玩家按下空格后再开始移动）
	Baffle* baffle = nullptr;//该局游戏的挡板对象
};

