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

#ifndef	STOCK_H_
#define STOCK_H_

struct Productinfo
{
	char product_name[20];
	int category_indetification;
	double price;
	int byweight;

};

struct StockRecord
{
	struct Productinfo productinfo;
	int quantity;
	double salequantity;
};

struct SalesRecord
{
	char product_name[20];
	double quantity;
	double price;
};

int readStockItems(struct StockRecord* stockrecord, int max_entries, int stdi_stock);

void centreText(int coloums, char design, char* heading);

void printStockReport(struct StockRecord* stockrecord, int numstockitems);

int readSale(struct StockRecord* stockrecord, int numstockitems, struct SalesRecord* salesrecord);

double printSalesReport(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numsaleitems);

void getTopSellers(struct StockRecord* stockrecord, int numstockitems, struct SalesRecord* topsellers, int raanks, int index);

void printTopSellers(struct StockRecord* stockrecord, struct SalesRecord* topsellers, int raanks, int index);


#endif // !STOCK_H_