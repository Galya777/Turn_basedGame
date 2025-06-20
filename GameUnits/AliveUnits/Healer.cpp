//
// Created by galya777 on 05.06.25.
//

#include "Healer.h"

Healer::Healer()
        : LivingUnit(
        290,
        new Unarmored(),    // The healer is unarmored
        150,
        new MeleeWeapon(2, "Staff"),
        200
)
{}

std::string Healer::getType() const {
    return "Healer";
}

void Healer::heal(LivingUnit& target) {
    if (!hasManaAttribute() || getMana() < 100) {
        throw std::runtime_error("Not enough mana to heal.");
    }
    if (!target.isAlive()) {
        throw std::runtime_error("Cannot heal a dead unit.");
    }

    target.getHealth().restore(100);
    setMana(getMana() - 100);
}

Unit* Healer::clone() const {
    return new Healer(*this);
}

