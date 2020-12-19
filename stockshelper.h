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

#include "stock.h"

int checkint(char* tempstring);

double checkdouble(char* tempstring);

void splitstring(char* string, char* IDstr, char* qstr);

int checkcondition(char* Idstr, char* qstr, int numstockitems);

void fillelement(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int Id, int index, double que);

void findhighest(struct StockRecord* stockrecord, int cat, int* id1, double* first, int numstockitems);

void findsecondhighest(struct StockRecord* stockrecord, int cat, int id1, int* id2, double* second, int numstockitems);

void findThirdHighest(struct StockRecord* stockrecord, int cat, int id1, int id2, int* id3, double* third, int numstockitems);

char* getcategory(int numcategory);

int* findindex(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numsaleitems, int max_entry);

double taxtotal(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numsaleitems, int max_entry);

void modifyStockReport(struct StockRecord* stockrecord, struct SalesRecord* salesrecord, int numSaleItems, int max_entry, int i);