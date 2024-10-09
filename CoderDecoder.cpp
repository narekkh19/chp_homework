#include <iostream>
#include <string>

class CoderDecoder {
public:
    static std::string Encode(const std::string& input, int shift) {
        std::string buffer = input;
        for (int i = 0; i < buffer.length(); i++) {
            char letter = buffer[i];
            letter = static_cast<char>(letter + shift);

            if (letter > 'z') {
                letter = static_cast<char>(letter - 26);
            } else if (letter < 'a') {
                letter = static_cast<char>(letter + 26);
            }

            buffer[i] = letter;
        }
        return buffer;
    }

    static std::string Decode(const std::string& input, int shift) {
        return Encode(input, -shift);
    }
};

int main() {
    std::string text;
    int shift;

    std::cout << "Enter text to encode: ";
    std::getline(std::cin, text);
    
    for (char& c : text) {
        c = std::tolower(c);
    }

    std::cout << "Enter shift value: ";
    std::cin >> shift;

    std::string encoded = CoderDecoder::Encode(text, shift);
    std::cout << "Encoded text: " << encoded << std::endl;

    std::string decoded = CoderDecoder::Decode(encoded, shift);
    std::cout << "Decoded text: " << decoded << std::endl;

    return 0;
}