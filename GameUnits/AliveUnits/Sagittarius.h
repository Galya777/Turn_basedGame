//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_SAGITTARIUS_H
#define TURN_BASEDGAME_SAGITTARIUS_H
#pragma once

#include "LivingUnit.h"
#include "../../Weapons/Armors/MediumArmor.h"
#include "../../Weapons/Firearm.h"

class Sagittarius : public LivingUnit {
public:
    //giving the weapon in parameter gives the freedom to choose a different weapon by his choice
    Sagittarius(FirearmType type = FirearmType::BOW)
            : LivingUnit(
            535,
            new MediumArmor(3),
            300,
            createWeapon(type)
    ) {}

    std::string getType() const override { return "Sagittarius"; }
    Unit* clone() const override {
        return new Sagittarius(*this);
    }
private:
    static Weapon* createWeapon(FirearmType type) {
        switch (type) {
            case FirearmType::BOW:
                return new Firearm(10, "Bow");
            case FirearmType::GUN:
                return new Firearm(12, "Gun");
            default:
                throw std::invalid_argument("Invalid FirearmType");
        }
    }
};



#endif //TURN_BASEDGAME_SAGITTARIUS_H
