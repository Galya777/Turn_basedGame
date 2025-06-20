//
// Created by galya777 on 11.05.25.
//

#include "Sagittarius.h"

Sagittarius::Sagittarius(FirearmType type)
        : LivingUnit(
        535,
        new MediumArmor(3),
        300,
        createWeapon(type)
)
{}

std::string Sagittarius::getType() const {
    return "Sagittarius";
}

Unit* Sagittarius::clone() const {
    return new Sagittarius(*this);
}

Weapon* Sagittarius::createWeapon(FirearmType type) {
    switch (type) {
        case FirearmType::BOW:
            return new Firearm(10, "Bow");
        case FirearmType::GUN:
            return new Firearm(12, "Gun");
        default:
            throw std::invalid_argument("Invalid FirearmType");
    }
}

