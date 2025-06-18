//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_UNDEADUNIT_H
#define TURN_BASEDGAME_UNDEADUNIT_H

#include "UnlivingUnit.h"


class PureUndead : public UndeadUnit {
public:
    PureUndead(int hp, Armor* arm, int goldCost) : UndeadUnit(hp, arm, goldCost) {}

    void attack(Unit& target) override=0;
    [[nodiscard]] std::string getType() const override { return "Pure Undead"; }
};

class RaisedUndead : public UndeadUnit {
public:
    RaisedUndead(int hp, Armor* arm, int goldCost) : UndeadUnit(hp, arm, goldCost) {}

    void attack(Unit& target) override=0;
    [[nodiscard]] std::string getType() const override { return "Raised Undead"; }
};



#endif //TURN_BASEDGAME_UNDEADUNIT_H
