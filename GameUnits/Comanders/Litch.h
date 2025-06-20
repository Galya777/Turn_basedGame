//
// Created by galya777 on 09.06.25.
//

#ifndef TURN_BASEDGAME_LICHCOMMANDER_H
#define TURN_BASEDGAME_LICHCOMMANDER_H

#include "Comander.h"
#include "../NotAliveUnits/Skeleton.h"
#include "../../Weapons/Armors/HeavyArmor.h"

class Lich : public Comander {
public:
    static bool hasRaisedThisTurn;

    explicit Lich(const std::string& name);

    Unit* clone() const override;
    void useAbility(std::vector<Unit*>& allies,
                    std::vector<Unit*>& enemies,
                    std::vector<Unit*>& fallenAllies) override;

    bool canUseAbility() const override;
    std::string getCommanderType() const override;
};

#endif // TURN_BASEDGAME_LICHCOMMANDER_H


