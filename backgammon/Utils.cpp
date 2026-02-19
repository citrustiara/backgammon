#include "Utils.h"
#include <iostream>

void clearScreen() {
    std::cout << "\033[H\033[J";
}
