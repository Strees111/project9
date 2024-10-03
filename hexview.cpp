#include <iostream>
#include <cstring>
#include <fstream>
const char y[] = "0123456789ABCDEF";
void symbol(unsigned char ch){
    if (static_cast<int>(ch) < 32){
        std::cout << '.';
        return;
    }
    std::cout << ch;
}
void number(int j){
    char a[10] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };
    int index = 9;
    while (j > 0) {
        a[index--] = y[j % 16];
        j /= 16;
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << a[i];
    }
}

void hexview(int n, int s, std::ifstream& infin) {
    int k = 0;
    char buffer[16];
    infin.seekg(s);
    while (n != 0 && infin.read(buffer, (n > 0 && n < 16)?n:16)) {
        size_t v = infin.gcount();
        number(k * 16);
        std::cout << ": ";
        for (size_t i = 0; i < 8; ++i) {
            if (i < v){
                std::cout << y[(buffer[i] >> 4) & 0xF];
                std::cout << y[buffer[i] & 0xF];
                std::cout << ' ';
            }
            else {
                std::cout << "   ";
            }
        }
        std::cout << "| ";
        for (size_t i = 8; i < 16; ++i) {
            if (i < v){
                std::cout << y[(buffer[i] >> 4) & 0xF];
                std::cout << y[buffer[i] & 0xF];
                std::cout << ' ';
            }
            else {
                std::cout << "   ";
            }
        }
        std::cout << ' ';
        for (size_t i = 0; i < v; ++i) {
            symbol(buffer[i]);
        }
        ++k;
        if (n > 0){
            n -= static_cast<int>(v);
        }
        if (n != 0){
            std::cout << std::endl;
        }
    }
    if(n != 0) {
        size_t v = infin.gcount();
        number(k * 16);
        std::cout << ": ";
        for (size_t i = 0; i < 8; ++i) {
            if (i < v) {
                std::cout << y[(buffer[i] >> 4) & 0xF];
                std::cout << y[buffer[i] & 0xF];
                std::cout << ' ';
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "| ";
        for (size_t i = 8; i < 16; ++i) {
            if (i < v) {
                std::cout << y[(buffer[i] >> 4) & 0xF];
                std::cout << y[buffer[i] & 0xF];
                std::cout << ' ';
            } else {
                std::cout << "   ";
            }
        }
        std::cout << ' ';
        for (size_t i = 0; i < v; ++i) {
            symbol(buffer[i]);
        }
    }
}
int main(int argc,char *argv[]) {
    int n = -1;
    int s = 0;
    std::ifstream infin(argv[argc-1]);
    if(!infin.is_open()){
        std::cout << "Can not open to file " << argv[argc-1] << std::endl;
        infin.close();
        return 1;
    }
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i],"-n") == 0){
            if (i + 1 < argc) {
                n = atoi(argv[i + 1]);
            }
            else{
                return 2;
            }
        }
        else if(strcmp(argv[i],"-s") == 0){
            if (i + 1 < argc) {
                s = atoi(argv[i + 1]);
            }
            else{
                return 3;
            }
        }
    }
    hexview(n,s,infin);
    infin.close();
    return 0;
}
