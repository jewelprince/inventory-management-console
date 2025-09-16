# NECCESSITIES: Inventory & Sales Management System

**A comprehensive console-based application built in C to automate inventory tracking, sales recording, and profit calculation for small businesses. Features secure role-based authentication for Admins and Cashiers.**

## Overview

This project is a full-featured inventory management system developed as a console application in C. It allows businesses to:
- **Manage Users:** Secure sign-up and login for Admins and Cashiers with role-based permissions.
- **Track Inventory:** Add items, update stock levels, and modify prices.
- **Record Sales:** Generate receipts for transactions and automatically update inventory.
- **Analyze Performance:** View total profits, sales history, and current stock status.

The system emphasizes data persistence by saving all critical information (user credentials, item data, receipts) to text files.

## Key Features

- **Role-Based Access Control:** 
  - **Admins** can input item prices, manage inventory, add items, change prices, and view profits/receipts.
  - **Cashiers** can record sales, manage inventory for sold items, and view data.
- **Inventory Management:** Add new items, track stock quantities, and update prices seamlessly.
- **Receipt Generation:** Automatically generates and saves detailed receipts for every sale.
- **Profit Analytics:** Calculates and displays total profits based on sales data.
- **Data Persistence:** All data is saved to external files (`admin_credentials.txt`, `receipts.txt`, `item_info.txt`) to ensure it persists between runs.

## Project Structure

inventory-system/
│
├── necessities.c # Main source code file
├── admin_credentials.txt # Generated file storing admin user data
├── cashier_credentials.txt # Generated file storing cashier user data
├── receipts.txt # Generated file storing all sales receipts
├── item_info.txt # Generated file storing item names, prices, and stock
│
└── README.md # This file


## Future Improvements

-  **Graphical User Interface (GUI):** Develop a GUI using GTK or another C library for easier use.
-  **Database Integration:** Replace file storage with a SQLite database for improved reliability and querying.
-  **Barcode Scanner Support:** Integrate functionality to input items via a barcode scanner.
-  **Advanced Reporting:** Add features to generate sales reports over custom time periods.

## Developer

**Jewel Prince**
- *STEM Student | Aspiring Software Developer*
- Email: 135jewel@gmail.com

---

## License

This project is open source and available under the [MIT License](https://opensource.org/licenses/MIT).
