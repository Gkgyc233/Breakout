#include "Baffle.h"

void Baffle::baffleDraw() {//ªÊ÷∆µ≤∞Â
	setfillcolor(WHITE);
	fillrectangle(x, WindowHeight / 4 * 3, x + length, WindowHeight /4*3 + baffleWidth);
}

void Baffle::baffleMove(){//“∆∂Øµ≤∞Â
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) x -= 5;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x += 5;
}