#include "Real_player.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

static std::random_device rd;
static std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 6);

void real_player::makemove(board& b) {
	int d1 = dist(gen);
	int d2 = dist(gen);

	std::vector<int> dice = { d1, d2 };
	if (d1 == d2) { // jezeli podwojne to 4 ruchy
		dice.push_back(d1);
		dice.push_back(d1);
	}
	b.draw();
	while (true) {
		int currentD1 = 0, currentD2 = 0;
		std::vector<int> available;
		for (int d : dice)
			if (d > 0)
				available.push_back(d);

		if (available.empty())
			break;

		std::vector<Move> all_moves = getallpossiblemoves(available, b);

		if (all_moves.empty()) {
			std::cout << "Brak mozliwych ruchow dla kostek: ";
			for (int d : available)
				std::cout << d << " ";
			std::cout << std::endl;
			break;
		}

		std::cout << "\nTwoje kostki: ";
		for (int d : available)
			std::cout << d << " ";
		std::cout << "\nTwoje mozliwe ruchy:\n";
		for (size_t i = 0; i < all_moves.size(); ++i) {
			std::cout << i + 1 << ". ";
			if (all_moves[i].from == -1)
				std::cout << "BAR";
			else
				std::cout << all_moves[i].from + 1;
			std::cout << " -> " << all_moves[i].to + 1 << "\n";
		}

		int choice;
		while (true) {
			std::cout << "Wybierz numer ruchu (lub 0 aby zakonczyc): ";
			if (!(std::cin >> choice)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Blad. Wpisz liczbe.\n";
				continue;
			}
			if (choice < 0 || choice >(int)all_moves.size()) {
				std::cout << "Blad. Wybierz z listy powyzej.\n";
				continue;
			}
			break;
		}

		if (choice == 0)
			break;

		Move selected = all_moves[choice - 1];
		b.executeMove(selected, color);
		b.draw();
		// sprawdzamy ktora kostka zostala uzyta po dystansie i zmieniamy ja na zero
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
}
