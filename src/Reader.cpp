#include "../include/Reader.h"

Reader::Reader()
{
    std::pair<int, char*> pairbuffer = openFile();
    //first length second array
    ENDLINE;

    std::string hexString = Utils::getHexadecimalFromByte(pairbuffer.second, pairbuffer.first);
    
    JavaClass *dotClass = new JavaClass(hexString);

}




std::string Reader::getFileName()
{
    std::string filename;
    std::cout << "Digite um path válido para o arquivo .class" << std::endl;
    ENDLINE
    // std::cin >> filename;
    filename = "assets/ClassFileDemo.class";

    return filename;
}

std::pair<int, char*> Reader::openFile()
{
    std::string fileName = getFileName();

    std::ifstream myFile;
    myFile.open(fileName, std::ios::out | std::ios::binary);

    std::cout << "Name Of File: " << fileName << std::endl;
    ENDLINE;

    if (myFile)
    {
        // get length of file:
        myFile.seekg (0, myFile.end);
        int length = myFile.tellg();
        myFile.seekg (0, myFile.beg);

        char * buffer = (char*)malloc(sizeof(char) * length);

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        myFile.read (buffer,length);

        if (myFile)
            std::cout << "all characters read successfully.";
        else
            std::cout << "error: only " << myFile.gcount() << " could be read";

        myFile.close();
        
        ENDLINE

        return std::make_pair(length, buffer);

    }
    else
    {
        return openFile();
    }
}

Reader::~Reader()
{
}