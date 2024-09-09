#include "Score.h"

Score::Score() {
}
Score::~Score() {
}

bool Score::checkScoreWinCondition(vector<Player> seriesOfPlayers) {
	for (int i = 0; i < seriesOfPlayers.size(); ++i) {
        if (seriesOfPlayers[i].getPlayerTotalScore() >= targetScore) {

            return true;
        }
	}
	return false;
}
int Score::checkAvailableScore(vector<Die> selectedDice) {
    vector<int> counts(7, 0);
    int outputScoreSum = 0;

    for (Die& die : selectedDice) {
        counts[die.getDieValue()]++;
    }

    vector<int> scorePerCount1 = {0, 100, 200, 300, 1000, 2000, 3000};
    vector<int> scorePerCount2 = {0, 0, 0, 200, 1000, 2000, 3000};
    vector<int> scorePerCount3 = {0, 0, 0, 300, 1000, 2000, 3000};
    vector<int> scorePerCount4 = {0, 0, 0, 400, 1000, 2000, 3000};
    vector<int> scorePerCount5 = {0, 50, 100, 500, 1000, 2000, 3000};
    vector<int> scorePerCount6 = {0, 0, 0, 600, 1000, 2000, 3000};

    outputScoreSum += scorePerCount1[counts[1]];
    outputScoreSum += scorePerCount2[counts[2]];
    outputScoreSum += scorePerCount3[counts[3]];
    outputScoreSum += scorePerCount4[counts[4]];
    outputScoreSum += scorePerCount5[counts[5]];
    outputScoreSum += scorePerCount6[counts[6]];

	
    if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1 && 
		counts[6] == 1) {
        outputScoreSum = 1500;
    }

    
	int pairCount = 0, fourOfAKindCount = 0, tripleCount = 0;
	for (int i = 1; i <= 6; ++i) {
    switch (counts[i]) {
        case 2:
            ++pairCount;
            break;
        case 3:
            ++tripleCount;
            break;
        case 4:
            ++fourOfAKindCount;
            break;
		}
	}	
	if (pairCount == 3)
		outputScoreSum = 1500;
	else if (fourOfAKindCount == 1 && pairCount == 1)
		outputScoreSum = 1500;
	else if (tripleCount == 2)
		outputScoreSum = 2500;	

    return outputScoreSum;
}