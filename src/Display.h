#ifndef DISPLAY_H
#define DISPLAY_H
//#define DEBUG

#include <vector>
#include <queue>

#include "Person.h"
#include "Event.h"

class Display
{
private:
	static const int WIDTH = 100;
	static const int MARGIN = 10;
	static std::string MG;
public:
	Display();
	~Display();

	//Exit Command
	void byeBye();

	//showRanking
	void showRanking(std::pair<std::vector<Person::Score>, std::vector<Person::Score>> scores);

	//ShowProefssions
	void showProfesisons(std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>>& professions, std::string gameName);

	//HelpCommand
	void showHelp(std::vector<std::string> help);

	//Show simulation messages
	void showGame(std::queue<Event> & events, std::string gameName);

	//Winner message
	void showWinner(Event & winnerMessage, std::string gameName);

	//ShowError
	void showError(std::string error);

private:
	void showDuel(Event const& e);
	void showPizzaFlee(Event const& e);
	void showInfectedOnDuel(Event const& e);
	void showFindVaccine(Event const& e);
	void showStealVaccine(Event const& e);
	void showGetVaccinated(Event const& e);
	void showGetCured(Event const& e);
	void showNaturalInfection(Event const& e);
	void showNewPlayer(Event const& e);
	void showInfectionElimination(Event const& e);

	//Centres str in the given width
	std::string helpCentre(int width, const std::string& str);
	std::string helpCentre(int width, const int number);
	//Returns a line for  making the Ranking
	std::string hLine();

};
#endif
