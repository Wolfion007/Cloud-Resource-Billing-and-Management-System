#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_CUSTOMERS 100
#define MAX_MONTHS 10

struct customerdata
{
    char name[50];
    char userId[4];
    float usage;
    float othercomputingresources; // 0.54
    float unitstorage;             // 1.80
    float unitdatabase;            // 0.75
    float totalBill;
};

struct customerdata customers[MAX_CUSTOMERS];
int customerCount = 0;

void addrecord();
void viewrecords();
void modifyRecord(char[]);
void viewPayment(char[]);
void searchRecord(char[]);
void deleteRecord(char[]);
void firstandlastuser(FILE *ffptr);  //First will be identified and sent over the message "You're the first to join" and last user "You're welcomed to use our product"  
void termCustomerPrize(struct customerdata *customers,int count);  // Highest usage customer can be rewarded with bonus star point
float generate_random_double(float min, float max);
void trim_whitespace(char *str);
void openFile(const char *filename);


int main()
{
    int choice;
    char userId[4];

    while (1)
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
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addrecord();
            printf("--------------------------------------------------------------\n");
            break;
        case 2:
            viewrecords();
            printf("--------------------------------------------------------------\n");
            break;
        case 3:
            printf("\nEnter userId to modify record: ");
            scanf("%s", userId);
            modifyRecord(userId);
            char filename[] = "modifiedcloudcustomerdata.txt";
            FILE *sfile=fopen(filename, "r");
            openFile(filename);
            fclose(sfile);
            printf("--------------------------------------------------------------\n");
            break;
        case 4:
            printf("\nEnter userId to view payment: ");
            scanf("%s", userId);
            viewPayment(userId);
            printf("--------------------------------------------------------------\n");
            break;
        case 5:
            printf("\nEnter userId to search record: ");
            scanf("%s", userId);
            searchRecord(userId);
            printf("--------------------------------------------------------------\n");
            break;
        case 6:
            printf("\nEnter userId to delete record: ");
            scanf("%s", userId);
            deleteRecord(userId);
            printf("--------------------------------------------------------------\n");
            break;
        case 7:
            FILE *ffptr = fopen("cloudcustomerdata.txt", "r");
                if (ffptr) 
                {
                    printf("\nThe First and the Most Recent user is:\n");
                    printf("--------------------------------------------------------------\n");
                    firstandlastuser(ffptr);
                    fclose(ffptr);
                } else {
                    perror("Error opening file");
                }
                break;
        case 8:
            termCustomerPrize(customers, customerCount); // Pass the array and count
            printf("--------------------------------------------------------------\n");
            break;
        case 9:
            FILE *tempptr= fopen("cloudcustomerdata.txt", "r");
             fclose(tempptr);
             tempptr=fopen("cloudcustomerdata.txt", "w");
             FILE *tempptr2= fopen("modifiedcloudcustomerdata.txt", "r");
             fclose(tempptr2);
             tempptr2=fopen("cloudcustomerdata.txt", "w");
            break;            
        case 10:
            return 0;
        default:
            printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void addrecord()
{
    FILE *fptr = fopen("cloudcustomerdata.txt", "a+");
    if (!fptr)
    {
        perror("Error opening file");
        return;
    }
    FILE *f_two_ptr = fopen("thiscloudcustomerdata.csv", "a+");
    if (!f_two_ptr)
    {
        perror("Error opening file");
        return;
    }


    srand((unsigned int) time(NULL));

    if (customerCount < MAX_CUSTOMERS) 
    {
        getchar();
        printf("\nEnter name: ");
        fgets(customers[customerCount].name,50, stdin);
        printf("Enter user_id: ");
        fgets(customers[customerCount].userId, 4, stdin);
        getchar();
        printf("Enter usage (in minutes): ");
        scanf("%f", &customers[customerCount].usage);
        
        // Define the range for random values
        float mindat = 0.75;
        float maxdat = 0.85;
        float minsto = 0.89;
        float maxsto = 0.99;
        float mincr = 0.50;
        float maxcr = 0.54;

        // Generate and assign random values
        customers[customerCount].unitdatabase = generate_random_double(mindat, maxdat);
        customers[customerCount].othercomputingresources = generate_random_double(minsto, maxsto);
        customers[customerCount].unitstorage = generate_random_double(mincr, maxcr);

        // Calculate totalBill
        customers[customerCount].totalBill = customers[customerCount].usage *
                                             customers[customerCount].othercomputingresources *
                                             customers[customerCount].unitdatabase *
                                             customers[customerCount].unitstorage;

        // Write to file
        fprintf(fptr,"Record added \n");
        fprintf(fptr,"------------------------------\n");
        fprintf(fptr, "Name: %s\nUserId: %s\nTotalBill: %.2f\nUsage: %.2f\n\n",
                customers[customerCount].name,
                customers[customerCount].userId,
                customers[customerCount].totalBill,
                customers[customerCount].usage);
        fprintf(f_two_ptr, "Name: %s\nUserId: %s\nTotalBill: %.2f\nUsage: %.2f\n\n",
                customers[customerCount].name,
                customers[customerCount].userId,
                customers[customerCount].totalBill,
                customers[customerCount].usage);
        fprintf(fptr,"------------------------------\n");
        fflush(fptr);
        printf("\nRecord added successfully!\n");

        customerCount++;
    }

    else
    {
        printf("\nMaximum number of records reached.\n");
    }
    
    firstandlastuser(fptr);

    fclose(fptr);
    fclose(f_two_ptr);
}

void viewrecords()
{
    printf("\nName\tUserId\tUsage(min)\tTotal Bill($)\n");
    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name,
               customers[i].userId, customers[i].usage,
               customers[i].totalBill);
    }
}

void modifyRecord(char userId[])
{
    FILE *origFile = fopen("modifiedcloudcustomerdata.txt", "a+");
    if (origFile == NULL)
    {
        perror("Error opening file");
        return;
    }
    int entered = 0;
    if (customerCount < MAX_CUSTOMERS)
    {
        for (int i = 0; i < MAX_CUSTOMERS; i++)
        {
            customers[i].othercomputingresources = 0.54f;
            customers[i].unitdatabase = 0.75;
            customers[i].unitstorage = 1.80f;

            if (strcmp(customers[i].userId, userId) == 0)
            {
                printf("\nEnter new usage (in minutes) for %s: ", customers[customerCount].name);
                scanf("%f", &customers[customerCount].usage);
                customers[customerCount].totalBill = customers[i].usage * customers[i].othercomputingresources * customers[i].unitdatabase * customers[i].unitstorage;
                entered = 1;
                customerCount++;
            
                fprintf(origFile,"Modified Record Added Succesfully \n");
                fprintf(origFile,"------------------------------\n");
                fprintf(origFile, "Name: %s\nUserId: %s\nTotalBill: %.2f\nUsage: %.2f\n\n", customers[i].name, customers[i].userId, customers[i].totalBill, customers[i].usage);
                fprintf(origFile,"------------------------------\n");
                break;
            }
        }
    }
    if (!entered)
    {
        printf("\nRecord not added!\n");
    }

    firstandlastuser(origFile);

    fclose(origFile);
}

void viewPayment(char userId[])
{
    int found = 0;
    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        if (strcmp(customers[i].userId, userId) == 0)
        {
            printf("\nTotal Bill for %s: $%.2f\n",
                   customers[i].name,
                   customers[i].totalBill);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nRecord not found!\n");
    }
}

void searchRecord(char userId[])
{
    int found = 0;
    printf("\nName\tUserId\tUsage(min)\tTotal Bill($)\n");
    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        if (strcmp(customers[i].userId, userId) == 0)
        {
            printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name, customers[i].userId, customers[i].usage, customers[i].totalBill);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nRecord not found!\n");
    }
}

void deleteRecord(char userId[])
{
    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        if (strcmp(customers[i].userId, userId) == 0)
        {
            for (int j = i; j < customerCount; j++)
            {
                customers[j] = customers[j + 1];
            }
            printf("\nRecord deleted successfully!\n");
            return;
        }
    }
    customerCount = 0;
    printf("\nRecord not found!\n");
}

void firstandlastuser(FILE *ffptr)
{
    if (!ffptr) {
        perror("Error opening file");
        return;
    }

    char line[256];
    char firstName[50] = "";
    char lastName[50] = "";
    char *token;

    int firstUserFound = 0;

    // Read through the file
    while (fgets(line, sizeof(line), ffptr)) {
        // Tokenize the line to find the name
        token = strtok(line, ":");
        if (token && strcmp(token, "Name") == 0) 
        {
            token = strtok(NULL, "\n");
            if (token) {
                // Trim whitespace from the name
                trim_whitespace(token);

                if (!firstUserFound) {
                    strncpy(firstName, token, sizeof(firstName) - 1);
                    firstName[sizeof(firstName) - 1] = '\0'; // Ensure null-termination
                    firstUserFound = 1;
                }
                // Update the last user name
                strncpy(lastName, token, sizeof(lastName) - 1);
                lastName[sizeof(lastName) - 1] = '\0'; // Ensure null-termination
            }
        }
    }

    
    if (firstUserFound) {
        printf("The First to join, %s!\n", firstName);
    }
    if (*lastName) {
        printf("Welcome Mr/Mrs.%s! who recently tried \n", lastName);
    }

    // Close the file
    fclose(ffptr);

}
void trim_whitespace(char *str) {
    char *end;

    // Trim leading spaces
    while (isspace((unsigned char)*str)) str++;

    // If all spaces, return
    if (*str == 0)
        return;

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Null-terminate
    *(end + 1) = '\0';
}

void termCustomerPrize(struct customerdata *customers, int count) {
    if (count <= 0) {
        printf("No customer records available to reward.\n");
        return;
    }

    // Initialize the pointer to the first customer
    struct customerdata *highestUsageCustomer = &customers[0];

    // Loop through the customers to find the one with the highest usage
    for (int i = 1; i < count; i++) {
        if (customers[i].usage > highestUsageCustomer->usage) {
            highestUsageCustomer = &customers[i];
        }
    }

    // Print the reward message for the customer with the highest usage
    printf("Congratulations to %s for having the highest usage of %.2f minutes! You've been rewarded with bonus star points.\n",
           highestUsageCustomer->name, highestUsageCustomer->usage);
}


float generate_random_double(float min, float max) 
{
    // Generate a random integer and scale it to the desired range

    float scale = rand() / (float) RAND_MAX;

    return min + scale * (max - min); // Scale to [min, max]
}

void openFile(const char *filename) {
    char command[256];

    snprintf(command, sizeof(command), "notepad \"%s\"", filename); // Quotes to handle filenames with spaces

    int result = system(command);

    if (result != 0) {
        printf("Failed to open file in Notepad. System call returned %d\n", result);
    }
}