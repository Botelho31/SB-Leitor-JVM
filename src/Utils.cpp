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

u1 * Utils::readUTF8 (FILE* fp, int size) {
	std::vector<unsigned char> *ret = new std::vector<unsigned char>(size);

	for (int i = 0; i < size; i++) {
		ret->at(i) = readU1(fp);
	}

	return (u1*)ret;
} 

u2 Utils::readU2 (FILE *fp) {
	unsigned short ret = 0;
	unsigned char aux;

	fread(&ret, 1, 1, fp);
	fread(&aux, 1, 1, fp);

	ret <<= 8;
	ret |= aux;

	return ret;
}

u1 Utils::readU1 (FILE *fp){
	unsigned char ret;

	fread(&ret, 1, 1, fp);

	return ret;
}

u4 Utils::readU4 (FILE *fp){
	unsigned int ret = 0;
	unsigned char aux;

	for (int i=0; i<4; i++) {
		ret <<= 8;
		fread(&aux, 1, 1, fp);
		ret |= aux;
	}

	return ret;
}