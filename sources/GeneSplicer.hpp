#pragma once
#include "Player.hpp"

namespace pandemic {
	class GeneSplicer : public Player
	{
	public:
		GeneSplicer(Board& game_board, City init_city);
		~GeneSplicer();
		Player& discover_cure(Color);
		static std::string role();
	};
}