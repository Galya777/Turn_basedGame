#ifndef TURN_BASEDGAME_COMMANDER_H
#define TURN_BASEDGAME_COMMANDER_H

#include "../Basics/Unit.h"
#include <string>
#include <utility>
#include <vector>

class Base;

class Comander : public Unit {
protected:
    std::string name;
    int mana;
    int attackPower;
    std::vector<Unit*> controlledUnits;
    Base* base = nullptr;

public:
    Comander(std::string  name, int hp, int mana, Armor* armor, int goldCost, int attackPower)
            : Unit(hp, armor, goldCost), name(std::move(name)), mana(mana), attackPower(attackPower), base(nullptr) {}

    Comander(const Comander& other)
            : Unit(other), name(other.name), mana(other.mana), attackPower(other.attackPower), base(other.base) {
        for (const auto& unit : other.controlledUnits) {
            controlledUnits.push_back(unit->clone());
        }
    }

    Comander& operator=(const Comander& other) {
        if (this != &other) {
            Unit::operator=(other);
            name = other.name;
            mana = other.mana;
            attackPower = other.attackPower;
            base = other.base;

            for (auto* unit : controlledUnits) {
                delete unit;
            }
            controlledUnits.clear();

            for (const auto& unit : other.controlledUnits) {
                controlledUnits.push_back(unit->clone());
            }
        }
        return *this;
    }

    virtual void useAbility(std::vector<Unit*>& allies,
                            std::vector<Unit*>& enemies,
                            std::vector<Unit*>& fallenAllies) {
        // По подразбиране няма способност — override при нужда
    }

    [[nodiscard]] const std::string& getName() const { return name; }

    virtual std::string getCommanderType() const {
        return "Comander";
    }

    [[nodiscard]] int getMana() const { return mana; }

    void reduceMana(int amount) {
        mana = std::max(0, mana - amount);
    }

    void increaseMana(int amount) {
        mana += amount;
    }

    int getAttackPower() const { return attackPower; }

    virtual bool canUseAbility() const {
        return false;
    }

    void attack(Unit& target) override {
        target.takeDamage(attackPower);
    }

    std::string getType() const override {
        return getCommanderType();
    }

    virtual Unit* clone() const override {
        return new Comander(*this);
    }

    void addUnit(Unit* unit) {
        if (unit) {
            controlledUnits.push_back(unit->clone());
        }
    }

    [[nodiscard]] const std::vector<Unit*>& getControlledUnits() const {
        return controlledUnits;
    }

    // 🔧 Нови методи:
    void setBase(Base* b) { base = b; }
    [[nodiscard]] Base* getBase() const { return base; }

    ~Comander() override {
        for (auto* unit : controlledUnits) {
            delete unit;
        }
        controlledUnits.clear();
    }

    [[nodiscard]] std::string serialize() const;
    static Comander* deserialize(const std::string& data);
};

#endif //TURN_BASEDGAME_COMMANDER_H
