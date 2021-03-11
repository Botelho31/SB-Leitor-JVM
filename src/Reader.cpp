#include "../include/Reader.h"

Reader::Reader()
{
    FILE * classFile = getFile();
    
    JavaClass *dotClass = new JavaClass(classFile);

}

char* Reader::getFileName()
{
    char* filename;
    std::cout << "Digite um path válido para o arquivo .class" << std::endl;
    ENDLINE
    // std::cin >> filename;
    filename = "assets/ClassFileDemo.class";

    return filename;
}

FILE * Reader::getFile()
{

    char* fileName = getFileName();
    FILE* fp = fopen(fileName, "rb");

	//verifica se o arquivo conseguiu ser aberto para leitura
	if (fp == NULL) {
        return getFile();
	}else{
        return fp;
    }
}

Reader::~Reader()
{
}