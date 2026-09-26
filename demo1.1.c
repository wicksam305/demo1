//this is demo 2
//level 1.1,in/output demo
#include <stdio.h>
#include <string.h>

int productcount=0;
void showall(void);
void showone(const char*targetCode);

typedef struct
{
    char code[20];//19 numbers
    char name[19];//six chinese characters
    float price;
    char category[13];//four chinese characters
}product;

product products[10];

int loadproducts()
{
    FILE*file;
    productcount=0;
    char line[128];
    product temp;
    file=fopen("products.csv","r");
    if (file==NULL)
    {
        return 0;
    }
    while (fgets(line,128,file)!=NULL)
    {
        if (sscanf(line,"%3[^,],%18[^,],%f,%12[^,\n\r]",temp.code,temp.name,&temp.price,temp.category)==4)
        {
            products[productcount]=temp;
            productcount++;
        }
    }
    fclose(file);
    return productcount;
}

void save()
{
    FILE*file;
    int i;
    file=fopen("products.csv","w");
    if (file==NULL)
    {
        printf("ERROR: no products.csv\n");
        return;
    }
    fprintf(file,"code,name,price,category\n");
    for (i=0;i<productcount;i++)
    {
        fprintf(file,"%s,%s,%.2f,%s\n",products[i].code,products[i].name,products[i].price,products[i].category);
    }
    fclose(file);
}

void initialize()
{
    int i;
    if (loadproducts()>0)
    {
        return;
    }
    product defaults[3]=
    {
        {"001","Cola",    3.50f,"Drink"},
        {"002","Lollipop",0.50f,"Snack"},
        {"003","Noodles", 6.00f,"Food"}
    };
    productcount=3;
    for (i=0;i<productcount;i++)
    {
        products[i]=defaults[i];
    };
    save();
}

void showall()
{
    FILE*file;
    char line[128];
    file=fopen("products.csv","r");
    if (file==NULL)
    {
    printf("ERROR: cannot open products.csv\n");
    return;
    }
    while (fgets(line,sizeof(line),file)!=NULL) 
    {
        printf("%s",line);
    }
    fclose(file);
    printf("\n");
}

void showone(const char*targetCode)
{
    FILE*file;
    char line[128];
    char code[20];
    int found=0;

    file = fopen("products.csv","r");

    if (file==NULL)
    {
        printf("ERROR: cannot open %s\n","products.csv");
        return;
    }

    while (fgets(line, sizeof(line), file)!=NULL)
    {
        if (sscanf(line,"%19[^,]",code)==1 && strcmp(code,targetCode)==0)
            {
            printf("%s",line);
            if (line[strlen(line)-1]!='\n')
            {
                printf("\n");
            }
            found=1;
            break;
        }
    }
    fclose(file);
    if (!found)
    {
        printf("ERROR: code not found\n");
    }
}

int main()
{
    initialize();
    char input[20];
    printf("=== 711 Convenience Store POS Level 1.1 ===\n");
    printf("Commands: <code>, prices, exit, quit\n");
    while (1) 
    {
        printf("> ");
        if (scanf("%19s",input)!=1) 
        {
            break;
        }
        if (strcmp(input,"exit")==0||strcmp(input,"quit")==0) 
            {
            break;
        } 
        else if (strcmp(input,"prices")==0) 
        {
            showall();
        } 
        else 
        {
            showone(input);
        }
    }

    save();
    printf("Bye\n");
    return 0;
}
