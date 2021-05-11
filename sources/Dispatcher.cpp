#include "Dispatcher.hpp"

namespace pandemic {
	Dispatcher::Dispatcher(Board& game_board, City init_city) : Player(game_board, init_city)
	{
		
	}
	Dispatcher::~Dispatcher()
	{
		
	}
	Player& Dispatcher::fly_direct(City dest_city)
	{
		if (this->curr_city == dest_city)
		{
			throw std::logic_error("cant fly to a city you're in");
		}
		if (this->has_research_station(curr_city))
		{
			this->curr_city = dest_city;
			return *this;
		}
		if (this->has_card(dest_city))
		{
			throw std::logic_error("cant fly to a city without the card of the destination city");
		}
		this->remove_card(dest_city);
		this->curr_city = dest_city;
		return *this;
	}
	std::string Dispatcher::role()
	{
		return "Dispatcher";
	}
}