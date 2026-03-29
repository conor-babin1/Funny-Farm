#include <vector>
#include <iostream>

class word {
public:
	word(std::string name, int id);
	~word();
	std::string getName();
	int getId();
	void addConnection(word* connection);
	const void printName();
	const void printDots();
	void guess();
	bool getGuessed();
	void available();
	bool getAvailable();
	void makeConnectionsAvailable();
	bool hasNodes();
	std::vector<word*> getConnections();
	void setPrinted(bool printed);
	bool getPrinted();
	static int getObjCount(); 

private:
	std::string _name;
	int _id;
	std::vector<word*> _connections;
	bool _guessed{false};
	bool _available{false};
	bool _printed{false};
	static int _objCount;
};
