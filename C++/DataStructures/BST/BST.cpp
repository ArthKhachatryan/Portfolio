#include <iostream>

struct Node{
int data;
Node* left = nullptr;
Node* right = nullptr;
Node(int data):data(data){}
};

class BST{
    Node* root = nullptr;

    Node* search(Node* root,int data){
        if(root == nullptr || data == root->data)
        return root;
        if(data > root->data)
            return search(root->right,data);

        return search(root->left,data);
    }

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
    void search(int data){
        if(search(root,data) == nullptr)
            std::cout << "\nNot found";
        else
            std::cout << "\nFound";
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

    bst.search(10);
    bst.search(111);
}