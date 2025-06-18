#include "Armor.h"
#include <ostream>
Armor::Armor(ArmorType type, int durability)
        : type(type), durability(durability) {}

void Armor::degrade() {
    if (durability > 0)
        --durability;
}

bool Armor::isUsable() const {
    return durability > 0;
}

int Armor::reduceDamage(int dmg) {
    if (!isUsable()) return dmg;

    float factor = getReductionFactor();  // взимаме колко % от удара да се намали
    int reduced = static_cast<int>(dmg * (1.0f - factor));
    return reduced;
}

int Armor::absorbDamage(int dmg) {
    int result = reduceDamage(dmg);
    if (isUsable()) {
        onHit();    // специално поведение при удар (наследник го имплементира)
        degrade();  // намалява durability
    }
    return result;
}

int Armor::getDurability() const {
    return durability;
}

ArmorType Armor::getType() const {
    return type;
}

