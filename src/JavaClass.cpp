#include "../include/JavaClass.h"


JavaClass::JavaClass(FILE *classFile){
    magic = Utils::readU4(classFile);
    if (!validateMagic(magic)){
        return;
    }

    minor_version = Utils::readU2(classFile);
    major_version = Utils::readU2(classFile);
    constant_pool_count = Utils::readU2(classFile);

    std::cout << "Constant Pool Count -> "<< constant_pool_count << std::endl;

    constant_pool = loadConstantPool(constant_pool_count, classFile);

    access_flags = Utils::readU2(classFile);
    this_class = Utils::readU2(classFile);
    super_class = Utils::readU2(classFile);


    std::cout << "Acess flags -> "<< access_flags << std::endl;

    std::cout << "This class -> "<< this_class << std::endl;

    std::cout << "Super class -> "<< super_class << std::endl;

    // interfaces_count = Utils::readU2(fp)
    // interfaces

    // methods_count = Utils::readU2(fp)
    // methods
    
    // attributes_count = Utils::readU2(fp)
    // attributes




}
    

JavaClass::~JavaClass(){
}

void JavaClass::printClass(){
    //minimo 26 bytes
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

bool JavaClass::validateMagic(u4 magic){
    
    if (magic != 0XCAFEBABE){
        std::cout << "Flag Magic inválida" << std::endl;
        return false;
    }else{

        std::cout << "Flag Magic Validada com sucesso" << std::endl;
        return true;
    }
    
}