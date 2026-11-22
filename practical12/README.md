# Practical 12 - Library Management System

A console-based library application developed using C++.

## Features

- Add books
- Search books by ID, title or author
- List all books
- Issue and return books
- Prevent duplicate IDs and invalid operations
- Save and reload records from `books.csv`
- Uses classes, inheritance, polymorphism, STL containers and exceptions

## Compile and Run

```bash
g++ -Wall -Wextra -std=c++11 library.cpp -o library
./library
```

On Windows PowerShell:

```powershell
.\library.exe
```

Keep `library.cpp` and `books.csv` in the same working directory.

## Data Format

`books.csv` contains:

```text
id,title,author,available
```

An availability value of `1` means available and `0` means issued.
