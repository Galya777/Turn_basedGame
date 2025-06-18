//
// Created by galya777 on 09.06.25.
//

// DreadLord.h
#ifndef TURN_BASEDGAME_DREADLORD_H
#define TURN_BASEDGAME_DREADLORD_H

#include "Comander.h"
#include "../NotAliveUnits/Necromancer.h"
#include "../NotAliveUnits/Gul.h"
#include "../../Weapons/Armors/HeavyArmor.h"

class DreadLord : public Comander {
public:
    DreadLord(const std::string& name)
            : Comander(name, 3000, 2000, new HeavyArmor(20), 300, 200) {}

    std::string getCommanderType() const override {
        return "DreadLord";
    }

    bool canUseAbility() const override {
        return mana >= 400; // Най-малката цена за призоваване
    }

    void useAbility(std::vector<Unit*>& allies,
                    std::vector<Unit*>& /* enemies */,
                    std::vector<Unit*>& /* fallenAllies */) override {
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

    Unit* clone() const override {
        return new DreadLord(*this);
    }
};

#endif //TURN_BASEDGAME_DREADLORD_H
