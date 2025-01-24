#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Class to represent a product
class Product {
public:
    int id;
    string name;
    double price;
    int quantity;

    Product(int pId, string pName, double pPrice, int pQuantity)
        : id(pId), name(pName), price(pPrice), quantity(pQuantity) {}
};

// Class to manage inventory
class Inventory {
private:
    vector<Product> products;

public:
    void addProduct(int id, string name, double price, int quantity) {
        products.push_back(Product(id, name, price, quantity));
        cout << "Product added successfully!" << endl;
    }

    void viewInventory() {
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (const auto& product : products) {
            cout << setw(10) << product.id << setw(20) << product.name << setw(10) << product.price << setw(10) << product.quantity << endl;
        }
    }

    bool updateStock(int id, int quantity) {
        for (auto& product : products) {
            if (product.id == id) {
                product.quantity += quantity;
                cout << "Stock updated successfully!" << endl;
                return true;
            }
        }
        cout << "Product not found!" << endl;
        return false;
    }

    Product* findProduct(int id) {
        for (auto& product : products) {
            if (product.id == id) return &product;
        }
        return nullptr;
    }
};

// Class to represent a sale transaction
class Sale {
public:
    int productId;
    int quantity;
    double totalAmount;

    Sale(int pId, int qty, double total)
        : productId(pId), quantity(qty), totalAmount(total) {}
};

// Class to manage sales and POS
class POS {
private:
    vector<Sale> sales;
    Inventory& inventory;

public:
    POS(Inventory& inv) : inventory(inv) {}

    void processSale(int productId, int quantity) {
        Product* product = inventory.findProduct(productId);
        if (product && product->quantity >= quantity) {
            double total = product->price * quantity;
            sales.push_back(Sale(productId, quantity, total));
            product->quantity -= quantity;
            cout << "Sale processed! Total amount: $" << total << endl;
        } else {
            cout << "Product not available or insufficient stock!" << endl;
        }
    }

    void viewSales() {
        cout << setw(10) << "Product ID" << setw(10) << "Quantity" << setw(10) << "Total Amount" << endl;
        for (const auto& sale : sales) {
            cout << setw(10) << sale.productId << setw(10) << sale.quantity << setw(10) << sale.totalAmount << endl;
        }
    }
};

// Main function
int main() {
    Inventory inventory;
    POS pos(inventory);

    int choice;
    do {
        cout << "\n--- Store Management System ---" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. View Inventory" << endl;
        cout << "3. Update Stock" << endl;
        cout << "4. Process Sale" << endl;
        cout << "5. View Sales" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, quantity;
                double price;
                string name;
                cout << "Enter product ID: ";
                cin >> id;
                cout << "Enter product name: ";
                cin >> ws;  // consume any trailing newline
                getline(cin, name);
                cout << "Enter product price: ";
                cin >> price;
                cout << "Enter product quantity: ";
                cin >> quantity;
                inventory.addProduct(id, name, price, quantity);
                break;
            }
            case 2:
                inventory.viewInventory();
                break;
            case 3: {
                int id, quantity;
                cout << "Enter product ID: ";
                cin >> id;
                cout << "Enter quantity to update: ";
                cin >> quantity;
                inventory.updateStock(id, quantity);
                break;
            }
            case 4: {
                int productId, quantity;
                cout << "Enter product ID: ";
                cin >> productId;
                cout << "Enter quantity: ";
                cin >> quantity;
                pos.processSale(productId, quantity);
                break;
            }
            case 5:
                pos.viewSales();
                break;
            case 0:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
