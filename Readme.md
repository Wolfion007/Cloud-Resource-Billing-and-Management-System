Cloud Resource Billing System
-----------------------------
Overview:
The Cloud Resource Billing System is a C program designed to manage customer records related to cloud resource usage. 
The program provides functionalities to add, view, modify, search, and delete customer records. 
Each record includes the customer’s name, user ID, resource usage, and the total bill calculated based on predefined rates.
--------------------------------------------------------------------------------------------------------------------------------------------
Global Variables:
customerdata customers[MAX_CUSTOMERS]: An array that stores up to 100 customer records.
int g_customercount = 0: A counter to keep track of the number of customer records currently stored.
--------------------------------------------------------------------------------------------------------------------------------------------
Functions
---------
1. Displaying Menu Choices
---------------------------
Function: static inline void display_choices()
Purpose: Displays the options available to the user (Add, View, Modify, etc.).
Technical Detail: Uses printf to print a menu to the console. Users can choose an action by entering a number.

2. Adding a Record
-------------------
Function: static void add_record()
Purpose: Collects customer details, calculates the total bill, and saves the record to a file.
Steps:
->Opens the file cloudcustomerdata.txt in append mode.
->Checks if there’s space for new records (g_customercount < MAX_CUSTOMERS).
->Reads user input (name, user ID, usage) and calculates the total bill based on fixed rates.
->Appends the new record to the file and updates the global record list.
->Closes the file.

3. Viewing Records
-------------------
Function: static void view_records()
Purpose: Displays all customer records currently stored in the program.
Steps:
->Prints out the details of each customer record from the global array using printf.

6. Modifying a Record
----------------------
Function: static void modify_records(uchar1_t user_id[])
Purpose: Updates the usage for a specific customer and saves the updated records to a new file.
Steps:
->Opens a new file modifiedcloudcustomerdata.txt.
->Searches for the record with the specified user_id.
->Updates the usage and recalculates the total bill.
->Writes the updated record to the new file.
->Closes the file.

7. Viewing Payment
-------------------
Function: static void viewPayment(uchar1_t user_id[])
Purpose: Displays the total bill for a specific customer.
Steps:
->Searches for the record with the specified user_id.
->Prints the total bill for the customer if found; otherwise, displays a not-found message.

8. Searching for a Record
--------------------------
Function: static void searchRecord(uchar1_t user_id[])
Purpose: Finds and displays details of a specific customer record.
Steps:
->Searches for the record with the specified user_id.
->Prints the record’s details if found; otherwise, shows a not-found message.

9. Deleting a Record
---------------------
Function: static void deleteRecord(uchar1_t user_id[])
Purpose: Removes a specific customer record from the global list.
Steps:
->Searches for the record with the specified user_id.
->Removes the record and shifts subsequent records up to fill the gap.
->Updates the global customer count.

10.Generating Random Values
-----------------------------
Function: static float32_t generate_random_double(float32_t min, float32_t max)
Purpose: Generates a random floating-point number within a specified range.
Steps:
->Uses rand() to generate a random integer and scales it to a floating-point number in the range [min, max].

11.Finding First and Most Recent Customer
-----------------------------------------
Function: static void first_and_recent_user(FILE *h_ffptr)
Purpose: Identifies and prints the first and most recent customer from the file.
Steps:
->Reads through the file and extracts the names of the first and most recent customers.
->Prints the names of these customers.

12.Trimming Whitespace
-----------------------
Function: static void trim_whitespace(uchar1_t *str)
Purpose: Removes leading and trailing whitespace from a string.
Steps:
->Trims leading and trailing whitespace characters from the string in place.

13.Rewarding the Customer with Highest Usage
--------------------------------------------
Function: static void term_customer_reward(customer_data customers[], uint32_t count)
Purpose: Identifies and rewards the customer with the highest usage.
Steps:
->Iterates over the customer records to find the one with the highest usage.
->Prints a congratulatory message to that customer

                                                              Workflow                                                      
--------------------------------------------------------------------------------------------------------------------------------------------
Starting the Program
When you run the program, it displays a menu of options.

Adding a New Customer
You choose to add a new customer. The program prompts you to enter the customer's name, 
user ID, and the number of minutes they used cloud resources.
It then calculates the bill and saves this information in a file.

Viewing All Customers
If you want to see all customers, select the view option, and the program will show you a list of all customers and their details.

Updating a Customer’s Usage
If a customer’s usage changes, you can update their record. The program recalculates their bill and saves the updated record to a new file.

Checking a Customer’s Bill
To find out how much a particular customer owes, search for their ID, and the program will display their total bill.

Finding a Specific Customer
You can search for a customer by their ID and view their details.

Removing a Customer
If a customer is no longer needed, you can delete their record, and the program will update the list accordingly.

Generating Random Values
Used during record addition to simulate varying rates for database, storage, and computing resources.

Finding the First and Most Recent Customer
Retrieve and display information about the first and most recent customer from the records file.

Trimming Whitespace
Ensures that customer names and other fields do not have leading or trailing spaces.

Rewarding the Customer with Highest Usage
Identifies and rewards the customer with the highest usage, demonstrating appreciation for high resource consumption.

----------------------------------------------------------------------------------------------------------------------------------------------
License
This program is copyrighted (c) 2024 by Murugesan. All rights reserved.

