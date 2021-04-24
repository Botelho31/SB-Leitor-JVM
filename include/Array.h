#ifndef JAVA_H
    #include "JavaClass.h"
#endif


#ifndef ARRAY_HPP
    #define ARRAY_HPP

    #include "Types.h"

    class Array
    {
    public:
        Array();
        ~Array();

        std::vector<typedElement*> data;
    };

#endif