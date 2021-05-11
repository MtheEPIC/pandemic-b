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
	Player::~Player()
	{
		
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
	bool Player::has_research_station(City city)
	{
		return std::find(this->research_stations.begin(), this->research_stations.end(), curr_city) != this->research_stations.end();
	}
	bool Player::has_card(City card)
	{
		return std::find(this->cards.begin(), this->cards.end(), card) != this->cards.end();
	}
	void Player::remove_card(City card)
	{
		auto it = std::find(this->cards.begin(), this->cards.end(), card);
		this->cards.erase(it);
		// this->cards.erase(card);
	}
	bool Player::is_neighbour_city(City dest_city)
	{
		return std::find(this->paths[this->curr_city].begin(), this->paths[this->curr_city].end(), dest_city) != this->paths[this->curr_city].end();
	}
	Player& Player::take_card(City card)
	{
		auto it = std::find(this->cards.begin(), this->cards.end(), card);
		if (it == this->cards.end())
		{
			this->cards.push_back(card);
		}
		// auto it = this->cards.find(card);
		// if (it == this->cards.end())
		// {
			// this->cards.insert({card, true});
		// }
		return *this;
	}
	Player& Player::remove_cards()
	{
		this->cards.clear();
		return *this;
	}
	Player& Player::treat(City city)
	{
		if(this->get_pandemic_levels()[city] == 0)
		{
			throw std::logic_error("cant treat a city if there is no disease");
		}
		if(this->curr_city != city)
		{
			throw std::logic_error("can't treat a disease in a city you're not in");
		}
		if (this->cures.contains(this->card_colors[city]))
		{
			this->set_pandemic_levels(city, 0);
		}
		else
		{
			this->set_pandemic_levels(city, -1);
		}
		return *this;
	}
	Player& Player::drive(City dest_city)
	{
		if (this->curr_city == dest_city)
		{
			throw std::logic_error("cant drive to a city you're in");
		}
		if (!this->is_neighbour_city(dest_city))
		{
			throw std::logic_error("the destination city doesn't neighbour the current city");
		}
		this->curr_city = dest_city;
		return *this;
	}
	Player& Player::fly_charter(City dest_city)
	{
		if (this->curr_city == dest_city)
		{
			throw std::logic_error("cant fly to a city you're in");
		}
		if (this->has_card(this->curr_city))
		{
			throw std::logic_error("cant fly to a city without the card of the current city");
		}
		this->remove_card(curr_city);
		this->curr_city = dest_city;
		return *this;
	}
	Player& Player::fly_direct(City dest_city)
	{
		if (this->curr_city == dest_city)
		{
			throw std::logic_error("cant fly to a city you're in");
		}
		if (this->has_card(dest_city))
		{
			throw std::logic_error("cant fly to a city without the card of the destination city");
		}
		this->remove_card(dest_city);
		this->curr_city = dest_city;
		return *this;
	}
	Player& Player::fly_shuttle(City dest_city) //add for dispatcher	
	{
		if (this->curr_city == dest_city)
		{
			throw std::logic_error("cant fly to a city you're in");
		}
		if (!this->has_research_station(dest_city))
		{
			throw std::logic_error("cant shuttle fly without a research station");
		}
		this->curr_city = dest_city;
		return *this;
	}
	Player& Player::build() //OperationsExpert
	{
		if (this->has_research_station(this->curr_city))
		{
			return *this;
		}
		if (this->role() != "OperationsExpert" && !this->has_card(this->curr_city))
		{
			throw std::logic_error("cant build without a city card");
		}
		this->research_stations.push_back(this->curr_city);
		return *this;
	}
	Player& Player::discover_cure(Color)
	{
		if (!this->has_research_station(curr_city))
		{
			throw std::logic_error("must be in a research station to discover a cure");
		}
		if (this->cards.size() == this->cards_for_cure)
		{
			throw std::logic_error("not enough card to discover a cure");
		}
		Color pandemic_color = this->card_colors[curr_city];
		int counter = 0;
		// for (auto i = this->cards.begin(); i != this->cards.end(); i++)
		// {
			// if (this->card_colors.[i] == pandemic_color)
			// {
				// counter++;
			// }
		// }
		if (counter < this->cards_for_cure)
		{
			throw std::logic_error("not enough cards of the right color to discover a cure");
		}
		return *this;
	}
	std::string Player::role()
	{
		return "";
	}
}