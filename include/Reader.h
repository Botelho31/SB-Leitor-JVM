#ifndef READER_H
    #define READER_H

    #define ENDLINE std::cout << std::endl;
    #include <iostream>
    #include <utility>
    #include <fstream>
    #include <vector>
    #include <memory>
    #include <cstdlib>
    // #include <bits/stdc++.h> 
    #include <ctime>
    
    class Reader{
        public:
            Reader();
            ~Reader();
        private:
            std::pair<int,char*> openFile();
            std::string getFileName();
    };

#endif