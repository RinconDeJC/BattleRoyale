#include "FightCommand.h"

#include "JsonOutput.h"

FightCommand::FightCommand(int ticks) :
	Command("fight", 'f', "[N] fight/f [O] turnos a simular (1 por defecto). Simula un turno. "),
	_ticks(ticks)
{
}

FightCommand::~FightCommand()
{
}

Command * FightCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new FightCommand(_ticks);
	}
	return nullptr;
}

void FightCommand::parseOptions(std::stringstream & ss)
{

	try {
		ss >> _ticks;
		if (ss.fail()) {
			//Default option = 1
			_ticks = 1;
			return;
		}
			
	}
	catch (std::exception &e) {
		std::string error = std::string(e.what());
		throw std::domain_error("Parametro de numero de ticks incorrecto" + error);
	}
	char test;
	ss >> test;
	if (!ss.fail()) {
		throw std::domain_error("Demasiados argumentos");
	}
}


void FightCommand::run(bool &exit)
{
	Game game = _controller->game();
	bool finished = _controller->game().finished();
	if (finished)
		throw std::runtime_error("El juego ya ha acabado");
	std::queue<Event> eventos = _controller->game().run(_ticks);
	_controller->display().showGame(eventos, _controller->game().gameName());

	if (_controller->game().finished()) {
		Event winner = _controller->game().winner();
		_controller->display().showWinner(winner, _controller->game().gameName());
	}

}
