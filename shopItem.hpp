#pragma once
#include <string>

using namespace std;

// Struct to hold individual product details
struct ShopItem
{
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
    {"E04", "Wireless Presenter Remote", "Electronics", 45.00, 4.6},

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
    {"H04", "Vintage Vlip Clock", "Home", 85.00, 4.5},
    
    // Study items
    {"S01", "Pomodoro Productivity Timer Cube", "Study", 38.00, 4.7},
    {"S02", "Posture Correction Back Brace", "Study", 65.00, 4.3},
    {"S03", "E-ink Distraction-Free Tablet", "Study", 950.00, 4.9},
    {"S04", "Digital Drawing Tablet", "Study", 1250.00, 4.8},
    {"S05", "Ergonomic Mechanical Number Pad", "Study", 89.00, 4.6},
    {"S06", "Smart LED Desk Lamp with Wireless Charger", "Study", 115.00, 4.7}};
