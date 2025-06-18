#include <iostream>
#include "GameState.h"
#include "ConfigLoader.h"
#include "GameUnits/Basics/Unit.h"
#include "GameUnits/Comanders/Comander.h"
#include "Weapons/Armors/Armor.h"
#include "Weapons/Armors/Unarmored.h"
#include "Weapons/Armors/LeatherArmor.h"
#include "Weapons/Armors/HeavyArmor.h"
#include "Weapons/Armors/MediumArmor.h"

void printMenu() {
    std::cout << "\n=== COMMAND MENU ===\n";
    std::cout << "1. CREATE <unit_type>\n";
    std::cout << "2. SELECT BOSS <commander_name>\n";
    std::cout << "3. SELECT <unit_type> <count>\n";
    std::cout << "4. START\n";
    std::cout << "5. SAVE <filename>\n";
    std::cout << "6. LOAD <filename>\n";
    std::cout << "7. RESTART\n";
    std::cout << "8. STATUS\n";
    std::cout << "9. EXIT\n";
    std::cout << "====================\n";
}

int main() {
    GameState game;
    CommanderLoader loader;
    std::string input;
    game.reset();

    // Sample commanders (in real game use CommanderLoader::loadFromFile or similar)
    game.addLivingCommander(new Comander("Arthur", 100, 50, new Unarmored(), 300, 25));
    game.addLivingCommander(new Comander("Elena", 80, 70, new MediumArmor(60), 350, 20));
    game.addUndeadCommander(new Comander("Morgoth", 120, 60, new HeavyArmor(70), 400, 30));
    game.addUndeadCommander(new Comander("Necra", 90, 80, new LeatherArmor(80), 300, 22));


    bool running = true;
    while (running) {
        printMenu();
        std::cout << "> ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "CREATE") {
            std::string type;
            iss >> type;
            Unit* unit = loader.createUnit(type);
            if (unit) {
                game.getCurrentLivingUnits().push_back(unit);
                std::cout << type << " created.\n";
            } else {
                std::cout << "Invalid unit type.\n";
            }
        } else if (command == "SELECT") {
            std::string subcmd;
            iss >> subcmd;
            if (subcmd == "BOSS") {
                std::string name;
                iss >> name;
                bool found = false;
                for (Comander* c : game.getAvailableLivingCommanders()) {
                    if (c->getName() == name) {
                        game.setSelectedLivingCommander(c);
                        std::cout << "Selected commander: " << name << "\n";
                        found = true;
                        break;
                    }
                }
                if (!found) std::cout << "Comander not found.\n";
            } else {
                std::string unitType = subcmd;
                int count;
                iss >> count;
                for (int i = 0; i < count; ++i) {
                    Unit* unit = loader.createUnit(unitType);
                    if (unit) game.getCurrentLivingUnits().push_back(unit);
                }
                std::cout << count << " " << unitType << " units selected.\n";
            }
        } else if (command == "START") {
            game.generateRandomUndeadArmy();
            game.startDuel();
        } else if (command == "SAVE") {
            std::string filename;
            iss >> filename;
            game.saveToFile(filename);
            std::cout << "Game saved to " << filename << "\n";
        } else if (command == "LOAD") {
            std::string filename;
            iss >> filename;
            game.loadFromFile(filename);
            std::cout << "Game loaded from " << filename << "\n";
        } else if (command == "RESTART") {
            game.reset();
            std::cout << "Game restarted.\n";
        } else if (command == "STATUS") {
            std::cout << "Gold: Living = " << game.getGoldPlayer1()
                      << ", Undead = " << game.getGoldPlayer2() << "\n";
            std::cout << "Wins: Living = " << game.getWinsPlayer1()
                      << ", Undead = " << game.getWinsPlayer2() << "\n";
            std::cout << "Comander: Living = "
                      << (game.getSelectedLivingCommander() ? game.getSelectedLivingCommander()->getName() : "None") << "\n";
            std::cout << "Units: Living = " << game.getCurrentLivingUnits().size() << "\n";
        } else if (command == "EXIT") {
            std::string answer;
            std::cout << "Do you want to save the game before exiting? (yes/no): ";
            std::getline(std::cin, answer);
            if (answer == "yes") {
                std::string filename;
                std::cout << "Enter filename: ";
                std::getline(std::cin, filename);
                game.saveToFile(filename);
                std::cout << "Game saved.\n";
            }
            running = false;
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}
