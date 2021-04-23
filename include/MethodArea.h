#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef METHOD_AREA_H
#define METHOD_AREA_H

class MethodArea;

#include "Types.h"
#include "ConstantPool.h"
#include "Frame.h"
#include "ClasseEstatica.h"


class MethodArea{
    public:
        static std::string path;
        static ClasseEstatica *getClass(std::string);
        static bool addClass(std::string);
        static bool addClass(JavaClass*);
        static void setFrameStack(FrameStack*);
    private:
        static std::map<std::string, ClasseEstatica*> classes;
        static FrameStack *fs;
};

#endif