#include "../include/Reader.h"

int main(int argc, char ** argv){
    std::cout << argc << argv << "\n" << std::endl;
    Reader *reader = new  Reader("assets/java.class");
    return 0;
}