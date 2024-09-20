#include "Character.h"
#include <iostream>

#ifndef __ELF_H__
#define __ELF_H__

class Elf : public Character {
    private:
        string family;
    public:
        Elf(const string &, double, double, const string &);
        const string & getFamily();
        void attack(Character &) override;
};

#endif