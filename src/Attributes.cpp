#include "../include/Attributes.h"


Attributes::Attributes(FILE* fp, ConstantPool *cp)
{
	attributes_count = Utils::readU2(fp);

  for(int var = 0; var < attributes_count; var++ )
  {
    attributes.push_back(new Attribute(fp,cp));
  }
}

Attributes::~Attributes(){

}

t_exception_table* Attributes::readExceptionHandler(FILE* fp)
{
  t_exception_table* return_value = (t_exception_table*) malloc(sizeof(t_exception_table));

  return_value->start_pc = Utils::readU2(fp);

  return_value->end_pc = Utils::readU2(fp);
  
  return_value->handler_pc = Utils::readU2(fp);
  
  return_value->catch_type = Utils::readU2(fp);

  return return_value;
}

void Attributes::printAttributes(ConstantPool* cp,std::string baseTab)
{ 

  std::cout << baseTab << "Attributes count -> " << attributes_count << std::endl;
  
  int var;
  for(var = 0; var < attributes_count; var++ ) 
  {
    std::cout << baseTab << "\tAttribute " << var << ": " << std::endl;
    attributes[var]->printAttribute(cp,baseTab);
  }
}