#pragma once
#include "Player.hpp"

namespace pandemic {
	class Researcher : public Player
	{
	public:
		Researcher(Board, City);
		~Researcher();
	};
}