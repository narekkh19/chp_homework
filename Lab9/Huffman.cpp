#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char c, int f) : character(c), frequency(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

void createHuffmanCodes(Node* node, const std::string& path, std::unordered_map<char, std::string>& codes) {
    if (!node) return;

    if (!node->left && !node->right) {
        codes[node->character] = path;
        return;
    }

    createHuffmanCodes(node->left, path + "0", codes);
    createHuffmanCodes(node->right, path + "1", codes);
}

Node* buildHuffmanTree(const std::string& text) {
    std::unordered_map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;

    for (const auto& entry : frequency) {
        minHeap.push(new Node(entry.first, entry.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }

    return minHeap.top();
}

std::string encodeText(const std::string& text, const std::unordered_map<char, std::string>& codes) {
    std::string encoded = "";
    for (char c : text) {
        encoded += codes.at(c);
    }
    return encoded;
}

std::string decodeText(Node* root, const std::string& encoded) {
    std::string decoded = "";
    Node* current = root;

    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            decoded += current->character;
            current = root;
        }
    }

    return decoded;
}

int main() {
    while (true) {
        std::cout << "Enter text to encode (or 'exit' to quit): ";
        std::string text;
        std::getline(std::cin, text);

        if (text == "exit") {
            std::cout << "Exiting the program.\n";
            break;
        }

        Node* huffmanTreeRoot = buildHuffmanTree(text);
        std::unordered_map<char, std::string> huffmanCodes;
        createHuffmanCodes(huffmanTreeRoot, "", huffmanCodes);

        std::string encodedString = encodeText(text, huffmanCodes);
        std::cout << "Encoded String: " << encodedString << "\n";

        std::cout << "Decoded String from the encoded binary sequence: ";
        std::string decodedString = decodeText(huffmanTreeRoot, encodedString);
        std::cout << decodedString << "\n";

        std::string reEncodedString = encodeText(decodedString, huffmanCodes);
        std::cout << "Re-encoded String from Decoded Input: " << reEncodedString << "\n";

        if (reEncodedString == encodedString) {
            std::cout << "Verification Passed: Re-encoded string matches the original input encoded string.\n\n";
        } else {
            std::cout << "Verification Failed: Re-encoded string does NOT match the original input encoded string.\n\n";
        }
    }

    return 0;
}
