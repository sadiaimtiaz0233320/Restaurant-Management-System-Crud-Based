#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Structure for menu items
struct MenuItem {
    string name;
    float price;
};

// Function declarations
void clearScreen();
void changeColor(int screen);
void displayMenu(MenuItem menu[], int size);
void addMenuItem(MenuItem menu[], int &size);
void updateMenuItem(MenuItem menu[], int size);
void deleteMenuItem(MenuItem menu[], int &size);
void takeOrder(MenuItem menu[], int size);
float calculateBill(MenuItem menu[], int orderQty[], int size, string paymentMethod, float* tax);
void thankYouMessage();

int main() {
    const int MAX_SIZE = 20;

    MenuItem menu[MAX_SIZE] = {
        {"Margherita Pizza", 1500},
        {"Cheeseburger", 1000},
        {"Grilled Chicken", 1200},
        {"Pasta Alfredo", 1250},
        {"Veggie Wrap", 700},
        {"Loaded Fries", 500},
        {"French Fries", 200},
        {"Lava Cake", 950},
        {"Iced Tea", 450},
        {"Coffee", 400},
        {"Chocolate Brownie", 800},
        {"Chicken Wings", 1100}
    };

    int size = 12;
    int choice;

    while (true) {
        clearScreen();
        changeColor(1);

        cout << "======= RSZ RESTAURANT CRUD MENU =======\n";
        cout << "1. View Menu\n2. Add Item\n3. Update Item\n4. Delete Item\n5. Order Food\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                clearScreen();
                changeColor(2);
                displayMenu(menu, size);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;

            case 2:
                clearScreen();
                changeColor(3);
                addMenuItem(menu, size);
                break;

            case 3:
                clearScreen();
                changeColor(4);
                updateMenuItem(menu, size);
                break;

            case 4:
                clearScreen();
                changeColor(5);
                deleteMenuItem(menu, size);
                break;

            case 5:
                clearScreen();
                changeColor(6);
                takeOrder(menu, size);
                break;

            case 6:
                thankYouMessage();
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void changeColor(int screen) {
#ifdef _WIN32
    switch(screen) {
        case 1: system("color 1F"); break;
        case 2: system("color 2F"); break;
        case 3: system("color 3F"); break;
        case 4: system("color 4F"); break;
        case 5: system("color 5F"); break;
        case 6: system("color 6F"); break;
        default: system("color 0F");
    }
#endif
}

void displayMenu(MenuItem menu[], int size) {
    cout << "*** MENU ***\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << menu[i].name << " - Rs" << menu[i].price << endl;
    }
}

void addMenuItem(MenuItem menu[], int &size) {
    cin.ignore();
    cout << "Enter item name: ";
    getline(cin, menu[size].name);

    cout << "Enter item price: ";
    cin >> menu[size].price;

    size++;
    cout << "Item added!\n";
    cin.get(); cin.get();
}

void updateMenuItem(MenuItem menu[], int size) {
    displayMenu(menu, size);

    int num;
    cout << "Enter item number: ";
    cin >> num;

    cin.ignore();
    cout << "New name: ";
    getline(cin, menu[num-1].name);

    cout << "New price: ";
    cin >> menu[num-1].price;

    cout << "Updated!\n";
    cin.get(); cin.get();
}

void deleteMenuItem(MenuItem menu[], int &size) {
    displayMenu(menu, size);

    int num;
    cout << "Enter item number: ";
    cin >> num;

    for(int i = num-1; i < size-1; i++) {
        menu[i] = menu[i+1];
    }

    size--;
    cout << "Deleted!\n";
    cin.get(); cin.get();
}

void takeOrder(MenuItem menu[], int size) {
    int orderQty[20] = {0};
    int choice, qty;

    while(true) {
        displayMenu(menu, size);

        cout << "Enter item number (0 to finish): ";
        cin >> choice;

        if(choice == 0) break;

        cout << "Quantity: ";
        cin >> qty;

        orderQty[choice-1] += qty;
    }

    string payment;
    cout << "Payment (cash/card): ";
    cin >> payment;

    float tax = 0;
    float total = calculateBill(menu, orderQty, size, payment, &tax);

    cout << "Tax: " << tax << "\nTotal: " << total << endl;

    cin.get(); cin.get();
}

float calculateBill(MenuItem menu[], int orderQty[], int size, string payment, float* tax) {
    float subtotal = 0;

    for(int i=0; i<size; i++) {
        subtotal += menu[i].price * orderQty[i];
    }

    if(payment == "cash") *tax = subtotal * 0.15;
    else *tax = subtotal * 0.03;

    return subtotal + *tax;
}

void thankYouMessage() {
    cout << "\nThank you for visiting!\n";
}
