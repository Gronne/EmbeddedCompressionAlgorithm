#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
#include "systemc.h"
#include <stack>
#include "ICompressionDecompress.h"
using namespace std;
template<class DecompressT, class CompressT, class ModelT = Node<typename DecompressT::value_type>>
class HuffmanDecompressor : public sc_module, public ICompressionDecompress<DecompressT, CompressT, ModelT>
{
public:
	HuffmanDecompressor(sc_module_name name)
    {
        //SC_THREAD(Decompressor);
    }
	SC_HAS_PROCESS(HuffmanDecompressor);
    DecompressT decode(CompressT compressedData)
    {
        cout << "\nDecoded string is:\n";
        if (_root == nullptr) {
            return DecompressT();
        }
        DecompressT tmp;
        if (_setup->isLeaf(_root))
        {
            // Special case: For input like a, aa, aaa, etc.
            while (_root->freq--) {
                return DecompressT({ DecompressT::value_type(_root->data) });
            }
        }
        else
        {
            // Traversing the Huffmantree i. e. the _root
            // decode the encoded string i. e. the compressedData
            int index = -1;
            
            while (index < (int)compressedData.size() - 1) {
                tmp += decode(_root, index, compressedData);
            }
            
        }
        return tmp;
    }
    DecompressT decode(ModelT* root, int& index, string str)
    {
        stack<pair<ModelT*, pair<int&, string>>> stack;
        stack.push({ root,{index,str } });
        while (!stack.empty())
        {
            pair<ModelT*, pair<int&, string>> element = stack.top();
            // Pop a node from stack
            stack.pop();
            if (element.first == nullptr) {
                break;
            }

            if (_setup->isLeaf(element.first)) {
                return DecompressT({DecompressT::value_type(element.first->data)});
                break;
            }
            element.second.first++;

            if (element.second.second[element.second.first] == '0') {
                if (element.first->left != nullptr)
                    stack.push({ element.first->left,{element.second.first,element.second.second} });
            }
            else {
                if (element.first->right != nullptr)
                    stack.push({ element.first->right,{element.second.first,element.second.second} });
            }
        }

    }

	void setModel(ICompressionSetup<DecompressT,ModelT>* setup) {
        _setup = (HuffmanSetup<DecompressT>*)setup;
        _root = _setup->getModel();
	};
private: 
	ModelT* _root;
    HuffmanSetup<DecompressT>* _setup;
};

