#pragma once
#include "HuffmanSetup.h"
#include <iostream>
#include <string>
#include <stack>
#include "systemc.h"
#include "ICompressionCompress.h"
using namespace std;
template<class DecompressT, class CompressT>
class HuffmanCompressor : public sc_module, public ICompressionCompress<DecompressT, CompressT>
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
		for (iterator_for<DecompressT> data : sensorData) {
			compressedData += _huffmanCode[data];
		}

		cout << "\nEncoded string is:\n" << compressedData << '\n';
		return compressedData;

	};

	void setModel(ICompressionSetup<CompressT, Node<iterator_for<DecompressT>>*>* setup) {
		_setup = (HuffmanSetup<CompressT>*)setup;
		_root = _setup->getModel();
	};

private:
	void encode(Node<iterator_for<DecompressT>>* root, string str) {
		stack<pair<Node<iterator_for<DecompressT>>*, string>> stack;
		stack.push({ root,str });
		while (!stack.empty())
		{
			pair<Node<iterator_for<DecompressT>>*, string> element = stack.top();
			// Pop a node from stack
			stack.pop();
			if (element.first == nullptr) {
				break;
			}

			// found a leaf node
			if (_setup->isLeaf(element.first)) {
				_huffmanCode[element.first->ch] = (element.second != EMPTY_STRING) ? element.second : "1";
			}
			if (element.first->left != nullptr)
				stack.push({ element.first->left, element.second + "0" });
			if (element.first->right != nullptr)
				stack.push({ element.first->right, element.second + "1" });
		}
	}
	
	Node<iterator_for<DecompressT>>* _root;
	unordered_map<iterator_for<DecompressT>, string> _huffmanCode;
	HuffmanSetup<CompressT>* _setup;
};

