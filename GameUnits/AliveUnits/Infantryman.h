//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_INFANTRYMAN_H
#define TURN_BASEDGAME_INFANTRYMAN_H

#include "../../Weapons/Armors/MediumArmor.h"
#include "../../Weapons/MeleeWeapon.h"
#include "LivingUnit.h"

class Infantryman : public LivingUnit {
public:
    Infantryman();

    std::string getType() const override;

    Unit* clone() const override;
};

#endif //TURN_BASEDGAME_INFANTRYMAN_H

