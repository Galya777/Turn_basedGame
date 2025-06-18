//
// Created by galya777 on 09.06.25.
//

#include "DeathKnight.h"

DeathKnight::DeathKnight(const std::string& name)
        : Comander(name, 2500, 1000, new HeavyArmor(15), 0, 150) {}

Comander* DeathKnight::clone() const {
    return new DeathKnight(*this);
}

std::string DeathKnight::getCommanderType() const {
    return "DeathKnight";
}

bool DeathKnight::canUseAbility() const {
    return mana >= 350;
}

void DeathKnight::useAbility(std::vector<Unit*>& allies,
                             std::vector<Unit*>& /*enemies*/,
                             std::vector<Unit*>& /*fallenAllies*/) {
    if (!canUseAbility()) return;

    for (Unit* ally : allies) {
        if (ally->isAlive() && ally->getType().find("Undead") != std::string::npos) {
            ally->heal(200);  // Възстановява 200 здраве на мъртвите съюзници
        }
    }
    reduceMana(350);
}

