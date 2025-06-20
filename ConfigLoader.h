#ifndef TURN_BASEDGAME_COMMANDERLOADER_H
#define TURN_BASEDGAME_COMMANDERLOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "GameUnits/AliveUnits/LivingUnit.h"
#include "GameUnits/NotAliveUnits/UnlivingUnit.h"
#include "GameUnits/Comanders/Comander.h"
#include "GameUnits/AliveUnits/Infantryman.h"
#include "GameUnits/AliveUnits/Sagittarius.h"
#include "GameUnits/AliveUnits/Knight.h"
#include "GameUnits/AliveUnits/Healer.h"
#include "GameUnits/AliveUnits/Wizard.h"
#include "GameUnits/NotAliveUnits/Skeleton.h"
#include "GameUnits/NotAliveUnits/Gul.h"
#include "GameUnits/NotAliveUnits/Necromancer.h"
#include "GameUnits/NotAliveUnits/Zombi.h"
#include "GameUnits/NotAliveUnits/Dibbuk.h"
#include "GameUnits/NotAliveUnits/Reverant.h"
#include "GameUnits/NotAliveUnits/Ghost.h"
#include "GameUnits/Comanders/Litch.h"
#include "GameUnits/Comanders/DreadLord.h"
#include "GameUnits/Comanders/DeathKnight.h"
#include "GameUnits/Comanders/UndeadHunter.h"
#include "GameUnits/Comanders/DancerWithBlades.h"
#include "GameUnits/Comanders/Paladin.h"

#include "Weapons/Armors/LeatherArmor.h"
#include "Weapons/Armors/MediumArmor.h"
#include "Weapons/Armors/HeavyArmor.h"
#include "Weapons/Armors/Unarmored.h"

class CommanderLoader {
private:
    std::vector<Comander*> livingCommanders;
    std::vector<Comander*> undeadCommanders;
public:
    Armor* createArmor(const std::string& name) {
        if (name == "Unarmored") {
            Unarmored armor;
            return armor.clone();
        } else if (name == "Leather") {
            LeatherArmor armor(3);
            return armor.clone();
        } else if (name == "Medium") {
            MediumArmor armor(8);
            return armor.clone();
        } else if (name == "Heavy") {
            HeavyArmor armor(10);
            return armor.clone();
        } else {
            std::cerr << "[!] Unknown armor name: " << name << ", using Unarmored.\n";
            Unarmored armor;
            return armor.clone();
        }
    }

    Unit* createUnit(const std::string& unitType, bool isCommander = false) {
        if (isCommander) {
            // Създава командир по име (тук можеш да разшириш с още имена)
            if (unitType == "Lich") return new Lich("Lich");
            else if (unitType == "DeathLord") return new DreadLord("DeathLord");
            else if (unitType == "DeadKnight") return new DeathKnight("DeadKnight");
            else if (unitType == "UndeadHunter") return new UndeadHunter("UndeadHunter");
            else if (unitType == "Bladedancer") return new DancerWithBlades("Bladedancer");
            else if (unitType == "Paladin") return new Paladin("Paladin");
            else {
                std::cerr << "[!] Unknown commander type: " << unitType << "\n";
                return nullptr;
            }
        } else {
            if (unitType == "Infantry") {
                Infantryman unit;
                return unit.clone();
            } else if (unitType == "Archer") {
                Sagittarius unit;
                return unit.clone();
            } else if (unitType == "Knight") {
                Knight unit;
                return unit.clone();
            } else if (unitType == "Healer") {
                Healer unit;
                return unit.clone();
            } else if (unitType == "Wizard") {
                Wizard unit;
                return unit.clone();
            } else if (unitType == "Skeleton") {
                Skeleton unit;
                return unit.clone();
            } else if (unitType == "Gul") {
                Gul unit;
                return unit.clone();
            } else if (unitType == "Necromancer") {
                Necromancer unit;
                return unit.clone();
            } else if (unitType == "Zombi") {
                Zombie unit;
                return unit.clone();
            } else if (unitType == "Dibbuk") {
                Dibbuk unit;
                return unit.clone();
            } else if (unitType == "Reverant") {
                Revenant unit;
                return unit.clone();
            } else if (unitType == "Ghost") {
                Ghost unit;
                return unit.clone();
            } else {
                std::cerr << "[!] Unknown unit type: " << unitType << "\n";
                return nullptr;
            }
        }
    }

    void assignUnitsToCommander(Comander* commander, const std::vector<std::string>& unitTypes) {
        for (const auto& unitType : unitTypes) {
            Unit* unit = createUnit(unitType);
            if (unit) commander->addUnit(unit);
        }
    }

    bool commanderNameExists(const std::string& name) {
        for (const auto* c : livingCommanders)
            if (c->getName() == name) return true;
        for (const auto* c : undeadCommanders)
            if (c->getName() == name) return true;
        return false;
    }

    ~CommanderLoader() {
        for (auto* c : livingCommanders) delete c;
        for (auto* c : undeadCommanders) delete c;
    }

    void parseCommanderLine(const std::string& line, bool isLiving) {
        std::istringstream ss(line);
        std::string name, armorName, unitListStr;
        int hp = 0, mana = 0, gold = 0;

        std::getline(ss, name, ',');
        ss >> hp; ss.ignore();
        ss >> mana; ss.ignore();
        ss >> gold; ss.ignore();
        std::getline(ss, armorName, ',');
        std::getline(ss, unitListStr);

        if (commanderNameExists(name)) {
            std::cerr << "[!] Comander already exists: " << name << "\n";
            return;
        }

        Armor* armor = createArmor(armorName);
        Comander* commander = nullptr;

        // Специални командири
        if (name == "Lich") commander = new Lich(name);
        else if (name == "DeathLord") commander = new DreadLord(name);
        else if (name == "DeadKnight") commander = new DeathKnight(name);
        else if (name == "UndeadHunter") commander = new UndeadHunter(name);
        else if (name == "Bladedancer") commander = new DancerWithBlades(name);
        else if (name == "Paladin") commander = new Paladin(name);
        else commander = new Comander(name, hp, mana, armor, gold, 0);

        // Раздели units
        std::vector<std::string> unitTypes;
        std::istringstream unitSS(unitListStr);
        std::string unit;
        while (std::getline(unitSS, unit, ';')) {
            unitTypes.push_back(unit);
        }

        assignUnitsToCommander(commander, unitTypes);

        if (isLiving) livingCommanders.push_back(commander);
        else undeadCommanders.push_back(commander);
    }

    void loadCommandersFromFile(const std::string& filename, bool isLiving) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[!] Could not open commander file: " << filename << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty())
                parseCommanderLine(line, isLiving);
        }
    }

    const std::vector<Comander*>& getLivingCommanders() const { return livingCommanders; }
    const std::vector<Comander*>& getUndeadCommanders() const { return undeadCommanders; }
};

#endif //TURN_BASEDGAME_COMMANDERLOADER_H
