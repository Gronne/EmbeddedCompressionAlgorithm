#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
using namespace std;
class HuffmanCompressor
{
public:
	HuffmanCompressor(HuffmanSetup* _setup);
	string compress(string text);
	void encode(Node* root, string str);
	string buildHuffmanTree(HuffmanSetup* _setup, string text);
	Node* _root;
	unordered_map<char, string> _huffmanCode;
private:
	HuffmanSetup* _setup;
};

