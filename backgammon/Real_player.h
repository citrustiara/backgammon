#pragma once
#include "Board.h"
#include "Player.h"
class real_player : public player {
public:
	real_player(bool c) : player(c) {}
	void makemove(board& b) override;
};