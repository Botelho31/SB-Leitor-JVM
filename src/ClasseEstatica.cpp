#include "../include/ClasseEstatica.h"

ClasseEstatica::ClasseEstatica(JavaClass *classeLida){
	classe = classeLida; ///class file lido
	int count = classeLida->getFieldsCount(); ///get numero de fields
	Fields *fields = classeLida->getFields();

	for (int i = 0; i < count; i++){
		if ((fields->fields[i]->accessFlags & 0x08) && (fields->fields[i]->accessFlags & 0x010) == 0){
			typedElement *auxValue = (typedElement *) malloc(sizeof(typedElement));
			auxValue->value.l = 0;
			std::string desc = classeLida->getCP()->dereferenceIndex(fields->fields[i]->descriptor_index);

			switch (desc[0]){
				case 'B':
					auxValue->type = TYPE_BOOL;
					break;
				case 'C':
					auxValue->type = TYPE_INT;
					break;
				case 'D':
					auxValue->type = TYPE_DOUBLE;
					break;
				case 'F':
					auxValue->type = TYPE_FLOAT;
					break;
				case 'I':
					auxValue->type = TYPE_INT;
					break;
				case 'J':
					auxValue->type = TYPE_LONG;
					break;
				case 'L':
					auxValue->type = TYPE_REFERENCE;
					break;
				case 'S':
					auxValue->type = TYPE_INT;
					break;
				case 'Z':
					auxValue->type = TYPE_BOOL;
					break;
				case '[':
					auxValue->type = TYPE_REFERENCE;
					break;
			}

			std::string auxName = classeLida->getCP()->dereferenceIndex(fields->fields[i]->name_index);
			staticFields.insert(std::pair<std::string, typedElement*>(auxName, auxValue));
		}
	}
}

ClasseInstancia *ClasseEstatica::getInstance(){
	ClasseInstancia *objeto_classe = new ClasseInstancia(this);
	Heap::addObject(objeto_classe);
	
	return objeto_classe;
}


typedElement ClasseEstatica::getField(std::string s){
	typedElement field_encontrado;
	field_encontrado.type = TYPE_NOT_SET;

	for (std::map<std::string, typedElement*>::const_iterator i = staticFields.begin(); i != staticFields.end(); i++){
	   if (i->first == s){
	   		return *(i->second);
	   }
	}

	return field_encontrado;
}

bool ClasseEstatica::setField(std::string s, typedElement e){
	for (std::map<std::string, typedElement*>::const_iterator i = staticFields.begin(); i != staticFields.end(); i++){
	   	if (i->first == s){
	   		if (i->second->type == e.type){
		   		*(i->second) = e;
		   		return true;
	   		}
			else{
	   			break;
	   		}
	   	}
	}

	return false;
}

bool ClasseEstatica::setFinals(std::string s, typedElement e)
{
	for (std::map<std::string, typedElement*>::const_iterator i = staticFields.begin(); i != staticFields.end(); i++){
	   	if (i->first == s){

	   		if (i->second->type == e.type){
		   		*(i->second) = e;
		   		return true;
	   		}
			else{
	   			break;
	   		}
	   	}
	}

	return false;
}

JavaClass *ClasseEstatica::getDef(){
	return classe;
}