#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 10

typedef struct 
{
    char code[20];
    char name[20];
    float price;
    char category[20];
} product;

product products[MAX_PRODUCTS];
int productcount = 0;

int loadProducts(void)
{
    FILE *file = fopen("products.csv", "r");
    char line[256];

    if (file == NULL) 
    {
        return 0;
    }

    productcount = 0;

    if (fgets(line, sizeof(line), file) == NULL) 
    {
        fclose(file);
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) 
    {
        product p;

        if (sscanf(line, "%19[^,],%19[^,],%f,%19[^,\n\r]",
                   p.code, p.name, &p.price, p.category) == 4) {
            if (productcount < MAX_PRODUCTS) {
                products[productcount++] = p;
            }
        }
    }

    fclose(file);
    return productcount;
}

static void saveProducts(void)
{
    FILE *file = fopen("products.csv", "w");
    int i;

    if (file == NULL) {
        printf("ERROR: cannot open products.csv for writing\n");
        return;
    }

    fprintf(file, "code,name,price,category\n");

    for (i = 0; i < productcount; i++) {
        fprintf(file, "%s,%s,%.2f,%s\n",
                products[i].code,
                products[i].name,
                products[i].price,
                products[i].category);
    }

    fclose(file);
}

static void initialize(void)
{
    product defaults[3] = {
        {"001", "Cola", 3.50f, "Drink"},
        {"002", "Lollipop", 0.50f, "Snack"},
        {"003", "Noodles", 6.00f, "Food"}
    };
    int i;

    if (loadProducts() > 0) {
        return;
    }

    productcount = 3;
    for (i = 0; i < productcount; i++) {
        products[i] = defaults[i];
    }

    saveProducts();
}

static void showall(void)
{
    FILE *file = fopen("products.csv", "r");
    char line[256];

    if (file == NULL) {
        printf("ERROR: cannot open products.csv\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
    printf("\n");
}

static void showone(const char *targetCode)
{
    FILE *file = fopen("products.csv", "r");
    char line[256];
    char code[20];
    int found = 0;

    if (file == NULL) {
        printf("ERROR: cannot open products.csv\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%19[^,]", code) == 1 &&
            strcmp(code, targetCode) == 0) {
            printf("%s", line);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("ERROR: code not found\n");
    }
}

int main(void)
{
    char input[20];

    initialize();

    printf("=== 711 Convenience Store POS Level 1.1 ===\n");
    printf("Commands: <code>, prices, exit, quit\n");

    while (1) {
        printf("> ");
        if (scanf("%19s", input) != 1) {
            break;
        }

        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        } else if (strcmp(input, "prices") == 0) {
            showall();
        } else {
            showone(input);
        }
    }

    saveProducts();
    printf("Bye\n");
    return 0;
}