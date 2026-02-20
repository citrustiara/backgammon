#include "Game.h"
#include <iostream>

Game::Game(player& player1, player& player2, board& gameBoard)
	: p1(player1), p2(player2), b(gameBoard) {
}

void Game::simulate() {
	int gameoverflag = 0;
	while (gameoverflag == 0) {
		std::cout << "\n--- TURA GRACZA 1 (B - Black) ---\n";
		p1.makemove(b);
		gameoverflag = b.isGameOver();
		if (gameoverflag > 0) break;
		std::cout << "\n--- TURA GRACZA 2 (W - White) ---\n";
		p2.makemove(b);
		gameoverflag = b.isGameOver();
		if (gameoverflag > 0) break;

	}
	if (gameoverflag == 1) {
		std::cout << "\nGRACZ 1 (B - Black) WYGRYWA\n";
	}
	else if (gameoverflag == 2) {
		std::cout << "\nGRACZ 2 (W - White) WYGRYWA\n";
	}
}
