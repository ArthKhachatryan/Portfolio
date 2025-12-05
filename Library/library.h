#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "book.h"

class Library {
public:
    void addBook(const Book& book);
    void removeBook(const std::string& title);
    Book* findBook(const std::string& title);
    void showBooks() const;

private:
    std::vector<Book> books;
};

#endif 
