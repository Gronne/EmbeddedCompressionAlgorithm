#include "HuffmanCompressor.h"
#include "HuffmanSetup.h"
#include <stdlib.h>




void HuffmanCompressor::compress() {
    // HuffmanSetup* start = _setup;

    //_encodestr = buildHuffmanTree(start, _creationstring);
    encode(_setup->_root, EMPTY_STRING);
    cout << "Huffman Codes are:\n" << '\n';
        for (auto pair : _huffmanCode) {
            cout << pair.first << " " << pair.second << '\n';
        }
    
        cout << "\nOriginal string is:\n" << _creationstring << '\n';
    
        // Print encoded string
        string str;
        for (char ch : _creationstring) {
            str += _huffmanCode[ch];
        }
    
        cout << "\nEncoded string is:\n" << str << '\n';
        _encodedString = str;
}

// public encode function to encode new incoming after initial encoding.
void HuffmanCompressor::encode(string str)
{
    string newstr;
    for (char ch : str) {
        newstr += _huffmanCode[ch];
    }
}


// Traverse the Huffman Tree and store Huffman Codes in a map.
void HuffmanCompressor::encode(Node* root, string str)
{
    stack<pair<Node*,string>> stack;
    stack.push({ root,str });
    while (!stack.empty())
    {
        pair<Node*,string> element = stack.top();
        // Pop a node from stack
        stack.pop();
        if (element.first == nullptr) {
            break;
        }

        // found a leaf node
        if (_setup->isLeaf(element.first)) {
            _huffmanCode[element.first->ch] = (element.second != EMPTY_STRING) ? element.second : "1";
        }
        if (element.first->left != nullptr)
            stack.push({ element.first->left, element.second + "0" });
        if (element.first->right != nullptr)
            stack.push({ element.first->right, element.second + "1" });
    }
}



// Builds Huffman Tree and decodes the given input text
//string HuffmanCompressor::buildHuffmanTree(HuffmanSetup* start,string text)
//{
//    // base case: empty string
//    if (text == EMPTY_STRING) {
//        return text;
//    }
//
//    // count frequency of appearance of each character
//    // and store it in a map
//    unordered_map<char, int> freq;
//    for (char ch : text) {
//        freq[ch]++;
//    }
//
//    // Create a priority queue to store live nodes of Huffman tree
//    priority_queue<Node*, vector<Node*>, comp> pq;
//
//    // Create a leaf node for each character and add it
//    // to the priority queue.
//    for (auto pair : freq) {
//        pq.push(_setup->getNode(pair.first, pair.second, nullptr, nullptr));
//    }
//
//    // do till there is more than one node in the queue
//    while (pq.size() != 1)
//    {
//        // Remove the two nodes of the highest priority
//        // (the lowest frequency) from the queue
//
//        Node* left = pq.top(); pq.pop();
//        Node* right = pq.top();    pq.pop();
//
//        // Create a new internal node with these two nodes
//        // as children and with frequency equal to the sum
//        // of the two nodes' frequencies. Add the new node
//        // to the priority queue.
//
//        int sum = left->freq + right->freq;
//        pq.push(start->getNode('\0', sum, left, right));
//    }
//
//    // root stores pointer to the root of Huffman Tree
//    _root = pq.top();
//
//    // Traverse the Huffman Tree and store Huffman Codes
//    // in a map. Also print them
//    encode(_root, EMPTY_STRING);
//
//    cout << "Huffman Codes are:\n" << '\n';
//    for (auto pair : _huffmanCode) {
//        cout << pair.first << " " << pair.second << '\n';
//    }
//
//    cout << "\nOriginal string is:\n" << text << '\n';
//
//    // Print encoded string
//    string str;
//    for (char ch : text) {
//        str += _huffmanCode[ch];
//    }
//
//    cout << "\nEncoded string is:\n" << str << '\n';
//    return str;
//}

HuffmanCompressor::HuffmanCompressor(sc_module_name name, HuffmanSetup* setup, string creationstring) : sc_module(name)
{
    SC_THREAD(compress);
    _creationstring = creationstring;
    _setup = setup;
}
