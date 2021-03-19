#include "../include/Attribute.h"

Attribute::Attribute (FILE* fp, ConstantPool *cp) {
  name_index = Utils::readU2(fp);
  length = Utils::readU4(fp);
  info = readAttributeInfo(fp, cp);
}

void Attribute::printAttribute (ConstantPool *cp,std::string baseTab) {
  std::string name_of_attribute = cp->dereferenceIndex(name_index);

  std::cout << baseTab << "\t\tName: cp info #" << name_index << " " <<  name_of_attribute << std::endl;

  std::cout << baseTab << "\t\tAttribute lenght: " << length << std::endl;

  if(name_of_attribute == "ConstantValue") 
  {
    std::cout << baseTab << "\t\tConstant Value: " << info->constantvalue.constantvalue_index << std::endl;
  }

  else if(name_of_attribute == "Code") 
  {
    
    std::cout << baseTab << "\t\tMisc: " << std::endl;
    std::cout << baseTab << "\t\t\tMax Stack: " << info->code.max_stack << std::endl;
    std::cout << baseTab << "\t\t\tMax Locals: " << info->code.max_locals << std::endl;
    std::cout << baseTab << "\t\t\tCode Length: " << info->code.code_length << std::endl;

    int var = 0;

    std::cout << baseTab << "\t\tBytecode: " << std::endl;
    
    while((unsigned int) var < info->code.code_length) 
    {
      std::cout << baseTab << "\t\t\t" << var << "  " << Utils::getMnemonic(info->code.code[var]);
      Utils::getOpcodeParams(info->code.code, &var);
      std::cout << baseTab << std::endl;
    }

    std::cout << baseTab << "\t\tException Table Length: " << info->code.exception_table_length << std::endl;

    for(int var = 0; var < info->code.exception_table_length; var++ )
    {
      std::cout << baseTab << "\t\tStart   PC: " << info->code.exception_table[var]->start_pc << std::endl;
      std::cout << baseTab << "\t\tEnd     PC: " << info->code.exception_table[var]->end_pc << std::endl;
      std::cout << baseTab << "\t\tHandler PC: " << info->code.exception_table[var]->handler_pc << std::endl;
      std::cout << baseTab << "\t\tCatch Type: " << info->code.exception_table[var]->catch_type << std::endl;
    }

    info->code.attributes->printAttributes(cp,baseTab + "\t\t");
  }

  else if(name_of_attribute == "Exceptions") 
  {
    std::cout << baseTab << "\t\tNumber of Exceptions: " << info->exception.number_of_exceptions << std::endl;

    for(int var = 0; var < info->exception.number_of_exceptions; var++ ) {
      
      std::cout << baseTab << "\t\tException Index: " << info->exception.exception_index_table[var] << std::endl; 
    }
  }
}


t_info* Attribute::readAttributeInfo(FILE* fp, ConstantPool *cp){
  t_info* info_reading = (t_info*) malloc(sizeof(t_info));

  std::string name_of_attribute = cp->dereferenceIndex(name_index);

  if(name_of_attribute == "ConstantValue") 
  {
    info_reading->constantvalue.constantvalue_index = Utils::readU2(fp);
  }

  else if(name_of_attribute == "Code")
  {
    info_reading->code.max_stack = Utils::readU2(fp);
    
    info_reading->code.max_locals = Utils::readU2(fp);
    
    info_reading->code.code_length = Utils::readU4(fp);

    unsigned char* list_code = (unsigned char*) malloc(sizeof(t_exception_table) * info_reading->code.code_length);

    for(int i = 0; (unsigned int) i < info_reading->code.code_length; i++ )
    {
      list_code[i] = Utils::readU1(fp);
    }
    info_reading->code.code = list_code;    

    info_reading->code.exception_table_length = Utils::readU2(fp);

    t_exception_table** table_of_exception = (t_exception_table**) malloc(sizeof(t_exception_table) * info_reading->code.exception_table_length);
    
    for(int i = 0; i < info_reading->code.exception_table_length; i++ ) 
    {
      table_of_exception[i] = readExceptionHandler(fp);
    }
    
    info_reading->code.exception_table = table_of_exception;

    Attributes* attributes_infos = new Attributes(fp,cp);

    info_reading->code.attributes = attributes_infos;
  }

  else if(name_of_attribute == "Exceptions") 
  {
    info_reading->exception.number_of_exceptions = Utils::readU2(fp);

    unsigned short* exceptions = (unsigned short*) malloc(sizeof(unsigned short) * info_reading->exception.number_of_exceptions);
    
    for(int i = 0; i < info_reading->exception.number_of_exceptions; i++ ) 
    {
      exceptions[i] = Utils::readU2(fp);
    }
    info_reading->exception.exception_index_table = exceptions;
  }
  
  else 
  {
    for(int i = 0; i < length; i++ )
    {
      Utils::readU1(fp);
    }
  }

  return info_reading;
}

t_exception_table* Attribute::readExceptionHandler(FILE* fp){
  t_exception_table* return_value = (t_exception_table*) malloc(sizeof(t_exception_table));

  return_value->start_pc = Utils::readU2(fp);

  return_value->end_pc = Utils::readU2(fp);
  
  return_value->handler_pc = Utils::readU2(fp);
  
  return_value->catch_type = Utils::readU2(fp);

  return return_value;
}