//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_SKELETON_H
#define TURN_BASEDGAME_SKELETON_H

#include "UndeadTypes.h"
#include "../../Weapons/Armors/MediumArmor.h"

class Skeleton : public PureUndead {
public:
    Skeleton();

    Unit* clone() const override {
        return new Skeleton(*this);
    }

    void attack(Unit& target) override;

    std::string getType() const override { return "Skeleton"; }
};

#endif // TURN_BASEDGAME_SKELETON_H

