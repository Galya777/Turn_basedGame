//
// Created by galya777 on 11.05.25.
//

#include "UnlivingUnit.h"
#include <stdexcept>

UndeadUnit::UndeadUnit(int hp, Armor* arm, int gold, int mana)
        : Unit(hp, arm, gold), hasMana(mana >= 0), manaPoints(mana) {}

bool UndeadUnit::hasManaAttribute() const {
    return hasMana;
}

int UndeadUnit::getMana() const {
    return hasMana ? manaPoints : -1;
}

void UndeadUnit::setMana(int m) {
    if (m < 0) {
        throw std::invalid_argument("Mana cannot be negative");
    }
    manaPoints = m;
    hasMana = true;
}

void UndeadUnit::increaseMana(int amount) {
    if (hasMana) {
        manaPoints += amount;
    }
}

std::string UndeadUnit::getType() const {
    return "Undead";
}

void UndeadUnit::attack(Unit& /* target */) {

}

Unit* UndeadUnit::clone() const {
    return new UndeadUnit(*this);
}

UndeadUnit::~UndeadUnit() = default;

