// Unit.h
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
    Unit(int hp, Armor* arm, int goldCos)
            : health(hp), armor(arm ? arm->clone() : nullptr), goldCost(goldCos) {}

    // Rule of 3: Копи конструктор
    Unit(const Unit& other)
            : health(other.health), armor(other.armor ? other.armor->clone() : nullptr),
            goldCost(other.goldCost){}

    // Rule of 3: Копиращо присвояване
    Unit& operator=(const Unit& other) {
        if (this != &other) {
            health = other.health;
            delete armor;
            armor = other.armor ? other.armor->clone() : nullptr;
        }
        return *this;
    }

    // Rule of 3: Деструктор
    virtual ~Unit() {
        delete armor;
    }
    [[nodiscard]] virtual Unit* clone() const = 0;
    [[nodiscard]] virtual bool hasManaAttribute() const { return false; }
    [[nodiscard]] virtual int getMana() const { return -1; }
    virtual void setMana(int m) {}
    virtual void increaseMana(int amount) {}

    // Полиморфни методи (ще се имплементират в наследници)
    virtual void attack(Unit& target) = 0;
    virtual std::string getType() const = 0;
    virtual bool isAlive() const {
        return health.getCurrent() > 0;
    }
    virtual void takeDamage(int dmg) {
        int reduced = reduceDamage(dmg);
        health.reduce(reduced);
    }
    int reduceDamage(int baseDamage) {
        if (armor && !armor->isUsable()) {
            std::cout << "Armor is destroyed!\n";
        }

        return (armor && armor->isUsable())
               ? armor->absorbDamage(baseDamage)
               : baseDamage;
    }

    virtual void heal(int amount) {
        health.heal(amount);
    }

    // Getters
    Health& getHealth() {
        return health;
    }

    const Health& getHealth() const {
        return health;
    }
    int getHP() const {
        return health.getCurrent();
    }


    int getGoldCost() const{
        return goldCost;
    }
    void setHP(int newHP) {
       health.setMax(newHP);
    }

    void setGoldCost(int newGoldCost) {
        goldCost = newGoldCost;
    }
    Armor* getArmor() const {
        return armor;
    }

    // Сетър с правилно управление на паметта
    void setArmor(Armor* newArmor) {
        if (armor != newArmor) {
            delete armor;
            armor = newArmor ? newArmor->clone() : nullptr;
        }
    }

protected:
    int goldCost;
    Health health;
    Armor* armor;
};

#endif // TURN_BASEDGAME_UNIT_H
