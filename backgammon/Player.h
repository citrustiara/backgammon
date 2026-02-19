#pragma once
#include "Board.h"
#include <vector>
class player {
protected:
  bool color;

public:
  player(bool c) : color(c) {}
  virtual ~player() {}
  virtual void makemove(board &b) = 0;
  bool getcolor() const { return color; }
  virtual std::vector<Move> getpossiblemoves(int dice1, board &b);
  std::vector<Move> getallpossiblemoves(const std::vector<int> &availableDice,
                                        board &b);
};