#include "HuffmanDecompressor.h"

#include <stack>

HuffmanDecompressor::HuffmanDecompressor(sc_module_name name, HuffmanSetup* setup, Node* root) : sc_module(name)
{
    SC_THREAD(Decompressor);
    _setup = setup;
    _root = root;
}

// Traverse the Huffman Tree and decode the encoded string
void HuffmanDecompressor::decode(Node* root, int& index, string str)
{
    stack<pair<Node*, pair<int&, string>>> stack;
    stack.push({ root,{index,str }});
    while (!stack.empty())
    {
        pair<Node*, pair<int&,string>> element = stack.top();
        // Pop a node from stack
        stack.pop();
        if (element.first == nullptr) {
            break;
        }

        if (_setup->isLeaf(element.first)) {
            cout << element.first->ch;
            break;
        }
        element.second.first++;

        if (element.second.second[element.second.first] == '0') {
            if (element.first->left != nullptr)
                stack.push({ element.first->left,{element.second.first,element.second.second} });
        }
        else {
            if (element.first->right != nullptr)
                stack.push({ element.first->right,{element.second.first,element.second.second} });
        }
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
