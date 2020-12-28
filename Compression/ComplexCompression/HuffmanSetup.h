#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""

// A Tree node
struct Node
{
    char ch;
    int freq;
    Node* left, * right;
};

// Comparison object to be used to order the heap
struct comp
{
    bool operator()(Node* l, Node* r)
    {
        // the highest priority item has the lowest frequency
        return l->freq > r->freq;
    }
};

class HuffmanSetup
{
public:
    Node* getNode(char ch, int freq, Node* left, Node* right);
    bool isLeaf(Node* root);
    void buildHuffmanTree(string text);
    unordered_map<char, string> _huffmanCode;
    Node* _root;
};

