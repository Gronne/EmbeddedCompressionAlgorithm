#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
#include "systemc.h"
using namespace std;
class HuffmanDecompressor : public sc_module
{
public:
	HuffmanDecompressor(sc_module_name name, HuffmanSetup* _setup, Node* root);
	SC_HAS_PROCESS(HuffmanDecompressor);
	void Decompressor();
	void decode(Node* root, int& index, string str);
	void ReadData(string str);
private: 
	Node* _root;
	string _encodestr;
	HuffmanSetup* _setup;
};

