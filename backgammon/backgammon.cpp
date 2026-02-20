#include "Board.h"
#include "Game.h"
#include "Real_player.h"
#include "rand_player.h"
#include "Utils.h"
#include <iostream>

int menu() {


// ____    _    ____ _  ______    _    __  __ __  __  ___  _   _ 
//| __ )  / \  / ___| |/ / ___|  / \  |  \/  |  \/  |/ _ \| \ | |
//|  _ \ / _ \| |   | ' / |  _  / _ \ | |\/| | |\/| | | | |  \| |
//| |_) / ___ \ |___| . \ |_| |/ ___ \| |  | | |  | | |_| | |\  |
//|____/_/   \_\____|_|\_\____/_/   \_\_|  |_|_|  |_|\___/|_| \_|
	
	std::cout << std::endl;
	std::cout <<"			 ____    _    ____ _  ______    _    __  __ __  __  ___  _   _ "<< std::endl;
	std::cout <<"			| __ )  / \\  / ___| |/ / ___|  / \\  |  \\/  |  \\/  |/ _ \\| \\ | |"<< std::endl;
	std::cout <<"			|  _ \\ / _ \\| |   | ' / |  _  / _ \\ | |\\/| | |\\/| | | | |  \\| |"<< std::endl;
	std::cout <<"			| |_) / ___ \\ |___| . \\ |_| |/ ___ \\| |  | | |  | | |_| | |\\  |"<< std::endl;
	std::cout <<"			|____/_/   \\_\\____|_|\\_\\____/_/   \\_\\_|  |_|_|  |_|\\___/|_| \\_|"<< std::endl;
	std::cout << std::endl;
	std::cout << "			                       press 1 to load from file" << std::endl;
	std::cout << "			                       press 2 to start new game" << std::endl;
	int choice = 0;
	while (true) {
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Blad. Wpisz liczbe.\n";
			continue;
		}
		if (choice < 0 || choice > 2) {
			std::cout << "Blad. Wybierz z listy.\n";
			continue;
		}
		break;
	}
	return choice;

}

int main() {
	
	board b;
	//real_player gracz1(0); // Black
	rand_player gracz1(0); // White
	rand_player gracz2(1); // White
	int choice = menu();
	if (choice == 2) {
		clearScreen();
		Game rozgrywka(gracz1, gracz2, b);
		rozgrywka.simulate();
	}
	if (choice == 1) {
		std::cout << "Opcja wczytywania z pliku nie jest jeszcze zaimplementowana.\n";
	}

	return 0;
}

