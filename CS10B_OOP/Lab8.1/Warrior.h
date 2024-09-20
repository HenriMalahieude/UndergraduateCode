#include "Character.h"
#include <iostream>

#ifndef __WARRIOR_H__
#define __WARRIOR_H__

class Warrior : public Character {
    private:
        string allegiance;
    public:
        Warrior(const string &, double, double, const string &);
        const string & getAllegiance();
        void attack(Character &);
};

#endif