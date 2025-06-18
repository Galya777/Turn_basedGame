//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_INFANTRYMAN_H
#define TURN_BASEDGAME_INFANTRYMAN_H

#pragma once

#include "../../Weapons/Armors/MediumArmor.h"
#include "../../Weapons/MeleeWeapon.h"
#include "LivingUnit.h"

class Infantryman : public LivingUnit {
public:
    Infantryman()
            : LivingUnit(
            420,                                   // Health
            new MediumArmor( 8),// Armor with durability 8
            250,                                   // Gold cost
            new MeleeWeapon(7, "Sword")            // Melee weapon with damage 7
    ) {}

    std::string getType() const override { return "Infantryman"; }
    Unit* clone() const override {
        return new Infantryman(*this);
    }
};

#endif //TURN_BASEDGAME_INFANTRYMAN_H
