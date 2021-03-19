#include "../include/JavaClass.h"


JavaClass::JavaClass(FILE *classFile){
    
    try{
        magic = Utils::readU4(classFile);
        if (!validateMagic(magic)){
            return;
        }

        minor_version = Utils::readU2(classFile);
        major_version = Utils::readU2(classFile);

        constant_pool = new ConstantPool(classFile);

        access_flags = Utils::readU2(classFile);
        this_class = Utils::readU2(classFile);
        super_class = Utils::readU2(classFile);

        interfaces = new Interfaces(classFile);

        fields = new Fields(classFile,constant_pool);

        methods = new Methods(classFile,constant_pool);

        attributes = new Attributes(classFile, constant_pool);
    } catch(std::string e){
        std::cout << e << std::endl;
        return;
    }
    
    printClass();
	
    fclose(classFile);
	classFile = NULL;
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

    std::cout << "Minor version -> "<< minor_version << std::endl;
    std::cout << "Major version -> "<< major_version << std::endl;

    std::cout << "-------------------------------------" << std::endl;
    constant_pool->printConstantPool();
    std::cout << "-------------------------------------" << std::endl;
    
    std::cout << "Access flags -> "<< access_flags << std::endl;
    std::cout << "This class -> "<< this_class << std::endl;
    std::cout << "Super class -> "<< super_class << std::endl;

    std::cout << "-------------------------------------" << std::endl;
    interfaces->printInterfaces(constant_pool);
    std::cout << "-------------------------------------" << std::endl;
    fields->printFields(constant_pool);
    std::cout << "-------------------------------------" << std::endl;
    methods->printMethods(constant_pool);
    std::cout << "-------------------------------------" << std::endl;
    attributes->printAttributes(constant_pool);
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