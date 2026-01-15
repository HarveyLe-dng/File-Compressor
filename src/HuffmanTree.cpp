#include "HuffmanTree.h"
#include <iostream>

Node::Node(char ch, int freq){ // constructor
    c = ch;
    fre = freq;
    l = r = nullptr;
    isInterval = 0;
}
struct cmp{
    bool operator()(Node* a, Node* b){
        return a->fre > b -> fre;
    }
};

Huffmantree::Huffmantree(){
    root = nullptr;
}
Huffmantree::~Huffmantree(){
    deletetree(root);
}
void Huffmantree::deletetree(Node* cur){
    if(cur == nullptr) return;
    deletetree(cur->l);
    deletetree(cur->r);
    delete cur;
}
// built tree from text
void Huffmantree::built_fromtext(const std::string &text){
    freq_map.clear();
    for(char c : text){
        freq_map[c] ++;
    }
    built_frommap(freq_map);
}
//built tree from map
void Huffmantree::built_frommap(std::map<char,int> mp){
    std::priority_queue<Node*, std::vector<Node*>, cmp> pq;
    this->freq_map = mp;// truyen mot map moi vao thi phai luu  lai tren object Huffman hien tai

    for(auto x : freq_map){
        Node* tmp = new Node(x.first, x.second);
        pq.push(tmp);
    }

    if(pq.size() == 1){
        pq.top()->isInterval = 1;
        pq.top()->l = new Node(pq.top()->c, pq.top()->fre);
        pq.top()->r = new Node('\0', 0);
    }
    while(pq.size() != 1){
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        Node* tmp = new Node('\0', a->fre + b->fre); // Interval Node

        tmp->isInterval = 1;
        tmp->l = a;
        tmp->r = b;

        pq.push(tmp);
    }
    root = pq.top();
    generate(root, 0, 0);
}

void Huffmantree::generate(Node* cur, unsigned int cur_code, int cur_len){
    if(cur == nullptr) return;
    if (!cur->isInterval) {
        unsigned char id = (unsigned char)cur->c;
        codes[id].code = cur_code;
        codes[id].len = cur_len;
    }
    generate(cur->l, (cur_code << 1), cur_len + 1);
    generate(cur->r, (cur_code << 1) | 1, cur_len + 1);
    
    return;
}

Node* Huffmantree::getroot(){
    return root;
}
Huffmancode* Huffmantree::getcodes() {
    return codes;
}

