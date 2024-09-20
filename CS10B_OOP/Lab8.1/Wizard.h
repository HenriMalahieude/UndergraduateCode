#include "Character.h"
#include <iostream>

#ifndef __WIZARD_H__
#define __WIZARD_H__

class Wizard : public Character {
    private:
        int rank;
    public:
        Wizard(const string &, double, double, int);
        int getRank();
        void attack(Character &) override;
};

#endif