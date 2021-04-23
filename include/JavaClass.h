#ifndef JAVA_H
    #define JAVA_H

    #define MISSING_ARGUMENT 1
    #define CANT_OPEN 2
    #define INVALID_FILE 3
    #define UNKNOWN_TYPE 4
    #define INVALID_NAME 5
    #define INVALID_EXTENSION 6
    #define MISSING_MAIN 7

    #define ENDLINE std::cout << std::endl;
    #include <iostream>
    #include <utility>
    #include <fstream>
    #include <vector>
    #include <memory>
    #include <cstdlib>
    #include <sstream>
    #include <ctime>
    #include <math.h>
    #include <map>
    #include <stack>
    
    #include "Types.h"
    #include "Utils.h"

    #include "ConstantPool.h"
    #include "Interfaces.h"
    #include "Attributes.h"
    #include "Fields.h"
    #include "Methods.h"
    #include "ClasseEstatica.h"
    #include "MethodArea.h"

    class JavaClass{
        public:
            JavaClass(char *in);
	        JavaClass(std::string in);
            ~JavaClass();
            int run();
	        int load();
            static bool validateMagic(u4 magic);
            void printClass();
            bool validExtension ();
            bool hasMain();
            bool findMain();
            bool findClinit();
            std::string getError(int);
            Method* getMain();
            bool hasClinit();
            Method* getClinit();
            bool checkThisClass ();
            int getStatus();
            ConstantPool* getCP() const;
            u2 getLengthCP();
            char *getPath();
            Methods* getMethods();
            u2 getMethodsCount();
            u2 getThis_class();
            u2 getSuper_class();
            u2 getFieldsCount();
            Fields* getFields();
            Field* getField(std::string field_name);
            Method* getMethod(std::string name, std::string descriptor);
            JavaClass* getClassThatHasSearchedMethod(std::string name, std::string descriptor);

            int status, mainMethod, clinit;
            bool foundMain, foundClinit;
            char *fileName;
            FILE *classFile;
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