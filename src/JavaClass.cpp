#include "../include/JavaClass.h"
#include <iostream>

// Minimo 26 Bytes
// ClassFile {
//      4-byte         magic;
//      2-byte         minor_version;
//      2-byte         major_version;
//      2-byte         constant_pool_count;
//      cp_info        constant_pool[constant_pool_count-1];
//      2-byte         access_flags;
//      2-byte         this_class;
//      2-byte         super_class;
//      2-byte         interfaces_count;
//      2-byte         interfaces[interfaces_count];
//      2-byte         fields_count;
//      field_info     fields[fields_count];
//      2-byte         methods_count;
//      method_info    methods[methods_count];
//      2-byte         attributes_count;
//      attribute_info attributes[attributes_count];
//  }

JavaClass::JavaClass(std::string hexString){
    
    std::cout << hexString << std::endl;
    
    int currentByte = 0;
    magic = Utils::hexSubstrByByte(hexString,currentByte,4);
    currentByte += 4;
    minor_version = Utils::hexSubstrByByte(hexString,currentByte,2);
    currentByte += 2;
    major_version = Utils::hexSubstrByByte(hexString,currentByte,2);
    currentByte += 2;
    constant_pool_count = Utils::hexSubstrByByte(hexString,currentByte,2);
    currentByte += 2;

    printClass();
    std::cout << Utils::getShortFromHex(constant_pool_count) << std::endl;


}

JavaClass::~JavaClass(){
}

void JavaClass::printClass(){
    // ClassFile {
    //      4-byte         magic;
    //      2-byte         minor_version;
    //      2-byte         major_version;
    //      2-byte         constant_pool_count;
    //      cp_info        constant_pool[constant_pool_count-1];
    //      2-byte         access_flags;
    //      2-byte         this_class;
    //      2-byte         super_class;
    //      2-byte         interfaces_count;
    //      2-byte         interfaces[interfaces_count];
    //      2-byte         fields_count;
    //      field_info     fields[fields_count];
    //      2-byte         methods_count;
    //      method_info    methods[methods_count];
    //      2-byte         attributes_count;
    //      attribute_info attributes[attributes_count];
    //  }
    std::cout << "Class{" << std::endl;
    std::cout << "\tmagic " << magic << std::endl;
    std::cout << "\tminor_version " << minor_version << std::endl;
    std::cout << "\tmajor_version " << major_version << std::endl;
    std::cout << "\tconstant_pool_count " << constant_pool_count << std::endl;
    std::cout << "}" << std::endl;
}

bool JavaClass::validateMagic(std::string hexString){
    std::string magicFlag = hexString.substr(0, 4*2);

    int isEqual = magicFlag.compare("CAFEBABE");

    std::cout << magicFlag << std::endl;
    
    if (isEqual == 0){
        std::cout << "Assinatura CAFEBABE válida" << std::endl;
        return true;
    }else{
        std::cout << "Assinatura CAFEBABE inválida" <<std::endl;
        return false;
    }
    
}