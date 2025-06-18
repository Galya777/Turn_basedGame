//
// Created by galya777 on 05.06.25.
//

// Knight.h
#ifndef TURN_BASEDGAME_KNIGHT_H
#define TURN_BASEDGAME_KNIGHT_H

#include "LivingUnit.h"
#include "../../Weapons/Armors/HeavyArmor.h"
#include "../../Weapons/MeleeWeapon.h"

class Knight : public LivingUnit {
public:
    Knight()
            : LivingUnit(
            835,
            new HeavyArmor(10),
            700,
            new MeleeWeapon(45, "Sword")
    ) {}

    std::string getType() const override { return "Knight"; }
    Unit* clone() const override {
        return new Knight(*this);
    }
};

#endif //TURN_BASEDGAME_KNIGHT_H

