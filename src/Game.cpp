#include "Game.h"
#include <assert.h>
Game::Game() : _time(-1)
{
}

Game::~Game()
{
}

std::queue<Event> Game::loadNew(std::istream & _in)
{
	_players.reset();
	_players.resetEvents();
	_players.loadNew(_in);
	_time = 0;
	return _players.turnEvents();
}

std::queue<Event> Game::loadSave(std::istream & in)
{
	_players.reset();
	_players.resetEvents();
	in >> _time;
	in.get();
	_players.loadSave(in);
	return _players.turnEvents();
}

std::queue<Event> Game::run(int _ticks)
{
	if (_time < 0) throw std::domain_error("No hay partida cargada");
	_players.resetEvents();
	int i = 0;
	while(i < _ticks && !finished()) {
		++_time;
		_players.findVaccine(_time);
		_players.curePlayers(_time);
		_players.vaccinatePlayers(_time);
		_players.checkInfections(_time);
		_players.simulate(_time);
		++i;
	}
	
	return _players.turnEvents();
}

bool Game::finished() const
{
	return _players.finished();
}

Event Game::winner() const
{
	return { Event::Type::_WINNER, _time, _players.winner() };
}

int Game::remaining() const
{
	return _players.remaining();
}

std::pair<std::vector<Person::Score>, std::vector<Person::Score>> Game::clasification() const
{
	return std::pair<std::vector<Person::Score>, std::vector<Person::Score>>(_players.aliveScore(), _players.eliminatedScore());
}

std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>> Game::profession()
{
	return _players.profession();
}

const std::unordered_map<std::string, std::vector<Person>>& Game::team_list() const
{
	return _players.team_list();
}

void Game::serialize(std::ostream & output)
{
	output << _time << '\n';
	_players.serialize(output);
}

std::string Game::gameName()
{
	return _game_name;
}

void Game::setName(std::string name)
{
	_game_name = name;
}
