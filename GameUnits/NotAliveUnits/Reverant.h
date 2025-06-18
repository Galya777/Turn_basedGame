//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_REVENANT_H
#define TURN_BASEDGAME_REVENANT_H

#include "Zombi.h"

class Revenant : public Zombie {
public:
    Revenant();

    std::string getType() const override { return "Revenant"; }
    Unit* clone() const override {
        return new Revenant(*this);
    }
};

#endif // TURN_BASEDGAME_REVENANT_H

