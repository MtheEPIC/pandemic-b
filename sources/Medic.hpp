#pragma once
#include "Player.hpp"

namespace pandemic {
	class Medic : public Player
	{
	protected:
		void auto_cure(City);
	public:
		Medic(Board& game_board, City init_city);
		~Medic();
		Player& treat(City);
		Player& drive(City);
		Player& fly_direct(City);
		Player& fly_charter(City);
		Player& fly_shuttle(City);
		static std::string role();
	};
}