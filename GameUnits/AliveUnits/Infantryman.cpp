//
// Created by galya777 on 11.05.25.
//

#include "Infantryman.h"

Infantryman::Infantryman()
        : LivingUnit(
        420,                   // Health
        new MediumArmor(8),    // Armor with durability 8
        250,                   // Gold cost
        new MeleeWeapon(7, "Sword")  // Melee weapon with damage 7
)
{}

std::string Infantryman::getType() const {
    return "Infantryman";
}

Unit* Infantryman::clone() const {
    return new Infantryman(*this);
}


