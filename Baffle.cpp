#include "Baffle.h"

void Baffle::baffleDraw() {//»æÖÆµ²°å
	setfillcolor(BROWN);
	fillrectangle(x, y, x + length, y + baffleWidth);
}

void Baffle::baffleMove(){//ÒÆ¶¯µ²°å
	int temp = x;
	if (((GetAsyncKeyState('A') & 0x8000)||(GetAsyncKeyState(VK_LEFT) & 0x8000)) && !hitLeftWall()) x -= speed;
	else if (((GetAsyncKeyState('D') & 0x8000)||(GetAsyncKeyState(VK_RIGHT) & 0x8000)) && !hitRightWall()) x += speed;

	if (x > temp) moving = 1;
	else if (x < temp) moving = -1;
	else moving = 0;
	return;
}