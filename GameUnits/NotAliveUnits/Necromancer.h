//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_NECROMANCER_H
#define TURN_BASEDGAME_NECROMANCER_H

#include "UndeadTypes.h"
#include "../../Weapons/Armors/Unarmored.h"
#include "UndeadCaster.h"
#include "Skeleton.h"
#include <vector>

class Necromancer : public UndeadCaster {
public:
    Necromancer();

    void attack(Unit& target) override;

    // Приема списък с мъртви живи единици (pointer-и) и връща списък с призовани скелети
    std::vector<Skeleton*> castSummonSkeletons(const std::vector<Unit*>& deadLivingUnits);

    std::string getType() const override { return "Necromancer"; }

    Unit* clone() const override {
        return new Necromancer(*this);
    }
};


#endif //TURN_BASEDGAME_NECROMANCER_H
