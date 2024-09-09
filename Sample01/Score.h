#pragma once

#include "Application.h"


class Score {

private:
    

public:
	Score();
	~Score();

	bool checkScoreWinCondition(vector<Player>);
	int checkAvailableScore(vector<Die>);
};