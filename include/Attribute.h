#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef ATTRIBUTES_H
    #include "Attributes.h"
#endif

#ifndef ATTRIBUTE_H
    #define ATTRIBUTE_H

    class Attribute{
            public:
                Attribute(FILE *fp, ConstantPool *cp);
                ~Attribute();
                t_info *readAttributeInfo(FILE *fp, ConstantPool *cp);
                void printAttribute (ConstantPool *cp,std::string baseTab);
                t_exception_table *readExceptionHandler(FILE *fp);
                unsigned short name_index;
                unsigned int length;
                t_info *info;
            private:
    };

#endif