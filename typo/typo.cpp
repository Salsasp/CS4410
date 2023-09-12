#include <iostream>
using namespace std;

class Node {
public:
    Node* children[26];
    bool isEndOfWord;
    string currentLetters;
    Node() : isEndOfWord(false){
        for(unsigned short int i = 0; i < 26; i++)
            children[i] = nullptr;
    }   
};

class Trie {
private:
    Node* root;

public:
    Trie(){
        root = new Node();
    }

    //TODO Test this function to see if you can get the right input
    void insert(string word) {
        string currLetters = "";
        bool isNew;
        Node* current = root;
        for (char c : word) {
            isNew = false;
            int index = c - 'a';
            //make sure to get rid of case sensitivity
            if(index < 0){
                index += 32;
            }
            currLetters += c;
            if (!current->children[index]) {
                current->children[index] = new Node();
                isNew = true;
            }
            if(isNew)current->children[index]->currentLetters = currLetters;
            else current->currentLetters = currLetters;
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }
    
    Node* findNode(string str)
    {
        Node* n = root;
        int index;
        for(int i = 0; i < str.length(); i++)
        {
            index = str[i] - 'a';
            if(index < 0){
                index += 32;
            }
            n = n->children[index];
            if(n == nullptr) return nullptr;
        }
        return n;
    }

    void display(Node* root, int num)
    {
        num += 1;
        if(root == nullptr)return;
        for(int i = 0; i < 26; i++)
        {
            cout << root->children[i]->currentLetters << endl;
        }
        display(root->children[num], num);
    }
};

int main()
{
    freopen("test.txt", "r", stdin); //remove this before kattis submission
    unsigned short int n = 9939;
    Trie trie;
    string word;
    for(unsigned short int i = 0; i < n; i++){
        cin>>word;
        trie.insert(word);
    }
    trie.display(trie.root);
}