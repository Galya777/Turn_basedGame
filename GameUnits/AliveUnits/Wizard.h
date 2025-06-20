//
// Created by galya777 on 05.06.25.
//

#ifndef TURN_BASEDGAME_WIZARD_H
#define TURN_BASEDGAME_WIZARD_H

#include "LivingUnit.h"
#include "../../Weapons/Armors/LeatherArmor.h"
#include "../../Weapons/MeleeWeapon.h"

class Wizard : public LivingUnit {
public:
    Wizard();

    void attack(Unit& target) override;

    std::string getType() const override;
    Unit* clone() const override;
};

#endif //TURN_BASEDGAME_WIZARD_H


