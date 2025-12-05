#include "library.h"
#include <iostream>

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::removeBook(const std::string& title) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getTitle() == title) {
            books.erase(it);
            std::cout << "Book \"" << title << "\" removed.\n";
            return;
        }
    }
    std::cout << "Book \"" << title << "\" not found.\n";
}

Book* Library::findBook(const std::string& title) {
    for (auto& book : books) {
        if (book.getTitle() == title) {
            return &book;
        }
    }
    return nullptr;
}

void Library::showBooks() const {
    if (books.empty()) {
        std::cout << "No books in the library.\n";
        return;
    }
    std::cout << "Books in the library:\n";
    for (const auto& book : books) {
        std::cout << "- " << book.getTitle() << " by " << book.getAuthor() << "\n";
    }
}
