//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_MELEEWEAPON_H
#define TURN_BASEDGAME_MELEEWEAPON_H


#include "Weapon.h"

class MeleeWeapon : public Weapon {
public:
    MeleeWeapon(int dmg, const std::string& name)
            : damage(dmg), weaponName(name) {}

    int getDamage() const override { return damage; }
    std::string getName() const override { return weaponName; }

private:
    int damage;
    std::string weaponName;
};

#endif //TURN_BASEDGAME_MELEEWEAPON_H
