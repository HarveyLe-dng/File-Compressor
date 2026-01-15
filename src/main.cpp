#include "HuffmanTree.h"
#include "Bitwriter.h"
#include <iostream>
#include <fstream>

void compress(std::string inf, std::string outf){
    std::ifstream inp(inf, std::ios::binary); // input
    std::ofstream out(outf, std::ios::binary); // output

    std::string text = "";
    char c;
    while(inp.get(c)){
        text += c; 
    }

    //convert to bits
    Huffmantree DSA;

    DSA.built_fromtext(text);
    Huffmancode* encode = DSA.getcodes();// du lieu ma hoa

    //write freq_map in header
    //1. write map location of map size 
    int mpsize = DSA.freq_map.size();
    out.write(reinterpret_cast<char*>(&mpsize), sizeof(mpsize));

    //2. write each ch and freq
    for(auto const&[key,val] : DSA.freq_map){
        char c = key;
        int cnt = val;
        out.put(c); // ghi ky tu
        out.write(reinterpret_cast<char*>(&cnt), sizeof(cnt));
    }

    //write in zip file
    Bitwriter writer;
    for(char c: text){
        unsigned char u_c = (unsigned char)c;
        Huffmancode h_c = encode[u_c];
        writer.write(h_c.code, h_c.len, out);
    }
    writer.flush(out);

    inp.close();
    out.close();

}

void decompress(std::string inf, std::string outf){
    std::ifstream inp(inf,std::ios::binary);
    std::ofstream out(outf);
    
    //lay map size
    int mpsize;
    inp.read(reinterpret_cast<char*>(&mpsize), sizeof(mpsize));

    std::map<char,int> restored_mp;
    long long total = 0; // tong so ky tu

    for(int i = 1; i<= mpsize; i++){
        char c;
        inp.get(c);
        int cnt;
        inp.read(reinterpret_cast<char*>(&cnt), sizeof(cnt));

        restored_mp[c] = cnt;
        total += cnt;
    }

    // restored lai cay
    Huffmantree DSA;
    DSA.built_frommap(restored_mp);
    Node* root = DSA.getroot();

    Node *cur = root;
    char byte;
    while(inp.get(byte) && total){
        unsigned char u_byte = static_cast<unsigned char> (byte); // for safe
        for(int i = 7; i>= 0; i--){

            if(((u_byte >> i) & 1) == 0) cur = cur->l;
            else cur = cur->r;

            if(!cur->isInterval){ // ur if normal leaf
                out.put(cur->c);
                total --;
                cur = root;
            }
            if(total == 0) break;
        }
    }
    inp.close();
    out.close();
}
int main(){

    std::string inputfile = "../data/INP.txt";
    std::string compressedfile = "../data/OUT.txt";
    std::string restoredfile = "../data/RES.txt";

    // std::string ty; std::cin >> ty;

    // if(ty == "-c")  compress(inputfile, compressedfile);

    // if(ty == "-d")  decompress (compressedfile, restoredfile);

    compress(inputfile, compressedfile);
    decompress(compressedfile, restoredfile);
    
    return 0;
}