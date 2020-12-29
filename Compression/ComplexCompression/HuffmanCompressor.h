#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
#include <stack>
#include "systemc.h"
using namespace std;
class HuffmanCompressor : public sc_module
{
public:
	HuffmanCompressor(sc_module_name name, HuffmanSetup* _setup, string creationstring);
	SC_HAS_PROCESS(HuffmanCompressor);
	void compress();
	Node* _root;
	unordered_map<char, string> _huffmanCode;
	string _encodedString;
	void encode(string str);
	//string _encodestr;
private:

	sc_fifo<uint32_t> localstack;

	string _creationstring;
	void encode(Node* root, string str);
	//string buildHuffmanTree(HuffmanSetup* _setup, string text);
	
	HuffmanSetup* _setup;
};

