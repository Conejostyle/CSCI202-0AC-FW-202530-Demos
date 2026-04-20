//M05 part b lab Benjamin Munoz

#include <vector>
using namespace std;

class BTreeNode{
    public:
    vector<int> keys; // Vector to store keys in the node
    vector<BTreeNode*> children; // Vector to store pointers to child nodes
    bool isLeaf; // Flag to indicate if the node is a leaf

    BTreeNode(bool leaf) {
        isLeaf = leaf;
    }
};