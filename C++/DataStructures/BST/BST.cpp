#include <iostream>

struct Node{
int data;
Node* left = nullptr;
Node* right = nullptr;
Node(int data):data(data){}
};

class BST{
    Node* root = nullptr;

    Node* insert(Node* root,int data){
    if(root == nullptr)
        return new Node(data);
        if(data > root->data){
        root->right = insert(root->right,data);
        }
        else{
        root->left = insert(root->left,data);
        }
        return root;
        }

    void inorderTraversal(Node* root){
        if (root == nullptr) return;
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
    public:
    void insert(int data){
        root = insert(root,data);
    }
    void inorderTraversal(){
        inorderTraversal(root);
    }
    
    
};

int main(){

    BST bst;
    bst.insert(15);
    bst.insert(17);
    bst.insert(11);
    bst.insert(33);
    bst.insert(2);
    bst.insert(10);
    bst.insert(0);
    bst.insert(17);
    bst.insert(14);
    bst.inorderTraversal();



}