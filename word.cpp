#include "word.h"

word::word(std::string name) : _name(name)
{
	++_objCount;
}

int word::getObjCount() {
	return _objCount;
}

word::~word(){}

std::string word::getName() {
	return _name;
}

void word::addConnection(word* connection) {
	_connections.push_back(connection);
}

std::vector<word*> word::getConnections() {
	std::vector<word*> connections;
	for(word* val : _connections) {
		connections.push_back(val);
	}
	return connections;
}

const void word::printName() {
	std::cout << _name << std::endl;
}

const void word::printDots() {
	for(int i = 0; i < _name.length(); i++) {
		std::cout << ".";
	}
	std::cout << std::endl;
}

void word::guess() {
	_guessed = true;
}

bool word::getGuessed() {
	return _guessed;
}

void word::available() {
        _available = true;
}

bool word::getAvailable() {
        return _available;
}

void word::makeConnectionsAvailable() {
	for(word* connection : _connections) {
		connection->available();
	}
}

bool word::hasNodes() {
	if(_connections.size()) {
		return true;
	}
	return false;
}

void word::setPrinted(bool printed) {
	_printed = printed;
}

bool word::getPrinted() {
	return _printed;
}
