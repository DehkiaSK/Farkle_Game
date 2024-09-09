#include "Player.h"


Player::Player(string name, int current, int total) {
    setPlayerName(name);
	setPlayerCurrentScore(current);
    setPlayerTotalScore(total);
}
Player::~Player() {}

string Player::getPlayerName() {
    return playerName;
}
int Player::getPlayerCurrentScore() {
    return playerCurrentScore;
}
int Player::getPlayerTotalScore() {
    return playerTotalScore;
}

void Player::setPlayerName(string newPlayerName) {
    playerName = newPlayerName;
}
void Player::setPlayerCurrentScore(int newPlayerCurrentScore) {
    playerCurrentScore = newPlayerCurrentScore;
}
void Player::setPlayerTotalScore(int newPlayerTotalScore) {
    playerTotalScore = newPlayerTotalScore;
}