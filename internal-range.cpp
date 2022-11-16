#include "internal-range.h"
using namespace std;


// You may add any prototypes of helper functions here
int sumInternalRange(Node * root, int depth, int min, int max)
{
    if(root==nullptr || depth==0)
    {
        return 0;
    }
    else if (root->key>=min && root->key<=max)
    {
        return sumInternalRange(root->left, depth-1, min, max)+sumInternalRange(root->right, depth-1, min, max)+1;
    }
    else
    {
        return sumInternalRange(root->left, depth-1, min, max)+sumInternalRange(root->right, depth-1, min, max);
    }
}

// Now implement the sumInternalRange function and any necessary helpers

