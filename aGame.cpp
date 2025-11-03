#include "aGame.h"
aGame::aGame(std::string settings, int gamelevel,
	std::vector<Brick>& bricks,
	std::string lastGame
) :
	settings(settings), gamelevel(gamelevel) {
	readLastGame(lastGame);
};
aGame::aGame(std::string settings, int gamelevel) :
	scores(0), blood(3), width(9),
	hight(18), settings(settings), gamelevel(gamelevel){
};

void aGame::readLastGame(std::string lastgame) {};