#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

bool IsEmptyFile(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

class Author {
private:
    std::string lastName;
    std::string firstName;
    std::string middleName;

public:
    Author() = default;

    Author(const std::string& fullName) {
        setFromFullName(fullName);
    }

    Author(const std::string& last, const std::string& first, const std::string& middle = "")
        : lastName(last), firstName(first), middleName(middle) {
    }

    std::string getFullName() const {
        std::string fullName = lastName;
        if (!firstName.empty()) fullName += " " + firstName;
        if (!middleName.empty()) fullName += " " + middleName;
        return fullName;
    }

    void setFromFullName(const std::string& fullName) {
        std::stringstream ss(fullName);
        std::vector<std::string> parts;
        std::string part;

        while (ss >> part) {
            parts.push_back(part);
        }

        if (parts.size() >= 1) lastName = parts[0];
        if (parts.size() >= 2) firstName = parts[1];
        if (parts.size() >= 3) middleName = parts[2];
        else if (parts.size() == 2) middleName = "";
    }

    const std::string& getLastName() const { return lastName; }
    const std::string& getFirstName() const { return firstName; }
    const std::string& getMiddleName() const { return middleName; }

    bool operator<(const Author& other) const {
        if (lastName != other.lastName) return lastName < other.lastName;
        if (firstName != other.firstName) return firstName < other.firstName;
        return middleName < other.middleName;
    }

    bool operator==(const Author& other) const {
        return lastName == other.lastName &&
            firstName == other.firstName &&
            middleName == other.middleName;
    }

    friend std::ostream& operator<<(std::ostream& os, const Author& author) {
        os << author.getFullName();
        return os;
    }
};

class Book {
private:
    int udc;
    std::list<Author> authors;
    std::string title;
    int year;

public:
    Book() : udc(0), year(0) {}

    Book(int u, const std::string& t, int y) : udc(u), title(t), year(y) {}

    Book(int u, const std::list<Author>& a, const std::string& t, int y)
        : udc(u), authors(a), title(t), year(y) {
        authors.sort();
    }

    int getUDC() const { return udc; }
    const std::list<Author>& getAuthors() const { return authors; }
    std::list<Author>& getAuthors() { return authors; }
    const std::string& getTitle() const { return title; }
    int getYear() const { return year; }

    void setUDC(int u) { udc = u; }
    void setTitle(const std::string& t) { title = t; }
    void setYear(int y) { year = y; }

    void addAuthor(const Author& author) {
        auto it = std::find(authors.begin(), authors.end(), author);
        if (it == authors.end()) {
            authors.push_back(author);
            authors.sort();
        }
    }

    bool removeAuthor(const Author& author) {
        auto it = std::find(authors.begin(), authors.end(), author);
        if (it != authors.end()) {
            authors.erase(it);
            return true;
        }
        return false;
    }

    bool hasAuthor(const Author& author) const {
        return std::find(authors.begin(), authors.end(), author) != authors.end();
    }

    void printInfo() const {
        std::cout << "Title: " << title << std::endl;
        std::cout << "UDC: " << udc << std::endl;
        std::cout << "Year: " << year << std::endl;
        std::cout << "Authors: ";

        if (authors.empty()) {
            std::cout << "None";
        }
        else {
            bool first = true;
            for (const auto& author : authors) {
                if (!first) std::cout << ", ";
                std::cout << author.getFullName();
                first = false;
            }
        }
        std::cout << std::endl;
    }

    bool operator<(const Book& other) const {
        return title < other.title;
    }
};

class Library {
private:
    std::list<Book> books;

    typename std::list<Book>::iterator findBookByTitle(const std::string& title) {
        return std::find_if(books.begin(), books.end(),
            [&title](const Book& book) { return book.getTitle() == title; });
    }

    typename std::list<Book>::const_iterator findBookByTitle(const std::string& title) const {
        return std::find_if(books.begin(), books.end(),
            [&title](const Book& book) { return book.getTitle() == title; });
    }

public:
    Library() = default;

    void addBook(const Book& book) {
        if (findBookByTitle(book.getTitle()) != books.end()) {
            std::cout << "Book \"" << book.getTitle() << "\" already exists." << std::endl;
            return;
        }

        auto it = books.begin();
        while (it != books.end() && it->getTitle() < book.getTitle()) {
            ++it;
        }

        books.insert(it, book);
        std::cout << "Book \"" << book.getTitle() << "\" added successfully." << std::endl;
    }

    bool removeBook(const std::string& title) {
        auto it = findBookByTitle(title);
        if (it != books.end()) {
            books.erase(it);
            std::cout << "Book \"" << title << "\" removed successfully." << std::endl;
            return true;
        }

        std::cout << "Book \"" << title << "\" not found." << std::endl;
        return false;
    }

    std::list<Book> findBooksByAuthor(const Author& author) const {
        std::list<Book> result;

        for (const auto& book : books) {
            if (book.hasAuthor(author)) {
                result.push_back(book);
            }
        }

        return result;
    }

    bool addAuthorToBook(const std::string& title, const Author& author) {
        auto it = findBookByTitle(title);
        if (it != books.end()) {
            if (!it->hasAuthor(author)) {
                it->addAuthor(author);
                std::cout << "Author " << author.getFullName()
                    << " added to book \"" << title << "\"." << std::endl;
                return true;
            }
            else {
                std::cout << "Author " << author.getFullName()
                    << " already exists for this book." << std::endl;
            }
        }
        else {
            std::cout << "Book \"" << title << "\" not found." << std::endl;
        }

        return false;
    }

    bool removeAuthorFromBook(const std::string& title, const Author& author) {
        auto it = findBookByTitle(title);
        if (it != books.end()) {
            if (it->hasAuthor(author)) {
                it->removeAuthor(author);
                std::cout << "Author " << author.getFullName()
                    << " removed from book \"" << title << "\"." << std::endl;
                return true;
            }
            else {
                std::cout << "Author " << author.getFullName()
                    << " not found for this book." << std::endl;
            }
        }
        else {
            std::cout << "Book \"" << title << "\" not found." << std::endl;
        }

        return false;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error: Cannot open file " << filename << std::endl;
            return;
        }

        if (IsEmptyFile(file)) {
            std::cout << "File " << filename << " is empty." << std::endl;
            file.close();
            return;
        }

        std::string line;
        int booksLoaded = 0;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string token;

            if (!std::getline(ss, token, '|')) continue;
            int udc = std::stoi(token);

            if (!std::getline(ss, token, '|')) continue;
            int authorCount = std::stoi(token);

            std::list<Author> authors;
            for (int i = 0; i < authorCount; ++i) {
                if (!std::getline(ss, token, '|')) break;
                authors.push_back(Author(token));
            }

            if (!std::getline(ss, token, '|')) continue;
            std::string title = token;

            if (!std::getline(ss, token, '|')) continue;
            int year = std::stoi(token);

            Book book(udc, authors, title, year);
            addBook(book);
            booksLoaded++;
        }

        file.close();
        std::cout << "Loaded " << booksLoaded << " books from " << filename << std::endl;
    }

    void printAllBooks() const {
        std::cout << "\n=== LIBRARY CATALOG ===" << std::endl;
        std::cout << "Total books: " << books.size() << std::endl;
        std::cout << "=======================\n" << std::endl;

        if (books.empty()) {
            std::cout << "No books in the library." << std::endl;
            return;
        }

        int counter = 1;
        for (const auto& book : books) {
            std::cout << "Book #" << counter++ << std::endl;
            book.printInfo();
            std::cout << std::endl;
        }
    }

    size_t getBookCount() const {
        return books.size();
    }

    const std::list<Book>& getAllBooks() const {
        return books;
    }
};

void demonstrateLibrary() {
    Library library;

    std::cout << "=== LOADING BOOKS FROM FILE ===" << std::endl;
    library.loadFromFile("books.txt");

    library.printAllBooks();

    std::cout << "=== SEARCH BOOKS BY AUTHOR ===" << std::endl;
    Author searchAuthor("Smith John");
    auto foundBooks = library.findBooksByAuthor(searchAuthor);

    if (!foundBooks.empty()) {
        std::cout << "Found " << foundBooks.size() << " books by author "
            << searchAuthor.getFullName() << ":\n" << std::endl;
        for (const auto& book : foundBooks) {
            book.printInfo();
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "No books found by author " << searchAuthor.getFullName() << std::endl;
    }

    std::cout << "=== ADD NEW BOOK ===" << std::endl;
    Book newBook(99999, "Master and Margarita", 1967);
    newBook.addAuthor(Author("Bulgakov Mikhail"));
    library.addBook(newBook);

    std::cout << "\n=== ADD AUTHOR TO EXISTING BOOK ===" << std::endl;
    library.addAuthorToBook("Master and Margarita", Author("Editor Robert"));

    std::cout << "\n=== REMOVE AUTHOR FROM BOOK ===" << std::endl;
    library.removeAuthorFromBook("Master and Margarita", Author("Editor Robert"));

    std::cout << "\n=== TRY TO ADD DUPLICATE BOOK ===" << std::endl;
    library.addBook(newBook);

    std::cout << "\n=== REMOVE BOOK ===" << std::endl;
    library.removeBook("Master and Margarita");

    std::cout << "\n=== FINAL CATALOG ===" << std::endl;
    library.printAllBooks();
}

int main() {
    demonstrateLibrary();
    return 0;
}
