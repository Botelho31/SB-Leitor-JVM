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
    
    typedef uint8_t  u1;
    typedef uint16_t u2;
    typedef uint32_t u4;
    typedef uint64_t u8;

    #include "Utils.h"
    #include "JavaClass.h"

    class Reader{
        public:
            Reader();
            ~Reader();
        private:
            std::pair<int,char*> openFile();
            std::string getFileName();
    };

#endif