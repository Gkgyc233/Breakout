#include "BasicSettings.h"


const int ballR = 10;//球半径
const int baffleWidth = 50;//挡板厚度


const int WindowWidth = 1080;
const int WindowHeight = 640;

enum brickType { Durable, Normal, Indestructible, No };//#,@,* 三种砖与没有砖的占位

const std::wstring hz = L".config";
const std::wstring mr = L".\\config\\";

const std::wstring lastgame_prefix = L".\\endgames\\";
const std::wstring lastgame_postfix = L".end";

const float g = 0.3;//重力加速度
/*
我们规定：
gameLevel只影响ball的速度和baffle的宽度；
ball的实际速度由base_v和gameLevel综合而来
残局信息覆盖配置信息

*/