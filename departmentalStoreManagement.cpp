#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

struct user
{
    // int id;
    char fname[10];
    char lname[10];
    char username[20];
    char email[40];
    char password[15];
    char mobile_number[12];
};

struct product
{
    int id;
    char pname[10];
    int price;
    int Qty;
};



int adminpanel()
{   
    FILE *f, *c;
    FILE *fptr;
    FILE *fp;
    char ename[10];
    int eprice,eqty;
    char ch;
    int n;
    struct product pr;
    struct product pr2;
    int choi , eid,did;
    printf("\n********* Menu ***********\n");
    printf(" 1]. List all products \n 2]. Add new Product \n 3]. Edit Product Details \n 4]. Delete Product \n 5]. exit ");
    printf("\n\nEnter your choice : ");
    scanf("%d", &choi);
    switch (choi)
    {
    case 1:
        fptr = fopen("product.txt", "r");
        printf("\n********* List of All products ***********\n");
        printf("Product ID          Product Name               Price          Qty avail\n");
        while (fread(&pr, sizeof(struct product), 1, fptr))
        {
            printf("%d\t\t\t%s\t\t\t%d\t\t\t%d\n", pr.id, pr.pname, pr.price, pr.Qty);
        }
        fclose(fptr);
        
        adminpanel();
        break;
    case 2:
        printf("enter number of product you want to add");
        scanf("%d", &n);
        while (n > 0)
        {
            fp = fopen("product.txt", "a");
            printf("Enter product Id:");
            scanf("%d", &pr.id);
            printf("Enter product name:");
            scanf("%s", &pr.pname);
            printf("Enter product price:");
            scanf("%d", &pr.price);
            printf("Enter product Qty:");
            scanf("%d", &pr.Qty);
            n--;
            fwrite(&pr, sizeof(struct product), 1, fp);
            fclose(fp);
            printf("Product added successfully");
        }
        
        adminpanel();
        break;
    case 3:
        printf("Enter product Id:");
        scanf("%d", &eid);
        printf("Enter product new name:");
        scanf("%s", &ename);
        printf("Enter product new price:");
        scanf("%d", &eprice);
        printf("Enter product new Qty:");
        scanf("%d", &eqty);
        f = fopen("product.txt","r");
        while (fread(&pr , sizeof(struct product),1, f))
        {
            if (pr.id == eid)
            {
              c = fopen("copy.txt","a");
              pr2.id = pr.id;
              strcpy(pr2.pname,ename);
              pr2.price = eprice;
              pr2.Qty = eqty;
              fwrite(&pr2 , sizeof(struct product),1,c);
              fclose(c);
            }
            else
            {
              c = fopen("copy.txt","a");
              pr2.id = pr.id;
              strcpy(pr2.pname,pr.pname);
              pr2.price = pr.price;
              pr2.Qty = pr.Qty;
              fwrite(&pr2 , sizeof(struct product),1,c);
              fclose(c);
            }  
        }
        fclose(f);
        remove("product.txt");
        rename("copy.txt","product.txt");
        adminpanel();
        break;
    case 4:
        printf("Enter product Id:");
        scanf("%d", &eid);
        f = fopen("product.txt","r");
        while (fread(&pr , sizeof(struct product),1, f))
        {
            if (pr.id == eid)
            {
              continue;
            }
            else
            {
              c = fopen("copy.txt","a");
              pr2.id = pr.id;
              strcpy(pr2.pname,pr.pname);
              pr2.price = pr.price;
              pr2.Qty = pr.Qty;
              fwrite(&pr2 , sizeof(struct product),1,c);
              fclose(c);
            }  
        }
        fclose(f);
        remove("product.txt");
        rename("copy.txt","product.txt");
        adminpanel();
        break;

    default :
        break;
}
return 0;
}

int userpanel()
{
    FILE *fp,*fptr;
    int b,n,pid,Qty;
    int  bill =0 ;
    struct product pr;
    fp = fopen("product.txt", "r");
    printf("\n****** List of All products ******\n\n");
    printf("*******************\n");
    printf("Product ID          Product Name               Price \n");
    printf("*******************\n");
    while (fread(&pr, sizeof(struct product), 1, fp))
    {
        printf("%d\t\t\t%s\t\t\t%d\n", pr.id, pr.pname, pr.price);
    }
    printf("\n\n1. Buy Products 2. Exit\t");
    scanf("%d",&b);
    switch (b)
    {
    case 1:
        printf("how many products u want to buy:");
        scanf("%d",&n);
        while (n>0)
        {
            printf("==================================\n");
            printf("Enter product id from above table :");
            scanf("%d",&pid);
            printf("Enter quantity:");
            scanf("%d",&Qty);
            fptr = fopen("product.txt", "r");
            while (fread(&pr, sizeof(struct product), 1, fptr))
            {
                if(pr.id == pid){
                    printf("Product name : %s\n",pr.pname);
                    bill = bill + Qty*pr.price;
                }
            }
            printf("====================================");
            n--;
        }
        if (bill == 0)
        {
           printf("\nPlease Select Correct Id ");
           userpanel();
        }
        else{
            printf("\n\nTotal Payable Amount : %d INR\n\n",bill);
            userpanel();
        }
        break;
    case 2:
        exit(0);
    default:
        break;
    }
    return 0;
}

int login()
{
    FILE *fp;
    int count = 0, choice, uid;
    struct user p;
    char iuser[40], ipaas[15];
    printf("1. User  2. Admin\nYour choice is :");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Enter username:");
        scanf("%s", &iuser);
        printf("Enter Password:");
        scanf("%s", &ipaas);
        fp = fopen("txta.txt", "r");
        while (fread(&p, sizeof(struct user), 1, fp))
        {
            if (strcmp(p.username, iuser) == 0 && strcmp(p.password, ipaas) == 0)
            {
                printf("WELCOME %s \n", p.fname);
                userpanel();
                count++;
            }
        }
        if (count == 0)
        {
            printf("sorry you are not registered ");
        }
        break;
    case 2:
        printf("Enter username:");
        scanf("%s", &iuser);
        printf("Enter Password:");
        scanf("%s", &ipaas);
        fp = fopen("admin.txt", "r");
        while (fread(&p, sizeof(struct user), 1, fp))
        {
            if (strcmp(p.username, iuser) == 0 && strcmp(p.password, ipaas) == 0)
            {
                printf("%s\n%s\n You are an admin", p.fname, p.lname);
                adminpanel();
                count++;
            }
        }
        if (count == 0)
        {
            printf("sorry you are not registered as admin");
        }
    default:
        break;
    }

    return 0;
}

int registration()
{
    FILE *fp;
    struct user p;
    int cho;
    char l;
    printf("1. User  2. Admin\nYour choice is :");
    scanf("%d", &cho);
    switch (cho)
    {
    case 1:
        fp = fopen("txta.txt", "a");
        printf("Enter first name:");
        scanf("%s", &p.fname);
        printf("Enter last name:");
        scanf("%s", &p.lname);
        printf("Enter username:");
        scanf("%s", &p.username);
        printf("Enter email:");
        scanf("%s", &p.email);
        printf("Enter password:");
        scanf("%s", &p.password);
        fwrite(&p, sizeof(struct user), 1, fp);
        fclose(fp);
        printf("\n***************\n");
        printf("You can now login using username password\n");
        printf("***************");
        printf("Press Y to login ");
        scanf("%c",l);
        if (l == 'Y')
        {
            login();
        }
        else
        {
            exit(0);
        }
        
        
        break;
    case 2:
        fp = fopen("admin.txt", "a");
        printf("Enter first name:");
        scanf("%s", &p.fname);
        printf("Enter last name:");
        scanf("%s", &p.lname);
        printf("Enter username:");
        scanf("%s", &p.username);
        printf("Enter email:");
        scanf("%s", &p.email);
        printf("Enter password:");
        scanf("%s", &p.password);
        fwrite(&p, sizeof(struct user), 1, fp);
        fclose(fp);
        printf("\n********\n");
        printf("You are now an admin\n");
        printf("********");
        break;
    default:
        printf("Enter correct choice");
        break;
    }
    return 0;
}

int main()
{
    int ch;
    printf("\n\n*****Welcome****\n\n");
    printf("    1. Login 2. Register  \nYour choice is :");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        login();
        break;
    case 2:
        registration();
        break;
    default:
        break;
    }
    return 0;
}
