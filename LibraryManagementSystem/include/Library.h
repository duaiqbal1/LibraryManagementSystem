#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "Book.h"
#include "Member.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

    std::string booksFile;
    std::string membersFile;

    int nextBookId;
    int nextMemberId;

    Book* findBookById(int id);
    Member* findMemberById(int id);

public:
    Library(const std::string& booksFilePath, const std::string& membersFilePath);
    ~Library();

    void loadData();
    void saveData() const;

    // Book operations
    void addBook(const std::string& title, const std::string& author,
                 const std::string& isbn, int copies);
    bool removeBook(int id);
    void searchBook(const std::string& keyword) const;
    void displayAllBooks() const;

    // Member operations
    void addMember(const std::string& name, const std::string& email);
    void displayAllMembers() const;

    // Transactions
    bool issueBook(int bookId, int memberId);
    bool returnBook(int bookId, int memberId);
};

#endif // LIBRARY_H
