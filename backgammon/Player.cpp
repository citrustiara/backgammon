#include "Player.h"
#include <array>
#include <cstdlib>
#include <random>
#include <vector>


static std::random_device rd;
static std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 6);

std::vector<Move> player::getpossiblemoves(int dice1, board& b) {
	std::vector<Move> moves;

	if (dice1 == 0)
		return moves;

	int bar = (color == 0) ? b.getBarP1() : b.getBarP2();

	const int& d = dice1;
	if (bar > 0) {
		int target = (color == 0) ? (d - 1) : (24 - d);
		if (b.canLand(target, color)) {
			moves.push_back({ -1, target }); //-1 to bar
		}
	}
	else {
		const std::array<int, 24>& points = b.getPoints();
		for (int i = 0; i < 24; ++i) {
			if ((color == 0 && points[i] > 0) || (color == 1 && points[i] < 0)) {
				int target = (color == 0) ? (i + d) : (i - d);
				if (b.canLand(target, color)) {
					moves.push_back({ i, target });
				}
			}
		}
	}
	return moves;
}

std::vector<Move>
player::getallpossiblemoves(board& b) {
	std::vector<Move> all_moves;
	const std::vector<int>& availableDice = dice; //reference nie zajmuje dodatkowej pamieci, niech tak zostanie po starej wersji juz
	// czy kostki sa takie same
	bool all_same = true;
	if (availableDice.size() >= 2 && availableDice[0] == availableDice[1] && availableDice[1]!=0) {
		all_moves = getpossiblemoves(availableDice[0], b);
	}

	else {
		for (int d : availableDice) {
			if (d != 0) {
				std::vector<Move> m = getpossiblemoves(d, b);
				all_moves.insert(all_moves.end(), m.begin(), m.end());
			}
		}
	}
	return all_moves;
}

void player::rolldice() {
	dice.clear();
	dice.push_back(dist(gen));
	dice.push_back(dist(gen));
	if (dice[0] == dice[1]) {
		dice.push_back(dice[0]);
		dice.push_back(dice[0]);
	}
}

bool player::areDiceEmpty() const {
	for (int d : dice) {
		if (d > 0)
			return false;
	}
	return true;
}
void player::consumeDie(Move selected) {
	int dist;
	if (selected.from == -1) {
		dist = (color == 0) ? (selected.to + 1) : (24 - selected.to);
	}
	else {
		dist = std::abs(selected.to - selected.from);
	}

	for (int& d : dice) {
		if (d == dist) {
			d = 0;
			break;
		}
	}
}
