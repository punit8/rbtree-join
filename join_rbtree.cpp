#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};
typedef Node *NodePtr;
class RedBlackTree
{
private:
NodePtr root;
NodePtr TNULL;
void initializeNULLNode(NodePtr node, NodePtr parent)
{
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
}
void preOrderHelper(NodePtr node)
{
    if (node != TNULL){
        cout << node->data << "(" << ((node->color == 0) ? "B) " : "R) ");
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}
void preOrder_to_array_helper(NodePtr node, vector<int> &v)
{
    if (node != TNULL)
    {
        v.push_back(node->data);
        preOrder_to_array_helper(node->left, v);
        preOrder_to_array_helper(node->right, v);
    }
}
void inOrder_to_array_helper(NodePtr node, vector<int> &v)
{
    if (node != TNULL)
    {
        inOrder_to_array_helper(node->left, v);
        v.push_back(node->data);
        inOrder_to_array_helper(node->right, v);
    }
}
void inOrderHelper(NodePtr node)
{
  if (node != TNULL)
  {
    inOrderHelper(node->left);
    cout << node->data << "(" << ((node->color == 0) ? "B) " : "R) ");
    inOrderHelper(node->right);
  }
}
void insertFix(NodePtr k)
{
  NodePtr u;
  while (k->parent->color == 1)
  {
        if (k->parent == k->parent->parent->right){
        u = k->parent->parent->left;
            if (u->color == 1){
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            }
            else{
                if (k == k->parent->left)
                {
                k = k->parent;
                rightRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        }
        else
        {
        u = k->parent->parent->right;
        if (u->color == 1){
            u->color = 0;
            k->parent->color = 0;
            k->parent->parent->color = 1;
            k = k->parent->parent;
        }
        else{
            if (k == k->parent->right)
            {
            k = k->parent;
            leftRotate(k);
            }
            k->parent->color = 0;
            k->parent->parent->color = 1;
            rightRotate(k->parent->parent);
        }
    }
    if (k == root)
    {
      break;
    }
  }
  root->color = 0;
}
public:
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void preorder(){
        preOrderHelper(this->root);
    }
    void preorder_to_array(vector<int> &v){
        preOrder_to_array_helper(this->root, v);
    }
    void inorder(){
    inOrderHelper(this->root);
    }
    void inorder_to_array(vector<int> &v){
        inOrder_to_array_helper(this->root, v);
    }
    void leftRotate(NodePtr x){
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr){
            this->root = y;
        }else if (x == x->parent->left){
            x->parent->left = y;
        }else{
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(NodePtr x){
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr){
            this->root = y;
        }
        else if (x == x->parent->right){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
    void insert(int key){
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;
        NodePtr y = nullptr;
        NodePtr x = this->root;
        while (x != TNULL){
            y = x;
            if (node->data < x->data){
            x = x->left;
            }
            else{
            x = x->right;
            }
        }
        node->parent = y;
        if (y == nullptr){
            root = node;
        }
        else if (node->data < y->data){
            y->left = node;
        }
        else{
            y->right = node;
        }
        if (node->parent == nullptr){
            node->color = 0;
            return;
        }
        if(node->parent->parent == nullptr){
            return;
        }
        insertFix(node);
        }
        NodePtr getRoot()
        {
        return this->root;
        }
};

void displayvector(vector<int> &v){
    for(int x : v){
        cout << x << " ";
    }
    cout << '\n';
}
int main()

{
    cout << "enter 1 for coustom input,\nenter 2 for random input\n";
    int choice;
    cin >> choice;

    switch(choice){
        case 1:
        {
            RedBlackTree rbt1;
            RedBlackTree rbt2;
            vector<int> tree1, tree2;
            int n1, n2;
            cout << "enter no of values in tree 1 ";
            cin >> n1;
            for(int i = 0; i < n1; i++){
                int temp;
                cin >> temp;
                rbt1.insert(temp);
            }
            cout << "enter no of values in tree 2 ";
            cin >> n2;
            for(int i = 0; i < n2; i++){
                int temp;
                cin >> temp;
                rbt2.insert(temp);
            }
            cout << "inoder of tree1 before Joining \n";
            rbt1.inorder();
            vector<int> preordert2;
            rbt2.preorder_to_array(preordert2);
            for(int x: preordert2){
                rbt1.insert(x);
            }
            cout << "\ninoder of tree1 after Joining \n";
            rbt1.inorder();

            break;
        }
        case 2:
        {
            set<int> s1;
            set<int> s2;
            int num = 25000;
            while(s1.size() < num){
                s1.insert(rand());
            }
            while(s2.size() < num){
                s2.insert(rand());
            }
            RedBlackTree rbt1, rbt2;
            for(auto it = s1.begin(); it != s1.end(); it++){
                rbt1.insert(*it);
            }
            for (auto it = s2.begin(); it != s2.end(); it++)
            {
                rbt2.insert(*it);
            }
            // rbt1.inorder();
            //Method 1: join inorder of both tree and create new tree out of it using it
            
            
            {
                RedBlackTree rbtans1;
                vector<int> rbt1in;
                rbt1.inorder_to_array(rbt1in);
                rbt2.inorder_to_array(rbt1in);
                sort(rbt1in.begin(), rbt1in.end());
                // cout << rbt1in.size() << " " << rbt2in.size() << '\n';
                auto start1 = chrono::high_resolution_clock::now();
                for(int x : rbt1in){
                    rbtans1.insert(x);
                }
                auto end1 = chrono::high_resolution_clock::now();
                double time_taken =chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
                // time_taken *= 1e-9;
                cout << "Time taken by Method 1 is : " << fixed << setprecision(2) << time_taken;
                cout << " nanosec" << endl;
            }
        

            //Method 2: keep one tree as it is, add tree 2 to tree 1, in preorder. 
            {
                RedBlackTree rbtans2 = rbt1;
                // rbtans2.inorder();
                auto start1 = chrono::high_resolution_clock::now();
                vector<int> rbt2pre;

                rbt2.preorder_to_array(rbt2pre);
                // cout << "SIZE " << rbt2pre.size() << " \n";
                for (int x : rbt2pre)
                {
                    rbtans2.insert(x);
                }
                auto end1 = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
                // time_taken *= 1e9;
                cout << "Time taken by Method 2 is : " << fixed << setprecision(2) << time_taken;
                cout << " nanosec" << endl;
            }
            break;
        }
    }
}