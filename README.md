---

# C++ File-Based Database

A lightweight, file-based database system written in C++ that allows you to create databases, tables, and rows, and persist them to the filesystem. Designed for simplicity and educational purposes, it demonstrates how database-like structures can be managed using C++ and standard file I/O.

---

## Features

* **Database Management**: Create and manage multiple databases.
* **Table Management**: Create tables with custom column names.
* **Row Management**: Insert, overwrite, and read rows in tables.
* **Persistent Storage**: Data is saved in the local filesystem under `./db/`.
* **Readable Table Display**: Print tables in a nicely formatted layout.
* **Memory Cleanup**: Automatic destruction of all allocated objects to prevent memory leaks.

---

## Project Structure

* `database.h` – Header file containing `Database`, `Table`, and `Row` class definitions.
* `database.cpp` – Core implementation file with functions for managing databases, tables, rows, and reading/writing data.
* `./db/` – Default storage location where databases, tables, and columns are saved as files.

---

## Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/hazretimarlboro/simpledbengine.git
   cd file-based-db
   ```
2. Compile the project with your preferred C++ compiler (C++17 or later required):

   ```bash
   g++ -std=c++17 -o db_app src/database.cpp main.cpp
   ```
3. Run your application:

   ```bash
   ./db_app
   ```

---

## Usage

### Creating a Database

```cpp
Database* myDb = createDatabase("MyDatabase");
if (!myDb) {
    cerr << "Failed to create database.\n";
}
```

### Creating a Table

```cpp
vector<string> columns = {"ID", "Name", "Age"};
Table* users = createTable(myDb, "Users", columns);
```

### Adding Rows

```cpp
vector<string> rowData = {"1", "Alice", "23"};
createRow(users, rowData, false); // false to append, true to overwrite
```

### Reading and Printing a Table

```cpp
printTable(users);
```

### Destroying All Data in Memory

```cpp
destroyEverything();
```

---

## Data Storage Format

* Each database is a folder under `./db/`.
* Each table is a subfolder inside its parent database folder.
* Each column is stored as a separate file in the table folder.
* Rows are stored line by line in their corresponding column files.

Example folder structure:

```
./db/
└── MyDatabase/
    └── Users/
        ├── ID
        ├── Name
        └── Age
```

---

## Notes

* Column and table names are case-sensitive.
* Ensure the number of values matches the number of columns when creating a row.
* Overwriting a row will replace all existing rows in the table.
* The project uses modern C++17 features such as `std::filesystem` for directory management.

---

## License

This project is licensed under the MIT License.

---

## Future Improvements

* Add support for querying and filtering rows.
* Implement data types beyond `std::string`.
* Support for indexing to improve read performance.
* Error handling improvements and exception safety.

---

