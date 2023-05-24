#include<stdio.h> //header files
#include<string.h>
#include<stdlib.h>

//structure to hold items

struct items{ 
    char item[20];
    float price;
    int qty;
};

struct orders{ 
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

//function to print bill header

void BillHeader(
    char name[50],char date[30])
{
    printf("\n\n");
        printf("\t    AKASH Restaurant");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}
//function to print bill body
void BillBody(
    char item[30],int qty, float price
    )
    {
    printf("%s\t\t",item); 
        printf("%d\t\t",qty); 
        printf("%.2f\t\t",qty * price); 
        printf("\n");
}

//function to print bill footer

void BillFooter(float total)
{
    printf("\n");

    float netTotal=total;
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
}
// main function
int main(){
    
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';
    char name[50];
    FILE *fp;

//loop to display menu

    while(contFlag == 'y')
    {
    system("clear");
    float total = 0;
    int invoiceFound = 0;
    printf("\t============AKASH RESTAURANT============");
    printf("\n\nPlease select your prefered operation");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);

    //switch case to perform operations
    switch(opt){
        case 1:
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        strcpy(ord.date,__DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;
        for(int i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item Name: %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        //print bill

        BillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++)
        BillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);

        //save bill to file

        if(saveBill == 'y'){
            //open file in append mode
            fp = fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else 
            printf("\nError saving");
            fclose(fp);
        }
        break;
        //show all invoices
        case 2:
        system("clear");
        //open file in read mode
        fp = fopen("RestaurantBill.dat","r");
        printf("\n  *****Your Previous Invoices*****\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            BillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
              
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            BillFooter(tot);
        }
        fclose(fp);
        break;
        //search invoice
        case 3:
        printf("Enter the name of the customer:\t");

        //fgetc(stdin);

        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t*****Invoice of %s*****",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
            BillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                tot+=order.itm[i].qty * order.itm[i].price;
            }
                  BillFooter(tot);
            invoiceFound = 1;
            }

        //fclose(fp);

        }
        if(!invoiceFound){
            printf("Sorry the invoice for %s doesnot exists",name);
        }
        fclose(fp);
        break;

        //exit

    case 4:
    printf("\n\t\t Bye Bye :)\n\n");
    exit(0);
    break;
    //default
    default:
    printf("Sorry invalid option");
    break;
    }
    //ask for continue
    printf("\nDo you want to perform another operation? [y/n]:\t");
    scanf("%s",&contFlag);
    }
    return 0;
}