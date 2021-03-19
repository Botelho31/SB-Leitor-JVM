#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef JAVA_H
    #define JAVA_H

    #include "ConstantPool.h"
    #include "Interfaces.h"
    #include "Attributes.h"
    #include "Fields.h"
    #include "Methods.h"

    class JavaClass{
        public:
            JavaClass(FILE * classFile);
            ~JavaClass();
            static bool validateMagic(u4 magic);
            void printClass();

            u4 magic;
            u2 minor_version, major_version;
            ConstantPool *constant_pool;
            u2 access_flags,this_class,super_class;
            Interfaces *interfaces;
            Fields *fields;
            Methods *methods;
            Attributes *attributes;
        private:
    };

#endif