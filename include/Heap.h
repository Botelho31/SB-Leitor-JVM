#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef HEAP_H
#define HEAP_H

#include "ClasseInstancia.h"

class Heap{
    public:
        static void addObject(ClasseInstancia *);
    private:
        static std::vector<ClasseInstancia *> objetos;
};

#endif
