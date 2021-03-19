#include "../include/Attributes.h"


Attributes::Attributes(FILE* fp, ConstantPool *cp){
	attributes_count = Utils::readU2(fp);

  for(int var = 0; var < attributes_count; var++ ){
    attributes.push_back(new Attribute(fp,cp));
    
  }
}

Attributes::~Attributes(){

}

void Attributes::printAttributes(ConstantPool* cp,std::string baseTab){ 

  std::cout << baseTab << "Attributes count -> " << attributes_count << std::endl;
  
  int var;
  for(var = 0; var < attributes_count; var++ ) {

    std::cout << baseTab << "\tAttribute " << var << ": " << std::endl;
    attributes[var]->printAttribute(cp,baseTab);
  
  }

}