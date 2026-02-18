#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

using namespace std;

struct Row;
struct Table;
struct Database;

enum class Err {
    OK,
    FolderCreationError
};

struct Row {
    vector<string> data;
    Table* parentTable;
};


struct Table {
    string name;
    Database* parentDb;
    vector<string> columnNames;
    vector<Row*> rows; 
};

struct Database {
    string name;
    vector<Table*> tables;
};

// Global storage
extern vector<Database*> allDatabases;
extern vector<Table*> allTables;
extern vector<Row*> allRows;

// Functions
Database* createDatabase(const string& name);
Table* createTable(Database* db, const string& name, const vector<string>& columnNames);
Row* createRow(Table* table, const vector<string>& data, bool overwrite = false);
vector<vector<string>> readAllRows(Table* table);
void printTable(Table* table);

void destroyEverything();

#endif
