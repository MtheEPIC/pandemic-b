#pragma once
#include "Player.hpp"

namespace pandemic {
	class Medic : public Player
	{
	public:
		Medic(Board& game_board, City init_city);
		~Medic();
		static std::string role();
	};
}