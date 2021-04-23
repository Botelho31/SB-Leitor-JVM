#include "../include/MethodArea.h"

std::map<std::string, ClasseEstatica*> MethodArea::classes;
std::string MethodArea::path = "";
FrameStack *MethodArea::fs = nullptr;

ClasseEstatica *MethodArea::getClass(std::string s)
{    
    for (std::map<std::string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++)
    {
        if (i->first == s)
        {
            return i->second;
        }
    }
    return nullptr;
}

bool MethodArea::addClass(std::string s)
{
    for (std::map<std::string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++)
    {
       if (i->first == s)
       {
            return false;
       }
    }

    JavaClass *l = new JavaClass(std::string(path+s));


    if (!l->validExtension())
    {
        delete l;
        l = new JavaClass(std::string(path+s+".class"));
    }

    if (l->load())
    {
        return false;
    }

    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(std::pair<std::string, ClasseEstatica*>(s, add));

    if (l->hasClinit())
    {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

bool MethodArea::addClass(JavaClass *l)
{
    if (l->getStatus() == -1)
    {
        l->load();
    }

    switch (l->getStatus())
    {
        case 0:
            break;
        default:
            return false;
    }

    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(std::pair<std::string, ClasseEstatica*>(l->getCP()->dereferenceIndex(l->getThis_class()), add));

    if (l->hasClinit())
    {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

void MethodArea::setFrameStack(FrameStack *newFS)
{
    fs = newFS;
}