#include "rand_player.h"
#include <cmath>
#include <iostream>
#include <random>
#include <vector>


static std::random_device rd;
static std::mt19937 gen(rd());

void rand_player::makemove(board &b) {
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

    std::uniform_int_distribution<int> idx(0, (int)all_moves.size() - 1);
    Move selected = all_moves[idx(gen)];
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
