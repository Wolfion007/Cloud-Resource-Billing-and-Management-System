#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 100

struct customerdata
{
    char name[50];
    char userId[50];
    float usage;
    float othercomputingresources; // 54.0.54
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

int main()
{
    int choice;
    char userId[50];

    while (1)
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
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addrecord();
            break;
        case 2:
            viewrecords();
            break;
        case 3:
            printf("\nEnter userId to modify record: ");
            scanf("%s", userId);
            modifyRecord(userId);
            break;
        case 4:
            printf("\nEnter userId to view payment: ");
            scanf("%s", userId);
            viewPayment(userId);
            break;
        case 5:
            printf("\nEnter userId to search record: ");
            scanf("%s", userId);
            searchRecord(userId);
            break;
        case 6:
            printf("\nEnter userId to delete record: ");
            scanf("%s", userId);
            deleteRecord(userId);
            break;
        case 7:
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

    if (customerCount < MAX_CUSTOMERS)
    {
        customers[customerCount].othercomputingresources = 0.54f;
        customers[customerCount].unitdatabase = 0.75f;
        customers[customerCount].unitstorage = 1.80f;

        printf("\nEnter name: ");
        scanf(" %[^\n]s", customers[customerCount].name);
        printf("Enter userId: ");
        scanf("%s", customers[customerCount].userId);
        printf("Enter usage (in minutes): ");
        scanf("%f", &customers[customerCount].usage);

        customers[customerCount].totalBill = customers[customerCount].usage * customers[customerCount].othercomputingresources * customers[customerCount].unitdatabase * customers[customerCount].unitstorage;

        fprintf(fptr, "Name: %s\nUserId: %s\nTotalBill: %.2f\nUsage: %.2f\n\n",
                customers[customerCount].name,
                customers[customerCount].userId,
                customers[customerCount].totalBill,
                customers[customerCount].usage);
        fflush(fptr);

        printf("\nRecord added successfully!\n");

        customerCount++;
    }
    else
    {
        printf("\nMaximum number of records reached.\n");
    }

    fclose(fptr);
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
            }

            fprintf(origFile, "Name: %s\nUserId: %s\nTotalBill: %.2f\nUsage: %.2f\n\n", customers[i].name, customers[i].userId, customers[i].totalBill, customers[i].usage);
            break;
        }
    }
    if (!entered)
    {
        printf("\nRecord not added!\n");
    }

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