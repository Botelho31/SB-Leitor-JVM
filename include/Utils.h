#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef UTILS_H
    #define UTILS_H

    class Utils{
        public:
            static std::string getHexadecimalFromByte(char* array, int size);
            static std::string hexSubstrByByte(std::string hex,int start,int size);
            static u1* readUTF8 (FILE* fp, int size);
            static u1 readU1(FILE *fp);
            static u2 readU2(FILE *fp);
            static u4 readU4(FILE *fp);
        private:
    };

#endif