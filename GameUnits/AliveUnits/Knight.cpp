//
// Created by galya777 on 05.06.25.
//

#include "Knight.h"

Knight::Knight()
        : LivingUnit(
        835,
        new HeavyArmor(10),
        700,
        new MeleeWeapon(45, "Sword")
)
{}

std::string Knight::getType() const {
    return "Knight";
}

Unit* Knight::clone() const {
    return new Knight(*this);
}

