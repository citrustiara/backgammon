#include "Player.h"
#include <array>
#include <vector>


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
player::getallpossiblemoves(const std::vector<int>& availableDice, board& b) {
	std::vector<Move> all_moves;

	// czy kostki sa takie same
	bool all_same = true;
	if (availableDice.size() >= 2 && availableDice[0] == availableDice[1]) {
		all_moves = getpossiblemoves(availableDice[0], b);
	}

	else {
		for (int d : availableDice) {
			std::vector<Move> m = getpossiblemoves(d, b);
			all_moves.insert(all_moves.end(), m.begin(), m.end());
		}
	}
	return all_moves;
}
