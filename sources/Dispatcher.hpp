#pragma once
#include "Player.hpp"

namespace pandemic {
	class Dispatcher : public Player
	{
	public:
		Dispatcher(Board& game_board, City init_city);
		~Dispatcher();
		Player& fly_direct(City dest_city);
		static std::string role();
	};
}