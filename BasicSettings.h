#pragma once//通用基础信息
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include<vector>
class BasicSettings
{
};
/*
我们规定：
gameLevel只影响ball的速度和baffle的宽度；

*/
const int ballR=10;//球半径
const int baffleWidth;//挡板厚度

enum brickType {Durable,Normal,Indestructible,No};//#,@,* 三种砖与没有砖的占位

