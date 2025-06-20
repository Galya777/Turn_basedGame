//
// Created by galya777 on 05.06.25.
//

#ifndef TURN_BASEDGAME_HEALER_H
#define TURN_BASEDGAME_HEALER_H

#include "LivingUnit.h"
#include "../../Weapons/MeleeWeapon.h"
#include "../../Weapons/Armors/Unarmored.h"
#include <stdexcept>

class Healer : public LivingUnit {
public:
    Healer();

    std::string getType() const override;

    void heal(LivingUnit& target);

    Unit* clone() const override;
};

#endif //TURN_BASEDGAME_HEALER_H


