#include <string>

using namespace std;

#ifndef ITEMTOPURCH_H
#define ITEMTOPURCH_H
class ItemToPurchase{
    private:
        string _name;
        string _description;
        int _price;
        int _quantity;
    public:
        //Constructors
        ItemToPurchase();
        ItemToPurchase(const string&, const string&, const int, const int);
        
        //Mutators
        void setName(const string &);
        void setPrice(const int);
        void setQuantity(const int);
        void setDescription(const string &);

        //Accessors
        string name() const;
        string description() const;
        int price() const;
        int quantity() const;

        //Methods
        void printItemCost() const;
        void printItemDescription() const;
};
#endif