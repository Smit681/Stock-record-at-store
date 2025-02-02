//==============================================
//Final assessment   :   PART C 
//==============================================
//Group member1  : Smit Shah
// Student Number: 116605205
// Email         : syshah3@myseneca.ca
//
// Group member2 : Pranami Rajput 
// Student Number: 114255201
// Email         : psrajput@myseneca.ca
//
// Group member3 : Meet Pandya
// Student Number: 116480203
// Email         : mpandya6@myseneca.ca
//
// Section       :  ZBB         
//==============================================

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stock.h"
#include "stockshelper.h"

#define MAX_STOCK_ENTRIES 100
#define MAX_ITEMS_IN_SALE 100
/***************************************************************/
/* Students who are implementing the file reading version for  */
/* bonus marks are allowed to change STOCK_FROM_STDIN to 0     */
/* to enable the program to read from a file.                  */
/***************************************************************/
#define STOCK_FROM_STDIN 0
#define NUM_CATS 7

int main(void)
{
    struct StockRecord storeStock[MAX_STOCK_ENTRIES] = { {{0, 0, 0.0, 0}, 0, 0.0} };
    struct SalesRecord saleItems[MAX_ITEMS_IN_SALE];
    struct SalesRecord topSellers[5];

    int  numStockItems = 0, numSales = 0, numSaleItems, totalSaleItems = 0, cat;
    double sale, totalSales = 0.0;

    numStockItems = readStockItems(storeStock, MAX_STOCK_ENTRIES, STOCK_FROM_STDIN);

    printf("\n");
    centreText(70, '*', " Seneca Groceries - Opening Stock ");
    printf("\n");
    centreText(70, '=', "");
    printf("\n");
    printStockReport(storeStock, numStockItems);

    printf("\n");
    centreText(70, '*', " Now in Sales Mode ");
    printf("\n");
    centreText(70, '=', "");
    printf("\n");
    do
    {
        numSaleItems = readSale(storeStock,  numStockItems, saleItems);
        if (numSaleItems > 0)
        {
            // from here
            sale = printSalesReport(storeStock, saleItems, numSaleItems);
            totalSales += sale;
            totalSaleItems += numSaleItems;
            numSales++;
        }
    } while (numSaleItems > 0);

    printf("\n");
    centreText(70, '*', " End of Day Summary ");
    printf("\n");
    centreText(70, '=', "");
    printf("\n");
    printf("%35s%8.2lf\n", "Cost of items sold before taxes", totalSales);
    printf("%35s%8d\n", "Number of Sales", numSales);
    printf("%35s%8.2lf\n\n", "Average items per sale", totalSaleItems / (double)numSales);

    printf("\n");
    centreText(70, '*', " Closing Stock ");
    printf("\n");
    centreText(70, '=', "");
    printf("\n");
    printStockReport(storeStock, numStockItems);
    printf("\n");
    for (cat = 0; cat < 5; cat++)
    {
        getTopSellers(storeStock, numStockItems, topSellers, 3, cat);
        printTopSellers(storeStock, topSellers, 3, cat);
    }
    for (cat = 5; cat < NUM_CATS; cat++)
    {
        getTopSellers(storeStock, numStockItems, topSellers, 2, cat);
        printTopSellers(storeStock, topSellers, 2, cat);
    }
    return 0;
}


