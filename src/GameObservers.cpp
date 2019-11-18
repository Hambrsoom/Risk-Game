
#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include "Player.h"
using namespace std;

GameObservers::GameObservers()
{

}


GameObservers::~GameObservers()
{
}

Subject::Subject() {
	_observers = new list<GameObservers*>;
}
Subject::~Subject() {
	list<GameObservers *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		delete (*i);
		*i = nullptr;
	}
	delete _observers;
	_observers = nullptr;
}

void Subject::attach(GameObservers* o) {
	_observers->push_back(o);
};

void Subject::detach(GameObservers* o) {
	_observers->remove(o);
};

void Subject::notify(string type) {
	list<GameObservers *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update(type);
};


AttackObserver::AttackObserver(GameEngine* p)
{
	subject = p;
	subject->attach(this);
}

AttackObserver ::~AttackObserver()
{
	subject->detach(this);
}

FortifyObserver::FortifyObserver(GameEngine* p)
{
	subject = p;
	subject->attach(this);
}

FortifyObserver ::~FortifyObserver()
{
	subject->detach(this);
}

ReinforceObserver::ReinforceObserver(GameEngine* p)
{
	subject = p;
	subject->attach(this);
}

ReinforceObserver ::~ReinforceObserver()
{
	subject->detach(this);
}

void AttackObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);

	if (phase.compare("attack") == 0) {
		vector <Player*> list = subject->getListOfPlayers();
		system("CLS");
		auto g = getSubject();
		cout << endl << endl << "Player " << token << ":Attack phase" << endl
			<< "The list of countries with more than one army are: " << endl;
		subject->getListOfPlayers().at(Utility::convertCStringToNumber(token))->printListOfCountriesWithMoreThanOneArmy();
	}
}


void FortifyObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);

	if (phase.compare("fortify") == 0) {
		system("CLS");
		GameEngine * p = getSubject();
		cout << endl << endl << "Player " << token << ":Fortify phase" << endl
			<< "The list of countries with more than one army are: " << endl;
		subject->getListOfPlayers().at(Utility::convertCStringToNumber(token))->printListOfCountriesWithMoreThanOneArmy();
	}
}

void ReinforceObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);

	if (phase.compare("reinforce") == 0) {
		system("CLS");
		GameEngine * p = getSubject();
		cout << endl << endl << "Player " << token << ":Reinforce phase" << endl;
		cout << "The player has: " << endl
			<< "countries: " << subject->getListOfPlayers().at(Utility::convertCStringToNumber(token))->getNumberTotalCountries() << endl
			<< "continents: " << subject->getListOfPlayers().at(Utility::convertCStringToNumber(token))->getContinentsOwnedByPlayer().size() << endl
			<< "cards: " << subject->getListOfPlayers().at(Utility::convertCStringToNumber(token))->getHandOfCards()->getTotalNumberOfCards() << endl;
	}
}

ConquerObserver::ConquerObserver(GameEngine * p)
{
	subject = p;
	subject->attach(this);
}

ConquerObserver::~ConquerObserver()
{
	subject->detach(this);
}

EliminationObserver::EliminationObserver(GameEngine* g)
{
	subject = g;
	subject->attach(this);
}

EliminationObserver::~EliminationObserver()
{
	subject->detach(this);
}

WinnerObserver::WinnerObserver(GameEngine* g)
{
	subject = g;
	subject->attach(this);
}

WinnerObserver ::~WinnerObserver()
{
	subject->detach(this);
}


void ConquerObserver::update(string type)
{
	if (type.compare("conquer") == 0) {
		GameEngine * p = getSubject();
		cout << endl << endl << "Player " << " has conquered a country." << endl << endl;

	}
}


void EliminationObserver::update(string type)
{
	if (type.compare("eliminate") == 0) {
		GameEngine * g = getSubject();
		printMapOwnership(g);
		cout << "Player has been Eliminated." << endl;

	}
}

void WinnerObserver::update(string type)
{
	if (type.compare("win") == 0) {
		GameEngine * g = getSubject();
		printMapOwnership(g);
		cout << endl << endl << "Player has won the game! Congratulations!" << endl << endl;

	}
}

void GameObservers::printMapOwnership(GameEngine * g)
{
	vector <Player*>  players = g->getListOfPlayers();
	cout << endl;
	cout << "***Player World Domination View***" << endl;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		Player * p = players[i];
		int playerCountries = p->getNumberPlayerCountries();
		int mapCountries = p->getNumberTotalCountries();
		double percentageOwnership = 100 * (double)playerCountries / (double)mapCountries;
		cout << "Player " << p->getPlayerName() << " has " << percentageOwnership << "% of countries on the Map." << endl;
		// delete p;
	}

	cout << endl;
}

