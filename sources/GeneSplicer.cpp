#include "GeneSplicer.hpp"

namespace pandemic {
	GeneSplicer::GeneSplicer(Board& game_board, City init_city) : Player(game_board, init_city)
	{
		
	}
	GeneSplicer::~GeneSplicer()
	{
		
	}
	Player& GeneSplicer::discover_cure(Color pandemic_color)
	{
		if (this->cures.contains(pandemic_color))
		{
			return *this;
		}
		if (!this->has_research_station(curr_city))
		{
			throw std::logic_error("must be in a research station to discover a cure");
		}
		if (this->cards.size() < this->cards_for_cure)
		{
			throw std::logic_error("not enough card to discover a cure");
		}
		int counter = 0;
		this->cures.insert(pandemic_color);
		// remove cards
		counter = 0;
		for (auto i = this->cards.begin(); i != this->cards.end(); i++)
		{
			if (this->card_colors[*i] == pandemic_color)
			{
				counter++;
				this->remove_card(*i);
				if (counter == this->cards_for_cure)
				{
					break;
				}
			}
		}
		return *this;
	}
	std::string GeneSplicer::role()
	{
		return "GeneSplicer";
	}
}