#include <iostream>
#include <bits/stdc++.h>

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

    void validWords()
    {
        stack<Node*> trieStack;
        trieStack.push(this);
        while(!trieStack.empty())
        {
            Node* n = trieStack.top();
            trieStack.pop();
            for(int i = 25; i >= 0; i--)
            {
                if(n->children[i] != NULL) trieStack.push(n->children[i]);
            }
            if(n->isEndOfWord)cout<<n->currentLetters;
        }
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
        Node* current = root;
        for (char c : word) {
            int index = c - 'a';
            //make sure to get rid of case sensitivity
            if(index < 0){
                index += 32;
            }
            if (!current->children[index]) {
                current->children[index] = new Node();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    void findAllWords(string str)
    {
        Node n = findNode(str);
        if(n == NULL)return;
        n.validWords();
    }
    
    Node findNode(string str)
    {
        Node* n = root;
        for(int i = 0; i < str.length(); i++)
        {
            n = n->children[str[i] - 'a'];
            if(n == nullptr) return NULL;
        }
        return *n;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.txt", "r", stdin);
    unsigned short int n = 9939;
    Trie trie;
    string word;
    for(unsigned short int i = 0; i < n; i++){
        cin>>word;
        trie.insert(word);
    }
    //TODO run search functionality here

    cout << "Print Tester" << endl;
    return 0;
}

