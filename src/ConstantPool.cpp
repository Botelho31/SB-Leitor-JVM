#include "../include/ConstantPool.h"


cp_info* loadConstantPool(int lengthCP, FILE* fp){
	
    cp_info *constantPool = (cp_info *) malloc(sizeof(cp_info) * lengthCP);

	for (int i = 1; i < lengthCP; i++){
		constantPool[i].tag = Utils::readU1(fp);
		
		if (constantPool[i].tag < 0 || constantPool[i].tag > 12 || constantPool[i].tag == 2){
            std::cout << "Erro com o tipo não identificado" << std::endl;
            return constantPool;
		}

        if (constantPool[i].tag == UTF8){ 
            constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
            constantPool[i].info[0].U2 = Utils::readU2(fp);
            constantPool[i].info[1].array = Utils::readUTF8(fp, constantPool[i].info[0].U2);

        }else if(constantPool[i].tag == INTEGER || constantPool[i].tag == FLOAT){
            constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constantPool[i].info[0].U4 = Utils::readU4(fp);

        }else if(constantPool[i].tag == LONG || constantPool[i].tag == DOUBLE){         
            constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constantPool[i].info[0].U4 = Utils::readU4(fp);
            constantPool[++i].tag = INVALID;
            constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constantPool[i].info[0].U4 = Utils::readU4(fp);

        }else if(constantPool[i].tag == CLASS || constantPool[i].tag == STRING){   
            constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
            constantPool[i].info[0].U2 = Utils::readU2(fp);

        }else if(constantPool[i].tag == FIELD_REF || constantPool[i].tag == METHOD_REF || constantPool[i].tag == INTERFACE_REF || constantPool[i].tag == NAME_AND_TYPE){
            constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
            constantPool[i].info[0].U2 = Utils::readU2(fp);
            constantPool[i].info[1].U2 = Utils::readU2(fp);
        }
	}

	// Retorna a propria constantPool
	return constantPool;
}