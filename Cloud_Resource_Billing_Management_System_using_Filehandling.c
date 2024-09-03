#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct customerdata {
    char name[50];
    char userId[50];
    float usage;
    float othercomputingresources; // 0.56
    float unitstorage;             // 1.80
    float unitdatabase;            // 0.75
    float totalBill;
};

struct customerdata customers[100];
int customerCount = 0;

void addrecord();
void viewrecords();
void modifyRecord(char[]);
void viewPayment(char[]);
void searchRecord(char[]);
void deleteRecord(char[]);

FILE *fptr;

int main() {
    int choice;
    char userId[15];

    while (1) {
        printf("\nEnter your choice:\n1. Add Record\n2. View Records\n3. Modify Record\n4. View Payment\n5. Search Record\n6. Delete Record\n7. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
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

void addrecord() {
    fptr = fopen("Addrecords.txt", "a+"); // Open in append mode
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    if (customerCount < 100) {
        struct customerdata newCustomer;
        newCustomer.othercomputingresources = 54.0f;
        newCustomer.unitdatabase = 0.75;
        newCustomer.unitstorage = 1.80f;

        printf("\nEnter name: ");
        scanf(" %[^\n]s", newCustomer.name);
        printf("Enter userId: ");
        scanf("%s", newCustomer.userId);
        printf("Enter usage (in minutes): ");
        scanf("%f", &newCustomer.usage);

        newCustomer.totalBill = newCustomer.usage * newCustomer.othercomputingresources * newCustomer.unitdatabase * newCustomer.unitstorage;

        // Write record to file
        fprintf(fptr, "%s %s %.2f %.2f\n", newCustomer.name, newCustomer.userId, newCustomer.usage, newCustomer.totalBill);

        customerCount++;
        printf("\nRecord added successfully!\n");
    }

    fclose(fptr); // Close the file
}

void viewrecords() {
    fptr = fopen("Addrecords.txt", "r"); // Open in read mode
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nName\tUser Id\tUsage(min)\tTotal Bill($)\n");

    char name[50], userId[50];
    float usage, totalBill;
    while (fscanf(fptr, "%s %s %f %f", name, userId, &usage, &totalBill) != EOF) {
        printf("%s\t%s\t%.2f\t\t%.2f\n", name, userId, usage, totalBill);
    }

    fclose(fptr); // Close the file
}

void modifyRecord(char userId[]) {
    FILE *tempFile;
    fptr = fopen("Addrecords.txt", "r"); // Open original file in read mode
    tempFile = fopen("Temp.txt", "w");   // Open temp file in write mode

    if (fptr == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char name[50], user_id[50];
    float usage, totalBill;
    int found = 0;

    while (fscanf(fptr, "%s %s %f %f", name, user_id, &usage, &totalBill) != EOF) {
        if (strcmp(user_id, userId) == 0) {
            found = 1;
            printf("\nEnter new usage (in minutes) for %s: ", name);
            scanf("%f", &usage);
            totalBill = usage * 54.0f * 0.75 * 1.80;
            printf("\nRecord modified successfully!\n");
        }

        // Write to temp file, whether modified or not
        fprintf(tempFile, "%s %s %.2f %.2f\n", name, user_id, usage, totalBill);
    }

    if (!found) {
        printf("\nRecord not found!\n");
    }

    fclose(fptr);      // Close original file
    fclose(tempFile);  // Close temp file

    remove("Addrecords.txt");          // Delete the original file
    rename("Temp.txt", "Addrecords.txt"); // Rename temp file to original file
}

void viewPayment(char userId[]) {
    fptr = fopen("Addrecords.txt", "r"); // Open file in read mode
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char name[50], user_id[50];
    float usage, totalBill;
    int found = 0;

    while (fscanf(fptr, "%s %s %f %f", name, user_id, &usage, &totalBill) != EOF) {
        if (strcmp(user_id, userId) == 0) {
            printf("\nTotal Bill for %s: $%.2f\n", name, totalBill);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRecord not found!\n");
    }

    fclose(fptr); // Close the file
}

void searchRecord(char userId[]) {
    fptr = fopen("Addrecords.txt", "r"); // Open file in read mode
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char name[50], user_id[50];
    float usage, totalBill;
    int found = 0;

    while (fscanf(fptr, "%s %s %f %f", name, user_id, &usage, &totalBill) != EOF) {
        if (strcmp(user_id, userId) == 0) {
            printf("\nName\tUser Id\tUsage(min)\tTotal Bill($)\n");
            printf("%s\t%s\t%.2f\t\t%.2f\n", name, user_id, usage, totalBill);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRecord not found!\n");
    }

    fclose(fptr); // Close the file
}

void deleteRecord(char userId[]) {
    FILE *tempFile;
    fptr = fopen("Addrecords.txt", "r"); // Open original file in read mode
    tempFile = fopen("Temp.txt", "w");   // Open temp file in write mode

    if (fptr == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char name[50], user_id[50];
    float usage, totalBill;
    int found = 0;

    while (fscanf(fptr, "%s %s %f %f", name, user_id, &usage, &totalBill) != EOF) {
        if (strcmp(user_id, userId) != 0) {
            // Write all records except the one to delete
            fprintf(tempFile, "%s %s %.2f %.2f\n", name, user_id, usage, totalBill);
        } else {
            found = 1;
        }
    }

    if (found) {
        printf("\nRecord deleted successfully!\n");
    } else {
        printf("\nRecord not found!\n");
    }

    fclose(fptr);      // Close original file
    fclose(tempFile);  // Close temp file

    remove("Addrecords.txt");          // Delete the original file
    rename("Temp.txt", "Addrecords.txt"); // Rename temp file to original file
}
