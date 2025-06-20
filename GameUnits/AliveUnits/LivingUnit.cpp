//
// Created by galya777 on 11.05.25.
//

#include "LivingUnit.h"

LivingUnit::LivingUnit(int hp, Armor* arm, int goldCost, Weapon* weap, int mana)
        : Unit(hp, arm, goldCost),
          weapon(weap),
          hasMana(mana >= 0),
          manaPoints(mana)
{}

LivingUnit::~LivingUnit() {
    delete weapon;
    for (auto* ability : abilities) {
        delete ability;
    }
}

bool LivingUnit::hasManaAttribute() const {
    return hasMana;
}

int LivingUnit::getMana() const {
    return hasMana ? manaPoints : -1;
}

void LivingUnit::setMana(int m) {
    if (m < 0) throw std::invalid_argument("Mana cannot be negative");
    manaPoints = m;
    hasMana = true;
}

Unit* LivingUnit::clone() const {
    return new LivingUnit(*this);
}

std::string LivingUnit::getType() const {
    return "Living";
}

void LivingUnit::attack(Unit& target) {
int baseDamage = weapon ? weapon->getDamage() : 10; // default base damage
int reduced = target.getArmor() ? target.getArmor()->absorbDamage(baseDamage) : baseDamage;
target.takeDamage(reduced);
}


