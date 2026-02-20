#pragma once
#include "Board.h"
#include <vector>
class player {
protected:
  bool color;
  std::vector<int> dice;

public:
  player(bool c) : color(c) {}
  virtual ~player() {}
  virtual void makemove(board &b) = 0;
  bool getcolor() const { return color; }
  virtual std::vector<Move> getpossiblemoves(int dice1, board &b);
  void rolldice();
  std::vector<Move> getallpossiblemoves(board &b);
  void consumeDie(Move selected);
  bool areDiceEmpty() const;
};