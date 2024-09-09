#pragma once


#include <string>
#include <vector>

using namespace std;

class Player {
private:
    string playerName;
	int playerCurrentScore;
    int playerTotalScore;

public:
    Player(string, int, int);
    ~Player();

    string getPlayerName();
	int getPlayerCurrentScore();
    int getPlayerTotalScore();
    
    void setPlayerName(string);
	void setPlayerCurrentScore(int);
    void setPlayerTotalScore(int);
};