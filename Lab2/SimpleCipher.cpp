#include <iostream>
#include <string>

using namespace std;

class SimpleCipher
{
    private:
    const int size = 256;
    char* originalChars;
    char* reversedChars; 
    
    int getCharIndex(char ch)
    {
        int i = 0;
        while(reversedChars[i] != ch)
        {
            i++;
        }
        return i;
    }
    
    public:
    SimpleCipher()
    {
        originalChars = new char[size];
        reversedChars = new char[size];
        
        for(int i = 0; i < size; i++)
        {
            originalChars[i] = (char)i;
            reversedChars[i] = (char)(size - i);
        }
    }
    
    char* encode(const string &input) {
        char* encodedText = new char[input.length()];
        
        for(int i = 0; i < input.length(); i++)
        {
            encodedText[i] = reversedChars[(int)input[i]];
        }
    
        return encodedText;
    }
    
    char* decode(const std::string &encodedInput) {
        char* decodedText = new char[encodedInput.length()];
        
        for(int i = 0; i < encodedInput.length(); i++)
        {
            decodedText[i] = originalChars[getCharIndex(encodedInput[i])];
        }
    
        return decodedText;
    }
    
    ~SimpleCipher()
    {
        delete[] originalChars;
        delete[] reversedChars;
    }
};

int main() {
    SimpleCipher cipher;
    
    std::string userInput;
    std::cout << "Enter the text to encode: ";
    std::cin >> userInput;
    
    char* encodedMessage = cipher.encode(userInput);
    std::cout << "Encoded message: " << encodedMessage << std::endl;

    char* decodedMessage = cipher.decode(encodedMessage);
    std::cout << "Decoded message: " << decodedMessage << std::endl;

    delete[] encodedMessage;
    delete[] decodedMessage;

    return 0;
}
