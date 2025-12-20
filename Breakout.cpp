// Breakout.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "BasicSettings.h"
#include "GameManager.h"

int main()
{
    
    initgraph(WindowWidth, WindowHeight);
    IMAGE img(WindowWidth, WindowHeight);
    SetWorkingImage(&img);
    GameManager gm(img);
    while (gm.ifRunning()) {//在没有退出游戏的情况下，不断循环刷新
        gm.run();
        gm.draw();
        SetWorkingImage(); // 切换回屏幕
        putimage(0, 0, &img); // 将内存图像输出到屏幕
        SetWorkingImage(&img); // 切换回内存缓冲区
        Sleep(10);
    }
    closegraph();
    return 0;

}
