#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef INTERFACES_H
    #define INTERFACES_H

    class Interfaces{
            public:
                Interfaces(FILE* fp);
                ~Interfaces();
                void printInterfaces (ConstantPool *cp);
                unsigned short *interfaces;
                u2 interfaces_count;
            private:
    };

#endif