#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
//******************************GLOBAL DECLARATION

//A product is identified by: its code, its name, its quantity, and its price.
typedef struct
{
    int code;
    char *name;
    int quantity;//quantit?
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
void addProduct(ProductsList* pl, Product p);

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
bool buyProduct(ProductsList* pl, PurchasedProductsList* ppl, int code, int quantity);

//Search Products By:
//Coded
int findProductByCode(ProductsList* pl, int code);

//Quantitiy.
bool findProductByQuantity(ProductsList* pl, int quantity);

//Stock status: allows you to display products whose quantity is less than 3.
bool stockStatus(ProductsList* pl);

//Alimenter le stock: permet de mettre ? jour la quantit? apr?s avoir introduit le code produit et la quantit? ? ajouter.
bool updateStock(ProductsList* pl, int code,  int quantity);

//Supprimer les produits par:
//Code
bool DeleteProductByCode(ProductsList* pl, int code);

//Display the total prices of products sold in the current day
double totalPricesToday(PurchasedProductsList* ppl);

//Display the average price of products sold on the current day
double averagePricesToday(PurchasedProductsList* ppl);

//Display the Max price of products sold on the current day
double maxPriceToday(PurchasedProductsList* ppl);

//Display the Min of the prices of the products sold in the current day
double minPriceToday(PurchasedProductsList* ppl);

//Helper functions
bool checkQuantity(ProductsList* pl, int code, int quantity);





int main()
{
    Product p;
    ProductsList pl;
    PurchasedProduct pp;
    PurchasedProductsList ppl;

    pl = initProductList();
    ppl = initPurchasedProductsList();

    int code;
    char name[20];
    int quantity;
    double price;

    ////////////
    int productsNumber; // store the number of the products that the user want to store.

    int op;//operation
    int subOp;
    int pos; //store the position of a product in the product list
    bool isBought;//store true if a product bought, other ways store false;
    bool isDone;
    ///////////
    double total, avg, min, max;



    START:
        system("cls");
        mainMenu();
        printf("=> ");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
                printf("nom      : ");
                scanf("%s", name);

                printf("code     : ");
                scanf("%d", &code);

                printf("price    : ");
                scanf("%lf", &price);

                printf("quantity : ");
                scanf("%d", &quantity);

                p = initProduct(code, name, quantity, price);
                addProduct(&pl, p);
                //displayProduct(p);
                pressKey();
                goto START;
            case 2:
                printf("nombre des produits : ");
                scanf("%d", &productsNumber);
                for (int i = 0; i <productsNumber; i++)
                {
                    printf("nom      : ");
                    scanf("%s", name);

                    printf("code     : ");
                    scanf("%d", &code);

                    printf("price    : ");
                    scanf("%lf", &price);

                    printf("quantity : ");
                    scanf("%d", &quantity);

                    p = initProduct(code, name, quantity, price);
                    addProduct(&pl, p);
                    printf("\n");
                }
                //displayProducts(pl);
                pressKey();
                goto START;
            case 3:
                sortByMenu();
                printf("=> ");
                scanf("%d", &subOp);
                switch(subOp)
                {
                    case 1:
                        ProductsAlphabeticallyAsc(&pl);
                        printf("\n\n");
                        displayProducts(pl);
                        pressKey();
                        goto START;
                    case 2:
                        ProductsByPriceDesc(&pl);
                        printf("\n\n");
                        displayProducts(pl);
                        pressKey();
                        goto START;
                    default:
                        printf("Invalis input, ");
                        pressKey();
                        goto START;
                }
            case 4:
                printf("code : ");
                scanf("%d", &code);

                printf("quantity : ");
                scanf("%d", &quantity);
                isBought = buyProduct(&pl, &ppl, code, quantity);
                if(isBought)
                {
                    printf("operation reussie\n");
                }
                else
                {
                    printf("Le operation a echoue\n");
                }
                //displayPurchasedProductsList(&ppl);
                pressKey();
                goto START;
            case 5:
                searchByMenu();
                printf("=> ");
                scanf("%d", &subOp);
                switch(subOp)
                {
                    case 1:
                        printf("code = ");
                        scanf("%d", &code);
                        pos = findProductByCode(&pl, code);
                        if(pos != -1)
                        {
                            printf("\n\n");
                            displayProduct(pl.products[pos]);
                        }
                        else
                        {
                            printf("le produit de code %d ne exist pas dans la list des produit >:\n", code);
                        }
                        pressKey();
                        goto START;
                    case 2:
                        printf("Quantitee = ");
                        scanf("%d", &quantity);
                        isDone = findProductByQuantity(&pl, quantity);
                        if(!isDone)
                        {
                            printf("le produit de quantity %d ne exist pas dans la list des produit >:\n", quantity);
                        }
                        pressKey();
                        goto START;
                    default:
                        printf("Invalis input, ");
                        pressKey();
                        goto START;
                }

             case 6 :
                isDone = stockStatus(&pl);
                if(!isDone)
                {
                    printf("Le operation a echoue\n");
                }
                pressKey();
                goto START;

            case 7:
                printf("code = ");
                scanf("%d", &code);

                printf("Quantitee = ");
                scanf("%d", &quantity);
                isDone =  updateStock(&pl, code, quantity);
                if(isDone)
                {
                    printf("operation reussie\n");
                }
                else
                {
                    printf("Le operation a echoue\n");
                }
                pressKey();
                goto START;
            case 8:
                printf("code = ");
                scanf("%d", &code);

                isDone = DeleteProductByCode(&pl, code);
                if(isDone)
                {
                    printf("operation reussie\n");
                }
                else
                {
                    printf("Le operation a echoue\n");
                }
                pressKey();
                goto START;

            case 9:
                salesStatisticsMenu();
                printf("=> ");
                scanf("%d", &subOp);

                switch(subOp)
                {
                    case 1 :
                        total = totalPricesToday(&ppl);
                        printf("le total des prix des produits vendus en journee courante = %f\n", total);
                        pressKey();
                        goto START;
                    case 2 :
                        avg = averagePricesToday(&ppl);
                        printf("Afficher la moyenne des prix des produits vendus en journee courante = %f\n", avg);
                        pressKey();
                        goto START;
                    case 3:
                        min = minPriceToday(&ppl);
                        printf("Afficher le Min des prix des produits vendus en journee courante = %f\n", min);
                        pressKey();
                        goto START;
                    case 4:
                        max = maxPriceToday(&ppl);
                        printf("Afficher le Max des prix des produits vendus en journee courante = %f\n", max);
                        pressKey();
                        goto START;

                }

            case 10:
                printf("Merci pour la visite\n");
                return 0;
        }

    return 0;
}
    //***********************Helper functions******************************
    void mainMenu()
    {
        printf("\t\t\t\tWelcome In The Pharmacy Managment System\n\n");
        //printf("\t\t ___________________________________________________\n");
        printf("\t\t 1  - Ajouter un nouveau produit                   \n\n");
        printf("\t\t 2  - Ajouter plusieurs nouveaux produits          \n\n");
        printf("\t\t 3  - Lister tous les produits par:                \n\n");
        printf("\t\t 4  - Acheter produit                              \n\n");
        printf("\t\t 5  - Rechercher les produits Par :                \n\n");
        printf("\t\t 6  - Etat du stock                                \n\n");
        printf("\t\t 7  - Alimenter le stock                           \n\n");
        printf("\t\t 8  - Supprimer les produits par code              \n\n");
        printf("\t\t 9  - Statistique de vente:                        \n\n");
        printf("\t\t 10 - Quitter                                      \n");
        //printf("\t\t ___________________________________________________\n\n");
    }

    void searchByMenu()
    {
        //printf("\t\t\t\t _______________________________________________\n");
        printf("\t\t\t\t 1  - Code                                     \n\n");
        printf("\t\t\t\t 2  - Quantitee                                \n\n");
        //printf("\t\t\t\t _______________________________________________\n\n");
    }
    void sortByMenu()
    {
        //printf("\t\t\t\t _______________________________________________\n");
        printf("\t\t\t\t 1  - lister tous les produits selon le ordre alphabetique  croissant du nom.\n\n");
        printf("\t\t\t\t 2  - lister tous les produits selon le ordre  decroissant du prix\n\n");
        //printf("\t\t\t\t _______________________________________________\n\n");
    }

    void salesStatisticsMenu()
    {
        //printf("\t\t\t\t _______________________________________________\n");
        printf("\t\t\t\t 1  - Afficher le total des prix des produits vendus en journee courante   \n\n");
        printf("\t\t\t\t 2  - Afficher la moyenne des prix des produits vendus en journee courante \n\n");
        printf("\t\t\t\t 3  - Afficher le Max des prix des produits vendus en journee courante     \n\n");
        printf("\t\t\t\t 4  - Afficher le Min des prix des produits vendus en journee courante     \n\n");
        //printf("\t\t\t\t _______________________________________________\n\n");
    }

    void pressKey()
    {
        printf("Press any key to continue...\n");
        getch();
    }

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


    void displayPurchasedProduct(PurchasedProduct pp)
    {
        printf("code  : %\i\n", pp.code);
        printf("price : %lf\n", pp.priceTTC);
        printf("date  : %d-%d-%d-%d-%d-%d\n\n", pp.date.year, pp.date.mon, pp.date.day, pp.date.hour, pp.date.min ,pp.date.sec);
    }

    void displayProducts(ProductsList* pl)
    {
        for (int i = 0; i < pl->len; i++)
        {
            displayProduct(pl->products[i]);
        }
    }

    void displayPurchasedProductsList(PurchasedProductsList* ppl)
    {
        for (int i = 0; i < ppl->len; i++)
        {
            displayPurchasedProduct(ppl->pps[i]);
        }
    }

    void addPurchasedProduct(PurchasedProductsList* ppl, PurchasedProduct pp)
    {
        ppl->size++;
        ppl->pps = realloc(ppl->pps, ppl->size * sizeof(*ppl->pps));
        ppl->pps[ppl->len] = pp;
        ppl->len++;

    }


    bool isPurchasedToday(PurchasedProduct pp)
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        if(pp.date.year == tm.tm_year + 1900 && pp.date.mon == tm.tm_mon + 1 && pp.date.day == tm.tm_mday )
        {
            return true;
        }
        return false;

    }

    int PurchasedProductCount(PurchasedProductsList* ppl)
    {
        int count = 0;
        for (int i = 0; i < ppl->len; i++)
        {
            if(isPurchasedToday(ppl->pps[i]))
            {
                count++;
            }
        }
        return count;

    }
    //**********************************************






Product initProduct(int code, char* name, int quantity, double price)
{
    Product p;

    p.code = code;
    p.name = malloc(strlen(name) + 1);
    strcpy(p.name, name);

    if(price >= 0 && quantity >= 0)
    {
        p.quantity = quantity;
        p.price = price;////p.price = price;
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
void addProduct(ProductsList* pl, Product p)
{
    pl->size++;
    pl->products = realloc(pl->products, (pl->size) * sizeof(*pl->products));
    pl->products[pl->len] = p;
    pl->len++;

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

bool findProductByQuantity(ProductsList* pl, int quantity)
{
    bool exist = false;
    for(int i = 0; i < pl->len; i++)
    {
        if(pl->products[i].quantity == quantity)
        {
            exist = true;
            displayProduct(pl->products[i]);
        }
    }
    return exist;
}

//Stock status: allows you to display products whose quantity is less than 3.
bool stockStatus(ProductsList* pl)
{
    for (int i = 0; i < pl->len; i++)
    {
        if(pl->products[i].quantity < 3 && pl->products[i].quantity >= 0)
        {
            displayProduct(pl->products[i]);
            return true;
        }
    }
    return false;
}

//Alimenter le stock: permet de mettre ? jour la quantit? apr?s avoir introduit le code produit et la quantit? ? ajouter.
bool updateStock(ProductsList* pl, int code,  int quantity)
{
    int pos = findProductByCode(pl, code);
    if(pos != -1 && quantity >= 0)
    {
        pl->products[pos].quantity += quantity;
        return true;
    }
    return false;
}
//Supprimer les produits par:
//Code
bool DeleteProductByCode(ProductsList* pl, int code)
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
        return true;

    }
    return false;
}

bool buyProduct(ProductsList* pl, PurchasedProductsList* ppl, int code, int quantity)
{
    bool isInStock = checkQuantity(pl, code, quantity);

    if(isInStock)
    {
        int pos = findProductByCode(pl, code);

        int code = pl->products[pos].code;
        double price =  pl->products[pos].price * quantity;

        PurchasedProduct pp;
        pp = initPurchasedProduct(code, price);

        addPurchasedProduct(ppl,pp);

        pl->products[pos].quantity -= quantity;

        return true;
    }
    return false;;
}

//Display the total prices of products sold in the current day
double totalPricesToday(PurchasedProductsList* ppl)
{
    double total = 0;
    for (int i = 0; i < ppl->len; i++)
    {
        if(isPurchasedToday(ppl->pps[i]))
        {
            total += ppl->pps[i].priceTTC;
        }
    }
    return total;
}


//Display the average price of products sold on the current day
double averagePricesToday(PurchasedProductsList* ppl)
{
    double total = totalPricesToday(ppl);
    int ppNumber = PurchasedProductCount(ppl);
    double avg = total/(double)ppNumber;
    return avg;
}

//Display the Max price of products sold on the current day
double maxPriceToday(PurchasedProductsList* ppl)
{
    double max = ppl->pps[0].priceTTC;
    for (int i = 1; i < ppl->len; i++)
    {
        if(ppl->pps[i].priceTTC > max)
        {
            max = ppl->pps[i].priceTTC;
        }
    }
    return max;
}

//Display the Min of the prices of the products sold in the current day
double minPriceToday(PurchasedProductsList* ppl)
{
    double min = ppl->pps[0].priceTTC;
    for (int i = 1; i < ppl->len; i++)
    {
        if(ppl->pps[i].priceTTC < min)
        {
            min = ppl->pps[i].priceTTC;
        }
    }
    return min;
}



