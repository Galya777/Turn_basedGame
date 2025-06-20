//
// Created by galya777 on 09.06.25.
//

#include "DreadLord.h"

DreadLord::DreadLord(const std::string& name)
        : Comander(name, 3000, 2000, new HeavyArmor(20), 300, 200) {}

std::string DreadLord::getCommanderType() const {
    return "DreadLord";
}

bool DreadLord::canUseAbility() const {
    return mana >= 400; // Най-малката цена за призоваване
}

void DreadLord::useAbility(std::vector<Unit*>& allies,
                           std::vector<Unit*>& /* enemies */,
                           std::vector<Unit*>& /* fallenAllies */) {
    if (mana >= 900) {
        allies.push_back(new Necromancer());
        allies.push_back(new Gul());
        reduceMana(900);
    } else if (mana >= 500) {
        allies.push_back(new Gul());
        reduceMana(500);
    } else if (mana >= 400) {
        allies.push_back(new Necromancer());
        reduceMana(400);
    }
}

Unit* DreadLord::clone() const {
    return new DreadLord(*this);
}

