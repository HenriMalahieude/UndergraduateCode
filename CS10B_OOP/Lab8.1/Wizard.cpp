#include "Wizard.h"

Wizard::Wizard(const string &name, double health, double attackStrength, int rank) : Character(WIZARD, name, health, attackStrength) {
    this->rank = rank;
}

int Wizard::getRank(){
    return rank;
}

void Wizard::attack(Character &opponent){
    cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl; 
    double ratio = 1;
    if (opponent.getType() == WIZARD){
        ratio = (double)rank / dynamic_cast<Wizard &>(opponent).getRank();
    }

    double damage = attackStrength * ratio;
    opponent.damage(damage);
}