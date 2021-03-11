#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef TYPES_H
    #define TYPES_H
    
    typedef uint8_t  u1;
    typedef uint16_t u2;
    typedef uint32_t u4;
    typedef uint64_t u8;

    typedef union {
        u1 U1;
        u2 U2;
        u4 U4;
        u1 *array;
    } ClassLoaderType;

#endif