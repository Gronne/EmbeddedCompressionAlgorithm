#include "HuffmanDecompressor.h"


HuffmanDecompressor::HuffmanDecompressor(HuffmanSetup* setup)
{
    _setup = setup;
}

// Traverse the Huffman Tree and decode the encoded string
void HuffmanDecompressor::decode(Node* root, int& index, string str)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (_setup->isLeaf(root)) {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
    }
}

void HuffmanDecompressor::Decompressor(Node* root, string str)
{
    cout << "\nDecoded string is:\n";

    if (_setup->isLeaf(root))
    {
        // Special case: For input like a, aa, aaa, etc.
        while (root->freq--) {
            cout << root->ch;
        }
    }
    else
    {
        // Traverse the Huffman Tree again and this time,
        // decode the encoded string
        int index = -1;
        while (index < (int)str.size() - 1) {
            decode(root, index, str);
        }
    }
}
