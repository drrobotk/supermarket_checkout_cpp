Supermarket Checkout
=====================

C++ program implementing a supermarket checkout which calculates the total price of a number of items with special offers.

Items are stored with their unit price in inventory.dat (sample file given) in the following format: (columns seperated by tabs)

<product id (int)> <product name (string)>  <product price (double)>  <product offer (int)>

The product offer codes are given by:
- '0' for "none"
- '1' for "buy 3 identical items and pay for 2"
- '2' for "buy 3 (in a set of items) and the cheapest is free"

This program was tested and compiled on GCC (Ubuntu), Visual Studio (Windows) and https://www.onlinegdb.com/online_c++_compiler.

Once started, the program prompts the user to enter the item codes to add items to the basket.
If the item already exists in the basket, it increases the qty value by +1, otherwise it adds a new item.

The output appears as:

```
-----------ITEMS-----------
Name    Price    Quantity

Total:
----------------------------
```

After all the items are added the user enters '0' to checkout, apply any discounts and print the receipt with output:

```
----------------------------
Subtotal:
(Offer)
Discount:

Total:
----------------------------
```

