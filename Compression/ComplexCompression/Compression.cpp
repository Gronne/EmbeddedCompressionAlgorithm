// ComplexCompression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HuffmanCompressor.h"
#include "HuffmanSetup.h"
#include "HuffmanDecompressor.h"


// Huffman coding algorithm
int sc_main(int argc, char** argv)
{
    string text = "Huffman coding is a data compression algorithm.";
    HuffmanSetup* setup = new HuffmanSetup("HuffmanSetup",text);
    HuffmanCompressor* compressor = new HuffmanCompressor("HuffmanCompressor",setup,text);
    // wait for sample size
    compressor->compress();


    HuffmanDecompressor* decompressor = new HuffmanDecompressor("HuffmanDecompressor", setup, compressor->_root, compressor->_encodestr);
    decompressor->Decompressor();

    cout << "\nHuffman Codes are:\n" << '\n';
    for (auto pair : compressor->_huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nOriginal string is:\n" << "Hello world" << '\n';

    string str;
    for (char ch : "Hello world") {
        str += compressor->_huffmanCode[ch];
    }

    cout << "\nEncoded string is:\n" << str << '\n';
    decompressor->ReadData(str);
    decompressor->Decompressor();
    sc_start(200, SC_MS);
    return 0;
}
