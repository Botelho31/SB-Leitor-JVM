#include "Heap.h"

std::vector<ClasseInstancia*> Heap::objetos;

void Heap::addObject(ClasseInstancia *ci){
	objetos.push_back(ci);
}
