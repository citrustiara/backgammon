#include "AI_player.h"
#include <iostream>
#include <random>
#include <vector>

static std::random_device rd;
static std::mt19937 gen(rd());
// TODO jakas prawdziwa logika
void AI_player::makemove(board& b) {
	rolldice();
	b.draw();
	std::cout << std::endl
		<< "RandPlayer wyrzucil kostki" << std::endl;

	while (true) {
		if (areDiceEmpty())
			break;

		std::vector<Move> all_moves = getallpossiblemoves(b);

		if (all_moves.empty())
			break;
		// zbicie przeciwnika najlepsze
		bool foundenemy = false;
		bool foundsingleown = false;
		Move selected = all_moves[0];
		for (Move& move : all_moves) {
			if (isEnemy(move.to, b)) {
				selected = move;
				foundenemy = true;
				break; //jezeli przeciwnik jest do zbicia to nie ma co szukac dalej to jest najlepszy ruch
			}
			if (isSingleOwn(move.to, b)) {
				selected = move;
				foundsingleown = true; //jesli nie bylo przeciwnika do zbicia to szukamy ruchu zabezpieczajacego pojedynczy pionek naszego koloru
			}
		}
		if (!foundenemy && !foundsingleown) { // jesli nie ma przeciwnika do zbicia ani naszego do zabezpieczenia to wybieramy losowy ruch
			std::uniform_int_distribution<int> idx(0, (int)all_moves.size() - 1);
			selected = all_moves[idx(gen)];
		}
		std::cout << std::endl << "RandPlayer wykonuje ruch: ";
		if (selected.from == -1)
			std::cout << "BAR";
		else
			std::cout << selected.from + 1;
		std::cout << " -> ";
		if (selected.to <= 23 && selected.to >= 0)
			std::cout << selected.to + 1 << std::endl;
		else
			std::cout << "OFF" << std::endl;

		b.executeMove(selected, color);
		b.draw();
		consumeDie(selected);
	}
}
