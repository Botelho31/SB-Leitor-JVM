#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef PILHAOPERANDOS_H
#define PILHAOPERANDOS_H

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6

#include "Array.h"


class PilhaOperandos{
    public:
        PilhaOperandos(int);
        uint8_t top_type();
        element top_value();
        element pop();
        typedElement popTyped();
        std::string getString();
        void push(int);
        void push(int64_t);
        void push(float);
        void push(double);
        void push(bool);
        void push(int*);
        void push(typedElement);
        void push(element, uint8_t);
        int size();
        int getMaxSize();
        bool empty();

        void printALL();
        const int max;
    private:
        std::stack<uint32_t> elementos;
        std::stack<uint8_t> tipos;
        std::stack<uint8_t> tiposReais;
        bool typePushed;
        static const bool bits64 = (sizeof(int*) == 8);
        const int realMax;
};

#endif
