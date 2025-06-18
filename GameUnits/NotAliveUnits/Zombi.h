//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_ZOMBIE_H
#define TURN_BASEDGAME_ZOMBIE_H

#include "UndeadTypes.h"
#include "../../Weapons/Armors/Unarmored.h"

class Zombie : public RaisedUndead {
public:
    Zombie();
    Unit* clone() const override {
        return new Zombie(*this);
    }
    void attack(Unit& target) override;

    std::string getType() const override { return "Zombie"; }
};

#endif // TURN_BASEDGAME_ZOMBIE_H

