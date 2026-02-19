#pragma once
#include "Board.h"
#include "Player.h"

class Game {
private:
	player& p1;
	player& p2;
	board& b;

public:
	Game(player& player1, player& player2, board& gameBoard);
	void simulate();
};