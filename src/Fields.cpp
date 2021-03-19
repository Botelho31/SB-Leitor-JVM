#include "Fields.h"

Fields::Fields(FILE* fp, ConstantPool* cp) {

   	fields_count = Utils::readU2(fp);
	for (int i = 0; i < fields_count; i++) {
		fields.push_back(new Field(fp,cp));
	}
}

Fields::~Fields(){
	
}

void Fields::printFields (ConstantPool *cp){
	std::cout << "Fields count -> " << fields_count << std::endl;
	for (int i = 0; i < fields_count; i++) {		
		std::cout << "\tField " << i << std::endl;
		fields[i]->printField(cp);
	}
}