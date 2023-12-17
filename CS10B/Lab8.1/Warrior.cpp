#include "Warrior.h"

Warrior::Warrior(const string &name, double health, double attackStrength, const string &allegiance) : Character(WARRIOR, name, health, attackStrength){
    this->allegiance = allegiance;
}

const string& Warrior::getAllegiance(){
    return allegiance;
}

void Warrior::attack(Character &opponent){
    //cout << "Warrior vs " << opponent.getType() << endl;
    if (opponent.getType() != WARRIOR || dynamic_cast<Warrior &>(opponent).getAllegiance() != allegiance){
        cout << "Warrior " << name << " attacks " << opponent.getName() << " --- SLASH!!" << endl; 
        double damage = (health / MAX_HEALTH) * attackStrength;
        opponent.damage(damage);
    }else{
        cout << "Warrior " << name << " does not attack Warrior " << opponent.getName() << "." << endl;
        cout << "They share an allegiance with " << allegiance << "." << endl;
    }
}