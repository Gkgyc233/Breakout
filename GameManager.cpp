#include"GameManager.h"


void GameManager::draw() {
	switch (state) {
	case 0:Menudraw(); break;
	case 1:SetDraw(); break;
	}
};