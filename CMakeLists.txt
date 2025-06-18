cmake_minimum_required(VERSION 3.31)
project(Turn_basedGame)

set(CMAKE_CXX_STANDARD 20)

# Добавяме всички нужни .cpp файлове тук
add_executable(Turn_basedGame
        main.cpp

        # Основни класове
        GameState.cpp
        ConfigLoader.cpp
        Base.cpp
        UndeadFactory.cpp

        # Базови единици
        GameUnits/Basics/Unit.cpp

        # Живи единици
        GameUnits/AliveUnits/LivingUnit.cpp
        GameUnits/AliveUnits/Infantryman.cpp
        GameUnits/AliveUnits/Sagittarius.cpp
        GameUnits/AliveUnits/Wizard.cpp
        GameUnits/AliveUnits/Healer.cpp

        # Немъртви единици
        GameUnits/NotAliveUnits/UndeadTypes.cpp
        GameUnits/NotAliveUnits/Zombi.cpp
        GameUnits/NotAliveUnits/Skeleton.cpp
        GameUnits/NotAliveUnits/Gul.cpp
        GameUnits/NotAliveUnits/Necromancer.cpp
        GameUnits/NotAliveUnits/Reverant.cpp
        GameUnits/NotAliveUnits/UndeadCaster.cpp
        GameUnits/NotAliveUnits/Dibbuk.cpp
        GameUnits/NotAliveUnits/Ghost.cpp
        GameUnits/NotAliveUnits/UnlivingUnit.cpp

        # Командири
        GameUnits/Comanders/Comander.cpp
        GameUnits/Comanders/DancerWithBlades.cpp
        GameUnits/Comanders/DeathKnight.cpp
        GameUnits/Comanders/DreadLord.cpp
        GameUnits/Comanders/Litch.cpp
        GameUnits/Comanders/Paladin.cpp
        GameUnits/Comanders/UndeadHunter.cpp


        # Оръжия и брони
        Weapons/Armors/Armor.cpp
        Weapons/Armors/HeavyArmor.cpp
        Weapons/Armors/LeatherArmor.cpp
        Weapons/Armors/MediumArmor.cpp
        Weapons/Armors/Unarmored.cpp
        Weapons/Ability.cpp
        Weapons/Firearm.cpp
        Weapons/Health.cpp
        Weapons/MeleeWeapon.cpp
        Weapons/Weapon.cpp

)

