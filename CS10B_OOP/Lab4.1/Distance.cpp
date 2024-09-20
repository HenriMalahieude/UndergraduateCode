#include <iostream>
#include <cmath>
#include "Distance.h"

Distance::Distance(){
    feet = 0;
    inches = 0;
}

Distance::Distance(unsigned ft, double in){
    feet = ft;
    inches = in;
    init();
}

Distance::Distance(double in){
    feet = 0;
    inches = in;
    init();
}

unsigned Distance::getFeet() const{
    return feet;
}

double Distance::getInches() const{
    return inches;
}

double Distance::distanceInInches() const{
    return (double)(feet * 12) + inches;
}

double Distance::distanceInFeet() const{
    return (double)(feet) + (inches / 12.0);
}

double Distance::distanceInMeters() const{
    return this->distanceInInches() * 0.0254;
}

Distance Distance::operator+(const Distance &rhs) const{
    double lhs_inches = distanceInInches();
    double rhs_inches = rhs.distanceInInches();

    return Distance(lhs_inches + rhs_inches);
}

Distance Distance::operator-(const Distance &rhs) const{
    double lhs_inches = distanceInInches();
    double rhs_inches = rhs.distanceInInches();

    return Distance(lhs_inches - rhs_inches);
}

ostream& operator<<(ostream &out, const Distance &rhs){
    return out << rhs.feet << "' " << rhs.inches << "\"";
}

void Distance::init(){
    double t_inches = abs((double)(feet * 12)) + abs(inches);
    feet = t_inches / 12;
    inches = fmod(t_inches, 12);
    return;
}