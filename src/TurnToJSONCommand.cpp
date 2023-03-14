#include "TurnToJSONCommand.h"


TurnToJSONCommand::TurnToJSONCommand() :
	Command("turn_json", 'j', "[N] turn_json/j. Ejecuta un turno de la partida cargada y guarda el resultado en un json con el nom,bre especificado por consola de comandos")
{
}

TurnToJSONCommand::~TurnToJSONCommand()
{
}

Command* TurnToJSONCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new TurnToJSONCommand();
	}
	return nullptr;
}

void TurnToJSONCommand::run(bool& exit)
{
	bool finished = _controller->game().finished();
	if (finished)
		throw std::runtime_error("El juego ya ha acabado");
	std::queue<Event> eventos = _controller->game().run();
	_controller->JSONOutput().writeOut(eventos, _controller->game().remaining());

	if (_controller->game().finished()) {
		Event winner = _controller->game().winner();
		_controller->JSONOutput().writeWinner(winner);
	}
}


