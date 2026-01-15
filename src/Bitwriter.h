#ifndef BITWRITER_H
#define BITWRITER_H
#include <iostream>
#include <fstream>

class Bitwriter{
    private:
        unsigned char  buffer; 
        int cnt;
    public:
        void write(unsigned int code, int len, std::ofstream& out);;
        void flush(std::ofstream& out);
        Bitwriter();

        // ~Bitwriter();
};

#endif