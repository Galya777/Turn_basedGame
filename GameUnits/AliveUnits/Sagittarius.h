//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_SAGITTARIUS_H
#define TURN_BASEDGAME_SAGITTARIUS_H

#include "LivingUnit.h"
#include "../../Weapons/Armors/MediumArmor.h"
#include "../../Weapons/Firearm.h"
#include <stdexcept>

class Sagittarius : public LivingUnit {
public:
    explicit Sagittarius(FirearmType type = FirearmType::BOW);

    std::string getType() const override;
    Unit* clone() const override;

private:
    static Weapon* createWeapon(FirearmType type);
};

#endif //TURN_BASEDGAME_SAGITTARIUS_H

