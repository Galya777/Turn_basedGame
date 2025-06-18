//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_ABILITY_H
#define TURN_BASEDGAME_ABILITY_H


#pragma once
#include "../GameUnits/Basics/Unit.h"

class Unit;

class Ability {
public:
    virtual ~Ability() = default;
    virtual void use(Unit& user, Unit& target) = 0;
};



#endif //TURN_BASEDGAME_ABILITY_H
