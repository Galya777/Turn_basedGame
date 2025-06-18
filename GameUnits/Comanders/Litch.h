//
// Created by galya777 on 09.06.25.
//

// LichCommander.h
#ifndef TURN_BASEDGAME_LICHCOMMANDER_H
#define TURN_BASEDGAME_LICHCOMMANDER_H

#include "Comander.h"
#include "../NotAliveUnits/Skeleton.h"
#include "../../Weapons/Armors/HeavyArmor.h"

class Lich : public Comander {
public:
    static bool hasRaisedThisTurn; // Контролира дали е въздигано вече

    Lich(const std::string& name)
            : Comander(name, 1500, 1000, new HeavyArmor(15), 500, 100) {}
    Unit* clone() const override {
        return new Lich(*this);
    }

    void useAbility(std::vector<Unit*>& allies,
                    std::vector<Unit*>& /*enemies*/,
                    std::vector<Unit*>& fallenAllies) override {
        if (mana >= 750 && !hasRaisedThisTurn && !fallenAllies.empty()) {
            for (Unit* fallen : fallenAllies) {
                std::string type = fallen->getType();
                if (type == "Human" || type == "Healer" || type == "Paladin") {
                    // Въздигане като нов немъртъв юнит – напр. Skeleton
                    allies.push_back(new Skeleton());
                } else {
                    // Ако вече е undead – можем да го възстановим
                    allies.push_back(fallen->clone());
                }
            }
            reduceMana(750);
            hasRaisedThisTurn = true;
            fallenAllies.clear();
        }
    }


    bool canUseAbility() const override {
        return mana >= 750 && !hasRaisedThisTurn;
    }

    std::string getCommanderType() const override {
        return "Lich";
    }
};



#endif // TURN_BASEDGAME_LICHCOMMANDER_H

