#include <iostream>
#include <string>
using namespace std;

string encodeRLE(const string& input) {
    string encoded = "";
    int count = 1;

    for (int i = 1; i < input.length(); i++) {
        if (input[i] == input[i - 1]) {
            count++;
        } else {
            while (count > 255) {
                encoded += input[i - 1];
                encoded += "255";
                count -= 255;
            }
            encoded += input[i - 1];
            encoded += to_string(count);
            count = 1;
        }
    }

    while (count > 255) {
        encoded += input[input.length() - 1];
        encoded += "255";
        count -= 255;
    }
    encoded += input[input.length() - 1];
    encoded += to_string(count);

    return encoded;
}

string decodeRLE(const string& encoded) {
    string decoded = "";
    int i = 0;

    while (i < encoded.length()) {
        char character = encoded[i++];
        int count = 0;

        while (i < encoded.length() && isdigit(encoded[i])) {
            count = count * 10 + (encoded[i] - '0');
            i++;
        }

        for (int j = 0; j < count; j++) {
            decoded += character;
        }
    }

    return decoded;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    string encoded = encodeRLE(input);
    string decoded = decodeRLE(encoded);

    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}
