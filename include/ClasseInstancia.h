#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef CLASSE_DINAMICA_H
#define CLASSE_DINAMICA_H

    #include "Types.h"
    #include "ClasseEstatica.h"

class JavaClass;
class ClasseEstatica;

class ClasseInstancia {
	public:
		ClasseInstancia(ClasseEstatica*);

		ClasseEstatica *getStatic();

		typedElement getField(std::string);

		bool setField(std::string, typedElement);


		bool setFinals(std::string, typedElement);

		void show();
	private:
		std::map<std::string, typedElement*> localFields;
		ClasseEstatica *classe;
};

#endif