#include "Character.h"
#include <iostream>

//Character::Character(){}

Character::Character(HeroType typ, const string &nam, double hp, double aStrength) : type(typ), name(nam), health(hp), attackStrength(aStrength){}

HeroType Character::getType() const{
    return type;
}

const string& Character::getName() const{
    return name;
}

int Character::getHealth() const{
    return health;
}

void Character::damage(double d){
    cout << name << " takes " << d << " damage." << endl;
    health -= d;
}

bool Character::isAlive() const{
    return health > 0.0;
}