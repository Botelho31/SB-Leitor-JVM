#include "../include/Field.h"

Field::Field(FILE *fp, ConstantPool *cp){
    accessFlags = Utils::readU2(fp) & 0X0df;
    name_index = Utils::readU2(fp);
    descriptor_index = Utils::readU2(fp);
    attributes = new Attributes(fp, cp);
}

Field::~Field(){
}

void Field::printField(ConstantPool *cp){
    std::cout << "\t\tNome: " << cp->dereferenceIndex(name_index).c_str() << std::endl;
    std::cout << "\t\tDescritor:  " << cp->dereferenceIndex(descriptor_index).c_str() << std::endl;
    attributes->printAttributes(cp,"\t\t\t");
}