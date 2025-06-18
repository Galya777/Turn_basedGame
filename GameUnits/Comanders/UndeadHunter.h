//
// Created by galya777 on 09.06.25.
//

#ifndef TURN_BASEDGAME_UNDEADHUNTER_H
#define TURN_BASEDGAME_UNDEADHUNTER_H

#include "Comander.h"
#include "../../Weapons/Armors/HeavyArmor.h"

class UndeadHunter : public Comander {
public:
    UndeadHunter(const std::string& name);

    Comander* clone() const override;

    std::string getCommanderType() const override;

    bool canUseAbility() const override;

    void useAbility(std::vector<Unit*>& allies,
                    std::vector<Unit*>& enemies,
                    std::vector<Unit*>& fallenAllies) override;
};


#endif //TURN_BASEDGAME_UNDEADHUNTER_H

