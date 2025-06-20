//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_HEALTH_H
#define TURN_BASEDGAME_HEALTH_H

#include <stdexcept>

class Health {
public:
    Health(int maxHealth);

    void reduce(int dmg);
    void heal(int amount);
    void restore(int amount);
    void reset();
    void setMax(int newMax);
    void kill();

    bool isAlive() const;
    int getCurrent() const;
    int getMax() const;

private:
    int current;
    int max;
};

#endif //TURN_BASEDGAME_HEALTH_H

