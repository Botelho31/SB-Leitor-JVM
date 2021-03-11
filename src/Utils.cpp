#include "../include/Utils.h"

std::string Utils::getHexadecimalFromByte(char* array, int size){
    std::string hexstring;
    for (int index = 0; index < size; index++){
        char buffer[3];
        sprintf(buffer, "%X", (unsigned char)array[index]);
        hexstring += buffer;
    }
    return hexstring;
}

std::string Utils::hexSubstrByByte(std::string hex,int start,int size){
    std::string substring = hex.substr(start*2,size*2);
    return substring;
}

int16_t Utils::getShortFromHex(std::string hex){
    int16_t x;   
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> x;
    return x;
}