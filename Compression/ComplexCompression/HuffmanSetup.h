#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include "systemc.h"
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

class HuffmanSetup: public sc_module
{
public:
    HuffmanSetup(sc_module_name name, string text);
    SC_HAS_PROCESS(HuffmanSetup);
    Node* getNode(char ch, int freq, Node* left, Node* right);
    bool isLeaf(Node* root);
    void buildHuffmanTree();
    string _text;
    unordered_map<char, string> _huffmanCode;
    Node* _root;
};

