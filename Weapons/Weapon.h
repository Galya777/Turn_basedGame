//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_WEAPON_H
#define TURN_BASEDGAME_WEAPON_H



#pragma once
#include <string>

class Weapon {
public:
    virtual ~Weapon() = default;
    virtual int getDamage() const = 0;
    virtual std::string getName() const = 0;
};



#endif //TURN_BASEDGAME_WEAPON_H
