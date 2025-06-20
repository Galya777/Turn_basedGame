//
// Created by galya777 on 05.06.25.
//

#ifndef TURN_BASEDGAME_KNIGHT_H
#define TURN_BASEDGAME_KNIGHT_H

#include "LivingUnit.h"
#include "../../Weapons/Armors/HeavyArmor.h"
#include "../../Weapons/MeleeWeapon.h"

class Knight : public LivingUnit {
public:
    Knight();

    std::string getType() const override;
    Unit* clone() const override;
};

#endif //TURN_BASEDGAME_KNIGHT_H


