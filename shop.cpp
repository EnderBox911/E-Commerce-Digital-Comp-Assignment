#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// Struct to hold individual product details
struct ShopItem {
    string itemCode;
    string itemName;
    string category;
    double price;
    double userRating;
};

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
    {"S06", "Smart LED Desk Lamp with Wireless Charger", "Study", 115.00, 4.7}
};

// Utility function to print a single item in a formatted table row
void displayItem(const ShopItem& item) {
    cout << left << setw(5) << item.itemCode 
         << setw(30) << item.itemName 
         << setw(15) << item.category 
         << "RM " << setw(8) << fixed << setprecision(2) << item.price 
         << item.userRating << " Stars\n";
}

int main() {
    int userChoice;
    
    do {
        cout << "\n=== SHOPPING SMART ASSISTANT ===\n";
        cout << "1. Browse Products\n2. Search/Filter Products\n3. Get Product Recommendation\n";
        cout << "4. Add to Cart (Akmal's Module)\n5. View Cart (Akmal's Module)\n6. Checkout (Akmal's Module)\n7. Exit\n";
        cout << "Select an option: ";
        
        // Prevents infinite loops if the user enters text instead of a number
        if (!(cin >> userChoice)) {
            //make sure user type correct choice. if not, it will keep looping
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (userChoice) {
            case 1: cout << "[Pending Browse Module]\n"; break;
            case 2: cout << "[Pending Search Module]\n"; break;
            case 3: cout << "[Pending Recommendation Module]\n"; break;
            case 4: case 5: case 6: cout << "\n[System] Routing to Cart Module...\n"; break;
            case 7: cout << "\nExiting System.\n"; break;
            default: cout << "\nInvalid selection. Try again.\n";
        }
    } while (userChoice != 7);
    
    return 0;
}
