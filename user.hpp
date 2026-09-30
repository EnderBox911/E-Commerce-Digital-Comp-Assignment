#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include "shopItem.hpp"

using namespace std;

class User {
    public:
        // The cart will contain a vector of shop items
        vector<ShopItem> cart;
        float totalPrice = 0;

        // Class function that will display the items listed in it's cart
        void displayCart() {

            cout << "\n--- Shopping Cart ---\n";
            cout << left << setw(45) << "Name" << setw(13) << "Price" << "Total\n";
            cout << string(88, '-') << "\n";

            // Going through each element inside cart
            for (int i = 0; i < cart.size(); i++) {

                // Prints the details of the item
                cout << left << setw(45) << cart[i].itemName
                << "RM " << setw(8) << fixed << setprecision(2) << cart[i].price << endl;

                // If the end of the cart is reached, print out the total
                if (i + 1 == cart.size()) {
                    cout << right << setw(60)  << "RM " << totalPrice << endl;
                }

            }
        }

        // Function to calculate the entire cart's price
        void updateTotalPrice() {
            totalPrice = 0;
            // Going through each element inside cart and recalculating the price
            for (int i = 0; i < cart.size(); i++) {

                totalPrice += cart[i].price;

            }
        }

        // Function to add an item into the user's cart
        void addToCart(ShopItem item) {
            cart.push_back(item);

            updateTotalPrice();
        }

        void removeFromCart(ShopItem item) {
            // No need to check if item exists in cart, this function called only when it exists

            // Base item index
            int itemIndex = 0;

            // Going through each element inside cart and recalculating the price
            for (int i = 0; i < cart.size(); i++) {

                if (item.itemCode == cart[i].itemCode) {
                    itemIndex = i;
                    break;
                }

            }

            // Removes the item at that given index
            cart.erase(cart.begin() + itemIndex);

            updateTotalPrice();
        }

};