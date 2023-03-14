#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <cmath>
#include <algorithm>

#include "Person.h"
class Probability
{
public:
	//All probabilities will be calculated regarding PROB_UPPER_BOUND as probability = 1
	//Upper bound
	static const int PROB_UPPER_BOUND = 1000;
	//Infection
	static const int INFECTION_BY_CONTACT_PROB = 750;
	static const int DOCTOR_VACCINE_PROB = 5;
	static const int DOCTOR_CURE_PROB = 10;
	static const int INFECTION_NATURAL_PROB = 100;
	static const int VACCINE_STARTING_PROB = 50;
	static const int GETTING_VACCINATED_PROB = 200;
	static const int INFECTION_DMG = 200;
	static const int INFECTION_BY_DAY_DMG = 20;

	/// Probability of curing the player by himself.
	/// Depends on number of doctors alive
	static bool naturallyCurePlayer(Person const& p, int _n_doctors);

	/// Probability of getting infected each turn
	/// Depends on the number of people infected, alive, doctors alive and vulerable 
	static bool naturallyInfect(int _n_infected, int _n_alive, int _n_doctors, int _n_vulnerable);

	/// Probability of getting eliminated because of the infection, provided p is infected
	/// Depends on number of doctors and days infected
	static bool eliminateFromInfection(Person const& p, double team_bonus, int _n_doctors);

	/// Probability of finding a vaccine
	/// Depends on number of doctors
	static bool findCure(int _n_doctors);

	/// Probability of getting vaccinated
	/// Depends on infected alive ratio
	static bool vaccinatePlayer(int _n_alive, int _n__infected);

	/// Returns true if p1 wins to p2 in a duel
	/// Depends on number of kills of each Persona and their Profession
	static bool firstWins(Person & p1, double team_bonus_1, Person & p2, double team_bonus_2);

	/// Probability of fleeing from a duel
	/// Only depends on the actual prtobability defined above
	static bool fleeProb();

	/// Probability of getting infected after duel
	/// The function assumes Person infectd is infected and subject is the one to be infected
	/// Depends on plain defined probability above
	static bool infectPlayer(Person const& infected, Person const& subject);

	/// an addiotional function is implemented in .cpp regarding Profession damage in the duel





};

#endif

