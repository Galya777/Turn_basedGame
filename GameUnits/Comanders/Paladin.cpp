//
// Created by galya777 on 09.06.25.
//

#include "Paladin.h"

Paladin::Paladin(const std::string& name)
        : Comander(name, 5000, 3000, new HeavyArmor(20), 0, 250) {}

Comander* Paladin::clone() const {
    return new Paladin(*this);
}

std::string Paladin::getCommanderType() const {
    return "Paladin";
}

bool Paladin::canUseAbility() const {
    return mana >= 500;
}

void Paladin::useAbility(std::vector<Unit*>& allies,
                         std::vector<Unit*>&,
                         std::vector<Unit*>&) {
    if (!canUseAbility()) return;


    for (Unit* ally : allies) {
        if (ally->isAlive() && ally->getHealth().getCurrent() < 5000) { // условна стойност
            ally->heal(500);  // възстанови здраве
            reduceMana(500);
            break;
        }
    }
}
