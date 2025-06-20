#include "Comander.h"
#include "../../Weapons/Armors/LeatherArmor.h"
#include "../../Weapons/Armors/MediumArmor.h"
#include "../../Weapons/Armors/HeavyArmor.h"
#include "../../Weapons/Armors/Unarmored.h"
#include "../../UndeadFactory.h"
#include <sstream>
#include "../Base.h"

// Създаване на броня по име
Armor* createArmorFromName(const std::string& name) {
    if (name == "LEATHER") return new LeatherArmor(50);
    if (name == "MEDIUM") return new MediumArmor(30);
    if (name == "HEAVY") return new HeavyArmor(70);
    return new Unarmored(); // Default
}

std::ostream& operator<<(std::ostream& os, ArmorType type) {
    switch (type) {
        case ArmorType::UNARMORED: return os << "UNARMORED";
        case ArmorType::LEATHER:   return os << "LEATHER";
        case ArmorType::MEDIUM:    return os << "MEDIUM";
        case ArmorType::HEAVY:     return os << "HEAVY";
        default:                   return os << "UNKNOWN";
    }
}

// Сериализация
std::string Comander::serialize() const {
    std::ostringstream out;
    // Тук можеш да сложиш логика за faction, ако я имаш, иначе hardcoded:
    char factionChar = 'L'; // примерно

    out << factionChar << '|'
        << name << ','
        << getHP() << ','
        << mana << ',';

    // Създаваме стринг за бронята с параметър
    if (armor) {
        ArmorType type = armor->getType();
        int armorVal = armor->getDurability(); // трябва да имаш getValue() или подобен метод
        switch (type) {
            case ArmorType::LEATHER: out << "LeatherArmor(" << armorVal << ")"; break;
            case ArmorType::MEDIUM: out << "MediumArmor(" << armorVal << ")"; break;
            case ArmorType::HEAVY: out << "HeavyArmor(" << armorVal << ")"; break;
            default: out << "Unarmored"; break;
        }
    } else {
        out << "Unarmored";
    }

    out << ',' << goldCost << ',' << attackPower;

    return out.str();
}

// deserialize - приема ред с формат:
// L|Arthur,100,50,MediumArmor(30),300,25
// И връща нов Comander*, създаден с фабрика и пълнен с данните от реда
Comander* Comander::deserialize(const std::string& line) {
    if (line.empty() || line[0] == '#') return nullptr;

    std::vector<std::string> tokens;
    std::istringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() != 7) {
        std::cerr << "Invalid field count (expected 7, got " << tokens.size() << "): " << line << "\n";
        return nullptr;
    }

    std::string typeName = tokens[0];
    std::string name     = tokens[1];

    int hp, mana, attackPower, goldCost;
    try {
        hp          = std::stoi(tokens[2]);
        mana        = std::stoi(tokens[3]);
        attackPower = std::stoi(tokens[4]);
        goldCost    = std::stoi(tokens[5]);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing integers: " << e.what() << " in line: " << line << "\n";
        return nullptr;
    }

    std::string armorStr = tokens[6];
    Armor* armor = createArmorFromName(armorStr);

    UndeadFactory* factory = new UndeadFactory();
    Base* base = new Base(1000, 100, factory);

    Unit* commanderUnit = base->spawnUnit(typeName, true);
    Comander* cmd = dynamic_cast<Comander*>(commanderUnit);


    if (!cmd) {
        std::cerr << "[!] Unknown unit type: " << typeName << "\n";
        delete base;
        delete factory;
        delete armor;
        return nullptr;
    }

    cmd->name = name;
    cmd->setHP(hp);
    cmd->mana = mana;
    cmd->attackPower = attackPower;
    cmd->goldCost = goldCost;
    cmd->armor = armor;
    cmd->base = base;

    return cmd;
}






