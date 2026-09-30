#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "shopLogic.hpp"

int main()
{
    int userChoice;

    do
    {
        cout << "\n=== SHOPPING SMART ASSISTANT ===\n";
        cout << "1. Browse Products\n2. Search/Filter Products\n3. Get Product Recommendation\n";
        cout << "4. Add to Cart (Akmal's Module)\n5. View Cart (Akmal's Module)\n6. Checkout (Akmal's Module)\n7. Exit\n";
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
        case 5:
        case 6:
            cout << "\n[System] Routing to Cart Module...\n";
            break;
        case 7:
            cout << "\nExiting System.\n";
            break;
        default:
            cout << "\nInvalid selection. Try again.\n";
        }
    } while (userChoice != 7);

    return 0;
}
