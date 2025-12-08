#pragma once//ÓÎÏ·ÀïµÄµ²°å
#include "BasicSettings.h"
class Baffle
{
public:
	Baffle() {};
	void baffleDraw();//»æÖÆµ²°å
	void baffleMove();//ÒÆ¶¯µ²°å
	int getMid() { return x+length/2; };
	int getx() { return x; };
	int gety() { return y; };
	int getlength() { return length; };
	bool hitLeftWall() { return x <= 40; };//¼ì²âÊÇ·ñÅöµ½×ó±ßÇ½±Ú
	bool hitRightWall() { return x + length >= 740; };//¼ì²âÊÇ·ñÅöµ½ÓÒ±ßÇ½±Ú
private:
	int length = WindowWidth*6/27;//µ²°å³¤¶È240px
	int x =(780-length)/2, y=480;//³õÊ¼×ø±ê
};

