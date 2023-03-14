#include "TeamHolder.h"

#include <iostream>
#include <iomanip>

TeamHolder::TeamHolder() : 
	_total_players_count(0)
{
}

TeamHolder::~TeamHolder()
{
	_teams.clear();
	_prob_modifiers.clear();
}

void TeamHolder::addPlayer(std::string const& team, Person const& p)
{
	_teams[team].push_back(p);
	_prob_modifiers[team] = 0;
	++_total_players_count;
}

const std::unordered_map<std::string, std::vector<Person>>& TeamHolder::team_list() const
{
	return _teams;
}

void TeamHolder::calculateFairProbModifier()
{
	/**
	 * Let n be the total number of players
	 * Suppose each player has a 1/n probability of winning.
	 * Then each team has a (team size)/n probability of winning, as the events
	 * of a players winning is disjoint from the rest.
	 * To make every probability equal all we need to do is multiply the team's chance
	 * so it is 1/(number of teams) and consiquently each players initial probability
	 * will be multiplied by this factor.
	 */
	for (auto it = _teams.begin(); it != _teams.end(); ++it) {
		_prob_modifiers[it->first] = (double)_total_players_count / (it->second.size()*_teams.size());
	}
}

double TeamHolder::fairProbModifier(std::string const& team)
{
	return _prob_modifiers[team];
}

void TeamHolder::serialize(std::ostream& out)
{
	out << (unsigned long)_prob_modifiers.size() << '\n';

	for (auto it = _prob_modifiers.begin(); it != _prob_modifiers.end(); ++it) {
		out << it->first << '\n';
		out << std::setprecision(10) << it->second << '\n';
	}
}

void TeamHolder::loadProbs(std::istream& in)
{
	size_t n;
	in >> n;
	std::string team;
	double prob;
	for (size_t i = 0; i < n; ++i) {
		std::getline(in, team);
		in >> prob;
		_prob_modifiers[team] = prob;
	}
}
