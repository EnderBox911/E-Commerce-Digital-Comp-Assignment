#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include "shopItem.hpp"
#include "user.hpp"

using namespace std;

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Utility function to print a single item in a formatted table row
void displayItem(const ShopItem &item)
{
    cout << left << setw(6) << item.itemCode
         << setw(45) << item.itemName
         << setw(15) << item.category
         << "RM " << setw(8) << fixed << setprecision(2) << item.price
         << item.userRating << " Stars\n";
}

// an utility that used for converting strings to lowercase for case-insensitive matching
string convertToLower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


// Option 1: Show all product if user choose first option
void viewAllProducts()
{
    cout << "\n--- Full Product Listing ---\n";
    cout << left << setw(6) << "ID" << setw(45) << "Name" << setw(15) << "Category" << setw(13) << "Price" << "Rating\n";
    cout << string(88, '-') << "\n";
    for (const auto &item : inventoryDB)
    {
        displayItem(item);
    }
}

// fuzzy matching: Levenshtein distance calculation for fuzzy search logic
int calculateEditDistance(const string &s1, const string &s2)
{
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    return dp[m][n];
}

// Option 2: Case-insensitive search matching against item names or categories
// Search matching against item names or categories with fuzzy fallback
void searchInventory()
{
    string query;
    cout << "\nEnter product name or category to search: ";
    getline(cin, query);

    string lowerQuery = convertToLower(query);
    bool isFound = false;

    cout << "\n--- Search Results ---\n";
    cout << left << setw(6) << "ID" 
         << setw(45) << "Name" 
         << setw(15) << "Category" 
         << setw(13) << "Price" 
         << "Rating\n";
    cout << string(88, '-') << "\n";

    // Pass 1: Substring search
    for (const auto &item : inventoryDB)
    {
        if (convertToLower(item.itemName).find(lowerQuery) != string::npos ||
            convertToLower(item.category).find(lowerQuery) != string::npos)
        {
            displayItem(item);
            isFound = true;
        }
    }

    // Pass 2: Fuzzy fallback for misspellings
    if (!isFound)
    {
        cout << "[No direct match found. Checking for closely related items...]\n\n";

        for (const auto &item : inventoryDB)
        {
            bool matchThisItem = false;

            // Check similarity with category
            if (calculateEditDistance(lowerQuery, convertToLower(item.category)) <= 2) {
                matchThisItem = true;
            }

            // Check similarity against individual words in item name
            string word = "";
            string lowerName = convertToLower(item.itemName);
            for (char ch : lowerName) {
                if (ch == ' ') {
                    if (!word.empty() && calculateEditDistance(lowerQuery, word) <= 2) {
                        matchThisItem = true;
                        break;
                    }
                    word = "";
                } else {
                    word += ch;
                }
            }
            if (!word.empty() && calculateEditDistance(lowerQuery, word) <= 2) {
                matchThisItem = true;
            }

            if (matchThisItem) {
                displayItem(item);
                isFound = true;
            }
        }
    }

    if (!isFound)
    {
        cout << "No products found matching or closely resembling '" << query << "'.\n";
    }
}

// Option 3: Recommendation logic based on category, max budget, and rating
void generateRecommendation() {
    int catChoice;
    string targetCategory;
    double maxSpend;

    cout << "\n--- Smart Shopping Assistant ---\n";
    cout << "Select Preferred Category:\n";
    cout << "1. Electronics\n";
    cout << "2. Gaming\n";
    cout << "3. Fashion\n";
    cout << "4. Home\n";
    cout << "5. Study\n";
    
    // Category selection loop with input validation
    while (true) {
        cout << "Enter your choice (1-5): ";
        if (cin >> catChoice && catChoice >= 1 && catChoice <=5) {
            break;
        }
        cout << "Invalid selection! Please enter a number between 1 and 5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Map choice to corresponding category string
    switch (catChoice) {
        case 1: targetCategory = "electronics"; break;
        case 2: targetCategory = "gaming"; break;
        case 3: targetCategory = "fashion"; break;
        case 4: targetCategory = "home"; break;
        case 5: targetCategory = "study"; break;
    }
    
    cout << "Enter maximum budget (RM): ";
    while (!(cin >> maxSpend) || maxSpend < 0) {
        cout << "Invalid budget. Please enter a valid positive number: RM ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    clearScreen();

    bool isFound = false;
    cout << "\n--- Recommended for You (Rating >= 4.5 & Under Budget) ---\n";
    cout << left << setw(6) << "ID" 
         << setw(45) << "Name" 
         << setw(15) << "Category" 
         << setw(13) << "Price" 
         << "Rating\n";
    cout << string(88, '-') << "\n";

    for (const auto &item : inventoryDB) {
        // parameters algorithmic filter
        if (convertToLower(item.category) == targetCategory && 
            item.price <= maxSpend && 
            item.userRating >= 4.5) {
            displayItem(item);
            isFound = true;
        }
    }
    
    if (!isFound) {
        cout << "No highly-rated products match your criteria. Try resetting your budget or category.\n";
    }
}

ShopItem checkIfItemExist() {
    string itemCode;
    ShopItem item;
    int itemIndex;
    bool itemExists = false;
    bool running = true;

    do {
        cout << "Please enter the Product ID (case-sensitive) or \"X\" to return to the menu: ";
        cin >> itemCode;

        // Stop the function if user selected to stop
        if (itemCode == "X" || itemCode == "x") {
            running = false;

        } else {
            // Continue with program otherwise

            // Checking if item code exists in the database
            for (int i = 0; i < inventoryDB.size(); i++) {
                if (inventoryDB[i].itemCode == itemCode) {
                    itemExists = true;
                    itemIndex = i;
                }
            }

            // Inform the user if the item doesn't exist
            if (!itemExists) {
                cout << "That item code is invalid! Please enter a correct code or \"X\" to return to the menu\n";
            } else {
                // Item exists in the database
                item = inventoryDB[itemIndex];
                return item;
            }

        }

    } while (!itemExists && running);

    if (!running) {
        // Code so that the program can know if the user was the one who stopped it
        item = {"User stopped", "", "", 0.0, 0.0};
    }

    return item;
}

// Menu to facilitate the user's add to cart function
void addItemToCartMenu(User &shopper) {
    ShopItem item = checkIfItemExist();

    if (item.itemCode == "User stopped") {
        // Quit and return to menu
        return;
    } else {
        cout << "Adding item: " << item.itemName << " to the cart!\n";
        shopper.addToCart(item);
    }
}

void removeItemFromCartMenu(User &shopper) {
    ShopItem item = checkIfItemExist();

    if (item.itemCode == "User stopped") {
        // Quit and return to menu
        return;
    } else {
        cout << "Removing item: " << item.itemName << " from the cart!\n";
        shopper.removeFromCart(item);
    }
}

void checkoutMenu(User &shopper, vector<string> couponCodes, int discountAmount) {
    string couponCode;
    bool couponExists = false;
    bool exitCouponCheck = false;

    float deliverCharge = 15.0;

    do {
        cout << "Please enter your coupon code, enter \"X\" if you do not wish to: ";
        cin >> couponCode;

        if (couponCode == "X" or couponCode == "x") {
            // User selected to not input coupon
            exitCouponCheck = true;
            // Sets the discount percentage as nothing
            shopper.discountPercentage = 0;
        } else {
            // Code was provided
            for (int i = 0; i < couponCodes.size(); i++) {
                // Checks if the code is valid
                if (couponCode == couponCodes[i]) {
                    cout << "Coupon exists! You get " << discountAmount << "\% off!\n";
                    // Set the discount percentage as the set value
                    shopper.discountPercentage = discountAmount;
                    couponExists = true;
                    break;
                }
            }

            if (!couponExists) {
                cout << "That coupon doesn't exist!\n";
            }
        }

    } while (!couponExists && !exitCouponCheck);

    // Show the current shopping cart
    shopper.displayCart();

    // Display the delivery charges
    cout << string(88, '-') << "\n";
    cout << left << "Delivery Charge "  
    << right << setw(66) << fixed << setprecision(2) << "RM " << deliverCharge << endl;

    // Display the discount provided
    float discountTotal = (shopper.subtotal + deliverCharge) * (static_cast<float>(shopper.discountPercentage)/100);
    cout << left << "Discount " 
    << right << setw(73) << fixed << setprecision(2) << "RM " << discountTotal << endl;

    
    // Display the total price including delivery and discount
    shopper.totalPrice = max(static_cast<double>(shopper.subtotal + deliverCharge - discountTotal), 0.0);
    cout << string(88, '-') << "\n";
    cout << left << "Total " 
    << right << setw(76) << fixed << setprecision(2) << "RM " << shopper.totalPrice << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
}