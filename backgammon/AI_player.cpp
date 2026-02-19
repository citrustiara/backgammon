#include "AI_player.h"
#include <Windows.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
// TODO jakas prawdziwa logika
void AI_player::makemove(board& b) {
    int d1 = (rand() % 6) + 1;
    int d2 = (rand() % 6) + 1;

    std::vector<int> dice = { d1, d2 };
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
        Move selected = all_moves[rand() % all_moves.size()];
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
