#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef METHOD_H
    #define METHOD_H

    #include "Attributes.h"

    class Method{
            public:
                Method(FILE* fp,ConstantPool *cp);
                ~Method();
                std::string getMethodFlags (uint16_t flags);
                void printMethod(ConstantPool *cp);
                uint16_t access_flags;
                uint16_t name_index;
                uint16_t descriptor_index;
                Attributes *attributes;
            private:
    };


#endif 