#include "word.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

void printBoard(const std::vector<word*> words);
void printConnections(word* item);
//std::vector<word*> createWords();
std::vector<word*> loadWordsFromJson(const std::string& filename);

int word::_objCount = 0;

int main() {
	// Add preset words
	//std::vector<word*> words = createWords();
	std::vector<word*> words = loadWordsFromJson("farm.json");

	int count = 0;
	printBoard(words);
	// get count for number of words instantiated
	int objCount = word::getObjCount();
	while (count < objCount - 1) {
		std::cout << "count: " << count << " num: " << objCount - 1 << std::endl;
		std::string guess;
		std::cout << "Guess: ";
		std::getline(std::cin, guess);
		// allow users to exit
		if(guess == "STOP") {
			return 0;
		}
		for(auto& c : guess) {
			c = std::tolower(c);
		}
		for (word* val : words) {
			if(val->getName() == guess && val->getAvailable()) {
				// correct guess, make the word guess and make all the connections print
				val->guess();
				val->makeConnectionsAvailable();
				count++;
				break;
			}
		}
		printBoard(words);
	}
	std::cout << "WINNER WINNER CHICKEN DINNER!" << std::endl;
	return 0;
}

std::vector<word*> loadWordsFromJson(const std::string& filename)
{
	std::ifstream inFile(filename);
	if (!inFile.is_open())
	{
		throw std::runtime_error("Could not open file: " + filename);
	}

	json j;
	inFile >> j;

	// Load nodes
	std::vector<word*> words;
	for (const auto& nodeJson : j.at("nodes")) {
		int id = nodeJson.at("id").get<int>();
		std::string name = nodeJson.at("name").get<std::string>();
		word* obj = new word(name, id);
		words.push_back(obj);
	}

	// Load edges
	for (const auto& edgeJson : j.at("edges"))
	{
		int sourceId = edgeJson.at("source").get<int>();
		int targetId = edgeJson.at("target").get<int>();
		for(int i = 0; i < words.size(); i++) {
			if(words[i]->getId() == sourceId) {
				bool found = false;
				for(int j = 0; j < words.size(); j++) {
					if(words[j]->getId() == targetId) {
						words[i]->addConnection(words[j]);
						found = true;
						break;
					}
				}
				if(!found) {
					std::cout << "Could not find target for edge: " << sourceId << " to " << targetId << std::endl;
				}
				break;
			}
			std::cout << "Could not find source for edge: " << sourceId << " to " << targetId << std::endl;
		}
	}
	// make 1st word set
	words[0]->guess();
        words[0]->available();
        words[0]->makeConnectionsAvailable();
	
	return words;

}

void printBoard(const std::vector<word*> words) {
	// clearing console
	std::cout << "\033[2J\033[1;1H";
	for(word* val : words) {
		if(val->getAvailable()) {
			if(val->getGuessed() && !val->getPrinted()) {
				val->printName();
				val->setPrinted(1);
				printConnections(val);
			}
			else {
				if(!val->getPrinted()) {
					val->printDots();
					val->setPrinted(1);
				}
			}
		}
	}
	for(word* val : words) {
		val->setPrinted(0);
	}
}

void printConnections(word* item) {
        bool newline = false;
        std::vector<word*> connections = item->getConnections();
	// two loops to ensure dots are printed before future words
        for(int i = 0; i < connections.size(); i++) {
                if (!connections[i]->getGuessed() && !connections[i]->getPrinted()) {
                        connections[i]->printDots();
                        connections[i]->setPrinted(1);
                        newline = true;
                }
        }
	for(int i = 0; i < connections.size(); i++) {
                std::vector<word*> multiConn;
                if(connections[i]->getGuessed() && !connections[i]->getPrinted()) {
                        connections[i]->printName();
                        connections[i]->setPrinted(1);
                        multiConn.push_back(connections[i]);
                        newline = true;
                }
		for(word* multi : multiConn) {
                        printConnections(multi);
                }
	}
        if(newline) {
                std::cout << std::endl;
        }
}

// TODO read from csv
/*std::vector<word*> createWords() {
	std::vector<word*> words;
	word* onTheFarm = new word("On The Farm");

        word* tractor = new word("tractor");
        word* trailer = new word("trailer");

        word* cow = new word("cow");
        word* bell = new word("bell");

        word* bull = new word("bull");
        word* bs = new word("bs");

        word* horse = new word("horse");
        word* cowboy = new word("cowboy");
        word* saddle = new word("saddle");

        word* chicken = new word("chicken");
        word* egg = new word("egg");
        word* omelet = new word("omelet");

        words.push_back(onTheFarm);
        words.push_back(tractor);
        words.push_back(cow);
        words.push_back(bull);
        words.push_back(horse);
        words.push_back(chicken);
        words.push_back(egg);
        words.push_back(trailer);
        words.push_back(bell);
        words.push_back(bs);
        words.push_back(cowboy);
        words.push_back(omelet);
	words.push_back(saddle);

        onTheFarm->guess();
        onTheFarm->available();
        onTheFarm->addConnection(tractor);
        onTheFarm->addConnection(cow);
        onTheFarm->addConnection(bull);
        onTheFarm->addConnection(horse);
        onTheFarm->addConnection(chicken);
        onTheFarm->makeConnectionsAvailable();

        chicken->addConnection(egg);

        egg->addConnection(omelet);

        horse->addConnection(cowboy);
        horse->addConnection(saddle);

        bull->addConnection(bs);

        tractor->addConnection(trailer);

        cow->addConnection(bell);
	return words;
}*/
