#include "Board.h"
#include "Utils.h"
#include <array>
#include <cmath>
#include <iostream>

board::board() {
	// Player 1 +, Player 2 -
	points.fill(0);
	points[0] = 2;   // Player 1
	points[5] = -5;  // Player 2
	points[7] = -3;  // Player 2
	points[11] = 5;  // Player 1
	points[12] = -5; // Player 2
	points[16] = 3;  // Player 1
	points[18] = 5;  // Player 1
	points[23] = -2; // Player 2

	bar_player1 = 0;
	bar_player2 = 0;
}

board::board(std::array<int, 24> initial_points, int bar1, int bar2) {
	this->points = initial_points;
	this->bar_player1 = bar1;
	this->bar_player2 = bar2;
}

void board::draw() {
	// clear screen and move cursor to home
	clearScreen();

	const int MAX_HEIGHT = 5;
	std::cout << "  13 14 15 16 17 18  | BAR |  19 20 21 22 23 24                "
		"      Player 1 (B)"
		<< std::endl;
	std::cout << " --------------------+-----+--------------------               "
		"      Player 2 (W)"
		<< std::endl;

	// gorna czesc planszy
	for (int h = 0; h < MAX_HEIGHT; ++h) {
		std::cout << " ";
		// 13-18
		for (int i = 12; i <= 17; ++i) {
			int count = std::abs(points[i]);
			if (count > h)
				std::cout << (points[i] > 0 ? "  B" : "  W");
			else
				std::cout << "  .";
		}

		// BAR gora
		std::cout << "  |  "
			<< (bar_player1 > h ? "B" : (bar_player2 > h ? "W" : " "))
			<< "  | ";

		// 19-24
		for (int i = 18; i <= 23; ++i) {
			int count = std::abs(points[i]);
			if (count > h)
				std::cout << (points[i] > 0 ? "  B" : "  W");
			else
				std::cout << "  .";
		}
		std::cout << std::endl;
	}

	std::cout << "                     |     |                    " << std::endl;

	// dolna czesc planszy
	for (int h = MAX_HEIGHT - 1; h >= 0; --h) {
		std::cout << " ";
		// 12-7
		for (int i = 11; i >= 6; --i) {
			int count = std::abs(points[i]);
			if (count > h)
				std::cout << (points[i] > 0 ? "  B" : "  W");
			else
				std::cout << "  .";
		}

		// BAR dol
		std::cout << "  |  "
			<< (bar_player1 > (h + MAX_HEIGHT)
				? "B"
				: (bar_player2 > (h + MAX_HEIGHT) ? "W" : " "))
			<< "  | ";

		// 6-1
		for (int i = 5; i >= 0; --i) {
			int count = std::abs(points[i]);
			if (count > h)
				std::cout << (points[i] > 0 ? "  B" : "  W");
			else
				std::cout << "  .";
		}
		std::cout << std::endl;
	}

	std::cout << " --------------------+-----+--------------------" << std::endl;
	std::cout << "  12 11 10  9  8  7  | BAR |   6  5  4  3  2  1" << std::endl;
}

void board::incBarPlayer1() { bar_player1++; }
void board::decBarPlayer1() {
	if (bar_player1 > 0)
		bar_player1--;
}
void board::incBarPlayer2() { bar_player2++; }
void board::decBarPlayer2() {
	if (bar_player2 > 0)
		bar_player2--;
}

const std::array<int, 24>& board::getPoints() const { return points; }

int board::getBarP1() const { return bar_player1; }

int board::getBarP2() const { return bar_player2; }

bool board::canLand(int index, bool color) const {
	//if (index < 0 || index >= 24)
	//	return false;
	if (index >= 24 && color == 0) { // 0 to black
		for (int i = 0; i < 18; ++i) {
			if (points[i] > 0 || bar_player1 > 0)
				return false;
		}
		return true;
	}
	if (index < 0 && color == 1) {
		for (int i = 23; i > 5; --i) {
			if (points[i] < 0 || bar_player1 > 0)
				return false;
		}
		return true;
	}
	int val = points[index];
	if (color == 0) {   // player 1 +
		return val >= -1; // empty, own or 1 opponent piece
	}
	else {            // player 2 -
		return val <= 1;  // empty, own or 1 opponent piece
	}
}

void board::executeMove(Move m, bool color) {
	// from
	if (m.from == -1) {
		if (color == 0)
			decBarPlayer1();
		else
			decBarPlayer2();
	}
	else {
		if (color == 0)
			points[m.from]--;
		else
			points[m.from]++;
	}

	// target
	if (color == 0) { // player 1 +
		if (m.to < 24) {
			points[m.to]++;
			if (points[m.to] == 0) { // jesli 0 po ++ to znaczy ze tam byl przeciwnik
				points[m.to] = 1;
				incBarPlayer2();
			}
		}
	}
	else { // player 2 -
		if (m.to >= 0) {
			points[m.to]--;
			if (points[m.to] == 0) { // analogicznie
				points[m.to] = -1;
				incBarPlayer1();
			}
		}
	}
}

int board::isGameOver() const {
	bool p1_wins = true, p2_wins = true;
	for (int i = 0; i < 24; ++i) {
		if (points[i] > 0)
			p1_wins = false;
		if (points[i] < 0)
			p2_wins = false;
	}
	if (bar_player1 > 0)
		p1_wins = false;
	if (bar_player2 > 0)
		p2_wins = false;
	if (p1_wins)
		return 1;
	if (p2_wins)
		return 2;
	return 0;
}