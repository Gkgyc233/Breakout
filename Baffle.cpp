#include "Baffle.h"

void Baffle::baffleDraw() {//ªÊ÷∆µ≤∞Â
	setfillcolor(WHITE);
	fillrectangle(x, y, x + length, y + baffleWidth);
}

void Baffle::baffleMove(){//“∆∂Øµ≤∞Â
	if ((GetAsyncKeyState('A') & 0x8000) && !hitLeftWall()) x -= baffleSpeed;
	else if ((GetAsyncKeyState('D') & 0x8000) && !hitRightWall()) x += baffleSpeed;
}