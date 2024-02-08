#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie();
    ~Trie();
    
    Trie& insert(const string& username);
    void remove(std::string username);
    T* search(std::string username);
    void findStartingWith(std::string prefix, std::vector<T*> &results);
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results);
    void print();

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    void deleteTrieNode(TrieNode*& node);
    void wildcardSearchHelper(TrieNode* node, const std::string &wildcardKey, std::vector<T*> &results);
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    /* IMPLEMENT THIS */
    if(root != NULL) deleteTrieNode(root);
    
}

template <class T>
void Trie<T>::deleteTrieNode(TrieNode*& node){
    
    if (node == NULL) return;
    
    for(int i = 0 ; i<128 ; i++){
        if(node->children[i] != NULL) deleteTrieNode(node->children[i]);
    }
    if (node->data != NULL) delete node->data;
    delete node;
}


template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    /* IMPLEMENT THIS */
    TrieNode* current = this->root;
    for (int i=0 ; i<key.size() ; i++){
        int index = key[i];
        if (current->children[index] == NULL){
            current->children[index] = new TrieNode(char(index));
        }
        current = current->children[index];
    }
    current->isEndOfKey = true;
    if(current->isEndOfKey && current->data==NULL) {
        current->data = new T(key);
    }
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    /* IMPLEMENT THIS */
    TrieNode* current = this->root;
    for (int j=0 ; j<username.size() ; j++){
        int index = username[j];
        if(current->children[index] != NULL) current = current->children[index];
        else return NULL;
    }
    if (current->isEndOfKey && current->data != NULL) return current->data;
    else return NULL;
}

template <class T>
void Trie<T>::remove(std::string username) {
    /* IMPLEMENT THIS */
    
    TrieNode* current = root;
    for (int k = 0 ; k<username.size() ; k++){
        char c = username[k];
        if (current->children[c] != NULL) current = current->children[c];
        else return;
    }
    if(current->isEndOfKey) current->isEndOfKey = false;
}

template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results) {
/* IMPLEMENT THIS */
    std::string startwithprefix = prefix + "*";
    wildcardSearch(startwithprefix, results);
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
/* IMPLEMENT THIS */
    wildcardSearchHelper(root, wildcardKey, results);
}

template <class T>
void Trie<T>::wildcardSearchHelper(TrieNode* node, const std::string &wildcardKey, std::vector<T*> &results){
    if (node == NULL) return;
    
    if (wildcardKey.length()==0){
        if(node->isEndOfKey && node->data!=NULL){
            bool varmi = false;
            for (int t = 0 ; t<results.size() ; t++){
                if(results[t] == node->data){
                    varmi = true;
                }
            }
            if(varmi==false){
                results.push_back(node->data);
            }
            return;
        }
    }

    char current_char = wildcardKey[0];

    
    if (current_char == '*'){
        if (wildcardKey[1] == '*') wildcardSearchHelper(node,wildcardKey.substr(1),results);
        else{
            wildcardSearchHelper(node,wildcardKey.substr(1),results);
            for(int i=0 ; i<128 ; i++){
                if(node->children[i] != NULL ) wildcardSearchHelper(node->children[i], wildcardKey,results);
            }
        }

    }
    
    else if (current_char == '?'){
        for(int k=0 ; k<128 ; k++){
            if (node->children[k] != NULL) wildcardSearchHelper(node->children[k],wildcardKey.substr(1),results);
        }
    }
    else{
        int index = current_char;
        if (node->children[index] != NULL) wildcardSearchHelper(node->children[index],wildcardKey.substr(1),results);
    }

}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}
