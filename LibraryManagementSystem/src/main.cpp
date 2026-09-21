#include <iostream>
#include <limits>
#include "Library.h"

namespace {
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int readInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                clearInput();
                return value;
            }
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
        }
    }

    std::string readLine(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    void printMenu() {
        std::cout << "\n===== Library Management System =====\n"
                   << "1. Add Book\n"
                   << "2. Remove Book\n"
                   << "3. Search Book\n"
                   << "4. Display All Books\n"
                   << "5. Register Member\n"
                   << "6. Display All Members\n"
                   << "7. Issue Book\n"
                   << "8. Return Book\n"
                   << "9. Save & Exit\n"
                   << "Choose an option: ";
    }
}

int main() {
    Library library("data/books.txt", "data/members.txt");

    bool running = true;
    while (running) {
        printMenu();
        int choice;
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 1: {
                std::string title = readLine("Title: ");
                std::string author = readLine("Author: ");
                std::string isbn = readLine("ISBN: ");
                int copies = readInt("Number of copies: ");
                library.addBook(title, author, isbn, copies);
                break;
            }
            case 2: {
                int id = readInt("Book ID to remove: ");
                library.removeBook(id);
                break;
            }
            case 3: {
                std::string keyword = readLine("Search keyword (title/author/ISBN): ");
                library.searchBook(keyword);
                break;
            }
            case 4:
                library.displayAllBooks();
                break;
            case 5: {
                std::string name = readLine("Member name: ");
                std::string email = readLine("Member email: ");
                library.addMember(name, email);
                break;
            }
            case 6:
                library.displayAllMembers();
                break;
            case 7: {
                int bookId = readInt("Book ID to issue: ");
                int memberId = readInt("Member ID: ");
                library.issueBook(bookId, memberId);
                break;
            }
            case 8: {
                int bookId = readInt("Book ID to return: ");
                int memberId = readInt("Member ID: ");
                library.returnBook(bookId, memberId);
                break;
            }
            case 9:
                library.saveData();
                std::cout << "Data saved. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
