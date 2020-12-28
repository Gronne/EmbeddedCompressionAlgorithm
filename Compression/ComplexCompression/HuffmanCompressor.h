#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
using namespace std;
class HuffmanCompressor
{
public:
	HuffmanCompressor(HuffmanSetup* _setup);
	void compress(string text);
	void encode(Node* root, string str, unordered_map<char, string>& huffmanCode, HuffmanSetup* _setup);
	void buildHuffmanTree(HuffmanSetup* _setup, string text);
private:
	HuffmanSetup* _setup;
};

