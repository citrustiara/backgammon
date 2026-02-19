#include "rand_player.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int> dist_d6(1, 6);

void rand_player::makemove(board &b) {
  int d1 = dist_d6(gen);
  int d2 = dist_d6(gen);

  std::vector<int> dice = {d1, d2};
  if (d1 == d2) {
    dice.push_back(d1);
    dice.push_back(d1);
  }
  b.draw();
  std::cout << std::endl
            << "RandPlayer wyrzucil: " << d1 << " i " << d2 << std::endl;

  while (true) {
    std::vector<int> available;
    for (int d : dice)
      if (d > 0)
        available.push_back(d);
    if (available.empty())
      break;

    std::vector<Move> all_moves = getallpossiblemoves(available, b);

    if (all_moves.empty())
      break;
    //Sleep(1000);
    std::uniform_int_distribution<int> idx(0, (int)all_moves.size() - 1);
    Move selected = all_moves[idx(gen)];
    std::cout << std::endl
              << "RandPlayer wykonuje ruch: "
              << (selected.from == -1 ? "BAR"
                                      : std::to_string(selected.from + 1))
              << " -> " << selected.to + 1 << std::endl;
    //Sleep(1000);
    b.executeMove(selected, color);
    b.draw();

    int dist;
    if (selected.from == -1) {
      dist = (color == 0) ? (selected.to + 1) : (24 - selected.to);
    } else {
      dist = std::abs(selected.to - selected.from);
    }

    for (int &d : dice) {
      if (d == dist) {
        d = 0;
        break;
      }
    }
  }
}
