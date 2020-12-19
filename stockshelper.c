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
#include <string.h>
#include <math.h>
#include "stock.h"
#include "stockshelper.h"

//spilt string delimeted with comma
void splitstring(char* string, char* IDstr, char* qstr)
{
	int flag = 0, Idindex = 0, qindex = 0;
	int length = strlen(string);

	for (int i = 0; i < length; i++)
	{
		if (string[i] == ',')
			flag = i;
	}
	for (int i = 0; i < length; i++)
	{
		if (i < flag)
		{
			IDstr[Idindex] = string[i];
			Idindex++;
		}
		else if (i > flag)
		{
			qstr[qindex] = string[i];
			qindex++;
		}
	}
}

//check for user input Id of product is available in define quantity or not
int checkcondition(char* Idstr, char* qstr, int numstockitems)
{
	int check = 0;
	if (checkint(Idstr) > 14 || checkint(Idstr) < 1)
	{
		printf("Invalid Product - Enter a number between 0 and %d: ", numstockitems);
		check = 1;
	}

	else if (checkdouble(qstr) > 100.00 || checkdouble(qstr) < 0.10)
	{
		printf("Invalid quantity - Enter a number between 0.10 and 100.00: ");
		check = 1;
	}
	return check;
}

//find the highest sold product according to category
void findhighest(struct StockRecord* stockrecord, int cat, int* id1, double* first, int numstockitems)
{
	for (int i = 0; i < numstockitems; i++)
	{
		if (stockrecord[i].productinfo.category_indetification == cat + 1 && stockrecord[i].salequantity > *first)
		{
			*first = stockrecord[i].salequantity;
			*id1 = i;
		}
	}
}

//find the second highest sold product according to category
void findsecondhighest(struct StockRecord* stockrecord, int cat, int id1, int* id2, double* second, int numstockitems)
{
	for (int i = 0; i < numstockitems; i++)
	{
		if (i == id1) continue;
		if (stockrecord[i].productinfo.category_indetification == cat + 1 && stockrecord[i].salequantity > *second)
		{
			*second = stockrecord[i].salequantity;
			*id2 = i;
		}
	}
}

//find the third highest sold product according to category
void findThirdHighest(struct StockRecord* stockrecord, int cat, int id1, int id2, int* id3, double* third, int numstockitems)
{
	for (int i = 0; i < numstockitems; i++)
	{
		if (i == id2 || i == id1) continue;
		if (stockrecord[i].productinfo.category_indetification == cat + 1 && stockrecord[i].salequantity > *third)
		{
			*third = stockrecord[i].salequantity;
			*id3 = i;
		}
	}
}

//fill sales record structure
void fillelement(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int Id, int index, double que)
{
	strcpy(salesrecord[index].product_name, stockrecord[Id].productinfo.product_name);
	salesrecord[index].price = stockrecord[Id].productinfo.price;
	if (que > stockrecord[Id].quantity)
		salesrecord[index].quantity = stockrecord[Id].quantity;
	else
		salesrecord[index].quantity = que;
}

//give the category string using number indentification
char* getcategory(int numcategory)
{
	char* category = "\0";
	switch (numcategory)
	{
	case 1 : 
		category = "produce";
		break;
	case 2:
		category = "bakery";
		break;
	case 3:
		category = "meat";
		break;
	case 4:
		category = "dairy";
		break;
	case 5:
		category = "baking";
		break;
	case 6:
		category = "house wares";
		break;
	case 7:
		category = "miscellaneous";
		break;
	default:
		break;
	}
	return category;
}

//check if element of string is integer 
int checkint(char* tempstring)
{
	int flag = 0;
	int integer = 0;
	int length = strlen(tempstring);
	for (int i = 0; i < length; i++)
	{
		if (isdigit(tempstring[i]) != 0) flag++;
	}
	if (flag == strlen(tempstring))
		integer = atoi(tempstring);
	return integer;
}

////check if element of string is double
double checkdouble(char* tempstring)
{
	int flag = 0;
	double num = 0.0;
	int lenght = strlen(tempstring);
	for (int i = 0; i < lenght; i++)
	{
		if (isdigit(tempstring[i]) != 0 || tempstring[i] == '.') flag++;
	}
	if (flag == strlen(tempstring))
		num = atof(tempstring);
	return num;
}

//find the index where product in stockrecord and salesrecoderd structure matches
int* findindex(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numsaleitems, int max_entry)
{
	static int index[100] = { 0 };
	for (int i = 0; i < numsaleitems; i++)
	{
		for (int j = 0; j <= max_entry; j++)
		{
			if (strcmp(salesrecord[i].product_name,stockrecord[j].productinfo.product_name)==0)
			{
				index[i] = j;
			}
		}
	}
	return index;
}

//count tax 
double taxtotal(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numsaleitems, int max_entry)
{
	double tax = 0.0;
	int* index = findindex(stockrecord, salesrecord, numsaleitems, max_entry);
	for (int i = 0; i < numsaleitems; i++)
	{
		if (stockrecord[index[i]].productinfo.category_indetification == 6 ||
			stockrecord[index[i]].productinfo.category_indetification == 7)
		{
			tax += salesrecord[i].price * 0.13;
		}
	}
	return tax;
}

//modify stock report
void modifyStockReport(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numSaleItems, int max_entry,int i)
{
	int* index = findindex(stockrecord, salesrecord, numSaleItems, max_entry);
		stockrecord[index[i]].salequantity = salesrecord[i].quantity;
		stockrecord[index[i]].quantity -= (int)round(salesrecord[i].quantity);
	
}
