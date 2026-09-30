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