#include "HuffmanSetup.h"

HuffmanSetup::HuffmanSetup(sc_module_name name, string text) : sc_module(name)
{
    _text = text;
    SC_METHOD(buildHuffmanTree)
    
}

// Function to allocate a new tree node
Node* HuffmanSetup::getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Utility function to check if Huffman Tree contains only a single node
bool HuffmanSetup::isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}


void HuffmanSetup::buildHuffmanTree()
{
    // base case: empty string
    if (_text == EMPTY_STRING) {
        return;
    }

    // count frequency of appearance of each character
    // and store it in a map
    unordered_map<char, int> freq;
    for (char ch : _text) {
        freq[ch]++;
    }

    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create a leaf node for each character and add it
    // to the priority queue.
    for (auto pair : freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
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
        pq.push(getNode('\0', sum, left, right));
    }

    // root stores pointer to the root of Huffman Tree
    _root = pq.top();
}