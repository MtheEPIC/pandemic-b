#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "OperationsExpert.hpp"
#include "Virologist.hpp"
#include "FieldDoctor.hpp"
#include "Medic.hpp"
#include "Scientist.hpp"
#include "GeneSplicer.hpp"
#include "Researcher.hpp"

#include "Dispatcher.hpp"

using namespace pandemic;
using namespace std;

void create_research_station(Board game_board, City city)
{
	OperationsExpert player {game_board, city};
	player.build();
}

void create_cure(Board game_board)
{
	Researcher player {game_board, City::Atlanta};
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	player.discover_cure(Color::Blue);
}

TEST_CASE("is_clean")
{
	Board game_board;
	CHECK_EQ(game_board.is_clean(), true);
	
	game_board[City::HongKong] = 1;
	CHECK_EQ(game_board.is_clean(), false);
	
	game_board[City::HongKong] = 0;
	CHECK_EQ(game_board.is_clean(), true);
	
	game_board[City::HongKong] = 1;
	game_board[City::Atlanta] = 1;
	game_board[City::HongKong] = 0;
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("player-drive")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	
	// drive to the same city
	CHECK_THROWS(player.drive(City::Atlanta));
	// drive to the near city
	CHECK_NOTHROW(player.drive(City::Chicago));
	// drive to the far city
	CHECK_THROWS(player.drive(City::HongKong));
}

TEST_CASE("player-fly_direct")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	
	// fly with no card
	CHECK_THROWS(player.fly_direct(City::HongKong));
	// fly to same city
	player.take_card(City::Atlanta);
	CHECK_THROWS(player.fly_direct(City::Atlanta));
	// fly with card
	player.take_card(City::HongKong);
	CHECK_NOTHROW(player.fly_direct(City::HongKong));
}

TEST_CASE("Dispatcher-fly_direct")
{
	Board game_board;
	Dispatcher player {game_board, City::Atlanta};
	
	// fly with no card
	CHECK_THROWS(player.fly_direct(City::HongKong));
	// fly to same city
	player.take_card(City::Atlanta);
	CHECK_THROWS(player.fly_direct(City::Atlanta));
	// fly with card
	player.take_card(City::HongKong);
	CHECK_NOTHROW(player.fly_direct(City::HongKong));
	// fly as Dispatcher
	create_research_station(game_board, City::HongKong);
	CHECK_NOTHROW(player.fly_direct(City::Paris));
}

TEST_CASE("player-fly_charter")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	
	// fly with no card
	CHECK_THROWS(player.fly_charter(City::HongKong));
	// fly to same city
	player.take_card(City::Atlanta);
	CHECK_THROWS(player.fly_charter(City::Atlanta));
	// fly with card
	CHECK_NOTHROW(player.fly_charter(City::HongKong));
	// fly with spent card
	CHECK_THROWS(player.fly_charter(City::Paris));
}

TEST_CASE("player-fly_shuttle")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	
	// fly with no station
	CHECK_THROWS(player.fly_shuttle(City::HongKong));
	// fly to same city
	create_research_station(game_board, City::Atlanta);
	CHECK_THROWS(player.fly_shuttle(City::Atlanta));
	CHECK_THROWS(player.fly_shuttle(City::HongKong));
	// fly with no destination station
	// fly as with 2 stations
	create_research_station(game_board, City::HongKong);
	CHECK_NOTHROW(player.fly_shuttle(City::HongKong));
}

TEST_CASE("player-treat")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	CHECK_EQ(game_board.is_clean(), true);
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're not it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("Virologist-treat")
{
	Board game_board;
	Virologist player {game_board, City::Atlanta};
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're not in
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), true);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("FieldDoctor-treat")
{
	Board game_board;
	FieldDoctor player {game_board, City::Atlanta};
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're not in
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("player-build")
{
	Board game_board;
	Virologist player {game_board, City::Atlanta};
	
	// build with no cards
	CHECK_THROWS(player.build());
	// build with wrong card
	player.take_card(City::Chicago);
	CHECK_THROWS(player.build());
	// build with right card
	player.take_card(City::Atlanta);
	CHECK_NOTHROW(player.build());
	// check card amount
	CHECK_EQ(player.cards.size(), 1);
	// try to build again
	player.take_card(City::Atlanta);
	CHECK_NOTHROW(player.build());
	CHECK_EQ(player.cards.size(), 2);
}

TEST_CASE("OperationsExpert-build")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	
	// build with no cards
	CHECK_NOTHROW(player.build());
	// build with wrong card
	player.take_card(City::Chicago);
	CHECK_NOTHROW(player.build());
	// build with right card
	player.take_card(City::Atlanta);
	CHECK_NOTHROW(player.build());
	// check card amount
	CHECK_EQ(player.cards.size(), 2);
}

TEST_CASE("Medic-treat")
{
	Board game_board;
	Medic player {game_board, City::Atlanta};
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're not in
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("player-discover_cure")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	create_research_station(game_board, City::Atlanta);
	
	// try to discover a cure with 4 cards
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of different colors
	player.take_card(City::HongKong);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of the same color
	player.take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	// check if player gave the cards back
	CHECK_EQ(player.cards.size(), 1);
	// try to discover a cure twice
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	CHECK_EQ(player.cards.size(), 6);
	// try to create a cure with no station
	player.drive(City::Miami);
	player.take_card(City::Miami).take_card(City::MexicoCity).take_card(City::LosAngeles).take_card(City::Lima).take_card(City::Bogota);
	CHECK_THROWS(player.discover_cure(Color::Yellow));
}

TEST_CASE("Scientist-discover_cure")
{
	Board game_board;
	Scientist player {game_board, City::Atlanta, 4};
	
	// try to discover a cure with 3 cards
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 4 cards of different colors
	player.take_card(City::HongKong);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 4 cards of the same color
	player.take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	// check if player gave the cards back
	CHECK_EQ(player.cards.size(), 1);
	// try to discover a cure twice
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	CHECK_EQ(player.cards.size(), 5);
	// try to create a cure with no station
	player.drive(City::Miami);
	player.take_card(City::Miami).take_card(City::MexicoCity).take_card(City::LosAngeles).take_card(City::Lima).take_card(City::Bogota);
	CHECK_THROWS(player.discover_cure(Color::Yellow));
}

TEST_CASE("GeneSplicer-discover_cure")
{
	Board game_board;
	GeneSplicer player {game_board, City::Atlanta}; //add Researcher station
	
	// try to discover a cure with 4 cards
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of different colors
	player.take_card(City::HongKong);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	// check if player gave the cards back
	CHECK_EQ(player.cards.size(), 0);
	// try to discover a cure twice
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	CHECK_EQ(player.cards.size(), 5);
	// try to create a cure with no station
	player.drive(City::Miami);
	player.take_card(City::Miami).take_card(City::MexicoCity).take_card(City::LosAngeles).take_card(City::Lima).take_card(City::Bogota);
	CHECK_THROWS(player.discover_cure(Color::Yellow));
}

TEST_CASE("Researcher-discover_cure")
{
	Board game_board;
	Researcher player {game_board, City::Atlanta};
	
	// try to discover a cure with 4 cards
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of different colors
	player.take_card(City::HongKong);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of the same color
	player.take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	// check if player gave the cards back
	CHECK_EQ(player.cards.size(), 1);
	// try to discover a cure twice
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	CHECK_EQ(player.cards.size(), 6);
	// try to create a cure with no station
	player.drive(City::Miami);
	player.take_card(City::Miami).take_card(City::MexicoCity).take_card(City::LosAngeles).take_card(City::Lima).take_card(City::Bogota);
	CHECK_NOTHROW(player.discover_cure(Color::Yellow));
}

TEST_CASE("player-treat-cure")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	create_research_station(game_board, City::Atlanta);
	create_cure(game_board);
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
}

TEST_CASE("Medic-treat-cure")
{
	Board game_board;
	Medic player {game_board, City::Atlanta};
	create_research_station(game_board, City::Atlanta);
	create_cure(game_board);
	
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), true);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	CHECK_THROWS(player.treat());
}