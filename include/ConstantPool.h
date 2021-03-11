#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef CONSTANTPOOL_H
    #define CONSTANTPOOL_H

    #define INVALID 99 
    #define UTF8 1
    #define INTEGER 3
    #define FLOAT 4
    #define LONG 5
    #define DOUBLE 6
    #define CLASS 7
    #define STRING 8
    #define FIELD_REF 9
    #define METHOD_REF 10
    #define INTERFACE_REF 11
    #define NAME_AND_TYPE 12

    typedef struct {
        u1 tag;
        ClassLoaderType *info;
    } cp_info;

    cp_info* loadConstantPool(int lengthCP, FILE* fp);

#endif