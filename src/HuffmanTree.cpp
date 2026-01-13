#include "Huffmantree.h"
#include <iostream>

Node::Node(char ch, int freq){ // constructor
    c = ch;
    fre = freq;
    l = r = nullptr;
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
    Huffmantree::deletetree(root);
}
void Huffmantree::deletetree(Node* cur){
    if(cur == nullptr) return;
    deletetree(cur->l);
    deletetree(cur->r);
    delete cur;
}

void Huffmantree::built(const std::string &text){
    std::map<char,int> cnt;
    std::priority_queue<Node*, std::vector<Node*>, cmp> pq;

    for(char c : text){
        cnt[c] ++;
    }
    for(auto x : cnt){
        Node* tmp = new Node(x.first, x.second);
        pq.push(tmp);
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
    Node* root = pq.top();
    generate(root, "");
}

void Huffmantree::generate(Node* cur, std::string s){
    if(cur == nullptr) return;
    if(!cur->isInterval){
        codes[cur->c] = s; // stored codes
    }
    generate(cur->l, s + '0');
    generate(cur->r, s + '1');
    
    return;
}

std::map<char, std::string> Huffmantree::getENcodes(){
    return codes;
}
