#pragma once
#include <array>

struct Move {
	int from;
	int to;
};

class board {
private:
	std::array<int, 24> points;
	int bar_player1;
	int bar_player2;

public:
	board();
	board(std::array<int, 24> initial_points, int bar1, int bar2);
	void draw();
	void incBarPlayer1();
	void decBarPlayer1();
	void incBarPlayer2();
	void decBarPlayer2();

	const std::array<int, 24>& getPoints() const;
	int getBarP1() const;
	int getBarP2() const;
	void executeMove(Move m, bool color);
	bool canLand(int index, bool color) const;
	int isGameOver() const;
};