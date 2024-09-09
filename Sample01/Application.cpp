#include "Application.h"


Application::Application() {
}
Application::~Application() {}

void Application::runInitialPage() {

    int userChoice;
    bool userFlag = true;

    do {

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "     Programming Fundamental Concepts      \n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[1] Ending The program\n";
        cout << "[2] Display Game Rules Information\n";
        cout << "[3] Play FARKLE\n";
        cout << "[4] Display the Reflection Report\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nWhich option would you like ( 1 to 4 ): ";
        cin >> userChoice;
        cout << endl;

        switch (userChoice) {

            case 1:
                cout << "Ending the program . . .";
                userFlag = false;
                break;

            case 2:
                displayGameRules();
                break;

            case 3:
				askAndReceivePlayerCount();
				farkleMainLoop();
                break;

            case 4:
                cout << "Placeholder4";
                break;

            default:
                cout << "Please choose an option from 1 to 4:";
                cin >> userChoice;
                break;
        }
    }
    while(userFlag);
	exit(0);
}
void Application::askAndReceivePlayerCount() {

    int newPlayerCount;

    cout << "\nHow Many Players? (1 - 4): ";
    cin >> newPlayerCount;

    if ( newPlayerCount >= 1 && newPlayerCount <= 4){
        playerCount = newPlayerCount;
    }
    else{
        while(newPlayerCount < 1 || newPlayerCount > 4){
            cout << "\nPlease Enter 1 - 4 Players:";
            cin >> newPlayerCount;
        }
        cout << "\n" << newPlayerCount << "Players";
        playerCount = newPlayerCount;
    }
	
    cin.ignore(); //clearing the buffer
    for (int i = 0; i < playerCount; ++i) {
        string userName;
        cout << "\nEnter Player " << i+1 << "'s Name: ";
        getline(cin, userName);
		seriesOfPlayers.push_back(Player(userName, 0, 0));
    }
}
void Application::farkleMainLoop() {
    cout << "\n*************************************************";
    cout << "\n      FARKLE :: A dice game for 1-4 players     ";
    cout << "\n*************************************************\n";

    bool roundFlag = true;
    generateSixDice();    
    generateSixSelectedDice();
	generateSixRemainingDice();
    Score score;
    
    while (!score.checkScoreWinCondition(seriesOfPlayers)) { 
        for (int playerNumber = 0; playerNumber < seriesOfPlayers.size(); ++playerNumber) {
            displayPlayersScoreboard();

            char userChoice = 'z';
            roundFlag = true;

            while (roundFlag) {
                cout << "\nIt's your turn, " << seriesOfPlayers[playerNumber].getPlayerName() << ":\n\n";

                do {
                    asignValueToSixDice();
                    displayDiceVisuals();
                        
                    if (score.checkAvailableScore(seriesOfDice)) {
                        cout << "\nDo you want to [f]orefit this round, or [s]core points?: ";
                        cin >> userChoice;
                        cout << endl;

                        if (userChoice == 'f' || userChoice == 'F') {
                            cout << "You scored no points " << seriesOfPlayers[playerNumber].getPlayerName()
							 <<"; moving to the next player...\n";
							resetPlayerCurrentScore(playerNumber);
							resetFunction();
                            roundFlag = false;
							break;
                        } else if (userChoice == 's' || userChoice == 'S') {
                            selectDice(playerNumber);

							while (checkRemainingDiceCount() > 0 && roundFlag == true) {
								char userRerollChoice;
								cout << "Do you want to reroll your remaining dice? ([y] for yes, [n] for no)\n";
								cin >> userRerollChoice;
								if (userRerollChoice == 'n' || userRerollChoice == 'N') {
									cout << "Your scored points were saved " <<
									seriesOfPlayers[playerNumber].getPlayerName() <<"; moving to the next player...\n";
									roundFlag = false;
									break;
								} 
								else if (userRerollChoice == 'y' || userRerollChoice == 'Y') {
									resetSelectedDiceValue();
									resetRemainingDiceValue();
									regenerateSeriesOfDiceUnlockedValue();
									insertFromSeriesToRemaining();
									displayDiceVisuals();

									if (!score.checkAvailableScore(remainingDice)) {
										cout << "You farkled " << seriesOfPlayers[playerNumber].getPlayerName() 
										<<"! Your current score is reset! Moving to the next player...\n";
										resetPlayerCurrentScore(playerNumber);
										resetFunction();

										roundFlag = false;
										break;
									}
									else if (score.checkAvailableScore(remainingDice)) {
										selectDice(playerNumber);
									}
								}
							}
							asignPlayerTotalScore(playerNumber);
							resetPlayerCurrentScore(playerNumber);
							resetFunction();
							roundFlag = false;
                        }
                    } else if (!score.checkAvailableScore(seriesOfDice)) {
                        cout << "You farkled " << seriesOfPlayers[playerNumber].getPlayerName() 
						<<"! Your current score is reset! Moving to the next player...\n";
						resetPlayerCurrentScore(playerNumber);
						resetFunction();
                        roundFlag = false;
						break;
                    } else {
                        cout << "Invalid input. Please enter a valid choice (f/s).\n";
                    }        
                } while (userChoice != 'f' && userChoice != 'F' && userChoice != 's' && userChoice != 'S');
            }
        }
    }
    displayPlayersScoreboard();
	cout << "Game Over!\n";
	resetFunction();
	exit(0);
}

void Application::generateSixDice() {
	for(int i = 1; i < 7 ; i ++) {
		seriesOfDice.push_back(Die(0,i,false));
	}
}
void Application::generateSixSelectedDice() {
	for (int i = 1; i < 7; i ++)
		selectedDice.push_back(Die(0, i, true));
}
void Application::generateSixRemainingDice() {
	for (int i = 1; i < 7; i ++)
		remainingDice.push_back(Die(0, i, false));
}
void Application::regenerateSeriesOfDiceUnlockedValue() {
	for (int i = 0; i < seriesOfDice.size(); i ++) {
		if (!seriesOfDice[i].getDieLockStatus()) {
			int randomValue;
			randomValue = seriesOfDice[i].generateDieValue();
			seriesOfDice[i].setDieValue(randomValue);
		}
	}
}
vector<int> Application::separatePositions(int selectedPositions) {
    vector<int> individualPositions(6, -1); // Initialize vector with 6 elements, all set to -1
    
    int index = 5; // Start from the last position
    while (selectedPositions > 0 && index >= 0) {
        int digit = selectedPositions % 10;
        if (digit >= 0 && digit <= 6) {
            individualPositions[digit - 1] = digit; // Place the digit in its corresponding position
        }
        selectedPositions /= 10;
        index--;
    }
    return individualPositions;
}
vector<Die> Application::insertToSelectedDice(vector<int> individualPositions) {
	for (int i = 0; i < seriesOfDice.size(); i ++) {
		if (seriesOfDice[i].getDiePosition() == individualPositions[i]) {
			seriesOfDice[i].setDieLockStatus(true);
			int newDieValue = seriesOfDice[i].getDieValue();
			selectedDice[i].setDieValue(newDieValue); 
		}
	}
	return selectedDice;
}
void Application::asignValueToSixDice() {
	for(int i = 0; i < seriesOfDice.size(); i ++) {
		int randomValue;
		randomValue = seriesOfDice[i].generateDieValue();
		seriesOfDice[i].setDieValue(randomValue);
	}
}
void Application::asignPlayerTotalScore(int playerNumber) {
	Score score;
	int newCurrentScore = seriesOfPlayers[playerNumber].getPlayerCurrentScore();
	int newTotalScore = seriesOfPlayers[playerNumber].getPlayerTotalScore();
	newTotalScore += newCurrentScore;
	seriesOfPlayers[playerNumber].setPlayerTotalScore(newTotalScore);
}
void Application::updatePlayerCurrentScore(int playerNumber) {
	Score score;
	int newCurrentScore = score.checkAvailableScore(selectedDice);
	int previousCurrentScore = seriesOfPlayers[playerNumber].getPlayerCurrentScore();
	int scoreSum = newCurrentScore + previousCurrentScore;
	seriesOfPlayers[playerNumber].setPlayerCurrentScore(scoreSum);
}
void Application::resetPlayerCurrentScore(int playerNumber) {
	seriesOfPlayers[playerNumber].setPlayerCurrentScore(0);
}
void Application::resetSelectedDiceValue() {
	for (int i = 0; i < selectedDice.size(); i ++)
		if (selectedDice[i].getDieValue())
			selectedDice[i].setDieValue(0);
}
void Application::resetSeriesOfDice() {
	for (int i = 0; i < seriesOfDice.size(); i ++) {
		seriesOfDice[i].setDieLockStatus(false);
	}
	asignValueToSixDice();
}
void Application::resetRemainingDiceValue() {
	for (int i = 0; i < remainingDice.size(); i ++)
		if (remainingDice[i].getDieValue())
			remainingDice[i].setDieValue(0);
}
void Application::resetFunction() {
	
	resetSeriesOfDice();
	resetSelectedDiceValue();
	resetRemainingDiceValue();
}
void Application::insertFromSeriesToRemaining() {
	for (int i = 0; i < seriesOfDice.size(); i ++) {
		if (!seriesOfDice[i].getDieLockStatus()) {
			int unlockedValue = seriesOfDice[i].getDieValue();
			remainingDice[i].setDieValue(unlockedValue);
		}
	}
}
int Application::checkRemainingDiceCount() {
	int count = 0;
	for (int i = 0; i < seriesOfDice.size(); i ++) {
		if (!seriesOfDice[i].getDieLockStatus())
			++ count;	
	}
	return count;
}
void Application::selectDice(int playerNumber) {
	int selectedPositions;            
	cout << "Please select the dice you want using the number under the die: ";
	cin >> selectedPositions;
	cout << endl;
                            
	vector<int> individualPositions = separatePositions(selectedPositions);
	insertToSelectedDice(individualPositions);
	updatePlayerCurrentScore(playerNumber);
	displayPlayersScoreboard();
	displayDiceVisuals();
}

void Application::displayGameRules(){

    fstream gameRules;
    gameRules.open("gameRules.txt");

    if(gameRules.is_open()){

        while(!gameRules.eof()){

            string aLineFromFile;

            getline(gameRules, aLineFromFile);
            cout << aLineFromFile << "\n";
        }
        gameRules.close();
    }
    else{
        cout << "\nFile Not Found";
    }
}
void Application::displayDiceVisuals() {
    vector<vector<string>> diceArt = {
        {" ----- ", "|     |", "|  *  |", "|     |", " ----- "},
        {" ----- ", "|*    |", "|     |", "|    *|", " ----- "},
        {" ----- ", "|*    |", "|  *  |", "|    *|", " ----- "},
        {" ----- ", "|*   *|", "|     |", "|*   *|", " ----- "},
        {" ----- ", "|*   *|", "|  *  |", "|*   *|", " ----- "},
        {" ----- ", "|*   *|", "|*   *|", "|*   *|", " ----- "} 
    };

    vector<string> crossArt = {
        "   @   ",
        "  @@@  ",
        " @@@@@ ",
        "  @@@  ",
        "   @   "
    };

    vector<string> output(5, "");

    for (int i = 0; i < seriesOfDice.size(); ++i) {
        if (seriesOfDice[i].getDieLockStatus() == true) {
            for (int j = 0; j < 5; ++j) {
                output[j] += crossArt[j] + "  ";
            }
        } else {
            int dieValue = seriesOfDice[i].getDieValue();
            for (int j = 0; j < 5; ++j) {
                output[j] += diceArt[dieValue - 1][j] + "  ";
            }
        }
    }

    for (const string& line : output) {
        cout << line << endl;
    }


    for (int i = 0; i < seriesOfDice.size(); ++i) {
        cout << "   " << seriesOfDice[i].getDiePosition() << "     ";
    }

    cout << endl;
}
void Application::displayPlayersScoreboard() {
    cout << endl;
    for (int i = 0; i < seriesOfPlayers.size(); ++i) {
        cout << left << setw(20) << seriesOfPlayers[i].getPlayerName()
             << "  Total Score: " << right << setw(5) << seriesOfPlayers[i].getPlayerTotalScore()
             << "  Current Score: " << right << setw(5) << seriesOfPlayers[i].getPlayerCurrentScore()
             << endl;
    }
    cout << endl;
}