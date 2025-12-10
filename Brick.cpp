#include "Brick.h"
#include "Ball.h"
#include "aGame.h"
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

void Brick::check(Ball* ball,aGame* game) {//检测与球的碰撞并处理
	if (brickType == 3) return;//无砖不检测 
	CollisionInfo* info = collide(ball->getx(), ball->gety(), ballR, x, y, w, h);//判断球与砖块是否碰撞
	if (info->collided) {//若碰撞
		if (brickType == 0) {//普通砖被打掉
			brickType = 3;
			game->earnScore();
		}
		else if (brickType == 1) {//耐久砖变为普通砖
			brickType = 0;
			game->earnScore();
		}
		//坚不可摧砖不受影响
		if (info->in) {//如果球速过快导致球直接进入砖块内部
			//我们简单地让球反弹回去
			ball->bounce('x');
			ball->bounce('y');
		}
		else {
			if (info->collisionY == y + h) {//如果球撞到了砖的水平面
				ball->sety(float(y + h + ballR));
				ball->bounce('x');
			}
			if (info->collisionY == y) {
				ball->sety(float(y - ballR));
				ball->bounce('x');
			}
			if (info->collisionX == x) {//如果球撞到了砖的垂直面
				ball->setx(float(x - ballR));
				ball->bounce('y');
			}
			if (info->collisionX == x + w) {
				ball->setx(float(x + w + ballR));
				ball->bounce('y');
			}
			//注：如果正好撞到角上，两个bounce都会执行。
		}
	}
	delete info;
	return;
}