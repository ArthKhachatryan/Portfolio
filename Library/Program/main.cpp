#include <iostream>
#include <string>
#include "book.h"
#include "library.h"

int main() {
    Library library;
    int choice;
    std::string title, author;

    do {
        std::cout << "1. Add Book\n2. Remove Book\n3. Find Book\n4. Show All Books\n0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter book title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter book author: ";
                std::getline(std::cin, author);
                library.addBook(Book(title, author));
                break;

            case 2:
                std::cout << "Enter book title to remove: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                library.removeBook(title);
                break;

            case 3:
                std::cout << "Enter book title to find: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                if (library.findBook(title)) {
                    std::cout << "Book \"" << title << "\" found.\n";
                } else {
                    std::cout << "Book \"" << title << "\" not found.\n";
                }
                break;

            case 4:
                library.showBooks();
                break;

            case 0:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
