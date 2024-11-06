#include <iostream>
#include <string>

std::string caesarEncrypt(const std::string& text, int shift) {
    std::string encrypted = text;
    for (char& c : encrypted) {
        c = (c + shift) % 128;  
    }
    return encrypted;
}

std::string caesarDecrypt(const std::string& text, int shift) {
    std::string decrypted = text;
    for (char& c : decrypted) {
        c = (c - shift + 128) % 128;
    }
    return decrypted;
}

std::string rleCompress(const std::string& text) {
    std::string compressed;
    for (size_t i = 0; i < text.length(); ++i) {
        int count = 1;
        while (i + 1 < text.length() && text[i] == text[i + 1]) {
            ++count;
            ++i;
        }
        compressed += text[i];
        if (count > 1) compressed += std::to_string(count);
    }
    return compressed;
}

std::string rleDecompress(const std::string& text) {
    std::string decompressed;
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        std::string countStr;
        while (i + 1 < text.length() && std::isdigit(text[i + 1])) {
            countStr += text[++i];
        }
        int count = countStr.empty() ? 1 : std::stoi(countStr);
        decompressed.append(count, c);
    }
    return decompressed;
}

std::string encrypt(const std::string& text, int shift) {
    return rleCompress(caesarEncrypt(text, shift));
}

std::string decrypt(const std::string& text, int shift) {
    return caesarDecrypt(rleDecompress(text), shift);
}

int main() {
    std::string originalText = "hello world!!!";
    int shift = 3;

    std::string encryptedText = encrypt(originalText, shift);
    std::cout << "Encrypted Text: " << encryptedText << std::endl;

    std::string decryptedText = decrypt(encryptedText, shift);
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}

