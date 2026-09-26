//this is demo 1
//level 1,documentary demo
#include <stdio.h>

int productcount=0;
char line[1024];

typedef struct
{
    char code[4];//three numbers
    char name[19];//six chinese characters
    float price;
    char category[13];//four chinese characters
}product;

product products[10];

int loadproducts()
{
    FILE*file;
    char line[128];
    product temp;
    file=fopen("products.csv",".r");
    if (file==NULL)
    {
        return 0;
    }
    while (fgets(line,1024,file)!=NULL)
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

int main()
{
    loadproducts();
    initialize();
    printf("=== 711 Convenience Store POS ===\n");
    save();
    printf("Bye\n");
}
