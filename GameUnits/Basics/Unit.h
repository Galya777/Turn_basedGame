#ifndef TURN_BASEDGAME_UNIT_H
#define TURN_BASEDGAME_UNIT_H

#include <string>
#include <iostream>
#include "../../Weapons/Health.h"
#include "../../Weapons/Armors/Armor.h"
#include "../../Weapons/Ability.h"

class Armor;
class Ability;

class Unit {
public:
    Unit(int hp, Armor* arm, int goldCost);
    Unit(const Unit& other);
    Unit& operator=(const Unit& other);
    virtual ~Unit();

    [[nodiscard]] virtual Unit* clone() const = 0;
    [[nodiscard]] virtual bool hasManaAttribute() const { return false; }
    [[nodiscard]] virtual int getMana() const { return -1; }
    virtual void setMana(int m) {}
    virtual void increaseMana(int amount) {}

    virtual void attack(Unit& target) = 0;
    virtual std::string getType() const = 0;
    virtual bool isAlive() const;
    virtual void takeDamage(int dmg);
    virtual void heal(int amount);

    // Getters
    Health& getHealth();
    const Health& getHealth() const;
    int getHP() const;
    int getGoldCost() const;
    Armor* getArmor() const;

    // Setters
    void setHP(int newHP);
    void setGoldCost(int newGoldCost);
    void setArmor(Armor* newArmor);

protected:
    int reduceDamage(int baseDamage);

protected:
    int goldCost;
    Health health;
    Armor* armor;
};

#endif // TURN_BASEDGAME_UNIT_H
