#include "../include/Reader.h"

int main(int argc, char ** argv){
    std::cout << "Argument Size " << argc <<std::endl << std::endl;
    Reader *reader = new  Reader(argv[1]);
    return 0;
}