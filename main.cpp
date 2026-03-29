#include "word.h"

void printBoard(const std::vector<word*> words);
void printConnections(word* item);
std::vector<word*> createWords();

int word::_objCount = 0;

int main() {

	std::vector<word*> words = createWords();

	int count = 0;
	printBoard(words);
	int objCount = word::getObjCount();
	while (count < objCount - 1) {
		std::string guess;
		std::cout << "Guess: ";
		std::cin >> guess;
		if(guess == "STOP") {
			return 0;
		}
		for (word* val : words) {
			if(val->getName() == guess && val->getAvailable()) {
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

void printBoard(const std::vector<word*> words) {
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

std::vector<word*> createWords() {
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
}
