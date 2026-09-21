#include "Book.h"
#include <iostream>
#include <sstream>
#include <vector>

Book::Book() : id(0), totalCopies(0), availableCopies(0) {}

Book::Book(int id, const std::string& title, const std::string& author,
           const std::string& isbn, int totalCopies, int availableCopies)
    : id(id), title(title), author(author), isbn(isbn),
      totalCopies(totalCopies), availableCopies(availableCopies) {}

void Book::display() const {
    std::cout << "[" << id << "] \"" << title << "\" by " << author
              << " | ISBN: " << isbn
              << " | Available: " << availableCopies << "/" << totalCopies
              << "\n";
}

// Fields are pipe-delimited: id|title|author|isbn|totalCopies|availableCopies
std::string Book::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << title << "|" << author << "|" << isbn << "|"
        << totalCopies << "|" << availableCopies;
    return oss.str();
}

Book Book::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string field;
    std::vector<std::string> parts;

    while (std::getline(ss, field, '|')) {
        parts.push_back(field);
    }

    Book b;
    if (parts.size() == 6) {
        b.id = std::stoi(parts[0]);
        b.title = parts[1];
        b.author = parts[2];
        b.isbn = parts[3];
        b.totalCopies = std::stoi(parts[4]);
        b.availableCopies = std::stoi(parts[5]);
    }
    return b;
}
