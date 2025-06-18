//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_GUL_H
#define TURN_BASEDGAME_GUL_H

#include "UndeadTypes.h"
#include "../../Weapons/Armors/HeavyArmor.h"

class Gul : public PureUndead {
public:
    Gul();

    void attack(Unit& target) override;

    std::string getType() const override { return "Gul"; }

    Unit* clone() const override {
        return new Gul(*this);
    }
};


#endif //TURN_BASEDGAME_GUL_H
