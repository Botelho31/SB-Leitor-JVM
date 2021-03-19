#include "Interfaces.h"


Interfaces::Interfaces(FILE* fp){
	interfaces_count = Utils::readU2(fp);
	interfaces = (unsigned short *) malloc(sizeof(int) * interfaces_count);

	for (int i = 0; i < interfaces_count; i++){
    	interfaces[i] = Utils::readU2(fp);
	
    }
}

Interfaces::~Interfaces(){

}

void Interfaces::printInterfaces (ConstantPool *cp)
{
	std::cout << "Inferface count -> " << interfaces_count << std::endl;
	for (int i = 0; i < interfaces_count; i++)
	{
		std::cout << "\tInterface " << index << ": " << cp->dereferenceIndex(interfaces[i]) << std::endl;
	}
}