//
// Created by galya777 on 05.06.25.
//

#include "Wizard.h"

Wizard::Wizard()
        : LivingUnit(
        325,
        new LeatherArmor(3),
        250,
        new MeleeWeapon(10, "Magic Bolt"), // Can be SpellWeapon
        200
)
{}

void Wizard::attack(Unit& target) {
    if (getMana() < 50) return;

    setMana(getMana() - 50);
    int baseDamage = weapon ? weapon->getDamage() : 0;
    int actualDamage = target.getArmor() ? target.getArmor()->absorbDamage(baseDamage) : baseDamage;
    target.takeDamage(actualDamage);
}

std::string Wizard::getType() const {
    return "Wizard";
}

Unit* Wizard::clone() const {
    return new Wizard(*this);
}

