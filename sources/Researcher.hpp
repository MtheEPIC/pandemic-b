#pragma once
#include "Player.hpp"

namespace pandemic {
	class Researcher : public Player
	{
	public:
		Researcher(Board& game_board, City init_city);
		~Researcher();
		static std::string role();
	};
}