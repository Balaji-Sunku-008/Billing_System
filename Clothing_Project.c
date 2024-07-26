#include <stdio.h>
#include <string.h>
int main()
{
     struct items{
        char item[50];
        float price;
        int qty;

    };
    struct orders{
        char customer[50];
        char date[50];
        int numOfItems;
        struct items itm[50];

    };
void generateBillHeader(char name[50],char date[50]){
    printf("\n\n");
        printf("\t   OMG. Clothing");
        printf("\n\t --------------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To:%s",name);
        printf("\n");
        printf("----------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n-----------------------------------------------");
        printf("\n\n");
}
void generateBillBody(char item[50], int qty, float price){
    printf("%s\t\t",item);
        printf("%d\t\t",qty);
        printf("%.2f\t\t",qty * price);
        printf("\n");

}
void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst = 0.06*netTotal,grandTotal=netTotal+2*cgst;
    printf("----------------------------------------\n");
    printf("Sub Total \t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @6%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @6%s\t\t\t%.2f","%",cgst);
    printf("\n-------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n-------------------------------------------");


}

    int opt;
    struct orders ord;
    int n,y,invoiceFound=0;
    float total;
    char saveBill = 'y',contFlag="y";
    FILE *fp;
    struct orders order;
    char name[50];


    printf("\t*********OMG CLOTHING*********");
    printf("\n\nPlease select your operation:\t");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoices");
    printf("\n4.Exit");


    printf("\n\nYou have selected:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt){
        case 1:
            system("clear");
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer,50,stdin);
            ord.customer[strlen(ord.customer)-1] = 0;
            strcpy(ord.date,__DATE__);
            printf("\nPlease Enter the number of items:\t");
            scanf("%d",&n);
            ord.numOfItems = n;
            for(int i=0;i<n;i++){
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t",i+1);
                fgets(ord.itm[i].item,50,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                printf("\nPlease enter the quantity:\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Please enter the unit price:\t");
                scanf("%f",&ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;


            }

            generateBillHeader(ord.customer,ord.date);
            for(int i=0;i<ord.numOfItems;i++){
                    generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);

            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice[y/n]:\t");
            scanf("%s",&saveBill);

            if(saveBill == 'y'){
                fp = fopen("ClothingBill.dat","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite != 0)
                    printf("\nSuccessfully saved");
                else
                    printf("\nError saving");
                fclose(fp);
            }
            break;

            case 2:
            system("clear");
            fp = fopen("ClothingBill.dat","r");
            printf("\n******Your Previous Invoices******\n");
            while(fread(&order,sizeof(struct orders),1,fp)){
                    float tot = 0;
                generateBillHeader(order.customer,order.date);
                for(int i=0;i<order.numOfItems;i++){
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot+=order.itm[i].qty*order.itm[i].price;
                 }
                 generateBillFooter(tot);
            }
            fclose(fp);
            break;
            case 3:
            printf("\nEnter the name of the customer:\t");
            //fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;
            system("clear");
            fp = fopen("ClothingBill.dat","r");
            printf("\t******Invoice of %s******\n",name);
            while(fread(&order,sizeof(struct orders),1,fp)){
                float tot = 0;
                if(!strcmp(order.customer,name)){
                            generateBillHeader(order.customer,order.date);
                for(int i=0;i<order.numOfItems;i++){
                         generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot+=order.itm[i].qty*order.itm[i].price;

                }


                 generateBillFooter(tot);
                 invoiceFound=1;



                }

            }
            if (!invoiceFound){
                printf("Sorry the invoice for this %s does not exist",name);

            }
            fclose(fp);
            break;
            case 4:
                printf("\n\t\t Happy Shopping:)");
                exit(0);
                break;


            default:
            printf("Sorry invalid option");
            break;





    }

    printf("\n\n");

	return 0;
}
