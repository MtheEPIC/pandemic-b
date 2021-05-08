#pragma once
#include "Player.hpp"

namespace pandemic {
	class Scientist : public Player
	{
	public:
		Scientist(Board, City, int);
		~Scientist();
	};
}