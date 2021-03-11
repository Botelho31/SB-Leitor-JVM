#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef JAVA_H
    #define JAVA_H

    class JavaClass{
        public:
            JavaClass(std::string hexString);
            ~JavaClass();
            static bool validateMagic(std::string array);
            void printClass();
            std::string magic;
            std::string minor_version;
            std::string major_version;
            std::string constant_pool_count;
            std::string constant_pool;
            std::string access_flags;
            std::string this_class;
            std::string super_class;
            std::string interfaces_count;
            std::string interfaces;
            std::string fields_count;
            std::string fields;
            std::string methods_count;
            std::string methods;
            std::string attributes_count;
            std::string attributes;
        private:
    };

#endif