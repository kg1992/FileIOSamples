#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Book
{
    char title[128];
    char subtitle[256];
    char author[128];
    char publisher[128];
    int publishYear;
};

std::istream& operator>>(std::istream& is, Book& book)
{
    char c;
    is >> c;
    is.unget();
    is.getline(book.title, sizeof(book.title), '|');
    is.getline(book.subtitle, sizeof(book.subtitle), '|');
    is.getline(book.author, sizeof(book.author), '|');
    is.getline(book.publisher, sizeof(book.publisher), '|');
    is >> book.publishYear;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
    return os
    << book.title << '|'
    << book.subtitle << '|'
    << book.author << '|'
    << book.publisher << '|'
    << book.publishYear;
}

int main()
{    
    const char* filename = "Books.txt";
    std::cout << "input command. input ctrl+z to stop:" << std::endl;
    std::vector<Book> books;
    std::string command;
    while( std::cin >> command )
    {
        if( command == "load" )
        {
            std::vector<Book> loaded;
            std::cout << "  * load" << std::endl;
            std::ifstream ifs(filename);
            Book book;
            while(ifs && !ifs.eof())
            {
                ifs >> book;
                if( ifs )
                {
                    loaded.push_back(book);
                }
            }
            books.swap(loaded);
            std::cout << "    - loaded"<< std::endl;
        }
        else if( command == "list")
        {
            std::cout << "  * list" << std::endl;
            for( const Book& book : books )
            {
                std::cout << "    - " << book << std::endl;
            }
        }
        else if( command == "add")
        {
            std::cout << "  * add" << std::endl;
            Book book;
            std::cout << "    - input book:" << std::endl;
            std::cin >> book;
            books.push_back(book);
            std::cout << "    - added " << book.title << std::endl;
        }
        else if (command == "remove" )
        {
            std::cout << "  * remove" << std::endl;
            std::string title;
            std::cout << "    - title of the book to be removed:" << std::endl;
            std::cin >> title;
            books.erase(
                std::remove_if(
                    books.begin(), 
                    books.end(), 
                    [&](const Book& book){return book.title == title;}
                ),
                books.end()
            );
            std::cout << "    - removed. " << books.size() << " books remaining." << std::endl;
        }
        else if( command == "save")
        {
            std::cout << "  * save" << std::endl;
            std::ofstream ofs(filename);
            if( ofs )
            {
                for( const Book& book : books )
                {
                    ofs << book << std::endl;
                }
                std::cout << "    - saved to " << filename << '.' << std::endl;
            }
        }
        else if( command == "quit" )
        {
            break;
        }
    }
    return 0;
}
