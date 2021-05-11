#pragma once
#include "Player.hpp"

namespace pandemic {
	class Researcher : public Player
	{
	public:
		Researcher(Board& game_board, City init_city);
		~Researcher();
		Player& discover_cure(Color);
		static std::string role();
	};
}