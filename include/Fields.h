#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef FIELDS_H
    #define FIELDS_H

    #include "Attributes.h"
    #include "Field.h"

    class Fields{
            public:
                Fields(FILE* fp,ConstantPool *cp);
                ~Fields();
                void printFields (ConstantPool *cp);
                std::vector<Field*> fields;
                u2 fields_count;
            private:
    };


#endif