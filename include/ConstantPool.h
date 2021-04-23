#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef CONSTANTPOOL_H
    #define CONSTANTPOOL_H

    #define UTF8 1
    #define INTEGER 3
    #define FLOAT 4
    #define LONG 5
    #define DOUBLE 6
    #define CLASS 7
    #define STRING 8
    #define FIELD_REF 9
    #define METHOD_REF 10
    #define INTERFACE_REF 11
    #define NAME_AND_TYPE 12
    #define INVALID 99 

    typedef struct {
        u1 tag;
        ClassLoaderType *info;
    } cp_info;

    const std::string typeNames[] = {"UTF-8", "-", "Integer", "Float", "Long", "Double", "Class", "String", "Field", "Method", "Interface", "Name and Type"};
    class ConstantPool{
            public:
                ConstantPool(FILE* fp);
                ~ConstantPool();
                std::string dereferenceIndex (u2 index);
                void printConstantPool ();
                cp_info *constant_pool;
                u2 constant_pool_count;
            private:
    };

#endif