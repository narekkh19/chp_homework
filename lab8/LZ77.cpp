#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TextProcessor {
public:
    void start() {
        while (true) {
            int option;
            cout << "Choose an option (1: Compress, 2: Decompress, others to quit): ";
            cin >> option;
            cin.ignore();

            if (option == 1) {
                cout << "Enter text to compress: ";
                string inputText;
                getline(cin, inputText);
                string compressedResult = performCompression(inputText);
                cout << "Compressed text: " << compressedResult << endl;
            } else if (option == 2) {
                cout << "Enter text to decompress: ";
                string compressedInput;
                getline(cin, compressedInput);
                string decompressedResult = performDecompression(compressedInput);
                cout << "Decompressed text: " << decompressedResult << endl;
            } else {
                cout << "Exiting the program." << endl;
                break;
            }
        }
    }

private:
    string performCompression(const string& input) {
        const int slidingWindow = 64;
        string compressedData;
        size_t position = 0;

        while (position < input.size()) {
            auto match = findBestMatch(input, position, slidingWindow);
            if (match.second > 3) {
                compressedData += "[" + to_string(match.first) + "|" + to_string(match.second) + "]";
                position += match.second;
            } else {
                compressedData += input[position];
                position++;
            }
        }
        return compressedData;
    }

    string performDecompression(const string& compressedText) {
        string decompressedData;
        size_t position = 0;

        while (position < compressedText.size()) {
            if (compressedText[position] == '[') {
                int backOffset = 0, matchLength = 0;
                position++;

                while (compressedText[position] != '|') {
                    backOffset = backOffset * 10 + (compressedText[position] - '0');
                    position++;
                }
                position++;

                while (compressedText[position] != ']') {
                    matchLength = matchLength * 10 + (compressedText[position] - '0');
                    position++;
                }
                position++;

                size_t startIdx = decompressedData.size() - backOffset;
                decompressedData += decompressedData.substr(startIdx, matchLength);
            } else {
                decompressedData += compressedText[position];
                position++;
            }
        }
        return decompressedData;
    }

    pair<int, int> findBestMatch(const string& input, size_t currentIndex, int windowSize) {
        int windowStart = max(0, static_cast<int>(currentIndex) - windowSize);
        int longestMatch = 0;
        int matchOffset = 0;

        for (int i = windowStart; i < currentIndex; ++i) {
            int currentLength = 0;

            while (currentIndex + currentLength < input.size() &&
                   input[i + currentLength] == input[currentIndex + currentLength]) {
                currentLength++;
            }

            if (currentLength > longestMatch) {
                longestMatch = currentLength;
                matchOffset = currentIndex - i;
            }
        }
        return {matchOffset, longestMatch};
    }
};

int main() {
    TextProcessor processor;
    processor.start();
    return 0;
}
