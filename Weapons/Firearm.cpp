//
// Created by galya777 on 11.05.25.
//

#include "Firearm.h"

Firearm* createFirearm(FirearmType type) {
    switch (type) {
        case FirearmType::BOW:
            return new Firearm(10, "Bow");
        case FirearmType::CROSSBOW:
            return new Firearm(12, "Crossbow");
        case FirearmType::MUSKET:
            return new Firearm(14, "Musket");
        case FirearmType::FLINTLOCK:
            return new Firearm(13, "Flintlock");
        case FirearmType::RIFLE:
            return new Firearm(16, "Rifle");
        default:
            return new Firearm(10, "Bow");
    }
}
