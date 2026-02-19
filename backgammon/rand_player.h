#pragma once
#include "Board.h"
#include "Player.h"
class rand_player : public player {
public:
	rand_player(bool c) : player(c) {}
	void makemove(board& b) override;
};