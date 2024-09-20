#include <string>
#include <vector>
#include <iostream>
#include "ShoppingCart.h"

using namespace std;

//Constructors
ShoppingCart::ShoppingCart(){
    _customerName = "none";
    _currentDate = "January 1, 2016";
}

ShoppingCart::ShoppingCart(const string &cName, const string &cDate){
    _customerName = cName;
    _currentDate = cDate;
}

//Mutators
void ShoppingCart::addItem(ItemToPurchase &nItem){
    _cartItems.push_back(nItem);
}

void ShoppingCart::removeItem(const string &oItem){
    for (unsigned i = 0; i < _cartItems.size(); i++){
        if (_cartItems.at(i).name() == oItem){
            cout << endl;
            _cartItems.erase(_cartItems.begin() + i);
            return;
        }
    }
    cout << "Item not found in cart. Nothing removed." << endl << endl;
}

void ShoppingCart::modifyItem(const ItemToPurchase &mItem){
    for (unsigned i = 0; i < _cartItems.size(); i++){
        if (_cartItems.at(i).name() == mItem.name()){
            ItemToPurchase &cItem = _cartItems.at(i);

            if (mItem.quantity() != 0){
                cItem.setQuantity(mItem.quantity());
            }

            if (mItem.price() != 0){
                cItem.setPrice(mItem.price());
            }
            
            if (mItem.description() != ""){
                cItem.setDescription(mItem.description());
            }

            return;
        }
    }
    cout << "Item not found in cart. Nothing modified." << endl << endl;
}

//Accessors
string ShoppingCart::customerName() const{
    return _customerName;
}

string ShoppingCart::date() const{
    return _currentDate;
}

int ShoppingCart::numItemsInCart() const{
    int am = 0;

    for (unsigned i = 0; i < _cartItems.size(); i++){
        ItemToPurchase it = _cartItems.at(i);
        am += it.quantity();
    }

    return am;
}

int ShoppingCart::costOfCart() const{
    int sum = 0;

    for (unsigned i = 0; i < _cartItems.size(); i++){
        ItemToPurchase it = _cartItems.at(i);
        sum += it.quantity() * it.price();
    }

    return sum;
}

//Methods
void ShoppingCart::printTotal() const{
    cout << _customerName << "'s Shopping Cart - " << _currentDate << endl;
    cout << "Number of Items: " << numItemsInCart() << endl << endl;

    if (numItemsInCart() > 0){
        for (unsigned i = 0; i < _cartItems.size(); i++){
            _cartItems.at(i).printItemCost();
        }
    }else{
        cout << "SHOPPING CART IS EMPTY" << endl;
    }

    cout << endl << "Total: $" << costOfCart() << endl << endl;
}

void ShoppingCart::printDescriptions() const{
    cout << _customerName << "'s Shopping Cart - " << _currentDate << endl;
    cout << endl << "Item Descriptions" << endl;

    for (unsigned i = 0; i < _cartItems.size(); i++){
        _cartItems.at(i).printItemDescription();
    }
    cout << endl;
}