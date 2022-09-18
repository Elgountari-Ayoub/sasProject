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
    int code;
    double pricTTC;
    struct tm date;
}purchasedProducts;

Product initProduct(int code, char* name, int quantity, double price);
ProductsList initProductList();


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
ProductsList buyProduct(ProductsList* pl, int code, int productsNumber);

//Search Products By:
//Coded
bool findProductByCode(int code);

//Amount.
bool findProductByAmmount(int quantity);

//Stock status: allows you to display products whose quantity is less than 3.
ProductsList stockStatus(ProductsList pl);

//Alimenter le stock: permet de mettre à jour la quantité après avoir introduit le code produit et la quantité à ajouter.
ProductsList updateStock(ProductsList* pl, int code, int ammount);

//Supprimer les produits par:
//Code
ProductsList DeleteProductByCode(ProductsList* pl, int code);

//Display the total prices of products sold in the current day
double totalPricesToday(purchasedProducts pp);

//Display the average price of products sold on the current day
double averagePricesToday(purchasedProducts pp);

//Display the Max price of products sold on the current day
double maxPriceToday(purchasedProducts pp);

//Display the Min of the prices of the products sold in the current day
double minPriceToday(purchasedProducts pp);


int main()
{
    return 0;
}
