#include "../include/ConstantPool.h"


ConstantPool::ConstantPool(FILE* fp){

	constant_pool_count = Utils::readU2(fp);
    constant_pool = (cp_info *) malloc(sizeof(cp_info) * constant_pool_count);

	for (int i = 1; i < constant_pool_count; i++){

		constant_pool[i].tag = Utils::readU1(fp);
		
		if (constant_pool[i].tag < 0 || constant_pool[i].tag > 12 || constant_pool[i].tag == 2){
			std::string exception = "Erro com o tag não identificado - " + std::to_string((int)constant_pool[i].tag); 
			throw exception;
            return;
		}

        if (constant_pool[i].tag == UTF8){ 
            constant_pool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
            constant_pool[i].info[0].U2 = Utils::readU2(fp);
            constant_pool[i].info[1].array = Utils::readUTF8(fp, constant_pool[i].info[0].U2);

        }else if(constant_pool[i].tag == INTEGER || constant_pool[i].tag == FLOAT){
            constant_pool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constant_pool[i].info[0].U4 = Utils::readU4(fp);

        }else if(constant_pool[i].tag == LONG || constant_pool[i].tag == DOUBLE){         
            constant_pool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constant_pool[i].info[0].U4 = Utils::readU4(fp);
            constant_pool[++i].tag = INVALID;
            constant_pool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constant_pool[i].info[0].U4 = Utils::readU4(fp);

        }else if(constant_pool[i].tag == CLASS || constant_pool[i].tag == STRING){   
            constant_pool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constant_pool[i].info[0].U2 = Utils::readU2(fp);

        }else if(constant_pool[i].tag == FIELD_REF || constant_pool[i].tag == METHOD_REF || constant_pool[i].tag == INTERFACE_REF || constant_pool[i].tag == NAME_AND_TYPE){
            constant_pool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
            constant_pool[i].info[0].U2 = Utils::readU2(fp);
            constant_pool[i].info[1].U2 = Utils::readU2(fp);
        }
	}
}

std::string ConstantPool::dereferenceIndex (u2 index){
	switch (constant_pool[index].tag){
		case UTF8:
			// Return the string
			return Utils::showUTF8(constant_pool[index].info[1].array, constant_pool[index].info[0].U2);

		case CLASS:
		case STRING:
			// Get the string from the info field
			return dereferenceIndex(constant_pool[index].info[0].U2);

		case NAME_AND_TYPE:
			// Get the string from the two info fields separeted bi ':'
			return (dereferenceIndex(constant_pool[index].info[0].U2) + "  " + dereferenceIndex(constant_pool[index].info[1].U2));

		case METHOD_REF:
		case INTERFACE_REF:
		case FIELD_REF:
			// Get the string from the two info fields separeted bi '.'
			return (dereferenceIndex(constant_pool[index].info[0].U2) + "  " + dereferenceIndex(constant_pool[index].info[1].U2));
	}
	return "";
}

void ConstantPool::printConstantPool(){

	std::cout << "Constant pool count -> "<< constant_pool_count << std::endl;
	std::cout << "Constant Pool:" << std::endl;
	
	for (int i = 1; i < constant_pool_count; i++) {	
		printf("\t [%3d] ",i);
		switch (constant_pool[i].tag){
			case UTF8: //tem um campo u2 e um array de u1 como info
				std::cout << "\t" << Utils::showUTF8(constant_pool[i].info[1].array, constant_pool[i].info[0].U2);
				break;
			case INTEGER: //tem apenas um campo u4 em info
				std::cout << "\t" << constant_pool[i].info[0].U4;
				break;
			case FLOAT: //tem apenas um campo u4 em info que deve ser convertido para float
				std::cout << "\t" << Utils::u4ToFloat(constant_pool[i].info[0]) << "f";
				break;
			case LONG: //tem dois campos u4 em info que devem ser convertidos em um long
				std::cout << "\t" << Utils::u4ToLong(constant_pool[i].info[0], constant_pool[i+1].info[0]) << "l";
				i++; //para ignorar o proximo slot
				break;
			case DOUBLE: //tem dois campos u4 em infoque devem ser convertidos em um double
				std::cout << "\t" << Utils::u4ToDouble(constant_pool[i].info[0], constant_pool[i+1].info[0]) << "d";
				i++; //para ignorar o proximo slot
				break;
			case CLASS: //tem apenas um campo u2 em info
			case STRING:
				std::cout << " " << constant_pool[i].info[0].U2 << "\t\t// " << dereferenceIndex(i);
				break;
			case NAME_AND_TYPE: //tipo que tem dois campos u2 de info e usam o ':' para separar eles
				std::cout << " cp info #" << constant_pool[i].info[0].U2 << "  cp info #" << constant_pool[i].info[1].U2;
				std::cout << "\t\t// " << dereferenceIndex(i);
				break;
			case METHOD_REF: //tipos que tem dois campos u2 de info e usam o '.' para separar eles
			case INTERFACE_REF:
			case FIELD_REF:
				std::cout << " cp info #" << constant_pool[i].info[0].U2 << "  cp info #" << constant_pool[i].info[1].U2;
				std::cout << "\t\t// " << dereferenceIndex(i);
				break;
		}
		ENDLINE;
	}
		ENDLINE;
}