#pragma once
#include <string>
#include <vector>
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

namespace pandemic {
	class Player
	{
	public:
		std::vector<City> cards;
		Player(Board&, City);
		Player(Board&, City, int);
		~Player();
		Player take_card(City);
		Player drive(City);
		Player fly_direct(City);
		Player treat();
		Player treat(City); // for Virologist
		Player fly_charter(City);
		Player build();
		Player fly_shuttle(City);
		Player discover_cure(Color);
		std::string role();
	};
}