//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_FIREARM_H
#define TURN_BASEDGAME_FIREARM_H


// Firearm.h
#pragma once
#include "Weapon.h"
enum class FirearmType {
    BOW,
    GUN,
    CROSSBOW,
    MUSKET,
    FLINTLOCK,
    RIFLE
};

class Firearm : public Weapon {
public:
    Firearm(int dmg, std::string n) : damage(dmg), name(std::move(n)) {}

    int getDamage() const override { return damage; }
    std::string getName() const override { return name; }

private:
    int damage;
    std::string name;
};



#endif //TURN_BASEDGAME_FIREARM_H
