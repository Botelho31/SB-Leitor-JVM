#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef FIELD_H
    #define FIELD_H

    #include "Attributes.h"

    class Field{
            public:
                Field(FILE* fp,ConstantPool *cp);
                ~Field();
                void printField(ConstantPool *cp);
                unsigned char accessFlags;
                unsigned char name_index;
                unsigned char descriptor_index;
                Attributes *attributes;
            private:
    };


#endif