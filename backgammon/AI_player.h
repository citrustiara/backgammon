#pragma once
#include "Board.h"
#include "Player.h"
class AI_player : public player {
public:
	AI_player(bool c) : player(c) {}
	void makemove(board& b) override;
};