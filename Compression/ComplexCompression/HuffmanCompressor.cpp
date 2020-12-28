#include "HuffmanCompressor.h"
#include "HuffmanSetup.h"



void HuffmanCompressor::compress(string text) {
    HuffmanSetup* start = _setup;

    buildHuffmanTree(start, text);
}


// Traverse the Huffman Tree and store Huffman Codes in a map.
void HuffmanCompressor::encode(Node* root, string str, unordered_map<char, string>& huffmanCode, HuffmanSetup* start)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (start->isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode, start);
    encode(root->right, str + "1", huffmanCode,start );
}

//// Traverse the Huffman Tree and decode the encoded string
//void decode(Node* root, int& index, string str)
//{
//    if (root == nullptr) {
//        return;
//    }
//
//    // found a leaf node
//    if (isLeaf(root)) {
//        cout << root->ch;
//        return;
//    }
//
//    index++;
//
//    if (str[index] == '0') {
//        decode(root->left, index, str);
//    }
//    else {
//        decode(root->right, index, str);
//    }
//}

// Builds Huffman Tree and decodes the given input text
void HuffmanCompressor::buildHuffmanTree(HuffmanSetup* start,string text)
{
    // base case: empty string
    if (text == EMPTY_STRING) {
        return;
    }

    // count frequency of appearance of each character
    // and store it in a map
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create a leaf node for each character and add it
    // to the priority queue.
    for (auto pair : freq) {
        pq.push(start->getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1)
    {
        // Remove the two nodes of the highest priority
        // (the lowest frequency) from the queue

        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();

        // Create a new internal node with these two nodes
        // as children and with frequency equal to the sum
        // of the two nodes' frequencies. Add the new node
        // to the priority queue.

        int sum = left->freq + right->freq;
        pq.push(start->getNode('\0', sum, left, right));
    }

    // root stores pointer to the root of Huffman Tree
    Node* root = pq.top();

    // Traverse the Huffman Tree and store Huffman Codes
    // in a map. Also print them
    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode, start);

    cout << "Huffman Codes are:\n" << '\n';
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nOriginal string is:\n" << text << '\n';

    // Print encoded string
    string str;
    for (char ch : text) {
        str += huffmanCode[ch];
    }

    cout << "\nEncoded string is:\n" << str << '\n';
    //cout << "\nDecoded string is:\n";

    //if (isLeaf(root))
    //{
    //    // Special case: For input like a, aa, aaa, etc.
    //    while (root->freq--) {
    //        cout << root->ch;
    //    }
    //}
    //else
    //{
    //    // Traverse the Huffman Tree again and this time,
    //    // decode the encoded string
    //    int index = -1;
    //    while (index < (int)str.size() - 1) {
    //        decode(root, index, str);
    //    }
    //}
}

HuffmanCompressor::HuffmanCompressor(HuffmanSetup* setup)
{
    _setup = setup;
}
