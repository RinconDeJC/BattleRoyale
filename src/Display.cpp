#include "Display.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#define AT_LINUX
//#define DEBUG
using namespace std;

string Display::MG = string(Display::MARGIN, ' ');

Display::Display()
{
}


Display::~Display()
{
}

void Display::byeBye()
{
#ifndef DEBUG
#ifdef AT_LINUX
	system("clear");
#else
	system("cls");
#endif
	cout << "\n\n";
	cout << helpCentre(Display::WIDTH, "Agradecimientos") << '\n';
	cout << "\n\n";
	cin.get();
	cout << helpCentre(Display::WIDTH, "Por escoger los nombres") << '\n' << '\n';
	cin.get();
	cout << helpCentre(Display::WIDTH, "Miguel Manzana") << '\n';
	cin.get();
	cout << helpCentre(Display::WIDTH, "Jorge Mapache") << '\n';
	cin.get();
	cout << helpCentre(Display::WIDTH, "Pizzero45") << '\n';
	cin.get();
	cout << helpCentre(Display::WIDTH, "Meri el calvo Imitador") << '\n';
	cin.get();
	cout << "\n\n";
	cout << helpCentre(Display::WIDTH, "Por desarrollar la app") << '\n' << '\n';
	cin.get();
	cout << helpCentre(Display::WIDTH, "SirJC") << '\n';
	cin.get();
	cout << "\n\n";
	cout << helpCentre(Display::WIDTH, "Y a ti");
	cin.get();
	cout << helpCentre(Display::WIDTH, "por jugar :)");
	cout << "\n";
#endif
}

void Display::showRanking(std::pair<std::vector<Person::Score>, std::vector<Person::Score>> scores)
{
#ifndef DEBUG
#ifdef AT_LINUX
	system("clear");
#else
	system("cls");
#endif
#endif
	cout << "\n\n";
	//Header
	cout << hLine() << '\n';
	cout << Display::MG << '|' << helpCentre(98, "VIVOS: " + to_string(scores.first.size())) << '|' << '\n';
	cout << hLine() << '\n';
	//Legend
	cout << Display::MG << '|' << helpCentre(26, "NOMBRE") << '|' << helpCentre(10, "PROFESION") << '|' <<
		helpCentre(3, "#K") << '|' << helpCentre(20, "KILLS") << '|'
		<< helpCentre(20, "ELIMINADOS POR") << '|' << helpCentre(4, "#S") << '|' << helpCentre(4, "#I") << '|'
		<< helpCentre(4, "#PI") << '|' << '\n';
	cout << hLine() << '\n';
	for (Person::Score s : scores.first) {
		cout << Display::MG << '|' << helpCentre(26, s._name) << '|' << helpCentre(10, s._prof) << '|' <<
			helpCentre(3, s._kills.size()) << '|' << (s._kills.empty() ? helpCentre(20, " ") : helpCentre(20, s._kills[0])) << '|'
			<< helpCentre(20, "?") << '|' << helpCentre(4, "?") << '|' << helpCentre(4, s._n_days_infected) << '|'
			<< helpCentre(4, s._n_people_infected) << '|' << '\n';
		for (int i = 1; i < s._kills.size(); ++i) {
			cout << Display::MG << '|' << helpCentre(26, " ") << '|' << helpCentre(10, " ") << '|' <<
				helpCentre(3, " ") << '|' << helpCentre(20, s._kills[i]) << '|'
				<< helpCentre(20, " ") << '|' << helpCentre(4, " ") << '|' << helpCentre(4, " ") << '|'
				<< helpCentre(4, " ") << '|' << '\n';
		}
		cout << hLine() << '\n';
	}
	cout << '\n';
	//Header
	cout << hLine() << '\n';
	cout << Display::MG << '|' << helpCentre(98, "ELIMINADOS: " + to_string(scores.second.size())) << '|' << '\n';
	cout << hLine() << '\n';
	//Legend
	cout << Display::MG << '|' << helpCentre(26, "NOMBRE") << '|' << helpCentre(10, "PROFESION") << '|' <<
		helpCentre(3, "#K") << '|' << helpCentre(20, "KILLS") << '|'
		<< helpCentre(20, "ELIMINADOS POR") << '|' << helpCentre(4, "#S") << '|' << helpCentre(4, "#I") << '|'
		<< helpCentre(4, "#PI") << '|' << '\n';
	cout << hLine() << '\n';
	for (Person::Score s : scores.second) {
		cout << Display::MG << '|' << helpCentre(26, s._name) << '|' << helpCentre(10, s._prof) << '|' <<
			helpCentre(3, s._kills.size()) << '|' << (s._kills.empty() ? helpCentre(20, " ") : helpCentre(20, s._kills[0])) << '|'
			<< helpCentre(20, s._killed_by) << '|' << helpCentre(4, s._n_days_survived) << '|' << helpCentre(4, s._n_days_infected) << '|'
			<< helpCentre(4, s._n_people_infected) << '|' << '\n';
		for (int i = 1; i < s._kills.size(); ++i) {
			cout << Display::MG << '|' << helpCentre(26, " ") << '|' << helpCentre(10, " ") << '|' <<
				helpCentre(3, " ") << '|' << helpCentre(20, s._kills[i]) << '|'
				<< helpCentre(20, " ") << '|' << helpCentre(4, " ") << '|' << helpCentre(4, " ") << '|'
				<< helpCentre(4, " ") << '|' << '\n';
		}
		cout << hLine() << '\n';
	}
	cout << "\n\n";
}

void Display::showProfesisons(std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>> & professions, std::string gameName)
{
#ifndef DEBUG
#ifdef AT_LINUX
	system("clear");
#else
	system("cls");
#endif
	ofstream out(gameName + "_professions" + ".txt");
	auto coutbuf = cout.rdbuf(out.rdbuf());

#endif
	cout << "RESUMEN DE LAS PROFESIONES DE LOS JUGADORES INICIALES.\n\n";
	cout << "Nombre del juego: " << gameName << '\n' << '\n';
	for (auto _pair = professions.begin(); _pair != professions.end(); ++_pair) {
		cout << _pair->first.getStringVal() << '\n' << '\n';
		for (auto it = _pair->second.begin(); it != _pair->second.end(); ++it) {
			cout << Display::MG << it->first << '\n';
		}
		cout << '\n' << '\n';
	}
#ifndef DEBUG
	out.close();
	cout.rdbuf(coutbuf);
#endif

}

void Display::showHelp(std::vector<std::string> help)
{
#ifndef DEBUG
#ifdef AT_LINUX
	system("clear");
#else
	system("cls");
#endif
#endif
	cout << "\n\n";
	for (std::string h : help) {
		cout << Display::MG << h << '\n';
	}
	cout << "\n\n";
}

void Display::showGame(std::queue<Event> & events, std::string gameName)
{

#ifndef DEBUG
#ifdef AT_LINUX
	system("clear");
#else
	system("cls");
#endif
	if (events.empty()) return;
	int time = events.front().time();
	ofstream out(gameName + "_" + to_string(time) + ".txt");
	auto coutbuf = cout.rdbuf(out.rdbuf());
	
#endif
	cout << "\n\n";
#ifdef DEBUG

#endif
	while (!events.empty()) {
#ifndef DEBUG
		if (time != events.front().time()) {
			time = events.front().time();
			out.close();
			out.open(gameName + "_" + to_string(time) + ".txt");
			cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
		}

#endif
		switch (events.front().type()) {
		case Event::Type::_DUEL :{
			showDuel(events.front());
			break;
		}
		case Event::Type::_PIZZA_FLEE: {
			showPizzaFlee(events.front());
			break;
		}
		case Event::Type::_INFECTED_ON_DUEL: {
			showInfectedOnDuel(events.front());
			break;
		}
		case Event::Type::_FIND_VACCINE: {
			showFindVaccine(events.front());
			break;
		}
		case Event::Type::_STEAL_VACCINE: {
			showStealVaccine(events.front());
			break;
		}
		case Event::Type::_GET_VACCINATED: {
			showGetVaccinated(events.front());
			break;
		}
		case Event::Type::_GET_CURED: {
			showGetCured(events.front());
			break;
		}
		case Event::Type::_NATURAL_INFECTION: {
			showNaturalInfection(events.front());
			break;
		}
		case Event::Type::_NEW_PLAYER: {
			showNewPlayer(events.front());
			break;
		}
		case Event::Type::_INFECTION_ELIMINATION: {
			showInfectionElimination(events.front());
			break;
		}
		default: {
			cout << "Evento sin soporte\n";
		}

		}
		events.pop();
	}
#ifndef DEBUG
	out.close();
	cout.rdbuf(coutbuf);
#endif
	cout << "\n\n";
}

void Display::showWinner(Event & winnerMessage, std::string gameName)
{
#ifndef DEBUG
#ifdef AT_LINUX
	system("clear");
#else
	system("cls");
#endif
	ofstream out(gameName + "_winner" + ".txt");
	auto coutbuf = cout.rdbuf(out.rdbuf());

#endif
	cout << "\n\n";
	cout << Display::MG << helpCentre(Display::WIDTH, "EL GANADOR DEL BATTLE ROYALE ES:") << '\n'
		<< Display::MG << helpCentre(Display::WIDTH, winnerMessage.score().first._name) << '\n';
	cout << "\n\n";
#ifndef DEBUG
	out.close();
	cout.rdbuf(coutbuf);
#endif
}

void Display::showError(std::string error)
{
#ifndef DEBUG
#ifdef AT_LINUX
	system("clear");
#else
	system("cls");
#endif
#endif
	cout << "\n\n";
	cout << Display::MG << "Error: " + error << '\n';
	cout << "\n\n";
}

void Display::showDuel(Event const & e)
{
	cout << Display::MG << "Combate numero: " << e.time() << '\n';
	cout << Display::MG << e.score().first._name << " ha eliminado a " << e.score().second._name << '\n';
}

void Display::showPizzaFlee(Event const & e)
{
	cout << Display::MG << "El pizzero salvaje " << e.score().first._name << " ha huido del combate" << '\n';
}

void Display::showInfectedOnDuel(Event const & e)
{
	cout << Display::MG << "Tras perder el combate, " << e.score().second._name << " ha infectado a " << e.score().first._name << '\n';
}

void Display::showFindVaccine(Event const & e)
{
	cout << Display::MG << "Se ha encontrado una vacuna para la infeccion" << '\n';
}

void Display::showStealVaccine(Event const & e)
{
	cout << Display::MG << "El hijo**** de " << e.score().first._name << " ha robado la vacuna cuando le estaban curando. Ahora no hay vacuna." << '\n';
}

void Display::showGetVaccinated(Event const & e)
{
	cout << Display::MG << e.score().first._name << " ha sido vacunado y ahora es inmune a LA ENFERMEDAD" << '\n';
}

void Display::showGetCured(Event const & e)
{
	cout << Display::MG << e.score().first._name << " se ha librado de LA ENFERMEDAD" << '\n';
}

void Display::showNaturalInfection(Event const & e)
{
	cout << Display::MG << e.score().first._name << " ha contraido LA ENFERMEDAD por causas naturales" << '\n';
}

void Display::showNewPlayer(Event const & e)
{
	cout << Display::MG << e.score().first._name << " se ha unido a la batalla" << '\n';
}

void Display::showInfectionElimination(Event const & e)
{
	cout << Display::MG << e.score().first._name << " ha sido eliminado a causa de LA ENFERMEDAD" << '\n';
}

//Formatting
string Display::helpCentre(int width, const string& str) {
	int len = str.length();
	if (width < len) { return str.substr(0, width - 3) + "..."; }

	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return string(pad1, ' ') + str + string(pad2, ' ');
}

string Display::helpCentre(int width, int number) {
	return helpCentre(width, to_string(number));
}

string Display::hLine() {
	return MG + string(WIDTH, '-');
}


