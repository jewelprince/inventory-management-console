#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_USERS 100
#define MAX_ITEMS 100
#define MAX_RECEIPTS 10000

// Definition of a structure named 'Receipt' to store information on sales
typedef struct {
    int receiptNumber;
    char customerName[50];
    char itemName[50];
    char date[20];
    double itemPrice;
} Receipt;

// Definition of a structure named ‘Admin’ to represent an administrative user
typedef struct {
    int receiptNumber;
    char name[50];
    char password[50];
    char email[50];
    int idNumber;
    char position[50];
} Admin;

// Definition of a structure named ‘Cashier’ to represent cashiers
typedef struct {
    char name[50];
    char password[50];
    char email[50];
    int idNumber;
} Cashier;

// Global variables
int numItems = 0; // Variable to track the number of items
int currentReceiptNumber = 1;
int admin_count = 0; // Variable to track the number of admins
int cashier_count = 0; // Variable to track the number of cashiers

// Declare arrays
Admin admin_credentials[MAX_USERS];
Cashier cashier_credentials[MAX_USERS];
char item_names[MAX_ITEMS][50];
double item_prices[MAX_ITEMS];
int inventory[MAX_ITEMS];
int sales[MAX_ITEMS];
Receipt receipts[MAX_RECEIPTS];

int viewChoice;

// Declare function prototypes
void saveAdminToFile(Admin *admin);
void saveCashierToFile(Cashier *cashier);
void saveReceiptToFile(Receipt *receipt);
void saveItemInfoToFile();
int restart();
void signUp(int role);
void login(int role);
void inputItemPrices();
void addItem(char name[], double price, int stock);
void manageInventory();
void changeItemPrice();
void displayInventory();
void displayProfits();
void displayReceipts();
void recordSales();

// Main function
int main() {
    int continueProgram = 1;

    while (continueProgram) {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("- - - - - - - - - - - - - - - - - - - - Welcome to Necessities! - - - - - - - - - - - - - - - - - -\n");
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("You can choose to:\n");
        printf("1. Sign up\n");
        printf("2. Login\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Choose your role to sign up as:\n");
                printf("1. Admin\n");
                printf("2. Cashier\n");
                int role;
                scanf("%d", &role);
                signUp(role);
                break;

            case 2:
                printf("Choose your role to log in as:\n");
                printf("1. Admin\n");
                printf("2. Cashier\n");
                int loginRole;
                scanf("%d", &loginRole);
                if (loginRole == 1 || loginRole == 2) {
                    login(loginRole);

                    if (loginRole == 1) {
                        // Admin functionality
                        int adminChoice;
                        printf("1. Input Item prices\n");
                        printf("2. Change Item Price\n");
                        printf("3. Add Item\n");
                        printf("4. Change item prices\n");
                        printf("5. View profit, receipts, or inventory\n");
                        printf("Enter your choice: ");
                        scanf("%d", &adminChoice);

                        switch (adminChoice) {
                            case 1:
                                inputItemPrices();
                                break;
                            case 2:
                                manageInventory();
                                break;
                            case 3:
                                addItem(item_names[numItems], item_prices[numItems], inventory[numItems]);
                                break;
                            case 4:
                                changeItemPrice();
                                break;
                            case 5:
                                printf("Choose what you want to view:\n");
                                printf("1. View Inventory\n");
                                printf("2. View Profits\n");
                                printf("3. View Receipts\n");
                                scanf("%d", &viewChoice);

                                switch (viewChoice) {
                                    case 1:
                                        displayInventory();
                                        break;
                                    case 2:
                                        displayProfits();
                                        break;
                                    case 3:
                                        displayReceipts();
                                        break;
                                    default:
                                        printf("Invalid choice.\n");
                                }
                                break;
                            default:
                                printf("Invalid choice.\n");
                        }
                    } else if (loginRole == 2) {
                        // Cashier functionality
                        int cashierChoice;
                        printf("Choose an action:\n");
                        printf("1. Record Sales\n");
                        printf("2. Change Item Price\n");
                        printf("3. Manage Inventory\n");
                        printf("4. Add Item\n");
                        printf("5. View profit, receipts, or inventory\n");
                        printf("Enter your choice: ");
                        scanf("%d", &cashierChoice);

                        switch (cashierChoice) {
                            case 1:
                                recordSales();
                                break;
                            case 2:
                                changeItemPrice();
                                break;
                            case 3:
                                manageInventory();
                                break;
                            case 4:
                                addItem(item_names[numItems], item_prices[numItems], inventory[numItems]);
                                break;
                            case 5:
                                printf("Choose what you want to view:\n");
                                printf("1. View Inventory\n");
                                printf("2. View Profits\n");
                                printf("3. View Receipts\n");
                                scanf("%d", &viewChoice);

                                switch (viewChoice) {
                                    case 1:
                                        displayInventory();
                                        break;
                                    case 2:
                                        displayProfits();
                                        break;
                                    case 3:
                                        displayReceipts();
                                        break;
                                    default:
                                        printf("Invalid choice.\n");
                                }
                                break;
                            default:
                                printf("Invalid choice.\n");
                        }
                    }
                } else {
                    printf("Invalid choice, enter 1 for sign up or 2 for login.\n");
                }
                break;

            default:
                printf("Invalid action. Please select 1 to sign up or 2 to log in.\n");
        }

        continueProgram = restart();
    }

    return 0;
}

// Declare functions
void saveAdminToFile(Admin *admin) {
    FILE *file = fopen("admin_credentials.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d %s %s\n", admin->name, admin->idNumber, admin->email, admin->position);
        fclose(file);
    } else {
        printf("Error opening admin file.\n");
    }
}

void saveCashierToFile(Cashier *cashier) {
    FILE *file = fopen("cashier_credentials.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d %s %s\n", cashier->name, cashier->idNumber, cashier->password, cashier->email);
        fclose(file);
    } else {
        printf("Error opening cashier file.\n");
    }
}

void saveReceiptToFile(Receipt *receipt) {
    FILE *file = fopen("receipts.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d %s %s %.2f %s\n", receipt->receiptNumber, receipt->customerName, receipt->itemName, receipt->itemPrice, receipt->date);
        fclose(file);
    } else {
        printf("Error opening receipts file.\n");
    }
}

void saveItemInfoToFile() {
    FILE *file = fopen("item_info.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < MAX_ITEMS; ++i) {
            fprintf(file, "%s %.2f %d\n", item_names[i], item_prices[i], inventory[i]);
        }
        fclose(file);
    } else {
        printf("Error opening item info file.\n");
    }
}

int restart() {
    int goBack;
    printf("Do you want to return to the main menu?\n");
    printf("Select 1 for yes and 0 for no: ");
    scanf("%d", &goBack);
    fflush(stdin);
    return goBack;
}

void signUp(int role) {
    char firstName[50], lastName[50], email[50], password[50];
    int username;

    printf("Enter your first name: ");
    fgets(firstName, sizeof(firstName), stdin);
    // Remove trailing newline character
    if (firstName[strlen(firstName) - 1] == '\n')
        firstName[strlen(firstName) - 1] = '\0';

    printf("Enter your last name: ");
    fgets(lastName, sizeof(lastName), stdin);
    // Remove trailing newline character
    if (lastName[strlen(lastName) - 1] == '\n')
        lastName[strlen(lastName) - 1] = '\0';

    printf("Enter your email: ");
    fgets(email, sizeof(email), stdin);
    // Remove trailing newline character
    if (email[strlen(email) - 1] == '\n')
        email[strlen(email) - 1] = '\0';

    if (role == 1) {
        Admin admin;
        printf("Enter your Position: \n");
        fgets(admin.position, sizeof(admin.position), stdin);
        // Remove trailing newline character
        if (admin.position[strlen(admin.position) - 1] == '\n')
            admin.position[strlen(admin.position) - 1] = '\0';

        printf("Enter your admin ID number: \n");
        scanf("%d", &username);
        // Loop until password is entered
        while (1) {
            printf("Enter your password: \n");
            scanf("%s", password);
        
            if (strlen(password) >= 8) {
                break; // Exit the loop if password meets the criteria
            } else {
                printf("Password must be at least 8 characters long. Please try again.\n");
            }
        }

        strcpy(admin.name, ""); // Clear the name field
        strcat(admin.name, firstName); // Concatenate first name
        strcat(admin.name, " "); // Add a space
        strcat(admin.name, lastName); // Concatenate last name
        strcpy(admin.email, email);
        strcpy(admin.password, password);
        admin.idNumber = username;

        // Save admin data to the array
        admin_credentials[admin_count++] = admin;

        saveAdminToFile(&admin);

        printf("Admin sign-up successful. You can now log in as an admin.\n");
    } else if (role == 2) {
        Cashier cashier;
        printf("Enter your cashier ID number: ");
        scanf("%d", &username);
        printf("Enter your password: ");
        scanf("%s", password);

        strcpy(cashier.name, ""); // Clear the name field
        strcat(cashier.name, firstName); // Concatenate first name
        strcat(cashier.name, " "); // Add a space
        strcat(cashier.name, lastName); // Concatenate last name
        strcpy(cashier.email, email);
        strcpy(cashier.password, password);
        cashier.idNumber = username;
        
        // Save cashier data to the array
        cashier_credentials[cashier_count++] = cashier;

        saveCashierToFile(&cashier);

        printf("Cashier sign-up successful. You can now log in as a cashier.\n");
    } else {
        printf("Invalid role, sign up canceled.\n");
    }
}

void login(int role) {
    int username;
    char password[50];

    printf("Enter your ID number: ");
    scanf(" %d", &username); // Added space before %d

    printf("Enter your password: ");
    scanf(" %s", password); // Added space before %s

    int loggedIn = 0; // Flag to check if login is successful

    if (role == 1) {
        for (int i = 0; i < MAX_USERS; ++i) {
            if (username == admin_credentials[i].idNumber && strcmp(password, admin_credentials[i].password) == 0) {
                printf("Admin login successful. Welcome, %s!\n", admin_credentials[i].name);
                printf("Position: %s\n", admin_credentials[i].position);
                printf("ID Number: %d\n", username);
                loggedIn = 1;
                break;
            }
        }
    } else if (role == 2) {
        for (int i = 0; i < MAX_USERS; ++i) {
            if (username == cashier_credentials[i].idNumber && strcmp(password, cashier_credentials[i].password) == 0) {
                printf("Cashier login successful. Welcome, %s!\n", cashier_credentials[i].name);
                printf("ID Number: %d\n", username);
                loggedIn = 1;
                break;
            }
        }
    }

    if (!loggedIn) {
        printf("Invalid credentials, login failed.\n");
    }
}

void addItem(char name[], double price, int stock) {
    if (numItems < MAX_ITEMS) {
        strcpy(item_names[numItems], name);
        item_prices[numItems] = price;
        inventory[numItems] = stock;
        numItems++; 
    } else {
        printf("Inventory is full. Cannot add more items.\n");
    }
}

void manageInventory() {
    char itemNameToUpdate[50];
    int itemIndexToUpdate = -1;

    printf("Which item's inventory would you like to update? (Enter item name): ");
    scanf("%s", itemNameToUpdate);

    for (int i = 0; i < MAX_ITEMS; ++i) {
        if (strcmp(item_names[i], itemNameToUpdate) == 0) {
            itemIndexToUpdate = i;
            break;
        }
    }

    if (itemIndexToUpdate >= 0) {
        printf("Enter the current stock for item %s: ", itemNameToUpdate);
        scanf("%d", &inventory[itemIndexToUpdate]);
        printf("Inventory updated successfully.\n");
        saveItemInfoToFile();
    } else {
        printf("Item not found. Inventory update canceled.\n");
    }
}

void changeItemPrice() {
    char itemNameToChange[50];
    int itemIndexToChange = -1;

    printf("Enter the name of the item you want to change the price for: ");
    scanf("%s", itemNameToChange);

    for (int i = 0; i < MAX_ITEMS; ++i) {
        if (strcmp(item_names[i], itemNameToChange) == 0) {
            itemIndexToChange = i;
            break;
        }
    }

    if (itemIndexToChange >= 0) {
        printf("Enter the new price for item %s: ", itemNameToChange);
        scanf("%lf", &item_prices[itemIndexToChange]);
        printf("Item price changed.\n");
        saveItemInfoToFile();
    } else {
        printf("Item not found. Price change canceled.\n");
    }
}

void displayInventory() {
    for (int i = 0; i < numItems; ++i) {
        printf("Item %s: Stock: %d, Price: %.2f\n", item_names[i], inventory[i], item_prices[i]);
    }
}

void displayProfits() {
    double totalProfits = 0;

    for (int i = 0; i < MAX_ITEMS; ++i) {
        totalProfits += sales[i] * item_prices[i];
    }

    printf("Total Profits: %.2f\n", totalProfits);
}

void displayReceipts() {
    printf("Receipts:\n");

    for (int k = 0; k < MAX_RECEIPTS; ++k) {
        int c=1;
        if (strlen(receipts[k].itemName) > 0) {
            printf("Receipt Number:\nCustomer: %s\nItem: %s\nPrice: %.2f\nDate: %s\n\n\n",
                   c, receipts[k].customerName, receipts[k].itemName, receipts[k].itemPrice, receipts[k].date);
        }
        c++;
    }
}

void recordSales() {
    char itemNameToSell[50];
    int itemIndexToSell = -1;

    printf("Which item was sold? (Enter item name): ");
    scanf("%s", itemNameToSell);

    for (int i = 0; i < MAX_ITEMS; ++i) {
        if (strcmp(item_names[i], itemNameToSell) == 0) {
            itemIndexToSell = i;
            break;
        }
    }

    if (itemIndexToSell >= 0) {
        printf("Enter the quantity sold for item %s: ", itemNameToSell);
        scanf("%d", &sales[itemIndexToSell]);

        inventory[itemIndexToSell] -= sales[itemIndexToSell];

        Receipt receipt;
        printf("Enter customer name: ");
        fgets(receipt.customerName, sizeof(receipt.customerName), stdin);
        // Remove trailing newline character
        if (receipt.customerName[strlen(receipt.customerName) - 1] == '\n')
            receipt.customerName[strlen(receipt.customerName) - 1] = '\0';
        printf("Enter date: ");
        scanf("%s", receipt.date);

        receipt.receiptNumber = currentReceiptNumber++;
        strcpy(receipt.itemName, itemNameToSell);
        receipt.itemPrice = item_prices[itemIndexToSell];

        saveReceiptToFile(&receipt);

        printf("Sale recorded successfully. Receipt number: %d\n", receipt.receiptNumber);
    } else {
        printf("Item not found. Sale recording canceled.\n");
    }
}

