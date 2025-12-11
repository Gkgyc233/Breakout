#pragma once
#include"BasicSettings.h"
class Button
{
private:
	bool ifsee = true;//可见性
	int id;//标明该按钮作用
	int x, y;//绘制的中心坐标
	int xx, yy;//半长宽
	COLORREF color;//按钮颜色
	COLORREF txtcolor;//文字颜色
	std::basic_string<TCHAR> word;//按钮上的文字
public:
	Button(int x,int y,int xx,int yy):x(x),y(y),xx(xx),yy(yy) {
		color = WHITE;      // 默认按钮颜色
		txtcolor = BLACK; //默认文字颜色
	}
	void setColor(COLORREF c) { color = c; }
	void settxtColor(COLORREF c) { txtcolor = c; }
	void setString(const std::basic_string<TCHAR>& str) { word = str; }
	void setString(const TCHAR* str) { word = str; }
	void draw() {
		if (!ifsee) { return; }
		setfillcolor(color);
		solidrectangle(
			x-xx,
			y-yy,
			x+xx,
			y+yy
		);
		settextcolor(txtcolor);
		setbkmode(TRANSPARENT);

		settextstyle(yy, 0, _T("Consolas"));
		int textWidth = textwidth(word.c_str());
		int textHeight = textheight(word.c_str());

		// 输出居中文字
		outtextxy(x - textWidth / 2, y - textHeight / 2, word.c_str());
	}
	bool ifIn(int inx, int iny) {
		if (ifsee&&inx > x - xx && inx < x + xx && iny<y + yy && iny>y - yy) { return true; }
		else { return false; }
	}
	void setid(int uid) { id = uid; }
	int uid() { return id; }
	void See() { ifsee = true; }
	void noSee() { ifsee = false; }
	int giveY() { return y; }
	void moveY(int dy) { y += dy;}
	std::wstring Word() { return word; }
};

