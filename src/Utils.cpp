#include "../include/Utils.h"

std::string Utils::convertHexToString(std::string hexadecimalString){
    int len = hexadecimalString.length();
    std::string newString;
    for(int i=0; i< len; i+=2)
    {
        std::string byte = hexadecimalString.substr(i,2);
        char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
        newString.push_back(chr);
    }
    return newString;
}