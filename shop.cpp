#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "shopItem.hpp"

using namespace std;

// Central database storing 15 products across 5 categories
vector<ShopItem> inventoryDB = {
    // Electronics gadgets
    {"E01", "Retro Bluetooth Cassette Player", "Electronics", 185.00, 4.6},
    {"E02", "Smart Ring Health Tracker", "Electronics", 450.00, 4.3},
    {"E03", "Holographic Projection Clock", "Electronics", 210.00, 4.8},

    // Gaming accessories
    {"G01", "RGB Arcade Fight Stick", "Gaming", 320.00, 4.7},
    {"G02", "Mobile Gaming Thumb Sleeves", "Gaming", 12.50, 4.9},
    {"G03", "Haptic Feedback Gaming Vest", "Gaming", 899.00, 4.4},

    // Fashion stuffs
    {"F01", "Techwear Cargo Pants", "Fashion", 145.00, 4.5},
    {"F02", "UV-Reactive Color-Changing Tee", "Fashion", 55.00, 4.2},
    {"F03", "LED Cyberpunk Visor Glasses", "Fashion", 35.00, 4.6},
    {"F04", "Eco-friendly Tote Bag", "Fashion", 25.00, 4.7},
    {"F05", "Waterproof Tactical Windbreaker", "Fashion", 180.00, 4.8},
    {"F06", "Modular Crossbody Chest Rig", "Fashion", 68.00, 4.4},
    {"F07", "Reflective Neon Accent Hoodie", "Fashion", 89.00, 4.3},
    {"F08", "Magnetic Buckle Utility Belt", "Fashion", 32.00, 4.5},

    // Home related items
    {"H01", "Magnetic Levitating Moon Lamp", "Home", 125.00, 4.8},
    {"H02", "Smart Soil Moisture Sensor", "Home", 45.00, 4.1},
    {"H03", "Automatic Self-Stirring Mug", "Home", 28.00, 4.4},

    // Study items
    {"S01", "Pomodoro Productivity Timer Cube", "Study", 38.00, 4.7},
    {"S02", "Posture Correction Back Brace", "Study", 65.00, 4.3},
    {"S03", "E-ink Distraction-Free Tablet", "Study", 950.00, 4.9},
    {"S04", "Digital Drawing Tablet", "Study", 1250.00, 4.8},
    {"S05", "Ergonomic Mechanical Number Pad", "Study", 89.00, 4.6},
    {"S06", "Smart LED Desk Lamp with Wireless Charger", "Study", 115.00, 4.7}};

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

// utility function to print a single item in a formatted table row
void displayAllItems(const ShopItem &item)
{
    cout << left << setw(6) << item.itemCode
         << setw(45) << item.itemName
         << setw(15) << item.category
         << "RM " << setw(8) << fixed << setprecision(2) << item.price
         << item.userRating << " Stars\n";
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
