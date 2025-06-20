//
// Created by galya777 on 09.06.25.
//

#ifndef TURN_BASEDGAME_DREADLORD_H
#define TURN_BASEDGAME_DREADLORD_H

#include "Comander.h"
#include "../NotAliveUnits/Necromancer.h"
#include "../NotAliveUnits/Gul.h"
#include "../../Weapons/Armors/HeavyArmor.h"
#include <vector>
#include <string>

class DreadLord : public Comander {
public:
    explicit DreadLord(const std::string& name);

    std::string getCommanderType() const override;
    bool canUseAbility() const override;
    void useAbility(std::vector<Unit*>& allies,
                    std::vector<Unit*>& enemies,
                    std::vector<Unit*>& fallenAllies) override;

    Unit* clone() const override;
};

#endif //TURN_BASEDGAME_DREADLORD_H

