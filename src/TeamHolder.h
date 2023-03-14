#ifndef TEAM_HOLDER_H
#define TEMAM_HOLDER_H

#include "Person.h"

#include <unordered_map>
#include <vector>

class TeamHolder
{
protected:
	std::unordered_map<std::string, std::vector<Person>> _teams;
	std::unordered_map<std::string, double> _prob_modifiers;
	size_t _total_players_count;

public:

	TeamHolder();

	~TeamHolder();

	void addPlayer(std::string const& team, Person const& p);

	const std::unordered_map<std::string, std::vector<Person>>& team_list() const;

	void calculateFairProbModifier();

	double fairProbModifier(std::string const& team);

	void serialize(std::ostream& out);

	void loadProbs(std::istream& in);
};
#endif

