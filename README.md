# 📚 Library Management System (C++)

A console-based **Library Management System** built in modern C++ (C++17), demonstrating clean object-oriented design, file-based data persistence, and modular project structure. Built as a portfolio-ready project to showcase core C++ and software design skills.

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![Build](https://img.shields.io/badge/Build-CMake-brightgreen.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

## ✨ Features

- **Book Management** — add, remove, search (by title/author/ISBN), and list all books
- **Member Management** — register library members and view their borrowing history
- **Issue / Return System** — tracks available copies and prevents over-issuing
- **Persistent Storage** — data is saved to plain-text files and reloaded automatically on the next run (no database required)
- **Input Validation** — guards against invalid menu choices and non-numeric input
- **Clean OOP Architecture** — separate `Book`, `Member`, and `Library` classes with header/source separation

## 🏗️ Project Structure

```
LibraryManagementSystem/
├── include/            # Class declarations (headers)
│   ├── Book.h
│   ├── Member.h
│   └── Library.h
├── src/                # Class implementations + entry point
│   ├── Book.cpp
│   ├── Member.cpp
│   ├── Library.cpp
│   └── main.cpp
├── data/               # Persisted data (plain text, auto-generated)
│   ├── books.txt
│   └── members.txt
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## 🚀 Getting Started

### Prerequisites
- A C++17-compatible compiler (g++, clang++, or MSVC)
- [CMake](https://cmake.org/) 3.10+ (optional but recommended)

### Build with CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
./library_system        # or library_system.exe on Windows
```

### Build directly with g++
```bash
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o library_system
./library_system
```

> Run the executable from the project root so it can find the `data/` folder.

## 🖥️ Usage

On launch you'll see a menu-driven interface:

```
===== Library Management System =====
1. Add Book
2. Remove Book
3. Search Book
4. Display All Books
5. Register Member
6. Display All Members
7. Issue Book
8. Return Book
9. Save & Exit
Choose an option:
```

Data is automatically saved on exit (option 9) and reloaded the next time the program starts.

## 🔧 Design Notes

- **Persistence format**: each record is stored as a pipe-delimited (`|`) line in a text file, making the storage layer human-readable and dependency-free. Swapping this for SQLite/JSON later would only require changing `Library::loadData()` and `Library::saveData()`.
- **Encapsulation**: `Book` and `Member` are simple data-holding classes with their own `serialize()`/`deserialize()` logic, keeping `Library` focused purely on business rules (issuing, returning, searching).
- **Extensibility**: the menu in `main.cpp` is intentionally thin — it only calls into `Library`'s public API, so a GUI or web frontend could reuse the same core logic.

## 🛣️ Possible Improvements

- [ ] Due dates and fine calculation for late returns
- [ ] Multiple copies tracked per physical unit (barcodes)
- [ ] Unit tests (Catch2/GoogleTest)
- [ ] Migrate storage to SQLite

## 📄 License

This project is licensed under the [MIT License](LICENSE). 

Dua Iqbal

---

*Built as a portfolio project — feel free to fork, extend, and use it as a base for your own C++ projects.*
