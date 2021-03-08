#include <iostream>
using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;
};

class BinaryTree
{
    Node *root;
    public:
    BinaryTree()
    {
        root =NULL;
    }
    BinaryTree(char ch)
    {
        root = new
    }
};

int main()
{
    char root = NULL;
    int c = 0;
    int n = 0;
    int m = 0;
    char d[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    BinaryLinkList<char> a;
    a.preOrderCreate(root, d, 0);
    cout << a.height() << a.leafNum() << endl;
    return 0;
}