#include"Die.h"


Die::Die(int value, int position, bool status) {
    setDieValue(value);
    setDiePosition(position);
    setDieLockStatus(status);
}
Die::~Die() {}

int Die::getDieValue() {
    return dieValue;
}
int Die::getDiePosition() {
    return diePosition;
}
bool Die::getDieLockStatus() {
    return dieLockStatus;
}

void Die::setDieValue(int newDieValue) {
	dieValue = newDieValue;
}
void Die::setDiePosition(int newDiePosition) {
	diePosition = newDiePosition;
}
void Die::setDieLockStatus(bool newDieLockStatus) {
	dieLockStatus = newDieLockStatus;
}

int Die::generateDieValue() {
	int dieValue = (rand() % 6) + 1;
	
	return dieValue;
}