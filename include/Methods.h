#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef METHODS_H
    #define METHODS_H

    #include "Attributes.h"
    #include "Method.h"

    class Methods{
            public:
                Methods(FILE* fp, ConstantPool *cp);
                ~Methods();
                std::string get_Method_Flags (uint16_t flags);
                void printMethods(ConstantPool *cp);
                std::vector<Method*> methods;
                u2 methods_count;
            private:
    };


#endif 