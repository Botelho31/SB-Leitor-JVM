#include "Interfaces.h"


unsigned short *loadInterfaces (FILE* fp, int length){
	unsigned short *interfaces = (unsigned short *) malloc(sizeof(int) * length);

	for (int i = 0; i < length; i++){
    	interfaces[i] = readU2(fp);
	
    }

	return interfaces;
}