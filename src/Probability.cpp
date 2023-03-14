#include "Probability.h"
#include "TeamHolder.h"
//TODO: revisar
bool Probability::naturallyCurePlayer(Person const& p, int _n_doctors)
{
	return rand() % PROB_UPPER_BOUND < 10 * sqrt(p.days_infected()) + _n_doctors * DOCTOR_CURE_PROB;
}

// TODO: revisar esta probabilidad
bool Probability::naturallyInfect(int _n_infected, int _n_alive, int _n_doctors, int _n_vulnerable)
{
	int border = rand() % PROB_UPPER_BOUND;
	return border < std::max((_n_infected - _n_doctors), _n_vulnerable) / _n_alive * INFECTION_NATURAL_PROB;
}

bool Probability::eliminateFromInfection(Person const& p, double team_bonus, int _n_doctors)
{
	return (rand() % PROB_UPPER_BOUND) < (INFECTION_DMG - _n_doctors * DOCTOR_CURE_PROB + 2 * sqrt(p.days_infected()) * INFECTION_BY_DAY_DMG) * team_bonus;
}

bool Probability::findCure(int _n_doctors)
{
	return rand() % PROB_UPPER_BOUND < VACCINE_STARTING_PROB + _n_doctors * DOCTOR_VACCINE_PROB;
}

bool Probability::vaccinatePlayer(int _n_alive, int _n_infected)
{
	return rand() % PROB_UPPER_BOUND < GETTING_VACCINATED_PROB* _n_infected / _n_alive;
}


int professionDuelMod(Profession const& prof1, Profession const& prof2)
{
	//POLICE
	if (prof1 == Profession::POLICE
		&&
		(prof2 == Profession::NERD
			||
			prof2 == Profession::ROBBER
			||
			prof2 == Profession::BULLY))

		return Profession::POLICE_DMG;

	if (prof2 == Profession::POLICE
		&&
		(prof1 == Profession::NERD
			||
			prof1 == Profession::ROBBER
			||
			prof1 == Profession::BULLY))

		return -1 * Profession::POLICE_DMG;

	//BULLY
	if (prof1 == Profession::BULLY && prof2 == Profession::NERD)
		return Profession::BULLY_DMG;
	if (prof2 == Profession::BULLY && prof1 == Profession::NERD)
		return -1 * Profession::BULLY_DMG;

	//FIGHTERS
	if (prof1 == Profession::FIGHTER)
		return Profession::FIGHTER_DMG;
	if (prof2 == Profession::FIGHTER)
		return -1 * Profession::FIGHTER_DMG;

	//PERUANO
	if (prof1 == Profession::PERUANO)
		return Profession::PERUANO_DMG;
	if (prof2 == Profession::PERUANO)
		return -1 * Profession::PERUANO_DMG;
	return 0;
}

bool Probability::firstWins(Person& p1, double team_bonus_1, Person& p2, double team_bonus_2)
{
	bool result;
	int diff = p1.kills() - p2.kills();
	//border determination
	// the higher the border that higher the chance of player 1 of winning
	int border = ((PROB_UPPER_BOUND / 2) + (PROB_UPPER_BOUND / 5) *
		atan(diff / 10.0) + professionDuelMod(p1.profession(), p2.profession()))
		* (team_bonus_1 / team_bonus_2);
	//Winner choosing
	if (p1.profession() == Profession::POLITICIAN
		xor
		p2.profession() == Profession::POLITICIAN)
	{
		result = p1.profession() != Profession::POLITICIAN;
	}
	else {
		result = border > rand() % PROB_UPPER_BOUND;
	}
	return result;
}

bool Probability::fleeProb()
{
	return rand() % PROB_UPPER_BOUND < Profession::FLEE_PROB;
}

bool Probability::infectPlayer(Person const& infected, Person const& subject)
{
	if (!subject.infected() && !subject.immune()) {
		if (infected.profession() == Profession::JUNKIE)
			return true;
		else if (infected.infected()) {
			int border = rand() % PROB_UPPER_BOUND;
			return border < INFECTION_BY_CONTACT_PROB;
		}
	}
	return false;
}
