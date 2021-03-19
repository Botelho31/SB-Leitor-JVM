#include "../include/Reader.h"

Reader::Reader(char* filename){
    FILE * classFile = getFile(filename);
    
    if(classFile == NULL)
        return;

    JavaClass *dotClass = new JavaClass(classFile);

}

// char* Reader::getFileName()
// {
//     char* filename;
//     std::cout << "Digite um path válido para o arquivo .class" << std::endl;
//     ENDLINE
//     filename = "assets/ClassFileDemo.class";

//     return filename;
// }

FILE * Reader::getFile(char* filename){

    // char* fileName = getFileName();
    FILE* fp = fopen(filename, "rb");

	//verifica se o arquivo conseguiu ser aberto para leitura
	if (fp == NULL) {
        std::cout << "Arquivo não encontrado" << std::endl;
        return NULL;
	}else{
        return fp;
    }
}

Reader::~Reader(){
}