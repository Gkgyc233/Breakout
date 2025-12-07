#include "Brick.h"

void Brick::brickDraw() {
	switch (this->brickType) {
		case 0: { setfillcolor(WHITE); break; }//普通砖白色
		case 1: { setfillcolor(RGB(255, 215, 0)); break; }//耐久砖金色
		case 2: { setfillcolor(RGB(128, 128, 128)); break; }//坚不可摧砖灰色
		case 3: { return; }//无砖不绘制
	}
	fillrectangle(x, y, x + w, y + h);
	return;
}