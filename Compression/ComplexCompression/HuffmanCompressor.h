#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
#include <stack>
#include "systemc.h"
#include "ICompressionCompress.h"
using namespace std;
template<class DecompressT, class CompressT, class ModelT = Node<typename DecompressT::value_type>>
class HuffmanCompressor : public sc_module, public ICompressionCompress<DecompressT, CompressT, ModelT>
{
public:
	HuffmanCompressor(sc_module_name name)
	{
		//SC_THREAD(compress);
	}
	SC_HAS_PROCESS(HuffmanCompressor);



	CompressT encode(DecompressT sensorData) {
		encode(_root, EMPTY_STRING);
		cout << "Huffman Codes are:\n" << '\n';
		for (auto pair : _huffmanCode) {
			cout << pair.first << " " << pair.second << '\n';
		}

		cout << "\nOriginal string is:\n" << sensorData << '\n';

		CompressT compressedData;
		for (auto data : sensorData) {
			compressedData += _huffmanCode[data];
		}

		cout << "\nEncoded string is:\n" << compressedData << '\n';
		return compressedData;

	};

	void setModel(ICompressionSetup<CompressT, ModelT>* setup) {
		_setup = (HuffmanSetup<CompressT>*)setup;
		_root = _setup->getModel();
	};

private:
	void encode(ModelT* root, string str) {
		stack<pair<ModelT*, string>> stack;
		stack.push({ root,str });
		while (!stack.empty())
		{
			pair<ModelT*, string> element = stack.top();
			// Pop a node from stack
			stack.pop();
			if (element.first == nullptr) {
				break;
			}

			// found a leaf node
			if (_setup->isLeaf(element.first)) {
				_huffmanCode[element.first->data] = (element.second != EMPTY_STRING) ? element.second : "1";
			}
			if (element.first->left != nullptr)
				stack.push({ element.first->left, element.second + "0" });
			if (element.first->right != nullptr)
				stack.push({ element.first->right, element.second + "1" });
		}
	}
	
	ModelT* _root;
	unordered_map<typename DecompressT::value_type, string> _huffmanCode;
	HuffmanSetup<CompressT>* _setup;
};

