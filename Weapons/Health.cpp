//
// Created by galya777 on 11.05.25.
//

#include "Health.h"

Health::Health(int maxHealth)
        : current(maxHealth), max(maxHealth) {}

void Health::reduce(int dmg) {
    if (dmg > 0) {
        current -= dmg;
        if (current < 0) current = 0;
    } else {
        throw std::invalid_argument("Damage must be a positive integer.");
    }
}

void Health::heal(int amount) {
    if (amount > 0) {
        current += amount;
        if (current > max) current = max;
    } else {
        throw std::invalid_argument("Healing amount must be positive.");
    }
}

void Health::restore(int amount) {
    current = std::min(current + amount, max);
}

void Health::reset() {
    current = max;
}

void Health::setMax(int newMax) {
    if (newMax <= 0) {
        throw std::invalid_argument("Max health must be greater than 0.");
    }
    max = newMax;
    if (current > max) {
        current = max;
    }
}

void Health::kill() {
    current = 0;
}

bool Health::isAlive() const {
    return current > 0;
}

int Health::getCurrent() const {
    return current;
}

int Health::getMax() const {
    return max;
}

