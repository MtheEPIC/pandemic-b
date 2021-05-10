#include <string>
#include "Player.hpp"

namespace pandemic {
	Player::Player(Board& game_board, City init_city) //: Board(game_board)
	{
		this->game_board = &game_board;
		this->curr_city = init_city;
		this->cards_for_cure = CARDS_FOR_CURE;
	}
	Player::Player(Board& game_board, City init_city, int discover_cure_cards)// : Board(game_board)
	{
		this->game_board = &game_board;
		this->curr_city = init_city;
		this->cards_for_cure = discover_cure_cards;
	}
	M Player::get_pandemic_levels()
	{
		return this->game_board->cities_pandemic_level;
	}
	void Player::set_pandemic_levels(City city, int level)
	{
		if (level == -1)
		{
			this->game_board->cities_pandemic_level[city]--;
			return;
		}
		this->game_board->cities_pandemic_level[city] = level;
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
	Player Player::treat(City city)
	{
		if(this->get_pandemic_levels()[city] == 0)
		{
			throw std::logic_error("cant treat a city if there is no disease");
		}
		if(this->curr_city != city)
		{
			if(this->role() != "FieldDoctor")
			{
				auto it = std::find(this->cards.begin(), this->cards.end(), city);
				if (it == this->cards.end())
				{
					throw std::logic_error("only FieldDoctor can treat a disease in a city his not in without having the proper card");	
				}
				this->cards.erase(it);
			}
		}
		// check if cure exists
		// -------------
		this->set_pandemic_levels(city, -1);
		
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
		if(this->cards.size() == this->cards_for_cure)
		{
			throw std::logic_error("not enough card to discover a cure");
		}
		return *this;
	}
	std::string Player::role()
	{
		return "";
	}
}