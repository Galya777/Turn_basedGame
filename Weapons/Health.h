//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_HEALTH_H
#define TURN_BASEDGAME_HEALTH_H

#include <exception>
#include <stdexcept>

class Health {


public:
    Health(int maxHealth) : current(maxHealth), max(maxHealth) {}

    void reduce(int dmg) {
        if(dmg>0) {
            current -= dmg;
            if (current < 0) current = 0;
        } else{
            throw std::invalid_argument("Damage must be a positive integer.");
        }
    }
    void heal(int amount) {
        if (amount > 0) {
            current += amount;
            if (current > max) current = max;
        } else {
            throw std::invalid_argument("Healing amount must be positive.");
        }
    }
    void restore(int amount) {
        current = std::min(current + amount, max);
    }

    void reset() {
        current = max;
    }

    void setMax(int newMax) {
        if (newMax <= 0) {
            throw std::invalid_argument("Max health must be greater than 0.");
        }
        max = newMax;
        if (current > max) {
            current = max;
        }
    }

    void kill() {
        current = 0;
    }

    bool isAlive() const { return current > 0; }
    int getCurrent() const { return current; }
    int getMax() const { return max; }

private:
    int current;
    int max;
};



#endif //TURN_BASEDGAME_HEALTH_H
