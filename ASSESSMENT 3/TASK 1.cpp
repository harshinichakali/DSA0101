#include <iostream>
#include <stdexcept>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int copies;

    static int validateCopies(int count) {
        if (count < 0) {
            throw std::invalid_argument("Number of copies cannot be negative.");
        }
        return count;
    }

public:
    // Default constructor: an empty record to fill in later.
    Book() : Book("", "", 0) {}

    // Donated book: title only, with one copy.
    explicit Book(const std::string& bookTitle) : Book(bookTitle, "", 1) {}

    // Parameterized constructor: full book details.
    Book(const std::string& bookTitle, const std::string& bookAuthor, int count)
        : title(bookTitle),
          author(bookAuthor),
          copies(validateCopies(count)) {}

    void print() const {
        std::cout << "Title: " << (title.empty() ? "(empty)" : title)
                  << ", Author: " << (author.empty() ? "(unknown)" : author)
                  << ", Copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book emptyRecord;
        Book donatedBook("The Hobbit");
        Book fullBook("1984", "George Orwell", 5);

        std::cout << "Objects after construction:\n";
        emptyRecord.print();
        donatedBook.print();
        fullBook.print();

        // Invalid construction throws std::invalid_argument.
        Book invalidBook("Invalid Book", "Unknown", -2);
    } catch (const std::invalid_argument& error) {
        std::cout << "Could not create book: " << error.what() << '\n';
    }
}
