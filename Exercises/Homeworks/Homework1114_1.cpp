#include <iostream>
#include <string>

using namespace std;

class Document {
public:
    string name;
};

class Book : public Document {
public:
    int pageCount;
};

int main() {
    Book book;
    book.name = "The Lord of the Rings";
    book.pageCount = 1178;
    cout << "Book name: " << book.name << endl;
    cout << "Page count: " << book.pageCount << endl;
    return 0;
}
