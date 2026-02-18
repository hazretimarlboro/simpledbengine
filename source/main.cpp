#include "../include/database.h"
#include <iostream>

int main(int argc, char** argv)
{
    Database* db = createDatabase("hello");
    Table* tb = createTable(db,"deneme",{"merhaba","ben","deniz"});
    Row* rw = createRow(tb,{"naber","yup","nope"});
    Row* rw2 = createRow(tb, {"test","test2","test3"});
    
    printTable(tb);

    destroyEverything();
    return 0;
}