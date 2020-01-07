/*
Supermarket checkout with special offers
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Product
{
	int id;
	string name;
	double price;
	int offer;
};
struct Cart
{
	Product product;
	int qty;
};

vector<Product> inventory;
vector<Cart> basket;
vector<Product> offer_products;

int main()
{
	
	double total = 0;
	double subtotal = 0;
	double m = 0;
	int check;
	int z = 0;
	int k = 0;
	bool flag = true;

	// load the inventory from a file
	ifstream file("inventory.dat");
	if (file.is_open())
	{
		while (!file.eof())
		{
			Product p;
			file >> p.id >> p.name >> p.price >> p.offer;
			inventory.push_back(p);
		}
		file.close();
	}

	// main interaction loop
	while (flag)
	{
		Cart c;
		z = 0;
		cout << "Enter ID (0 to print receipt): " << endl;
		cin >> check;

		if (check == 0)
		{
			flag = false;
		}
		else
		{
			// If item exists in the basket, then +1 to the qty, otherwise add to the basket.
			for (int i = 0; i < inventory.size(); i++)
			{
				if (check == inventory[i].id)
				{
					if (inventory[i].offer == 2)
					{
						offer_products.push_back(inventory[i]);
					}
					for (int q = 0; q < basket.size(); q++)
					{
						if (inventory[i].name == basket[q].product.name)
						{
							basket[q].qty += 1;
						}
						else
						{
							z = z + 1;
						}
					}
					if (z == basket.size())
					{
						c.product = inventory[i];
						c.qty = 1;
						basket.push_back(c);
					}
					// Listing items currently in the basket and computing the total
					total = 0;
					cout << "-----------ITEMS-----------" << endl;
					for (int j = 0; j < basket.size(); j++)
					{
						cout << basket[j].product.name << "   £" << basket[j].product.price << "  qty:" << basket[j].qty << endl;
						total += basket[j].qty * basket[j].product.price;
					}
					cout << " " << endl;
					cout << "Total: £" << total << endl;
					cout << "----------------------------" << endl;
				}
				else
				{
					k = k + 1;
				}
			}
			if (k == inventory.size())
			{
				cout << "ID not found." << endl;
			}
			flag = true;
			k = 0;
		}
	}

	subtotal = total;

	// output subtotal
	cout << "----------------------------" << endl;
	cout << "Subtotal: £" << subtotal << endl;
	total = 0;

	// apply "Offer 1" 3-for-2 discount; changing "qty" to "qty - floor(qty/3)" for "Offer 1" items
	for (int j = 0; j < basket.size(); j++)
	{
		if (basket[j].product.offer == 1 && basket[j].qty >= 3)
		{
			int discount = basket[j].qty / 3;
			cout << "(3 for 2: " << basket[j].product.name << " x " << discount << " free)" << endl;
			cout << "Discount: -£" << basket[j].product.price * discount << endl;
			basket[j].qty = basket[j].qty - discount;
			total += basket[j].qty * basket[j].product.price;
		}
		else
		{
			total += basket[j].qty * basket[j].product.price;
		}
	}
    
	// apply "Offer 2" 3rd item free discount on smallest "floor(q/3)" items 
	// where q=offer_products.size() is the total qty of all "Offer 2" items
	sort(offer_products.begin(), offer_products.end(), [](Product left, Product right) { return left.price < right.price; });
	for (int i = 0; i < offer_products.size() / 3; i++)
	{
		cout << "(3rd free: " << offer_products[i].name << ")" << endl;
		cout << "Discount: -£" << offer_products[i].price << endl;
		m += offer_products[i].price;
	}
	
	// output grand total
	total = total - m;   
	cout << " " << endl;
	cout << "Total: £" << total << endl;
	cout << "----------------------------" << endl;
}
