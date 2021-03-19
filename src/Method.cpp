#include "../include/Method.h"

Method::Method(FILE *fp, ConstantPool *cp){
    access_flags = Utils::readU2(fp) & 0xFFF;
    name_index = Utils::readU2(fp);
    descriptor_index = Utils::readU2(fp);
    attributes = new Attributes(fp, cp);
}

Method::~Method(){
}

std::string Method::getMethodFlags(uint16_t flags){
    bool first = true;
    std::string ret = "";

    if (flags & 0x01)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_PUBLIC";
    }

    if (flags & 0x02)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_PRIVATE";
    }

    if (flags & 0x04)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_PROTECTED";
    }

    if (flags & 0x08)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_STATIC";
    }

    if (flags & 0x010)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_FINAL";
    }

    if (flags & 0x020)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_SYNCHRONIZED";
    }

    if (flags & 0x0100)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_NATIVE";
    }

    if (flags & 0x0400)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_ABSTRACT";
    }

    if (flags & 0x0800)
    {
        if (first)
        {
            ret += "\tflags: ";
            first = false;
        }
        else
        {
            ret += ", ";
        }
        ret += "ACC_STRICT";
    }

    ret += "\n";

    return ret;
}

void Method::printMethod(ConstantPool *cp){

    std::cout << "\tName: cp info #" << name_index << " " << cp->dereferenceIndex(name_index) << std::endl;

    std::cout << "\tDescriptor: cp info # " << descriptor_index << cp->dereferenceIndex(descriptor_index) << std::endl;

    std::cout << "" << getMethodFlags(access_flags);

    attributes->printAttributes(cp,"\t");
}
