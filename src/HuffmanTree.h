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

struct Huffmancode {
    unsigned int code;
    int len;
};

class Huffmantree{
    private:
        Node* root;
        Huffmancode codes[256];
        void generate(Node* cur, unsigned int cur_code, int cur_len);// sinh code 01
        void deletetree(Node* root); // freetree

    public:
        std::map<char,int> freq_map;
        Huffmantree();
        ~Huffmantree();

        void built_fromtext(const std::string& text);
        void built_frommap (std::map<char,int> mp);

        Huffmancode* getcodes();
        Node* getroot();
};

#endif
