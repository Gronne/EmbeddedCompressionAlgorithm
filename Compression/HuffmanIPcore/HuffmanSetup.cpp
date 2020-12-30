#include "HuffmanSetup.h"
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

void HuffmanSetup::setup() {
    // mapping based on frequency
    

    

    //unordered_map<indata, int> freq;
    //for (auto data : indata) {
    //    freq[data]++;
    //}

    //priority_queue<ModelT*, vector<ModelT*>, comp<typename T::value_type>> pq;

    //// Create a leaf node for each character and add it
    //// to the priority queue.
    //for (auto pair : freq) {
    //    pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    //}

    //while (pq.size() != 1)
    //{
    //    // Get the two nodes with the highest frequency

    //    ModelT* left = pq.top(); pq.pop();
    //    ModelT* right = pq.top(); pq.pop();

    //    // Create a new node with these two nodes
    //    // as children.  Add the new node
    //    // to the priority queue.

    //    int sum = left->freq + right->freq;
    //    pq.push(getNode('\0', sum, left, right));
    //}

    //// root stores pointer to the root of Huffman Tree
    //_root = pq.top();
    //return true;
}