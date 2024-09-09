#pragma once

#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

class Die{
private:
    int dieValue;
    int diePosition;
    bool dieLockStatus;

public:
    Die(int, int, bool);
    ~Die();

    int getDieValue();
    int getDiePosition();
    bool getDieLockStatus();
    
    void setDieValue(int);
    void setDiePosition(int);
    void setDieLockStatus(bool);
    
    int generateDieValue();
};