#pragma once

#include "Die.h"
#include "Player.h"
#include "Score.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;


static int targetScore = 5000;
static int playerCount;

class Application {
private:
    

public:
	vector<Die> seriesOfDice;
	vector<Die> selectedDice;
	vector<Die> remainingDice;
    vector<Player> seriesOfPlayers;

    Application();
    ~Application();

	void runInitialPage();
	void askAndReceivePlayerCount();
	void farkleMainLoop();

	void generateSixDice();
	void generateSixSelectedDice();
	void generateSixRemainingDice();
	void regenerateSeriesOfDiceUnlockedValue();
	vector<int> separatePositions(int);
	vector<Die> insertToSelectedDice(vector<int>);
	void asignValueToSixDice();
	void asignPlayerTotalScore(int);
	void updatePlayerCurrentScore(int);
	void resetPlayerCurrentScore(int);
	void resetSelectedDiceValue();
	void resetSeriesOfDice();
	void resetRemainingDiceValue();
	void resetFunction();
	void insertFromSeriesToRemaining();
	int checkRemainingDiceCount();
	void selectDice(int);

	void displayGameRules();
    void displayDiceVisuals();
	void displayPlayersScoreboard();
};