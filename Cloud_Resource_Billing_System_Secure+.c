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
#include <time.h>
#include <ctype.h>

#define MAX_CUSTOMERS 100  // Total Number of customers
#define MAX_LENGTH 50     // Total length of the name
#define MAX_ID_LENGTH 5   //Total length of the user_id

typedef  int uint32_t;
typedef  char uchar1_t;
typedef float float32_t;

// Define the customer_data structure
typedef struct
{
    uchar1_t name[MAX_LENGTH];
    uchar1_t user_id[MAX_ID_LENGTH];
    float32_t usage;                         // in minutes
    float32_t other_computing_resources;    // 0.54
    float32_t unit_storage;                // 1.80
    float32_t unit_database;              // 0.75
    float32_t total_bill;                //  in USD
} customer_data;

customer_data customers[MAX_CUSTOMERS];
uint32_t g_customer_count = 0;


// Function Prototypes with static keyword to access limit within file scope
static inline void display_choices();
static void add_record();
static void view_records();
static void modify_records(uchar1_t[]);
static void view_payment(uchar1_t[]);
static void search_records(uchar1_t[]);
static void delete_records(uchar1_t[]);
static float32_t generate_random_double(float32_t, float32_t);
static void first_and_recent_user(FILE *h_ffptr);
static void trim_whitespace(uchar1_t *str);
static void term_customer_reward(customer_data *customers,uint32_t count);


// Main Function
uint32_t main()
{
    uint32_t choice;
    uchar1_t user_id[MAX_ID_LENGTH];

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
            printf("-----------------------------------------------\n");
            break;

        case 2:
            // View all users details
            view_records();
            printf("-----------------------------------------------\n");
            break;

        case 3:
            // Modify the user details
            printf("\nEnter user_id to modify record: ");
            fgets(user_id, MAX_ID_LENGTH, stdin);
            modify_records(user_id);
            printf("-----------------------------------------------\n");
            break;

        case 4:
            // The Total payment of user can be calculated
            printf("\nEnter user_id to view payment: ");
            fgets(user_id, MAX_ID_LENGTH, stdin);
            view_payment(user_id);
            printf("-----------------------------------------------\n");
            break;

        case 5:
            // Search the user record
            printf("\nEnter user_id to search record: ");
            fgets(user_id, MAX_ID_LENGTH, stdin);
            search_records(user_id);
            printf("-----------------------------------------------\n");
            break;

        case 6:
            // Delete the user record
            printf("\nEnter user_id to delete record: ");
            fgets(user_id, MAX_ID_LENGTH, stdin);
            delete_records(user_id);
            printf("-----------------------------------------------\n");
            break;

        case 7:
            FILE *h_ffptr = fopen("cloudcustomer_data.txt", "r");
                if (h_ffptr) 
                {
                    printf("\nThe First and the Most Recent user is:\n");
                    printf("-----------------------------------------------\n");
                    first_and_recent_user(h_ffptr);
                    fclose(h_ffptr);
                } 

                else 
                {
                    perror("Error opening file");
                }
                break;

        case 8:
            term_customer_reward(customers, g_customer_count); // Pass the array and count
            printf("-----------------------------------------------\n");
            break;

        case 9:
            FILE *h_temp_ptr= fopen("cloudcustomer_data.txt", "r");
            fclose(h_temp_ptr);
            h_temp_ptr=fopen("cloudcustomer_data.txt", "w");
            FILE *h_temp_ptr_2= fopen("modifiedcloudcustomer_data.txt", "r");
            fclose(h_temp_ptr_2);
            h_temp_ptr_2=fopen("cloudcustomer_data.txt", "w");
            printf("Status Updated\a\t Record Cleared\n");
            break;          

        case 10:
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
        printf("7. Finding First and Recent Cutomer \n");
        printf("8. Rewarding the user with Highest Usage \n");
        printf("9. Erasing all customer data from the database \n");
        printf("10. Exit \n");
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
    srand((uint32_t) time(NULL));

    if (g_customer_count < MAX_CUSTOMERS)
    {
        getchar();
        printf("\nEnter name: ");
        fgets(customers[g_customer_count].name, MAX_LENGTH, stdin);
        printf("Enter user_id: ");
        fgets(customers[g_customer_count].user_id, MAX_ID_LENGTH, stdin);
        getchar();
        printf("Enter usage (in minutes): ");
        scanf("%f", &customers[g_customer_count].usage);
        float mindat = 0.75f;
        float maxdat = 0.85f;
        float minsto = 0.89f;
        float maxsto = 0.99f;
        float mincr = 0.50f;
        float maxcr = 0.54f;

        // Generate and assign random values
        customers[g_customer_count].unit_database = generate_random_double(mindat, maxdat);
        customers[g_customer_count].other_computing_resources = generate_random_double(minsto, maxsto);
        customers[g_customer_count].unit_storage = generate_random_double(mincr, maxcr);



        // calculation of total amount
        customers[g_customer_count].total_bill = ((customers[g_customer_count].usage) *
                            (customers[g_customer_count].other_computing_resources) *
                            (customers[g_customer_count].unit_database) *
                            (customers[g_customer_count].unit_storage));

        // Write to file                    
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
    srand((unsigned int) time(NULL));

    if (g_customer_count < MAX_CUSTOMERS)
    {
        for (uint32_t i = 0; i < MAX_CUSTOMERS; i++)
        {
                // Define the range for random values
                float mindat = 0.75f;
                float maxdat = 0.85f;
                float minsto = 0.89f;
                float maxsto = 0.99f;
                float mincr = 0.50f;
                float maxcr = 0.54f;

                // Generate and assign changing values over time.
                customers[g_customer_count].unit_database = generate_random_double(mindat, maxdat);
                customers[g_customer_count].other_computing_resources = generate_random_double(minsto, maxsto);
                customers[g_customer_count].unit_storage = generate_random_double(mincr, maxcr);

            if (strncmp(customers[i].user_id, user_id) == 0)
            {   
                getchar();
                printf("\nEnter new usage(in min)for %s:",customers[g_customer_count].name);
                scanf("%f", &customers[g_customer_count].usage);

                // Calculation of modified total amount.
                customers[g_customer_count].total_bill = ((customers[i].usage) *
                                    (customers[i].other_computing_resources) *
                                               (customers[i].unit_database) *
                                                (customers[i].unit_storage));
                entered = 1;
                printf(" Added Modified record\n");
                fprintf(h_origfile," Added Modified record\n");
                fprintf(h_origfile,"-----------------------------\n");
                fprintf(h_origfile, "Name: %s\nuser_id: %s\ntotal_bill: %.2f\nUsage: %.2f\n\n",
                    customers[i].name,
                    customers[i].user_id,
                    customers[i].total_bill,
                    customers[i].usage);
                fprintf(h_origfile,"-----------------------------\n");
                g_customer_count++;
                break;
            }
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
        if (strncmp(customers[i].user_id, user_id,MAX_ID_LENGTH) == 0)
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

        if (strncmp(customers[i].user_id, user_id,MAX_ID_LENGTH) == 0)
        {
            printf("%s\t",customers[i].name);
            printf("%s\t",customers[i].user_id);
            printf("%.2f\t",customers[i].usage);
            printf("%.2f\t",customers[i].total_bill);
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
        if (strncmp(customers[i].user_id, user_id,MAX_ID_LENGTH) == 0)
        {
            for (uint32_t j = i; j < g_customer_count; j++)
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

/**
 * @brief Generates a random floating-point number within a specified range.
 *
 * This function generates a pseudo-random floating-point number between the 
 * specified minimum and maximum values. The function uses the `rand()` function 
 * to generate a random integer, which is then scaled to a floating-point number 
 * in the range [min, max]. The result is uniformly distributed across the range.
 *
 * @param min The minimum value of the range (inclusive).
 * @param max The maximum value of the range (exclusive).
 * @return A random floating-point number between min and max.
 * @pre The `rand()` function is seeded using `srand()` before calling this function.
 * @post The generated number is a pseudo-random floating-point value within the specified range.
 */
static float32_t generate_random_double(float32_t min, float32_t max) 
{
    // Generate a random integer and scale it to the desired range

    float32_t scale = rand() / (float32_t) RAND_MAX;

    return min + scale * (max - min); // Scale to [min, max]
}

/**
 * @brief Identifies and prints the first and most recent customer from the file.
 *
 * This function reads through the provided file and identifies the first and
 * the most recent customer based on the order of records. It then prints 
 * a welcome message for both the first and the most recent customer.
 *
 * @param ffptr A file pointer to the file containing customer records.
 * @pre The file pointed to by ffptr must be open and readable.
 * @post The names of the first and most recent customers are printed to the console.
 */
static void first_and_recent_user(FILE *h_ffptr)
{
    if (!h_ffptr) 
    {
        perror("Error opening file");
        return;
    }

    char line[256];
    char first_name[MAX_LENGTH] = "";
    char last_name[MAX_LENGTH] = "";
    char *token;

    int first_user_found = 0;

    // Read through the file As source is set to desired file pointer
    while (fgets(line, sizeof(line), h_ffptr)) 
    {
        // Tokenize the line to find the name
        token = strtok(line, ":");
        if (token && strcmp(token, "Name") == 0) 
        {
            token = strtok(NULL, "\n");
            if (token) 
            {
                // Trim whitespace from the name
                trim_whitespace(token);

                if (!first_user_found) 
                {
                    strncpy(first_name, token, sizeof(first_name) - 1);
                    //Ensure null-termination
                    first_name[sizeof(first_name) - 1] = '\0'; 
                    first_user_found = 1;
                }

                // Update the last user name
                strncpy(last_name, token, sizeof(last_name) - 1);
                //Ensure null-termination
                last_name[sizeof(last_name) - 1] = '\0'; 

            }
        
        }

    }

    // Print messages based on the first and last user
    if (first_user_found) 
    {
        printf("The First to join, %s!\n", first_name);
    }

    if (*last_name) 
    {  // Check if lastName is not empty
        printf("Welcome Mr/Mrs.%s! who recently tried \n", last_name);
    }

    // Close the file
    fclose(h_ffptr);

}

/**
 * @brief Trims leading and trailing whitespace from a string.
 *
 * This function removes all leading and trailing whitespace characters from 
 * the provided string. It modifies the string in place.
 *
 * @param str A pointer to the string to be trimmed.
 * @pre The string pointed to by str must be a valid null-terminated C string.
 * @post The string is modified in place to remove leading and trailing whitespace.
 */
static void trim_whitespace(uchar1_t *str) 
{

    char *end;

    // Trim leading spaces
    while (isspace((uchar1_t)*str))
    {
      str++;
    } 

    // If all spaces, return
    if (*str == 0)
    {
        return;
    }

    // Trim trailing spaces
    end = str + strlen(str) - 1;

    while (end > str && isspace((uchar1_t)*end))
    {
        end--;
    } 

    // Null-terminate
    *(end + 1) = '\0';
}

/**
 * @brief Identifies and rewards the customer with the highest usage.
 *
 * This function iterates over an array of customer records and finds the customer
 * with the highest usage. It then prints a congratulatory message to that customer.
 *
 * @param customers Array of customer records.
 * @param count Number of customers in the array.
 * @pre The array of customers must be valid and count should represent
 *      the number of customers in the array.
 * @post The customer with the highest usage is rewarded with a message.
 */
static void term_customer_reward(customer_data customers[], uint32_t count) 
{

    if (count <= 0) 
    {
        printf("No customer records available to reward.\n");
        return;
    }

    // Initialize the pointer to the first customer
     customer_data *p_highest_use_customer = &customers[0];

    // Loop through the customers to find the one with the highest usage
    for (uint32_t i = 1; i < count; i++) 
    {

        if (customers[i].usage > p_highest_use_customer->usage) 
        {
            p_highest_use_customer = &customers[i];
        }

    }

    // Print the reward message for the customer with the highest usage
    printf("Congratulations to %s",p_highest_use_customer->name);
    printf("For having the highest usage of %.2f minutes!\n",p_highest_use_customer->usage);
    printf("You've been rewarded with bonus star points.\n");

}

/***  end of file  ***/