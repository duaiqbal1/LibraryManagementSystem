#include "Library.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

namespace {
    std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                        [](unsigned char c) { return std::tolower(c); });
        return s;
    }
}

Library::Library(const std::string& booksFilePath, const std::string& membersFilePath)
    : booksFile(booksFilePath), membersFile(membersFilePath),
      nextBookId(1), nextMemberId(1) {
    loadData();
}

Library::~Library() {
    saveData();
}

void Library::loadData() {
    std::ifstream bIn(booksFile);
    std::string line;
    while (std::getline(bIn, line)) {
        if (line.empty()) continue;
        Book b = Book::deserialize(line);
        books.push_back(b);
        if (b.id >= nextBookId) nextBookId = b.id + 1;
    }
    bIn.close();

    std::ifstream mIn(membersFile);
    while (std::getline(mIn, line)) {
        if (line.empty()) continue;
        Member m = Member::deserialize(line);
        members.push_back(m);
        if (m.id >= nextMemberId) nextMemberId = m.id + 1;
    }
    mIn.close();
}

void Library::saveData() const {
    std::ofstream bOut(booksFile, std::ios::trunc);
    for (const auto& b : books) {
        bOut << b.serialize() << "\n";
    }
    bOut.close();

    std::ofstream mOut(membersFile, std::ios::trunc);
    for (const auto& m : members) {
        mOut << m.serialize() << "\n";
    }
    mOut.close();
}

Book* Library::findBookById(int id) {
    for (auto& b : books) {
        if (b.id == id) return &b;
    }
    return nullptr;
}

Member* Library::findMemberById(int id) {
    for (auto& m : members) {
        if (m.id == id) return &m;
    }
    return nullptr;
}

void Library::addBook(const std::string& title, const std::string& author,
                       const std::string& isbn, int copies) {
    Book b(nextBookId++, title, author, isbn, copies, copies);
    books.push_back(b);
    std::cout << "Book added successfully with ID: " << b.id << "\n";
}

bool Library::removeBook(int id) {
    auto it = std::find_if(books.begin(), books.end(),
                            [id](const Book& b) { return b.id == id; });
    if (it == books.end()) {
        std::cout << "Book with ID " << id << " not found.\n";
        return false;
    }
    if (it->availableCopies != it->totalCopies) {
        std::cout << "Cannot remove: some copies are currently issued.\n";
        return false;
    }
    books.erase(it);
    std::cout << "Book removed successfully.\n";
    return true;
}

void Library::searchBook(const std::string& keyword) const {
    std::string key = toLower(keyword);
    bool found = false;
    for (const auto& b : books) {
        if (toLower(b.title).find(key) != std::string::npos ||
            toLower(b.author).find(key) != std::string::npos ||
            toLower(b.isbn).find(key) != std::string::npos) {
            b.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No matching books found.\n";
    }
}

void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "No books in the library yet.\n";
        return;
    }
    for (const auto& b : books) {
        b.display();
    }
}

void Library::addMember(const std::string& name, const std::string& email) {
    Member m(nextMemberId++, name, email);
    members.push_back(m);
    std::cout << "Member registered successfully with ID: " << m.id << "\n";
}

void Library::displayAllMembers() const {
    if (members.empty()) {
        std::cout << "No members registered yet.\n";
        return;
    }
    for (const auto& m : members) {
        m.display();
    }
}

bool Library::issueBook(int bookId, int memberId) {
    Book* b = findBookById(bookId);
    Member* m = findMemberById(memberId);

    if (!b) { std::cout << "Book not found.\n"; return false; }
    if (!m) { std::cout << "Member not found.\n"; return false; }
    if (b->availableCopies <= 0) {
        std::cout << "No available copies of this book right now.\n";
        return false;
    }

    b->availableCopies--;
    m->borrowedBookIds.push_back(bookId);
    std::cout << "Book \"" << b->title << "\" issued to " << m->name << ".\n";
    return true;
}

bool Library::returnBook(int bookId, int memberId) {
    Book* b = findBookById(bookId);
    Member* m = findMemberById(memberId);

    if (!b) { std::cout << "Book not found.\n"; return false; }
    if (!m) { std::cout << "Member not found.\n"; return false; }

    auto it = std::find(m->borrowedBookIds.begin(), m->borrowedBookIds.end(), bookId);
    if (it == m->borrowedBookIds.end()) {
        std::cout << m->name << " has not borrowed this book.\n";
        return false;
    }

    m->borrowedBookIds.erase(it);
    b->availableCopies++;
    std::cout << "Book \"" << b->title << "\" returned by " << m->name << ".\n";
    return true;
}
