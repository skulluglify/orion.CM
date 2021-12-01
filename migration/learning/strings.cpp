#include<iostream>
#include<cstring>
#include<string>

#define LOG(x) std::cout << x << std::endl;

class String {

    private:

        char* m_Buffer;
        uint32_t m_Size;

    public:

        String(void) {}
        
        String(const char* string) {

            m_Size = strlen(string);
            m_Buffer = new char[m_Size + 1];
            memcpy(m_Buffer, string, m_Size);
            m_Buffer[m_Size] = 0;
        }
        
        String(const String& other) : m_Size(other.m_Size) {

            m_Buffer = new char[m_Size + 1];
            memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
        }

        ~String() {

            delete[] m_Buffer;
        }

        char& operator[](uint32_t index) {

            return m_Buffer[index];
        }

        friend std::ostream& operator<<(std::ostream& stream, const String& string);
};


std::ostream& operator<<(std::ostream& stream, const String& string) {

    stream << string.m_Buffer;
    return stream;
}

void printString(const String& string) {
    std::cout << string << std::endl;
}

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    String name = "UDIN";
    String something = name;

    something[2] = 'A';
    
    printString(name);
    printString(something);

    return 0;
}
