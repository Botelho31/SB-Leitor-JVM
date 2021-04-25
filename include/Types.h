#ifndef JAVA_H
    #include "JavaClass.h"
#endif


#ifndef TYPES_H
    #define TYPES_H


    #define Float_NaN 0x7f800001
    #define Float_PlusInfinity 0x7f800000
    #define Float_MinusInfinity 0xff800000
    #define Double_NaN 0x7ff0000000000001L 
    #define Double_PlusInfinity 0x7ff0000000000000L
    #define Double_MinusInfinity 0xfff0000000000000L

    #define RT_BYTE 1
    #define RT_BOOL 2
    #define RT_CHAR 3
    #define RT_SHORT 4
    #define RT_INT 5
    #define RT_FLOAT 6
    #define RT_DOUBLE 7
    #define RT_REFERENCE 8
    #define RT_LONG 9
    
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

    class Array;
    typedef union element_u{
        double d;
        float f;
        uint32_t i;
        int32_t is;
        uint64_t l;
        int64_t ls;
        uint16_t s;
        int16_t ss;
        uint8_t b;
        int8_t bs;
        int* pi;
    } element;

    typedef struct typedElement_s {
        element value;
        uint8_t type;
        uint8_t realType;
    } typedElement;
#endif