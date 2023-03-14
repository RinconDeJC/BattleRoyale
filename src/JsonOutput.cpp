#include "JsonOutput.h"
#include "writer.h"
#include "prettywriter.h"
#include "stringbuffer.h"
#include "filereadstream.h"
#include "filewritestream.h"
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace rapidjson;

const char* JsonOutput::_EXT = ".json";

JsonOutput::JsonOutput(std::string const& fn, std::string const& path) : 
	_file_name(fn),
	_path(path)
{}

void JsonOutput::writeInitialPlayerList(std::vector<std::pair<std::string, std::pair<std::string, std::string>>>& list)
{
	Document playersJSON;
	playersJSON.Parse("{\"players_array\":[],\"players\":{},\"time\":0,\"vaccine\":false}");
	MemoryPoolAllocator<>& allocator = playersJSON.GetAllocator();
	Value& jsonList = playersJSON["players"];
	Value& players_array = playersJSON["players_array"];
	for (auto it = list.begin(); it != list.end(); ++it) {
		Value littleJSON(kObjectType);
		Value name(kStringType);
		Value prof(kStringType);
		Value team(kStringType);
		name.SetString(it->first.c_str(), allocator);
		team.SetString(it->second.first.c_str(), allocator);
		prof.SetString(it->second.second.c_str(), allocator);

		littleJSON.AddMember("team", team, allocator);
		littleJSON.AddMember("profession", prof, allocator);
		littleJSON.AddMember("alive", kTrueType, allocator);
		littleJSON.AddMember("vaccinated", kFalseType, allocator);
		littleJSON.AddMember("infected", kFalseType, allocator);
		jsonList.AddMember(GenericStringRef<char>(it->first.c_str()), littleJSON, allocator);
		name.SetString(it->first.c_str(), allocator);
		players_array.PushBack(name, allocator);
	}

	printJSON(playersJSON, _path + _file_name + "_list" + _EXT);
}


void JsonOutput::writeTeamsList(std::unordered_map<std::string, std::vector<Person>> const& teams)
{
	Document teamsJSON;
	// JSON array of JSON object where each of them will be a team
	teamsJSON.Parse("{\"teams\":[]}");
	MemoryPoolAllocator<>& allocator = teamsJSON.GetAllocator();
	Value& teams_array = teamsJSON["teams"];

	auto it = teams.cbegin();
	while (it != teams.cend()) {

		Value team(kObjectType);
		Value team_name(kStringType);
		Value list(kArrayType);

		team_name.SetString(it->first.c_str(), allocator);
		auto it_team = it->second.cbegin();
		while (it_team != it->second.cend()) {
			Value player_name(kStringType);
			player_name.SetString(it_team->name().c_str(), allocator);
			list.PushBack(player_name, allocator);
			++it_team;
		}
		team.AddMember("name", team_name, allocator);
		team.AddMember("players", list, allocator);

		teams_array.PushBack(team, allocator);
		++it;
	}

	printJSON(teamsJSON, _path + _file_name + "_teams" + _EXT);
}

void JsonOutput::writeOut(std::queue<Event>& events, int remaining)
{
	// Reading and parsing the players_list
	std::string file_name_list(_path + _file_name + "_list" + _EXT);
	FILE* fp = fopen(file_name_list.c_str(), "rb"); // non-Windows use "r"

	char Buffer[8192];
	FileReadStream is(fp, Buffer, sizeof(Buffer));

	Document players_list;
	players_list.ParseStream(is);
	fclose(fp);

	Document doc;
	assert(!events.empty());
	int time = events.front().time();
	startDocument(doc, time, remaining);

	while (!events.empty()) {
		if (time != events.front().time()) {
			printJSON(doc, _path + _file_name + "_" + std::to_string(time) + _EXT);
			time = events.front().time();
			startDocument(doc, time, remaining);
		}
		writeEvent(events.front(), doc);
		switch (events.front().type()) {
		case Event::_DUEL:
			players_list["players"][events.front().score().second._name.c_str()]["alive"] = kFalseType;
			break;
		case Event::_FIND_VACCINE:
			players_list["vaccine"] = kTrueType;
			break;
		case Event::_GET_CURED:
		case Event::_GET_VACCINATED:
			players_list["players"][events.front().score().first._name.c_str()]["vaccinated"] = kTrueType;
			break;
		case Event::_INFECTED_ON_DUEL:
		case Event::_NATURAL_INFECTION:
			players_list["players"][events.front().score().first._name.c_str()]["infected"] = kTrueType;
			break;
		case Event::_INFECTION_ELIMINATION:
			players_list["players"][events.front().score().first._name.c_str()]["alive"] = kFalseType;
			break;
		case Event::_STEAL_VACCINE:
			players_list["vaccine"] = kFalseType;
			break;
		}
		events.pop();
	}

	printJSON(doc, _path + _file_name + "_" + std::to_string(time) + _EXT);

	//Final update on list
	players_list["time"] = time;

	fp = fopen(file_name_list.c_str(), "wb"); // non-Windows use "w"

	FileWriteStream os(fp, Buffer, sizeof(Buffer));

	PrettyWriter<FileWriteStream> writer(os);
	players_list.Accept(writer);

	fclose(fp);
}

void JsonOutput::writeWinner(Event& winner)
{
	Document doc;
	startDocument(doc, winner.time(), 1);
	writeEvent(winner, doc);

	printJSON(doc, _path + _file_name + "_winner" + _EXT);
}

void JsonOutput::printJSON(Document& doc, std::string fullFileName)
{
	// Stringify the DOM
	StringBuffer buffer;
	//Writer<StringBuffer> writer(buffer);
	PrettyWriter<StringBuffer> writer(buffer);
	doc.Accept(writer);

	// Output
	std::ofstream output(fullFileName);
	assert(output.is_open());
	output << buffer.GetString();
	output.close();
}

void JsonOutput::startDocument(Document& d, int time, int remaining)
{
	d.Parse("{\"events\":[],\"time\":0,\"remaining\":0}");
	d["time"] = time;
	d["remaining"] = remaining;
}

void JsonOutput::writeEvent(Event const& e, Document& d)
{
	Value& events = d["events"];
	assert(events.IsArray());
	MemoryPoolAllocator<>& allocator = d.GetAllocator();
	Value newEvent(kObjectType);
	Value aux;
	aux.SetString(e.typeToC_String(), allocator);
	newEvent.AddMember("type", aux, allocator);
	aux.SetInt(e.time());
	newEvent.AddMember("time", aux, allocator);

	//Create JSON of person1 score
	newEvent.AddMember("person1", scoreJSON(e.score().first, allocator), allocator);


	if (e.score().second._name == "") {
		aux.SetNull();
		newEvent.AddMember("person2", aux , allocator);
	}
	else {
		newEvent.AddMember("person2", scoreJSON(e.score().second, allocator), allocator);
	}

	events.PushBack(newEvent, allocator);
}

Value JsonOutput::scoreJSON(Person::Score const& score, MemoryPoolAllocator<>& allocator)
{
	Value ret_val(kObjectType);
	Value aux;

	aux.SetString(score._name.c_str(), allocator);
	ret_val.AddMember("name", aux, allocator);

	aux.SetString(score._team.c_str(), allocator);
	ret_val.AddMember("team", aux, allocator);
	
	aux.SetString(score._prof.c_str(), allocator);
	ret_val.AddMember("profession", aux, allocator);

	Value kills(kArrayType);
	for (std::string n : score._kills) {
		Value val;
		val.SetString(n.c_str(), allocator);
		kills.PushBack(val, allocator);
	}
	ret_val.AddMember("kills", kills, allocator);

	aux.SetString(score._killed_by.c_str(), allocator);
	ret_val.AddMember("killed_by", aux, allocator);

	aux.SetInt(score._n_days_survived);
	ret_val.AddMember("days_survived", aux, allocator);

	aux.SetInt(score._n_days_infected);
	ret_val.AddMember("days_infected", aux, allocator);

	return ret_val;
}
