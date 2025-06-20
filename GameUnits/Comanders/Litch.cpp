//
// Created by galya777 on 09.06.25.
//

#include "Litch.h"

bool Lich::hasRaisedThisTurn = false;

Lich::Lich(const std::string& name)
        : Comander(name, 1500, 1000, new HeavyArmor(15), 500, 100) {}

Unit* Lich::clone() const {
    return new Lich(*this);
}

void Lich::useAbility(std::vector<Unit*>& allies,
                      std::vector<Unit*>& /*enemies*/,
                      std::vector<Unit*>& fallenAllies) {
    if (mana >= 750 && !hasRaisedThisTurn && !fallenAllies.empty()) {
        for (Unit* fallen : fallenAllies) {
            std::string type = fallen->getType();
            if (type == "Human" || type == "Healer" || type == "Paladin") {
                allies.push_back(new Skeleton());
            } else {
                allies.push_back(fallen->clone());
            }
        }
        reduceMana(750);
        hasRaisedThisTurn = true;
        fallenAllies.clear();
    }
}

bool Lich::canUseAbility() const {
    return mana >= 750 && !hasRaisedThisTurn;
}

std::string Lich::getCommanderType() const {
    return "Lich";
}
