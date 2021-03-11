#ifndef READER_H
    #define READER_H

    #define ENDLINE std::cout << std::endl;
    #include <iostream>
    #include <utility>
    #include <fstream>
    #include <vector>
    #include <memory>
    #include <cstdlib>
    #include <sstream>
    #include <ctime>
    
    #include "Types.h"
    #include "Utils.h"
    #include "JavaClass.h"
    #include "ConstantPool.h"

    class Reader{
        public:
            Reader();
            ~Reader();
        private:
            FILE * getFile();
            char* getFileName();
    };

#endif