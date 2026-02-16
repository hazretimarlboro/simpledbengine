#include "../include/database.h"

int main(int argc, char** argv)
{
    Database* db = createDatabase("hello");
    Table* tb = createTable(db,"deneme",{"merhaba","ben","deniz"});
    Row* rw = createRow(tb,{"naber","yup","nope"});

    destroyEverything();
    return 0;
}