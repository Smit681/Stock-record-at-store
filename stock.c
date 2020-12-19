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
#include <ctype.h>
#include <stdlib.h>
#include "stock.h"
#include "stockshelper.h"
#include<string.h>
#define MAX_STOCK_ENTRIES 100

//read data from the file
int readStockItems(struct StockRecord* stockrecord, int max_entries, int stdi_stock)
{
	int index = 0;
	FILE* Fpointer;
	Fpointer = fopen("Stocks.txt", "r");
	if (Fpointer == NULL)
	{
		printf("Stock file is missing");
	}
	else
	{
		while (fscanf(Fpointer, "%d%*c%d%*c%lf%*c%d%*c%[^\n]\n",
			&(stockrecord[index]).quantity, &(stockrecord[index]).productinfo.category_indetification,
			&(stockrecord[index]).productinfo.price, &(stockrecord[index]).productinfo.byweight,
			&(stockrecord[index]).productinfo.product_name) == 5)
		{
			index++;
		}
		
		fclose(Fpointer);
	}
	
	return index;
}

//print the headings with design
void centreText(int coloums, char design, char* heading)
{
	int headinglen = strlen(heading);
	for (int i = 1; i <= (coloums - 2 - headinglen) / 2; i++)
	{
		printf("%c", design);
	}
	printf("%s", heading);
	for (int i = 1; i <= (coloums - 2 - headinglen) / 2; i++)
	{
		printf("%c", design);
	}
	return;
}

//print stockrecord 
void printStockReport(struct StockRecord* stockrecord, int numstockitems)
{
	printf("ID  Product               Category      Price   Quantity \n");

	for (int i = 0; i < numstockitems; i++)
	{
		printf("%2d  ", i + 1);
		printf("%-22s", (stockrecord[i]).productinfo.product_name);
		printf("%-12s", getcategory((stockrecord[i]).productinfo.category_indetification));
		printf("%6.2f", (stockrecord[i]).productinfo.price);
		printf("%9d", (stockrecord[i]).quantity);
		printf("\n");
	}
	return;
}

//read user's shoping list
int readSale(struct StockRecord* stockrecord, int numstockitems, struct SalesRecord* salesrecord)
{
	int numsaleitems = 0, j = 0,k=0,flag=0,index =0;
	char str[20] = "\0";
	int check = 0;
	do
	{
		printf("Enter a product ID to purchase, and the quantity (0 to stop): ");
		do
		{
			char IDstr[15] = {0};
			char qstr[15] = {0};
			
			gets_s(str, 20);
			if (str[0] == '0')
				break;
			splitstring(str, IDstr, qstr);
			int Id = checkint(IDstr) - 1;
			double que = checkdouble(qstr);
			check = checkcondition(IDstr, qstr, numstockitems);
			if(check == 0)
			{
				fillelement(stockrecord,salesrecord, Id,index,que);
				index++;
				modifyStockReport(stockrecord, salesrecord, 10, numstockitems,index-1);
			}
		} while (check == 1);
		numsaleitems++;
	} while (str[0] != '0');
	return numsaleitems - 1;
}

//print sales report
double printSalesReport(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numsaleitems)
{
	int i = 0;
	double purchasetotal=0, tax = 0, sale = 0;
	for (int i = 0; i < numsaleitems; i++)
	{
		printf("%-25s%8.2lf%8.2lf\n", (salesrecord[i]).product_name, (salesrecord[i]).price, ((salesrecord[i]).price) * ((salesrecord[i]).quantity));
		purchasetotal += ((salesrecord[i]).price) * ((salesrecord[i]).quantity);
	}
	printf("Purchase total      %.2lf\n", purchasetotal);
	
	tax = taxtotal(stockrecord, salesrecord, numsaleitems, MAX_STOCK_ENTRIES);
	printf("Tax:                %.2lf\n", tax);
	sale = purchasetotal + tax;
	printf("Total:              %.2lf\n", sale);
	printf("Thank you for shopping at Seneca!\n\n");
	return purchasetotal;
}

// get first 3 or 2 highest sold product
void getTopSellers(struct StockRecord* stockrecord, int numstockitems, struct SalesRecord* topsellers, int ranks, int cat)
{
	for (int i = 0; i < 5; i++)
	{
		strcpy(topsellers[i].product_name, "<none>");
		topsellers[i].quantity = 0.0;
	}
	double first =0.0, second = 0.0 , third = 0.0;
	int id1 = -1, id2 = -1, id3 = -1;

	findhighest(stockrecord, cat, &id1, &first,numstockitems);
	if (first != 0.0)
	{
		strcpy(topsellers[0].product_name, stockrecord[id1].productinfo.product_name);
		topsellers[0].quantity = first;
	}
	
	findsecondhighest(stockrecord, cat, id1, &id2, &second, numstockitems);
	if (second != 0.0)
	{
		strcpy(topsellers[1].product_name, stockrecord[id2].productinfo.product_name);
		topsellers[1].quantity = second;
	}
	
	findThirdHighest(stockrecord, cat, id1, id2, &id3, &third, numstockitems);
	if (ranks == 3)
	{
		if (third != 0.0)
		{
			strcpy(topsellers[2].product_name, stockrecord[id3].productinfo.product_name);
			topsellers[2].quantity = third;
		}
	}
}

//print highest sold products according to category
void printTopSellers(struct StockRecord* stockrecord, struct SalesRecord* topsellers, int ranks, int index)
{
	char str1[50] = "Top 3 sellors in ";
	char* str2 = getcategory(index + 1);
	strcat(str1, str2);
	centreText(50, '-', str1);
	printf("\nRank  product               Sales\n");
	
	for (int i = 0; i < ranks; i++)
	{
		printf("%4d  %-22s%.2lf\n", i + 1, topsellers[i].product_name, topsellers[i].quantity);
	}
}                       