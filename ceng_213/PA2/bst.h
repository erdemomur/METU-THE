#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void insertHelper(TreeNode* &n, const string key, const T& value);
    bool searchHelper(TreeNode* n, std::string value) const;
    void removeHelper(TreeNode* &n,std::string key);
    void tree2vector_helper(TreeNode* node, vector<TreeNode> &result);
    void destructor(TreeNode* node);
    vector<typename BST<T>::TreeNode>mergeHelper(const vector<TreeNode>& firstvector, const vector<TreeNode>& secondvector);
    
};
    
    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
    /* IMPLEMENT THIS */
        destructor(this->root);
    }
    
    template <class T>
    void BST<T>::destructor(TreeNode* node){
        if (node == NULL) {
            return;
        }
        destructor(node->left);
        destructor(node->right);
        delete node;
    }
    
    // Insert function for BST.
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
             /* IMPLEMENT THIS */
        if(this->root == NULL){
            TreeNode* n = new TreeNode(key,value);
            root = n;
            return *this;
        }
        insertHelper(this->root,key,value);
        return *this;
    }
    
    template <class T>
    void BST<T>::insertHelper(TreeNode* &n, const string key, const T& value){
        if (n == NULL){
            n = new TreeNode(key,value);
        }
        else if (n->key > key) insertHelper(n->left,key,value);
        else if (n->key < key) insertHelper(n->right,key,value);
    }

    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
     /* IMPLEMENT THIS */
        bool a = searchHelper(this->root,value);
        return a;
    }
    
    template <class T>
    bool BST<T>::searchHelper(TreeNode* n, std::string value) const {
        if (n == NULL){
            return false;
        }
        else{
            if(n->key == value) return true;
            else if (n->key > value) return searchHelper(n->left,value);
            else return searchHelper(n->right,value);
        }
    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
        removeHelper(this->root,key);
    }
    
    template <class T>
    void BST<T>::removeHelper(TreeNode* &n,std::string key){
        if (n == NULL) return;
        else if (n->key > key) removeHelper(n->left,key);
        else if (n->key < key) removeHelper(n->right,key);
        else{
            if (n->left != NULL && n->right != NULL){
                /*two child*/
                TreeNode* getMin = n->right;
                while (getMin->left != NULL) getMin = getMin->left;
                n->key = getMin->key;
                n->data = getMin->data;
                removeHelper(n->right,n->key);
            }
            else{
                TreeNode* prev = n;
                if (n->left != NULL){
                    /* one child on left*/
                    n = n->left;
                    if(prev != NULL) delete prev;
                    prev = NULL;
                }
                else if (n->right != NULL){
                    /* one child on right*/
                    n = n->right;
                    if(prev != NULL) delete prev;
                    prev = NULL;
                }
                else if (n->right == NULL && n->left == NULL){
                    /*leaf*/
                    if(n != NULL) delete n;
                    n = NULL;
                }
            }
        }
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vector_helper(root,result);
        return result;
    }
    
    template <class T>
    void BST<T>::tree2vector_helper(TreeNode* node, vector<TreeNode> &result){
        if (node != NULL) {
            tree2vector_helper(node->left,result);
            result.push_back(*node);
            tree2vector_helper(node->right,result);
        }
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */

        vector<TreeNode> firstbst = tree2vector(root);
        vector<TreeNode> secondbst = bst->tree2vector(bst->getRoot());
        vector<TreeNode> newvector = mergeHelper(firstbst,secondbst);
        
        BST<T>* mergedBST = new BST<T>();
        
        for(int i=0 ; i<newvector.size() ; i++){
                mergedBST->insert(newvector[i].key,newvector[i].data);
            }
        return mergedBST;
    }
    
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::mergeHelper(const vector<TreeNode>& firstvector, const vector<TreeNode>& secondvector) {
        vector<TreeNode> sortedvector;
        int i = 0, j = 0;

        while (i < firstvector.size() && j < secondvector.size()) {
            if (firstvector[i].key < secondvector[j].key) {
                sortedvector.push_back(firstvector[i]);
                i++;
            }
            else {
                sortedvector.push_back(secondvector[j]);
                j++;
            }
        }
        while (i < firstvector.size()) {
            sortedvector.push_back(firstvector[i]);
            i++;
        }
        while (j < secondvector.size()) {
            sortedvector.push_back(secondvector[j]);
            j++;
        }
        return sortedvector;
    }
    
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> firstbst = tree2vector(root);
    vector<TreeNode> secondbst = tree2vector(bst->getRoot());

    vector<TreeNode> intersectionvector;
    int i = 0, j = 0;

    while (i < firstbst.size() && j < secondbst.size()) {
        if (firstbst[i].key == secondbst[j].key) {
            intersectionvector.push_back(firstbst[i]);
            i++;
            j++;
        } else if (firstbst[i].key < secondbst[j].key) {
            i++;
        } else {
            j++;
        }
    }

    BST<T>* intersectionBST = new BST<T>();

    for (int k = 0; k<intersectionvector.size(); k++) {
        intersectionBST->insert(intersectionvector[k].key,intersectionvector[k].data);
    }

    return intersectionBST;
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }
