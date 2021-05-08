#pragma once
#include "Player.hpp"

namespace pandemic {
	class Medic : public Player
	{
	public:
		Medic(Board, City);
		~Medic();
	};
}