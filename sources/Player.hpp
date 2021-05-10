#pragma once
#include <string>
#include <vector>
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#define CARDS_FOR_CURE 5

namespace pandemic {
	class Player : public Board
	{
	public:
		Board* game_board;
		City curr_city;
		std::vector<City> cards;
		int cards_for_cure;
		Player(Board&, City);
		Player(Board&, City, int);
		M get_pandemic_levels();
		void set_pandemic_levels(City city, int level);
		~Player();
		Player take_card(City);
		Player drive(City);
		Player fly_direct(City);
		Player treat(City);
		Player fly_charter(City);
		Player build();
		Player fly_shuttle(City);
		Player discover_cure(Color);
		std::string role();
	};
}