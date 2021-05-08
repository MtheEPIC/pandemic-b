#include <string>
#include "Player.hpp"

namespace pandemic {
	Player::Player(Board &game_board, City init_city)
	{
		
	}
	Player::Player(Board &game_board, City init_city, int discover_cure_cards)
	{
		
	}
	Player::~Player()
	{
		
	}
	Player Player::take_card(City)
	{
		return *this;
	}
	Player Player::drive(City)
	{
		return *this;
	}
	Player Player::fly_direct(City)
	{
		return *this;
	}
	Player Player::treat()
	{
		return *this;
	}
	Player Player::treat(City)
	{
		return *this;
	}
	Player Player::fly_charter(City)
	{
		return *this;
	}
	Player Player::build()
	{
		return *this;
	}
	Player Player::fly_shuttle(City)
	{
		return *this;
	}
	Player Player::discover_cure(Color)
	{
		return *this;
	}
	std::string Player::role()
	{
		return "";
	}
}