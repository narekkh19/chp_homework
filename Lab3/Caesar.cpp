#include <iostream>
#include <string>

using namespace std;

class CaesarCipher
{
    private:
    int shift;

    public:
    CaesarCipher(int shiftValue) {
        shift = shiftValue;
    }
    
    string encrypt(const string& plaintext) {
        string ciphertext = plaintext;
        
        for (int i = 0; i < plaintext.length(); i++) {
            ciphertext[i] = (plaintext[i] + shift) % 128;
        }
        
        return ciphertext;
    }

    string decrypt(const string& ciphertext) {
        string decryptedText = ciphertext;
        
        for (int i = 0; i < ciphertext.length(); i++) {
            decryptedText[i] = (ciphertext[i] - shift + 128) % 128;
        }
        
        return decryptedText;
    }
};

int main() {
    int shift;
    cout << "Enter the shift value: ";
    cin >> shift;

    CaesarCipher cipher(shift);
    
    string plaintext;
    cout << "Enter the text to encrypt: ";
    cin.ignore();
    getline(cin, plaintext);
    
    string ciphertext = cipher.encrypt(plaintext);
    cout << "Encrypted text: " << ciphertext << endl;
    
    string decryptedText = cipher.decrypt(ciphertext);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
