#include <string>
#include <vector>
#include "ItemToPurchase.h"

using namespace std;

#ifndef SHOPPCART_H
#define SHOPPCART_H

class ShoppingCart{
    private:
        string _customerName;
        string _currentDate;
        vector<ItemToPurchase> _cartItems;
    public:
        //Constructors
        ShoppingCart();
        ShoppingCart(const string&, const string&);

        //Mutators
        void addItem(ItemToPurchase&);
        void removeItem(const string&);
        void modifyItem(const ItemToPurchase&); 

        //Accessors
        string customerName() const;
        string date() const;        
        int numItemsInCart() const;
        int costOfCart() const;

        //Methods
        void printTotal() const;
        void printDescriptions() const;
};

#endif