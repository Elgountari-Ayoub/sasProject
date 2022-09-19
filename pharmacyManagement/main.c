#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
//******************************GLOBAL DECLARATION

//A product is identified by: its code, its name, its quantity, and its price.
typedef struct
{
    int code;
    char *name;
    int quantity;//quantité
    double price;
}Product;

typedef struct
{
    Product* products;
    int len;
    int size;
}ProductsList;

typedef struct
{
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int sec;
}Date;

typedef struct
{
    int code;
    double priceTTC;
    Date date;

}PurchasedProduct;

typedef struct
{
    PurchasedProduct* pps;
    int len;
    int size;
}PurchasedProductsList;

Product initProduct(int code, char* name, int quantity, double price);
ProductsList initProductList();
PurchasedProduct initPurchasedProduct(int code, double price);
PurchasedProductsList initPurchasedProductsList();


//Add a new product
ProductsList addProduct(ProductsList* pl, Product p);

//Add many new products
//ProductsList addProducts(ProductsList *pl, int productsNumber);

//List all products (Name, price, price including VAT):
//N.B: each product has a Price including VAT = Price + 15% of the price
//- list all products in ascending alphabetical order of name.
int ProductsAlphabeticallyAsc(ProductsList* pl);

//- list all products in descending order of price.
int ProductsByPriceDesc(ProductsList* pl);


//Buy product: allows you to update the quantity after entering the product code and the quantity to be deducted
//      N.B: For each product purchased, you must record the price including VAT and the date of purchase.
ProductsList buyProduct(ProductsList* pl, PurchasedProductsList* ppl, int code, int quantity);

//Search Products By:
//Coded
int findProductByCode(ProductsList* pl, int code);

//Quantitiy.
int findProductByQuantity(ProductsList* pl, int quantity);

//Stock status: allows you to display products whose quantity is less than 3.
ProductsList stockStatus(ProductsList* pl);

//Alimenter le stock: permet de mettre à jour la quantité après avoir introduit le code produit et la quantité à ajouter.
ProductsList updateStock(ProductsList* pl, int code,  int quantity);

//Supprimer les produits par:
//Code
ProductsList DeleteProductByCode(ProductsList* pl, int code);

//Display the total prices of products sold in the current day
double totalPricesToday(PurchasedProductsList pp);

//Display the average price of products sold on the current day
double averagePricesToday(PurchasedProductsList pp);

//Display the Max price of products sold on the current day
double maxPriceToday(PurchasedProductsList pp);

//Display the Min of the prices of the products sold in the current day
double minPriceToday(PurchasedProductsList pp);

//Helper functions
bool checkQuantity(ProductsList* pl, int code, int quantity);
int main()
{
    return 0;
}

Product initProduct(int code, char* name, int quantity, double price)
{
    Product p;

    p.code = code;
    p.name = malloc(strlen(name) + 1);
    strcpy(p.name, name);

    if(price >= 0 && quantity >= 0)
    {
        p.quantity = quantity;
        p.price = price;
    }
    else
    {
        return;
    }
    return p;
}

ProductsList initProductList()
{
    ProductsList pl;
    pl.len = 0;
    pl.products = calloc(1, sizeof(*pl.products));
    pl.size = 1;
    return pl;
}

PurchasedProduct initPurchasedProduct(int code, double price)
{
    PurchasedProduct pp;

    pp.code = code;
    pp.priceTTC = price + (price * 0.15);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    pp.date.year = tm.tm_year + 1900;
    pp.date.mon = tm.tm_mon + 1;
    pp.date.day = tm.tm_mday;
    pp.date.hour= tm.tm_hour;
    pp.date.min = tm.tm_min;
    pp.date.sec = tm.tm_sec;
    return pp;
}
PurchasedProductsList initPurchasedProductsList()
{
    PurchasedProductsList ppl;
    ppl.len = 0;
    ppl.pps = calloc(1, sizeof(*ppl.pps));
    ppl.size = 1;
    return ppl;
}


//Add a new product
ProductsList addProduct(ProductsList* pl, Product p)
{
    pl->size++;
    pl->products = realloc(pl->products, (pl->size) * sizeof(*pl->products));
    pl->products[pl->len] = p;
    pl->len++;
    return *pl;
}

int ProductsAlphabeticallyAsc(ProductsList* pl)
{
    Product tempP;
    int len = pl->len;
    int i,j;
    for(i=0;i<len;i++){
      for(j=i+1;j<len;j++){
         if(strcmp(pl->products[i].name,pl->products[j].name)>0){
            tempP = pl->products[i];
            pl->products[i] = pl->products[j];
            pl->products[j] = tempP;
        }
      }
   }
}

int ProductsByPriceDesc(ProductsList* pl)
{
    Product tempP;
    int len = pl->len;
    int i,j;
   for(i=0;i<len;i++){
      for(j=i+1;j<len;j++){
        if(pl->products[j].price > pl->products[i].price)
        {
            tempP = pl->products[i];
            pl->products[i] = pl->products[j];
            pl->products[j] = tempP;
        }
      }
   }
}

int findProductByCode(ProductsList* pl, int code)
{
    int pos = -1;
    for(int i = 0; i < pl->len; i++)
    {
        if(pl->products[i].code == code)
        {
            pos = i;
            return pos;
        }
    }

    return pos;
}

int findProductByQuantity(ProductsList* pl, int quantity)
{
    for(int i = 0; i < pl->len; i++)
    {
        if(pl->products[i].quantity == quantity)
        {
            displayProduct(pl->products[i]);
        }
    }
    return 0;
}

//***********************Helper functions******************************
//returns true if the demanded quantity <= existing quantity
bool checkQuantity(ProductsList* pl, int code, int quantity)
{
    int pos = findProductByCode(pl, code);
    if(pos != -1)
    {
        if( quantity <= pl->products[pos].quantity)
        {
            return true;
        }
    }
    return false;
}

void displayProduct(Product p)
{
    printf("name : %s\n", p.name);
    printf("code : %\i\n", p.code);
    printf("price : %lf\n", p.price);
    printf("quantity : %d\n\n", p.quantity);
}

void displayProducts(ProductsList* pl)
{
    for (int i = 0; i < pl->len; i++)
    {
        displayProduct(pl->products[i]);
    }
}

void addPurchasedProduct(PurchasedProductsList* ppl, PurchasedProduct pp)
{
    ppl->size++;
    ppl->pps = realloc(ppl->pps, ppl->size * sizeof(*ppl->pps));
    ppl->pps[ppl->len] = pp;
    ppl->len++;

}
//**********************************************
//Stock status: allows you to display products whose quantity is less than 3.
ProductsList stockStatus(ProductsList* pl)
{
    for (int i = 0; i < pl->len; i++)
    {
        if(pl->products[i].quantity < 3 && pl->products[i].quantity >= 0)
        {
            displayProduct(pl->products[i]);
        }
    }
    return *pl;
}

//Alimenter le stock: permet de mettre à jour la quantité après avoir introduit le code produit et la quantité à ajouter.
ProductsList updateStock(ProductsList* pl, int code,  int quantity)
{
    int pos = findProductByCode(pl, code);
    if(pos != -1 && quantity >= 0)
    {
        printf("pos = %i\n", pos);
        pl->products[pos].quantity += quantity;
    }
    return *pl;
}
//Supprimer les produits par:
//Code
ProductsList DeleteProductByCode(ProductsList* pl, int code)
{
    int pos = findProductByCode(pl, code);
    if(pos != -1)
    {
        for (int i = pos; i < pl->len - 1; i++)
        {
            pl->products[i] = pl->products[i+1];
        }
        pl->size--;
        pl->products = realloc(pl->products, (pl->size) * sizeof(*pl->products));
        pl->len--;
        return *pl;

    }
}

ProductsList buyProduct(ProductsList* pl, PurchasedProductsList* ppl, int code, int quantity)
{
    bool isInStock = checkQuantity(pl, code, quantity);

    if(isInStock)
    {
        int pos = findProductByCode(pl, code);

        int code = pl->products[pos].code;
        double priceTTC =  pl->products[pos].price + (pl->products[pos].price * 0.15);

        PurchasedProduct pp;
        pp = initPurchasedProduct(code, priceTTC);

        addPurchasedProduct(ppl,pp);

        //DeleteProductByCode(pl, code);

        pl->products[pos].quantity -= quantity;

    }
    return *pl;
}
