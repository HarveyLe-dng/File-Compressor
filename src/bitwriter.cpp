#include "Bitwriter.h"
#include <iostream>
#include <fstream>

Bitwriter::Bitwriter(){
    buffer = cnt = 0;
}

void Bitwriter::write(unsigned int code, int len, std::ofstream& out) {
    for (int i = len-1; i >= 0; i--){
        cnt ++ ;
        buffer <<= 1;
        buffer |= ((code >> i) & 1);


        if(cnt == 8){
            out.put(buffer);
            cnt = buffer = 0;
        }
    }

}

void Bitwriter::flush(std::ofstream &out){
    if(cnt != 0){
        buffer <<= (8-cnt);
        out.put(buffer);
        buffer = cnt = 0;
    }
}