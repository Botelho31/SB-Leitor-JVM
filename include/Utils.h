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
            static std::string showUTF8 (unsigned char * s, int size);
            static u1 readU1(FILE *fp);
            static u2 readU2(FILE *fp);
            static u4 readU4(FILE *fp);
            static float u4ToFloat (ClassLoaderType in);
            static long u4ToLong (ClassLoaderType high, ClassLoaderType low);
            static double u4ToDouble (ClassLoaderType high, ClassLoaderType low);
            static uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index);
            static std::string getMnemonic(int opcode);
            static void getOpcodeParams(unsigned char* code, int* index);
        private:
    };

#endif