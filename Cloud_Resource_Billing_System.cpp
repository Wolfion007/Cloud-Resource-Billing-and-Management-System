//Documentation--Cloud Resource Billing and Management System
/*


*/

#include<stdio.h>



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
void modifyRecord(char);
void viewPayment(char);
void searchRecord(char);
void deleteRecord(char);

int main()
{
	int choice; 
    char userId[15]; 
  
    while (1) { 
        displayMenu(); 
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
                "\nEnter phone number to modify record: "); 
            scanf("%s", userId); 
            modifyRecord(userId); 
            break; 
        case 4: 
            printf( 
                "\nEnter phone number to view payment: "); 
            scanf("%s", userId); 
            viewPayment(userId); 
            break; 
        case 5: 
            printf( 
                "\nEnter phone number to search record: "); 
            scanf("%s", userId); 
            searchRecord(userId); 
            break; 
        case 6: 
            printf( 
                "\nEnter phone number to delete record: "); 
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
	if(customerCount<100)
	{
	customers[customerCount].othercomputingresources=0.56f;
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
    customers[customerCount].othercomputingresources=0.56f;
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
    customersCount=0;
    printf("\nRecord not found!\n"); 
}

void viewPayment(char userId[]) 
{ 
    for (int i = 0; i < customerCount; i++) { 
        if (strcmp(customers[i].phoneNumber, phoneNumber) 
            == 0) { 
            printf("\nTotal Bill for %s: $%.2f\n", 
                   customers[i].name, 
                   customers[i].totalBill); 
            return; 
        } 
    } 
    printf("\nRecord$not$found!\n"); 
}

void searchRecord(char phoneNumber[]) { 
    printf("\nName\tPhone Number\tUsage(min)\tTotal Bill($)\n"); 
    for (int i = 0; i < customerCount; i++) { 
        if (strcmp(customers[i].phoneNumber, phoneNumber) == 0) { 
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
	customersCount=0;
	 printf("\nRecord not found!\n"); 
}