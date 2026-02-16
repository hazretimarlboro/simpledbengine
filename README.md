---

# Mini Text-Based C++ Database

A lightweight, pointer-based, column-oriented database implemented in C++ using **text files for persistence**. Each database, table, and column maps directly to a folder and file structure on disk. Supports creating databases, tables, inserting rows, and overwriting existing data.

---

## Features

* Pointer-safe design (`Database*`, `Table*`, `Row*`)
* Each row stores `vector<string>` (easy text storage)
* Column-oriented storage: each column has its own file
* Supports overwriting column files when needed
* Automatic folder creation with `std::filesystem`
* Memory-safe: all heap objects tracked and deleted by `destroyEverything()`

---

## Folder Structure

```
./db/
    MyDatabase/
        Users/
            Name       <- column file
            Age        <- column file
            Job        <- column file
```

* **Database folder** → `./db/<DatabaseName>`
* **Table folder** → `./db/<DatabaseName>/<TableName>`
* **Column files** → one file per column, stores one row per line

---

## Usage

### Include Header

```cpp
#include "database.h"
```

### Creating a Database

```cpp
Database* db = createDatabase("MyDB");
```

### Creating a Table

```cpp
Table* tbl = createTable(db, "Users", {"Name", "Age", "Job"});
```

### Inserting Rows

```cpp
vector<string> row1 = {"Alice","25","Engineer"};
vector<string> row2 = {"Bob","30","Doctor"};

// Overwrite existing column files
createRow(tbl, row1, true);

// Append new rows
createRow(tbl, row2);
```

### Destroying All Data in Memory

```cpp
destroyEverything(); // deletes all Database*, Table*, Row* objects
```

---

## Notes

* **Text-based only**: Works with strings; multi-line strings require escaping.
* **Overwrite**: `createRow(..., true)` clears the column files before writing.
* **Pointer consistency**: All rows and tables are stored as pointers to simplify memory management.
* **Automatic folder creation**: You don’t need to create `./db` manually; the system does it.

---

## Future Improvements

* Implement `readRow` function to reconstruct tables from disk.
* Support multi-line strings or escape characters.
* Add column types (int, float) with fixed widths for more structured storage.
* Implement basic queries or filtering.

---
