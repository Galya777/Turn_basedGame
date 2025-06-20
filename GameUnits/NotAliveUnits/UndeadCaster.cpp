//
// Created by galya777 on 08.06.25.
//

#include "UndeadCaster.h"
#include <stdexcept>

UndeadCaster::UndeadCaster(int hp, Armor* armor, int goldCost, int manaAmount)
        : UndeadUnit(hp, armor, goldCost), mana(manaAmount) {}

void UndeadCaster::useMana(int amount) {
    if (amount <= mana) {
        mana -= amount;
    } else {
        throw std::runtime_error("Not enough mana!");
    }
}

int UndeadCaster::getMana() const {
    return mana;
}

Unit* UndeadCaster::clone() const {
    return new UndeadCaster(*this);
}

UndeadCaster::~UndeadCaster() = default;

