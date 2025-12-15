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
	Map():ifempty(false) {};
	Map(int seed,int xBlockNum ,int yBlockNum , int level);
	void mapDraw();
    void setBrick(brickType t, int x, int y) { bricks[x][y].setType(t); }
	bool is_empty();//判断地图上是否还有可摧毁砖块
	void check(Ball* ball,aGame* game);//检测球与砖块的碰撞并处理
	void clear();//清图，调试用。

    // 序列化：将Map对象转换为字节流
    void serialize(std::ofstream& out) const {
        // 保存基本参数
        out.write(reinterpret_cast<const char*>(&xBlockNum), sizeof(xBlockNum));
        out.write(reinterpret_cast<const char*>(&yBlockNum), sizeof(yBlockNum));
        out.write(reinterpret_cast<const char*>(&BlockWidth), sizeof(BlockWidth));
        out.write(reinterpret_cast<const char*>(&BlockHeight), sizeof(BlockHeight));
        out.write(reinterpret_cast<const char*>(&BrickHeight), sizeof(BrickHeight));
        out.write(reinterpret_cast<const char*>(&BrickWidth), sizeof(BrickWidth));


        for (const auto& row : bricks) {
            for (const Brick& brick : row) {
                brick.serialize(out); 
            }
        }
    }
    // 反序列化：从字节流恢复Map对象
    bool deserialize(std::ifstream& in) {
        // 读取基本参数
        if (!in.read(reinterpret_cast<char*>(&xBlockNum), sizeof(xBlockNum))) return false;
        if (!in.read(reinterpret_cast<char*>(&yBlockNum), sizeof(yBlockNum))) return false;
        if (!in.read(reinterpret_cast<char*>(&BlockWidth), sizeof(BlockWidth))) return false;
        if (!in.read(reinterpret_cast<char*>(&BlockHeight), sizeof(BlockHeight))) return false;
        if (!in.read(reinterpret_cast<char*>(&BrickHeight), sizeof(BrickHeight))) return false;
        if (!in.read(reinterpret_cast<char*>(&BrickWidth), sizeof(BrickWidth))) return false;

        bricks.resize(xBlockNum);
        // 读取每一行
        for (int i = 0; i < xBlockNum; i++) {
            bricks[i].resize(yBlockNum);
            // 读取当前行的每个Brick
            for (int j = 0; j < yBlockNum; j++) {
                bricks[i][j].deserialize(in);  
            }
        }
    }



private:
	int xBlockNum;//横向砖块数量
	int yBlockNum;//纵向砖块数量
    bool ifempty = false;
	std::vector<std::vector<Brick>> bricks;//砖块二维数组
	int BlockWidth;
	int BlockHeight;
	int BrickHeight;
	int BrickWidth;
    bool checkEmpty();
};

