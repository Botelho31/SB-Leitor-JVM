#include "../include/Methods.h"


Methods::Methods(FILE* fp, ConstantPool *cp) {

	methods_count = Utils::readU2(fp);
	for (int i = 0; i < methods_count; i++){
		methods.push_back(new Method(fp,cp));
	}
}

Methods::~Methods(){

}

void Methods::printMethods(ConstantPool *cp) {
    std::cout << "Methods count -> " << methods_count << std::endl;
	for (int i = 0; i < methods_count; i++){
		std::cout << "Method " << index << ":" << std::endl;
		methods[i]->printMethod(cp);
	}
}
