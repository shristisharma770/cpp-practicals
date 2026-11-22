# Library Management System UML

```text
+------------------+
|   LibraryItem    |
+------------------+
| - id             |
| - title          |
| - author         |
+------------------+
| + typeName()     |
| + id()           |
| + title()        |
| + author()       |
+------------------+
         ^
         | inherits
+------------------+
|      Book        |
+------------------+
| - available      |
+------------------+
| + issue()        |
| + returnBook()   |
+------------------+

+-----------------------------+
|          Library            |
+-----------------------------+
| - items: vector<LibraryItem> |
| - fileName                  |
+-----------------------------+
| + load()                    |
| + save()                    |
| + addBook()                 |
| + searchBooks()             |
| + listBooks()               |
| + issueBook()               |
| + returnBook()              |
+-----------------------------+

LibraryException derives from std::exception.
Library contains zero or more Book objects.
```
