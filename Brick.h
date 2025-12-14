#pragma once//游戏内的砖头
#include"BasicSettings.h"
#include"Ball.h"

class Ball;//前向声明

class Brick
{
public:
    Brick() {};
		Brick(int x,int y,int h,int w,int brickType = 0): x(x),y(y),h(h),w(w),brickType(brickType){};
		int Type() { return brickType; };
		void brickDraw();
		void check(Ball* ball,aGame* game);//检测与球的碰撞并处理
		void destroy() { brickType = 3; }//自毁，调试用。

        // 序列化：将Brick对象转换为字节流
        void serialize(std::ofstream& out) const {
            out.write((char*)&brickType, sizeof(brickType));
            out.write((char*)&x, sizeof(x));
            out.write((char*)&y, sizeof(y));
            out.write((char*)&h, sizeof(h));
            out.write((char*)&w, sizeof(w));
        }

        // 反序列化：从字节流恢复Brick对象
        void deserialize(std::ifstream& in) {
            in.read((char*)&brickType, sizeof(brickType));
            in.read((char*)&x, sizeof(x));
            in.read((char*)&y, sizeof(y));
            in.read((char*)&h, sizeof(h));
            in.read((char*)&w, sizeof(w));
        }




private:
	int brickType;//砖块类型:0-普通砖 1-耐久砖 2-坚不可摧砖 3-无砖
	int x, y;//坐标
	int h, w;//高宽
};

