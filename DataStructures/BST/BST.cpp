#include <iostream>

struct Node{
int key;
int value;
Node* left = nullptr;
Node* right = nullptr;
Node(int key,int value):key{key},value{value} {}
};

    void insert(Node* node,int key,int value){
        if(key < node->key){
            if(node->left == nullptr) node->left = new Node(key,value);
            else insert(node->left, key, value);
        }
        else{ // key >= node->key(Non-strict BST)
            if(node->right == nullptr) node->right = new Node(key,value);
            else insert(node->right, key, value);
        }
        }

    Node* search(Node* node, int key){
        if(node == nullptr || key == node->key)
            return node;
        if(key < node->key)
            return search(node->left,key);
        return search(node->right,key);
    }
    Node* getMin(Node* node){
        if(node == nullptr || node->left == nullptr) return node;
        return getMin(node->left);
    }

    Node* getMax(Node* node){
        if(node == nullptr || node->right == nullptr) return node;
        return getMax(node->right);
    }

        void remove(Node*& node, int key){
        if(node == nullptr) return;
        if (key < node->key)
            remove(node-> left,key);
        else if(key > node->key)
            remove(node-> right,key);
        else{
            if(node->left == nullptr || node->right == nullptr){
                node = (node->left == nullptr) ? node->right : node->left;
            }
            else{
                Node* maxElementinleft = getMax(node->left);
                node->key = maxElementinleft->key;
                node->value = maxElementinleft->value;
                remove(node->left,maxElementinleft->key);
            }
        }
           
    }
   
    void inorderTraversal(Node* node){
        if (node == nullptr) return;
        inorderTraversal(node->left);
        std::cout << node->key << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node* node){
        if (node == nullptr) return;
        std::cout << node->key << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);

    }

    void postorderTraversal(Node* node){
        if (node == nullptr) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->key << " ";
    }

    void deleteTree(Node* node){
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
    void printResult(Node* result){
    if (result != nullptr)
    std::cout << "Found key: " << result->key << " with value: " << result->value << "\n";
    else
    std::cout << "Key not found.\n";
    }


int main(){
    Node* root = new Node(21,201);
    insert(root,15,302);
    insert(root,17,320);
    insert(root,11,201);
    insert(root,33,478);
    insert(root,38,408);
    insert(root,23,488);
    insert(root,27,778);
    insert(root,111,178);
    insert(root,2,854);
    insert(root,10,784);
    insert(root,0,412);
    insert(root,17,201);
    insert(root,14,214);

    std::cout << "Inorder: ";
    inorderTraversal(root);
    std::cout << "\n";

    std::cout << "Postorder: ";
    postorderTraversal(root);
    std::cout << "\n";

    std::cout << "Preorder: ";
    preorderTraversal(root);
    std::cout << "\n";

    remove(root, 0);
    remove(root, 11);
    remove(root, 38);

    std::cout << "After removal, Inorder: ";
    inorderTraversal(root);
    std::cout << "\n";

    std::cout << "After removal, Postorder: ";
    postorderTraversal(root);
    std::cout << "\n";

    std::cout << "After removal, Preorder: ";
    preorderTraversal(root);
    std::cout << "\n";
    printResult(search(root,10));
    printResult(search(root,11));
    deleteTree(root);
}
