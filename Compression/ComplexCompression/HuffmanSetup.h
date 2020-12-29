#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include "systemc.h"
#include "ICompressionSetup.h"
using namespace std;

#define EMPTY_STRING ""

template<class T>
struct iterator_for
{
    typedef typename T::iterator  type;
};

// A Tree node
template <typename T>
struct Node
{
    T data;
    int freq;
    Node* left, * right;
};

// Comparison object to be used to order the heap
template <typename T>
struct comp
{
    bool operator()(Node<T>* l, Node<T>* r)
    {
        // the highest priority item has the lowest frequency
        return l->freq > r->freq;
    }
};

template <class T>
class HuffmanSetup: public sc_module, public ICompressionSetup<T,Node<iterator_for<T>>>
{
public:
    HuffmanSetup(sc_module_name name) : sc_module(name)
    {
        //SC_METHOD(setup);
    }
    SC_HAS_PROCESS(HuffmanSetup);
    // Function to allocate a new tree node
    Node<iterator_for<T>>* getNode(T data, int freq, Node<iterator_for<T>>* left, Node<iterator_for<T>>* right)
    {
        Node<iterator_for<T>>* node = new Node<iterator_for<T>>();
        node->data = data;
        node->freq = freq;
        node->left = left;
        node->right = right;
        return node;
    }
    // Utility function to check if Huffman Tree contains only a single node
    bool isLeaf(Node<iterator_for<T>>* root)
    {
        return root->left == nullptr && root->right == nullptr;
    }
    bool setup(T datachunk)
    {

        // count frequency of appearance of each character
        // and store it in a map
        unordered_map<iterator_for<T>, int> freq;
        for (iterator_for<T> data : datachunk) {
            freq[data]++;
        }

        // Create a priority queue to store live nodes of Huffman tree
        priority_queue<Node<iterator_for<T>>*, vector<Node<iterator_for<T>>*>, comp<iterator_for<T>>> pq;

        // Create a leaf node for each character and add it
        // to the priority queue.
        for (auto pair : freq) {
            pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
        }

        // do till there is more than one node in the queue
        while (pq.size() != 1)
        {
            // Remove the two nodes of the highest priority
            // (the lowest frequency) from the queue

            Node<iterator_for<T>>* left = pq.top(); pq.pop();
            Node<iterator_for<T>>* right = pq.top(); pq.pop();

            // Create a new internal node with these two nodes
            // as children and with frequency equal to the sum
            // of the two nodes' frequencies. Add the new node
            // to the priority queue.

            int sum = left->freq + right->freq;
            pq.push(getNode('\0', sum, left, right));
        }

        // root stores pointer to the root of Huffman Tree
        _root = pq.top();
        return true;
    }

    Node<iterator_for<T>>* GetModel()
    {
        return _root;
    }
private:
    Node<iterator_for<T>>* _root;
};

