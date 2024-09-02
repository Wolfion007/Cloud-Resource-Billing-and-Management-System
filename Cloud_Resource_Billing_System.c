//Documentation--Cloud Resource Billing and Management System
/*
Add New Record: Add new customer record.
View List of Records: View all the records at a glance.
Modify Record: Modification of an already existing record.
View Payment: View the bill for a given customer.
Delete Record: The deletion of a record from the memory
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct customerdata{
	
	char name[50];
	char userId[50];
	float usage;   
	float othercomputingresources; //0.56
	float unitstorage;   //1.80
	float unitdatabase; //0.75
	float totalBill;
};

struct customerdata customers[100];



int customerCount=0;

void addrecord();
void viewrecords();
void modifyRecord(char[]);
void viewPayment(char[]);
void searchRecord(char[]);
void deleteRecord(char[]);

int main()
{
    struct customerdata *customers;
    customers=(struct customerdata*)malloc(sizeof(struct customerdata));
	int choice; 
    char userId[15]; 
  
    while (1) { 
         
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
  
        switch (choice) { 
        case 1: 
            addrecord(); 
            break; 
        case 2: 
            viewrecords(); 
            break; 
        case 3: 
            printf( 
                "\nEnter userId to modify record: "); 
            scanf("%s", userId); 
            modifyRecord(userId); 
            break; 
        case 4: 
            printf( 
                "\nEnter userId to view payment: "); 
            scanf("%s", userId); 
            viewPayment(userId); 
            break; 
        case 5: 
            printf( 
                "\nEnter userId to search record: "); 
            scanf("%s", userId); 
            searchRecord(userId); 
            break; 
        case 6: 
            printf( 
                "\nEnter userId to delete record: "); 
            scanf("%s", userId); 
            deleteRecord(userId); 
            break; 
        case 7: 
            return 0; 
        default: 
            printf("\nInvalid choice! Please try again.\n"); 
        } 
    }
	free(customers);
  
}
void addrecord()
{   
	if(customerCount<100)
	{
	customers[customerCount].othercomputingresources=54.0f;
    customers[customerCount].unitdatabase=0.75;
    customers[customerCount].unitstorage=1.80f;
	printf("\nEnter name: "); 
        scanf(" %[^\n]s", customers[customerCount].name); 
        while(getchar()!='\n');
        printf("Enter userId "); 
        scanf("%s", customers[customerCount].userId); 
        while(getchar()!='\n');
        printf("Enter usage (in minutes): "); 
        scanf("%f", &customers[customerCount].usage); 
        customers[customerCount].totalBill 
            = customers[customerCount].usage * customers[customerCount].othercomputingresources*customers[customerCount].unitdatabase*customers[customerCount].unitstorage; 
        customerCount++; 
        printf("\nRecord added successfully!\n"); 	
	}
	
}

void viewrecords()
{
printf("\nName\tUser Id\tUsage(min)\tTotal "
           "Bill($)\n"); 
    for (int i = 0; i < customerCount; i++) { 
        printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name, 
               customers[i].userId, customers[i].usage, 
               customers[i].totalBill); 
    } 		
}

void modifyRecord(char userId[]) 
{ 
    for (int i = 0; i < customerCount; i++) { 
    customers[customerCount].othercomputingresources=54.0f;
    customers[customerCount].unitdatabase=0.75;
    customers[customerCount].unitstorage=1.80f;
        if (strcmp(customers[i].userId, userId) 
            == 0) { 
            printf( 
                "\nEnter new usage (in minutes) for %s: ", 
                customers[i].name); 
            scanf("%f", &customers[i].usage); 
            customers[i].totalBill 
                = customers[i].usage * customers[customerCount].othercomputingresources*customers[customerCount].unitdatabase*customers[customerCount].unitstorage; 
            printf("\nRecord modified successfully!\n"); 
            return; 
        } 
    }
    customerCount=0;
    printf("\nRecord not found!\n"); 
}

void viewPayment(char userId[]) 
{ 
    for (int i = 0; i < customerCount; i++) { 
        if (strcmp(customers[i].userId, userId) 
            == 0) { 
            printf("\nTotal Bill for %s: $%.2f\n", 
                   customers[i].name, 
                   customers[i].totalBill); 
            return; 
        } 
    } 
    printf("\nRecord not found!\n"); 
}

void searchRecord(char userId[]) { 
    printf("\nName\tPhone Number\tUsage(min)\tTotal Bill($)\n"); 
    for (int i = 0; i < customerCount; i++) { 
        if (strcmp(customers[i].userId, userId) == 0) { 
            printf("%s\t%s\t%.2f\t\t%.2f\n", customers[i].name, customers[i].userId, customers[i].usage, customers[i].totalBill); 
            return; 
        } 
    } 
    printf("\nRecord not found!\n"); 
}

void deleteRecord(char userId[]){
	
	for(int i=0; i<customerCount;i++)
	{
		if(strcmp(customers[customerCount].userId,userId)==0){
			for(int j=i;j<customerCount;j++)
			{
				customers[j]=customers[j+1];		
			}
			printf("\nRecord deleted successfully!\n"); 
            return; 
		}
	}
	customerCount=0;
	 printf("\nRecord not found!\n"); 
}