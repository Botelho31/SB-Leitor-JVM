#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef JAVA_H
    #define JAVA_H

    #include "ConstantPool.h"
    #include "Interfaces.h"

    class JavaClass{
        public:
            JavaClass(FILE * classFile);
            ~JavaClass();
            static bool validateMagic(u4 magic);
            void printClass();


            u4 magic;
            u2 minor_version, major_version, constant_pool_count;
            cp_info* constant_pool;
            u2 access_flags,this_class,super_class,interfaces_count;
            unsigned short * interfaces;
            u2 fields_count;
            // u2 fields;
            u2 methods_count;
            // u2 methods;
            u2 attributes_count;
            // u2 attributes;
        private:
    };

#endif