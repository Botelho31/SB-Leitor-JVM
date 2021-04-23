#include "../include/ClasseInstancia.h"


ClasseInstancia::ClasseInstancia(ClasseEstatica* c){
	this->classe = c;

	int count = classe->getDef()->getFieldsCount();
	Fields *fields = classe->getDef()->getFields();
	for (int i = 0; i < count; i++){
		if ((fields->fields[i]->accessFlags & 0x08) == 0){
			typedElement *auxValue = (typedElement *) malloc(sizeof(typedElement));
			auxValue->value.l = 0;
			std::string desc = classe->getDef()->getCP()->dereferenceIndex(fields->fields[i]->descriptor_index);

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
			std::string auxName = classe->getDef()->getCP()->dereferenceIndex(fields->fields[i]->name_index);
			localFields.insert(std::pair<std::string, typedElement*>(auxName, auxValue));
		}
	}	
}


typedElement ClasseInstancia::getField(std::string s){
	typedElement ret;
	ret.type = TYPE_NOT_SET;

	for (std::map<std::string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++){
	   if (i->first == s)
	   {
	   		return *(i->second);
	   }
	}

	return ret;
}

ClasseEstatica *ClasseInstancia::getStatic(){
	return classe;
}

bool ClasseInstancia::setField(std::string s, typedElement e){
	for (std::map<std::string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++){
	   	if (i->first == s){
	   		if (i->second->type == e.type){
		   		*(i->second) = e;
		   		return true;
	   		}
			else
			{
	   			break;
	   		}
	   	}
	}

	return false;
}


bool ClasseInstancia::setFinals(std::string s, typedElement e)
{
	for (std::map<std::string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++){
	   	if (i->first == s){
	   		if (i->second->type == e.type){
		   		*(i->second) = e;
		   		return true;
	   		}
			else
			{
	   			break;
	   		}
	   	}
	}

	return false;
}

void ClasseInstancia::show(){
	for (std::map<std::string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++){
	   std::cout << i->first << std::endl;
	}
}
