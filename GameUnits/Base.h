#ifndef TURN_BASEDGAME_BASE_H
#define TURN_BASEDGAME_BASE_H

#include <vector>
#include <string>
#include <iostream>
#include "Basics/Unit.h"
#include "../UndeadFactory.h"
#include "../ConfigLoader.h"

class CommanderLoader;

class Base {
private:
    int gold;
    int unitLimit;
    int currentUnitCount;
    std::vector<Unit*> units;
    std::vector<Unit*> commanders;
    std::vector<std::pair<std::string, int>> commanderTypeCount;

    UndeadFactory* undeadFactory;

public:
    Base(int initialGold, int unitLimit, UndeadFactory* undeadFactory)
            : gold(initialGold), unitLimit(unitLimit),
              currentUnitCount(0), undeadFactory(undeadFactory) {}

    ~Base() {
        clearUnits();
        clearCommanders();
    }

    Unit* spawnUnit(Unit* prototype, bool isCommander = false) {
        if (!prototype) {
            std::cerr << "[!] Invalid prototype.\n";
            return nullptr;
        }

        if (isCommander) {
            std::string typeName = prototype->getType();
            if (getCommanderTypeCount(typeName) >= 7) {
                std::cerr << "[!] Cannot add more than 7 commanders of type: " << typeName << "\n";
                return nullptr;
            }
        } else {
            if (currentUnitCount >= unitLimit) {
                std::cerr << "[!] Unit limit reached.\n";
                return nullptr;
            }
        }

        if (gold < prototype->getGoldCost()) {
            std::cerr << "[!] Not enough gold to create unit.\n";
            return nullptr;
        }

        Unit* newUnit = prototype->clone();
        gold -= newUnit->getGoldCost();

        if (isCommander) {
            incrementCommanderTypeCount(newUnit->getType());
            commanders.push_back(newUnit);
        } else {
            units.push_back(newUnit);
            ++currentUnitCount;
        }

        std::cout << "[+] Unit created: " << newUnit->getType()
                  << (isCommander ? " (Commander)" : "") << ", gold left: " << gold << "\n";
        return newUnit;
    }

    Unit* spawnUnit(const std::string& unitTypeName, bool isCommander = false) {
        CommanderLoader loader;
        Unit* prototype = loader.createUnit(unitTypeName);
        if (!prototype) {
            std::cerr << "[!] Invalid unit type: " << unitTypeName << "\n";
            return nullptr;
        }
        return spawnUnit(prototype, isCommander);
    }

    Unit* resurrectUnit(Unit* deadUnit) {
        if (deadUnit->isAlive()) {
            std::cerr << "[!] Cannot resurrect a living unit.\n";
            return nullptr;
        }

        Unit* undead = undeadFactory->getUndeadFor(deadUnit->getType());
        if (!undead) {
            std::cerr << "[!] No undead version available for " << deadUnit->getType() << ".\n";
            return nullptr;
        }

        if (currentUnitCount >= unitLimit) {
            std::cerr << "[!] Unit limit reached. Cannot resurrect.\n";
            delete undead;
            return nullptr;
        }

        if (gold < undead->getGoldCost()) {
            std::cerr << "[!] Not enough gold to resurrect unit.\n";
            delete undead;
            return nullptr;
        }

        gold -= undead->getGoldCost();
        units.push_back(undead);
        ++currentUnitCount;

        std::cout << "[+] Unit resurrected: " << undead->getType() << ", gold left: " << gold << "\n";
        return undead;
    }

    void addGold(int amount) {
        gold += amount;
    }

    int getGold() const { return gold; }
    int getUnitLimit() const { return unitLimit; }
    int getCurrentUnitCount() const { return currentUnitCount; }

    const std::vector<Unit*>& getUnits() const { return units; }
    const std::vector<Unit*>& getCommanders() const { return commanders; }

    void clearUnits() {
        for (Unit* u : units) delete u;
        units.clear();
        currentUnitCount = 0;
    }

    void clearCommanders() {
        for (Unit* cmd : commanders) delete cmd;
        commanders.clear();
        commanderTypeCount.clear();
    }

    void recoverUnits() {
        for (auto& unit : units)
            if (unit->isAlive()) unit->heal(100);
        recoverMana(units);

        for (auto& cmd : commanders)
            if (cmd->isAlive()) cmd->heal(100);
        recoverMana(commanders);
    }

    void recoverMana(std::vector<Unit*>& unitList) {
        for (Unit* unit : unitList) {
            if (unit->isAlive() && unit->hasManaAttribute()) {
                unit->increaseMana(75);
                std::cout << "[Mana Recovery] " << unit->getType() << " +75 mana\n";
            }
        }
    }
private:
    int getCommanderTypeCount(const std::string& type) const {
        for (const auto& pair : commanderTypeCount) {
            if (pair.first == type) return pair.second;
        }
        return 0;
    }

    void incrementCommanderTypeCount(const std::string& type) {
        for (auto& pair : commanderTypeCount) {
            if (pair.first == type) {
                ++pair.second;
                return;
            }
        }
        commanderTypeCount.emplace_back(type, 1);
    }
};

#endif //TURN_BASEDGAME_BASE_H
