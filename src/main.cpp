#include "HuffmanTree.h"
#include <iostream>
#include <fstream>

int main(){
    // DATA
    std::ifstream inp("../data/INP.txt");
    std::ofstream out("../data/OUT.txt");

    std::string text = "";
    std::string line = "";
    while(getline(inp, line)){
        text += line + '\n';
    }

    // COMPRESSION
    Huffmantree DSA;

    DSA.built(text);
    std::map<char,std::string> result = DSA.getENcodes();

    for(char c : text){
        out << result[c];
    }
    inp.close();
    out.close();

    return 0;
}