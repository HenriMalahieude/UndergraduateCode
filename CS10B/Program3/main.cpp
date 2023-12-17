#include <iostream>
#include <string>
#include "ItemToPurchase.h"
#include "ShoppingCart.h"

using namespace std;

void promptForInfo(string, string &);
void printMenu(ShoppingCart &);

int main(){
    string customersName, dateSet;

    promptForInfo("Enter customer's name: ", customersName);
    promptForInfo("Enter today's date: ", dateSet);

    cout << endl << "Customer name: " << customersName << endl;
    cout << "Today's date: " << dateSet << endl << endl;

    ShoppingCart cart = ShoppingCart(customersName, dateSet);

    printMenu(cart);

    return 0;
}

void promptForInfo(string prompt, string &var){
    cout << prompt;
    getline(cin, var);
    cout << endl;
}

void promptForInfo(string prompt, int &var){
    cout << prompt;
    cin >> var;
    cout << endl;
}

void printMenu(ShoppingCart &cart){
    char option = 'z';
    //char dummy = ' ';
    bool stop = false;

    cout << "MENU" << endl;
    cout << "a - Add item to cart" << endl;
    cout << "d - Remove item from cart" << endl;
    cout << "c - Change item quantity" << endl;
    cout << "i - Output items' descriptions" << endl;
    cout << "o - Output shopping cart" << endl;
    cout << "q - Quit" << endl << endl;

    while (true){
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore(1000, '\n');
        cout << endl;

        if (option == 'q'){
            stop = true;
            break;
        }else if (option == 'o'){
            cout << endl << "OUTPUT SHOPPING CART" << endl;
            cart.printTotal();
            break;
        }else if (option == 'i'){
            cout << "OUTPUT ITEMS' DESCRIPTIONS" << endl;
            cart.printDescriptions();
            break;
        }else if (option == 'a'){
            string itemName, itemDesc;
            int quant, pri;
            cout << endl << "ADD ITEM TO CART" << endl;
            promptForInfo("Enter the item name: ", itemName);
            promptForInfo("Enter the item description: ", itemDesc);
            promptForInfo("Enter the item price: ", pri);
            promptForInfo("Enter the item quantity: ", quant);
            cout << endl;
            //cout << itemName << endl << itemDesc << endl << pri << endl << quant << endl;

            ItemToPurchase nItem = ItemToPurchase(itemName, itemDesc, pri, quant);
            cart.addItem(nItem);
            break;
        }else if (option == 'd'){
            string itemName;
            cout << "REMOVE ITEM FROM CART" << endl;
            promptForInfo("Enter name of item to remove: ", itemName);
            //cout << endl;
            cart.removeItem(itemName);
            break;
        }else if (option == 'c'){
            string itemName;
            int quantity;
            cout << endl << "CHANGE ITEM QUANTITY" << endl;

            promptForInfo("Enter the item name: ", itemName);
            promptForInfo("Enter the new quantity: ", quantity);
            ItemToPurchase mItem = ItemToPurchase(itemName, "", 0, quantity);
            cart.modifyItem(mItem);
            break;
        }
    }
    if (!stop){
        printMenu(cart); //recursive functions are sufferable
    }
}