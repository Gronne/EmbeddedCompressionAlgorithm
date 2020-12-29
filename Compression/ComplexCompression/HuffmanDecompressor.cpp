#include "HuffmanDecompressor.h"


HuffmanDecompressor::HuffmanDecompressor(sc_module_name name, HuffmanSetup* setup, Node* root) : sc_module(name)
{
    SC_THREAD(Decompressor);
    _setup = setup;
    _root = root;
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

void HuffmanDecompressor::ReadData(string str)
{
    _encodestr = str;
}

void HuffmanDecompressor::Decompressor()
{
    cout << "\nDecoded string is:\n";
    if (_setup->_root == nullptr) {
        return;
    }

    if (_setup->isLeaf(_setup->_root))
    {
        // Special case: For input like a, aa, aaa, etc.
        while (_setup->_root->freq--) {
            cout << _setup->_root->ch;
        }
    }
    else
    {
        // Traverse the Huffman Tree again and this time,
        // decode the encoded string
        int index = -1;
        while (index < (int)_encodestr.size() - 1) {
            decode(_setup->_root, index, _encodestr);
        }
    }
}
