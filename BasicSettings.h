#pragma once//通用基础信息
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include<vector>
#include <string>
class BasicSettings
{
};

const static int ballR = 10;//球半径
const static int baffleWidth = 50;//挡板厚度


const static int WindowWidth = 1080;
const static int WindowHeight = 640;

enum brickType { Durable, Normal, Indestructible, No };//#,@,* 三种砖与没有砖的占位







/*
我们规定：
gameLevel只影响ball的速度和baffle的宽度；
ball的实际速度由base_v和gameLevel综合而来
残局信息覆盖配置信息

*/


