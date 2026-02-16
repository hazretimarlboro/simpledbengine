#include "../include/database.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

vector<Database*> allDatabases;
vector<Table*> allTables;
vector<Row*> allRows;


void destroyEverything()
{
    for (Row* row : allRows) delete row;
    for (Table* table : allTables) delete table;
    for (Database* db : allDatabases) delete db;

    allRows.clear();
    allTables.clear();
    allDatabases.clear();
}

Database* createDatabase(const string& name)
{
    string folder = "./db/" + name;


    fs::create_directories("./db");

    if (fs::exists(folder)) fs::remove_all(folder);

    if (!fs::create_directory(folder)) {
        cerr << "Failed to create database folder: " << folder << "\n";
        return nullptr;
    }

    Database* db = new Database;
    db->name = name;
    db->tables = {};

    allDatabases.push_back(db);
    return db;
}

Table* createTable(Database* db, const string& name, const vector<string>& columnNames)
{
    if (!db) return nullptr;

    string folder = "./db/" + db->name + "/" + name;

    if (fs::exists(folder)) fs::remove_all(folder);

    if (!fs::create_directories(folder)) {
        cerr << "Failed to create table folder: " << folder << "\n";
        return nullptr;
    }


    for (const string& col : columnNames) {
        string colPath = folder + "/" + col;
        ofstream file(colPath);
        if (!file) {
            cerr << "Failed to create column file: " << colPath << "\n";
            return nullptr;
        }
        file.close();
    }

    Table* table = new Table;
    table->name = name;
    table->parentDb = db;
    table->columnNames = columnNames;
    table->rows = {};

    db->tables.push_back(table);
    allTables.push_back(table);

    return table;
}

Row* createRow(Table* table, const vector<string>& data, bool overwrite)
{
    if (!table) return nullptr;

    if (table->columnNames.size() != data.size()) {
        cerr << "Column count mismatch\n";
        return nullptr;
    }

    for (size_t i = 0; i < table->columnNames.size(); i++) {
        string path = "./db/" + table->parentDb->name + "/" +
                      table->name + "/" + table->columnNames[i];

        ofstream file;
        if (overwrite) {
            file.open(path, ios::trunc);
        } else {
            file.open(path, ios::app);
        }

        if (!file) {
            cerr << "Failed to open column file: " << path << "\n";
            return nullptr;
        }

        file << data[i] << "\n";
        file.close();
    }

    Row* row = new Row;
    row->data = data;
    row->parentTable = table;

    table->rows.push_back(row);
    allRows.push_back(row);

    return row;
}
