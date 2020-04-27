#include <iostream>
#include <string.h>

//****************************************************************
// A custom String Class which supports constructor, destructor, 
// copy constructor, move constructor, move assignment operator,
// and more.
//****************************************************************
class MyString {
    private:
    // pointer to character array
    char* buffer;
    // Private default constructor
    MyString() : buffer(NULL) {
        std::cout << "Default constructor called" << std::endl;
    }

    public:
    // Constructor
    MyString(const char* str) {
        std::cout << "Constructor called for: " << str << std::endl;
        if (str != NULL) {
            // allocate space in memory for buffer
            buffer = new char[strlen(str) + 1];
            // copy contents of str to buffer
            strcpy(buffer, str);
        }
        else {
            buffer = NULL;
        }
    }

    // Destructor
    ~MyString() {
        if (buffer != NULL) {
            delete[] buffer;
        }
    }

    // Move Constructor
    MyString(MyString&& moveSrc) {
        std::cout << "Move constructor moves from: " << moveSrc.buffer << std::endl;
        if (moveSrc.buffer != NULL) {
            // take ownership
            buffer = moveSrc.buffer;
            // free move source
            moveSrc.buffer = NULL;
        }
    }

    // Move Assignment operator
    MyString& operator=(MyString&& moveSrc) {
        std::cout << "Move assignment operator moves from: " << moveSrc.buffer << std::endl;
        // Ensure we don't assign it to itself
        if ((moveSrc.buffer != NULL) && (this != &moveSrc)) {
            // deallocate memory
            delete[] buffer;
            // take ownership
            buffer = moveSrc.buffer;
            // free move source
            moveSrc.buffer = NULL;
        }
        return *this;
    }

    // Copy constructor
    MyString(const MyString& copySrc) {
        std::cout << "Copy constructor copies from: " << copySrc.buffer << std::endl;
        buffer = NULL;
        if (copySrc.buffer != NULL) {
            // allocate space in memory for buffer
            buffer = new char[strlen(copySrc.buffer) + 1];
            // copy contents of copy buffer into buffer
            strcpy(buffer, copySrc.buffer);
            // print address of memory block being pointed to by buffer
            std::cout << "buffer points to: " << std::hex << (unsigned int*)buffer << std::endl;
        }
    }

    // Copy assignment
    MyString& operator=(const MyString& copySrc) {
        std::cout << "Copy assignment operator copies from: " << copySrc.buffer << std::endl;
        // Ensure we don't assign it to itself
        if ((copySrc.buffer != NULL) && (this != &copySrc)) {
            if (buffer != NULL) {
                // deallocate memory
                delete[] buffer;
            }
            // allocate memory for new buffer
            buffer = new char[strlen(copySrc.buffer) + 1];
            // copy from copy sources buffer
            strcpy(buffer, copySrc.buffer);
        }
        return *this;
    }

    // overloaded + operator
    MyString operator+(const MyString& rhs) {
        std::cout << "operator+ called:" << std::endl;
        MyString temp;
        if (rhs.buffer != NULL) {
            // allocate memory for buffer
            temp.buffer = new char[length() + strlen(rhs.buffer) + 1];
            // copy contents of buffer into newly created string
            strcpy(temp.buffer, buffer);
            // append rhs buffer to temp buffer
            strcat(temp.buffer, rhs.buffer);
        }
        return temp;
    }

    int length() { return strlen(buffer); }

    void show() {
        std::cout << "MyString contains a string of length: " << length() << " which contains the character array: " << (*this) << std::endl;
    }

    // Print string to screen. std::ostream declared as a friend of MyString
    // as it needs access to private variable buffer
    friend std::ostream& operator<<(std::ostream& fout, const MyString& str) {
        fout << str.buffer;
    }
};

int main(int argc, char** argv) {
    MyString s1("Hello ");
    MyString s2("World");
    MyString s3(" !!!");
    MyString sayHelloAgain ("will overwrite this to demonstrate move semantics");
    sayHelloAgain = s1 + s2 + s3;
    sayHelloAgain.show();
    return 0;
}