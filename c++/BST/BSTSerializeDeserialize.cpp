#include <vector>
#include <iostream>
// Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 

class BST{
public:
    TreeNode *head;
    BST(vector<int> input)
    {
        head = NULL;
        for(int i : input)
            this->insert(i);
    }
    BST(TreeNode *head)
    {
        this->head  = head;
    }
    void insert(int i)
    {
        cout << "inserting " << i << endl;
        TreeNode *n = new TreeNode(i);
        if (!head)
            head = n;
        else
        { 
            TreeNode *cur = head;
            while(1)
            {
                if(cur->val < i)
                {
                    // go right
                    if(cur->right)
                        cur = cur->right;
                    else
                    {
                        cur->right = n;
                        break;
                    }
                }
                else
                {
                    // go left
                    if(cur->left)
                        cur = cur->left;
                    else
                    {
                        cur->left = n;
                        break;
                    }
                }
            }
        }
    }
    vector<int> preOrder()
    {
        vector<int> ret;
        preOrder(head, ret);
        return ret;
    }
    void preOrder(TreeNode *cur, vector<int> &ret)
    {
        if(!cur)
            return;
        ret.push_back(cur->val);
        preOrder(cur->left, ret);
        preOrder(cur->right, ret);
    }
};
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        //in order search to generate string
        BST in(root);
        string ret;
        vector<int> preO = in.preOrder();
        for (int i : preO)
        {
            ret += i;
            ret += ",";
        }
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        //use stringstream to get new list
        stringstream ss(data);
        int i;
        vector<int> input;
        
        while(ss >> i)
        {
            input.push_back(i);
            if(ss.peek() == ',')
                ss.ignore();
        }
        
        //push one note at a time into tree
        BST out(input);
        
        return out.head;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
