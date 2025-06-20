//
// Created by galya777 on 11.05.25.
//

#include "Unit.h"

Unit::Unit(int hp, Armor* arm, int goldCost)
        : health(hp), armor(arm ? arm->clone() : nullptr), goldCost(goldCost) {}

Unit::Unit(const Unit& other)
        : health(other.health),
          armor(other.armor ? other.armor->clone() : nullptr),
          goldCost(other.goldCost) {}

Unit& Unit::operator=(const Unit& other) {
    if (this != &other) {
        health = other.health;
        delete armor;
        armor = other.armor ? other.armor->clone() : nullptr;
        goldCost = other.goldCost;
    }
    return *this;
}

Unit::~Unit() {
    delete armor;
}

bool Unit::isAlive() const {
    return health.getCurrent() > 0;
}

void Unit::takeDamage(int dmg) {
    int reduced = reduceDamage(dmg);
    health.reduce(reduced);
}

int Unit::reduceDamage(int baseDamage) {
    if (armor && !armor->isUsable()) {
        std::cout << "Armor is destroyed!\n";
    }
    return (armor && armor->isUsable())
           ? armor->absorbDamage(baseDamage)
           : baseDamage;
}

void Unit::heal(int amount) {
    health.heal(amount);
}

Health& Unit::getHealth() {
    return health;
}

const Health& Unit::getHealth() const {
    return health;
}

int Unit::getHP() const {
    return health.getCurrent();
}

int Unit::getGoldCost() const {
    return goldCost;
}

Armor* Unit::getArmor() const {
    return armor;
}

void Unit::setHP(int newHP) {
    health.setMax(newHP);
}

void Unit::setGoldCost(int newGoldCost) {
    goldCost = newGoldCost;
}

void Unit::setArmor(Armor* newArmor) {
    if (armor != newArmor) {
        delete armor;
        armor = newArmor ? newArmor->clone() : nullptr;
    }
}

