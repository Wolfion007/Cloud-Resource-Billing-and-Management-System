/** @file Cloud_Resource_Billing_System_Standard.c
*
* @brief
C program to add customer details and to calculate
the total bill for cloud resource usage in minutes,then save the
updated data regarding customer details to a new file.
*
* @par
* COPYRIGHT NOTICE: (c) 2024 Murugesan. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 100 // Total Number of customers
#define MAX_LENGTH 50     // Total length of the string

typedef  int uint32_t;
typedef  char uchar1_t;
typedef float float32_t;

// Define the customer_data structure
typedef struct
{
    uchar1_t name[MAX_LENGTH];
    uchar1_t user_id[MAX_LENGTH];
    float32_t usage;                       // in minutes
    float32_t other_computing_resources;  // 0.54
    float32_t unit_storage;              // 1.80
    float32_t unit_database;            // 0.75
    float32_t total_bill;              //  in USD
} customer_data;

customer_data customers[MAX_CUSTOMERS];
int g_customer_count = 0;

// Function Prototypes with static keyword to access limit within file scope
static inline void display_choices();
static void add_record();
static void view_records();
static void modify_records(uchar1_t[]);
static void view_payment(uchar1_t[]);
static void search_records(uchar1_t[]);
static void delete_records(uchar1_t[]);

// Main Function
uint32_t main()
{
    uint32_t choice;
    uchar1_t user_id[MAX_LENGTH];

    while (1)
    {  
        display_choices();
        scanf("%d", &choice);
        getchar(); 

        switch (choice)
        {
        case 1:
            // Add the user details
            add_record();
            break;
        case 2:
            // View all users details
            view_records();
            break;
        case 3:
            // Modify the user details
            printf("\nEnter user_id to modify record: ");
            fgets(user_id, MAX_LENGTH, stdin);
            modify_records(user_id);
            break;
        case 4:
            // The Total payment of user can be calculated
            printf("\nEnter user_id to view payment: ");
            fgets(user_id, MAX_LENGTH, stdin);
            view_payment(user_id);
            break;
        case 5:
            // Search the user record
            printf("\nEnter user_id to search record: ");
            fgets(user_id, MAX_LENGTH, stdin);
            search_records(user_id);
            break;
        case 6:
            // Delete the user record
            printf("\nEnter user_id to delete record: ");
            fgets(user_id, MAX_LENGTH, stdin);
            delete_records(user_id);
            break;
        case 7:
            return 0;
        default:
            printf("\nInvalid choice! Please try again.\n");
        }

    }

}

/**
 * @brief Displays the menu choices to the user.
 *
 * This function prints out the options available in the menu for the user
 * to select from. It does not modify any global state.
 *
 * @pre The function only prints to the console and does not interact with files.
 * @post The menu options are displayed to the user.
 */

static inline void display_choices()
{
        printf("\n--- Customer Records Menu ---\n");
        printf("1. Add Record\n");
        printf("2. View Records\n");
        printf("3. Modify Record\n");
        printf("4. View Payment\n");
        printf("5. Search Record\n");
        printf("6. Delete Record\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

}

/**
 * @brief Views all customer records.
 *
 * This function prints out all customer records including name, user_id,
 * usage in minutes, and total bill. It displays information for all records
 * in the global customer list.
 *
 * @pre The global customer list must be populated.
 * @post The customer records are printed to the console.
 */

static void add_record()
{
    FILE *h_fptr = fopen("cloudcustomer_data.txt", "a+");
    if (!h_fptr)
    {
        perror("Error opening file");
        return;
    }

    if (g_customer_count < MAX_CUSTOMERS)
    {
        customers[g_customer_count].other_computing_resources = 0.54f;
        customers[g_customer_count].unit_database = 0.75f;
        customers[g_customer_count].unit_storage = 1.80f;
        getchar();
        printf("\nEnter name: ");
        fgets(customers[g_customer_count].name, MAX_LENGTH, stdin);
        printf("Enter user_id: ");
        fgets(customers[g_customer_count].user_id, MAX_LENGTH, stdin);
        printf("Enter usage (in minutes): ");
        scanf("%f", &customers[g_customer_count].usage);
        // calculation of total amount
        customers[g_customer_count].total_bill = ((customers[g_customer_count].usage) *
                            (customers[g_customer_count].other_computing_resources) *
                            (customers[g_customer_count].unit_database) *
                            (customers[g_customer_count].unit_storage));
        fprintf(h_fptr,"Added Record\n");
        fprintf(h_fptr,"-----------------------------\n");
        fprintf(h_fptr, "Name: %s\n user_id: %s\n total_bill: %.2f\n Usage: %.2f\n\n",
                customers[g_customer_count].name,
                customers[g_customer_count].user_id,
                customers[g_customer_count].total_bill,
                customers[g_customer_count].usage);
        fprintf(h_fptr,"-----------------------------\n");

        printf("\nRecord added successfully!\n");
        g_customer_count++;
    }

    else
    {
        printf("\nMaximum number of records reached.\n");
    }
    fclose(h_fptr);
}

/**
 * @brief Modifies an existing customer record.
 *
 * This function updates the usage for a customer based on the provided user_id.
 * It recalculates the total bill and writes the updated records to a new file.
 *
 * @param user_id The ID of the user whose record is to be modified.
 * @pre The file "modifiedcloudcustomer_data.txt" must be writable.
 * @post The record for the specified user_id is updated and written to the file.
 */

static void view_records()
{
    printf("\nName\tuser_id\tUsage(min)\tTotal Bill($)\n");
    for (uint32_t i = 0; i < MAX_CUSTOMERS; i++)
    {
        printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name,
               customers[i].user_id, customers[i].usage,
               customers[i].total_bill);
    }

}

/**
 * @brief Modifies an existing customer record.
 *
 * This function updates the usage for a customer based on the provided user_id.
 * It recalculates the total bill and writes the updated records to a new file.
 *
 * @param user_id The ID of the user whose record is to be modified.
 * @pre The file "modifiedcloudcustomer_data.txt" must be writable.
 * @post The record for the specified user_id is updated and written to the file.
 */

static void modify_records(uchar1_t user_id[])
{
    FILE *h_origfile = fopen("modifiedcloudcustomer_data.txt", "a+");
    if (h_origfile == NULL)
    {
        perror("Error opening file");
        return;
    }

    int entered = 0;

    if (g_customer_count < MAX_CUSTOMERS)
    {
        for (uint32_t i = 0; i < MAX_CUSTOMERS; i++)
        {
            customers[i].other_computing_resources = 0.54f;
            customers[i].unit_database = 0.75;
            customers[i].unit_storage = 1.80f;
            if (strcmp(customers[i].user_id, user_id) == 0)
            {
                printf("\nEnter new usage(in min)for %s:",customers[g_customer_count].name);
                scanf("%f", &customers[g_customer_count].usage);

                // calculation of modified total amount
                customers[g_customer_count].total_bill = ((customers[i].usage) *
                                    (customers[i].other_computing_resources) *
                                               (customers[i].unit_database) *
                                                (customers[i].unit_storage));
                entered = 1;
                g_customer_count++;
            }
            fprintf(h_origfile," Added Modified record\n");
            fprintf(h_origfile,"-----------------------------\n");
            fprintf(h_origfile, "Name: %s\nuser_id: %s\ntotal_bill: %.2f\nUsage: %.2f\n\n",
                    customers[i].name,
                    customers[i].user_id,
                    customers[i].total_bill,
                    customers[i].usage);
            fprintf(h_origfile,"-----------------------------\n");
            break;
        }
    }

    if (!entered)
    {
        printf("\nRecord not added!\n");
    }

    fclose(h_origfile);
}

/**
 * @brief Views the payment record for a specific user.
 *
 * This function searches for a user record by user_id and prints the total bill
 * for the specified user. If the user is not found, an appropriate message is displayed.
 *
 * @param user_id The ID of the user whose payment record is to be viewed.
 * @pre The global customer list must be populated.
 * @post The total bill for the specified user_id is printed to the console.
 */

static void view_payment(uchar1_t user_id[])
{
    uint32_t found = 0;

    for (uint32_t i = 0; i < MAX_CUSTOMERS; i++)
    {
        if (strcmp(customers[i].user_id, user_id) == 0)
        {
            printf("\nTotal Bill for %s: $%.2f\n",
                   customers[i].name,
                   customers[i].total_bill);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nRecord not found!\n");
    }

}

/**
 * @brief Searches for a user record by user_id.
 *
 * This function searches for a user record based on the provided user_id and
 * prints out the details of the record if found. If the record is not found,
 * an appropriate message is displayed.
 *
 * @param user_id The ID of the user whose record is to be searched.
 * @pre The global customer list must be populated.
 * @post The details of the record for the specified user_id are printed to the console.
 */

static void search_records(uchar1_t user_id[])
{
    uint32_t found = 0;
    printf("\nName\tuser_id\tUsage(min)\tTotal Bill($)\n");
    for (uint32_t i = 0; i < MAX_CUSTOMERS; i++)
    {

        if (strcmp(customers[i].user_id, user_id) == 0)
        {
            printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name,
                   customers[i].user_id, customers[i].usage, customers[i].total_bill);
            found = 1;
            break;
        }

    }

    if (!found)
    {
        printf("\nRecord not found!\n");
    }

}

/**
 * @brief Deletes a user record based on user_id.
 *
 * This function searches for a record with the given user_id and deletes it
 * from the global list of customers. The list is then compacted to fill the gap.
 *
 * @param user_id The ID of the user whose record is to be deleted.
 * @pre The global customer list must be populated.
 * @post The record for the specified user_id is removed from the list.
 */

static void delete_records(uchar1_t user_id[])
{
    for (uint32_t i = 0; i < MAX_CUSTOMERS; i++)
    {
        if (strcmp(customers[i].user_id, user_id) == 0)
        {
            for (int j = i; j < g_customer_count; j++)
            {
                customers[j] = customers[j + 1];
            }
            printf("\nRecord deleted successfully!\n");
            return;
        }
    }

    g_customer_count = 0;
    printf("\nRecord not found!\n");
}

/***  end of file  ***/