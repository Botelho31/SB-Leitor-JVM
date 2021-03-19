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
                attribute_info attribute;
            private:
    };

#endif