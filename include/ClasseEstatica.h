#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef CLASSE_ESTATICA_H
#define CLASSE_ESTATICA_H

    #include "Types.h"
    #include "Heap.h"
    #include "ClasseInstancia.h"

class JavaClass;
class ClasseInstancia;

class ClasseEstatica{
    public:
        ClasseEstatica(JavaClass *);
        typedElement getField(std::string);
        bool setField(std::string, typedElement);
        bool setFinals(std::string, typedElement);
        ClasseInstancia *getInstance();
        JavaClass *getDef();
    private:
        std::map<std::string, typedElement*> staticFields;
        JavaClass *classe;
};

#endif