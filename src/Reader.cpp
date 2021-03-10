#include "../include/Reader.h"

Reader::Reader(std::string NameOfFile){
    std::fstream FileReader;
    FileReader.open(NameOfFile);
    std::string checkline;
    if (FileReader.is_open()) {
        while (!FileReader.eof()) {
            FileReader >> checkline; 
            std::cout << checkline;
        }
    }else{
        ENDLINE
        std::cout << "No .class Found" << std::endl; //Printa um erro caso nao consiga dar load na file
    }
    FileReader.close();
}

Reader::~Reader(){
}