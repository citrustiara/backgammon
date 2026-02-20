#include "Real_player.h"
#include <cmath>
#include <iostream>
#include <vector>

void real_player::makemove(board& b) {
	rolldice();
	b.draw();
	while (true) {
		if(areDiceEmpty()) break;

		std::vector<Move> all_moves = getallpossiblemoves(b);

		if (all_moves.empty()) {
			std::cout << "Brak mozliwych ruchow dla kostek: ";
			for (int& d : dice) {
				if (d > 0) std::cout << d << " ";
			}
			std::cout << std::endl;
			break;
		}

		std::cout << "\nTwoje kostki: ";
		for (int& d : dice) {
			if(d>0) std::cout << d << " ";
		}
		std::cout << "\nTwoje mozliwe ruchy:\n";
		for (size_t i = 0; i < all_moves.size(); ++i) {
			std::cout << i + 1 << ". ";
			if (all_moves[i].from == -1)
				std::cout << "BAR";
			else
				std::cout << all_moves[i].from + 1;
			std::cout << " -> ";
			if(all_moves[i].to<=23 && all_moves[i].to >= 0) std::cout << all_moves[i].to + 1 << "\n";
			else {
				int dist = abs(all_moves[i].to - all_moves[i].from);
				std::cout << "OFF" << " (dice: " << dist << " )\n";}
		}

		int choice;
		while (true) {
			std::cout << "Wybierz numer ruchu: ";
			if (!(std::cin >> choice)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Blad. Wpisz liczbe.\n";
				continue;
			}
			if (choice < 1 || choice >(int)all_moves.size()) {
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
		consumeDie(selected);
	}
}
