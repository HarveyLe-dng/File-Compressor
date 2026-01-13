#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <iostream>
#include <map>
#include <queue>

class Node{
    public:
        char c;
        int fre;
        int isInterval;
        Node *r, *l;

        Node(char ch, int freq);
};

class Huffmantree{
    private:
        Node* root;
        std::map<char, std::string> codes;
        void generate(Node* cur, std::string s); // sinh code 01
        void deletetree(Node* root); // freetree

    public:
        Huffmantree();
        ~Huffmantree();
        void built(const std::string& text);
        std::map<char, std::string> getENcodes();
        
};

#endif
