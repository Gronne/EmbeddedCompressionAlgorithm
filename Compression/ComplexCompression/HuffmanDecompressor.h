#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
using namespace std;
class HuffmanDecompressor
{
public:
	HuffmanDecompressor(HuffmanSetup* _setup);
	void Decompressor(Node* root, string str);
	void decode(Node* root, int& index, string str);
private: 
	HuffmanSetup* _setup;
};

