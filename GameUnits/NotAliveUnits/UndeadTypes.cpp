//
// Created by galya777 on 11.05.25.
//

#include "UndeadTypes.h"
#include <iostream>

PureUndead::PureUndead(int hp, Armor* arm, int goldCost)
        : UndeadUnit(hp, arm, goldCost) {}

std::string PureUndead::getType() const {
    return "Pure Undead";
}

RaisedUndead::RaisedUndead(int hp, Armor* arm, int goldCost)
        : UndeadUnit(hp, arm, goldCost) {}

std::string RaisedUndead::getType() const {
    return "Raised Undead";
}




