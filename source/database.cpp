#include "../include/database.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

vector<Database*> allDatabases;
vector<Table*> allTables;
vector<Row*> allRows;


vector<vector<string>> readAllRows(Table* table)
{
    vector<vector<string>> columns;
    vector<vector<string>> rows;
    string folderName = "./db/" + table->parentDb->name + "/" + table->name;

    for(int i =0; i < table->columnNames.size(); i++)
    {
        vector<string> lines;
        string filename = folderName+"/"+table->columnNames[i];
        fstream individualFile(filename, ios::in);
        string line;
        while(std::getline(individualFile,line))
        {
            lines.push_back(line);
        }

        columns.push_back(lines);
    }

    if (columns.empty())
        return {};
    size_t rowcount = columns[0].size();

    int j=0;
    for(int i=0; i < rowcount; i++)
    {
        vector<string> row;
        for(const auto& x: columns)
        {
            row.push_back(x[i]);
        }

        rows.push_back(row);
    }
 
    return rows;
}

void printTable(Table* table)
{
    if (!table) return;

    vector<vector<string>> rows = readAllRows(table);

    if (rows.empty())
    {
        cout << "Table is empty.\n";
        return;
    }

    size_t colCount = table->columnNames.size();

    vector<size_t> colWidths(colCount);

    for (size_t i = 0; i < colCount; i++)
    {
        colWidths[i] = table->columnNames[i].length();
    }

    for (const auto& row : rows)
    {
        for (size_t i = 0; i < colCount; i++)
        {
            colWidths[i] = max(colWidths[i], row[i].length());
        }
    }

    for (size_t i = 0; i < colCount; i++)
    {
        cout << left << setw(colWidths[i] + 2)
             << table->columnNames[i];
    }
    cout << "\n";

    for (size_t i = 0; i < colCount; i++)
    {
        cout << string(colWidths[i], '-') << "  ";
    }
    cout << "\n";

    for (const auto& row : rows)
    {
        for (size_t i = 0; i < colCount; i++)
        {
            cout << left << setw(colWidths[i] + 2)
                 << row[i];
        }
        cout << "\n";
    }
}

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
