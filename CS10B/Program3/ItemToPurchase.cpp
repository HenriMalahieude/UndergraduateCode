#include "ItemToPurchase.h"
#include <iostream>
#include <string>

using namespace std;

//Constructors
ItemToPurchase::ItemToPurchase(){
    _name = "";
    _description = "";
    _price = 0;
    _quantity = 0;
}

ItemToPurchase::ItemToPurchase(const string &name, const string &desc, const int price, const int quantity){
    _name = name;
    _description = desc;
    _price = price;
    _quantity = quantity;
}

//Mutators
void ItemToPurchase::setName(const string &newName){
    _name = newName;
}

void ItemToPurchase::setPrice(const int newPrice){
    _price = newPrice;
}

void ItemToPurchase::setQuantity(const int nQuantity){
    _quantity = nQuantity;
}

void ItemToPurchase::setDescription(const string &nDesc){
    _description = nDesc;
}

//Accessors
string ItemToPurchase::name() const{
    return _name;
}

int ItemToPurchase::price() const{
    return _price;
}

int ItemToPurchase::quantity() const{
    return _quantity;
}

string ItemToPurchase::description() const{
    return _description;
}

//Methods
void ItemToPurchase::printItemCost() const{
    cout << _name << " " << _quantity << " @ $" << _price << " = $" << (_quantity * _price) << endl;
}

void ItemToPurchase::printItemDescription() const{
    cout << _name << ": " << _description << endl;
}