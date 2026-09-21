#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    std::string isbn;
    int totalCopies;
    int availableCopies;

    Book();
    Book(int id, const std::string& title, const std::string& author,
         const std::string& isbn, int totalCopies, int availableCopies);

    void display() const;
    std::string serialize() const;
    static Book deserialize(const std::string& line);
};

#endif // BOOK_H
