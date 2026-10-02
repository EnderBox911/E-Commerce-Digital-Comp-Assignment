# Shopping Smart Assistant

A console-based e-commerce shopping assistant written in C++. Users can browse a product catalogue, search with typo tolerance, get budget-based recommendations, manage a shopping cart and check out with a coupon and a payment method.

This repository also contains our group research on how Shopee disrupted e-commerce in Southeast Asia (see [`impact_research.md`](impact_research.md)).

## Features

| Menu option | What it does |
|---|---|
| **1. Browse Products** | Lists all 22 products across 5 categories (Electronics, Gaming, Fashion, Home, Study) with ID, name, category, price and rating. |
| **2. Search / Filter Products** | Case-insensitive search by product name or category. If nothing matches, a fuzzy fallback (Levenshtein edit distance of 2 or less) suggests close matches, so small typos still work. |
| **3. Get Product Recommendation** | Choose a category and a maximum budget (RM). Shows only products within budget that have a rating of **4.5 or higher**. |
| **4. Add to Cart** | Add an item by Product ID (for example `H04`). IDs are case-sensitive; enter `X` to go back. |
| **5. Remove from Cart** | Remove an item by Product ID. |
| **6. View Cart** | Shows the items in the cart and the subtotal. |
| **7. Checkout** | Apply an optional coupon (15% off), add the RM 15.00 delivery charge, then pay by cash or card. |
| **8. Exit** | Quit the program. |

### Checkout details

- **Coupons:** a valid code gives 15% off the subtotal plus delivery. Codes are defined in `main.cpp`. Enter `X` to skip.
- **Cash:** the amount must cover the total, and change is calculated.
- **Card:** validates a 16-digit card number, an expiry date in `MM/YY` format and a 3-digit CVV. It only checks the format; no real payment is made and no card data is stored.
- The cart is cleared after a successful payment.

## Project structure

```
.
├── main.cpp            # Main menu loop and program entry point
├── shopItem.hpp        # ShopItem struct and the product database (inventoryDB)
├── shopLogic.hpp       # Browse, search, recommendation, cart and checkout logic
├── user.hpp            # User class: cart, subtotal, discount and total
├── impact_research.md  # Shopee impact and market research
└── README.md
```

## Getting started

### Requirements

- A C++ compiler with C++11 support or later (g++, clang++ or MSVC)
- Windows, macOS or Linux (the screen is cleared with `cls` or `clear` depending on the OS)

### Build and run

```bash
g++ -std=c++17 main.cpp -o shop
./shop          # on Windows: .\shop.exe
```

## Example session

```
=== SHOPPING SMART ASSISTANT ===
1. Browse Products
2. Search/Filter Products
3. Get Product Recommendation
4. Add to Cart
5. Remove from Cart
6. View Cart
7. Checkout
8. Exit
Select an option:
```

Try: `2` then `flip clock` to search, or `3` then category `4` (Home) with a budget of `200` to see recommendations.

## Adding a product

Open `shopItem.hpp` and add a new line to `inventoryDB` in this format:

```cpp
{"H04", "Vintage Flip Clock", "Home", 85.00, 4.5},
// {code, name, category, price in RM, rating out of 5}
```

The product then appears automatically in browsing, search, recommendations, the cart and checkout. Use one of the existing category names (`Electronics`, `Gaming`, `Fashion`, `Home`, `Study`) so that recommendations can find it.

## Research

`impact_research.md` covers Shopee's impact on consumers, sellers and SMEs, existing retailers and competitors, and the wider digital-commerce ecosystem. It supports our Christensen Disruptive Innovation poster.
