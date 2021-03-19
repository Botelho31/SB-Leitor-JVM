#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef ATTRIBUTES_H
    #define ATTRIBUTES_H

    class Attributes;
    struct attribute_info;

    typedef struct
    {
        unsigned short constantvalue_index;
    } constantvalue_attribute;

    typedef struct
    {
        unsigned short start_pc;
        unsigned short end_pc;
        unsigned short handler_pc;
        unsigned short catch_type;
    } t_exception_table;

    typedef struct
    {
        unsigned short max_stack;
        unsigned short max_locals;
        unsigned int code_length;
        unsigned char *code;
        unsigned short exception_table_length;
        t_exception_table **exception_table;
        Attributes* attributes;
    } code_attribute;

    typedef struct
    {
        unsigned short number_of_exceptions;
        unsigned short *exception_index_table;
    } exception_attribute;

    typedef union
    {
        constantvalue_attribute constantvalue;
        code_attribute code;
        exception_attribute exception;
    } t_info;

    struct attribute_info
    {
        unsigned short name_index;
        unsigned int length;

        t_info *info;
    };

    #include "Attribute.h"
    
    class Attributes{
            public:
                Attributes(FILE *fp, ConstantPool *cp);
                ~Attributes();
                static t_exception_table *readExceptionHandler(FILE *fp);
                void printAttributes(ConstantPool* cp,std::string baseTab = "");

                std::vector<Attribute*> attributes;
                u2 attributes_count;
            private:
    };

#endif