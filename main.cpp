#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "shopLogic.hpp"
#include "user.hpp"

int main()
{
    int userChoice;
    User shopper;

    do
    {
        cout << "\n=== SHOPPING SMART ASSISTANT ===\n";
        cout << "1. Browse Products\n2. Search/Filter Products\n3. Get Product Recommendation\n";
        cout << "4. Add to Cart\n5. Remove from Cart\n6. View Cart\n7. Checkout\n8. Exit\n";
        cout << "Select an option: ";

        // Prevents infinite loops if the user enters text instead of a number
        if (!(cin >> userChoice))
        {
            // make sure user type correct choice. if not, it will keep looping
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();

        switch (userChoice)
        {
        case 1:
            viewAllProducts();
            break;
        case 2:
            searchInventory();
            break;
        case 3:
            generateRecommendation();
            break;
        case 4:
            // Add to cart
            addItemToCartMenu(shopper);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 5:
            // Remove from cart
            removeItemFromCartMenu(shopper);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 6:
            // View cart
            shopper.displayCart();
            break;
        case 7:
            // Checkout
            cout << "\n[System] Routing to Cart Module...\n";
            break;
        case 8:
            // Exit
            cout << "\nExiting System.\n";
            break;
        default:
            cout << "\nInvalid selection. Try again.\n";
        }

        if (userChoice >= 1 && userChoice <= 7)
        {
            cout << "\nPress Enter to return to the main menu...";
            cin.get();
            clearScreen(); // Clears display and navigate to main menu
        }
    } while (userChoice != 8);

    return 0;
}
