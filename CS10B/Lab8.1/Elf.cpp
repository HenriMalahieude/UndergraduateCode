#include "Elf.h"

Elf::Elf(const string &name, double health, double attackStrength, const string &family) : Character(ELF, name, health, attackStrength) {
    this->family = family;
}

const string& Elf::getFamily(){
    return family;
}

void Elf::attack(Character &opponent){
    //cout << "Elf vs " << opponent.getType() << endl;
    if (opponent.getType() != ELF || dynamic_cast<Elf &>(opponent).getFamily() != family){
        cout << "Elf " << name << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl; 
        double damage = (health / MAX_HEALTH) * attackStrength;
        opponent.damage(damage);
    }else{
        cout << "Elf " << name << " does not attack Elf " << opponent.getName() << "." << endl;
        cout << "They are both members of the " << family << " family." << endl;
    }
}